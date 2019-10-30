# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

import pytest

from swh.search import get_search
from .test_search import CommonSearchTest


class BaseElasticsearchTest(unittest.TestCase):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self, elasticsearch_host):
        self._elasticsearch_host = elasticsearch_host
        self.search = get_search('elasticsearch', {
            'hosts': [elasticsearch_host],
        })

    def setUp(self):
        self.reset()

    def reset(self):
        self.search.deinitialize()
        self.search.initialize()


class TestElasticsearchSearch(CommonSearchTest, BaseElasticsearchTest):
    pass
