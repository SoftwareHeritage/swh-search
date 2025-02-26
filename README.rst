Software Heritage - Search service
==================================

Search service for the Software Heritage archive.

It is similar to swh-storage in what it contains, but provides different ways
to query it: while swh-storage is mostly a key-value store that returns an
object from a primary key, swh-search is focused on reverse indices, to allow
finding objects that match some criteria; for example full-text search.

Currently uses ElasticSearch, and provides only origin search (by URL and
metadata).

Dependencies
------------

- Python tests for this module include tests that cannot be run without a local
  ElasticSearch instance, so you need the ElasticSearch server executable on
  your machine (no need to have a running ElasticSearch server).

  - Debian-like host

    The elasticsearch package is required. As it's not part of debian-stable,
    `another debian repository is required to be configured`_

    .. _`another debian repository is required to be configured`: https://www.elastic.co/guide/en/elasticsearch/reference/current/deb.html

  - Non Debian-like host

    The tests expect:

    - ``/usr/share/elasticsearch/jdk/bin/java`` to exist.
    - ``org.elasticsearch.bootstrap.Elasticsearch`` to be in java's classpath.

- Emscripten is required for generating tree-sitter WASM module. The following
  commands need to be executed for the setup:

  .. code-block:: shell

     cd /opt && git clone https://github.com/emscripten-core/emsdk.git && cd emsdk && \
     ./emsdk install latest && ./emsdk activate latest
     PATH="${PATH}:/opt/emsdk/upstream/emscripten"


  **Note:** If emsdk isn't found in the PATH, the tree-sitter cli automatically pulls `emscripten/emsdk` image from docker hub when `make ts-build-wasm` or `make ts-build` is used.


Make targets
------------

Below is the list of available make targets that can be executed from the root
directory of swh-search in order to build and/or execute the swh-search under
various configurations:

* **ts-install**: Install node_modules and emscripten SDK required for
  TreeSitter

* **ts-generate**: Generate parser files(C and JSON) from the grammar

* **ts-repl**: Starts a web based playground for the TreeSitter grammar. It's
  the recommended way for developing TreeSitter grammar.

* **ts-dev**: Parse the `query_language/sample_query` and print the
  corresponding syntax expression along with the start and end positions of all
  the nodes.

* **ts-dev sanitize=1**: Same as **ts-dev** but without start and end position
  of the nodes. This format is expected by TreeSitter's native test command.
  `sanitize=1` cleans the output of **ts-dev** using `sed` to achieve the
  desired format.

* **ts-test**: executes TreeSitter's native tests

* **ts-build-so**: Generates `swh_ql.so` file from the previously generated
  parser using py-tree-sitter

* **ts-build-so**: Generates `swh_ql.wasm` file from the previously generated
  parser using emscripten

* **ts-build**: Executes both **ts-build-so** and **ts-build-so**
