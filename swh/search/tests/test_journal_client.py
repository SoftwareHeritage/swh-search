# Copyright (C) 2019-2026  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from datetime import datetime, timedelta, timezone

import pytest

from swh.model.hashutil import hash_to_bytes
from swh.model.model import (
    ObjectType,
    Origin,
    OriginVisit,
    Person,
    Release,
    Revision,
    RevisionType,
    Snapshot,
    SnapshotBranch,
    SnapshotTargetType,
    TimestampWithTimezone,
)
from swh.search.journal_client import (
    convert_from_origin_metadata_dict,
    convert_journal_object,
    convert_origin,
    convert_origin_visit_status,
    fetch_last_revision_release_date,
)
from swh.storage import get_storage

VISIT_DATE = datetime(2024, 5, 30, 1, 2, 3, tzinfo=timezone(timedelta(hours=2)))

ORIGIN = Origin(url="http://foobar.baz")
ORIGIN2 = Origin(url="http://foobar2.baz")
ORIGIN3 = Origin(url="http://barbaz.qux")

ORIGINS = [ORIGIN, ORIGIN2, ORIGIN3]

DATES = [
    TimestampWithTimezone.from_datetime(
        datetime(2009, 2, 14, 1, 31, 31, tzinfo=timezone(timedelta(hours=2)))
    ),
    TimestampWithTimezone.from_datetime(
        datetime(2009, 2, 14, 1, 31, 32, tzinfo=timezone(timedelta(hours=2)))
    ),
    TimestampWithTimezone.from_datetime(
        datetime(2009, 2, 14, 1, 31, 33, tzinfo=timezone(timedelta(hours=2)))
    ),
    TimestampWithTimezone.from_datetime(
        datetime(2009, 2, 14, 1, 31, 34, tzinfo=timezone(timedelta(hours=2)))
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
                target_type=SnapshotTargetType.REVISION,
                target=REVISIONS[0].id,
            ),
            b"target/revision2": SnapshotBranch(
                target_type=SnapshotTargetType.REVISION,
                target=REVISIONS[1].id,
            ),
            b"target/revision3": SnapshotBranch(
                target_type=SnapshotTargetType.REVISION,
                target=REVISIONS[2].id,
            ),
            b"target/release1": SnapshotBranch(
                target_type=SnapshotTargetType.RELEASE, target=RELEASES[0].id
            ),
            b"target/release2": SnapshotBranch(
                target_type=SnapshotTargetType.RELEASE, target=RELEASES[1].id
            ),
            b"target/release3": SnapshotBranch(
                target_type=SnapshotTargetType.RELEASE, target=RELEASES[2].id
            ),
            b"target/alias": SnapshotBranch(
                target_type=SnapshotTargetType.ALIAS, target=b"target/revision1"
            ),
        },
    ),
    Snapshot(
        branches={
            b"target/revision1": SnapshotBranch(
                target_type=SnapshotTargetType.REVISION,
                target=REVISIONS[0].id,
            )
        },
    ),
    Snapshot(
        branches={
            b"target/release1": SnapshotBranch(
                target_type=SnapshotTargetType.RELEASE, target=RELEASES[0].id
            )
        },
    ),
    Snapshot(branches={}),
]

VISITS = [
    OriginVisit(
        # used for the test case in which the visit status message does not
        # come with the 'type' element
        origin=ORIGIN2.url,
        date=VISIT_DATE,
        type="hg",
        visit=5,
    )
]


@pytest.fixture
def storage():
    storage = get_storage("memory")

    storage.revision_add(REVISIONS)
    storage.release_add(RELEASES)
    storage.snapshot_add(SNAPSHOTS)
    storage.origin_add(ORIGINS + [Origin(url=visit.origin) for visit in VISITS])
    storage.origin_visit_add(VISITS)
    return storage


def test_convert_origin(storage):
    actual_origin = convert_origin(ORIGIN, storage)

    assert actual_origin == ORIGIN


