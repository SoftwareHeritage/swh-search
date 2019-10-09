# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

import pytest

from swh.search.in_memory import InMemorySearch
from .test_search import CommonSearchTest


class InmemorySearchTest(unittest.TestCase, CommonSearchTest):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self):
        self.search = InMemorySearch()

    def setUp(self):
        self.reset()

    def reset(self):
        self.search.deinitialize()
        self.search.initialize()

    @pytest.mark.skip('Not implemented in the in-memory search')
    def test_origin_intrinsic_metadata_description(self):
        pass

    @pytest.mark.skip('Not implemented in the in-memory search')
    def test_origin_intrinsic_metadata_keywords(self):
        pass

    @pytest.mark.skip('Not implemented in the in-memory search')
    def test_origin_intrinsic_metadata_paging(self):
        pass