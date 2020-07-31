# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information


def stream_results(f, *args, **kwargs):
    """Consume the paginated result and stream the page results

    """
    if "page_token" in kwargs:
        raise TypeError('stream_results has no argument "page_token".')
    page_token = None
    while True:
        page_result = f(*args, page_token=page_token, **kwargs)
        yield from page_result.results
        page_token = page_result.next_page_token
        if page_token is None:
            break
