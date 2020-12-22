swh-search
==========

Search service for the Software Heritage archive.

It is similar to swh-storage in what it contains,
but provides different ways to query it: while swh-storage is mostly
a key-value store that returns an object from a primary key,
swh-search is focused on reverse indices, to allow finding objects that
match some criteria; for example full-text search.

Currently uses ElasticSearch, and provides only origin search (by URL and metadata)

# Dependencies

Python tests for this module include tests that cannot be run without a local
ElasticSearch instance, so you need the ElasticSearch server executable on your
machine (no need to have a running ElasticSearch server).

## Debian-like host

The elasticsearch package is required. As it's not part of debian-stable,
[another debian repository is required to be
configured](https://www.elastic.co/guide/en/elasticsearch/reference/current/deb.html#deb-repo)

## Non Debian-like host

The tests expect:
- `/usr/share/elasticsearch/jdk/bin/java` to exist.
- `org.elasticsearch.bootstrap.Elasticsearch` to be in java's classpath.
