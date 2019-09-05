# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import os

from swh.core import config
from swh.core.api import (RPCServerApp, error_handler,
                          encode_data_server as encode_data)

from .. import get_search
from ..elasticsearch import ElasticSearch


def _get_search():
    global search
    if not search:
        search = get_search(**app.config['search'])
        print('got search', repr(search.__class__))

    return search


app = RPCServerApp(__name__,
                   backend_class=ElasticSearch,
                   backend_factory=_get_search)

search = None


@app.errorhandler(Exception)
def my_error_handler(exception):
    return error_handler(exception, encode_data)


@app.route('/')
def index():
    return 'SWH Search API server'


def load_and_check_config(config_file, type='elasticsearch'):
    """Check the minimal configuration is set to run the api or raise an
       error explanation.

    Args:
        config_file (str): Path to the configuration file to load
        type (str): configuration type. For 'local' type, more
                    checks are done.

    Raises:
        Error if the setup is not as expected

    Returns:
        configuration as a dict

    """
    if not config_file:
        raise EnvironmentError('Configuration file must be defined')

    if not os.path.exists(config_file):
        raise FileNotFoundError('Configuration file %s does not exist' % (
            config_file, ))

    cfg = config.read(config_file)
    if 'search' not in cfg:
        raise KeyError("Missing 'search' configuration")

    return cfg
