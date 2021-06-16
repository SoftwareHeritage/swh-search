# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from datetime import datetime, timezone
import functools
from unittest.mock import MagicMock

from swh.search.journal_client import process_journal_objects


def test_journal_client_origin_from_journal():
    search_mock = MagicMock()

    worker_fn = functools.partial(process_journal_objects, search=search_mock,)

    worker_fn({"origin": [{"url": "http://foobar.baz"},]})
    search_mock.origin_update.assert_called_once_with(
        [{"url": "http://foobar.baz"},]
    )

    search_mock.reset_mock()

    worker_fn({"origin": [{"url": "http://foobar.baz"}, {"url": "http://barbaz.qux"},]})
    search_mock.origin_update.assert_called_once_with(
        [{"url": "http://foobar.baz"}, {"url": "http://barbaz.qux"},]
    )


def test_journal_client_origin_visit_from_journal():
    search_mock = MagicMock()

    worker_fn = functools.partial(process_journal_objects, search=search_mock,)

    worker_fn({"origin_visit": [{"origin": "http://foobar.baz", "type": "git"},]})
    search_mock.origin_update.assert_called_once_with(
        [{"url": "http://foobar.baz", "visit_types": ["git"]},]
    )


def test_journal_client_origin_visit_status_from_journal():
    search_mock = MagicMock()

    worker_fn = functools.partial(process_journal_objects, search=search_mock,)
    current_datetime = datetime.now(tz=timezone.utc)

    worker_fn(
        {
            "origin_visit_status": [
                {
                    "origin": "http://foobar.baz",
                    "status": "full",
                    "visit": 5,
                    "date": current_datetime,
                    "snapshot": None,
                }  # full visits ok
            ]
        }
    )
    search_mock.origin_update.assert_called_once_with(
        [
            {
                "url": "http://foobar.baz",
                "has_visits": True,
                "nb_visits": 5,
                "snapshot_id": None,
                "last_visit_date": current_datetime.isoformat(),
                "last_eventful_visit_date": current_datetime.isoformat(),
            },
        ]
    )

    search_mock.reset_mock()

    # non-full visits are filtered out
    worker_fn(
        {
            "origin_visit_status": [
                {
                    "origin": "http://foobar.baz",
                    "status": "partial",
                    "visit": 5,
                    "date": current_datetime,
                }
            ]
        }
    )
    search_mock.origin_update.assert_not_called()


def test_journal_client_origin_metadata_from_journal():
    search_mock = MagicMock()

    worker_fn = functools.partial(process_journal_objects, search=search_mock,)

    worker_fn(
        {
            "origin_intrinsic_metadata": [
                {
                    "id": "http://foobar.baz",
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
