# Copyright (C) 2020 The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import pytest

from swh.search import get_search

from swh.search.elasticsearch import ElasticSearch
from swh.search.api.client import RemoteSearch
from swh.search.in_memory import InMemorySearch


SEARCH_IMPLEMENTATIONS_KWARGS = [
    ("remote", RemoteSearch, {"url": "localhost"}),
    ("elasticsearch", ElasticSearch, {"hosts": ["localhost"]}),
]

SEARCH_IMPLEMENTATIONS = SEARCH_IMPLEMENTATIONS_KWARGS + [
    ("memory", InMemorySearch, None),
]


def test_get_search_failure():
    with pytest.raises(ValueError, match="Unknown search class"):
        get_search("unknown-search")


@pytest.mark.parametrize("class_,expected_class,kwargs", SEARCH_IMPLEMENTATIONS)
def test_get_search(mocker, class_, expected_class, kwargs):
    mocker.patch("swh.search.elasticsearch.Elasticsearch")
    if kwargs:
        concrete_search = get_search(class_, **kwargs)
    else:
        concrete_search = get_search(class_)
    assert isinstance(concrete_search, expected_class)


@pytest.mark.parametrize("class_,expected_class,kwargs", SEARCH_IMPLEMENTATIONS_KWARGS)
def test_get_search_deprecation_warning(mocker, class_, expected_class, kwargs):
    with pytest.warns(DeprecationWarning):
        concrete_search = get_search(class_, args=kwargs)
    assert isinstance(concrete_search, expected_class)
