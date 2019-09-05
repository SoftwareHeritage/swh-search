# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from swh.core.api import RPCClient

from ..elasticsearch import ElasticSearch


class RemoteSearch(RPCClient):
    """Proxy to a remote search API"""
    backend_class = ElasticSearch
