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
