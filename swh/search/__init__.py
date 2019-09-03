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
    else:
        raise ValueError('Unknown indexer search class `%s`' % cls)

    return Search(**args)


