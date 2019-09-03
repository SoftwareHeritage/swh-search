# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

def stream_results(f, *args, **kwargs):
    if 'cursor' in kwargs:
        raise ArgumentError('stream_results has no argument "cursor".')
    cursor = None
    while True:
        results = f(*args, cursor=cursor, **kwargs)
        yield from results['results']
        cursor = results['cursor']
        if cursor is None:
            break
