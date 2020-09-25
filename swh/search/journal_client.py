# Copyright (C) 2018-2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import logging

EXPECTED_MESSAGE_TYPES = {
    "origin",
    "origin_visit",
    "origin_intrinsic_metadata",
}


def process_journal_objects(messages, *, search):
    """Worker function for `JournalClient.process(worker_fn)`, after
    currification of `scheduler` and `task_names`."""
    assert set(messages) <= EXPECTED_MESSAGE_TYPES, set(messages)

    if "origin" in messages:
        process_origins(messages["origin"], search)

    if "origin_visit" in messages:
        process_origin_visits(messages["origin_visit"], search)

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
                "has_visits": True,
            }
            for visit in visits
        ]
    )


def process_origin_intrinsic_metadata(origin_metadata, search):
    logging.debug("processing origin intrinsic_metadata %r", origin_metadata)

    origin_metadata = [
        {"url": item["origin_url"], "intrinsic_metadata": item["metadata"],}
        for item in origin_metadata
    ]

    search.origin_update(origin_metadata)
