# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import tempfile
from unittest.mock import patch, MagicMock

from click.testing import CliRunner

from swh.journal.serializers import value_to_kafka
from swh.journal.tests.utils import MockedKafkaConsumer

from swh.search.cli import cli
from .test_elasticsearch import BaseElasticsearchTest


CLI_CONFIG = '''
search:
    cls: elasticsearch
    args:
        hosts:
        - '{elasticsearch_host}'
'''

JOURNAL_OBJECTS_CONFIG = '''
journal:
    brokers:
        - 192.0.2.1
    prefix: swh.journal.objects
    group_id: test-consumer
'''


class MockedKafkaConsumerWithTopics(MockedKafkaConsumer):
    def list_topics(self, timeout=None):
        return {
            'swh.journal.objects.origin',
            'swh.journal.objects.origin_visit',
        }


def invoke(catch_exceptions, args, config='', *, elasticsearch_host):
    runner = CliRunner()
    with tempfile.NamedTemporaryFile('a', suffix='.yml') as config_fd:
        config_fd.write((CLI_CONFIG + config).format(
            elasticsearch_host=elasticsearch_host
        ))
        config_fd.seek(0)
        result = runner.invoke(cli, ['-C' + config_fd.name] + args)
    if not catch_exceptions and result.exception:
        print(result.output)
        raise result.exception
    return result


class CliTestCase(BaseElasticsearchTest):
    def test__journal_client__origin(self):
        """Tests the re-indexing when origin_batch_size*task_batch_size is a
        divisor of nb_origins."""
        topic = 'swh.journal.objects.origin'
        value = value_to_kafka({
            'url': 'http://foobar.baz',
        })
        message = MagicMock()
        message.error.return_value = None
        message.topic.return_value = topic
        message.value.return_value = value

        mock_consumer = MockedKafkaConsumerWithTopics([message])

        with patch('swh.journal.client.Consumer',
                   return_value=mock_consumer):
            result = invoke(False, [
                    'journal-client', 'objects',
                    '--max-messages', '1',
                ], JOURNAL_OBJECTS_CONFIG,
                elasticsearch_host=self._elasticsearch_host)

        # Check the output
        expected_output = (
            'Processed 1 messages.\n'
            'Done.\n'
        )
        assert result.exit_code == 0, result.output
        assert result.output == expected_output

        self.search.flush()

        results = self.search.origin_search(url_pattern='foobar')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://foobar.baz'}]}

        results = self.search.origin_search(url_pattern='foobar',
                                            with_visit=True)
        assert results == {'next_page_token': None, 'results': []}

    def test__journal_client__origin_visit(self):
        """Tests the re-indexing when origin_batch_size*task_batch_size is a
        divisor of nb_origins."""
        topic = 'swh.journal.objects.origin_visit'
        value = value_to_kafka({
            'origin': 'http://foobar.baz',
        })
        message = MagicMock()
        message.error.return_value = None
        message.topic.return_value = topic
        message.value.return_value = value

        mock_consumer = MockedKafkaConsumerWithTopics([message])

        with patch('swh.journal.client.Consumer',
                   return_value=mock_consumer):
            result = invoke(False, [
                    'journal-client', 'objects',
                    '--max-messages', '1',
                ], JOURNAL_OBJECTS_CONFIG,
                elasticsearch_host=self._elasticsearch_host)

        # Check the output
        expected_output = (
            'Processed 1 messages.\n'
            'Done.\n'
        )
        assert result.exit_code == 0, result.output
        assert result.output == expected_output

        self.search.flush()

        results = self.search.origin_search(url_pattern='foobar',
                                            with_visit=True)
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://foobar.baz'}]}
