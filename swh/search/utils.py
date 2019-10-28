# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information


def stream_results(f, *args, **kwargs):
    if 'scroll_token' in kwargs:
        raise TypeError('stream_results has no argument "scroll_token".')
    scroll_token = None
    while True:
        results = f(*args, scroll_token=scroll_token, **kwargs)
        yield from results['results']
        scroll_token = results['scroll_token']
        if scroll_token is None:
            break
