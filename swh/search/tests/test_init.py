# Copyright (C) 2020 The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import inspect

import pytest

from swh.search import get_search
from swh.search.api.client import RemoteSearch
from swh.search.elasticsearch import ElasticSearch
from swh.search.in_memory import InMemorySearch
from swh.search.interface import SearchInterface

SEARCH_IMPLEMENTATIONS_KWARGS = [
    ("remote", RemoteSearch, {"url": "localhost"}),
    (
        "elasticsearch",
        ElasticSearch,
        {"hosts": ["localhost"], "indexes": {"origin": {"index": "test"}}},
    ),
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


@pytest.mark.parametrize("class_,expected_class,kwargs", SEARCH_IMPLEMENTATIONS)
def test_types(mocker, class_, expected_class, kwargs):
    """Checks all methods of SearchInterface are implemented by this
    backend, and that they have the same signature.

    """
    mocker.patch("swh.search.elasticsearch.Elasticsearch")
    if kwargs:
        concrete_search = get_search(class_, **kwargs)
    else:
        concrete_search = get_search(class_)

    # Create an instance of the protocol (which cannot be instantiated
    # directly, so this creates a subclass, then instantiates it)
    interface = type("_", (SearchInterface,), {})()

    for meth_name in dir(interface):
        if meth_name.startswith("_"):
            continue
        interface_meth = getattr(interface, meth_name)

        missing_methods = []

        try:
            concrete_meth = getattr(concrete_search, meth_name)
        except AttributeError:
            if not getattr(interface_meth, "deprecated_endpoint", False):
                # The backend is missing a (non-deprecated) endpoint
                missing_methods.append(meth_name)
                continue

        expected_signature = inspect.signature(interface_meth)
        actual_signature = inspect.signature(concrete_meth)

        assert expected_signature == actual_signature, meth_name

        assert missing_methods == []
