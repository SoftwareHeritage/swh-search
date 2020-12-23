# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
from typing import Any, Dict, Iterable, Iterator, List, Optional

from elasticsearch import Elasticsearch
from elasticsearch.helpers import bulk, scan
import msgpack

from swh.indexer import codemeta
from swh.model import model
from swh.model.identifiers import origin_identifier
from swh.search.interface import PagedResult


def _sanitize_origin(origin):
    origin = origin.copy()

    # Whitelist fields to be saved in Elasticsearch
    res = {"url": origin.pop("url")}
    for field_name in ("intrinsic_metadata", "has_visits"):
        if field_name in origin:
            res[field_name] = origin.pop(field_name)

    # Run the JSON-LD expansion algorithm
    # <https://www.w3.org/TR/json-ld-api/#expansion>
    # to normalize the Codemeta metadata.
    # This is required as Elasticsearch will needs each field to have a consistent
    # type across documents to be searchable; and non-expanded JSON-LD documents
    # can have various types in the same field. For example, all these are
    # equivalent in JSON-LD:
    # * {"author": "Jane Doe"}
    # * {"author": ["Jane Doe"]}
    # * {"author": {"@value": "Jane Doe"}}
    # * {"author": [{"@value": "Jane Doe"}]}
    # and JSON-LD expansion will convert them all to the last one.
    if "intrinsic_metadata" in res:
        res["intrinsic_metadata"] = codemeta.expand(res["intrinsic_metadata"])

    return res


def token_encode(index_to_tokenize: Dict[bytes, Any]) -> str:
    """Tokenize as string an index page result from a search

    """
    page_token = base64.b64encode(msgpack.dumps(index_to_tokenize))
    return page_token.decode()


def token_decode(page_token: str) -> Dict[bytes, Any]:
    """Read the page_token

    """
    return msgpack.loads(base64.b64decode(page_token.encode()), raw=True)


class ElasticSearch:
    def __init__(self, hosts: List[str], index_prefix=None):
        self._backend = Elasticsearch(hosts=hosts)
        self.index_prefix = index_prefix

        self.origin_index = "origin"

        if index_prefix:
            self.origin_index = index_prefix + "_" + self.origin_index

    def check(self):
        return self._backend.ping()

    def deinitialize(self) -> None:
        """Removes all indices from the Elasticsearch backend"""
        self._backend.indices.delete(index="*")

    def initialize(self) -> None:
        """Declare Elasticsearch indices and mappings"""
        if not self._backend.indices.exists(index=self.origin_index):
            self._backend.indices.create(index=self.origin_index)
        self._backend.indices.put_mapping(
            index=self.origin_index,
            body={
                "properties": {
                    # sha1 of the URL; used as the document id
                    "sha1": {"type": "keyword", "doc_values": True,},
                    # Used both to search URLs, and as the result to return
                    # as a response to queries
                    "url": {
                        "type": "text",
                        # To split URLs into token on any character
                        # that is not alphanumerical
                        "analyzer": "simple",
                        # 2-gram and partial-3-gram search (ie. with the end of the
                        # third word potentially missing)
                        "fields": {
                            "as_you_type": {
                                "type": "search_as_you_type",
                                "analyzer": "simple",
                            }
                        },
                    },
                    # used to filter out origins that were never visited
                    "has_visits": {"type": "boolean",},
                    "intrinsic_metadata": {
                        "type": "nested",
                        "properties": {
                            "@context": {
                                # don't bother indexing tokens in these URIs, as the
                                # are used as namespaces
                                "type": "keyword",
                            }
                        },
                    },
                }
            },
        )

    def flush(self) -> None:
        self._backend.indices.refresh(index=self.origin_index)

    def origin_update(self, documents: Iterable[Dict]) -> None:
        documents = map(_sanitize_origin, documents)
        documents_with_sha1 = (
            (origin_identifier(document), document) for document in documents
        )
        actions = [
            {
                "_op_type": "update",
                "_id": sha1,
                "_index": self.origin_index,
                "doc": {**document, "sha1": sha1,},
                "doc_as_upsert": True,
            }
            for (sha1, document) in documents_with_sha1
        ]
        bulk(self._backend, actions, index=self.origin_index)

    def origin_dump(self) -> Iterator[model.Origin]:
        results = scan(self._backend, index=self.origin_index)
        for hit in results:
            yield self._backend.termvectors(
                index=self.origin_index, id=hit["_id"], fields=["*"]
            )

    def origin_search(
        self,
        *,
        url_pattern: Optional[str] = None,
        metadata_pattern: Optional[str] = None,
        with_visit: bool = False,
        page_token: Optional[str] = None,
        limit: int = 50,
    ) -> PagedResult[Dict[str, Any]]:
        query_clauses: List[Dict[str, Any]] = []

        if url_pattern:
            query_clauses.append(
                {
                    "multi_match": {
                        "query": url_pattern,
                        "type": "bool_prefix",
                        "operator": "and",
                        "fields": [
                            "url.as_you_type",
                            "url.as_you_type._2gram",
                            "url.as_you_type._3gram",
                        ],
                    }
                }
            )

        if metadata_pattern:
            query_clauses.append(
                {
                    "nested": {
                        "path": "intrinsic_metadata",
                        "query": {
                            "multi_match": {
                                "query": metadata_pattern,
                                # Makes it so that the "foo bar" query returns
                                # documents which contain "foo" in a field and "bar"
                                # in a different field
                                "type": "cross_fields",
                                # All keywords must be found in a document for it to
                                # be considered a match.
                                # TODO: allow missing keywords?
                                "operator": "and",
                                # Searches on all fields of the intrinsic_metadata dict,
                                # recursively.
                                "fields": ["intrinsic_metadata.*"],
                            }
                        },
                    }
                }
            )

        if not query_clauses:
            raise ValueError(
                "At least one of url_pattern and metadata_pattern must be provided."
            )

        if with_visit:
            query_clauses.append({"term": {"has_visits": True,}})

        body = {
            "query": {"bool": {"must": query_clauses,}},
            "sort": [{"_score": "desc"}, {"sha1": "asc"},],
        }
        if page_token:
            # TODO: use ElasticSearch's scroll API?
            page_token_content = token_decode(page_token)
            body["search_after"] = [
                page_token_content[b"score"],
                page_token_content[b"sha1"].decode("ascii"),
            ]

        res = self._backend.search(index=self.origin_index, body=body, size=limit)

        hits = res["hits"]["hits"]

        next_page_token: Optional[str] = None

        if len(hits) == limit:
            # There are more results after this page; return a pagination token
            # to get them in a future query
            last_hit = hits[-1]
            next_page_token_content = {
                b"score": last_hit["_score"],
                b"sha1": last_hit["_source"]["sha1"],
            }
            next_page_token = token_encode(next_page_token_content)

        assert len(hits) <= limit

        return PagedResult(
            results=[{"url": hit["_source"]["url"]} for hit in hits],
            next_page_token=next_page_token,
        )
