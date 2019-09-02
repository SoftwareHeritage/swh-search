# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import unittest

from hypothesis import given, strategies, settings
import pytest

from swh.model.model import Origin

from swh.search.elasticsearch import ElasticSearch
from swh.search.utils import stream_results


def test_origin_url_unique_word_prefix(elasticsearch_host):
    search = ElasticSearch([elasticsearch_host])
    search.initialize()
    search.origin_update([
        {'url': 'http://foobar.baz'},
        {'url': 'http://barbaz.qux'},
        {'url': 'http://qux.quux'},
    ])

    results = search.origin_search(url_substring='foobar')
    assert results == {'cursor': None, 'results': [{'url': 'http://foobar.baz'}]}

    results = search.origin_search(url_substring='barb')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    # 'bar' is part of 'foobar', but is not the beginning of it
    results = search.origin_search(url_substring='bar')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    results = search.origin_search(url_substring='barbaz')
    assert results == {'cursor': None, 'results': [{'url': 'http://barbaz.qux'}]}

    results = search.origin_search(url_substring='qu')
    assert results['cursor'] == None
    assert sorted(res['url'] for res in results['results']) \
        == ['http://barbaz.qux', 'http://qux.quux']

    results = search.origin_search(url_substring='qux')
    assert results['cursor'] == None
    assert sorted(res['url'] for res in results['results']) \
        == ['http://barbaz.qux', 'http://qux.quux']


def test_origin_intrinsic_metadata_description(elasticsearch_host):
    search = ElasticSearch([elasticsearch_host])
    search.initialize()
    search.origin_update([
        {
            'url': 'http://origin1',
            'intrinsic_metadata': {},
        },
        {
            'url': 'http://origin2',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'description': 'foo bar',
            },
        },
        {
            'url': 'http://origin3',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'description': 'bar baz',
            }
        },
    ])

    results = search.origin_search(metadata_substring='foo')
    assert results == {'cursor': None, 'results': [{'url': 'http://origin2'}]}

    results = search.origin_search(metadata_substring='foo bar')
    assert results == {'cursor': None, 'results': [
        {'url': 'http://origin2'}, {'url': 'http://origin3'}]}

    results = search.origin_search(metadata_substring='bar baz')
    assert results == {'cursor': None, 'results': [
        {'url': 'http://origin3'}, {'url': 'http://origin2'}]}


def test_origin_intrinsic_metadata_keywords(elasticsearch_host):
    search = ElasticSearch([elasticsearch_host])
    search.initialize()
    search.origin_update([
        {
            'url': 'http://origin1',
            'intrinsic_metadata': {},
        },
        {
            'url': 'http://origin2',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'keywords': ['foo', 'bar'],
            },
        },
        {
            'url': 'http://origin3',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'keywords': ['bar', 'baz'],
            }
        },
    ])

    results = search.origin_search(metadata_substring='foo')
    assert results == {'cursor': None, 'results': [{'url': 'http://origin2'}]}

    results = search.origin_search(metadata_substring='foo bar')
    assert results == {'cursor': None, 'results': [
        {'url': 'http://origin2'}, {'url': 'http://origin3'}]}

    results = search.origin_search(metadata_substring='bar baz')
    assert results == {'cursor': None, 'results': [
        {'url': 'http://origin3'}, {'url': 'http://origin2'}]}


@settings(deadline=None)
@given(strategies.integers(min_value=1, max_value=4))
def test_origin_paging(elasticsearch_host, count):
    search = ElasticSearch([elasticsearch_host])
    search.deinitialize()
    search.initialize()
    search.origin_update([
        {
            'url': 'http://origin1',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'keywords': ['foo'],
            },
        },
        {
            'url': 'http://origin2',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'keywords': ['foo', 'bar'],
            },
        },
        {
            'url': 'http://origin3',
            'intrinsic_metadata': {
                '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                'keywords': ['foo', 'bar', 'baz'],
            }
        },
    ])

    results = stream_results(
        search.origin_search, metadata_substring='foo bar baz', count=count)
    assert list(results) == [
        {'url': 'http://origin3'},
        {'url': 'http://origin2'},
        {'url': 'http://origin1'}]

    results = stream_results(
        search.origin_search, metadata_substring='foo bar', count=count)
    assert list(results) == [
        {'url': 'http://origin2'},
        {'url': 'http://origin3'},
        {'url': 'http://origin1'}]

    results = stream_results(
        search.origin_search, metadata_substring='foo', count=count)
    assert list(results) == [
        {'url': 'http://origin1'},
        {'url': 'http://origin2'},
        {'url': 'http://origin3'}]
