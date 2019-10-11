# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
from typing import Iterable, Dict, List, Iterator

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
    for field_name in ('intrinsic_metadata',):
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
        self._backend.indices.create(
            index='origin',
            body={
                'mappings': {
                    'properties': {
                        'url': {
                            'type': 'text',
                            # TODO: consider removing fielddata when
                            # swh-storage allows querying by hash, so the
                            # full URL does not have to be stored in ES'
                            # memory. See:
                            # https://www.elastic.co/guide/en/elasticsearch/reference/current/fielddata.html#before-enabling-fielddata
                            'fielddata': True,
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
            }
        )

    @remote_api_endpoint('origin/update')
    def origin_update(self, documents: Iterable[dict]) -> None:
        documents = map(_sanitize_origin, documents)
        actions = [
            {
                '_op_type': 'update',
                '_id': origin_identifier(document),
                '_index': 'origin',
                'doc': document,
                'doc_as_upsert': True,
            }
            for document in documents
        ]
        bulk(self._backend, actions, index='origin', refresh='wait_for')

    def origin_dump(self) -> Iterator[model.Origin]:
        """Returns all content in Elasticsearch's index. Not exposed
        publicly; but useful for tests."""
        results = list(scan(self._backend, index='*'))
        for hit in results:
            yield self._backend.termvectors(
                index='origin', id=hit['_id'],
                fields=['*'])

    @remote_api_endpoint('origin/search')
    def origin_search(
            self, *,
            url_pattern: str = None, metadata_pattern: str = None,
            cursor: str = None, count: int = 50
            ) -> Dict[str, object]:
        """Searches for origins matching the `url_pattern`.

        Args:
            url_pattern (str): Part of thr URL to search for
            cursor (str): `cursor` is opaque value used for pagination.
            count (int): number of results to return.

        Returns:
            a dictionary with keys:
            * `cursor`:
              opaque value used for fetching more results. `None` if there
              are no more result.
            * `results`:
              list of dictionaries with key:
              * `url`: URL of a matching origin
        """
        query_clauses = []

        if url_pattern:
            query_clauses.append({
                'multi_match': {
                    'query': url_pattern,
                    'type': 'bool_prefix',
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
                            'fields': ['intrinsic_metadata.*']
                        }
                    },
                }
            })

        if not query_clauses:
            raise ValueError(
                'At least one of url_pattern and metadata_pattern '
                'must be provided.')

        body = {
            'query': {
                'bool': {
                    'should': query_clauses,
                }
            },
            'size': count,
            'sort': [
                {'_score': 'desc'},
                {'_id': 'asc'},
            ]
        }
        if cursor:
            cursor = msgpack.loads(base64.b64decode(cursor))
            body['search_after'] = \
                [cursor[b'score'], cursor[b'id'].decode('ascii')]

        res = self._backend.search(
            index='origin',
            body=body,
            size=count,
        )

        hits = res['hits']['hits']

        if len(hits) == count:
            last_hit = hits[-1]
            next_cursor = {
                b'score': last_hit['_score'],
                b'id': last_hit['_id'],
            }
            next_cursor = base64.b64encode(msgpack.dumps(next_cursor))
        else:
            next_cursor = None

        return {
            'cursor': next_cursor,
            'results': [
                {'url': hit['_source']['url']}
                for hit in hits
            ]
        }
