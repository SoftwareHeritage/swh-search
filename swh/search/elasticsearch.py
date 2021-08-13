# Copyright (C) 2019-2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import base64
import logging
import pprint
from textwrap import dedent
from typing import Any, Dict, Iterable, Iterator, List, Optional

from elasticsearch import Elasticsearch, helpers
import msgpack

from swh.indexer import codemeta
from swh.model import model
from swh.model.identifiers import origin_identifier
from swh.search.interface import (
    SORT_BY_OPTIONS,
    MinimalOriginDict,
    OriginDict,
    PagedResult,
)
from swh.search.metrics import send_metric, timed
from swh.search.translator import Translator
from swh.search.utils import escape, get_expansion, is_date_parsable

logger = logging.getLogger(__name__)

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
    for field_name in (
        "blocklisted",
        "has_visits",
        "intrinsic_metadata",
        "visit_types",
        "nb_visits",
        "snapshot_id",
        "last_visit_date",
        "last_eventful_visit_date",
        "last_revision_date",
        "last_release_date",
    ):
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
        intrinsic_metadata = res["intrinsic_metadata"]
        for date_field in ["dateCreated", "dateModified", "datePublished"]:
            if date_field in intrinsic_metadata:
                date = intrinsic_metadata[date_field]

                # If date{Created,Modified,Published} value isn't parsable
                # It gets rejected and isn't stored (unlike other fields)
                if not is_date_parsable(date):
                    intrinsic_metadata.pop(date_field)

        res["intrinsic_metadata"] = codemeta.expand(intrinsic_metadata)

    return res


def token_encode(index_to_tokenize: Dict[bytes, Any]) -> str:
    """Tokenize as string an index page result from a search"""
    page_token = base64.b64encode(msgpack.dumps(index_to_tokenize))
    return page_token.decode()


def token_decode(page_token: str) -> Dict[bytes, Any]:
    """Read the page_token"""
    return msgpack.loads(base64.b64decode(page_token.encode()), raw=True)


