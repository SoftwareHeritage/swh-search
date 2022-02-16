Search Query Language
=====================


Every query is composed of filters separated by ``and`` or ``or``.
These filters have 3 components in the order : ``Name Operator Value``

Some of the examples are :
    * ``origin : plasma and language in [python] and visits >= 5``
    * ``last_revision > 2020-01-01 and limit = 10``
    * ``last_visit > 2021-01-01 or last_visit < 2020-01-01``
    * ``visited = false and metadata = "kubernetes" or origin : "minikube"``
    * ``keyword in ["orchestration", "kubectl"] and language in ["go", "rust"]``
    * ``(origin : debian or visit_type = ["deb"]) and license in ["GPL-3"]``

**Note**:
    * Whitespaces are optional between the three components of a filter.
    * The conjunction operators have left precedence. Therefore ``foo and bar and baz`` means ``(foo and bar) and baz``
    * ``and`` has higher precedence than ``or``. Therefore ``foo or bar and baz`` means ``foo or (bar and baz)``
    * Precedence can be overridden using parentheses: ``(`` and ``)``. For example, you can override the default precedence in the previous query as: ``(foo or bar) and baz``
    * To actually search for ``and`` or ``or`` as strings, just put them within quotes. Example : ``metadata : "vcs history and metadata"``, or even just ``metadata : "and"`` to search for the string ``and`` in the metadata

The filters have been classified based on the type of value that they expects.


Pattern filters
---------------
Returns origins having the given keywords in their url or intrinsic metadata

    * Name:
        * ``origin``: Keywords from the origin url
        * ``metadata``: Keywords from all the intrinsic metadata fields
    * Operator: ``:``
    * Value: String wrapped in quotation marks(``"`` or ``'``)

**Note:** If a string has no whitespace then the quotation marks become optional.

**Examples:**

    * ``origin : https://github.com/Django/django``
    * ``origin : kubernetes``
    * ``origin : "github python"``
    * ``metadata : orchestration``
    * ``metadata : "javascript language"``

Boolean filters
---------------
Returns origins having their boolean type values equal to given values

    * Name: ``visited`` : Whether the origin has been visited
    * Operator: ``=``
    * Value: ``true`` or ``false``

**Examples:**

    * ``visited = true``
    * ``visited = false``


Numeric filters
---------------
Returns origins having their numeric type values in the given range

    * Name: ``visits`` : Number of visits of an origin
    * Operator: ``<`` ``<=`` ``=`` ``!=`` ``>`` ``>=``
    * Value: Positive integer

**Examples:**


    * ``visits > 2``
    * ``visits = 5``
    * ``visits <= 10``


Un-bounded List filters
-----------------------

Returns origins that satisfy the criteria based on a given list

    * Name:
        * ``language`` : Programming languages used
        * ``license`` : License used
        * ``keyword`` : keywords (often same as tags) or description (includes README) from the metadata
    * Operator: ``in`` ``not in``
    * Value: Array of strings

**Note:**
    * If a string has no whitespace then the quotation marks become optional.

    * The ``keyword`` filter gives more priority to the keywords field of intrinsic metadata than the description field. So origins having the queried term in their intrinsic metadata keyword will appear first.


**Examples:**

    * ``language in [python, js]``
    * ``license in ["GPL 3.0 or later", MIT]``
    * ``keyword in ["Software Heritage", swh]``


Bounded List filters
--------------------

Returns origins that satisfy the criteria based on a list of fixed options

    **visit_type**

    * Name: ``visit_type`` : Returns only origins with at least one of the specified visit types
    * Operator: ``=``
    * Value: Array of the following values

        ``any``
        ``cran``
        ``deb``
        ``deposit``
        ``ftp``
        ``hg``
        ``git``
        ``nixguix``
        ``npm``
        ``pypi``
        ``svn``
        ``tar``

    **sort_by**

    * Name: ``sort_by`` : Sorts origins based on the given list of origin attributes
    * Operator: ``=``
    * Value: Array of the following values

        ``visits``
        ``last_visit``
        ``last_eventful_visit``
        ``last_revision``
        ``last_release``
        ``created``
        ``modified``
        ``published``

**Examples:**


    * ``visit_type = [svn, npm]``
    * ``visit_type = [nixguix, "ftp"]``
    * ``sort_by = ["last_visit", created]``
    * ``sort_by = [visits, modified]``

Date filters
------------

Returns origins having their date type values in the given range

    * Name:

            * ``last_visit`` : Latest visit date
            * ``last_eventful_visit`` : Latest visit date where a new snapshot was detected
            * ``last_revision`` : Latest commit date
            * ``last_release`` : Latest release date
            * ``created`` Creation date
            * ``modified`` Modification date
            * ``published`` Published date

    * Operator: ``<`` ``<=`` ``=`` ``!=`` ``>`` ``>=``
    * Value: Date in ``Standard ISO`` format

    **Note:** The last three date filters are based on metadata that has to be manually entered
    by the repository authors. So they might not be correct or up-to-date.

**Examples:**

    * ``last_visit > 2001-01-01 and last_visit < 2101-01-01``
    * ``last_revision = "2000-01-01 18:35Z"``
    * ``last_release != "2021-07-17T18:35:00Z"``
    * ``created <= "2021-07-17 18:35"``

Limit filter
------------

Limits the number of results to at most N

    * Name: ``limit``
    * Operator: ``=``
    * Value: Positive Integer

**Note:** The default value of the limit is 50

**Examples:**

    * ``limit = 1``
    * ``limit = 15``
