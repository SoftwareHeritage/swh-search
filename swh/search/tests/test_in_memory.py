# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

import pytest

from swh.indexer import codemeta
from swh.search import get_search
from swh.search.in_memory import _nested_get

from .test_search import CommonSearchTest


class InmemorySearchTest(unittest.TestCase, CommonSearchTest):
    @pytest.fixture(autouse=True)
    def _instantiate_search(self):
        self.search = get_search("memory")

    def setUp(self):
        self.reset()

    def reset(self):
        self.search.deinitialize()
        self.search.initialize()


def test_nested_get_helper_function():

    instrinsic_metadata = codemeta.expand(
        {
            "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
            "keywords": ["bar", "baz"],
            "description": "foo bar 3",
            "programmingLanguage": "cpp",
            "license": "https://spdx.org/licenses/LGPL-2.0-only",
        }
    )
    expected_expansion = [
        {
            "http://schema.org/description": [{"@value": "foo bar 3"}],
            "http://schema.org/license": [
                {"@id": "https://spdx.org/licenses/LGPL-2.0-only"}
            ],
            "http://schema.org/keywords": [{"@value": "bar"}, {"@value": "baz"}],
            "http://schema.org/programmingLanguage": [{"@value": "cpp"}],
        }
    ]
    assert instrinsic_metadata == expected_expansion
    assert _nested_get(instrinsic_metadata, ["http://schema.org/license", "@id"]) == [
        "https://spdx.org/licenses/LGPL-2.0-only"
    ]

    new_field = [
        {"name": [{"@value": {"first": "f1", "last": "l1"}}], "address": "XYZ"},
        {"name": [{"@value": {"first": "f2", "last": "l2"}}], "address": "ABC"},
        {"name": [{"@value": {"first": "f3"}}], "address": {}},
        {"name": [{"@value": {"first": "f4"}}], "address": []},
    ]
    assert _nested_get(new_field, ["name", "@value", "last"]) == ["l1", "l2", "", ""]
    assert _nested_get(new_field, ["name", "@value", "first"]) == [
        "f1",
        "f2",
        "f3",
        "f4",
    ]

    assert _nested_get(new_field, ["address"]) == ["XYZ", "ABC", {}, []]
    # shouldn't allow fetching intermediate values
    assert _nested_get(new_field, ["name", "@value"]) == ["", "", "", ""]
