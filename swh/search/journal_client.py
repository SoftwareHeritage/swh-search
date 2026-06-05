# Copyright (C) 2018-2026  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import logging
import sys
from typing import Callable, Dict, Optional

from swh.journal.client import JournalClientBase
from swh.model.model import SnapshotTargetType
from swh.search.interface import SearchInterface
from swh.storage.algos.snapshot import snapshot_get_all_branches
from swh.storage.interface import StorageInterface

EXPECTED_MESSAGE_TYPES = {
    "origin",
    "origin_visit_status",
    "origin_intrinsic_metadata",
    "origin_extrinsic_metadata",
}


def fetch_last_revision_release_date(
    snapshot_id: bytes, storage: StorageInterface
) -> Dict[str, str]:
    if "pytest" not in sys.modules:
        # FIXME: This function is too slow to be reasonably used in the journal-client
        # (at least the main one), we need to figure out a solution before this can
        # be enabled again.
        return {}

    if not snapshot_id:
        return {}

    snapshot = snapshot_get_all_branches(storage, snapshot_id)
    if not snapshot:
        return {}

    branches = snapshot.branches.values()

    tip_revision_ids = []
    tip_release_ids = []

    for branch in branches:
        if branch.target_type == SnapshotTargetType.REVISION:
            tip_revision_ids.append(branch.target)
        elif branch.target_type == SnapshotTargetType.RELEASE:
            tip_release_ids.append(branch.target)

    revision_datetimes = [
        revision.date.to_datetime()
        for revision in storage.revision_get(tip_revision_ids)
        if revision and revision.date
    ]

    release_datetimes = [
        release.date.to_datetime()
        for release in storage.release_get(tip_release_ids)
        if release and release.date
    ]

    ret = {}
    if revision_datetimes:
        ret["last_revision_date"] = max(revision_datetimes).isoformat()
    if release_datetimes:
        ret["last_release_date"] = max(release_datetimes).isoformat()

    return ret


def convert_origin(origin, storage: StorageInterface):
    logging.debug("Converting origins %r", origin)

    return origin


def _hexify(b: Optional[bytes]) -> Optional[str]:
    if b is None:
        return None
    return b.hex()


def convert_origin_visit_status(visit_status, storage: StorageInterface):
    logging.debug("Converting origin visit statuses %r", visit_status)

    visit_types = []
    visit_type = visit_status.get("type")
    if visit_type is None:
        visit = storage.origin_visit_get_by(
            origin=visit_status["origin"], visit=visit_status["visit"]
        )
        if visit is not None:
            visit_types.append(visit.type)
    else:
        visit_types.append(visit_type)

    processed_status = {
        "url": visit_status["origin"],
        "visit_types": visit_types,
    }
    if visit_status["status"] == "full":
        processed_status.update(
            {
                "has_visits": True,
                "nb_visits": visit_status["visit"],
                "snapshot_id": _hexify(visit_status.get("snapshot")),
                "last_visit_date": visit_status["date"].isoformat(),
                "last_eventful_visit_date": visit_status["date"].isoformat(),
                **fetch_last_revision_release_date(
                    visit_status.get("snapshot"), storage
                ),
            }
        )

    return processed_status


def convert_from_origin_metadata_dict(
    origin_dict: Dict, storage: StorageInterface
) -> Dict:
    logging.debug("Converting origin (intrinsic|extrinsic) metadata %r", origin_dict)
    return {
        "url": origin_dict["id"],
        "jsonld": origin_dict["metadata"],
    }


# A dictionary to ease the conversion of different objects into ready to be indexed
# object in elasticsearch
map_convert_fn: Dict[str, Callable] = {
    "origin": convert_origin,
    "origin_visit_status": convert_origin_visit_status,
    "origin_intrinsic_metadata": convert_from_origin_metadata_dict,
    "origin_extrinsic_metadata": convert_from_origin_metadata_dict,
}


def convert_journal_object(
    object_type: str, object_data: Dict, storage: StorageInterface
) -> Optional[Dict]:
    """Convert object_data of type object_type into a ready dict of data to be pushed to
    elasticsearch."""

    convert_fn: Callable[[Dict, StorageInterface], Dict] | None = map_convert_fn.get(
        object_type
    )
    if not convert_fn:
        return None

    return convert_fn(object_data, storage)


class SearchJournalClient(JournalClientBase):
    """Journal Client implementation"""

    object_types = EXPECTED_MESSAGE_TYPES

    def __init__(
        self, search: SearchInterface, storage: StorageInterface, *args, **kwargs
    ):
        super().__init__(*args, **kwargs)
        self.storage = storage
        self.search = search

    def process_one_object(self, decoded_object, decoded_object_type, raw_message):
        assert decoded_object_type in self.object_types

        convert_obj = convert_journal_object(
            decoded_object_type, decoded_object, self.storage
        )

        if convert_obj:
            self.search.origin_update([convert_obj])
