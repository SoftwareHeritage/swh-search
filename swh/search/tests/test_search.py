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
        self.search.flush()

        results = self.search.origin_search(url_pattern='foobar')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://foobar.baz'}]}

        results = self.search.origin_search(url_pattern='barb')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://barbaz.qux'}]}

        # 'bar' is part of 'foobar', but is not the beginning of it
        results = self.search.origin_search(url_pattern='bar')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://barbaz.qux'}]}

        results = self.search.origin_search(url_pattern='barbaz')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://barbaz.qux'}]}

    def test_origin_url_unique_word_prefix_multiple_results(self):
        self.search.origin_update([
            {'url': 'http://foobar.baz'},
            {'url': 'http://barbaz.qux'},
            {'url': 'http://qux.quux'},
        ])
        self.search.flush()

        results = self.search.origin_search(url_pattern='qu')
        assert results['next_page_token'] is None

        results = [res['url'] for res in results['results']]
        expected_results = ['http://qux.quux', 'http://barbaz.qux']
        assert sorted(results) == sorted(expected_results)

        results = self.search.origin_search(url_pattern='qux')
        assert results['next_page_token'] is None

        results = [res['url'] for res in results['results']]
        expected_results = ['http://barbaz.qux', 'http://qux.quux']
        assert sorted(results) == sorted(expected_results)

    def test_origin_url_all_terms(self):
        self.search.origin_update([
            {'url': 'http://foo.bar/baz'},
            {'url': 'http://foo.bar/foo.bar'},
        ])
        self.search.flush()

        # Only results containing all terms should be returned.
        results = self.search.origin_search(url_pattern='foo bar baz')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://foo.bar/baz'},
        ]}

    def test_origin_with_visit(self):
        self.search.origin_update([
            {'url': 'http://foobar.baz', 'has_visits': True},
        ])
        self.search.flush()

        results = self.search.origin_search(
            url_pattern='foobar', with_visit=True)
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://foobar.baz'}]}

    def test_origin_with_visit_added(self):
        self.search.origin_update([
            {'url': 'http://foobar.baz'},
        ])
        self.search.flush()

        results = self.search.origin_search(
            url_pattern='foobar', with_visit=True)
        assert results == {'next_page_token': None, 'results': []}

        self.search.origin_update([
            {'url': 'http://foobar.baz', 'has_visits': True},
        ])
        self.search.flush()

        results = self.search.origin_search(
            url_pattern='foobar', with_visit=True)
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://foobar.baz'}]}

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
        self.search.flush()

        results = self.search.origin_search(metadata_pattern='foo')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin2'}]}

        results = self.search.origin_search(metadata_pattern='foo bar')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin2'}]}

        results = self.search.origin_search(metadata_pattern='bar baz')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin3'}]}

    def test_origin_intrinsic_metadata_all_terms(self):
        self.search.origin_update([
            {
                'url': 'http://origin1',
                'intrinsic_metadata': {
                    '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                    'description': 'foo bar foo bar',
                },
            },
            {
                'url': 'http://origin3',
                'intrinsic_metadata': {
                    '@context': 'https://doi.org/10.5063/schema/codemeta-2.0',
                    'description': 'foo bar baz',
                }
            },
        ])
        self.search.flush()

        results = self.search.origin_search(metadata_pattern='foo bar baz')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin3'}]}

    def test_origin_intrinsic_metadata_nested(self):
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
        self.search.flush()

        results = self.search.origin_search(metadata_pattern='foo')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin2'}]}

        results = self.search.origin_search(metadata_pattern='foo bar')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin2'}]}

        results = self.search.origin_search(metadata_pattern='bar baz')
        assert results == {'next_page_token': None, 'results': [
            {'url': 'http://origin3'}]}

    # TODO: add more tests with more codemeta terms

    # TODO: add more tests with edge cases

    @settings(deadline=None)
    @given(strategies.integers(min_value=1, max_value=4))
    def test_origin_url_paging(self, count):
        # TODO: no hypothesis
        self.reset()
        self.search.origin_update([
            {'url': 'http://origin1/foo'},
            {'url': 'http://origin2/foo/bar'},
            {'url': 'http://origin3/foo/bar/baz'},
        ])
        self.search.flush()

        results = stream_results(
            self.search.origin_search,
            url_pattern='foo bar baz', count=count)
        results = [res['url'] for res in results]
        expected_results = [
            'http://origin3/foo/bar/baz',
        ]
        assert sorted(results[0:len(expected_results)]) == \
            sorted(expected_results)

        results = stream_results(
            self.search.origin_search,
            url_pattern='foo bar', count=count)
        expected_results = [
            'http://origin2/foo/bar',
            'http://origin3/foo/bar/baz',
        ]
        results = [res['url'] for res in results]
        assert sorted(results[0:len(expected_results)]) == \
            sorted(expected_results)

        results = stream_results(
            self.search.origin_search,
            url_pattern='foo', count=count)
        expected_results = [
            'http://origin1/foo',
            'http://origin2/foo/bar',
            'http://origin3/foo/bar/baz',
        ]
        results = [res['url'] for res in results]
        assert sorted(results[0:len(expected_results)]) == \
            sorted(expected_results)

    @settings(deadline=None)
    @given(strategies.integers(min_value=1, max_value=4))
    def test_origin_intrinsic_metadata_paging(self, count):
        # TODO: no hypothesis
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
        self.search.flush()

        results = stream_results(
            self.search.origin_search,
            metadata_pattern='foo bar baz', count=count)
        assert list(results) == [
            {'url': 'http://origin3'}]

        results = stream_results(
            self.search.origin_search,
            metadata_pattern='foo bar', count=count)
        assert list(results) == [
            {'url': 'http://origin2'},
            {'url': 'http://origin3'}]

        results = stream_results(
            self.search.origin_search,
            metadata_pattern='foo', count=count)
        assert list(results) == [
            {'url': 'http://origin1'},
            {'url': 'http://origin2'},
            {'url': 'http://origin3'}]
