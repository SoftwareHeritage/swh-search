# Copyright (C) 2022  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

__all__ = ("SearchException", "SearchQuerySyntaxError")


class SearchException(Exception):
    """Base exception for errors specific to swh-search"""

    pass


class SearchQuerySyntaxError(SearchException):
    """Raised when the 'query' argument of origin_search cannot be parsed"""

    pass
