# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from collections import defaultdict
import itertools
import re
from typing import Any, Dict, Iterable, Iterator, List, Optional

from swh.model.identifiers import origin_identifier
from swh.search.interface import PagedResult


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

    def origin_update(self, documents: Iterable[Dict]) -> None:
        for document in documents:
            document = document.copy()
            id_ = origin_identifier(document)
            if "url" in document:
                document["_url_tokens"] = set(self._url_splitter.split(document["url"]))
            self._origins[id_].update(document)
            if id_ not in self._origin_ids:
                self._origin_ids.append(id_)

    def origin_search(
        self,
        *,
        url_pattern: Optional[str] = None,
        metadata_pattern: Optional[str] = None,
        with_visit: bool = False,
        page_token: Optional[str] = None,
        limit: int = 50,
    ) -> PagedResult[Dict[str, Any]]:
        hits: Iterator[Dict[str, Any]] = (
            self._origins[id_] for id_ in self._origin_ids
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
            raise NotImplementedError(
                "Metadata search is not implemented in the in-memory backend."
            )

        if not url_pattern and not metadata_pattern:
            raise ValueError(
                "At least one of url_pattern and metadata_pattern must be provided."
            )

        next_page_token: Optional[str] = None

        if with_visit:
            hits = filter(lambda o: o.get("has_visits"), hits)

        start_at_index = int(page_token) if page_token else 0

        origins = [
            {"url": hit["url"]}
            for hit in itertools.islice(hits, start_at_index, start_at_index + limit)
        ]

        if len(origins) == limit:
            next_page_token = str(start_at_index + limit)

        assert len(origins) <= limit

        return PagedResult(results=origins, next_page_token=next_page_token,)
