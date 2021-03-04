# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

import pytest

from swh.search.metrics import OPERATIONS_METRIC

from .test_search import CommonSearchTest


class BaseElasticsearchTest(unittest.TestCase):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self, swh_search, elasticsearch_host, mocker):
        self._elasticsearch_host = elasticsearch_host
        self.search = swh_search
        self.mocker = mocker

    def reset(self):
        self.search.deinitialize()
        self.search.initialize()


class TestElasticsearchSearch(CommonSearchTest, BaseElasticsearchTest):
    def test_metrics_update_duration(self):
        mock = self.mocker.patch("swh.search.metrics.statsd.timing")

        for url in ["http://foobar.bar", "http://foobar.baz"]:
            self.search.origin_update([{"url": url}])

        assert mock.call_count == 2

    def test_metrics_search_duration(self):
        mock = self.mocker.patch("swh.search.metrics.statsd.timing")

        for url_pattern in ["foobar", "foobaz"]:
            self.search.origin_search(url_pattern=url_pattern, with_visit=True)

        assert mock.call_count == 2

    def test_metrics_indexation_counters(self):
        mock_es = self.mocker.patch("elasticsearch.helpers.bulk")
        mock_es.return_value = 2, ["error"]

        mock_metrics = self.mocker.patch("swh.search.metrics.statsd.increment")

        self.search.origin_update([{"url": "http://foobar.baz"}])

        assert mock_metrics.call_count == 2

        mock_metrics.assert_any_call(
            OPERATIONS_METRIC,
            2,
            tags={
                "endpoint": "origin_update",
                "object_type": "document",
                "operation": "index",
            },
        )
        mock_metrics.assert_any_call(
            OPERATIONS_METRIC,
            1,
            tags={
                "endpoint": "origin_update",
                "object_type": "document",
                "operation": "index_error",
            },
        )

    def test_write_alias_usage(self):
        mock = self.mocker.patch("elasticsearch.helpers.bulk")
        mock.return_value = 2, ["result"]

        self.search.origin_update([{"url": "http://foobar.baz"}])

        assert mock.call_args[1]["index"] == "test-write"

    def test_read_alias_usage(self):
        mock = self.mocker.patch("elasticsearch.Elasticsearch.search")
        mock.return_value = {"hits": {"hits": []}}

        self.search.origin_search(url_pattern="foobar.baz")

        assert mock.call_args[1]["index"] == "test-read"
