# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from collections import defaultdict
from datetime import datetime, timezone
import re
from typing import Any, Dict, Iterable, Iterator, List, Optional

from swh.indexer import codemeta
from swh.model.identifiers import origin_identifier
from swh.search.interface import (
    SORT_BY_OPTIONS,
    MinimalOriginDict,
    OriginDict,
    PagedResult,
)
from swh.search.utils import get_expansion, is_date_parsable

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


def _nested_get(nested_dict, nested_keys, default=""):
    """Extracts values from deeply nested dictionary nested_dict
    using the nested_keys and returns a list of all of the values
    discovered in the process.


    >>> nested_dict = [
    ... {"name": [{"@value": {"first": "f1", "last": "l1"}}], "address": "XYZ"},
    ... {"name": [{"@value": {"first": "f2", "last": "l2"}}], "address": "ABC"},
    ... ]
    >>> _nested_get(nested_dict, ["name", "@value", "last"])
    ['l1', 'l2']
    >>> _nested_get(nested_dict, ["address"])
    ['XYZ', 'ABC']

    It doesn't allow fetching intermediate values and returns "" for such cases
    >>> _nested_get(nested_dict, ["name", "@value"])
    ['', '']
    """

    def _nested_get_recursive(nested_dict, nested_keys):
        try:
            curr_obj = nested_dict
            type_curr_obj = type(curr_obj)
            for i, key in enumerate(nested_keys):
                if key in curr_obj:
                    curr_obj = curr_obj[key]
                    type_curr_obj = type(curr_obj)
                else:
                    if type_curr_obj == list:
                        curr_obj = [
                            _nested_get_recursive(obj, nested_keys[i:])
                            for obj in curr_obj
                        ]
                    # If value isn't a list or string or integer
                    elif type_curr_obj != str and type_curr_obj != int:
                        return default

            # If only one element is present in the list, take it out
            # This ensures a flat array every time
            if type_curr_obj == list and len(curr_obj) == 1:
                curr_obj = curr_obj[0]

            return curr_obj
        except Exception:
            return default

    res = _nested_get_recursive(nested_dict, nested_keys)
    if type(res) != list:
        return [res]

    return res


