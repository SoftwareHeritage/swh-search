# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from hypothesis import given, strategies, settings

from swh.search.utils import stream_results


class CommonSearchTest:
    def test_origin_url_unique_word_prefix(self):
        self.search.origin_update([
            {'url': 'http://foobar.baz'},
            {'url': 'http://barbaz.qux'},
            {'url': 'http://qux.quux'},
        ])

        results = self.search.origin_search(url_substring='foobar')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://foobar.baz'}]})

        results = self.search.origin_search(url_substring='barb')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://barbaz.qux'}]})

        # 'bar' is part of 'foobar', but is not the beginning of it
        results = self.search.origin_search(url_substring='bar')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://barbaz.qux'}]})

        results = self.search.origin_search(url_substring='barbaz')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://barbaz.qux'}]})

        results = self.search.origin_search(url_substring='qu')
        self.assertIsNone(results['cursor'])
        self.assertEqual(
            sorted(res['url'] for res in results['results']),
            ['http://barbaz.qux', 'http://qux.quux'])

        results = self.search.origin_search(url_substring='qux')
        self.assertIsNone(results['cursor'])
        self.assertEqual(
            sorted(res['url'] for res in results['results']),
            ['http://barbaz.qux', 'http://qux.quux'])

    def test_origin_intrinsic_metadata_description(self):
        self.search.origin_update([
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

        results = self.search.origin_search(metadata_substring='foo')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://origin2'}]})

        results = self.search.origin_search(metadata_substring='foo bar')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://origin2'}, {'url': 'http://origin3'}]})

        results = self.search.origin_search(metadata_substring='bar baz')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://origin3'}, {'url': 'http://origin2'}]})

    def test_origin_intrinsic_metadata_keywords(self):
        self.search.origin_update([
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

        results = self.search.origin_search(metadata_substring='foo')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://origin2'}]})

        results = self.search.origin_search(metadata_substring='foo bar')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://origin2'}, {'url': 'http://origin3'}]})

        results = self.search.origin_search(metadata_substring='bar baz')
        self.assertEqual(results, {'cursor': None, 'results': [
            {'url': 'http://origin3'}, {'url': 'http://origin2'}]})

    @settings(deadline=None)
    @given(strategies.integers(min_value=1, max_value=4))
    def test_origin_paging(self, count):
        self.reset()
        self.search.origin_update([
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
            self.search.origin_search,
            metadata_substring='foo bar baz', count=count)
        self.assertEqual(list(results), [
            {'url': 'http://origin3'},
            {'url': 'http://origin2'},
            {'url': 'http://origin1'}])

        results = stream_results(
            self.search.origin_search,
            metadata_substring='foo bar', count=count)
        self.assertEqual(list(results), [
            {'url': 'http://origin2'},
            {'url': 'http://origin3'},
            {'url': 'http://origin1'}])

        results = stream_results(
            self.search.origin_search,
            metadata_substring='foo', count=count)
        self.assertEqual(list(results), [
            {'url': 'http://origin1'},
            {'url': 'http://origin2'},
            {'url': 'http://origin3'}])
