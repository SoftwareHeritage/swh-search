# Copyright (C) 2019-2024  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import logging
from pathlib import Path
import socket
import subprocess
import textwrap
import time

import elasticsearch
import pytest

from swh.search import get_search

logger = logging.getLogger(__name__)


def free_port():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("127.0.0.1", 0))
    port = sock.getsockname()[1]
    sock.close()
    return port


CONFIG_TEMPLATES = {
    "elasticsearch.yml": """\
        action.auto_create_index: false
        action.destructive_requires_name: false
        cluster.routing.allocation.disk.threshold_enabled: false
        discovery.type: single-node
        http.port: {http_port}
        network.host: 127.0.0.1
        node.name: node-1
        path.data: {data}
        path.logs: {logs}
        stack.templates.enabled: false
        transport.port: {transport_port}
        xpack.ml.enabled: false
        xpack.security.enabled: false
    """,
    "jvm.options": """\
        -XX:+UseG1GC
        -Djava.io.tmpdir={data}
        20-:--add-modules=jdk.incubator.vector
        -XX:+HeapDumpOnOutOfMemoryError
        -XX:+ExitOnOutOfMemoryError
        -XX:HeapDumpPath={logs}
        -XX:ErrorFile={logs}/hs_err_pid%p.log
        -Xlog:gc*,gc+age=trace,safepoint:file={logs}/gc.log:utctime,level,pid,tags:filecount=32,filesize=64m
        -Xms512m
        -Xmx512m
    """,
    "log4j2.properties": """\
        status = error

        appender.console.type = Console
        appender.console.name = console
        appender.console.layout.type = PatternLayout
        appender.console.layout.pattern = [%d{{ISO8601}}][%-5p][%-25c{{1.}}] [%node_name]%marker %m%consoleException%n

        rootLogger.level = info
        rootLogger.appenderRef.console.ref = console
    """,  # noqa
}

ES_HOME = "/usr/share/elasticsearch"


def _get_es_version():
    """Parse /usr/share/elasticsearch/lib/elasticsearch-X.Y.Z.jar into X"""
    jars = list(Path(f"{ES_HOME}/lib").glob("elasticsearch-[0-9]*.jar"))
    if len(jars) != 1:
        raise ValueError(f"Found unexpected contents in {ES_HOME}/lib: {jars}")

    jarfile = jars[0]
    major = jarfile.stem.split("-")[-1].split(".")[0]
    return int(major)


def _run_elasticsearch(
    conf_dir, data_dir, logs_dir, http_port, transport_port, libffi_tmpdir
):
    for filename, template in CONFIG_TEMPLATES.items():
        with open(f"{conf_dir}/{filename}", "w") as fd:
            fd.write(
                textwrap.dedent(template).format(
                    data=data_dir,
                    logs=logs_dir,
                    http_port=http_port,
                    transport_port=transport_port,
                )
            )

    major = _get_es_version()
    if major >= 8:
        cmd = [
            f"{ES_HOME}/jdk/bin/java",
            "-Dcli.name=server",
            f"-Dcli.script={ES_HOME}/bin/elasticsearch",
            "-Dcli.libs=lib/tools/server-cli",
            f"-Des.path.home={ES_HOME}",
            f"-Des.path.conf={conf_dir}",
            "-Des.distribution.type=deb",
            "-Des.bundled_jdk=true",
            "-cp",
            f"{ES_HOME}/lib/*:{ES_HOME}/lib/cli-launcher/*",
            "org.elasticsearch.launcher.CliToolLauncher",
        ]
    else:
        cmd = [
            f"{ES_HOME}/jdk/bin/java",
            f"-Des.path.home={ES_HOME}",
            f"-Des.path.conf={conf_dir}",
            "-Des.bundled_jdk=true",
            "-Dlog4j2.disable.jmx=true",
            # fix UnsupportedOperationException related to deprecated Security Manager
            # when using JDK >= 18
            "-Djava.security.manager=allow",
            "-cp",
            f"{ES_HOME}/lib/*",
            "org.elasticsearch.bootstrap.Elasticsearch",
        ]

    process = subprocess.Popen(cmd, cwd=ES_HOME, env={"LIBFFI_TMPDIR": libffi_tmpdir})

    for _ in range(3000):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect(("127.0.0.1", http_port))
        except ConnectionRefusedError:
            if process.poll() is not None:

                # process has exited
                break

            time.sleep(0.1)
        else:
            sock.close()
            break

    host = f"http://127.0.0.1:{http_port}"
    client = elasticsearch.Elasticsearch([host])
    assert client.ping()

    return process, major


@pytest.fixture(scope="session")
def elasticsearch_session(tmpdir_factory):
    tmpdir = tmpdir_factory.mktemp("elasticsearch")
    es_conf = tmpdir.mkdir("conf")

    http_port = free_port()
    transport_port = free_port()

    proc, major = _run_elasticsearch(
        conf_dir=str(es_conf),
        data_dir=str(tmpdir.mkdir("data")),
        logs_dir=str(tmpdir.mkdir("logs")),
        http_port=http_port,
        transport_port=transport_port,
        libffi_tmpdir=str(tmpdir.mkdir("libffi")),
    )

    yield f"http://127.0.0.1:{http_port}"

    # Check ES didn't stop
    assert proc.returncode is None, proc.returncode

    proc.terminate()
    if major < 8:
        proc.kill()
    proc.wait()


@pytest.fixture(scope="class")
def elasticsearch_host(elasticsearch_session):
    yield elasticsearch_session


@pytest.fixture
def swh_search(elasticsearch_host):
    """Instantiate a search client, initialize the elasticsearch instance,
    and returns it

    """
    logger.debug("swh_search: elasticsearch_host: %s", elasticsearch_host)
    search = get_search(
        "elasticsearch",
        hosts=[elasticsearch_host],
        indexes={
            "origin": {
                "index": "test",
                "read_alias": "test-read",
                "write_alias": "test-write",
            }
        },
    )
    search.deinitialize()  # To reset internal state from previous runs
    search.initialize()  # install required index
    yield search