def test_convert_origin_visit_status(storage):
    current_datetime = datetime.now(tz=timezone.utc)

    actual_ovs = convert_origin_visit_status(
        {
            "origin": ORIGIN.url,
            "status": "full",
            "type": "git",
            "visit": 5,
            "date": current_datetime,
            "snapshot": SNAPSHOTS[0].id,
        },  # full visits ok
        storage,
    )

    assert actual_ovs == {
        "url": ORIGIN.url,
        "visit_types": ["git"],
        "has_visits": True,
        "nb_visits": 5,
        "snapshot_id": SNAPSHOTS[0].id.hex(),
        "last_visit_date": current_datetime.isoformat(),
        "last_eventful_visit_date": current_datetime.isoformat(),
        "last_revision_date": "2009-02-14T01:31:33+02:00",
        "last_release_date": "2009-02-14T01:31:34+02:00",
    }

    # 2.
    # non-full visits only set the visit_types attribute

    actual_ovs2 = convert_origin_visit_status(
        {
            "origin": ORIGIN.url,
            "type": "git",
            "status": "partial",
            "visit": 5,
            "date": current_datetime,
        },
        storage,
    )

    assert actual_ovs2 == {"url": ORIGIN.url, "visit_types": ["git"]}

    # 3.
    # test a visit status missing the 'type' item (there are such topic
    # messages in kafka) but the visit exists in the storage

    actual_ovs3 = convert_origin_visit_status(
        {
            "origin": ORIGIN2.url,
            "status": "full",
            "visit": 5,
            "date": current_datetime,
            "snapshot": SNAPSHOTS[0].id,
        },  # full visits ok
        storage,
    )

    assert actual_ovs3 == {
        "url": ORIGIN2.url,
        "visit_types": ["hg"],
        "has_visits": True,
        "nb_visits": 5,
        "snapshot_id": SNAPSHOTS[0].id.hex(),
        "last_visit_date": current_datetime.isoformat(),
        "last_eventful_visit_date": current_datetime.isoformat(),
        "last_revision_date": "2009-02-14T01:31:33+02:00",
        "last_release_date": "2009-02-14T01:31:34+02:00",
    }

    # 4.
    # test a visit status missing the 'type' item (there are such topic
    # messages in kafka) but the visit does not exists in the storage
    actual_ovs4 = convert_origin_visit_status(
        {
            "origin": ORIGIN.url,
            "status": "full",
            "visit": 5,
            "date": current_datetime,
            "snapshot": SNAPSHOTS[0].id,
        },  # full visits ok
        storage,
    )

    assert actual_ovs4 == {
        "url": ORIGIN.url,
        "visit_types": [],
        "has_visits": True,
        "nb_visits": 5,
        "snapshot_id": SNAPSHOTS[0].id.hex(),
        "last_visit_date": current_datetime.isoformat(),
        "last_eventful_visit_date": current_datetime.isoformat(),
        "last_revision_date": "2009-02-14T01:31:33+02:00",
        "last_release_date": "2009-02-14T01:31:34+02:00",
    }

    # test a visit status missing the 'type' item (there are such topic
    # messages in kafka) but the visit does not exists in the storage


def test_convert_origin_metadata(storage):

    metadata = {
        "@context": "https://doi.org/10.5063/schema/codemeta-2.0",
        "description": "foo bar",
        "programmingLanguage": "python",
        "license": "MIT",
    }
    actual_meta = convert_from_origin_metadata_dict(
        {
            "id": ORIGIN.url,
            "metadata": metadata,
            "dropped-key": "foobar",
        },
        storage,
    )

    assert actual_meta == {
        "url": ORIGIN.url,
        "jsonld": metadata,
    }


def test_convert_journal_object(storage):
    """Simple test to assume good inputs are called properly."""
    assert convert_journal_object("origin", ORIGIN, storage) == ORIGIN
    assert convert_journal_object("unknown-object-type", ORIGIN, storage) is None


def test_fetch_last_revision_release_date(storage):
    for snapshot in SNAPSHOTS:
        assert fetch_last_revision_release_date(snapshot.id, storage) is not None
