# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

import pytest

from swh.core.api.tests.server_testing import ServerTestFixture
from swh.search import get_search
from swh.search.api.server import app

from .test_search import CommonSearchTest


class TestRemoteSearch(CommonSearchTest, ServerTestFixture, unittest.TestCase):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self, elasticsearch_host):
        self._elasticsearch_host = elasticsearch_host

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
        super().setUp()
        self.reset()
        self.search = get_search("remote", url=self.url(),)

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