def _tokenize(x):
    return x.lower().replace(",", " ").split()


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

    DATETIME_OBJ_MAX = datetime.max.replace(tzinfo=timezone.utc)
    DATETIME_MIN = "0001-01-01T00:00:00Z"

    DATE_OBJ_MAX = datetime.max
    DATE_MIN = "0001-01-01"

    if field == "score":
        if reversed:
            return -origin.get(field, 0)
        else:
            return origin.get(field, 0)

    if field in ["date_created", "date_modified", "date_published"]:
        date = datetime.strptime(
            _nested_get(origin, get_expansion(field), DATE_MIN)[0], "%Y-%m-%d"
        )
        if reversed:
            return DATE_OBJ_MAX - date
        else:
            return date

    elif field in ["nb_visits"]:  # unlike other options, nb_visits is of type integer
        if reversed:
            return -origin.get(field, 0)
        else:
            return origin.get(field, 0)

    elif field in SORT_BY_OPTIONS:
        date = datetime.fromisoformat(
            origin.get(field, DATETIME_MIN).replace("Z", "+00:00")
        )
        if reversed:
            return DATETIME_OBJ_MAX - date
        else:
            return date


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
            if "intrinsic_metadata" in document:
                intrinsic_metadata = document["intrinsic_metadata"]

                for date_field in ["dateCreated", "dateModified", "datePublished"]:
                    if date_field in intrinsic_metadata:
                        date = intrinsic_metadata[date_field]

                        # If date{Created,Modified,Published} value isn't parsable
                        # It gets rejected and isn't stored (unlike other fields)
                        if not is_date_parsable(date):
                            intrinsic_metadata.pop(date_field)

                document["intrinsic_metadata"] = codemeta.expand(intrinsic_metadata)

                if len(document["intrinsic_metadata"]) != 1:
                    continue

                metadata = document["intrinsic_metadata"][0]
                if "http://schema.org/license" in metadata:
                    metadata["http://schema.org/license"] = [
                        {"@id": license["@id"].lower()}
                        for license in metadata["http://schema.org/license"]
                    ]
                if "http://schema.org/programmingLanguage" in metadata:
                    metadata["http://schema.org/programmingLanguage"] = [
                        {"@value": license["@value"].lower()}
                        for license in metadata["http://schema.org/programmingLanguage"]
                    ]

            self._origins[id_].update(document)

            if id_ not in self._origin_ids:
                self._origin_ids.append(id_)

    def origin_search(
        self,
        *,
        query: str = "",
        url_pattern: Optional[str] = None,
        metadata_pattern: Optional[str] = None,
        with_visit: bool = False,
        visit_types: Optional[List[str]] = None,
        min_nb_visits: int = 0,
        min_last_visit_date: str = "",
        min_last_eventful_visit_date: str = "",
        min_last_revision_date: str = "",
        min_last_release_date: str = "",
        min_date_created: str = "",
        min_date_modified: str = "",
        min_date_published: str = "",
        programming_languages: Optional[List[str]] = None,
        licenses: Optional[List[str]] = None,
        keywords: Optional[List[str]] = None,
        sort_by: Optional[List[str]] = None,
        page_token: Optional[str] = None,
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

        if min_date_created:
            min_date_created_obj = datetime.strptime(min_date_created, "%Y-%m-%d")
            hits = filter(
                lambda o: datetime.strptime(
                    _nested_get(o, get_expansion("date_created"))[0], "%Y-%m-%d"
                )
                >= min_date_created_obj,
                hits,
            )
        if min_date_modified:
            min_date_modified_obj = datetime.strptime(min_date_modified, "%Y-%m-%d")
            hits = filter(
                lambda o: datetime.strptime(
                    _nested_get(o, get_expansion("date_modified"))[0], "%Y-%m-%d"
                )
                >= min_date_modified_obj,
                hits,
            )
        if min_date_published:
            min_date_published_obj = datetime.strptime(min_date_published, "%Y-%m-%d")
            hits = filter(
                lambda o: datetime.strptime(
                    _nested_get(o, get_expansion("date_published"))[0], "%Y-%m-%d"
                )
                >= min_date_published_obj,
                hits,
            )

        if licenses:
            queried_licenses = [license_keyword.lower() for license_keyword in licenses]
            hits = filter(
                lambda o: any(
                    # If any of the queried licenses are found, include the origin
                    any(
                        # returns True if queried_license_keyword is found
                        # in any of the licenses of the origin
                        queried_license_keyword in origin_license
                        for origin_license in _nested_get(o, get_expansion("licenses"))
                    )
                    for queried_license_keyword in queried_licenses
                ),
                hits,
            )
        if programming_languages:
            queried_programming_languages = [
                lang_keyword.lower() for lang_keyword in programming_languages
            ]
            hits = filter(
                lambda o: any(
                    # If any of the queried languages are found, include the origin
                    any(
                        # returns True if queried_lang_keyword is found
                        # in any of the langs of the origin
                        queried_lang_keyword in origin_lang
                        for origin_lang in _nested_get(
                            o, get_expansion("programming_languages")
                        )
                    )
                    for queried_lang_keyword in queried_programming_languages
                ),
                hits,
            )
        if keywords:

            if sort_by:
                sort_by.append("-score")
            else:
                sort_by = ["-score"]

            from copy import deepcopy

            hits_list = deepcopy(list(hits))

            for origin in hits_list:
                origin_keywords = [
                    _tokenize(keyword)
                    for keyword in _nested_get(origin, get_expansion("keywords"))
                ]
                origin_descriptions = [
                    _tokenize(description)
                    for description in _nested_get(
                        origin, get_expansion("descriptions")
                    )
                ]

                for q_keyword in keywords:
                    for origin_keyword_tokens in origin_keywords:
                        if q_keyword in origin_keyword_tokens:
                            origin["score"] = origin.get("score", 0) + 2
                    for origin_description_token in origin_descriptions:
                        if q_keyword in origin_description_token:
                            origin["score"] = origin.get("score", 0) + 1

            hits = (origin for origin in hits_list if origin.get("score", 0) > 0)

        if visit_types is not None:
            visit_types_set = set(visit_types)
            hits = filter(
                lambda o: visit_types_set.intersection(o.get("visit_types", set())),
                hits,
            )

        hits_list = list(hits)
        if sort_by:
            sort_by_list = list(sort_by)
            hits_list.sort(
                key=lambda o: tuple(
                    _get_sorting_key(o, field) for field in sort_by_list
                )
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
