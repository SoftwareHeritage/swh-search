# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information


def get_search(cls, args):
    """Get an search object of class `search_class` with
    arguments `search_args`.

    Args:
        cls (str): search's class, either 'local' or 'remote'
        args (dict): dictionary of arguments passed to the
            search class constructor

    Returns:
        an instance of swh.search's classes (either local or remote)

    Raises:
        ValueError if passed an unknown search class.

    """
    if cls == 'remote':
        from .api.client import RemoteSearch as Search
    elif cls == 'elasticsearch':
        from .elasticsearch import ElasticSearch as Search
    elif cls == 'memory':
        from .in_memory import InMemorySearch as Search
    else:
        raise ValueError('Unknown indexer search class `%s`' % cls)

    return Search(**args)
