# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
from typing import Any, Iterable, Dict, List, Iterator, Optional

from elasticsearch import Elasticsearch
from elasticsearch.helpers import bulk, scan
import msgpack

from swh.core.api import remote_api_endpoint
from swh.model import model
from swh.model.identifiers import origin_identifier


def _sanitize_origin(origin):
    origin = origin.copy()
    res = {
        'url': origin.pop('url')
    }
    for field_name in ('intrinsic_metadata', 'has_visits'):
        if field_name in origin:
            res[field_name] = origin.pop(field_name)
    return res


class ElasticSearch:
    def __init__(self, hosts: List[str]):
        self._backend = Elasticsearch(hosts=hosts)

    @remote_api_endpoint('check')
    def check(self):
        return self._backend.ping()

    def deinitialize(self) -> None:
        """Removes all indices from the Elasticsearch backend"""
        self._backend.indices.delete(index='*')

    def initialize(self) -> None:
        """Declare Elasticsearch indices and mappings"""
        if not self._backend.indices.exists(index='origin'):
            self._backend.indices.create(index='origin')
        self._backend.indices.put_mapping(
            index='origin',
            body={
                'properties': {
                    'sha1': {
                        'type': 'keyword',
                        'doc_values': True,
                    },
                    'url': {
                        'type': 'text',
                        # To split URLs into token on any character
                        # that is not alphanumerical
                        'analyzer': 'simple',
                        'fields': {
                            'as_you_type': {
                                'type': 'search_as_you_type',
                                'analyzer': 'simple',
                            }
                        }
                    },
                    'has_visits': {
                        'type': 'boolean',
                    },
                    'intrinsic_metadata': {
                        'type': 'nested',
                        'properties': {
                            '@context': {
                                # don't bother indexing tokens
                                'type': 'keyword',
                            }
                        },
                    },
                }
            }
        )

    @remote_api_endpoint('flush')
    def flush(self) -> None:
        """Blocks until all previous calls to _update() are completely
        applied."""
        self._backend.indices.refresh(index='_all')

    @remote_api_endpoint('origin/update')
    def origin_update(self, documents: Iterable[dict]) -> None:
        documents = map(_sanitize_origin, documents)
        documents_with_sha1 = ((origin_identifier(document), document)
                               for document in documents)
        actions = [
            {
                '_op_type': 'update',
                '_id': sha1,
                '_index': 'origin',
                'doc': {
                    **document,
                    'sha1': sha1,
                },
                'doc_as_upsert': True,
            }
            for (sha1, document) in documents_with_sha1
        ]
        bulk(self._backend, actions, index='origin')

    def origin_dump(self) -> Iterator[model.Origin]:
        """Returns all content in Elasticsearch's index. Not exposed
        publicly; but useful for tests."""
        results = scan(self._backend, index='*')
        for hit in results:
            yield self._backend.termvectors(
                index='origin', id=hit['_id'],
                fields=['*'])

    @remote_api_endpoint('origin/search')
    def origin_search(
            self, *,
            url_pattern: str = None, metadata_pattern: str = None,
            with_visit: bool = False,
            page_token: str = None, count: int = 50
            ) -> Dict[str, object]:
        """Searches for origins matching the `url_pattern`.

        Args:
            url_pattern (str): Part of thr URL to search for
            with_visit (bool): Whether origins with no visit are to be
                               filtered out
            page_token (str): Opaque value used for pagination.
            count (int): number of results to return.

        Returns:
            a dictionary with keys:
            * `next_page_token`:
              opaque value used for fetching more results. `None` if there
              are no more result.
            * `results`:
              list of dictionaries with key:
              * `url`: URL of a matching origin
        """
        query_clauses = []  # type: List[Dict[str, Any]]

        if url_pattern:
            query_clauses.append({
                'multi_match': {
                    'query': url_pattern,
                    'type': 'bool_prefix',
                    'operator': 'and',
                    'fields': [
                        'url.as_you_type',
                        'url.as_you_type._2gram',
                        'url.as_you_type._3gram',
                    ]
                }
            })

        if metadata_pattern:
            query_clauses.append({
                'nested': {
                    'path': 'intrinsic_metadata',
                    'query': {
                        'multi_match': {
                            'query': metadata_pattern,
                            'operator': 'and',
                            'fields': ['intrinsic_metadata.*']
                        }
                    },
                }
            })

        if not query_clauses:
            raise ValueError(
                'At least one of url_pattern and metadata_pattern '
                'must be provided.')

        if with_visit:
            query_clauses.append({
                'term': {
                    'has_visits': True,
                }
            })

        body = {
            'query': {
                'bool': {
                    'must': query_clauses,
                }
            },
            'size': count,
            'sort': [
                {'_score': 'desc'},
                {'sha1': 'asc'},
            ]
        }
        if page_token:
            # TODO: use ElasticSearch's scroll API?
            page_token_content = msgpack.loads(
                base64.b64decode(page_token))
            body['search_after'] = \
                [page_token_content[b'score'],
                 page_token_content[b'sha1'].decode('ascii')]

        res = self._backend.search(
            index='origin',
            body=body,
            size=count,
        )

        hits = res['hits']['hits']

        if len(hits) == count:
            last_hit = hits[-1]
            next_page_token_content = {
                b'score': last_hit['_score'],
                b'sha1': last_hit['_source']['sha1'],
            }
            next_page_token = base64.b64encode(msgpack.dumps(
                next_page_token_content))  # type: Optional[bytes]
        else:
            next_page_token = None

        return {
            'next_page_token': next_page_token,
            'results': [
                {
                    # TODO: also add 'id'?
                    'url': hit['_source']['url'],
                }
                for hit in hits
            ]
        }
