# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import copy
import tempfile

from click.testing import CliRunner
from confluent_kafka import Producer
import pytest
import yaml

from swh.journal.serializers import value_to_kafka
from swh.model.hashutil import hash_to_bytes
from swh.search.cli import search_cli_group

CLI_CONFIG = """
search:
    cls: elasticsearch
    args:
        hosts:
        - '%(elasticsearch_host)s'
"""

JOURNAL_OBJECTS_CONFIG_TEMPLATE = """
journal:
    brokers:
        - {broker}
    prefix: {prefix}
    group_id: {group_id}
"""


def invoke(catch_exceptions, args, config="", *, elasticsearch_host):
    runner = CliRunner()
    with tempfile.NamedTemporaryFile("a", suffix=".yml") as config_fd:
        config_fd.write(
            (CLI_CONFIG + config) % {"elasticsearch_host": elasticsearch_host}
        )
        config_fd.seek(0)
        result = runner.invoke(search_cli_group, ["-C" + config_fd.name] + args)
    if not catch_exceptions and result.exception:
        print(result.output)
        raise result.exception
    return result


def test__journal_client__origin(
    swh_search, elasticsearch_host: str, kafka_prefix: str, kafka_server
):
    """Tests the re-indexing when origin_batch_size*task_batch_size is a
    divisor of nb_origins."""
    producer = Producer(
        {
            "bootstrap.servers": kafka_server,
            "client.id": "test search origin producer",
            "acks": "all",
        }
    )
    origin_foobar_baz = {
        "url": "http://foobar.baz",
    }
    value = value_to_kafka(origin_foobar_baz)
    topic = f"{kafka_prefix}.origin"
    producer.produce(topic=topic, key=b"bogus-origin", value=value)

    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker=kafka_server, prefix=kafka_prefix, group_id="test-consumer"
    )
    result = invoke(
        False,
        [
            "journal-client",
            "objects",
            "--stop-after-objects",
            "1",
            "--object-type",
            "origin",
            "--prefix",
            kafka_prefix,
        ],
        journal_objects_config,
        elasticsearch_host=elasticsearch_host,
    )

    # Check the output
    expected_output = "Processed 1 messages.\nDone.\n"
    assert result.exit_code == 0, result.output
    assert result.output == expected_output

    swh_search.flush()

    # searching origin without visit as requirement
    actual_page = swh_search.origin_search(url_pattern="foobar")
    # We find it
    assert actual_page.next_page_token is None
    assert actual_page.results == [origin_foobar_baz]

    # It's an origin with no visit, searching for it with visit
    actual_page = swh_search.origin_search(url_pattern="foobar", with_visit=True)
    # returns nothing
    assert actual_page.next_page_token is None
    assert actual_page.results == []


def test__journal_client__origin_visit(
    swh_search, elasticsearch_host, kafka_prefix: str, kafka_server
):
    """Tests the re-indexing when origin_batch_size*task_batch_size is a
    divisor of nb_origins."""
    origin_foobar = {"url": "http://baz.foobar"}
    producer = Producer(
        {
            "bootstrap.servers": kafka_server,
            "client.id": "test search origin visit producer",
            "acks": "all",
        }
    )
    topic = f"{kafka_prefix}.origin_visit"
    value = value_to_kafka({"origin": origin_foobar["url"]})
    producer.produce(topic=topic, key=b"bogus-origin-visit", value=value)

    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker=kafka_server, prefix=kafka_prefix, group_id="test-consumer"
    )
    result = invoke(
        False,
        [
            "journal-client",
            "objects",
            "--stop-after-objects",
            "1",
            "--object-type",
            "origin_visit",
        ],
        journal_objects_config,
        elasticsearch_host=elasticsearch_host,
    )

    # Check the output
    expected_output = "Processed 1 messages.\nDone.\n"
    assert result.exit_code == 0, result.output
    assert result.output == expected_output

    swh_search.flush()

    # Both search returns the visit
    actual_page = swh_search.origin_search(url_pattern="foobar", with_visit=False)
    assert actual_page.next_page_token is None
    assert actual_page.results == [origin_foobar]

    actual_page = swh_search.origin_search(url_pattern="foobar", with_visit=True)
    assert actual_page.next_page_token is None
    assert actual_page.results == [origin_foobar]


def test__journal_client__origin_visit_status(
    swh_search, elasticsearch_host, kafka_prefix: str, kafka_server
):
    """Subscribing to origin-visit-status should result in swh-search indexation

    """
    origin_foobar = {"url": "http://baz.foobar"}
    producer = Producer(
        {
            "bootstrap.servers": kafka_server,
            "client.id": "test search origin visit status producer",
            "acks": "all",
        }
    )
    topic = f"{kafka_prefix}.origin_visit_status"
    value = value_to_kafka(
        {
            "origin": origin_foobar["url"],
            "visit": 1,
            "snapshot": None,
            "status": "full",
        }
    )
    producer.produce(topic=topic, key=b"bogus-origin-visit-status", value=value)

    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker=kafka_server, prefix=kafka_prefix, group_id="test-consumer"
    )
    result = invoke(
        False,
        [
            "journal-client",
            "objects",
            "--stop-after-objects",
            "1",
            "--prefix",
            kafka_prefix,
            "--object-type",
            "origin_visit_status",
        ],
        journal_objects_config,
        elasticsearch_host=elasticsearch_host,
    )

    # Check the output
    expected_output = "Processed 1 messages.\nDone.\n"
    assert result.exit_code == 0, result.output
    assert result.output == expected_output

    swh_search.flush()

    # Both search returns the visit
    actual_page = swh_search.origin_search(url_pattern="foobar", with_visit=False)
    assert actual_page.next_page_token is None
    assert actual_page.results == [origin_foobar]

    actual_page = swh_search.origin_search(url_pattern="foobar", with_visit=True)
    assert actual_page.next_page_token is None
    assert actual_page.results == [origin_foobar]


