# Copyright (C) 2021  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import os
from typing import Any, Dict

import pytest
import yaml

from swh.core.api import RPCServerApp
from swh.core.config import load_from_envvar
from swh.search.api import server
from swh.search.api.server import load_and_check_config, make_app_from_configfile


def teardown_function():
    # Ensure there is no configuration loaded from a previous test
    server.api_cfg = None


def _write_config_file(tmp_path, monkeypatch, content):
    conf_path = os.path.join(str(tmp_path), "search.yml")
    with open(conf_path, "w") as f:
        f.write(yaml.dump(content))
    monkeypatch.setenv("SWH_CONFIG_FILENAME", conf_path)
    return conf_path


@pytest.fixture
def swh_search_server_config_without_indexes() -> Dict[str, Any]:
    return {"search": {"cls": "elasticsearch", "hosts": ["es1"],}}


@pytest.fixture
def swh_search_server_config_with_indexes(
    swh_search_server_config_without_indexes,
) -> Dict[str, Any]:
    return {
        "search": {
            **{"indexes": {"origin": {"index": "test"}}},
            **swh_search_server_config_without_indexes["search"],
        }
    }


@pytest.fixture
def swh_search_config_without_indexes(
    monkeypatch, swh_search_server_config_without_indexes, tmp_path
):
    return _write_config_file(
        tmp_path, monkeypatch, swh_search_server_config_without_indexes
    )


@pytest.fixture
def swh_search_config_with_indexes(
    monkeypatch, swh_search_server_config_with_indexes, tmp_path
):
    return _write_config_file(
        tmp_path, monkeypatch, swh_search_server_config_with_indexes
    )


def prepare_config_file(tmpdir, config_dict: Dict, name: str = "config.yml") -> str:
    """Prepare configuration file in `$tmpdir/name` with content `content`.

    Args:
        tmpdir (LocalPath): root directory
        content: Content of the file either as string or as a dict.
                            If a dict, converts the dict into a yaml string.
        name: configuration filename

    Returns
        path of the configuration file prepared.

    """
    config_path = tmpdir / name
    config_path.write_text(yaml.dump(config_dict), encoding="utf-8")
    # pytest on python3.5 does not support LocalPath manipulation, so
    # convert path to string
    return str(config_path)


@pytest.mark.parametrize("config_file", [None, ""])
def test_load_and_check_config_no_configuration(config_file):
    """Inexistent configuration files raises"""
    with pytest.raises(EnvironmentError, match="Configuration file must be defined"):
        load_and_check_config(config_file)


def test_load_and_check_config_inexistent_file():
    config_path = "/some/inexistent/config.yml"
    expected_error = f"Configuration file {config_path} does not exist"
    with pytest.raises(EnvironmentError, match=expected_error):
        load_and_check_config(config_path)


def test_load_and_check_config_wrong_configuration(tmpdir):
    """Wrong configuration raises"""
    config_path = prepare_config_file(tmpdir, {"something": "useless"})
    with pytest.raises(KeyError, match="Missing 'search' configuration"):
        load_and_check_config(config_path)


def test_load_and_check_config_local_config_fine(
    swh_search_server_config_with_indexes, tmpdir
):
    """'local' complete configuration is fine"""
    config_path = prepare_config_file(tmpdir, swh_search_server_config_with_indexes)
    cfg = load_and_check_config(config_path)
    assert cfg == swh_search_server_config_with_indexes


def test_server_make_app_from_config_file_without_indexes(
    swh_search_config_without_indexes,
):
    app = make_app_from_configfile()
    expected_cfg = load_from_envvar()

    assert app is not None
    assert isinstance(app, RPCServerApp)
    assert app.config["search"] == expected_cfg["search"]

    app2 = make_app_from_configfile()
    assert app is app2


def test_server_make_app_from_config_file_with_indexes(swh_search_config_with_indexes,):
    app = make_app_from_configfile()
    expected_cfg = load_from_envvar()
    assert app is not None
    assert isinstance(app, RPCServerApp)
    assert app.config["search"] == expected_cfg["search"]

    app2 = make_app_from_configfile()
    assert app is app2


def test_server_first_call_initialize_elasticsearch(
    swh_search_config_with_indexes, mocker
):
    """Test the initialize method is called during the first and first only
       request to the server"""
    mock = mocker.patch("swh.search.elasticsearch.ElasticSearch.initialize")

    app = make_app_from_configfile()
    app.config["TESTING"] = True
    tc = app.test_client()

    tc.get("/")
    assert mock.call_count == 1

    tc.get("/")
    assert mock.call_count == 1
