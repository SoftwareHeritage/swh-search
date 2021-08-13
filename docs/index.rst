.. _swh-search:

Software Heritage - Search service
==================================

The SWH search service, or swh-search, stores a partial copy of
the |swh| archive.
It is similar to swh-storage in what it contains,
but provides different ways to query it: while swh-storage is mostly
a key-value store that returns an object from a primary key,
swh-search is focused on reverse indices, to allow finding objects that
match some criteria; for example full-text search.

It is currently based on Elasticsearch, allowing full-text search on both
URLs (using a ``search_as_you_type`` index) and on intrinsic metadata of
their head revision in CodeMeta_ format.

It is kept in sync with :ref:`the main SWH storage <swh-storage>` via
:ref:`the SWH journal <swh-journal>`.

.. _CodeMeta: https://codemeta.github.io/


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   cli
   query-language

Reference Documentation
-----------------------

.. toctree::
   :maxdepth: 2

   /apidoc/swh.search
