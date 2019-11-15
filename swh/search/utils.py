# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information


def stream_results(f, *args, **kwargs):
    if 'page_token' in kwargs:
        raise TypeError('stream_results has no argument "page_token".')
    page_token = None
    while True:
        results = f(*args, page_token=page_token, **kwargs)
        yield from results['results']
        page_token = results['next_page_token']
        if page_token is None:
            break
