#!/usr/bin/env python3
# Copyright (C) 2015-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

from distutils.cmd import Command
from io import open
import os
import shutil
import subprocess
import sys

from setuptools import find_packages, setup
from setuptools.command.build_py import build_py
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


yarn = os.environ.get("YARN", "yarn")


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


class TSGenerateCommand(TSCommand):
    description = "Generates parser related files from grammar.js"

    def run(self):
        subprocess.run([yarn, "generate"], check=True)


class TSBuildSoCommand(TSCommand):
    description = "Builds swh_ql.so"

    def run(self):
        # setup_requires changes sys.path so the build dependencies
        # can be imported even though they are in a temporary
        # directory (usually `.eggs`). We need to pass this updated sys.path to
        # 'yarn build-so', as it invokes a Python script that needs to import
        # tree_sitter
        env = {**os.environ, "PYTHONPATH": os.pathsep.join(sys.path)}
        subprocess.run([yarn, "build-so"], check=True, env=env)
        print("swh_ql.so file generated")


class TSBuildWasmCommand(TSCommand):
    description = "Builds swh_ql.wasm"

    def run(self):
        subprocess.run([yarn, "build-wasm"], check=True)
        print("swh_ql.wasm file generated")


class TSBuildCommand(TSCommand):
    description = "Builds swh_ql.so and swh_ql.wasm"

    def run(self):
        self.run_command("ts_build_so")
        self.run_command("ts_build_wasm")


class TSBuildExportCommand(TSCommand):
    description = "Builds swh_ql.so and swh_ql.wasm and exports them to static/"

    def initialize_options(self):
        self.build_lib = None
        super().initialize_options()

    def finalize_options(self):
        self.set_undefined_options("build", ("build_lib", "build_lib"))
        super().finalize_options()

    def run(self):
        self.run_command("ts_install")
        self.run_command("ts_build")

        print("static files generated. copying them to package dir")
        os.makedirs(os.path.join(self.build_lib, "swh/search/static"), exist_ok=True)
        shutil.copyfile(
            "query_language/swh_ql.so",
            os.path.join(self.build_lib, "swh/search/static/swh_ql.so"),
        )
        shutil.copyfile(
            "query_language/swh_ql.wasm",
            os.path.join(self.build_lib, "swh/search/static/swh_ql.wasm"),
        )


class custom_build(build_py):
    def run(self):
        super().run()

        if not self.dry_run:
            self.run_command("ts_build_export")


class custom_sdist(sdist):
    def make_release_tree(self, base_dir, files):
        super().make_release_tree(base_dir, files)
        # TODO: build the .c file and .wasm but not .so, because it's architecture-
        # dependent, and shouldn't be in a sdist (aka *source* distribution)
        if not self.dry_run:
            self.run_command("ts_install")
            self.run_command("ts_build")

            print("static files generated. copying them to package dir")
            os.makedirs(os.path.join(base_dir, "swh/search/static"), exist_ok=True)
            shutil.copyfile(
                "query_language/swh_ql.so",
                os.path.join(base_dir, "swh/search/static/swh_ql.so"),
            )
            shutil.copyfile(
                "query_language/swh_ql.wasm",
                os.path.join(base_dir, "swh/search/static/swh_ql.wasm"),
            )


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
    setup_requires=["setuptools-scm", "tree-sitter==0.19.0"],
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
        "build_py": custom_build,
        "sdist": custom_sdist,
        "ts_install": TSInstallCommand,
        "ts_generate": TSGenerateCommand,
        "ts_build_so": TSBuildSoCommand,
        "ts_build_wasm": TSBuildWasmCommand,
        "ts_build": TSBuildCommand,
        "ts_build_export": TSBuildExportCommand,
    },
    zip_safe=False,
)
