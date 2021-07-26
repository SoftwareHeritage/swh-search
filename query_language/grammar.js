// Copyright (C) 2019-2021  The Software Heritage developers
// See the AUTHORS file at the top-level directory of this distribution
// License: GNU General Public License version 3, or any later version
// See top-level LICENSE file for more information


const PRECEDENCE = {
    or: 2,
    and: 3,
    bracket: 4,
}

module.exports = grammar({
    name: 'swh_search_ql',

    rules: {
        query: $ => seq($.filters, optional($.sortBy) ,optional($.limit)),

        filters: $ => choice(
            prec.left(PRECEDENCE.and,
                seq(
                    field('left', $.filters),
                    field('operator', $.and),
                    field('right', $.filters),
                )
            ),
            prec.left(PRECEDENCE.or,
                seq(
                    field('left', $.filters),
                    field('operator', $.or),
                    field('right', $.filters),
                )
            ),
            prec.left(PRECEDENCE.bracket,
                seq("(", $.filters, ")"),
            ),
            $.filter
        ),

        sortBy: $ => seq($.sortByField, $.sortByOp, $.sortByVal),
        sortByField: $ => token('sort_by'),
        sortByOp: $ => $.equalOp,
        sortByVal: $ => createArray(optionalWrapWith($.sortByOptions, ["'", '"'])),
        sortByOptions: $ => seq(optional(token.immediate('-')) ,choice(
            'visits',
            'last_visit',
            'last_eventful_visit',
            'last_revision',
            'last_release',
            'created',
            'modified',
            'published'
        )),

        limit: $ => seq('limit', $.equalOp, $.number),

        filter: $ => choice(
            $.patternFilter,
            $.booleanFilter,
            $.numericFilter,
            $.boundedListFilter,
            $.unboundedListFilter,
            $.dateFilter
        ),

        patternFilter: $ => seq($.patternField, $.patternOp, $.patternVal),
        patternField: $ => token(choice('origin', 'metadata')),
        patternOp: $ => $.equalOp,
        patternVal: $ => $.string,

        booleanFilter: $ => seq($.booleanField, $.booleanOp, $.booleanVal),
        booleanField: $ => token(choice('visited')),
        booleanOp: $ => $.equalOp,
        booleanVal: $ => choice($.booleanTrue, $.booleanFalse),

        numericFilter: $ => seq($.numericField, $.numericOp, $.numberVal),
        numericField: $ => token(choice('visits')),
        numericOp: $ => $.rangeOp,
        numberVal: $ => $.number,

        boundedListFilter: $ => choice($.visitTypeFilter),

        visitTypeFilter: $ => seq($.visitTypeField, $.visitTypeOp, $.visitTypeVal),
        visitTypeField: $ => token(choice('visit_type')),
        visitTypeOp: $ => $.equalOp,
        visitTypeVal: $ => createArray(optionalWrapWith($.visitTypeOptions, ["'", '"'])),
        visitTypeOptions: $ => choice(
            "any",
            "cran",
            "deb",
            "deposit",
            "ftp",
            "hg",
            "git",
            "nixguix",
            "npm",
            "pypi",
            "svn",
            "tar"
        ), // TODO: fetch this list dynamically from other swh services?

        sortBy: $ => seq($.sortByField, $.sortByOp, $.sortByVal),
        sortByField: $ => token(choice('sort_by')),
        sortByOp: $ => $.equalOp,
        sortByVal: $ => createArray(optionalWrapWith($.sortByOptions, ["'", '"'])),
        sortByOptions: $ => seq(
            optional(token.immediate('-')),
            choice(
            'visits',
            'last_visit',
            'last_eventful_visit',
            'last_revision',
            'last_release',
            'created',
            'modified',
            'published'
        )),

        unboundedListFilter: $ => seq($.listField, $.listOp, $.listVal),
        listField: $ => token(choice('language', 'license', 'keyword')),
        listOp: $ => $.choiceOp,
        listVal: $ => createArray($.string),


        dateFilter: $ => seq($.dateField, $.dateOp, $.dateVal),
        dateField: $ => token(choice(
            'last_visit',
            'last_eventful_visit',
            'last_revision',
            'last_release',
            'created',
            'modified',
            'published'
        )),
        dateOp: $ => $.rangeOp,
        dateVal: $ => $.isoDateTime,

        limit: $ => seq('limit', $.equalOp, $.number),


        rangeOp: $ => token(choice('<', '<=', '=', '!=', '>=', '>')),
        equalOp: $ => token('='),
        choiceOp: $ => token(choice('in', 'not in')),

        isoDateTime: $ => /\d{4}[-]\d{2}[-]\d{2}(\s|T)*(\d{2}:\d{2}(:\d{2})?)?(Z)?/,

        string: $ => choice(wrapWith($.stringContent, ["'", '"']), $.singleWord),
        number: $ => /\d+/,
        booleanTrue: $ => "true",
        booleanFalse: $ => "false",

        or: $ => "or",
        and: $ => "and",

        stringContent: $ => repeat1(choice(
            token.immediate(/[^\\"\n]+/),
            $.escape_sequence
        )),
        singleWord: $ => /[^\s"'\[\]\(\),]+/,
        escape_sequence: $ => token.immediate(seq(
            '\\',
            /(\"|\'|\\|\/|b|n|r|t|u)/
        )),

    }
});


function joinBySep1(rule, sep) {
    // At least one repetition of the rule separated by `sep`
    return seq(rule, repeat(seq(sep, optional(rule))))
}

function joinBySep(rule, sep = ",") {
    // Any number of repetitions of the rule separated by `sep`
    return optional(joinBySep1(rule, sep))
}

function createArray(rule) {
    // An array having `rule` as its member
    return seq(
        "[",
        joinBySep(
            field('array_member', rule),
            ","
        ),
        "]"
    )
}

function wrapWith(rule, wrappers = ["'", '"']) {
    // The rule must be wrapped with one of the wrappers
    const wrappedRules = wrappers.map(wrapper => seq(wrapper, rule, wrapper))
    return choice(...wrappedRules)
}

function optionalWrapWith(rule, wrappers = ["'", '"']) {
    // The rule may or may not be wrapped with the wrappers
    return choice(wrapWith(rule, wrappers), rule)
}
