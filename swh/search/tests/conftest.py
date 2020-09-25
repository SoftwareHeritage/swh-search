# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import logging
import socket
import subprocess
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


def wait_for_peer(addr, port):
    while True:
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((addr, port))
        except ConnectionRefusedError:
            time.sleep(0.1)
        else:
            sock.close()
            break


CONFIG_TEMPLATE = """
node.name: node-1
path.data: {data}
path.logs: {logs}
network.host: 127.0.0.1
http.port: {http_port}
transport.port: {transport_port}
"""


def _run_elasticsearch(conf_dir, data_dir, logs_dir, http_port, transport_port):
    es_home = "/usr/share/elasticsearch"

    with open(conf_dir + "/elasticsearch.yml", "w") as fd:
        fd.write(
            CONFIG_TEMPLATE.format(
                data=data_dir,
                logs=logs_dir,
                http_port=http_port,
                transport_port=transport_port,
            )
        )

    with open(conf_dir + "/log4j2.properties", "w") as fd:
        pass

    cmd = [
        "/usr/share/elasticsearch/jdk/bin/java",
        "-Des.path.home={}".format(es_home),
        "-Des.path.conf={}".format(conf_dir),
        "-Des.bundled_jdk=true",
        "-Dlog4j2.disable.jmx=true",
        "-cp",
        "{}/lib/*".format(es_home),
        "org.elasticsearch.bootstrap.Elasticsearch",
    ]

    host = "127.0.0.1:{}".format(http_port)

    with open(logs_dir + "/output.txt", "w") as fd:
        p = subprocess.Popen(cmd)

    wait_for_peer("127.0.0.1", http_port)

    client = elasticsearch.Elasticsearch([host])
    assert client.ping()

    return p


@pytest.fixture(scope="session")
def elasticsearch_session(tmpdir_factory):
    tmpdir = tmpdir_factory.mktemp("elasticsearch")
    es_conf = tmpdir.mkdir("conf")

    http_port = free_port()
    transport_port = free_port()

    p = _run_elasticsearch(
        conf_dir=str(es_conf),
        data_dir=str(tmpdir.mkdir("data")),
        logs_dir=str(tmpdir.mkdir("logs")),
        http_port=http_port,
        transport_port=transport_port,
    )

    yield "127.0.0.1:{}".format(http_port)

    # Check ES didn't stop
    assert p.returncode is None, p.returncode

    p.kill()
    p.wait()


@pytest.fixture(scope="class")
def elasticsearch_host(elasticsearch_session):
    yield elasticsearch_session


@pytest.fixture
def swh_search(elasticsearch_host):
    """Instantiate a search client, initialize the elasticsearch instance,
    and returns it

    """
    logger.debug("swh_search: elasticsearch_host: %s", elasticsearch_host)
    search = get_search("elasticsearch", hosts=[elasticsearch_host],)
    search.deinitialize()  # To reset internal state from previous runs
    search.initialize()  # install required index
    yield search
