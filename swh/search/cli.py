# Copyright (C) 2019-2020  The Software Heritage developers
# See the AUTHORS file at the top-level directory of this distribution
# License: GNU General Public License version 3, or any later version
# See top-level LICENSE file for more information

# WARNING: do not import unnecessary things here to keep cli startup time under
# control
import click

from swh.core.cli import CONTEXT_SETTINGS
from swh.core.cli import swh as swh_cli_group


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
@click.option(
    "--object-type",
    "-o",
    multiple=True,
    help="Default list of object types to subscribe to",
)
@click.option(
    "--prefix", "-p", help="Topic prefix to use (e.g swh.journal.indexed)",
)
@click.pass_context
def journal_client_objects(ctx, stop_after_objects, object_type, prefix):
    """Listens for new objects from the SWH Journal, and schedules tasks
    to run relevant indexers (currently, origin and origin_visit)
    on these new objects.

    """
    import functools

    from swh.journal.client import get_journal_client
    from swh.storage import get_storage

    from . import get_search
    from .journal_client import process_journal_objects

    config = ctx.obj["config"]
    journal_cfg = config["journal"]

    journal_cfg["object_types"] = object_type or journal_cfg.get("object_types", [])
    journal_cfg["prefix"] = prefix or journal_cfg.get("prefix")
    journal_cfg["stop_after_objects"] = stop_after_objects or journal_cfg.get(
        "stop_after_objects"
    )

    if len(journal_cfg["object_types"]) == 0:
        raise ValueError("'object_types' must be specified by cli or configuration")

    if journal_cfg["prefix"] is None:
        raise ValueError("'prefix' must be specified by cli or configuration")

    client = get_journal_client(cls="kafka", **journal_cfg,)
    search = get_search(**config["search"])
    storage = get_storage(**config["storage"])

    worker_fn = functools.partial(
        process_journal_objects, search=search, storage=storage
    )
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
