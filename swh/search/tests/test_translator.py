import pytest

from swh.search.translator import Translator
from swh.search.utils import get_expansion


def _test_results(query, expected):
    output = Translator().parse_query(query)
    assert output == expected


def test_empty_query():
    query = ""
    with pytest.raises(Exception):
        _test_results(query, {})


def test_conjunction_operators():
    query = "visited = true or visits > 2 and visits < 5"
    expected = {
        "filters": {
            "bool": {
                "should": [
                    {"term": {"has_visits": True}},
                    {
                        "bool": {
                            "must": [
                                {"range": {"nb_visits": {"gt": 2}}},
                                {"range": {"nb_visits": {"lt": 5}}},
                            ]
                        }
                    },
                ]
            }
        }
    }
    _test_results(query, expected)


def test_conjunction_op_precedence_override():
    query = "(visited = false or visits > 2) and visits < 5"
    expected = {
        "filters": {
            "bool": {
                "must": [
                    {
                        "bool": {
                            "should": [
                                {"term": {"has_visits": False}},
                                {"range": {"nb_visits": {"gt": 2}}},
                            ]
                        }
                    },
                    {"range": {"nb_visits": {"lt": 5}}},
                ]
            }
        }
    }

    _test_results(query, expected)


def test_limit_and_sortby():
    query = "visited = true sort_by = [-visits,last_visit] limit = 15"
    expected = {
        "filters": {"term": {"has_visits": True}},
        "sortBy": ["-visits", "last_visit"],
        "limit": 15,
    }

    _test_results(query, expected)


def test_deeply_nested_filters():
    query = "(((visited = true and visits > 0)))"
    expected = {
        "filters": {
            "bool": {
                "must": [
                    {"term": {"has_visits": True},},
                    {"range": {"nb_visits": {"gt": 0}}},
                ]
            }
        },
    }

    _test_results(query, expected)


def test_origin_and_metadata_filters():
    query = 'origin = django or metadata = "framework and web"'
    expected = {
        "filters": {
            "bool": {
                "should": [
                    {
                        "multi_match": {
                            "query": "django",
                            "type": "bool_prefix",
                            "operator": "and",
                            "fields": [
                                "url.as_you_type",
                                "url.as_you_type._2gram",
                                "url.as_you_type._3gram",
                            ],
                        }
                    },
                    {
                        "nested": {
                            "path": "intrinsic_metadata",
                            "query": {
                                "multi_match": {
                                    "query": "framework and web",
                                    "type": "cross_fields",
                                    "operator": "and",
                                    "fields": ["intrinsic_metadata.*"],
                                    "lenient": True,
                                }
                            },
                        }
                    },
                ]
            }
        }
    }

    _test_results(query, expected)


def test_visits_not_equal_to_filter():
    query = "visits != 5"
    expected = {
        "filters": {
            "bool": {"must_not": [{"range": {"nb_visits": {"gte": 5, "lte": 5}}},]}
        },
    }

    _test_results(query, expected)


def test_visit_type_filter():
    query = 'visit_type = [git,"pypi"]'
    expected = {"filters": {"terms": {"visit_types": ["git", "pypi"]}}}

    _test_results(query, expected)


def test_keyword_filter():
    query = r"""keyword in [word1, "word2 \" \' word3"]"""
    expected = {
        "filters": {
            "nested": {
                "path": "intrinsic_metadata",
                "query": {
                    "multi_match": {
                        "query": r"""word1 word2 " ' word3""",
                        "fields": [
                            get_expansion("keywords", ".") + "^2",
                            get_expansion("descriptions", "."),
                        ],
                    }
                },
            }
        }
    }

    _test_results(query, expected)


def test_language_filter():
    query = 'language in [python, "go lang", cpp]'
    expected = {
        "filters": {
            "nested": {
                "path": "intrinsic_metadata",
                "query": {
                    "bool": {
                        "should": [
                            {
                                "match": {
                                    get_expansion(
                                        "programming_languages", "."
                                    ): "python"
                                }
                            },
                            {
                                "match": {
                                    get_expansion(
                                        "programming_languages", "."
                                    ): "go lang"
                                }
                            },
                            {
                                "match": {
                                    get_expansion("programming_languages", "."): "cpp"
                                }
                            },
                        ]
                    }
                },
            }
        }
    }

    _test_results(query, expected)


def test_license_filter():
    query = 'license in ["GPL 3", Apache, MIT]'
    expected = {
        "filters": {
            "nested": {
                "path": "intrinsic_metadata",
                "query": {
                    "bool": {
                        "should": [
                            {"match": {get_expansion("licenses", "."): "GPL 3"}},
                            {"match": {get_expansion("licenses", "."): "Apache"}},
                            {"match": {get_expansion("licenses", "."): "MIT"}},
                        ]
                    }
                },
            }
        }
    }

    _test_results(query, expected)


def test_date_created_not_equal_to_filter():
    query = "created != 2020-01-01"
    expected = {
        "filters": {
            "nested": {
                "path": "intrinsic_metadata",
                "query": {
                    "bool": {
                        "must_not": [
                            {
                                "range": {
                                    get_expansion("date_created", "."): {
                                        "gte": "2020-01-01",
                                        "lte": "2020-01-01",
                                    }
                                }
                            }
                        ]
                    }
                },
            }
        }
    }

    _test_results(query, expected)


def test_date_created_greater_than_filter():
    query = "created >= 2020-01-01"
    expected = {
        "filters": {
            "nested": {
                "path": "intrinsic_metadata",
                "query": {
                    "bool": {
                        "must": [
                            {
                                "range": {
                                    get_expansion("date_created", "."): {
                                        "gte": "2020-01-01",
                                    }
                                }
                            }
                        ]
                    }
                },
            }
        }
    }

    _test_results(query, expected)


def test_last_eventful_visit_not_equal_to_filter():
    query = "last_visit != 2020-01-01"
    expected = {
        "filters": {
            "bool": {
                "must_not": [
                    {
                        "range": {
                            "last_visit_date": {
                                "gte": "2020-01-01",
                                "lte": "2020-01-01",
                            }
                        }
                    }
                ]
            }
        }
    }

    _test_results(query, expected)


def test_last_eventful_visit_less_than_to_filter():
    query = "last_visit < 2020-01-01"
    expected = {"filters": {"range": {"last_visit_date": {"lt": "2020-01-01"}}}}

    _test_results(query, expected)


def test_keyword_no_escape_inside_filter():
    # any keyword (filter name/operator/value) inside a filter
    # must be considered a string.
    query = r'''origin = "language in [\'go lang\', python]"'''
    expected = {
        "filters": {
            "multi_match": {
                "query": r"""language in ['go lang', python]""",
                "type": "bool_prefix",
                "operator": "and",
                "fields": [
                    "url.as_you_type",
                    "url.as_you_type._2gram",
                    "url.as_you_type._3gram",
                ],
            }
        }
    }
    _test_results(query, expected)


def test_escaped_punctutation_parsing():
    query = r"""keyword in ["foo \'\" bar"]"""
    expected = {
        "filters": {
            "nested": {
                "path": "intrinsic_metadata",
                "query": {
                    "multi_match": {
                        "query": r"""foo '" bar""",
                        "fields": [
                            get_expansion("keywords", ".") + "^2",
                            get_expansion("descriptions", "."),
                        ],
                    }
                },
            }
        }
    }
    _test_results(query, expected)
