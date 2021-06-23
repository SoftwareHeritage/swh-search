# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from collections import defaultdict
from datetime import datetime, timezone
import re
from typing import Any, Dict, Iterable, Iterator, List, Optional

from swh.model.identifiers import origin_identifier
from swh.search.interface import (
    SORT_BY_OPTIONS,
    MinimalOriginDict,
    OriginDict,
    PagedResult,
)

_words_regexp = re.compile(r"\w+")


def _dict_words_set(d):
    """Recursively extract set of words from dict content."""
    values = set()

    def extract(obj, words):
        if isinstance(obj, dict):
            for k, v in obj.items():
                extract(v, words)
        elif isinstance(obj, list):
            for item in obj:
                extract(item, words)
        else:
            words.update(_words_regexp.findall(str(obj).lower()))
        return words

    return extract(d, values)


def _get_sorting_key(origin, field):
    """Get value of the field from an origin for sorting origins.

    Here field should be a member of SORT_BY_OPTIONS.
    If "-" is present at the start of field then invert the value
    in a way that it reverses the sorting order.
    """
    reversed = False
    if field[0] == "-":
        field = field[1:]
        reversed = True

    datetime_max = datetime.max.replace(tzinfo=timezone.utc)

    if field in ["nb_visits"]:  # unlike other options, nb_visits is of type integer
        if reversed:
            return -origin.get(field, 0)
        else:
            return origin.get(field, 0)

    elif field in SORT_BY_OPTIONS:
        if reversed:
            return datetime_max - datetime.fromisoformat(
                origin.get(field, "0001-01-01T00:00:00Z").replace("Z", "+00:00")
            )
        else:
            return datetime.fromisoformat(
                origin.get(field, "0001-01-01T00:00:00Z").replace("Z", "+00:00")
            )


