# Copyright (C) 2019  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

import functools

import click

from swh.core import config
from swh.core.cli import CONTEXT_SETTINGS
from swh.journal.cli import get_journal_client

from . import get_search
from .journal_client import process_journal_objects
from .api.server import load_and_check_config, app


@click.group(name='search', context_settings=CONTEXT_SETTINGS)
@click.option('--config-file', '-C', default=None,
              type=click.Path(exists=True, dir_okay=False,),
              help="Configuration file.")
@click.pass_context
def cli(ctx, config_file):
    '''Software Heritage Search tools.'''
    ctx.ensure_object(dict)

    conf = config.read(config_file)
    ctx.obj['config'] = conf


@cli.command('initialize')
@click.pass_context
def initialize(ctx):
    """Creates Elasticsearch indices."""
    search = get_search(**ctx.obj['config']['search'])
    search.initialize()
    print('Done.')


@cli.group('journal-client')
@click.pass_context
def journal_client(ctx):
    """"""
    pass


@journal_client.command('objects')
@click.option('--max-messages', '-m', default=None, type=int,
              help='Maximum number of objects to replay. Default is to '
                   'run forever.')
@click.pass_context
def journal_client_objects(ctx, max_messages):
    """Listens for new objects from the SWH Journal, and schedules tasks
    to run relevant indexers (currently, only origin)
    on these new objects."""
    client = get_journal_client(
        ctx, object_types=['origin', 'origin_visit'],
        max_messages=max_messages)
    search = get_search(**ctx.obj['config']['search'])

    worker_fn = functools.partial(
        process_journal_objects,
        search=search,
    )
    nb_messages = 0
    try:
        while not max_messages or nb_messages < max_messages:
            nb_messages += client.process(worker_fn)
            print('Processed %d messages.' % nb_messages)
    except KeyboardInterrupt:
        ctx.exit(0)
    else:
        print('Done.')


@cli.command('rpc-serve')
@click.argument('config-path', required=True)
@click.option('--host', default='0.0.0.0', help="Host to run the server")
@click.option('--port', default=5010, type=click.INT,
              help="Binding port of the server")
@click.option('--debug/--nodebug', default=True,
              help="Indicates if the server should run in debug mode")
def rpc_server(config_path, host, port, debug):
    """Starts a Software Heritage Indexer RPC HTTP server."""
    api_cfg = load_and_check_config(config_path, type='any')
    app.config.update(api_cfg)
    app.run(host, port=int(port), debug=bool(debug))
