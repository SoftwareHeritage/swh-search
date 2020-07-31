# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import functools
import unittest
from unittest.mock import MagicMock

from swh.search.journal_client import process_journal_objects


class SearchJournalClientTest(unittest.TestCase):
    def test_origin_from_journal(self):
        search_mock = MagicMock()

        worker_fn = functools.partial(process_journal_objects, search=search_mock,)

        worker_fn({"origin": [{"url": "http://foobar.baz"},]})
        search_mock.origin_update.assert_called_once_with(
            [{"url": "http://foobar.baz"},]
        )

        search_mock.reset_mock()

        worker_fn(
            {"origin": [{"url": "http://foobar.baz"}, {"url": "http://barbaz.qux"},]}
        )
        search_mock.origin_update.assert_called_once_with(
            [{"url": "http://foobar.baz"}, {"url": "http://barbaz.qux"},]
        )

    def test_origin_visit_from_journal(self):
        search_mock = MagicMock()

        worker_fn = functools.partial(process_journal_objects, search=search_mock,)

        worker_fn({"origin_visit": [{"origin": {"url": "http://foobar.baz"},}]})
        search_mock.origin_update.assert_called_once_with(
            [{"url": "http://foobar.baz", "has_visits": True},]
        )

    def test_origin_metadata_from_journal(self):
        search_mock = MagicMock()

        worker_fn = functools.partial(process_journal_objects, search=search_mock,)

        worker_fn(
            {
                "origin_intrinsic_metadata": [
                    {
                        "origin_url": "http://foobar.baz",
                        "metadata": {
                            "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                            "description": "foo bar",
                        },
                    },
                ]
            }
        )
        search_mock.origin_update.assert_called_once_with(
            [
                {
                    "url": "http://foobar.baz",
                    "intrinsic_metadata": {
                        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
                        "description": "foo bar",
                    },
                },
            ]
        )
