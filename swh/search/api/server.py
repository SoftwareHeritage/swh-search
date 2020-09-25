# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import logging
import os

from swh.core import config
from swh.core.api import RPCServerApp
from swh.core.api import encode_data_server as encode_data
from swh.core.api import error_handler

from .. import get_search
from ..interface import SearchInterface


def _get_search():
    global search
    if not search:
        search = get_search(**app.config["search"])

    return search


app = RPCServerApp(__name__, backend_class=SearchInterface, backend_factory=_get_search)

search = None


@app.errorhandler(Exception)
def my_error_handler(exception):
    return error_handler(exception, encode_data)


@app.route("/")
def index():
    return "SWH Search API server"


api_cfg = None


def load_and_check_config(config_file, type="elasticsearch"):
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
        raise EnvironmentError("Configuration file must be defined")

    if not os.path.exists(config_file):
        raise FileNotFoundError("Configuration file %s does not exist" % (config_file,))

    cfg = config.read(config_file)
    if "search" not in cfg:
        raise KeyError("Missing 'search' configuration")

    return cfg


def make_app_from_configfile():
    """Run the WSGI app from the webserver, loading the configuration from
       a configuration file.

       SWH_CONFIG_FILENAME environment variable defines the
       configuration path to load.

    """
    global api_cfg
    if not api_cfg:
        config_file = os.environ.get("SWH_CONFIG_FILENAME")
        api_cfg = load_and_check_config(config_file)
        app.config.update(api_cfg)
    handler = logging.StreamHandler()
    app.logger.addHandler(handler)
    return app
