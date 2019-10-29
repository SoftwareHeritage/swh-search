# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
from collections import defaultdict
import itertools
import re
from typing import Iterable, Dict

import msgpack

from swh.core.api import remote_api_endpoint
from swh.model.identifiers import origin_identifier


def _sanitize_origin(origin):
    origin = origin.copy()
    res = {
        'url': origin.pop('url')
    }
    for field_name in ('type', 'intrinsic_metadata'):
        if field_name in origin:
            res[field_name] = origin.pop(field_name)
    return res


class InMemorySearch:
    def __init__(self):
        pass

    @remote_api_endpoint('check')
    def check(self):
        return True

    def deinitialize(self) -> None:
        if hasattr(self, '_origins'):
            del self._origins
            del self._origin_ids

    def initialize(self) -> None:
        self._origins = defaultdict(dict)
        self._origin_ids = []

    _url_splitter = re.compile(r'\W')

    @remote_api_endpoint('origin/update')
    def origin_update(self, documents: Iterable[dict]) -> None:
        for document in documents:
            document = document.copy()
            id_ = origin_identifier(document)
            if 'url' in document:
                document['_url_tokens'] = \
                    set(self._url_splitter.split(document['url']))
            self._origins[id_].update(document)
            if id_ not in self._origin_ids:
                self._origin_ids.append(id_)

    @remote_api_endpoint('origin/search')
    def origin_search(
            self, *,
            url_pattern: str = None, metadata_pattern: str = None,
            with_visit: bool = False,
            scroll_token: str = None, count: int = 50
            ) -> Dict[str, object]:
        matches = (self._origins[id_] for id_ in self._origin_ids)

        if url_pattern:
            tokens = set(self._url_splitter.split(url_pattern))

            def predicate(match):
                missing_tokens = tokens - match['_url_tokens']
                if len(missing_tokens) == 0:
                    return True
                elif len(missing_tokens) > 1:
                    return False
                else:
                    # There is one missing token, look up by prefix.
                    (missing_token,) = missing_tokens
                    return any(token.startswith(missing_token)
                               for token in match['_url_tokens'])

            matches = filter(predicate, matches)

        if metadata_pattern:
            raise NotImplementedError(
                'Metadata search is not implemented in the in-memory backend.')

        if not url_pattern and not metadata_pattern:
            raise ValueError(
                'At least one of url_pattern and metadata_pattern '
                'must be provided.')

        if with_visit:
            matches = filter(lambda o: o.get('has_visits'), matches)

        if scroll_token:
            scroll_token = msgpack.loads(base64.b64decode(scroll_token))
            start_at_index = scroll_token[b'start_at_index']
        else:
            start_at_index = 0

        hits = list(itertools.islice(
            matches, start_at_index, start_at_index+count))

        if len(hits) == count:
            next_scroll_token = {
                b'start_at_index': start_at_index+count,
            }
            next_scroll_token = base64.b64encode(msgpack.dumps(
                next_scroll_token))
        else:
            next_scroll_token = None

        return {
            'scroll_token': next_scroll_token,
            'results': [
                {'url': hit['url']}
                for hit in hits
            ]
        }
