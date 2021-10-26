# Copyright (C) 2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import pytest

from swh.search.utils import parse_and_format_date


@pytest.mark.parametrize(
    "date_str",
    ["2021-07-03", "2021-7-03", "2021-07-3", "2021-7-3", "2021-07-03T15:17:08Z"],
)
def test_parse_and_format_date_success(date_str):
    assert parse_and_format_date(date_str) == "2021-07-03"


@pytest.mark.parametrize(
    "date_str", ["foo", "2021/07/03", "2021+07+03T15,17,08Z"],
)
def test_parse_and_format_date_failure(date_str):
    assert parse_and_format_date(date_str) is None
