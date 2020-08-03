# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from pkgutil import extend_path
from typing import Iterable

__path__: Iterable[str] = extend_path(__path__, __name__)
