# Copyright (C) 2020-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from typing import Iterable, List, Optional, TypeVar

from typing_extensions import TypedDict

from swh.core.api import remote_api_endpoint
from swh.core.api.classes import PagedResult as CorePagedResult

TResult = TypeVar("TResult")
PagedResult = CorePagedResult[TResult, str]


class MinimalOriginDict(TypedDict):
    """Mandatory keys of an :class:`OriginDict`"""

    url: str


class OriginDict(MinimalOriginDict, total=False):
    """Argument passed to :meth:`SearchInterface.origin_update`."""

    visit_types: List[str]
    has_visits: bool


class SearchInterface:
    @remote_api_endpoint("check")
    def check(self):
        """Dedicated method to execute some specific check per implementation.

        """
        ...

    @remote_api_endpoint("flush")
    def flush(self) -> None:
        """Blocks until all previous calls to _update() are completely
        applied.

        """
        ...

    @remote_api_endpoint("origin/update")
    def origin_update(self, documents: Iterable[OriginDict]) -> None:
        """Persist documents to the search backend.

        """
        ...

    @remote_api_endpoint("origin/search")
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
        limit: int = 50,
    ) -> PagedResult[MinimalOriginDict]:
        """Searches for origins matching the `url_pattern`.

        Args:
            url_pattern: Part of the URL to search for
            with_visit: Whether origins with no visit are to be
              filtered out
            visit_types: Only origins having any of the provided visit types
                (e.g. git, svn, pypi) will be returned
            page_token: Opaque value used for pagination
            min_nb_visits: Filter origins that have number of visits >=
                the provided value
            min_last_visit_date: Filter origins that have
                last_visit_date on or after the provided date(ISO format)
            min_last_eventful_visit_date: Filter origins that have
                last_eventful_visit_date (eventful = snapshot_id changed)
                on or after the provided date(ISO format)
            limit: number of results to return

        Returns:
            PagedResult of origin dicts matching the search criteria. If next_page_token
            is None, there is no longer data to retrieve.

        """
        ...
