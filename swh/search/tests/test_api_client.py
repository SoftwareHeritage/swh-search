# Copyright (C) 2019-2023  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information


import pytest

from swh.core.api.tests.server_testing import ServerTestFixture
from swh.search import get_search
from swh.search.api.server import app

from .test_elasticsearch import CommonElasticsearchSearchTest
from .test_in_memory import CommonInmemorySearchTest


class TestRemoteSearchElasticSearch(CommonElasticsearchSearchTest, ServerTestFixture):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self, elasticsearch_host):
        self._elasticsearch_host = elasticsearch_host

    @pytest.fixture(autouse=True)
    def setUp(self):
        self.config = {
            "search": {
                "cls": "elasticsearch",
                "args": {
                    "hosts": [self._elasticsearch_host],
                    "indexes": {
                        "origin": {
                            "index": "test",
                            "read_alias": "test-read",
                            "write_alias": "test-write",
                        }
                    },
                },
            }
        }
        self.app = app
        self.start_server()
        self.reset()
        self.search = get_search(
            "remote",
            url=self.url(),
        )
        yield
        self.stop_server()

    def reset(self):
        search = get_search(
            "elasticsearch",
            hosts=[self._elasticsearch_host],
            indexes={
                "origin": {
                    "index": "test",
                    "read_alias": "test-read",
                    "write_alias": "test-write",
                }
            },
        )
        search.deinitialize()
        search.initialize()

    @pytest.mark.skip(
        "Elasticsearch also returns close matches, so this test would fail"
    )
    def test_origin_url_paging(self, count):
        pass


class TestRemoteSearchInMemory(CommonInmemorySearchTest, ServerTestFixture):
    @pytest.fixture(autouse=True)
    def setUp(self):
        self.config = {
            "search": {
                "cls": "memory",
            }
        }
        self.app = app
        self.start_server()
        self.search = get_search(
            "remote",
            url=self.url(),
        )
        yield
        self.stop_server()

    def reset(self):
        pass
