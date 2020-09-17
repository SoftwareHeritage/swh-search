# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import importlib
from typing import TYPE_CHECKING, Any, Dict
import warnings

if TYPE_CHECKING:
    # importing swh.storage.interface triggers the load of 300+ modules, so...
    from swh.search.interface import SearchInterface


SEARCH_IMPLEMENTATIONS = {
    "elasticsearch": ".elasticsearch.ElasticSearch",
    "remote": ".api.client.RemoteSearch",
    "memory": ".in_memory.InMemorySearch",
}


def get_search(cls: str, **kwargs: Dict[str, Any]) -> "SearchInterface":
    """Get an search object of class `cls` with arguments `args`.

    Args:
        cls: search's class, either 'local' or 'remote'
        args: dictionary of arguments passed to the
            search class constructor

    Returns:
        an instance of swh.search's classes (either local or remote)

    Raises:
        ValueError if passed an unknown search class.

    """
    if "args" in kwargs:
        warnings.warn(
            'Explicit "args" key is deprecated, use keys directly instead.',
            DeprecationWarning,
        )
        kwargs = kwargs["args"]

    class_path = SEARCH_IMPLEMENTATIONS.get(cls)
    if class_path is None:
        raise ValueError(
            "Unknown search class `%s`. Supported: %s"
            % (cls, ", ".join(SEARCH_IMPLEMENTATIONS))
        )

    (module_path, class_name) = class_path.rsplit(".", 1)
    module = importlib.import_module(module_path, package=__package__)
    Search = getattr(module, class_name)
    return Search(**kwargs)
