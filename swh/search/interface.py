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

SORT_BY_OPTIONS = [
    "nb_visits",
    "last_visit_date",
    "last_eventful_visit_date",
    "last_revision_date",
    "last_release_date",
    "date_created",
    "date_modified",
    "date_published",
]


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
        """Searches for origins matching the `url_pattern`.

        Args:
            query: Find origins according the queries written as per the
                swh-search query language syntax.
            url_pattern: Part of the URL to search for
            metadata_pattern: Keywords to look for
            (across all the fields of intrinsic_metadata)
            with_visit: Whether origins with no visits are to be filtered out
            visit_types: Only origins having any of the provided visit types
                (e.g. git, svn, pypi) will be returned
            min_nb_visits: Filter origins that have number of visits >=
                the provided value
            min_last_visit_date: Filter origins that have
                last_visit_date on or after the provided date(ISO format)
            min_last_eventful_visit_date: Filter origins that have
                last_eventful_visit_date (eventful = snapshot_id changed)
                on or after the provided date(ISO format)
            min_last_revision_date: Filter origins that have
                last_revision_date on or after the provided date(ISO format)
            min_last_release_date: Filter origins that have
                last_release_date on or after the provided date(ISO format)
            min_date_created: Filter origins that have date_created
                from intrinsic_metadata on or after the provided date
            min_date_modified: Filter origins that have date_modified
                from intrinsic_metadata on or after the provided date
            min_date_published: Filter origins that have date_published
                from intrinsic_metadata on or after the provided date
            programming_languages: Filter origins with programming languages
                present in the given list (based on instrinsic_metadata)
            licenses: Filter origins with licenses present in the given list
                (based on instrinsic_metadata)
            keywords: Filter origins having description/keywords
                (extracted from instrinsic_metadata) that match given values
            sort_by: Sort results based on a list of fields mentioned in SORT_BY_OPTIONS
                (nb_visits,last_visit_date, last_eventful_visit_date,
                last_revision_date, last_release_date).
                Return results in descending order if "-" is present at the beginning
                otherwise in ascending order.
            page_token: Opaque value used for pagination
            limit: number of results to return

        Returns:
            PagedResult of origin dicts matching the search criteria. If next_page_token
            is None, there is no longer data to retrieve.

        """
        ...
