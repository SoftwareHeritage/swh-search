#!/usr/bin/env python3
# Copyright (C) 2015-2023  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import glob
import os
import shutil
import subprocess

from setuptools import Command, setup
from setuptools.command.build_py import build_py
from setuptools.command.develop import develop
from setuptools.command.sdist import sdist


def needs_regen(dest, sources) -> bool:
    """Returns whether any of the 'sources' files was modified after 'dst'."""
    if not os.path.exists(dest):
        return True

    dest_mtime = os.stat(dest).st_mtime

    for source in sources:
        if os.stat(source).st_mtime > dest_mtime:
            return True

    return False


yarn = os.environ.get("YARN", "yarnpkg" if shutil.which("yarnpkg") else "yarn")


class TSCommand(Command):
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass


class TSInstallCommand(TSCommand):
    description = "Installs node_modules related to query language"

    def run(self):
        subprocess.run([yarn, "install"], check=True)


class TSBuildSoCommand(TSCommand):
    description = "Builds swh_ql.so"

    def initialize_options(self):
        self.build_lib = None
        super().initialize_options()

    def finalize_options(self):
        self.set_undefined_options("build", ("build_lib", "build_lib"))
        super().finalize_options()

    def run(self):
        ql_dir = os.path.join(self.build_lib, "swh/search/query_language")
        copy_ql_tree(ql_dir)
        if needs_regen(
            os.path.join(ql_dir, "src/parser.c"),
            glob.glob("swh/search/query_language/**/*"),
        ):
            print("parser.c missing from build dir.")
            self.run_command("ts_install")
            generate_parser(ql_dir)

        static_dir = os.path.join(self.build_lib, "swh/search/static")
        os.makedirs(static_dir, exist_ok=True)

        # This import cannot be toplevel, as setuptools installs it after the script
        # starts running
        from tree_sitter import Language

        Language.build_library(os.path.join(static_dir, "swh_ql.so"), [ql_dir])
        print("swh_ql.so file generated")


class TSBuildCommand(TSCommand):
    description = "Builds swh_ql.so"

    def run(self):
        self.run_command("ts_build_so")


class custom_build(build_py):
    def run(self):
        super().run()
        if not self.dry_run:
            if getattr(self, "editable_mode", False):
                # setuptools >= 64
                self.run_command("ts_install")
                generate_parser("swh/search/query_language")
            else:
                self.run_command("ts_build")


class custom_sdist(sdist):
    def make_release_tree(self, base_dir, files):
        super().make_release_tree(base_dir, files)

        dist_ql_path = os.path.join(base_dir, "swh/search/query_language")

        if not self.dry_run:
            self.run_command("ts_install")

            copy_ql_tree(dist_ql_path)
            generate_parser(dist_ql_path)


class custom_develop(develop):
    def run(self):
        super().run()
        if not self.dry_run:
            self.run_command("ts_install")
            generate_parser("swh/search/query_language")


def copy_ql_tree(dest_path):
    # FIXME: setuptools should copy this itself...
    print("Copying parser files")
    if os.path.exists(dest_path):
        shutil.rmtree(dest_path)
    shutil.copytree("swh/search/query_language", dest_path)


def generate_parser(dest_path):
    print("Getting path")
    path = subprocess.check_output([yarn, "bin"]).decode().strip()
    env = {**os.environ, "PATH": os.pathsep.join([path, os.environ["PATH"]])}
    print("Generating")
    subprocess.run(["tree-sitter", "generate", "--no-bindings"], cwd=dest_path, env=env)


setup(
    cmdclass={
        "build_py": custom_build,
        "sdist": custom_sdist,
        "develop": custom_develop,
        "ts_install": TSInstallCommand,
        "ts_build_so": TSBuildSoCommand,
        "ts_build": TSBuildCommand,
    },
)
