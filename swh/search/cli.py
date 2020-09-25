# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

# WARNING: do not import unnecessary things here to keep cli startup time under
# control
import click

from swh.core.cli import CONTEXT_SETTINGS, swh as swh_cli_group


@swh_cli_group.group(name="search", context_settings=CONTEXT_SETTINGS)
@click.option(
    "--config-file",
    "-C",
    default=None,
    type=click.Path(exists=True, dir_okay=False,),
    help="Configuration file.",
)
@click.pass_context
def search_cli_group(ctx, config_file):
    """Software Heritage Search tools."""
    from swh.core import config

    ctx.ensure_object(dict)
    conf = config.read(config_file)
    ctx.obj["config"] = conf


@search_cli_group.command("initialize")
@click.pass_context
def initialize(ctx):
    """Creates Elasticsearch indices."""
    from . import get_search

    search = get_search(**ctx.obj["config"]["search"])
    search.initialize()
    print("Done.")


@search_cli_group.group("journal-client")
@click.pass_context
def journal_client(ctx):
    """"""
    pass


@journal_client.command("objects")
@click.option(
    "--stop-after-objects",
    "-m",
    default=None,
    type=int,
    help="Maximum number of objects to replay. Default is to run forever.",
)
@click.pass_context
def journal_client_objects(ctx, stop_after_objects):
    """Listens for new objects from the SWH Journal, and schedules tasks
    to run relevant indexers (currently, only origin)
    on these new objects."""
    import functools

    from swh.journal.client import get_journal_client

    from . import get_search
    from .journal_client import process_journal_objects

    config = ctx.obj["config"]
    journal_cfg = config["journal"]

    client = get_journal_client(
        cls="kafka",
        object_types=["origin", "origin_visit"],
        stop_after_objects=stop_after_objects,
        **journal_cfg,
    )
    search = get_search(**config["search"])

    worker_fn = functools.partial(process_journal_objects, search=search,)
    nb_messages = 0
    try:
        nb_messages = client.process(worker_fn)
        print("Processed %d messages." % nb_messages)
    except KeyboardInterrupt:
        ctx.exit(0)
    else:
        print("Done.")
    finally:
        client.close()


@search_cli_group.command("rpc-serve")
@click.argument("config-path", required=True)
@click.option("--host", default="0.0.0.0", help="Host to run the server")
@click.option("--port", default=5010, type=click.INT, help="Binding port of the server")
@click.option(
    "--debug/--nodebug",
    default=True,
    help="Indicates if the server should run in debug mode",
)
def rpc_server(config_path, host, port, debug):
    """Starts a Software Heritage Indexer RPC HTTP server."""
    from .api.server import app, load_and_check_config

    api_cfg = load_and_check_config(config_path, type="any")
    app.config.update(api_cfg)
    app.run(host, port=int(port), debug=bool(debug))
