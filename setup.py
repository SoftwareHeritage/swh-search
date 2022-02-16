#!/usr/bin/env python3
# Copyright (C) 2015-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from distutils.cmd import Command
from distutils.command.build import build
import glob
from io import open
import os
import shutil
import subprocess

from setuptools import find_packages, setup
from setuptools.command.develop import develop
from setuptools.command.sdist import sdist

here = os.path.abspath(os.path.dirname(__file__))

# Get the long description from the README file
with open(os.path.join(here, "README.md"), encoding="utf-8") as f:
    long_description = f.read()


def parse_requirements(name=None):
    if name:
        reqf = "requirements-%s.txt" % name
    else:
        reqf = "requirements.txt"

    requirements = []
    if not os.path.exists(reqf):
        return requirements

    with open(reqf) as f:
        for line in f.readlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            requirements.append(line)
    return requirements


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


class custom_build(build):
    def run(self):
        super().run()

        if not self.dry_run:
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
    name="swh.search",
    description="Software Heritage search service",
    long_description=long_description,
    long_description_content_type="text/markdown",
    python_requires=">=3.7",
    author="Software Heritage developers",
    author_email="swh-devel@inria.fr",
    url="https://forge.softwareheritage.org/diffusion/DSEA",
    packages=find_packages(),  # packages's modules
    install_requires=parse_requirements() + parse_requirements("swh"),
    tests_require=parse_requirements("test"),
    entry_points="""
        [swh.cli.subcommands]
        search=swh.search.cli
    """,
    setup_requires=["setuptools-scm", "tree-sitter"],
    use_scm_version=True,
    extras_require={"testing": parse_requirements("test")},
    include_package_data=True,
    classifiers=[
        "Programming Language :: Python :: 3",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
        "Operating System :: OS Independent",
        "Development Status :: 3 - Alpha",
    ],
    project_urls={
        "Bug Reports": "https://forge.softwareheritage.org/maniphest",
        "Funding": "https://www.softwareheritage.org/donate",
        "Source": "https://forge.softwareheritage.org/source/swh-search",
        "Documentation": "https://docs.softwareheritage.org/devel/swh-search/",
    },
    cmdclass={
        "build": custom_build,
        "sdist": custom_sdist,
        "develop": custom_develop,
        "ts_install": TSInstallCommand,
        "ts_build_so": TSBuildSoCommand,
        "ts_build": TSBuildCommand,
    },
    zip_safe=False,
)
