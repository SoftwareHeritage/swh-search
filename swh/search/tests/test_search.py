# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from hypothesis import given, settings, strategies

from swh.core.api.classes import stream_results


class CommonSearchTest:
    def test_origin_url_unique_word_prefix(self):
        origin_foobar_baz = {"url": "http://foobar.baz"}
        origin_barbaz_qux = {"url": "http://barbaz.qux"}
        origin_qux_quux = {"url": "http://qux.quux"}
        origins = [origin_foobar_baz, origin_barbaz_qux, origin_qux_quux]

        self.search.origin_update(origins)
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="foobar")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_foobar_baz]

        actual_page = self.search.origin_search(url_pattern="barb")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_barbaz_qux]

        # 'bar' is part of 'foobar', but is not the beginning of it
        actual_page = self.search.origin_search(url_pattern="bar")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_barbaz_qux]

        actual_page = self.search.origin_search(url_pattern="barbaz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_barbaz_qux]

    def test_origin_url_unique_word_prefix_multiple_results(self):
        origin_foobar_baz = {"url": "http://foobar.baz"}
        origin_barbaz_qux = {"url": "http://barbaz.qux"}
        origin_qux_quux = {"url": "http://qux.quux"}

        self.search.origin_update(
            [origin_foobar_baz, origin_barbaz_qux, origin_qux_quux]
        )
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="qu")
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = [o["url"] for o in [origin_qux_quux, origin_barbaz_qux]]
        assert sorted(results) == sorted(expected_results)

        actual_page = self.search.origin_search(url_pattern="qux")
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = [o["url"] for o in [origin_qux_quux, origin_barbaz_qux]]
        assert sorted(results) == sorted(expected_results)

    def test_origin_url_all_terms(self):
        origin_foo_bar_baz = {"url": "http://foo.bar/baz"}
        origin_foo_bar_foo_bar = {"url": "http://foo.bar/foo.bar"}
        origins = [origin_foo_bar_baz, origin_foo_bar_foo_bar]

        self.search.origin_update(origins)
        self.search.flush()

        # Only results containing all terms should be returned.
        actual_page = self.search.origin_search(url_pattern="foo bar baz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_foo_bar_baz]

    def test_origin_with_visit(self):
        origin_foobar_baz = {"url": "http://foobar/baz"}

        self.search.origin_update(
            [{**o, "has_visits": True} for o in [origin_foobar_baz]]
        )
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="foobar", with_visit=True)
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_foobar_baz]

    def test_origin_with_visit_added(self):
        origin_foobar_baz = {"url": "http://foobar.baz"}

        self.search.origin_update([origin_foobar_baz])
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="foobar", with_visit=True)
        assert actual_page.next_page_token is None
        assert actual_page.results == []

        self.search.origin_update(
            [{**o, "has_visits": True} for o in [origin_foobar_baz]]
        )
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="foobar", with_visit=True)
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin_foobar_baz]

    def test_origin_no_visit_types_search(self):
        origins = [{"url": "http://foobar.baz"}]

        self.search.origin_update(origins)
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="http", visit_types=["git"])
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = []
        assert sorted(results) == sorted(expected_results)

        actual_page = self.search.origin_search(url_pattern="http", visit_types=None)
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = [origin["url"] for origin in origins]
        assert sorted(results) == sorted(expected_results)

    def test_origin_visit_types_search(self):
        origins = [
            {"url": "http://foobar.baz", "visit_types": ["git"]},
            {"url": "http://barbaz.qux", "visit_types": ["svn"]},
            {"url": "http://qux.quux", "visit_types": ["hg"]},
        ]

        self.search.origin_update(origins)
        self.search.flush()

        for origin in origins:
            actual_page = self.search.origin_search(
                url_pattern="http", visit_types=origin["visit_types"]
            )
            assert actual_page.next_page_token is None
            results = [r["url"] for r in actual_page.results]
            expected_results = [origin["url"]]
            assert sorted(results) == sorted(expected_results)

        actual_page = self.search.origin_search(url_pattern="http", visit_types=None)
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = [origin["url"] for origin in origins]
        assert sorted(results) == sorted(expected_results)

    def test_origin_visit_types_update_search(self):
        origin_url = "http://foobar.baz"
        self.search.origin_update([{"url": origin_url}])
        self.search.flush()

        def _add_visit_type(visit_type):
            self.search.origin_update(
                [{"url": origin_url, "visit_types": [visit_type]}]
            )
            self.search.flush()

        def _check_visit_types(visit_types_list):
            for visit_types in visit_types_list:
                actual_page = self.search.origin_search(
                    url_pattern="http", visit_types=visit_types
                )
                assert actual_page.next_page_token is None
                results = [r["url"] for r in actual_page.results]
                expected_results = [origin_url]
                assert sorted(results) == sorted(expected_results)

        _add_visit_type("git")
        _check_visit_types([["git"], ["git", "hg"]])

        _add_visit_type("svn")
        _check_visit_types([["git"], ["svn"], ["svn", "git"], ["git", "hg", "svn"]])

        _add_visit_type("hg")
        _check_visit_types(
            [
                ["git"],
                ["svn"],
                ["hg"],
                ["svn", "git"],
                ["hg", "git"],
                ["hg", "svn"],
                ["git", "hg", "svn"],
            ]
        )

    def test_origin_update_with_no_visit_types(self):
        """
        Update an origin with visit types first then with no visit types,
        check origin can still be searched with visit types afterwards.
        """
        origin_url = "http://foobar.baz"
        self.search.origin_update([{"url": origin_url, "visit_types": ["git"]}])
        self.search.flush()

        self.search.origin_update([{"url": origin_url}])
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="http", visit_types=["git"])
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = [origin_url]
        assert results == expected_results

    def test_origin_intrinsic_metadata_description(self):
        origin1_nothin = {"url": "http://origin1"}
        origin2_foobar = {"url": "http://origin2"}
        origin3_barbaz = {"url": "http://origin3"}

        self.search.origin_update(
            [
                {**origin1_nothin, "intrinsic_metadata": {},},
                {
                    **origin2_foobar,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": "foo bar",
                    },
                },
                {
                    **origin3_barbaz,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": "bar baz",
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="foo")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2_foobar]

        actual_page = self.search.origin_search(metadata_pattern="foo bar")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2_foobar]

        actual_page = self.search.origin_search(metadata_pattern="bar baz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin3_barbaz]

    def test_origin_intrinsic_metadata_all_terms(self):
        origin1_foobarfoobar = {"url": "http://origin1"}
        origin3_foobarbaz = {"url": "http://origin2"}

        self.search.origin_update(
            [
                {
                    **origin1_foobarfoobar,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": "foo bar foo bar",
                    },
                },
                {
                    **origin3_foobarbaz,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": "foo bar baz",
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="foo bar baz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin3_foobarbaz]

    def test_origin_intrinsic_metadata_long_description(self):
        origin1 = {"url": "http://origin1"}

        self.search.origin_update(
            [
                {
                    **origin1,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": " ".join(f"foo{i}" for i in range(1000000)),
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="foo42")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1]

    def test_origin_intrinsic_metadata_matches_cross_fields(self):
        """Checks the backend finds results even if the two words in the query are
        each in a different field."""
        origin1 = {"url": "http://origin1"}

        self.search.origin_update(
            [
                {
                    **origin1,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": "foo bar",
                        "author": "John Doe",
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="foo John")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1]

    def test_origin_intrinsic_metadata_nested(self):
        origin1_nothin = {"url": "http://origin1"}
        origin2_foobar = {"url": "http://origin2"}
        origin3_barbaz = {"url": "http://origin3"}

        self.search.origin_update(
            [
                {**origin1_nothin, "intrinsic_metadata": {},},
                {
                    **origin2_foobar,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "keywords": ["foo", "bar"],
                    },
                },
                {
                    **origin3_barbaz,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "keywords": ["bar", "baz"],
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="foo")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2_foobar]

        actual_page = self.search.origin_search(metadata_pattern="foo bar")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2_foobar]

        actual_page = self.search.origin_search(metadata_pattern="bar baz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin3_barbaz]

    def test_origin_intrinsic_metadata_inconsistent_type(self):
        """Checks the same field can have a concrete value, an object, or an array
        in different documents."""
        origin1_foobar = {"url": "http://origin1"}
        origin2_barbaz = {"url": "http://origin2"}
        origin3_bazqux = {"url": "http://origin3"}

        self.search.origin_update(
            [
                {
                    **origin1_foobar,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "author": {"familyName": "Foo", "givenName": "Bar",},
                    },
                },
            ]
        )
        self.search.flush()
        self.search.origin_update(
            [
                {
                    **origin2_barbaz,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "author": "Bar Baz",
                    },
                },
                {
                    **origin3_bazqux,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "author": ["Baz", "Qux"],
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="bar")
        assert actual_page.next_page_token is None
        results = [r["url"] for r in actual_page.results]
        expected_results = [o["url"] for o in [origin2_barbaz, origin1_foobar]]
        assert sorted(results) == sorted(expected_results)

        actual_page = self.search.origin_search(metadata_pattern="baz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2_barbaz, origin3_bazqux]

        actual_page = self.search.origin_search(metadata_pattern="foo")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1_foobar]

        actual_page = self.search.origin_search(metadata_pattern="bar baz")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2_barbaz]

        actual_page = self.search.origin_search(metadata_pattern="qux")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin3_bazqux]

        actual_page = self.search.origin_search(metadata_pattern="baz qux")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin3_bazqux]

        actual_page = self.search.origin_search(metadata_pattern="foo bar")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1_foobar]

    def test_origin_intrinsic_metadata_date(self):
        """Checks inserting a date-like in a field does not update the mapping to
        require every document uses a date in that field; or that search queries
        use a date either.
        Likewise for numeric fields."""
        origin1 = {"url": "http://origin1"}
        origin2 = {"url": "http://origin2"}

        self.search.origin_update(
            [
                {
                    **origin1,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "dateCreated": "2021-02-18T10:16:52",
                        "version": "1.0",
                    },
                }
            ]
        )
        self.search.flush()

        self.search.origin_update(
            [
                {
                    **origin2,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "dateCreated": "a long time ago",
                        "address": "in a galaxy far, far away",
                        "version": "a new hope",
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="2021")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1]

        actual_page = self.search.origin_search(metadata_pattern="long time ago")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin2]

    def test_origin_intrinsic_metadata_update(self):
        origin = {"url": "http://origin1"}
        origin_data = {
            **origin,
            "intrinsic_metadata": {
                "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                "author": "John Doe",
            },
        }

        self.search.origin_update([origin_data])
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="John")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin]

        origin_data["intrinsic_metadata"]["author"] = "Jane Doe"

        self.search.origin_update([origin_data])
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="Jane")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin]

    # TODO: add more tests with more codemeta terms

    # TODO: add more tests with edge cases

    @settings(deadline=None)
    @given(strategies.integers(min_value=1, max_value=4))
    def test_origin_url_paging(self, limit):
        # TODO: no hypothesis
        origin1_foo = {"url": "http://origin1/foo"}
        origin2_foobar = {"url": "http://origin2/foo/bar"}
        origin3_foobarbaz = {"url": "http://origin3/foo/bar/baz"}

        self.reset()
        self.search.origin_update([origin1_foo, origin2_foobar, origin3_foobarbaz])
        self.search.flush()

        results = stream_results(
            self.search.origin_search, url_pattern="foo bar baz", limit=limit
        )
        results = [res["url"] for res in results]
        expected_results = [o["url"] for o in [origin3_foobarbaz]]
        assert sorted(results[0 : len(expected_results)]) == sorted(expected_results)

        results = stream_results(
            self.search.origin_search, url_pattern="foo bar", limit=limit
        )
        results = [res["url"] for res in results]
        expected_results = [o["url"] for o in [origin2_foobar, origin3_foobarbaz]]
        assert sorted(results[0 : len(expected_results)]) == sorted(expected_results)

        results = stream_results(
            self.search.origin_search, url_pattern="foo", limit=limit
        )
        results = [res["url"] for res in results]
        expected_results = [
            o["url"] for o in [origin1_foo, origin2_foobar, origin3_foobarbaz]
        ]
        assert sorted(results[0 : len(expected_results)]) == sorted(expected_results)

    @settings(deadline=None)
    @given(strategies.integers(min_value=1, max_value=4))
    def test_origin_intrinsic_metadata_paging(self, limit):
        # TODO: no hypothesis
        origin1_foo = {"url": "http://origin1"}
        origin2_foobar = {"url": "http://origin2"}
        origin3_foobarbaz = {"url": "http://origin3"}

        self.reset()
        self.search.origin_update(
            [
                {
                    **origin1_foo,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "keywords": ["foo"],
                    },
                },
                {
                    **origin2_foobar,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "keywords": ["foo", "bar"],
                    },
                },
                {
                    **origin3_foobarbaz,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "keywords": ["foo", "bar", "baz"],
                    },
                },
            ]
        )
        self.search.flush()

        results = stream_results(
            self.search.origin_search, metadata_pattern="foo bar baz", limit=limit
        )
        assert list(results) == [origin3_foobarbaz]

        results = stream_results(
            self.search.origin_search, metadata_pattern="foo bar", limit=limit
        )
        assert list(results) == [origin2_foobar, origin3_foobarbaz]

        results = stream_results(
            self.search.origin_search, metadata_pattern="foo", limit=limit
        )
        assert list(results) == [origin1_foo, origin2_foobar, origin3_foobarbaz]

    def test_search_blocklisted_results(self):
        origin1 = {"url": "http://origin1"}
        origin2 = {"url": "http://origin2", "blocklisted": True}

        self.search.origin_update([origin1, origin2])
        self.search.flush()

        actual_page = self.search.origin_search(url_pattern="origin")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1]

    def test_search_blocklisted_update(self):
        origin1 = {"url": "http://origin1"}
        self.search.origin_update([origin1])
        self.search.flush()

        result_page = self.search.origin_search(url_pattern="origin")
        assert result_page.next_page_token is None
        assert result_page.results == [origin1]

        self.search.origin_update([{**origin1, "blocklisted": True}])
        self.search.flush()

        result_page = self.search.origin_search(url_pattern="origin")
        assert result_page.next_page_token is None
        assert result_page.results == []

        self.search.origin_update(
            [{**origin1, "has_visits": True, "visit_types": ["git"]}]
        )
        self.search.flush()

        result_page = self.search.origin_search(url_pattern="origin")
        assert result_page.next_page_token is None
        assert result_page.results == []
