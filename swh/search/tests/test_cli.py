# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import tempfile
from unittest.mock import patch, MagicMock

from click.testing import CliRunner

from swh.journal.serializers import value_to_kafka

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
        mock_consumer = MagicMock()

        topic = 'swh.journal.objects.origin'
        value = value_to_kafka({
            'url': 'http://foobar.baz',
        })
        message = MagicMock()
        message.error.return_value = None
        message.topic.return_value = topic
        message.value.return_value = value
        mock_consumer.poll.return_value = message

        with patch('swh.journal.client.Consumer',
                   return_value=mock_consumer):
            result = invoke(False, [
                    'journal-client', 'objects',
                    '--max-messages', '1',
                ], JOURNAL_OBJECTS_CONFIG,
                elasticsearch_host=self._elasticsearch_host)

        mock_consumer.subscribe.assert_called_once_with(topics=[topic])
        mock_consumer.poll.assert_called_once_with(timeout=1.0)
        mock_consumer.commit.assert_called_once_with()

        # Check the output
        expected_output = (
            'Processed 1 messages.\n'
            'Done.\n'
        )
        assert result.exit_code == 0, result.output
        assert result.output == expected_output

        results = self.search.origin_search(url_pattern='foobar')
        assert results == {'scroll_token': None, 'results': [
            {'url': 'http://foobar.baz'}]}
