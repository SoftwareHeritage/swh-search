from datetime import datetime

import iso8601  # type: ignore


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


def is_date_parsable(date_str):
    """
    Return True if date_str is in the format
    %Y-%m-%d or the standard ISO format.
    Otherwise return False.
    """
    try:
        datetime.strptime(date_str, "%Y-%m-%d")
        return True
    except Exception:
        try:
            iso8601.parse_date(date_str)
            return True
        except Exception:
            return False


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
    """

    return bytes(string, "utf-8").decode("unicode_escape")
