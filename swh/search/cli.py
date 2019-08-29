# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import click

from swh.core.cli import CONTEXT_SETTINGS


@click.group(name='search', context_settings=CONTEXT_SETTINGS)
@click.pass_context
def search(ctx):
    '''Software Heritage Search tools.'''
    pass
