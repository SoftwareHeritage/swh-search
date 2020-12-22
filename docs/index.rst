.. _swh-search:

Software Heritage - search service
==================================

The SWH search service, or swh-search, stores a partial copy of
the |swh| archive.
It is similar to swh-storage in what it contains,
but provides different ways to query it: while swh-storage is mostly
a key-value store that returns an object from a primary key,
swh-search is focused on reverse indices, to allow finding objects that
match some criteria; for example full-text search.


.. toctree::
   :maxdepth: 2
   :caption: Contents:


Reference Documentation
-----------------------

.. toctree::
   :maxdepth: 2

   /apidoc/swh.search
