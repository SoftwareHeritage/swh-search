# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

import pytest

from swh.model.model import Origin
from swh.search.elasticsearch import ElasticSearch


def test_origin_url_unique_word_prefix(elasticsearch_host):
    search = ElasticSearch([elasticsearch_host])
    search.initialize()
    search.origin_add([
        Origin(url='http://foobar.baz', type=None),
        Origin(url='http://barbaz.qux', type=None),
    ])

    results = search.origin_search('foobar')
    assert results == {'cursor': None, 'results': [{'url': 'http://foobar.baz'}]}

    results = search.origin_search('barb')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    # 'bar' is part of 'foobar', but is not the beginning of it
    results = search.origin_search('bar')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    results = search.origin_search('barbaz')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    results = search.origin_search('qu')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    results = search.origin_search('qux')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}
