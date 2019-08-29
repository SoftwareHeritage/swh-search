# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
from typing import Iterable, Dict, List, Iterator

from elasticsearch import Elasticsearch
from elasticsearch.client import IndicesClient
from elasticsearch.helpers import bulk, scan
import msgpack

from swh.model import model
from swh.model.identifiers import origin_identifier


class ElasticSearch:
    def __init__(self, hosts: List[str]):
        self._backend = Elasticsearch(hosts=hosts)

    def check(self):
        self._backend.ping()

    def initialize(self) -> None:
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
                            'analyzer': 'simple',
                            'fields': {
                                'as_you_type': {
                                    'type': 'search_as_you_type',
                                    'analyzer': 'simple',
                                }
                            }
                        }
                    }
                }
            }
        )

    def origin_add(self, origins: Iterable[model.Origin]) -> None:
        origins = (origin.to_dict() for origin in origins)
        '''
        for origin in origins:
            self._backend.index(
                index='origin',
                id=origin_identifier(origin),
                body=origin,
            )
        self._backend.indices.refresh(index='origin')
        '''
        actions = [
            {
                '_id': origin_identifier(origin),
                '_index': 'origin',
                '_source': origin,
            }
            for origin in origins
        ]
        res = bulk(self._backend, actions, index='origin', refresh='wait_for')

    def origin_dump(self) -> Iterator[model.Origin]:
        results = list(scan(self._backend, index='*'))
        for hit in results:
            yield self._backend.termvectors(
                index='origin', id=hit['_id'],
                fields=['url', 'url.as_you_type', 'url.as_you_type._2gram'
                        'url.as_you_type._3gram', 'url._2gram', 'url._3gram'])

    def origin_search(
            self, url_substring: str, cursor: str = None, count: int = 50
            ) -> Dict[str, object]:
        """Searches for origins matching the `url_substring`.

        Args:
            url_substring (str): Part of thr URL to search for
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
        body = {
            'query': {
                'multi_match': {
                    'query': url_substring,
                    'type': 'bool_prefix',
                    'fields': [
                        'url.as_you_type',
                        'url.as_you_type._2gram',
                        'url.as_you_type._3gram',
                    ]
                }
            },
            'size': count,
            'sort': [
                {'_score': 'desc'},
                {'url': 'asc'},
            ]
        }
        if cursor:
            cursor = msgpack.decode(base64.b64decode(cursor))
            body['search_after'] = [cursor['_score'], cursor['url']]

        res = self._backend.search(
            index='origin',
            body=body,
            size=count,
        )

        hits = res['hits']['hits']

        if len(hits) == count:
            last_hit = hits[-1]
            next_cursor = {
                'score': last_hit['_score'],
                'url': last_hit['_source']['url'],
            }
            next_cursor = base64.b64encode(msgpack.dumps(next_cursor))
        else:
            next_cursor = None

        return {
            'cursor': next_cursor,
            'results': [
                {'url': hit['_source']['url'] for hit in hits}
            ]
        }
