# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from datetime import datetime, timedelta, timezone
from textwrap import dedent
import types
import unittest

from elasticsearch.helpers.errors import BulkIndexError
import pytest

from swh.search.metrics import OPERATIONS_METRIC

from .test_search import CommonSearchTest


class BaseElasticsearchTest(unittest.TestCase):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self, swh_search, elasticsearch_host, mocker):
        self._elasticsearch_host = elasticsearch_host
        self.search = swh_search
        self.mocker = mocker

        # override self.search.origin_update to catch painless script errors
        # and pretty print them
        origin_update = self.search.origin_update

        def _origin_update(self, *args, **kwargs):
            script_error = False
            error_detail = ""
            try:
                origin_update(*args, **kwargs)
            except BulkIndexError as e:
                error = e.errors[0].get("update", {}).get("error", {}).get("caused_by")
                if error and "script_stack" in error:
                    script_error = True
                    error_detail = dedent(
                        f"""
                        Painless update script failed ({error.get('reason')}).
                        error type: {error.get('caused_by', {}).get('type')}
                        error reason: {error.get('caused_by', {}).get('reason')}
                        script stack:

                        """
                    )
                    error_detail += "\n".join(error["script_stack"])
                else:
                    raise e
            assert script_error is False, error_detail[1:]

        self.search.origin_update = types.MethodType(_origin_update, self.search)

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

    def test_sort_by_and_limit_query(self):
        now = datetime.now(tz=timezone.utc).isoformat()
        now_minus_5_hours = (
            datetime.now(tz=timezone.utc) - timedelta(hours=5)
        ).isoformat()
        now_plus_5_hours = (
            datetime.now(tz=timezone.utc) + timedelta(hours=5)
        ).isoformat()

        ORIGINS = [
            {
                "url": "http://foobar.1.com",
                "nb_visits": 1,
                "last_visit_date": now_minus_5_hours,
                "last_eventful_visit_date": now_minus_5_hours,
            },
            {
                "url": "http://foobar.2.com",
                "nb_visits": 2,
                "last_visit_date": now,
                "last_eventful_visit_date": now,
            },
            {
                "url": "http://foobar.3.com",
                "nb_visits": 3,
                "last_visit_date": now_plus_5_hours,
                "last_eventful_visit_date": now_minus_5_hours,
            },
        ]

        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_results(query, origin_indices):
            page = self.search.origin_search(url_pattern="foobar", query=query)
            results = [r["url"] for r in page.results]
            assert results == [ORIGINS[index]["url"] for index in origin_indices]

        _check_results("sort_by = [-visits]", [2, 1, 0])
        _check_results("sort_by = [last_visit]", [0, 1, 2])
        _check_results("sort_by = [-last_eventful_visit, visits]", [1, 0, 2])
        _check_results("sort_by = [last_eventful_visit,-last_visit]", [2, 0, 1])

        _check_results("sort_by = [-visits] limit = 1", [2])
        _check_results("sort_by = [last_visit] and limit = 2", [0, 1])
        _check_results("sort_by = [-last_eventful_visit, visits] limit = 3", [1, 0, 2])
