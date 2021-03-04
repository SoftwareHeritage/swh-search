# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
from typing import Any, Dict, Iterable, Iterator, List, Optional

from elasticsearch import Elasticsearch, helpers
import msgpack

from swh.indexer import codemeta
from swh.model import model
from swh.model.identifiers import origin_identifier
from swh.search.interface import MinimalOriginDict, OriginDict, PagedResult
from swh.search.metrics import send_metric, timed

INDEX_NAME_PARAM = "index"
READ_ALIAS_PARAM = "read_alias"
WRITE_ALIAS_PARAM = "write_alias"

ORIGIN_DEFAULT_CONFIG = {
    INDEX_NAME_PARAM: "origin",
    READ_ALIAS_PARAM: "origin-read",
    WRITE_ALIAS_PARAM: "origin-write",
}


def _sanitize_origin(origin):
    origin = origin.copy()

    # Whitelist fields to be saved in Elasticsearch
    res = {"url": origin.pop("url")}
    for field_name in ("intrinsic_metadata", "has_visits", "visit_types"):
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
    def __init__(self, hosts: List[str], indexes: Dict[str, Dict[str, str]] = {}):
        self._backend = Elasticsearch(hosts=hosts)

        # Merge current configuration with default values
        origin_config = indexes.get("origin", {})
        self.origin_config = {**ORIGIN_DEFAULT_CONFIG, **origin_config}

    def _get_origin_index(self) -> str:
        return self.origin_config[INDEX_NAME_PARAM]

    def _get_origin_read_alias(self) -> str:
        return self.origin_config[READ_ALIAS_PARAM]

    def _get_origin_write_alias(self) -> str:
        return self.origin_config[WRITE_ALIAS_PARAM]

    @timed
    def check(self):
        return self._backend.ping()

    def deinitialize(self) -> None:
        """Removes all indices from the Elasticsearch backend"""
        self._backend.indices.delete(index="*")

    def initialize(self) -> None:
        """Declare Elasticsearch indices, aliases and mappings"""

        if not self._backend.indices.exists(index=self._get_origin_index()):
            self._backend.indices.create(index=self._get_origin_index())

        if not self._backend.indices.exists_alias(self._get_origin_read_alias()):
            self._backend.indices.put_alias(
                index=self._get_origin_index(), name=self._get_origin_read_alias()
            )

        if not self._backend.indices.exists_alias(self._get_origin_write_alias()):
            self._backend.indices.put_alias(
                index=self._get_origin_index(), name=self._get_origin_write_alias()
            )

        self._backend.indices.put_mapping(
            index=self._get_origin_index(),
            body={
                "date_detection": False,
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
                    "visit_types": {"type": "keyword"},
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
                },
            },
        )

    @timed
    def flush(self) -> None:
        self._backend.indices.refresh(index=self._get_origin_write_alias())

    @timed
    def origin_update(self, documents: Iterable[OriginDict]) -> None:
        write_index = self._get_origin_write_alias()
        documents = map(_sanitize_origin, documents)
        documents_with_sha1 = (
            (origin_identifier(document), document) for document in documents
        )
        # painless script that will be executed when updating an origin document
        update_script = """
        // backup current visit_types field value
        List visit_types = ctx._source.getOrDefault("visit_types", []);

        // update origin document with new field values
        ctx._source.putAll(params);

        // restore previous visit types after visit_types field overriding
        if (ctx._source.containsKey("visit_types")) {
            for (int i = 0; i < visit_types.length; ++i) {
                if (!ctx._source.visit_types.contains(visit_types[i])) {
                    ctx._source.visit_types.add(visit_types[i]);
                }
            }
        }
        """

        actions = [
            {
                "_op_type": "update",
                "_id": sha1,
                "_index": write_index,
                "scripted_upsert": True,
                "upsert": {**document, "sha1": sha1,},
                "script": {
                    "source": update_script,
                    "lang": "painless",
                    "params": document,
                },
            }
            for (sha1, document) in documents_with_sha1
        ]

        indexed_count, errors = helpers.bulk(self._backend, actions, index=write_index)
        assert isinstance(errors, List)  # Make mypy happy

        send_metric("document:index", count=indexed_count, method_name="origin_update")
        send_metric(
            "document:index_error", count=len(errors), method_name="origin_update"
        )

    def origin_dump(self) -> Iterator[model.Origin]:
        results = helpers.scan(self._backend, index=self._get_origin_read_alias())
        for hit in results:
            yield self._backend.termvectors(
                index=self._get_origin_read_alias(), id=hit["_id"], fields=["*"]
            )

    @timed
    def origin_search(
        self,
        *,
        url_pattern: Optional[str] = None,
        metadata_pattern: Optional[str] = None,
        with_visit: bool = False,
        visit_types: Optional[List[str]] = None,
        page_token: Optional[str] = None,
        limit: int = 50,
    ) -> PagedResult[MinimalOriginDict]:
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

        if visit_types is not None:
            query_clauses.append({"terms": {"visit_types": visit_types}})

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

        res = self._backend.search(
            index=self._get_origin_read_alias(), body=body, size=limit
        )

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
