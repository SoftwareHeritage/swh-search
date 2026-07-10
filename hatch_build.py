# Copyright (C) 2026  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import glob
import os
import shutil
import subprocess
from typing import Any

from hatchling.builders.hooks.plugin.interface import BuildHookInterface

yarn = os.environ.get("YARN", "yarnpkg" if shutil.which("yarnpkg") else "yarn")


def needs_regen(dest, sources) -> bool:
    """Returns whether any of the 'sources' files was modified after 'dst'."""
    if not os.path.exists(dest):
        return True

    dest_mtime = os.stat(dest).st_mtime

    for source in sources:
        if os.stat(source).st_mtime > dest_mtime:
            return True

    return False


def generate_parser(dest_path):
    print("Generating swh/search/query_language/src/parser.c")
    path = subprocess.check_output([yarn, "bin"]).decode().strip()
    env = {
        **os.environ,
        "PATH": os.pathsep.join([path, "node_modules/.bin", os.environ["PATH"]]),
    }
    subprocess.run(
        ["tree-sitter", "generate", "--no-bindings"], cwd=dest_path, env=env, check=True
    )


class CustomBuildHook(BuildHookInterface):

    def initialize(self, version: str, build_data: dict[str, Any]) -> None:
        os.makedirs(os.path.join(self.root, "swh/search/static"), exist_ok=True)
        ql_dir = os.path.join(self.root, "swh/search/query_language")
        if needs_regen(
            os.path.join(ql_dir, "src/parser.c"),
            glob.glob("swh/search/query_language/**/*"),
        ):
            print("parser.c missing from build dir.")
            print("Installing tree-sitter-cli")
            subprocess.run([yarn, "install"], check=True)
            generate_parser(ql_dir)
