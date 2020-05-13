# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import copy
import tempfile
import yaml

import pytest

from confluent_kafka import Producer
from click.testing import CliRunner

from swh.journal.serializers import value_to_kafka

from swh.search.cli import cli


CLI_CONFIG = """
search:
    cls: elasticsearch
    args:
        hosts:
        - '{elasticsearch_host}'
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
            (CLI_CONFIG + config).format(elasticsearch_host=elasticsearch_host)
        )
        config_fd.seek(0)
        result = runner.invoke(cli, ["-C" + config_fd.name] + args)
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
    value = value_to_kafka({"url": "http://foobar.baz",})
    topic = f"{kafka_prefix}.origin"
    producer.produce(topic=topic, key=b"bogus-origin", value=value)

    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker=kafka_server, prefix=kafka_prefix, group_id="test-consumer"
    )
    result = invoke(
        False,
        ["journal-client", "objects", "--stop-after-objects", "1",],
        journal_objects_config,
        elasticsearch_host=elasticsearch_host,
    )

    # Check the output
    expected_output = "Processed 1 messages.\nDone.\n"
    assert result.exit_code == 0, result.output
    assert result.output == expected_output

    swh_search.flush()

    # searching origin without visit as requirement
    results = swh_search.origin_search(url_pattern="foobar")
    # We find it
    assert results == {
        "next_page_token": None,
        "results": [{"url": "http://foobar.baz"}],
    }

    # It's an origin with no visit, searching for it with visit
    results = swh_search.origin_search(url_pattern="foobar", with_visit=True)
    # returns nothing
    assert results == {"next_page_token": None, "results": []}


def test__journal_client__origin_visit(
    swh_search, elasticsearch_host, kafka_prefix: str, kafka_server
):
    """Tests the re-indexing when origin_batch_size*task_batch_size is a
    divisor of nb_origins."""
    producer = Producer(
        {
            "bootstrap.servers": kafka_server,
            "client.id": "test search origin visit producer",
            "acks": "all",
        }
    )
    topic = f"{kafka_prefix}.origin_visit"
    value = value_to_kafka({"origin": "http://baz.foobar",})
    producer.produce(topic=topic, key=b"bogus-origin-visit", value=value)

    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker=kafka_server, prefix=kafka_prefix, group_id="test-consumer"
    )
    result = invoke(
        False,
        ["journal-client", "objects", "--stop-after-objects", "1",],
        journal_objects_config,
        elasticsearch_host=elasticsearch_host,
    )

    # Check the output
    expected_output = "Processed 1 messages.\nDone.\n"
    assert result.exit_code == 0, result.output
    assert result.output == expected_output

    swh_search.flush()

    expected_result = {
        "next_page_token": None,
        "results": [{"url": "http://baz.foobar"}],
    }
    # Both search returns the visit
    results = swh_search.origin_search(url_pattern="foobar", with_visit=False)
    assert results == expected_result
    results = swh_search.origin_search(url_pattern="foobar", with_visit=True)
    assert results == expected_result


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
    journal_objects_config = JOURNAL_OBJECTS_CONFIG_TEMPLATE.format(
        broker="192.0.2.1", prefix="swh.journal.objects", group_id="test-consumer"
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
                args=["journal-client", "objects", "--stop-after-objects", "1",],
                config=yaml_cfg,  # incomplete config will make the cli raise
                elasticsearch_host=elasticsearch_host,
            )
