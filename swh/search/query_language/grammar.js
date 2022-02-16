// Copyright (C) 2021  The Software Heritage developers
// See the AUTHORS file at the top-level directory of this distribution
// License: GNU General Public License version 3, or any later version
// See top-level LICENSE file for more information

const { visitTypeField, sortByField, limitField } = require("./tokens.js");
const {
    patternFields,
    booleanFields,
    numericFields,
    listFields,
    dateFields
} = require("./tokens.js");
const { equalOp, containOp, rangeOp, choiceOp } = require("./tokens.js");
const { sortByOptions, visitTypeOptions } = require("./tokens.js");
const { OR, AND, TRUE, FALSE } = require("./tokens.js");

const PRECEDENCE = {
    or: 2,
    and: 3,
    bracket: 4,
}

module.exports = grammar({
    name: 'swh_search_ql',

    rules: {
        query: $ => seq(
            $.filters,
            optional(seq(
                optional($.and),
                choice(
                    seq($.sortBy, optional($.and), optional($.limit)),
                    seq($.limit, optional($.and), optional($.sortBy)),
                ),
            ))
        ),

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

        sortBy: $ => annotateFilter($.sortByField, $.sortByOp, $.sortByVal),
        sortByField: $ => token(sortByField),
        sortByOp: $ => $.equalOp,
        sortByVal: $ => createArray(optionalWrapWith($.sortByOptions, ["'", '"'])),
        sortByOptions: $ => seq(
            optional('-'),
            choice(...sortByOptions)
        ),

        limit: $ => annotateFilter($.limitField, $.equalOp, $.number),
        limitField: $ => token(limitField),

        filter: $ => field('category', choice(
            $.patternFilter,
            $.booleanFilter,
            $.numericFilter,
            $.boundedListFilter,
            $.unboundedListFilter,
            $.dateFilter
        )),

        patternFilter: $ => annotateFilter($.patternField, $.patternOp, $.patternVal),
        patternField: $ => token(choice(...patternFields)),
        patternOp: $ => $.containOp,
        patternVal: $ => $.string,

        booleanFilter: $ => annotateFilter($.booleanField, $.booleanOp, $.booleanVal),
        booleanField: $ => token(choice(...booleanFields)),
        booleanOp: $ => $.equalOp,
        booleanVal: $ => choice($.booleanTrue, $.booleanFalse),

        numericFilter: $ => annotateFilter($.numericField, $.numericOp, $.numberVal),
        numericField: $ => token(choice(...numericFields)),
        numericOp: $ => $.rangeOp,
        numberVal: $ => $.number,

        // Array members must be from the given options
        boundedListFilter: $ => choice($.visitTypeFilter),

        visitTypeFilter: $ => annotateFilter($.visitTypeField, $.visitTypeOp, $.visitTypeVal),
        visitTypeField: $ => token(visitTypeField),
        visitTypeOp: $ => $.equalOp,
        visitTypeVal: $ => createArray(optionalWrapWith($.visitTypeOptions, ["'", '"'])),
        visitTypeOptions: $ => choice(...visitTypeOptions),
        // TODO: fetch visitTypeOptions choices dynamically from other swh services?

        // Array members can be any string
        unboundedListFilter: $ => annotateFilter($.listField, $.listOp, $.listVal),
        listField: $ => token(choice(...listFields)),
        listOp: $ => $.choiceOp,
        listVal: $ => createArray($.string),

        dateFilter: $ => annotateFilter($.dateField, $.dateOp, $.dateVal),
        dateField: $ => token(choice(...dateFields)),
        dateOp: $ => $.rangeOp,
        dateVal: $ => $.isoDateTime,

        rangeOp: $ => token(choice(...rangeOp)),
        equalOp: $ => token(choice(...equalOp)),
        containOp: $ => token(choice(...containOp)),
        choiceOp: $ => token(choice(...choiceOp)),

        isoDateTime: $ => {
            const dateRegex = (/\d{4}[-]\d{2}[-]\d{2}/).source
            const dateTimeSepRegex = (/(\s|T)*/).source
            const timeRegex = (/\d{2}:\d{2}(:\d{2}(\.\d{6})?)?/).source
            const timezoneRegex = (/\+\d{2}:\d{2}|Z/).source
            return new RegExp(`${dateRegex}(${dateTimeSepRegex}${timeRegex}(${timezoneRegex})?)?`)
        },

        string: $ => choice(wrapWith($.stringContent, ["'", '"']), $.singleWord),
        number: $ => /\d+/,
        booleanTrue: $ => TRUE,
        booleanFalse: $ => FALSE,

        or: $ => OR,
        and: $ => AND,

        singleWord: $ => /[^\s"'\[\]\(\),]+/,

        // Based on tree-sitter-json grammar:
        stringContent: $ => repeat1(choice(
            token.immediate(/[^\\'"\n]+/),
            $.escape_sequence
        )),
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

function annotateFilter(filterField, filterOp, filterVal) {
    return seq(
        field('field', filterField),
        field('op', filterOp),
        field('value', filterVal)
    );
}