class ElasticSearch:
    def __init__(self, hosts: List[str], indexes: Dict[str, Dict[str, str]] = {}):
        self._backend = Elasticsearch(hosts=hosts)
        self._translator = Translator()

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
                "dynamic_templates": [
                    {
                        "booleans_as_string": {
                            # All fields stored as string in the metadata
                            # even the booleans
                            "match_mapping_type": "boolean",
                            "path_match": "intrinsic_metadata.*",
                            "mapping": {"type": "keyword"},
                        }
                    }
                ],
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
                    "nb_visits": {"type": "integer"},
                    "snapshot_id": {"type": "keyword"},
                    "last_visit_date": {"type": "date"},
                    "last_eventful_visit_date": {"type": "date"},
                    "last_release_date": {"type": "date"},
                    "last_revision_date": {"type": "date"},
                    "intrinsic_metadata": {
                        "type": "nested",
                        "properties": {
                            "@context": {
                                # don't bother indexing tokens in these URIs, as the
                                # are used as namespaces
                                "type": "keyword",
                            },
                            "http://schema": {
                                "properties": {
                                    "org/dateCreated": {
                                        "properties": {"@value": {"type": "date",}}
                                    },
                                    "org/dateModified": {
                                        "properties": {"@value": {"type": "date",}}
                                    },
                                    "org/datePublished": {
                                        "properties": {"@value": {"type": "date",}}
                                    },
                                }
                            },
                        },
                    },
                    # Has this origin been taken down?
                    "blocklisted": {"type": "boolean",},
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
        update_script = dedent(
            """
            // utility function to get and parse date
            ZonedDateTime getDate(def ctx, String date_field) {
                String default_date = "0001-01-01T00:00:00Z";
                String date = ctx._source.getOrDefault(date_field, default_date);
                return ZonedDateTime.parse(date);
            }

            // backup current visit_types field value
            List visit_types = ctx._source.getOrDefault("visit_types", []);
            int nb_visits = ctx._source.getOrDefault("nb_visits", 0);

            ZonedDateTime last_visit_date = getDate(ctx, "last_visit_date");

            String snapshot_id = ctx._source.getOrDefault("snapshot_id", "");
            ZonedDateTime last_eventful_visit_date =
                getDate(ctx, "last_eventful_visit_date");
            ZonedDateTime last_revision_date = getDate(ctx, "last_revision_date");
            ZonedDateTime last_release_date = getDate(ctx, "last_release_date");

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

            // Undo overwrite if incoming nb_visits is smaller
            if (ctx._source.containsKey("nb_visits")) {
                int incoming_nb_visits = ctx._source.getOrDefault("nb_visits", 0);
                if(incoming_nb_visits < nb_visits){
                    ctx._source.nb_visits = nb_visits;
                }
            }

            // Undo overwrite if incoming last_visit_date is older
            if (ctx._source.containsKey("last_visit_date")) {
                ZonedDateTime incoming_last_visit_date = getDate(ctx, "last_visit_date");
                int difference =
                    // returns -1, 0 or 1
                    incoming_last_visit_date.compareTo(last_visit_date);
                if(difference < 0){
                    ctx._source.last_visit_date = last_visit_date;
                }
            }

            // Undo update of last_eventful_date and snapshot_id if
            // snapshot_id hasn't changed OR incoming_last_eventful_visit_date is older
            if (ctx._source.containsKey("snapshot_id")) {
                String incoming_snapshot_id = ctx._source.getOrDefault("snapshot_id", "");
                ZonedDateTime incoming_last_eventful_visit_date =
                    getDate(ctx, "last_eventful_visit_date");
                int difference =
                    // returns -1, 0 or 1
                    incoming_last_eventful_visit_date.compareTo(last_eventful_visit_date);
                if(snapshot_id == incoming_snapshot_id || difference < 0){
                    ctx._source.snapshot_id = snapshot_id;
                    ctx._source.last_eventful_visit_date = last_eventful_visit_date;
                }
            }

            // Undo overwrite if incoming last_revision_date is older
            if (ctx._source.containsKey("last_revision_date")) {
                ZonedDateTime incoming_last_revision_date =
                    getDate(ctx, "last_revision_date");
                int difference =
                    // returns -1, 0 or 1
                    incoming_last_revision_date.compareTo(last_revision_date);
                if(difference < 0){
                    ctx._source.last_revision_date = last_revision_date;
                }
            }

            // Undo overwrite if incoming last_release_date is older
            if (ctx._source.containsKey("last_release_date")) {
                ZonedDateTime incoming_last_release_date =
                    getDate(ctx, "last_release_date");
                // returns -1, 0 or 1
                int difference = incoming_last_release_date.compareTo(last_release_date);
                if(difference < 0){
                    ctx._source.last_release_date = last_release_date;
                }
            }
            """  # noqa
        )

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
        query: str = "",
        url_pattern: Optional[str] = None,
        metadata_pattern: Optional[str] = None,
        with_visit: bool = False,
        visit_types: Optional[List[str]] = None,
        min_nb_visits: int = 0,
        min_last_visit_date: str = "",
        min_last_eventful_visit_date: str = "",
        min_last_revision_date: str = "",
        min_last_release_date: str = "",
        min_date_created: str = "",
        min_date_modified: str = "",
        min_date_published: str = "",
        programming_languages: Optional[List[str]] = None,
        licenses: Optional[List[str]] = None,
        keywords: Optional[List[str]] = None,
        sort_by: Optional[List[str]] = None,
        page_token: Optional[str] = None,
        limit: int = 50,
    ) -> PagedResult[MinimalOriginDict]:
        query_clauses: List[Dict[str, Any]] = []

        query_filters = []
        if url_pattern:
            query_filters.append(f"origin = {escape(url_pattern)}")

        if metadata_pattern:
            query_filters.append(f"metadata = {escape(metadata_pattern)}")

        # if not query_clauses:
        #     raise ValueError(
        #         "At least one of url_pattern and metadata_pattern must be provided."
        #     )

        if with_visit:
            query_filters.append(f"visited = {'true' if with_visit else 'false'}")
        if min_nb_visits:
            query_filters.append(f"visits >= {min_nb_visits}")
        if min_last_visit_date:
            query_filters.append(
                f"last_visit >= {min_last_visit_date.replace('Z', '+00:00')}"
            )
        if min_last_eventful_visit_date:
            query_filters.append(
                "last_eventful_visit >= "
                f"{min_last_eventful_visit_date.replace('Z', '+00:00')}"
            )
        if min_last_revision_date:
            query_filters.append(
                f"last_revision >= {min_last_revision_date.replace('Z', '+00:00')}"
            )
        if min_last_release_date:
            query_filters.append(
                f"last_release >= {min_last_release_date.replace('Z', '+00:00')}"
            )
        if keywords:
            query_filters.append(f"keyword in {escape(keywords)}")
        if licenses:
            query_filters.append(f"license in {escape(licenses)}")

        if programming_languages:
            query_filters.append(f"language in {escape(programming_languages)}")

        if min_date_created:
            query_filters.append(
                f"created >= {min_date_created.replace('Z', '+00:00')}"
            )
        if min_date_modified:
            query_filters.append(
                f"modified >= {min_date_modified.replace('Z', '+00:00')}"
            )
        if min_date_published:
            query_filters.append(
                f"published >= {min_date_published.replace('Z', '+00:00')}"
            )

        if visit_types is not None:
            query_filters.append(f"visit_type = {escape(visit_types)}")

        combined_filters = f"({' and '.join(query_filters)})"
        query = f"{combined_filters}{' and ' if query != '' else ' '}{query}"
        parsed_query = self._translator.parse_query(query)
        query_clauses.append(parsed_query["filters"])

        field_map = {
            "visits": "nb_visits",
            "last_visit": "last_visit_date",
            "last_eventful_visit": "last_eventful_visit_date",
            "last_revision": "last_revision_date",
            "last_release": "last_release_date",
            "created": "date_created",
            "modified": "date_modified",
            "published": "date_published",
        }

        if "sortBy" in parsed_query:
            if sort_by is None:
                sort_by = []
            for sort_by_option in parsed_query["sortBy"]:
                if sort_by_option[0] == "-":
                    sort_by.append("-" + field_map[sort_by_option[1:]])
                else:
                    sort_by.append(field_map[sort_by_option])
        if parsed_query.get("limit", 0):
            limit = parsed_query["limit"]

        sorting_params: List[Dict[str, Any]] = []

        if sort_by:
            for field in sort_by:
                order = "asc"
                if field and field[0] == "-":
                    field = field[1:]
                    order = "desc"

                if field in ["date_created", "date_modified", "date_published"]:
                    sorting_params.append(
                        {
                            get_expansion(field, "."): {
                                "nested_path": "intrinsic_metadata",
                                "order": order,
                            }
                        }
                    )
                elif field in SORT_BY_OPTIONS:
                    sorting_params.append({field: order})

        sorting_params.extend(
            [{"_score": "desc"}, {"sha1": "asc"},]
        )

        body = {
            "query": {
                "bool": {
                    "must": query_clauses,
                    "must_not": [{"term": {"blocklisted": True}}],
                }
            },
            "sort": sorting_params,
        }

        if page_token:
            # TODO: use ElasticSearch's scroll API?
            page_token_content = token_decode(page_token)
            body["search_after"] = [
                page_token_content[b"score"],
                page_token_content[b"sha1"].decode("ascii"),
            ]

        if logger.isEnabledFor(logging.DEBUG):
            formatted_body = pprint.pformat(body)
            logger.debug("Search query body: %s", formatted_body)

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