def test__journal_client__origin_intrinsic_metadata(
    swh_search, elasticsearch_host, kafka_prefix: str, kafka_server
):
    """Subscribing to origin-intrinsic-metadata should result in swh-search indexation

    """
    origin_foobar = {"url": "https://github.com/clojure/clojure"}

    origin_intrinsic_metadata = {
        "id": origin_foobar["url"],
        "metadata": {
            "name": "clojure",
            "type": "SoftwareSourceCode",
            "license": "http://opensource.org/licenses/eclipse-1.0.php",
            "version": "1.10.2-master-SNAPSHOT",
            "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
            "identifier": "org.clojure",
            "description": "Clojure core environment and runtime library.",
            "codeRepository": "https://repo.maven.apache.org/maven2/org/clojure/clojure",  # noqa
        },
        "indexer_configuration_id": 1,
        "from_revision": hash_to_bytes("f47c139e20970ee0852166f48ee2a4626632b86e"),
        "mappings": ["maven"],
    }

    producer = Producer(
        {
            "bootstrap.servers": kafka_server,
            "client.id": "test search origin intrinsic metadata producer",
            "acks": "all",
        }
    )
    topic = f"{kafka_prefix}.origin_intrinsic_metadata"
    value = value_to_kafka(origin_intrinsic_metadata)
    producer.produce(topic=topic, key=b"bogus-origin-intrinsic-metadata", value=value)

    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker=kafka_server, prefix=kafka_prefix, group_id="test-consumer"
    )
    result = invoke(
        False,
        [
            "journal-client",
            "objects",
            "--stop-after-objects",
            "1",
            "--object-type",
            "origin_intrinsic_metadata",
        ],
        journal_objects_config,
        elasticsearch_host=elasticsearch_host,
    )

    # Check the output
    expected_output = "Processed 1 messages.\nDone.\n"
    assert result.exit_code == 0, result.output
    assert result.output == expected_output

    swh_search.flush()

    # search without visit returns the metadata
    actual_page = swh_search.origin_search(url_pattern="clojure", with_visit=False)
    assert actual_page.next_page_token is None
    assert actual_page.results == [origin_foobar]

    # no visit associated so it does not return anything
    actual_page = swh_search.origin_search(url_pattern="clojure", with_visit=True)
    assert actual_page.next_page_token is None
    assert actual_page.results == []


def test__journal_client__missing_main_journal_config_key(elasticsearch_host):
    """Missing configuration on journal should raise"""
    with pytest.raises(KeyError, match="journal"):
        invoke(
            catch_exceptions=False,
            args=["journal-client", "objects", "--stop-after-objects", "1",],
            config="",  # missing config will make it raise
            elasticsearch_host=elasticsearch_host,
        )


def test__journal_client__missing_journal_config_keys(elasticsearch_host):
    """Missing configuration on mandatory journal keys should raise"""
    kafka_prefix = "swh.journal.objects"
    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker="192.0.2.1", prefix=kafka_prefix, group_id="test-consumer"
    )
    journal_config = yaml.safe_load(journal_objects_config)

    for key in journal_config["journal"].keys():
        if key == "prefix":  # optional
            continue
        cfg = copy.deepcopy(journal_config)
        del cfg["journal"][key]  # make config incomplete
        yaml_cfg = yaml.dump(cfg)

        with pytest.raises(TypeError, match=f"{key}"):
            invoke(
                catch_exceptions=False,
                args=[
                    "journal-client",
                    "objects",
                    "--stop-after-objects",
                    "1",
                    "--prefix",
                    kafka_prefix,
                    "--object-type",
                    "origin_visit_status",
                ],
                config=yaml_cfg,  # incomplete config will make the cli raise
                elasticsearch_host=elasticsearch_host,
            )


def test__journal_client__missing_prefix_config_key(
    swh_search, elasticsearch_host, kafka_server
):
    """Missing configuration on mandatory prefix key should raise"""

    journal_cfg_template = """
journal:
    brokers:
        - {broker}
    group_id: {group_id}
    """

    journal_cfg = journal_cfg_template.format(
        broker=kafka_server, group_id="test-consumer"
    )

    with pytest.raises(ValueError, match="prefix"):
        invoke(
            False,
            # Missing --prefix (and no config key) will make the cli raise
            [
                "journal-client",
                "objects",
                "--stop-after-objects",
                "1",
                "--object-type",
                "origin_visit_status",
            ],
            journal_cfg,
            elasticsearch_host=elasticsearch_host,
        )


def test__journal_client__missing_object_types_config_key(
    swh_search, elasticsearch_host, kafka_server
):
    """Missing configuration on mandatory object-types key should raise"""

    journal_cfg_template = """
journal:
    brokers:
        - {broker}
    prefix: swh.journal.objects
    group_id: {group_id}
    """

    journal_cfg = journal_cfg_template.format(
        broker=kafka_server, group_id="test-consumer"
    )

    with pytest.raises(ValueError, match="object_types"):
        invoke(
            False,
            # Missing --object-types (and no config key) will make the cli raise
            ["journal-client", "objects", "--stop-after-objects", "1"],
            journal_cfg,
            elasticsearch_host=elasticsearch_host,
        )
