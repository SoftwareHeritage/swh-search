swh-search
==========

Search service for the Software Heritage archive.

Currently uses ElasticSearch, and provides only origin search (by URL and metadata)

# Dependencies

Python tests for this module include tests that cannot be run without a local
ElasticSearch instance, so you need the ElasticSearch server executable on your
machine (no need to have a running ElasticSearch server).

## Debian-like host

The following instructions is enough:
```
sudo apt install elasticsearch
```


## Non Debian-like host

The tests expect:
- `/usr/share/elasticsearch/jdk/bin/java` to exist.
- `org.elasticsearch.bootstrap.Elasticsearch` to be in java's classpath.
