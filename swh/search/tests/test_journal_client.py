# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from datetime import datetime, timezone
import functools
from unittest.mock import MagicMock

import pytest

from swh.model.model import (
    ObjectType,
    Person,
    Release,
    Revision,
    RevisionType,
    Snapshot,
    SnapshotBranch,
    TargetType,
    Timestamp,
    TimestampWithTimezone,
    hash_to_bytes,
)
from swh.search.journal_client import (
    fetch_last_revision_release_date,
    process_journal_objects,
)
from swh.storage import get_storage

DATES = [
    TimestampWithTimezone(
        timestamp=Timestamp(seconds=1234567891, microseconds=0,),
        offset=120,
        negative_utc=False,
    ),
    TimestampWithTimezone(
        timestamp=Timestamp(seconds=1234567892, microseconds=0,),
        offset=120,
        negative_utc=False,
    ),
    TimestampWithTimezone(
        timestamp=Timestamp(seconds=1234567893, microseconds=0,),
        offset=120,
        negative_utc=False,
    ),
    TimestampWithTimezone(
        timestamp=Timestamp(seconds=1234567894, microseconds=0,),
        offset=120,
        negative_utc=False,
    ),
]

COMMITTERS = [
    Person(fullname=b"foo", name=b"foo", email=b""),
    Person(fullname=b"bar", name=b"bar", email=b""),
]

REVISIONS = [
    Revision(
        message=b"revision_1_message",
        date=DATES[0],
        committer=COMMITTERS[0],
        author=COMMITTERS[0],
        committer_date=DATES[0],
        type=RevisionType.GIT,
        directory=b"\x01" * 20,
        synthetic=False,
        metadata=None,
        parents=(
            hash_to_bytes("9b918dd063cec85c2bc63cc7f167e29f5894dcbc"),
            hash_to_bytes("757f38bdcd8473aaa12df55357f5e2f1a318e672"),
        ),
    ),
    Revision(
        message=b"revision_2_message",
        date=DATES[1],
        committer=COMMITTERS[1],
        author=COMMITTERS[1],
        committer_date=DATES[1],
        type=RevisionType.MERCURIAL,
        directory=b"\x02" * 20,
        synthetic=False,
        metadata=None,
        parents=(),
        extra_headers=((b"foo", b"bar"),),
    ),
    Revision(
        message=b"revision_3_message",
        date=DATES[2],
        committer=COMMITTERS[0],
        author=COMMITTERS[0],
        committer_date=DATES[2],
        type=RevisionType.GIT,
        directory=b"\x03" * 20,
        synthetic=False,
        metadata=None,
        parents=(),
    ),
]

RELEASES = [
    Release(
        name=b"v0.0.1",
        date=DATES[1],
        author=COMMITTERS[0],
        target_type=ObjectType.REVISION,
        target=b"\x04" * 20,
        message=b"foo",
        synthetic=False,
    ),
    Release(
        name=b"v0.0.2",
        date=DATES[2],
        author=COMMITTERS[1],
        target_type=ObjectType.REVISION,
        target=b"\x05" * 20,
        message=b"bar",
        synthetic=False,
    ),
    Release(
        name=b"v0.0.3",
        date=DATES[3],
        author=COMMITTERS[1],
        target_type=ObjectType.REVISION,
        target=b"\x05" * 20,
        message=b"foobar",
        synthetic=False,
    ),
]

SNAPSHOTS = [
    Snapshot(
        branches={
            b"target/revision1": SnapshotBranch(
                target_type=TargetType.REVISION, target=REVISIONS[0].id,
            ),
            b"target/revision2": SnapshotBranch(
                target_type=TargetType.REVISION, target=REVISIONS[1].id,
            ),
            b"target/revision3": SnapshotBranch(
                target_type=TargetType.REVISION, target=REVISIONS[2].id,
            ),
            b"target/release1": SnapshotBranch(
                target_type=TargetType.RELEASE, target=RELEASES[0].id
            ),
            b"target/release2": SnapshotBranch(
                target_type=TargetType.RELEASE, target=RELEASES[1].id
            ),
            b"target/release3": SnapshotBranch(
                target_type=TargetType.RELEASE, target=RELEASES[2].id
            ),
            b"target/alias": SnapshotBranch(
                target_type=TargetType.ALIAS, target=b"target/revision1"
            ),
        },
    ),
    Snapshot(
        branches={
            b"target/revision1": SnapshotBranch(
                target_type=TargetType.REVISION, target=REVISIONS[0].id,
            )
        },
    ),
    Snapshot(
        branches={
            b"target/release1": SnapshotBranch(
                target_type=TargetType.RELEASE, target=RELEASES[0].id
            )
        },
    ),
    Snapshot(branches={}),
]


@pytest.fixture
def storage():
    storage = get_storage("memory")

    storage.revision_add(REVISIONS)
    storage.release_add(RELEASES)
    storage.snapshot_add(SNAPSHOTS)
    return storage


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


def test_journal_client_origin_visit_status_from_journal(storage):
    search_mock = MagicMock()

    worker_fn = functools.partial(
        process_journal_objects, search=search_mock, storage=storage
    )
    current_datetime = datetime.now(tz=timezone.utc)

    worker_fn(
        {
            "origin_visit_status": [
                {
                    "origin": "http://foobar.baz",
                    "status": "full",
                    "type": "git",
                    "visit": 5,
                    "date": current_datetime,
                    "snapshot": SNAPSHOTS[0].id,
                }  # full visits ok
            ]
        }
    )
    search_mock.origin_update.assert_called_once_with(
        [
            {
                "url": "http://foobar.baz",
                "visit_types": ["git"],
                "has_visits": True,
                "nb_visits": 5,
                "snapshot_id": SNAPSHOTS[0].id.hex(),
                "last_visit_date": current_datetime.isoformat(),
                "last_eventful_visit_date": current_datetime.isoformat(),
                "last_revision_date": "2009-02-14T01:31:33+02:00",
                "last_release_date": "2009-02-14T01:31:34+02:00",
            },
        ]
    )

    search_mock.reset_mock()

    # non-full visits only set the visit_types attribute
    worker_fn(
        {
            "origin_visit_status": [
                {
                    "origin": "http://foobar.baz",
                    "type": "git",
                    "status": "partial",
                    "visit": 5,
                    "date": current_datetime,
                }
            ]
        }
    )
    search_mock.origin_update.assert_called_once_with(
        [{"url": "http://foobar.baz", "visit_types": ["git"]}]
    )


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
                        "programmingLanguage": "python",
                        "license": "MIT",
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
                    "programmingLanguage": "python",
                    "license": "MIT",
                },
            },
        ]
    )


def test_fetch_last_revision_release_date(storage):
    for snapshot in SNAPSHOTS:
        assert fetch_last_revision_release_date(snapshot.id, storage) is not None
