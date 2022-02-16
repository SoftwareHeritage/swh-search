# Copyright (C) 2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import codecs
from datetime import datetime
from typing import Optional

import iso8601


def get_expansion(field, sep=None):
    METADATA_FIELDS = {
        "licenses": ["intrinsic_metadata", "http://schema.org/license", "@id"],
        "programming_languages": [
            "intrinsic_metadata",
            "http://schema.org/programmingLanguage",
            "@value",
        ],
        "keywords": ["intrinsic_metadata", "http://schema.org/keywords", "@value",],
        "descriptions": [
            "intrinsic_metadata",
            "http://schema.org/description",
            "@value",
        ],
        "date_created": [
            "intrinsic_metadata",
            "http://schema.org/dateCreated",
            "@value",
        ],
        "date_modified": [
            "intrinsic_metadata",
            "http://schema.org/dateModified",
            "@value",
        ],
        "date_published": [
            "intrinsic_metadata",
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
    if type(obj) == list:
        items = [escape(item) for item in obj]
        return "[" + ", ".join(items) + "]"
    elif type(obj) == str:
        return (
            '"'
            + obj.translate({ord("'"): r"\'", ord('"'): r"\"", ord("\\"): r"\\",})
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
