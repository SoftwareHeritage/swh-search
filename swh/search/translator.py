import os

from pkg_resources import resource_filename
from tree_sitter import Language, Parser

from swh.search.utils import get_expansion, unescape


class Translator:

    RANGE_OPERATOR_MAP = {
        ">": "gt",
        "<": "lt",
        ">=": "gte",
        "<=": "lte",
    }

    def __init__(self):
        ql_rel_paths = [
            "static/swh_ql.so",  # installed
            "../../query_language/static/swh_ql.so",  # development
        ]
        for ql_rel_path in ql_rel_paths:
            ql_path = resource_filename("swh.search", ql_rel_path)
            if os.path.exists(ql_path):
                break
        else:
            assert False, "swh_ql.so was not found in any of the expected paths"

        search_ql = Language(ql_path, "swh_search_ql")

        self.parser = Parser()
        self.parser.set_language(search_ql)
        self.query = ""

    def parse_query(self, query):
        self.query = query
        tree = self.parser.parse(query.encode("utf8"))
        self.query_node = tree.root_node

        if self.query_node.has_error:
            raise Exception("Invalid query")

        return self._traverse(self.query_node)

    def _traverse(self, node):
        if len(node.children) == 3 and node.children[1].type == "filters":
            # filters => ( filters )
            return self._traverse(node.children[1])  # Go past the () brackets
        if node.type == "query":
            result = {}
            for child in node.children:
                # query => filters sort_by limit
                result[child.type] = self._traverse(child)

            return result

        if node.type == "filters":
            if len(node.children) == 1:
                # query => filters
                # filters => filters
                # filters => filter
                # Current node is just a wrapper, so go one level deep
                return self._traverse(node.children[0])

            if len(node.children) == 3:
                # filters => filters conj_op filters
                filters1 = self._traverse(node.children[0])
                conj_op = self._get_value(node.children[1])
                filters2 = self._traverse(node.children[2])

                if conj_op == "and":
                    # "must" is equivalent to "AND"
                    return {"bool": {"must": [filters1, filters2]}}
                if conj_op == "or":
                    # "should" is equivalent to "OR"
                    return {"bool": {"should": [filters1, filters2]}}

        if node.type == "filter":
            filter_category = node.children[0]
            return self._parse_filter(filter_category)

        if node.type == "sortBy":
            return self._parse_filter(node)

        if node.type == "limit":
            return self._parse_filter(node)

        return Exception(
            f"Unknown node type ({node.type}) "
            f"or unexpected number of children ({node.children})"
        )

    def _get_value(self, node):
        if (
            len(node.children) > 0
            and node.children[0].type == "["
            and node.children[-1].type == "]"
        ):
            # array
            return [self._get_value(child) for child in node.children if child.is_named]

        start = node.start_point[1]
        end = node.end_point[1]

        value = self.query[start:end]

        if len(value) > 1 and (
            (value[0] == "'" and value[-1] == "'") or (value[0] and value[-1] == '"')
        ):
            return unescape(value[1:-1])

        if node.type in ["number", "numberVal"]:
            return int(value)
        return unescape(value)

    def _parse_filter(self, filter):

        if filter.type == "boundedListFilter":
            filter = filter.children[0]

        children = filter.children
        assert len(children) == 3

        category = filter.type
        name, op, value = [self._get_value(child) for child in children]

        if category == "patternFilter":
            if name == "origin":
                return {
                    "multi_match": {
                        "query": value,
                        "type": "bool_prefix",
                        "operator": "and",
                        "fields": [
                            "url.as_you_type",
                            "url.as_you_type._2gram",
                            "url.as_you_type._3gram",
                        ],
                    }
                }
            elif name == "metadata":
                return {
                    "nested": {
                        "path": "intrinsic_metadata",
                        "query": {
                            "multi_match": {
                                "query": value,
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
                                # date{Created,Modified,Published} are of type date
                                "lenient": True,
                            }
                        },
                    }
                }

        if category == "booleanFilter":
            if name == "visited":
                return {"term": {"has_visits": value == "true"}}

        if category == "numericFilter":
            if name == "visits":
                if op in ["=", "!="]:
                    return {
                        "bool": {
                            ("must" if op == "=" else "must_not"): [
                                {"range": {"nb_visits": {"gte": value, "lte": value}}}
                            ]
                        }
                    }
                else:
                    return {
                        "range": {"nb_visits": {self.RANGE_OPERATOR_MAP[op]: value}}
                    }

        if category == "visitTypeFilter":
            if name == "visit_type":
                return {"terms": {"visit_types": value}}

        if category == "unboundedListFilter":
            value_array = value

            if name == "keyword":
                return {
                    "nested": {
                        "path": "intrinsic_metadata",
                        "query": {
                            "multi_match": {
                                "query": " ".join(value_array),
                                "fields": [
                                    get_expansion("keywords", ".") + "^2",
                                    get_expansion("descriptions", "."),
                                    # "^2" boosts an origin's score by 2x
                                    # if it the queried keywords are
                                    # found in its intrinsic_metadata.keywords
                                ],
                            }
                        },
                    }
                }
            elif name in ["language", "license"]:
                name_mapping = {
                    "language": "programming_languages",
                    "license": "licenses",
                }
                name = name_mapping[name]

                return {
                    "nested": {
                        "path": "intrinsic_metadata",
                        "query": {
                            "bool": {
                                "should": [
                                    {"match": {get_expansion(name, "."): val}}
                                    for val in value_array
                                ],
                            }
                        },
                    }
                }

        if category == "dateFilter":

            if name in ["created", "modified", "published"]:
                if op in ["=", "!="]:
                    return {
                        "nested": {
                            "path": "intrinsic_metadata",
                            "query": {
                                "bool": {
                                    ("must" if op == "=" else "must_not"): [
                                        {
                                            "range": {
                                                get_expansion(f"date_{name}", "."): {
                                                    "gte": value,
                                                    "lte": value,
                                                }
                                            }
                                        }
                                    ],
                                }
                            },
                        }
                    }

                return {
                    "nested": {
                        "path": "intrinsic_metadata",
                        "query": {
                            "bool": {
                                "must": [
                                    {
                                        "range": {
                                            get_expansion(f"date_{name}", "."): {
                                                self.RANGE_OPERATOR_MAP[op]: value,
                                            }
                                        }
                                    }
                                ],
                            }
                        },
                    }
                }
            else:
                if op in ["=", "!="]:
                    return {
                        "bool": {
                            ("must" if op == "=" else "must_not"): [
                                {
                                    "range": {
                                        f"{name}_date": {"gte": value, "lte": value,}
                                    }
                                }
                            ],
                        }
                    }
                return {
                    "range": {
                        f"{name}_date": {
                            self.RANGE_OPERATOR_MAP[op]: value.replace("Z", "+00:00"),
                        }
                    }
                }

        if category == "sortBy":
            return value

        if category == "limit":
            return value

        raise Exception(f"Unknown filter {category}.{name}")