class InMemorySearch:
    def __init__(self):
        pass

    def check(self):
        return True

    def deinitialize(self) -> None:
        if hasattr(self, "_origins"):
            del self._origins
            del self._origin_ids

    def initialize(self) -> None:
        self._origins: Dict[str, Dict[str, Any]] = defaultdict(dict)
        self._origin_ids: List[str] = []

    def flush(self) -> None:
        pass

    _url_splitter = re.compile(r"\W")

    def origin_update(self, documents: Iterable[OriginDict]) -> None:
        for source_document in documents:
            document: Dict[str, Any] = dict(source_document)
            id_ = origin_identifier(document)
            if "url" in document:
                document["_url_tokens"] = set(
                    self._url_splitter.split(source_document["url"])
                )
            if "visit_types" in document:
                document["visit_types"] = set(source_document["visit_types"])
                if "visit_types" in self._origins[id_]:
                    document["visit_types"].update(self._origins[id_]["visit_types"])
            if "nb_visits" in document:
                document["nb_visits"] = max(
                    document["nb_visits"], self._origins[id_].get("nb_visits", 0)
                )
            if "last_visit_date" in document:
                document["last_visit_date"] = max(
                    datetime.fromisoformat(document["last_visit_date"]),
                    datetime.fromisoformat(
                        self._origins[id_]
                        .get("last_visit_date", "0001-01-01T00:00:00.000000Z",)
                        .replace("Z", "+00:00")
                    ),
                ).isoformat()

            if "snapshot_id" in document and "last_eventful_visit_date" in document:
                incoming_date = datetime.fromisoformat(
                    document["last_eventful_visit_date"]
                )
                current_date = datetime.fromisoformat(
                    self._origins[id_]
                    .get("last_eventful_visit_date", "0001-01-01T00:00:00Z",)
                    .replace("Z", "+00:00")
                )
                incoming_snapshot_id = document["snapshot_id"]
                current_snapshot_id = self._origins[id_].get("snapshot_id", "")

                if (
                    incoming_snapshot_id == current_snapshot_id
                    or incoming_date < current_date
                ):
                    # update not required so override the incoming_values
                    document["snapshot_id"] = current_snapshot_id
                    document["last_eventful_visit_date"] = current_date.isoformat()

            if "last_revision_date" in document:
                document["last_revision_date"] = max(
                    datetime.fromisoformat(document["last_revision_date"]),
                    datetime.fromisoformat(
                        self._origins[id_]
                        .get("last_revision_date", "0001-01-01T00:00:00Z",)
                        .replace("Z", "+00:00")
                    ),
                ).isoformat()
            if "last_release_date" in document:
                document["last_release_date"] = max(
                    datetime.fromisoformat(document["last_release_date"]),
                    datetime.fromisoformat(
                        self._origins[id_]
                        .get("last_release_date", "0001-01-01T00:00:00Z",)
                        .replace("Z", "+00:00")
                    ),
                ).isoformat()
            self._origins[id_].update(document)

            if id_ not in self._origin_ids:
                self._origin_ids.append(id_)

    def origin_search(
        self,
        *,
        url_pattern: Optional[str] = None,
        metadata_pattern: Optional[str] = None,
        with_visit: bool = False,
        visit_types: Optional[List[str]] = None,
        page_token: Optional[str] = None,
        min_nb_visits: int = 0,
        min_last_visit_date: str = "",
        min_last_eventful_visit_date: str = "",
        min_last_revision_date: str = "",
        min_last_release_date: str = "",
        sort_by: List[str] = [],
        limit: int = 50,
    ) -> PagedResult[MinimalOriginDict]:
        hits: Iterator[Dict[str, Any]] = (
            self._origins[id_]
            for id_ in self._origin_ids
            if not self._origins[id_].get("blocklisted")
        )

        if url_pattern:
            tokens = set(self._url_splitter.split(url_pattern))

            def predicate(match):
                missing_tokens = tokens - match["_url_tokens"]
                if len(missing_tokens) == 0:
                    return True
                elif len(missing_tokens) > 1:
                    return False
                else:
                    # There is one missing token, look up by prefix.
                    (missing_token,) = missing_tokens
                    return any(
                        token.startswith(missing_token)
                        for token in match["_url_tokens"]
                    )

            hits = filter(predicate, hits)

        if metadata_pattern:
            metadata_pattern_words = set(
                _words_regexp.findall(metadata_pattern.lower())
            )

            def predicate(match):
                if "intrinsic_metadata" not in match:
                    return False

                return metadata_pattern_words.issubset(
                    _dict_words_set(match["intrinsic_metadata"])
                )

            hits = filter(predicate, hits)

        if not url_pattern and not metadata_pattern:
            raise ValueError(
                "At least one of url_pattern and metadata_pattern must be provided."
            )

        next_page_token: Optional[str] = None

        if with_visit:
            hits = filter(lambda o: o.get("has_visits"), hits)
        if min_nb_visits:
            hits = filter(lambda o: o.get("nb_visits", 0) >= min_nb_visits, hits)
        if min_last_visit_date:
            hits = filter(
                lambda o: datetime.fromisoformat(
                    o.get("last_visit_date", "0001-01-01T00:00:00Z").replace(
                        "Z", "+00:00"
                    )
                )
                >= datetime.fromisoformat(min_last_visit_date),
                hits,
            )

        if min_last_eventful_visit_date:
            hits = filter(
                lambda o: datetime.fromisoformat(
                    o.get("last_eventful_visit_date", "0001-01-01T00:00:00Z").replace(
                        "Z", "+00:00"
                    )
                )
                >= datetime.fromisoformat(min_last_eventful_visit_date),
                hits,
            )

        if min_last_revision_date:
            hits = filter(
                lambda o: datetime.fromisoformat(
                    o.get("last_revision_date", "0001-01-01T00:00:00Z").replace(
                        "Z", "+00:00"
                    )
                )
                >= datetime.fromisoformat(min_last_revision_date),
                hits,
            )
        if min_last_release_date:
            hits = filter(
                lambda o: datetime.fromisoformat(
                    o.get("last_release_date", "0001-01-01T00:00:00Z").replace(
                        "Z", "+00:00"
                    )
                )
                >= datetime.fromisoformat(min_last_release_date),
                hits,
            )

        if visit_types is not None:
            visit_types_set = set(visit_types)
            hits = filter(
                lambda o: visit_types_set.intersection(o.get("visit_types", set())),
                hits,
            )

        hits_list = sorted(
            hits, key=lambda o: tuple(_get_sorting_key(o, field) for field in sort_by),
        )

        start_at_index = int(page_token) if page_token else 0

        origins = [
            {"url": hit["url"]}
            for hit in hits_list[start_at_index : start_at_index + limit]
        ]

        if len(origins) == limit:
            next_page_token = str(start_at_index + limit)

        assert len(origins) <= limit

        return PagedResult(results=origins, next_page_token=next_page_token,)
