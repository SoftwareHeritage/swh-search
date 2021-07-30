# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from datetime import datetime, timedelta, timezone
from itertools import permutations

from hypothesis import given, settings, strategies
import pytest

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

    def test_origin_nb_visits_update_search(self):
        origin_url = "http://foobar.baz"
        self.search.origin_update([{"url": origin_url}])
        self.search.flush()

        def _update_nb_visits(nb_visits):
            self.search.origin_update([{"url": origin_url, "nb_visits": nb_visits}])
            self.search.flush()

        def _check_min_nb_visits(min_nb_visits):
            actual_page = self.search.origin_search(
                url_pattern=origin_url, min_nb_visits=min_nb_visits,
            )
            assert actual_page.next_page_token is None
            results = [r["url"] for r in actual_page.results]
            expected_results = [origin_url]
            assert sorted(results) == sorted(expected_results)

        _update_nb_visits(2)
        _check_min_nb_visits(2)  # Works for = 2
        _check_min_nb_visits(1)  # Works for < 2

        with pytest.raises(AssertionError):
            _check_min_nb_visits(
                5
            )  # No results for nb_visits >= 5 (should throw error)

        _update_nb_visits(5)
        _check_min_nb_visits(5)  # Works for = 5
        _check_min_nb_visits(3)  # Works for < 5

    def test_origin_last_visit_date_update_search(self):
        origin_url = "http://foobar.baz"
        self.search.origin_update([{"url": origin_url}])
        self.search.flush()

        def _update_last_visit_date(last_visit_date):
            self.search.origin_update(
                [{"url": origin_url, "last_visit_date": last_visit_date}]
            )
            self.search.flush()

        def _check_min_last_visit_date(min_last_visit_date):
            actual_page = self.search.origin_search(
                url_pattern=origin_url, min_last_visit_date=min_last_visit_date,
            )
            assert actual_page.next_page_token is None
            results = [r["url"] for r in actual_page.results]
            expected_results = [origin_url]
            assert sorted(results) == sorted(expected_results)

        now = datetime.now(tz=timezone.utc).isoformat()
        now_minus_5_hours = (
            datetime.now(tz=timezone.utc) - timedelta(hours=5)
        ).isoformat()
        now_plus_5_hours = (
            datetime.now(tz=timezone.utc) + timedelta(hours=5)
        ).isoformat()

        _update_last_visit_date(now)

        _check_min_last_visit_date(now)  # Works for =
        _check_min_last_visit_date(now_minus_5_hours)  # Works for <
        with pytest.raises(AssertionError):
            _check_min_last_visit_date(now_plus_5_hours)  # Fails for >

        _update_last_visit_date(now_plus_5_hours)

        _check_min_last_visit_date(now_plus_5_hours)  # Works for =
        _check_min_last_visit_date(now)  # Works for <

    def test_journal_client_origin_visit_status_permutation(self):
        NOW = datetime.now(tz=timezone.utc).isoformat()
        NOW_MINUS_5_HOURS = (
            datetime.now(tz=timezone.utc) - timedelta(hours=5)
        ).isoformat()
        NOW_PLUS_5_HOURS = (
            datetime.now(tz=timezone.utc) + timedelta(hours=5)
        ).isoformat()

        VISIT_STATUSES = [
            {
                "url": "http://foobar.baz",
                "snapshot_id": "SNAPSHOT_1",
                "last_eventful_visit_date": NOW,
            },
            {
                "url": "http://foobar.baz",
                "snapshot_id": "SNAPSHOT_1",
                "last_eventful_visit_date": NOW_MINUS_5_HOURS,
            },
            {
                "url": "http://foobar.baz",
                "snapshot_id": "SNAPSHOT_2",
                "last_eventful_visit_date": NOW_PLUS_5_HOURS,
            },
        ]

        for visit_statuses in permutations(VISIT_STATUSES, len(VISIT_STATUSES)):
            self.search.origin_update(visit_statuses)
            self.search.flush()
            origin_url = "http://foobar.baz"
            actual_page = self.search.origin_search(
                url_pattern=origin_url, min_last_eventful_visit_date=NOW_PLUS_5_HOURS,
            )
            assert actual_page.next_page_token is None
            results = [r["url"] for r in actual_page.results]
            expected_results = [origin_url]
            assert sorted(results) == sorted(expected_results)

            self.reset()

    def test_origin_last_eventful_visit_date_update_search(self):
        origin_url = "http://foobar.baz"
        self.search.origin_update([{"url": origin_url}])
        self.search.flush()

        def _update_last_eventful_visit_date(snapshot_id, last_eventful_visit_date):
            self.search.origin_update(
                [
                    {
                        "url": origin_url,
                        "snapshot_id": snapshot_id,
                        "last_eventful_visit_date": last_eventful_visit_date,
                    }
                ]
            )
            self.search.flush()

        def _check_min_last_eventful_visit_date(min_last_eventful_visit_date):
            actual_page = self.search.origin_search(
                url_pattern=origin_url,
                min_last_eventful_visit_date=min_last_eventful_visit_date,
            )
            assert actual_page.next_page_token is None
            results = [r["url"] for r in actual_page.results]
            expected_results = [origin_url]
            assert sorted(results) == sorted(expected_results)

        now = datetime.now(tz=timezone.utc).isoformat()
        now_minus_5_hours = (
            datetime.now(tz=timezone.utc) - timedelta(hours=5)
        ).isoformat()
        now_plus_5_hours = (
            datetime.now(tz=timezone.utc) + timedelta(hours=5)
        ).isoformat()

        snapshot_1 = "SNAPSHOT_1"
        snapshot_2 = "SNAPSHOT_2"

        _update_last_eventful_visit_date(snapshot_1, now)

        _check_min_last_eventful_visit_date(now)  # Works for =
        _check_min_last_eventful_visit_date(now_minus_5_hours)  # Works for <
        with pytest.raises(AssertionError):
            _check_min_last_eventful_visit_date(now_plus_5_hours)  # Fails for >

        _update_last_eventful_visit_date(
            snapshot_1, now_plus_5_hours
        )  # Revisit(not eventful) same origin

        _check_min_last_eventful_visit_date(
            now
        )  # Should remain the same because recent visit wasn't eventful
        with pytest.raises(AssertionError):
            _check_min_last_eventful_visit_date(now_plus_5_hours)

        _update_last_eventful_visit_date(
            snapshot_2, now_plus_5_hours
        )  # Revisit(eventful) same origin
        _check_min_last_eventful_visit_date(now_plus_5_hours)  # Works for =
        _check_min_last_eventful_visit_date(now)  # Works for <

    def _test_origin_last_revision_release_date_update_search(self, date_type):
        origin_url = "http://foobar.baz"
        self.search.origin_update([{"url": origin_url}])
        self.search.flush()

        def _update_last_revision_release_date(date):
            self.search.origin_update([{"url": origin_url, date_type: date,}])
            self.search.flush()

        def _check_min_last_revision_release_date(date):
            actual_page = self.search.origin_search(
                url_pattern=origin_url, **{f"min_{date_type}": date},
            )
            assert actual_page.next_page_token is None
            results = [r["url"] for r in actual_page.results]
            expected_results = [origin_url]
            assert sorted(results) == sorted(expected_results)

        now = datetime.now(tz=timezone.utc).isoformat()
        now_minus_5_hours = (
            datetime.now(tz=timezone.utc) - timedelta(hours=5)
        ).isoformat()
        now_plus_5_hours = (
            datetime.now(tz=timezone.utc) + timedelta(hours=5)
        ).isoformat()

        _update_last_revision_release_date(now)

        _check_min_last_revision_release_date(now)
        _check_min_last_revision_release_date(now_minus_5_hours)
        with pytest.raises(AssertionError):
            _check_min_last_revision_release_date(now_plus_5_hours)

        _update_last_revision_release_date(now_plus_5_hours)

        _check_min_last_revision_release_date(now_plus_5_hours)
        _check_min_last_revision_release_date(now)

    def test_origin_last_revision_date_update_search(self):
        self._test_origin_last_revision_release_date_update_search(
            date_type="last_revision_date"
        )

    def test_origin_last_release_date_update_search(self):
        self._test_origin_last_revision_release_date_update_search(
            date_type="last_revision_date"
        )

    def test_origin_instrinsic_metadata_dates_filter_sorting_search(self):

        DATE_0 = "1999-06-28"
        DATE_1 = "2001-02-13"
        DATE_2 = "2005-10-02"

        ORIGINS = [
            {
                "url": "http://foobar.0.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "dateCreated": DATE_0,
                    "dateModified": DATE_1,
                    "datePublished": DATE_2,
                },
            },
            {
                "url": "http://foobar.1.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "dateCreated": DATE_1,
                    "dateModified": DATE_2,
                    "datePublished": DATE_2,
                },
            },
            {
                "url": "http://foobar.2.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "dateCreated": DATE_2,
                    "dateModified": DATE_2,
                    "datePublished": DATE_2,
                },
            },
        ]
        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_results(origin_indices, sort_results=True, **kwargs):
            page = self.search.origin_search(url_pattern="foobar", **kwargs)
            results = [r["url"] for r in page.results]
            if sort_results:
                assert sorted(results) == sorted(
                    [ORIGINS[index]["url"] for index in origin_indices]
                )
            else:
                assert results == [ORIGINS[index]["url"] for index in origin_indices]

        _check_results(min_date_created=DATE_0, origin_indices=[0, 1, 2])
        _check_results(min_date_created=DATE_1, origin_indices=[1, 2])
        _check_results(min_date_created=DATE_2, origin_indices=[2])

        _check_results(min_date_modified=DATE_0, origin_indices=[0, 1, 2])
        _check_results(min_date_modified=DATE_1, origin_indices=[0, 1, 2])
        _check_results(min_date_modified=DATE_2, origin_indices=[1, 2])

        _check_results(min_date_published=DATE_0, origin_indices=[0, 1, 2])
        _check_results(min_date_published=DATE_1, origin_indices=[0, 1, 2])
        _check_results(min_date_published=DATE_2, origin_indices=[0, 1, 2])

        # Sorting
        _check_results(
            sort_by=["-date_created"], origin_indices=[2, 1, 0], sort_results=False
        )
        _check_results(
            sort_by=["date_created"], origin_indices=[0, 1, 2], sort_results=False
        )

    def test_origin_keywords_search(self):
        ORIGINS = [
            {
                "url": "http://foobar.1.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "Django is a backend framework for applications",
                    "keywords": "django,backend,server,web,framework",
                },
            },
            {
                "url": "http://foobar.2.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "Native Android applications are fast",
                    "keywords": "android,mobile,ui",
                },
            },
            {
                "url": "http://foobar.3.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "React framework helps you build web applications",
                    "keywords": "react,web,ui",
                },
            },
        ]
        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_results(keywords, origin_indices, sorting=False):
            page = self.search.origin_search(url_pattern="foobar", keywords=keywords)
            results = [r["url"] for r in page.results]
            if sorting:
                assert sorted(results) == sorted(
                    [ORIGINS[index]["url"] for index in origin_indices]
                )
            else:
                assert results == [ORIGINS[index]["url"] for index in origin_indices]

        _check_results(["build"], [2])

        _check_results(["web"], [2, 0])
        _check_results(["ui"], [1, 2])

        # Following tests ensure that boosts work properly

        # Baseline: "applications" is common in all origin descriptions
        _check_results(["applications"], [1, 0, 2], True)

        # ORIGINS[0] has 'framework' in: keyword + description
        # ORIGINS[2] has 'framework' in: description
        # ORIGINS[1] has 'framework' in: None
        _check_results(["framework", "applications"], [0, 2, 1])

        # ORIGINS[1] has 'ui' in: keyword
        # ORIGINS[1] has 'ui' in: keyword
        # ORIGINS[0] has 'ui' in: None
        _check_results(["applications", "ui"], [1, 2, 0])

        # ORIGINS[2] has 'web' in: keyword + description
        # ORIGINS[0] has 'web' in: keyword
        # ORIGINS[1] has 'web' in: None
        _check_results(["web", "applications"], [2, 0, 1])

    def test_origin_sort_by_search(self):

        now = datetime.now(tz=timezone.utc).isoformat()
        now_minus_5_hours = (
            datetime.now(tz=timezone.utc) - timedelta(hours=5)
        ).isoformat()
        now_plus_5_hours = (
            datetime.now(tz=timezone.utc) + timedelta(hours=5)
        ).isoformat()

        ORIGINS = [
            {
                "url": "http://foobar.1.com",
                "nb_visits": 1,
                "last_visit_date": now_minus_5_hours,
            },
            {"url": "http://foobar.2.com", "nb_visits": 2, "last_visit_date": now,},
            {
                "url": "http://foobar.3.com",
                "nb_visits": 3,
                "last_visit_date": now_plus_5_hours,
            },
        ]
        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_results(sort_by, origins):
            page = self.search.origin_search(url_pattern="foobar", sort_by=sort_by)
            results = [r["url"] for r in page.results]
            assert results == [origin["url"] for origin in origins]

        _check_results(["nb_visits"], ORIGINS)
        _check_results(["-nb_visits"], ORIGINS[::-1])

        _check_results(["last_visit_date"], ORIGINS)
        _check_results(["-last_visit_date"], ORIGINS[::-1])

        _check_results(["nb_visits", "-last_visit_date"], ORIGINS)
        _check_results(["-last_visit_date", "nb_visits"], ORIGINS[::-1])

    def test_origin_instrinsic_metadata_license_search(self):
        ORIGINS = [
            {
                "url": "http://foobar.1.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar",
                    "license": "https://spdx.org/licenses/MIT",
                },
            },
            {
                "url": "http://foobar.2.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar",
                    "license": "BSD-3-Clause",
                },
            },
        ]
        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_results(licenses, origin_indices):
            page = self.search.origin_search(url_pattern="foobar", licenses=licenses)
            results = [r["url"] for r in page.results]
            assert sorted(results) == sorted(
                [ORIGINS[i]["url"] for i in origin_indices]
            )

        _check_results(["MIT"], [0])
        _check_results(["bsd"], [1])
        _check_results(["mit", "3-Clause"], [0, 1])

    def test_origin_instrinsic_metadata_programming_language_search(self):
        ORIGINS = [
            {
                "url": "http://foobar.1.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar",
                    "programmingLanguage": "python",
                },
            },
            {
                "url": "http://foobar.2.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar",
                    "programmingLanguage": "javascript",
                },
            },
        ]
        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_results(programming_languages, origin_indices):
            page = self.search.origin_search(
                url_pattern="foobar", programming_languages=programming_languages
            )
            results = [r["url"] for r in page.results]
            assert sorted(results) == sorted(
                [ORIGINS[i]["url"] for i in origin_indices]
            )

        _check_results(["python"], [0])
        _check_results(["javascript"], [1])
        _check_results(["python", "javascript"], [0, 1])

    def test_origin_instrinsic_metadata_multiple_field_search(self):
        ORIGINS = [
            {
                "url": "http://foobar.1.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar 1",
                    "programmingLanguage": "python",
                    "license": "https://spdx.org/licenses/MIT",
                },
            },
            {
                "url": "http://foobar.2.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar 2",
                    "programmingLanguage": ["javascript", "html", "css"],
                    "license": [
                        "https://spdx.org/licenses/CC-BY-1.0",
                        "https://spdx.org/licenses/Apache-1.0",
                    ],
                },
            },
            {
                "url": "http://foobar.3.com",
                "intrinsic_metadata": {
                    "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                    "description": "foo bar 3",
                    "programmingLanguage": ["Cpp", "c"],
                    "license": "https://spdx.org/licenses/LGPL-2.0-only",
                },
            },
        ]
        self.search.origin_update(ORIGINS)
        self.search.flush()

        def _check_result(programming_languages, licenses, origin_indices):
            page = self.search.origin_search(
                url_pattern="foobar",
                programming_languages=programming_languages,
                licenses=licenses,
            )
            results = [r["url"] for r in page.results]
            assert sorted(results) == sorted(
                [ORIGINS[i]["url"] for i in origin_indices]
            )

        _check_result(["javascript"], ["CC"], [1])
        _check_result(["css"], ["CC"], [1])
        _check_result(["css"], ["CC", "apache"], [1])

        _check_result(["python", "javascript"], ["MIT"], [0])

        _check_result(["c", "python"], ["LGPL", "mit"], [2, 0])

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
        """Checks ElasticSearch does not try to store large values untokenize,
        which would be inefficient and crash it with:

        Document contains at least one immense term in field="intrinsic_metadata.http://schema.org/description.@value" (whose UTF8 encoding is longer than the max length 32766), all of which were skipped.
        """  # noqa
        origin1 = {"url": "http://origin1"}

        self.search.origin_update(
            [
                {
                    **origin1,
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": " ".join(f"foo{i}" for i in range(100000)),
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

    def test_origin_intrinsic_metadata_string_mapping(self):
        """Checks inserting a date-like in a field does not update the mapping to
        require every document uses a date in that field; or that search queries
        use a date either.
        Likewise for numeric and boolean fields."""
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
                        "isAccessibleForFree": True,
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
                        "isAccessibleForFree": "it depends",
                    },
                },
            ]
        )
        self.search.flush()

        actual_page = self.search.origin_search(metadata_pattern="1.0")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1]

        actual_page = self.search.origin_search(metadata_pattern="long")
        assert actual_page.next_page_token is None
        assert (
            actual_page.results == []
        )  # "%Y-%m-%d" not followed, so value is rejected

        actual_page = self.search.origin_search(metadata_pattern="true")
        assert actual_page.next_page_token is None
        assert actual_page.results == [origin1]

        actual_page = self.search.origin_search(metadata_pattern="it depends")
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

    def test_filter_keyword_in_filter(self):
        origin1 = {
            "url": "foo language in ['foo baz'] bar",
        }
        self.search.origin_update([origin1])
        self.search.flush()

        result_page = self.search.origin_search(url_pattern="language in ['foo bar']")
        assert result_page.next_page_token is None
        assert result_page.results == [origin1]

        result_page = self.search.origin_search(url_pattern="baaz")
        assert result_page.next_page_token is None
        assert result_page.results == []
