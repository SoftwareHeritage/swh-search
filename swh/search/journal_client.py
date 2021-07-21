# Copyright (C) 2018-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import logging

from swh.model.model import TargetType
from swh.storage.algos.snapshot import snapshot_get_all_branches

EXPECTED_MESSAGE_TYPES = {
    "origin",
    "origin_visit",
    "origin_visit_status",
    "origin_intrinsic_metadata",
}


def fetch_last_revision_release_date(snapshot_id, storage):
    if not snapshot_id:
        return {}

    branches = snapshot_get_all_branches(storage, snapshot_id).branches.values()

    tip_revision_ids = []
    tip_release_ids = []

    for branch in branches:
        if branch.target_type == TargetType.REVISION:
            tip_revision_ids.append(branch.target)
        elif branch.target_type == TargetType.RELEASE:
            tip_release_ids.append(branch.target)

    revision_datetimes = [
        revision.date.to_datetime()
        for revision in storage.revision_get(tip_revision_ids)
    ]

    release_datetimes = [
        release.date.to_datetime() for release in storage.release_get(tip_release_ids)
    ]

    return {
        "last_revision_date": max(revision_datetimes).isoformat(),
        "last_release_date": max(release_datetimes).isoformat(),
    }


def process_journal_objects(messages, *, search, storage=None):
    """Worker function for `JournalClient.process(worker_fn)`, after
    currification of `scheduler` and `task_names`."""
    assert set(messages) <= EXPECTED_MESSAGE_TYPES, set(messages)

    if "origin" in messages:
        process_origins(messages["origin"], search)

    if "origin_visit" in messages:
        process_origin_visits(messages["origin_visit"], search)

    if "origin_visit_status" in messages:
        process_origin_visit_statuses(messages["origin_visit_status"], search, storage)

    if "origin_intrinsic_metadata" in messages:
        process_origin_intrinsic_metadata(messages["origin_intrinsic_metadata"], search)


def process_origins(origins, search):
    logging.debug("processing origins %r", origins)

    search.origin_update(origins)


def process_origin_visits(visits, search):
    logging.debug("processing origin visits %r", visits)

    search.origin_update(
        [
            {
                "url": (
                    visit["origin"]
                    if isinstance(visit["origin"], str)
                    else visit["origin"]["url"]
                ),
                "visit_types": [visit["type"]],
            }
            for visit in visits
        ]
    )


def process_origin_visit_statuses(visit_statuses, search, storage):
    logging.debug("processing origin visit statuses %r", visit_statuses)

    full_visit_status = [
        {
            "url": visit_status["origin"],
            "has_visits": True,
            "nb_visits": visit_status["visit"],
            "snapshot_id": visit_status.get("snapshot"),
            "last_visit_date": visit_status["date"].isoformat(),
            "last_eventful_visit_date": visit_status["date"].isoformat(),
            **fetch_last_revision_release_date(visit_status.get("snapshot"), storage),
        }
        for visit_status in visit_statuses
        if visit_status["status"] == "full"
    ]

    if full_visit_status:
        search.origin_update(full_visit_status)


def process_origin_intrinsic_metadata(origin_metadata, search):
    logging.debug("processing origin intrinsic_metadata %r", origin_metadata)

    origin_metadata = [
        {"url": item["id"], "intrinsic_metadata": item["metadata"],}
        for item in origin_metadata
    ]

    search.origin_update(origin_metadata)
