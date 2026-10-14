# Copyright (C) 2021-2026  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import codecs
from datetime import datetime
from typing import Any, Dict, Optional

import iso8601

EMPTY_SNAPSHOT_ID = "1a8893e6a86f444e8be8e7bda6cb34fb1735a00e"


def get_expansion(field, sep=None):
    METADATA_FIELDS = {
        "licenses": ["jsonld", "http://schema.org/license", "@id"],
        "programming_languages": [
            "jsonld",
            "http://schema.org/programmingLanguage",
            "@value",
        ],
        "keywords": [
            "jsonld",
            "http://schema.org/keywords",
            "@value",
        ],
        "descriptions": [
            "jsonld",
            "http://schema.org/description",
            "@value",
        ],
        "date_created": [
            "jsonld",
            "http://schema.org/dateCreated",
            "@value",
        ],
        "date_modified": [
            "jsonld",
            "http://schema.org/dateModified",
            "@value",
        ],
        "date_published": [
            "jsonld",
            "http://schema.org/datePublished",
            "@value",
        ],
    }

    if sep:
        return sep.join(METADATA_FIELDS[field])

    return METADATA_FIELDS[field]


def parse_and_format_date(date_str: str) -> Optional[str]:
    """
    Parses a string date in the format %Y-%m-%d or ISO8601 and returns
    a new string date in the format YYYY-mm-dd if the parsing succeeded
    otherwise None.
    """
    try:
        return datetime.strptime(date_str, "%Y-%m-%d").strftime("%Y-%m-%d")
    except Exception:
        try:
            return iso8601.parse_date(date_str).strftime("%Y-%m-%d")
        except Exception:
            return None


def escape(obj):
    r"""Makes the object directly injectable into the
    query language by converting the escapable parts of
    the object into escape sequences.

    For strings, appends \ before special characters like ', ", and \

    For arrays, applies the same transformation on each element, joins the
    elements and returns a string-like representation of the list.

    >>> print(escape("foo ' bar"))
    "foo \' bar"

    >>> print(escape([r"foo ' bar", r"bar \\\' baz", r'foo " baz']))
    ["foo \' bar", "bar \\\\\\\' baz", "foo \" baz"]

    """
    if type(obj) is list:
        items = [escape(item) for item in obj]
        return "[" + ", ".join(items) + "]"
    elif type(obj) is str:
        return (
            '"'
            + obj.translate(
                {
                    ord("'"): r"\'",
                    ord('"'): r"\"",
                    ord("\\"): r"\\",
                }
            )
            + '"'
        )
    else:
        raise Exception(f"Unexpected item type {type(obj)}")


def unescape(string):
    r"""Processes the escaped special characters

    >>> unescape(r'''foo " bar''') == r'''foo " bar'''
    True
    >>> unescape(r'''foo \" bar''') == r'''foo " bar'''
    True
    >>> unescape(r'''foo \\" bar''') == r'''foo \" bar'''
    True
    >>> unescape(r'''foo \\\" bar''') == r'''foo \" bar'''
    True
    >>> unescape(r'''foo \\\\" bar''') == r'''foo \\" bar'''
    True
    >>> unescape(r'''café \" foo''') == r'''café " foo'''
    True
    """
    return codecs.escape_decode(string.encode())[0].decode()


def clean_optional_date(date: Optional[str]) -> datetime:
    return datetime.fromisoformat(
        (date or "0001-01-01T00:00:00.000000Z").replace("Z", "+00:00")
    )


def merge_documents(left: Dict[str, Any], right: Dict[str, Any]) -> Dict[str, Any]:
    """Merge two documents into the right document"""
    if "visit_types" in left:
        right["visit_types"] = list(
            set(right.get("visit_types", []) + left["visit_types"])
        )

    if "nb_visits" in left:
        right["nb_visits"] = max(right.get("nb_visits", 0), left["nb_visits"])

    for date in ("last_visit_date", "last_revision_date", "last_release_date"):
        if date in left or date in right:
            right[date] = max(
                clean_optional_date(left.get(date)),
                clean_optional_date(right.get(date)),
            ).isoformat()

    if (
        right.get("snapshot_id") is not None
        and (right_date := right.get("last_eventful_visit_date")) is not None
    ):
        incoming_date = datetime.fromisoformat(right_date)
        current_date = clean_optional_date(left.get("last_eventful_visit_date"))
        incoming_snapshot_id = right["snapshot_id"]
        current_snapshot_id = left.get("snapshot_id", "")

        if incoming_snapshot_id == current_snapshot_id or incoming_date < current_date:
            # update not required so override the incoming_values
            right["snapshot_id"] = current_snapshot_id
            right["last_eventful_visit_date"] = current_date.isoformat()
    else:
        if "snapshot_id" in left:
            right["snapshot_id"] = left["snapshot_id"]
        if "last_eventful_visit_date" in left:
            right["last_eventful_visit_date"] = left["last_eventful_visit_date"]

    return right
