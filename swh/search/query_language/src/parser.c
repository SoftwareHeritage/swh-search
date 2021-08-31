#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 126
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 83
#define ALIAS_COUNT 0
#define TOKEN_COUNT 49
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 8
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 9

enum {
  anon_sym_LPAREN = 1,
  anon_sym_RPAREN = 2,
  sym_sortByField = 3,
  anon_sym_LBRACK = 4,
  anon_sym_SQUOTE = 5,
  anon_sym_DQUOTE = 6,
  anon_sym_COMMA = 7,
  anon_sym_RBRACK = 8,
  anon_sym_DASH = 9,
  anon_sym_visits = 10,
  anon_sym_last_visit = 11,
  anon_sym_last_eventful_visit = 12,
  anon_sym_last_revision = 13,
  anon_sym_last_release = 14,
  anon_sym_created = 15,
  anon_sym_modified = 16,
  anon_sym_published = 17,
  sym_limitField = 18,
  sym_patternField = 19,
  sym_booleanField = 20,
  sym_numericField = 21,
  sym_visitTypeField = 22,
  anon_sym_any = 23,
  anon_sym_cran = 24,
  anon_sym_deb = 25,
  anon_sym_deposit = 26,
  anon_sym_ftp = 27,
  anon_sym_hg = 28,
  anon_sym_git = 29,
  anon_sym_nixguix = 30,
  anon_sym_npm = 31,
  anon_sym_pypi = 32,
  anon_sym_svn = 33,
  anon_sym_tar = 34,
  sym_listField = 35,
  sym_dateField = 36,
  sym_rangeOp = 37,
  sym_equalOp = 38,
  sym_choiceOp = 39,
  sym_isoDateTime = 40,
  sym_number = 41,
  sym_booleanTrue = 42,
  sym_booleanFalse = 43,
  sym_or = 44,
  sym_and = 45,
  sym_singleWord = 46,
  aux_sym_stringContent_token1 = 47,
  sym_escape_sequence = 48,
  sym_query = 49,
  sym_filters = 50,
  sym_sortBy = 51,
  sym_sortByOp = 52,
  sym_sortByVal = 53,
  sym_sortByOptions = 54,
  sym_limit = 55,
  sym_filter = 56,
  sym_patternFilter = 57,
  sym_patternOp = 58,
  sym_patternVal = 59,
  sym_booleanFilter = 60,
  sym_booleanOp = 61,
  sym_booleanVal = 62,
  sym_numericFilter = 63,
  sym_numericOp = 64,
  sym_numberVal = 65,
  sym_boundedListFilter = 66,
  sym_visitTypeFilter = 67,
  sym_visitTypeOp = 68,
  sym_visitTypeVal = 69,
  sym_visitTypeOptions = 70,
  sym_unboundedListFilter = 71,
  sym_listOp = 72,
  sym_listVal = 73,
  sym_dateFilter = 74,
  sym_dateOp = 75,
  sym_dateVal = 76,
  sym_string = 77,
  sym_stringContent = 78,
  aux_sym_sortByVal_repeat1 = 79,
  aux_sym_visitTypeVal_repeat1 = 80,
  aux_sym_listVal_repeat1 = 81,
  aux_sym_stringContent_repeat1 = 82,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_sortByField] = "sortByField",
  [anon_sym_LBRACK] = "[",
  [anon_sym_SQUOTE] = "'",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACK] = "]",
  [anon_sym_DASH] = "-",
  [anon_sym_visits] = "visits",
  [anon_sym_last_visit] = "last_visit",
  [anon_sym_last_eventful_visit] = "last_eventful_visit",
  [anon_sym_last_revision] = "last_revision",
  [anon_sym_last_release] = "last_release",
  [anon_sym_created] = "created",
  [anon_sym_modified] = "modified",
  [anon_sym_published] = "published",
  [sym_limitField] = "limitField",
  [sym_patternField] = "patternField",
  [sym_booleanField] = "booleanField",
  [sym_numericField] = "numericField",
  [sym_visitTypeField] = "visitTypeField",
  [anon_sym_any] = "any",
  [anon_sym_cran] = "cran",
  [anon_sym_deb] = "deb",
  [anon_sym_deposit] = "deposit",
  [anon_sym_ftp] = "ftp",
  [anon_sym_hg] = "hg",
  [anon_sym_git] = "git",
  [anon_sym_nixguix] = "nixguix",
  [anon_sym_npm] = "npm",
  [anon_sym_pypi] = "pypi",
  [anon_sym_svn] = "svn",
  [anon_sym_tar] = "tar",
  [sym_listField] = "listField",
  [sym_dateField] = "dateField",
  [sym_rangeOp] = "rangeOp",
  [sym_equalOp] = "equalOp",
  [sym_choiceOp] = "choiceOp",
  [sym_isoDateTime] = "isoDateTime",
  [sym_number] = "number",
  [sym_booleanTrue] = "booleanTrue",
  [sym_booleanFalse] = "booleanFalse",
  [sym_or] = "or",
  [sym_and] = "and",
  [sym_singleWord] = "singleWord",
  [aux_sym_stringContent_token1] = "stringContent_token1",
  [sym_escape_sequence] = "escape_sequence",
  [sym_query] = "query",
  [sym_filters] = "filters",
  [sym_sortBy] = "sortBy",
  [sym_sortByOp] = "sortByOp",
  [sym_sortByVal] = "sortByVal",
  [sym_sortByOptions] = "sortByOptions",
  [sym_limit] = "limit",
  [sym_filter] = "filter",
  [sym_patternFilter] = "patternFilter",
  [sym_patternOp] = "patternOp",
  [sym_patternVal] = "patternVal",
  [sym_booleanFilter] = "booleanFilter",
  [sym_booleanOp] = "booleanOp",
  [sym_booleanVal] = "booleanVal",
  [sym_numericFilter] = "numericFilter",
  [sym_numericOp] = "numericOp",
  [sym_numberVal] = "numberVal",
  [sym_boundedListFilter] = "boundedListFilter",
  [sym_visitTypeFilter] = "visitTypeFilter",
  [sym_visitTypeOp] = "visitTypeOp",
  [sym_visitTypeVal] = "visitTypeVal",
  [sym_visitTypeOptions] = "visitTypeOptions",
  [sym_unboundedListFilter] = "unboundedListFilter",
  [sym_listOp] = "listOp",
  [sym_listVal] = "listVal",
  [sym_dateFilter] = "dateFilter",
  [sym_dateOp] = "dateOp",
  [sym_dateVal] = "dateVal",
  [sym_string] = "string",
  [sym_stringContent] = "stringContent",
  [aux_sym_sortByVal_repeat1] = "sortByVal_repeat1",
  [aux_sym_visitTypeVal_repeat1] = "visitTypeVal_repeat1",
  [aux_sym_listVal_repeat1] = "listVal_repeat1",
  [aux_sym_stringContent_repeat1] = "stringContent_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_sortByField] = sym_sortByField,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_visits] = anon_sym_visits,
  [anon_sym_last_visit] = anon_sym_last_visit,
  [anon_sym_last_eventful_visit] = anon_sym_last_eventful_visit,
  [anon_sym_last_revision] = anon_sym_last_revision,
  [anon_sym_last_release] = anon_sym_last_release,
  [anon_sym_created] = anon_sym_created,
  [anon_sym_modified] = anon_sym_modified,
  [anon_sym_published] = anon_sym_published,
  [sym_limitField] = sym_limitField,
  [sym_patternField] = sym_patternField,
  [sym_booleanField] = sym_booleanField,
  [sym_numericField] = sym_numericField,
  [sym_visitTypeField] = sym_visitTypeField,
  [anon_sym_any] = anon_sym_any,
  [anon_sym_cran] = anon_sym_cran,
  [anon_sym_deb] = anon_sym_deb,
  [anon_sym_deposit] = anon_sym_deposit,
  [anon_sym_ftp] = anon_sym_ftp,
  [anon_sym_hg] = anon_sym_hg,
  [anon_sym_git] = anon_sym_git,
  [anon_sym_nixguix] = anon_sym_nixguix,
  [anon_sym_npm] = anon_sym_npm,
  [anon_sym_pypi] = anon_sym_pypi,
  [anon_sym_svn] = anon_sym_svn,
  [anon_sym_tar] = anon_sym_tar,
  [sym_listField] = sym_listField,
  [sym_dateField] = sym_dateField,
  [sym_rangeOp] = sym_rangeOp,
  [sym_equalOp] = sym_equalOp,
  [sym_choiceOp] = sym_choiceOp,
  [sym_isoDateTime] = sym_isoDateTime,
  [sym_number] = sym_number,
  [sym_booleanTrue] = sym_booleanTrue,
  [sym_booleanFalse] = sym_booleanFalse,
  [sym_or] = sym_or,
  [sym_and] = sym_and,
  [sym_singleWord] = sym_singleWord,
  [aux_sym_stringContent_token1] = aux_sym_stringContent_token1,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_query] = sym_query,
  [sym_filters] = sym_filters,
  [sym_sortBy] = sym_sortBy,
  [sym_sortByOp] = sym_sortByOp,
  [sym_sortByVal] = sym_sortByVal,
  [sym_sortByOptions] = sym_sortByOptions,
  [sym_limit] = sym_limit,
  [sym_filter] = sym_filter,
  [sym_patternFilter] = sym_patternFilter,
  [sym_patternOp] = sym_patternOp,
  [sym_patternVal] = sym_patternVal,
  [sym_booleanFilter] = sym_booleanFilter,
  [sym_booleanOp] = sym_booleanOp,
  [sym_booleanVal] = sym_booleanVal,
  [sym_numericFilter] = sym_numericFilter,
  [sym_numericOp] = sym_numericOp,
  [sym_numberVal] = sym_numberVal,
  [sym_boundedListFilter] = sym_boundedListFilter,
  [sym_visitTypeFilter] = sym_visitTypeFilter,
  [sym_visitTypeOp] = sym_visitTypeOp,
  [sym_visitTypeVal] = sym_visitTypeVal,
  [sym_visitTypeOptions] = sym_visitTypeOptions,
  [sym_unboundedListFilter] = sym_unboundedListFilter,
  [sym_listOp] = sym_listOp,
  [sym_listVal] = sym_listVal,
  [sym_dateFilter] = sym_dateFilter,
  [sym_dateOp] = sym_dateOp,
  [sym_dateVal] = sym_dateVal,
  [sym_string] = sym_string,
  [sym_stringContent] = sym_stringContent,
  [aux_sym_sortByVal_repeat1] = aux_sym_sortByVal_repeat1,
  [aux_sym_visitTypeVal_repeat1] = aux_sym_visitTypeVal_repeat1,
  [aux_sym_listVal_repeat1] = aux_sym_listVal_repeat1,
  [aux_sym_stringContent_repeat1] = aux_sym_stringContent_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_sortByField] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_visits] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_last_visit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_last_eventful_visit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_last_revision] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_last_release] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_created] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_modified] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_published] = {
    .visible = true,
    .named = false,
  },
  [sym_limitField] = {
    .visible = true,
    .named = true,
  },
  [sym_patternField] = {
    .visible = true,
    .named = true,
  },
  [sym_booleanField] = {
    .visible = true,
    .named = true,
  },
  [sym_numericField] = {
    .visible = true,
    .named = true,
  },
  [sym_visitTypeField] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_any] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cran] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_deb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_deposit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ftp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_hg] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_git] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nixguix] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_npm] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pypi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_svn] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tar] = {
    .visible = true,
    .named = false,
  },
  [sym_listField] = {
    .visible = true,
    .named = true,
  },
  [sym_dateField] = {
    .visible = true,
    .named = true,
  },
  [sym_rangeOp] = {
    .visible = true,
    .named = true,
  },
  [sym_equalOp] = {
    .visible = true,
    .named = true,
  },
  [sym_choiceOp] = {
    .visible = true,
    .named = true,
  },
  [sym_isoDateTime] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_booleanTrue] = {
    .visible = true,
    .named = true,
  },
  [sym_booleanFalse] = {
    .visible = true,
    .named = true,
  },
  [sym_or] = {
    .visible = true,
    .named = true,
  },
  [sym_and] = {
    .visible = true,
    .named = true,
  },
  [sym_singleWord] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_stringContent_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_query] = {
    .visible = true,
    .named = true,
  },
  [sym_filters] = {
    .visible = true,
    .named = true,
  },
  [sym_sortBy] = {
    .visible = true,
    .named = true,
  },
  [sym_sortByOp] = {
    .visible = true,
    .named = true,
  },
  [sym_sortByVal] = {
    .visible = true,
    .named = true,
  },
  [sym_sortByOptions] = {
    .visible = true,
    .named = true,
  },
  [sym_limit] = {
    .visible = true,
    .named = true,
  },
  [sym_filter] = {
    .visible = true,
    .named = true,
  },
  [sym_patternFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_patternOp] = {
    .visible = true,
    .named = true,
  },
  [sym_patternVal] = {
    .visible = true,
    .named = true,
  },
  [sym_booleanFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_booleanOp] = {
    .visible = true,
    .named = true,
  },
  [sym_booleanVal] = {
    .visible = true,
    .named = true,
  },
  [sym_numericFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_numericOp] = {
    .visible = true,
    .named = true,
  },
  [sym_numberVal] = {
    .visible = true,
    .named = true,
  },
  [sym_boundedListFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_visitTypeFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_visitTypeOp] = {
    .visible = true,
    .named = true,
  },
  [sym_visitTypeVal] = {
    .visible = true,
    .named = true,
  },
  [sym_visitTypeOptions] = {
    .visible = true,
    .named = true,
  },
  [sym_unboundedListFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_listOp] = {
    .visible = true,
    .named = true,
  },
  [sym_listVal] = {
    .visible = true,
    .named = true,
  },
  [sym_dateFilter] = {
    .visible = true,
    .named = true,
  },
  [sym_dateOp] = {
    .visible = true,
    .named = true,
  },
  [sym_dateVal] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_stringContent] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_sortByVal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_visitTypeVal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_listVal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_stringContent_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_array_member = 1,
  field_category = 2,
  field_field = 3,
  field_left = 4,
  field_op = 5,
  field_operator = 6,
  field_right = 7,
  field_value = 8,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_array_member] = "array_member",
  [field_category] = "category",
  [field_field] = "field",
  [field_left] = "left",
  [field_op] = "op",
  [field_operator] = "operator",
  [field_right] = "right",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 3},
  [3] = {.index = 4, .length = 3},
  [4] = {.index = 7, .length = 1},
  [5] = {.index = 8, .length = 2},
  [6] = {.index = 10, .length = 2},
  [7] = {.index = 12, .length = 3},
  [8] = {.index = 15, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_category, 0},
  [1] =
    {field_field, 0},
    {field_op, 1},
    {field_value, 2},
  [4] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
  [7] =
    {field_array_member, 1},
  [8] =
    {field_array_member, 1},
    {field_array_member, 2, .inherited = true},
  [10] =
    {field_array_member, 0, .inherited = true},
    {field_array_member, 1, .inherited = true},
  [12] =
    {field_array_member, 1},
    {field_array_member, 2},
    {field_array_member, 3},
  [15] =
    {field_array_member, 1},
    {field_array_member, 2},
    {field_array_member, 3},
    {field_array_member, 4, .inherited = true},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static inline bool sym_singleWord_character_set_1(int32_t c) {
  return (c < '"'
    ? (c < '\r'
      ? (c < '\t'
        ? c == 0
        : c <= '\n')
      : (c <= '\r' || c == ' '))
    : (c <= '"' || (c < '['
      ? (c < ','
        ? (c >= '\'' && c <= ')')
        : c <= ',')
      : (c <= '[' || c == ']'))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(236);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(242);
      if (lookahead == '\'') ADVANCE(241);
      if (lookahead == '(') ADVANCE(237);
      if (lookahead == ')') ADVANCE(238);
      if (lookahead == ',') ADVANCE(243);
      if (lookahead == '-') ADVANCE(245);
      if (lookahead == '<') ADVANCE(274);
      if (lookahead == '=') ADVANCE(273);
      if (lookahead == '>') ADVANCE(274);
      if (lookahead == '[') ADVANCE(240);
      if (lookahead == '\\') ADVANCE(211);
      if (lookahead == ']') ADVANCE(244);
      if (lookahead == 'a') ADVANCE(124);
      if (lookahead == 'c') ADVANCE(147);
      if (lookahead == 'd') ADVANCE(48);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'g') ADVANCE(84);
      if (lookahead == 'h') ADVANCE(77);
      if (lookahead == 'i') ADVANCE(125);
      if (lookahead == 'k') ADVANCE(49);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(59);
      if (lookahead == 'n') ADVANCE(85);
      if (lookahead == 'o') ADVANCE(148);
      if (lookahead == 'p') ADVANCE(194);
      if (lookahead == 's') ADVANCE(139);
      if (lookahead == 't') ADVANCE(23);
      if (lookahead == 'v') ADVANCE(86);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(234)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(285);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(4)
      if (lookahead == '"') ADVANCE(242);
      if (lookahead == '\'') ADVANCE(241);
      if (lookahead == '\\') ADVANCE(211);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(293);
      if (lookahead != 0) ADVANCE(294);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(89);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(242);
      if (lookahead == '\'') ADVANCE(241);
      if (lookahead == ',') ADVANCE(243);
      if (lookahead == ']') ADVANCE(244);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '[') ADVANCE(292);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(242);
      if (lookahead == '\'') ADVANCE(241);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      END_STATE();
    case 5:
      if (lookahead == '(') ADVANCE(237);
      if (lookahead == '=') ADVANCE(275);
      if (lookahead == 'c') ADVANCE(154);
      if (lookahead == 'k') ADVANCE(49);
      if (lookahead == 'l') ADVANCE(31);
      if (lookahead == 'm') ADVANCE(60);
      if (lookahead == 'o') ADVANCE(153);
      if (lookahead == 'p') ADVANCE(199);
      if (lookahead == 's') ADVANCE(138);
      if (lookahead == 'v') ADVANCE(112);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(286);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(219);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(220);
      END_STATE();
    case 8:
      if (lookahead == ':') ADVANCE(221);
      END_STATE();
    case 9:
      if (lookahead == ':') ADVANCE(222);
      END_STATE();
    case 10:
      if (lookahead == '=') ADVANCE(273);
      END_STATE();
    case 11:
      if (lookahead == '_') ADVANCE(53);
      END_STATE();
    case 12:
      if (lookahead == '_') ADVANCE(34);
      END_STATE();
    case 13:
      if (lookahead == '_') ADVANCE(202);
      END_STATE();
    case 14:
      if (lookahead == '_') ADVANCE(186);
      if (lookahead == 'e') ADVANCE(41);
      if (lookahead == 's') ADVANCE(246);
      END_STATE();
    case 15:
      if (lookahead == '_') ADVANCE(186);
      if (lookahead == 'e') ADVANCE(41);
      if (lookahead == 's') ADVANCE(257);
      END_STATE();
    case 16:
      if (lookahead == '_') ADVANCE(72);
      END_STATE();
    case 17:
      if (lookahead == '_') ADVANCE(203);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(115);
      if (lookahead == 't') ADVANCE(144);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(131);
      if (lookahead == 'i') ADVANCE(36);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(255);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(46);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(127);
      if (lookahead == 'e') ADVANCE(26);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(149);
      if (lookahead == 'r') ADVANCE(197);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(81);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(158);
      if (lookahead == 'i') ADVANCE(123);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(188);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(190);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(187);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(162);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(163);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(132);
      if (lookahead == 'i') ADVANCE(36);
      END_STATE();
    case 32:
      if (lookahead == 'b') ADVANCE(261);
      if (lookahead == 'p') ADVANCE(143);
      END_STATE();
    case 33:
      if (lookahead == 'b') ADVANCE(117);
      END_STATE();
    case 34:
      if (lookahead == 'b') ADVANCE(209);
      END_STATE();
    case 35:
      if (lookahead == 'b') ADVANCE(119);
      END_STATE();
    case 36:
      if (lookahead == 'c') ADVANCE(62);
      if (lookahead == 'm') ADVANCE(96);
      END_STATE();
    case 37:
      if (lookahead == 'd') ADVANCE(291);
      END_STATE();
    case 38:
      if (lookahead == 'd') ADVANCE(291);
      if (lookahead == 'y') ADVANCE(259);
      END_STATE();
    case 39:
      if (lookahead == 'd') ADVANCE(251);
      END_STATE();
    case 40:
      if (lookahead == 'd') ADVANCE(271);
      END_STATE();
    case 41:
      if (lookahead == 'd') ADVANCE(256);
      END_STATE();
    case 42:
      if (lookahead == 'd') ADVANCE(252);
      END_STATE();
    case 43:
      if (lookahead == 'd') ADVANCE(253);
      END_STATE();
    case 44:
      if (lookahead == 'd') ADVANCE(272);
      END_STATE();
    case 45:
      if (lookahead == 'd') ADVANCE(87);
      END_STATE();
    case 46:
      if (lookahead == 'd') ADVANCE(28);
      END_STATE();
    case 47:
      if (lookahead == 'd') ADVANCE(108);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(208);
      END_STATE();
    case 50:
      if (lookahead == 'e') ADVANCE(26);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(287);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(288);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(201);
      if (lookahead == 'r') ADVANCE(55);
      if (lookahead == 'v') ADVANCE(110);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(271);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(118);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(258);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(250);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(272);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(182);
      if (lookahead == 'o') ADVANCE(45);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(182);
      if (lookahead == 'o') ADVANCE(47);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(39);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(135);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(29);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(42);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(134);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(44);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(27);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(30);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(120);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(136);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(204);
      if (lookahead == 'r') ADVANCE(70);
      if (lookahead == 'v') ADVANCE(113);
      END_STATE();
    case 73:
      if (lookahead == 'f') ADVANCE(195);
      END_STATE();
    case 74:
      if (lookahead == 'f') ADVANCE(98);
      END_STATE();
    case 75:
      if (lookahead == 'f') ADVANCE(102);
      END_STATE();
    case 76:
      if (lookahead == 'f') ADVANCE(200);
      END_STATE();
    case 77:
      if (lookahead == 'g') ADVANCE(264);
      END_STATE();
    case 78:
      if (lookahead == 'g') ADVANCE(196);
      END_STATE();
    case 79:
      if (lookahead == 'g') ADVANCE(198);
      END_STATE();
    case 80:
      if (lookahead == 'g') ADVANCE(95);
      END_STATE();
    case 81:
      if (lookahead == 'g') ADVANCE(54);
      END_STATE();
    case 82:
      if (lookahead == 'h') ADVANCE(66);
      END_STATE();
    case 83:
      if (lookahead == 'h') ADVANCE(67);
      END_STATE();
    case 84:
      if (lookahead == 'i') ADVANCE(173);
      END_STATE();
    case 85:
      if (lookahead == 'i') ADVANCE(207);
      if (lookahead == 'o') ADVANCE(174);
      if (lookahead == 'p') ADVANCE(122);
      END_STATE();
    case 86:
      if (lookahead == 'i') ADVANCE(166);
      END_STATE();
    case 87:
      if (lookahead == 'i') ADVANCE(74);
      END_STATE();
    case 88:
      if (lookahead == 'i') ADVANCE(268);
      END_STATE();
    case 89:
      if (lookahead == 'i') ADVANCE(125);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(206);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(80);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(156);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(141);
      END_STATE();
    case 94:
      if (lookahead == 'i') ADVANCE(161);
      END_STATE();
    case 95:
      if (lookahead == 'i') ADVANCE(128);
      END_STATE();
    case 96:
      if (lookahead == 'i') ADVANCE(176);
      END_STATE();
    case 97:
      if (lookahead == 'i') ADVANCE(177);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(64);
      END_STATE();
    case 99:
      if (lookahead == 'i') ADVANCE(178);
      END_STATE();
    case 100:
      if (lookahead == 'i') ADVANCE(179);
      END_STATE();
    case 101:
      if (lookahead == 'i') ADVANCE(180);
      END_STATE();
    case 102:
      if (lookahead == 'i') ADVANCE(67);
      END_STATE();
    case 103:
      if (lookahead == 'i') ADVANCE(185);
      END_STATE();
    case 104:
      if (lookahead == 'i') ADVANCE(181);
      END_STATE();
    case 105:
      if (lookahead == 'i') ADVANCE(189);
      END_STATE();
    case 106:
      if (lookahead == 'i') ADVANCE(164);
      END_STATE();
    case 107:
      if (lookahead == 'i') ADVANCE(142);
      END_STATE();
    case 108:
      if (lookahead == 'i') ADVANCE(75);
      END_STATE();
    case 109:
      if (lookahead == 'i') ADVANCE(165);
      END_STATE();
    case 110:
      if (lookahead == 'i') ADVANCE(168);
      END_STATE();
    case 111:
      if (lookahead == 'i') ADVANCE(169);
      END_STATE();
    case 112:
      if (lookahead == 'i') ADVANCE(170);
      END_STATE();
    case 113:
      if (lookahead == 'i') ADVANCE(171);
      END_STATE();
    case 114:
      if (lookahead == 'i') ADVANCE(172);
      END_STATE();
    case 115:
      if (lookahead == 'l') ADVANCE(159);
      END_STATE();
    case 116:
      if (lookahead == 'l') ADVANCE(13);
      END_STATE();
    case 117:
      if (lookahead == 'l') ADVANCE(92);
      END_STATE();
    case 118:
      if (lookahead == 'l') ADVANCE(63);
      if (lookahead == 'v') ADVANCE(94);
      END_STATE();
    case 119:
      if (lookahead == 'l') ADVANCE(106);
      END_STATE();
    case 120:
      if (lookahead == 'l') ADVANCE(69);
      if (lookahead == 'v') ADVANCE(109);
      END_STATE();
    case 121:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 122:
      if (lookahead == 'm') ADVANCE(267);
      END_STATE();
    case 123:
      if (lookahead == 'm') ADVANCE(96);
      END_STATE();
    case 124:
      if (lookahead == 'n') ADVANCE(38);
      END_STATE();
    case 125:
      if (lookahead == 'n') ADVANCE(276);
      END_STATE();
    case 126:
      if (lookahead == 'n') ADVANCE(269);
      END_STATE();
    case 127:
      if (lookahead == 'n') ADVANCE(260);
      END_STATE();
    case 128:
      if (lookahead == 'n') ADVANCE(255);
      END_STATE();
    case 129:
      if (lookahead == 'n') ADVANCE(249);
      END_STATE();
    case 130:
      if (lookahead == 'n') ADVANCE(272);
      END_STATE();
    case 131:
      if (lookahead == 'n') ADVANCE(78);
      if (lookahead == 's') ADVANCE(175);
      END_STATE();
    case 132:
      if (lookahead == 'n') ADVANCE(78);
      if (lookahead == 's') ADVANCE(191);
      END_STATE();
    case 133:
      if (lookahead == 'n') ADVANCE(37);
      END_STATE();
    case 134:
      if (lookahead == 'n') ADVANCE(184);
      END_STATE();
    case 135:
      if (lookahead == 'n') ADVANCE(160);
      END_STATE();
    case 136:
      if (lookahead == 'n') ADVANCE(192);
      END_STATE();
    case 137:
      if (lookahead == 'o') ADVANCE(45);
      END_STATE();
    case 138:
      if (lookahead == 'o') ADVANCE(152);
      END_STATE();
    case 139:
      if (lookahead == 'o') ADVANCE(152);
      if (lookahead == 'v') ADVANCE(126);
      END_STATE();
    case 140:
      if (lookahead == 'o') ADVANCE(151);
      END_STATE();
    case 141:
      if (lookahead == 'o') ADVANCE(129);
      END_STATE();
    case 142:
      if (lookahead == 'o') ADVANCE(130);
      END_STATE();
    case 143:
      if (lookahead == 'o') ADVANCE(167);
      END_STATE();
    case 144:
      if (lookahead == 'p') ADVANCE(263);
      END_STATE();
    case 145:
      if (lookahead == 'p') ADVANCE(88);
      END_STATE();
    case 146:
      if (lookahead == 'p') ADVANCE(56);
      END_STATE();
    case 147:
      if (lookahead == 'r') ADVANCE(22);
      END_STATE();
    case 148:
      if (lookahead == 'r') ADVANCE(290);
      END_STATE();
    case 149:
      if (lookahead == 'r') ADVANCE(270);
      END_STATE();
    case 150:
      if (lookahead == 'r') ADVANCE(289);
      END_STATE();
    case 151:
      if (lookahead == 'r') ADVANCE(40);
      END_STATE();
    case 152:
      if (lookahead == 'r') ADVANCE(183);
      END_STATE();
    case 153:
      if (lookahead == 'r') ADVANCE(91);
      END_STATE();
    case 154:
      if (lookahead == 'r') ADVANCE(68);
      END_STATE();
    case 155:
      if (lookahead == 'r') ADVANCE(50);
      END_STATE();
    case 156:
      if (lookahead == 's') ADVANCE(82);
      END_STATE();
    case 157:
      if (lookahead == 's') ADVANCE(246);
      END_STATE();
    case 158:
      if (lookahead == 's') ADVANCE(175);
      END_STATE();
    case 159:
      if (lookahead == 's') ADVANCE(52);
      END_STATE();
    case 160:
      if (lookahead == 's') ADVANCE(54);
      END_STATE();
    case 161:
      if (lookahead == 's') ADVANCE(93);
      END_STATE();
    case 162:
      if (lookahead == 's') ADVANCE(57);
      END_STATE();
    case 163:
      if (lookahead == 's') ADVANCE(58);
      END_STATE();
    case 164:
      if (lookahead == 's') ADVANCE(83);
      END_STATE();
    case 165:
      if (lookahead == 's') ADVANCE(107);
      END_STATE();
    case 166:
      if (lookahead == 's') ADVANCE(97);
      END_STATE();
    case 167:
      if (lookahead == 's') ADVANCE(99);
      END_STATE();
    case 168:
      if (lookahead == 's') ADVANCE(100);
      END_STATE();
    case 169:
      if (lookahead == 's') ADVANCE(101);
      END_STATE();
    case 170:
      if (lookahead == 's') ADVANCE(103);
      END_STATE();
    case 171:
      if (lookahead == 's') ADVANCE(104);
      END_STATE();
    case 172:
      if (lookahead == 's') ADVANCE(105);
      END_STATE();
    case 173:
      if (lookahead == 't') ADVANCE(265);
      END_STATE();
    case 174:
      if (lookahead == 't') ADVANCE(2);
      END_STATE();
    case 175:
      if (lookahead == 't') ADVANCE(11);
      END_STATE();
    case 176:
      if (lookahead == 't') ADVANCE(254);
      END_STATE();
    case 177:
      if (lookahead == 't') ADVANCE(14);
      END_STATE();
    case 178:
      if (lookahead == 't') ADVANCE(262);
      END_STATE();
    case 179:
      if (lookahead == 't') ADVANCE(247);
      END_STATE();
    case 180:
      if (lookahead == 't') ADVANCE(248);
      END_STATE();
    case 181:
      if (lookahead == 't') ADVANCE(272);
      END_STATE();
    case 182:
      if (lookahead == 't') ADVANCE(21);
      END_STATE();
    case 183:
      if (lookahead == 't') ADVANCE(12);
      END_STATE();
    case 184:
      if (lookahead == 't') ADVANCE(73);
      END_STATE();
    case 185:
      if (lookahead == 't') ADVANCE(15);
      END_STATE();
    case 186:
      if (lookahead == 't') ADVANCE(210);
      END_STATE();
    case 187:
      if (lookahead == 't') ADVANCE(20);
      END_STATE();
    case 188:
      if (lookahead == 't') ADVANCE(61);
      END_STATE();
    case 189:
      if (lookahead == 't') ADVANCE(157);
      END_STATE();
    case 190:
      if (lookahead == 't') ADVANCE(67);
      END_STATE();
    case 191:
      if (lookahead == 't') ADVANCE(16);
      END_STATE();
    case 192:
      if (lookahead == 't') ADVANCE(76);
      END_STATE();
    case 193:
      if (lookahead == 'u') ADVANCE(33);
      END_STATE();
    case 194:
      if (lookahead == 'u') ADVANCE(33);
      if (lookahead == 'y') ADVANCE(145);
      END_STATE();
    case 195:
      if (lookahead == 'u') ADVANCE(116);
      END_STATE();
    case 196:
      if (lookahead == 'u') ADVANCE(24);
      END_STATE();
    case 197:
      if (lookahead == 'u') ADVANCE(51);
      END_STATE();
    case 198:
      if (lookahead == 'u') ADVANCE(90);
      END_STATE();
    case 199:
      if (lookahead == 'u') ADVANCE(35);
      END_STATE();
    case 200:
      if (lookahead == 'u') ADVANCE(121);
      END_STATE();
    case 201:
      if (lookahead == 'v') ADVANCE(65);
      END_STATE();
    case 202:
      if (lookahead == 'v') ADVANCE(111);
      END_STATE();
    case 203:
      if (lookahead == 'v') ADVANCE(113);
      END_STATE();
    case 204:
      if (lookahead == 'v') ADVANCE(71);
      END_STATE();
    case 205:
      if (lookahead == 'w') ADVANCE(140);
      END_STATE();
    case 206:
      if (lookahead == 'x') ADVANCE(266);
      END_STATE();
    case 207:
      if (lookahead == 'x') ADVANCE(79);
      END_STATE();
    case 208:
      if (lookahead == 'y') ADVANCE(205);
      END_STATE();
    case 209:
      if (lookahead == 'y') ADVANCE(239);
      END_STATE();
    case 210:
      if (lookahead == 'y') ADVANCE(146);
      END_STATE();
    case 211:
      if (lookahead == '"' ||
          lookahead == '\'' ||
          lookahead == '/' ||
          lookahead == '\\' ||
          lookahead == 'b' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't' ||
          lookahead == 'u') ADVANCE(295);
      END_STATE();
    case 212:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(7);
      END_STATE();
    case 213:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(281);
      END_STATE();
    case 214:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(277);
      END_STATE();
    case 215:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 216:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(279);
      END_STATE();
    case 217:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(278);
      END_STATE();
    case 218:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(280);
      END_STATE();
    case 219:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(212);
      END_STATE();
    case 220:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(213);
      END_STATE();
    case 221:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(216);
      END_STATE();
    case 222:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(214);
      END_STATE();
    case 223:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(217);
      END_STATE();
    case 224:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(218);
      END_STATE();
    case 225:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 226:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(225);
      END_STATE();
    case 227:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(224);
      END_STATE();
    case 228:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(226);
      END_STATE();
    case 229:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 230:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(229);
      END_STATE();
    case 231:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(227);
      END_STATE();
    case 232:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(231);
      END_STATE();
    case 233:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(232);
      END_STATE();
    case 234:
      if (eof) ADVANCE(236);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(242);
      if (lookahead == '\'') ADVANCE(241);
      if (lookahead == '(') ADVANCE(237);
      if (lookahead == ')') ADVANCE(238);
      if (lookahead == ',') ADVANCE(243);
      if (lookahead == '-') ADVANCE(245);
      if (lookahead == '<') ADVANCE(274);
      if (lookahead == '=') ADVANCE(273);
      if (lookahead == '>') ADVANCE(274);
      if (lookahead == '[') ADVANCE(240);
      if (lookahead == ']') ADVANCE(244);
      if (lookahead == 'a') ADVANCE(124);
      if (lookahead == 'c') ADVANCE(147);
      if (lookahead == 'd') ADVANCE(48);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'g') ADVANCE(84);
      if (lookahead == 'h') ADVANCE(77);
      if (lookahead == 'i') ADVANCE(125);
      if (lookahead == 'k') ADVANCE(49);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(59);
      if (lookahead == 'n') ADVANCE(85);
      if (lookahead == 'o') ADVANCE(148);
      if (lookahead == 'p') ADVANCE(194);
      if (lookahead == 's') ADVANCE(139);
      if (lookahead == 't') ADVANCE(23);
      if (lookahead == 'v') ADVANCE(86);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(234)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(285);
      END_STATE();
    case 235:
      if (eof) ADVANCE(236);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(242);
      if (lookahead == '\'') ADVANCE(241);
      if (lookahead == ')') ADVANCE(238);
      if (lookahead == ',') ADVANCE(243);
      if (lookahead == '-') ADVANCE(245);
      if (lookahead == '<') ADVANCE(274);
      if (lookahead == '=') ADVANCE(273);
      if (lookahead == '>') ADVANCE(274);
      if (lookahead == ']') ADVANCE(244);
      if (lookahead == 'a') ADVANCE(133);
      if (lookahead == 'c') ADVANCE(155);
      if (lookahead == 'l') ADVANCE(25);
      if (lookahead == 'm') ADVANCE(137);
      if (lookahead == 'o') ADVANCE(150);
      if (lookahead == 'p') ADVANCE(193);
      if (lookahead == 's') ADVANCE(138);
      if (lookahead == 'v') ADVANCE(114);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(235)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(228);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_sortByField);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(anon_sym_visits);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_last_visit);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_last_eventful_visit);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(anon_sym_last_revision);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_last_release);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_created);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_modified);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(anon_sym_published);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym_limitField);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(sym_patternField);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(sym_booleanField);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(sym_numericField);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(sym_visitTypeField);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(anon_sym_any);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(anon_sym_cran);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(anon_sym_deb);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(anon_sym_deposit);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(anon_sym_ftp);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(anon_sym_hg);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(anon_sym_git);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_nixguix);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_npm);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_pypi);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_svn);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(anon_sym_tar);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(sym_listField);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(sym_dateField);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(sym_rangeOp);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(sym_rangeOp);
      if (lookahead == '=') ADVANCE(273);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(sym_equalOp);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(sym_choiceOp);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(sym_isoDateTime);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(230);
      if (lookahead == '.') ADVANCE(233);
      if (lookahead == 'Z') ADVANCE(277);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(230);
      if (lookahead == ':') ADVANCE(223);
      if (lookahead == 'Z') ADVANCE(277);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(230);
      if (lookahead == 'Z') ADVANCE(277);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(230);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(281);
      if (lookahead == 'Z') ADVANCE(277);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(215);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(219);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(286);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(282);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(283);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(284);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(286);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_booleanTrue);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_booleanFalse);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_or);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_or);
      if (lookahead == 'i') ADVANCE(80);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_and);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_singleWord);
      if (!sym_singleWord_character_set_1(lookahead)) ADVANCE(292);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(293);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 5},
  [2] = {.lex_state = 5},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 5},
  [7] = {.lex_state = 5},
  [8] = {.lex_state = 235},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 235},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 235},
  [15] = {.lex_state = 235},
  [16] = {.lex_state = 235},
  [17] = {.lex_state = 235},
  [18] = {.lex_state = 235},
  [19] = {.lex_state = 235},
  [20] = {.lex_state = 235},
  [21] = {.lex_state = 235},
  [22] = {.lex_state = 235},
  [23] = {.lex_state = 235},
  [24] = {.lex_state = 235},
  [25] = {.lex_state = 235},
  [26] = {.lex_state = 235},
  [27] = {.lex_state = 235},
  [28] = {.lex_state = 235},
  [29] = {.lex_state = 235},
  [30] = {.lex_state = 235},
  [31] = {.lex_state = 235},
  [32] = {.lex_state = 235},
  [33] = {.lex_state = 235},
  [34] = {.lex_state = 235},
  [35] = {.lex_state = 235},
  [36] = {.lex_state = 235},
  [37] = {.lex_state = 235},
  [38] = {.lex_state = 235},
  [39] = {.lex_state = 235},
  [40] = {.lex_state = 235},
  [41] = {.lex_state = 235},
  [42] = {.lex_state = 235},
  [43] = {.lex_state = 235},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 235},
  [46] = {.lex_state = 235},
  [47] = {.lex_state = 3},
  [48] = {.lex_state = 3},
  [49] = {.lex_state = 1},
  [50] = {.lex_state = 1},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 1},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 1},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 235},
  [81] = {.lex_state = 3},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 5},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 5},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 5},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 5},
  [101] = {.lex_state = 235},
  [102] = {.lex_state = 5},
  [103] = {.lex_state = 235},
  [104] = {.lex_state = 235},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 235},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 5},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 5},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 5},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_sortByField] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_visits] = ACTIONS(1),
    [anon_sym_last_visit] = ACTIONS(1),
    [anon_sym_last_eventful_visit] = ACTIONS(1),
    [anon_sym_last_revision] = ACTIONS(1),
    [anon_sym_last_release] = ACTIONS(1),
    [anon_sym_created] = ACTIONS(1),
    [anon_sym_modified] = ACTIONS(1),
    [anon_sym_published] = ACTIONS(1),
    [sym_limitField] = ACTIONS(1),
    [sym_patternField] = ACTIONS(1),
    [sym_booleanField] = ACTIONS(1),
    [sym_numericField] = ACTIONS(1),
    [sym_visitTypeField] = ACTIONS(1),
    [anon_sym_any] = ACTIONS(1),
    [anon_sym_cran] = ACTIONS(1),
    [anon_sym_deb] = ACTIONS(1),
    [anon_sym_deposit] = ACTIONS(1),
    [anon_sym_ftp] = ACTIONS(1),
    [anon_sym_hg] = ACTIONS(1),
    [anon_sym_git] = ACTIONS(1),
    [anon_sym_nixguix] = ACTIONS(1),
    [anon_sym_npm] = ACTIONS(1),
    [anon_sym_pypi] = ACTIONS(1),
    [anon_sym_svn] = ACTIONS(1),
    [anon_sym_tar] = ACTIONS(1),
    [sym_listField] = ACTIONS(1),
    [sym_dateField] = ACTIONS(1),
    [sym_rangeOp] = ACTIONS(1),
    [sym_equalOp] = ACTIONS(1),
    [sym_choiceOp] = ACTIONS(1),
    [sym_isoDateTime] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_booleanTrue] = ACTIONS(1),
    [sym_booleanFalse] = ACTIONS(1),
    [sym_or] = ACTIONS(1),
    [sym_and] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
  },
  [1] = {
    [sym_query] = STATE(116),
    [sym_filters] = STATE(21),
    [sym_filter] = STATE(31),
    [sym_patternFilter] = STATE(30),
    [sym_booleanFilter] = STATE(30),
    [sym_numericFilter] = STATE(30),
    [sym_boundedListFilter] = STATE(30),
    [sym_visitTypeFilter] = STATE(29),
    [sym_unboundedListFilter] = STATE(30),
    [sym_dateFilter] = STATE(30),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_patternField] = ACTIONS(5),
    [sym_booleanField] = ACTIONS(7),
    [sym_numericField] = ACTIONS(9),
    [sym_visitTypeField] = ACTIONS(11),
    [sym_listField] = ACTIONS(13),
    [sym_dateField] = ACTIONS(15),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 15,
    ACTIONS(3), 1,
      anon_sym_LPAREN,
    ACTIONS(5), 1,
      sym_patternField,
    ACTIONS(7), 1,
      sym_booleanField,
    ACTIONS(9), 1,
      sym_numericField,
    ACTIONS(11), 1,
      sym_visitTypeField,
    ACTIONS(13), 1,
      sym_listField,
    ACTIONS(15), 1,
      sym_dateField,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(19), 1,
      sym_limitField,
    STATE(25), 1,
      sym_filters,
    STATE(29), 1,
      sym_visitTypeFilter,
    STATE(31), 1,
      sym_filter,
    STATE(55), 1,
      sym_sortBy,
    STATE(56), 1,
      sym_limit,
    STATE(30), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [51] = 5,
    ACTIONS(21), 1,
      anon_sym_SQUOTE,
    ACTIONS(23), 1,
      anon_sym_DQUOTE,
    STATE(96), 1,
      sym_visitTypeOptions,
    ACTIONS(25), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
    ACTIONS(27), 12,
      anon_sym_any,
      anon_sym_cran,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_pypi,
      anon_sym_svn,
      anon_sym_tar,
  [79] = 11,
    ACTIONS(3), 1,
      anon_sym_LPAREN,
    ACTIONS(5), 1,
      sym_patternField,
    ACTIONS(7), 1,
      sym_booleanField,
    ACTIONS(9), 1,
      sym_numericField,
    ACTIONS(11), 1,
      sym_visitTypeField,
    ACTIONS(13), 1,
      sym_listField,
    ACTIONS(15), 1,
      sym_dateField,
    STATE(29), 1,
      sym_visitTypeFilter,
    STATE(31), 1,
      sym_filter,
    STATE(80), 1,
      sym_filters,
    STATE(30), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [118] = 5,
    ACTIONS(29), 1,
      anon_sym_SQUOTE,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      sym_visitTypeOptions,
    ACTIONS(27), 12,
      anon_sym_any,
      anon_sym_cran,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_pypi,
      anon_sym_svn,
      anon_sym_tar,
  [145] = 11,
    ACTIONS(3), 1,
      anon_sym_LPAREN,
    ACTIONS(5), 1,
      sym_patternField,
    ACTIONS(7), 1,
      sym_booleanField,
    ACTIONS(9), 1,
      sym_numericField,
    ACTIONS(11), 1,
      sym_visitTypeField,
    ACTIONS(13), 1,
      sym_listField,
    ACTIONS(15), 1,
      sym_dateField,
    STATE(25), 1,
      sym_filters,
    STATE(29), 1,
      sym_visitTypeFilter,
    STATE(31), 1,
      sym_filter,
    STATE(30), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [184] = 11,
    ACTIONS(3), 1,
      anon_sym_LPAREN,
    ACTIONS(5), 1,
      sym_patternField,
    ACTIONS(7), 1,
      sym_booleanField,
    ACTIONS(9), 1,
      sym_numericField,
    ACTIONS(11), 1,
      sym_visitTypeField,
    ACTIONS(13), 1,
      sym_listField,
    ACTIONS(15), 1,
      sym_dateField,
    STATE(29), 1,
      sym_visitTypeFilter,
    STATE(31), 1,
      sym_filter,
    STATE(35), 1,
      sym_filters,
    STATE(30), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [223] = 6,
    ACTIONS(35), 1,
      anon_sym_SQUOTE,
    ACTIONS(37), 1,
      anon_sym_DQUOTE,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(88), 1,
      sym_sortByOptions,
    ACTIONS(39), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
    ACTIONS(43), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [250] = 2,
    STATE(106), 1,
      sym_visitTypeOptions,
    ACTIONS(27), 12,
      anon_sym_any,
      anon_sym_cran,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_pypi,
      anon_sym_svn,
      anon_sym_tar,
  [268] = 2,
    STATE(114), 1,
      sym_visitTypeOptions,
    ACTIONS(27), 12,
      anon_sym_any,
      anon_sym_cran,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_pypi,
      anon_sym_svn,
      anon_sym_tar,
  [286] = 6,
    ACTIONS(41), 1,
      anon_sym_DASH,
    ACTIONS(45), 1,
      anon_sym_SQUOTE,
    ACTIONS(47), 1,
      anon_sym_DQUOTE,
    ACTIONS(49), 1,
      anon_sym_RBRACK,
    STATE(86), 1,
      sym_sortByOptions,
    ACTIONS(43), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [312] = 2,
    STATE(111), 1,
      sym_visitTypeOptions,
    ACTIONS(27), 12,
      anon_sym_any,
      anon_sym_cran,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_pypi,
      anon_sym_svn,
      anon_sym_tar,
  [330] = 2,
    STATE(110), 1,
      sym_visitTypeOptions,
    ACTIONS(27), 12,
      anon_sym_any,
      anon_sym_cran,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_pypi,
      anon_sym_svn,
      anon_sym_tar,
  [348] = 3,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(108), 1,
      sym_sortByOptions,
    ACTIONS(43), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [365] = 3,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(123), 1,
      sym_sortByOptions,
    ACTIONS(43), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [382] = 3,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(122), 1,
      sym_sortByOptions,
    ACTIONS(43), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [399] = 3,
    ACTIONS(41), 1,
      anon_sym_DASH,
    STATE(113), 1,
      sym_sortByOptions,
    ACTIONS(43), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [416] = 1,
    ACTIONS(51), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [427] = 1,
    ACTIONS(53), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [438] = 1,
    ACTIONS(55), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [449] = 7,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(57), 1,
      ts_builtin_sym_end,
    ACTIONS(59), 1,
      sym_or,
    ACTIONS(61), 1,
      sym_and,
    STATE(51), 1,
      sym_sortBy,
    STATE(57), 1,
      sym_limit,
  [471] = 1,
    ACTIONS(63), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [480] = 1,
    ACTIONS(65), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [489] = 1,
    ACTIONS(67), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [498] = 1,
    ACTIONS(69), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [507] = 1,
    ACTIONS(71), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [516] = 1,
    ACTIONS(73), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [525] = 1,
    ACTIONS(75), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [534] = 1,
    ACTIONS(77), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [543] = 1,
    ACTIONS(79), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [552] = 1,
    ACTIONS(81), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [561] = 1,
    ACTIONS(83), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [570] = 1,
    ACTIONS(85), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [579] = 1,
    ACTIONS(87), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [588] = 2,
    ACTIONS(89), 1,
      sym_and,
    ACTIONS(69), 5,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
  [599] = 1,
    ACTIONS(91), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [608] = 1,
    ACTIONS(93), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [617] = 1,
    ACTIONS(95), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [626] = 1,
    ACTIONS(97), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [635] = 1,
    ACTIONS(99), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [644] = 1,
    ACTIONS(101), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [653] = 1,
    ACTIONS(103), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [662] = 1,
    ACTIONS(105), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [671] = 5,
    ACTIONS(107), 1,
      anon_sym_SQUOTE,
    ACTIONS(109), 1,
      anon_sym_DQUOTE,
    ACTIONS(113), 1,
      sym_singleWord,
    STATE(99), 1,
      sym_string,
    ACTIONS(111), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [688] = 1,
    ACTIONS(115), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [697] = 1,
    ACTIONS(117), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [706] = 5,
    ACTIONS(107), 1,
      anon_sym_SQUOTE,
    ACTIONS(109), 1,
      anon_sym_DQUOTE,
    ACTIONS(113), 1,
      sym_singleWord,
    ACTIONS(119), 1,
      anon_sym_RBRACK,
    STATE(69), 1,
      sym_string,
  [722] = 5,
    ACTIONS(107), 1,
      anon_sym_SQUOTE,
    ACTIONS(109), 1,
      anon_sym_DQUOTE,
    ACTIONS(113), 1,
      sym_singleWord,
    STATE(38), 1,
      sym_patternVal,
    STATE(39), 1,
      sym_string,
  [738] = 3,
    STATE(50), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(121), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(123), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [750] = 3,
    STATE(50), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(125), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(127), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [762] = 4,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(130), 1,
      ts_builtin_sym_end,
    ACTIONS(132), 1,
      sym_and,
    STATE(119), 1,
      sym_limit,
  [775] = 3,
    STATE(49), 1,
      aux_sym_stringContent_repeat1,
    STATE(124), 1,
      sym_stringContent,
    ACTIONS(134), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [786] = 1,
    ACTIONS(136), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [793] = 1,
    ACTIONS(138), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [800] = 4,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(142), 1,
      sym_and,
    STATE(109), 1,
      sym_limit,
  [813] = 4,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(144), 1,
      sym_and,
    STATE(109), 1,
      sym_sortBy,
  [826] = 4,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(130), 1,
      ts_builtin_sym_end,
    ACTIONS(146), 1,
      sym_and,
    STATE(119), 1,
      sym_sortBy,
  [839] = 1,
    ACTIONS(148), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [846] = 3,
    STATE(49), 1,
      aux_sym_stringContent_repeat1,
    STATE(120), 1,
      sym_stringContent,
    ACTIONS(134), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [857] = 2,
    STATE(41), 1,
      sym_booleanVal,
    ACTIONS(150), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [865] = 3,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(152), 1,
      ts_builtin_sym_end,
    STATE(112), 1,
      sym_limit,
  [875] = 1,
    ACTIONS(154), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [881] = 3,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    STATE(109), 1,
      sym_sortBy,
  [891] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(158), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [901] = 1,
    ACTIONS(160), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [907] = 3,
    ACTIONS(162), 1,
      anon_sym_COMMA,
    ACTIONS(165), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [917] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(169), 1,
      anon_sym_RBRACK,
    STATE(73), 1,
      aux_sym_visitTypeVal_repeat1,
  [927] = 1,
    ACTIONS(171), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [933] = 3,
    ACTIONS(173), 1,
      anon_sym_COMMA,
    ACTIONS(175), 1,
      anon_sym_RBRACK,
    STATE(85), 1,
      aux_sym_listVal_repeat1,
  [943] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(177), 1,
      anon_sym_RBRACK,
    STATE(64), 1,
      aux_sym_sortByVal_repeat1,
  [953] = 1,
    ACTIONS(179), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [959] = 1,
    ACTIONS(181), 3,
      ts_builtin_sym_end,
      sym_sortByField,
      sym_and,
  [965] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(183), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [975] = 3,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    STATE(109), 1,
      sym_limit,
  [985] = 3,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(152), 1,
      ts_builtin_sym_end,
    STATE(112), 1,
      sym_sortBy,
  [995] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(185), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [1005] = 1,
    ACTIONS(187), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1011] = 3,
    ACTIONS(189), 1,
      anon_sym_COMMA,
    ACTIONS(192), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      aux_sym_listVal_repeat1,
  [1021] = 3,
    ACTIONS(194), 1,
      anon_sym_COMMA,
    ACTIONS(197), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1031] = 3,
    ACTIONS(59), 1,
      sym_or,
    ACTIONS(89), 1,
      sym_and,
    ACTIONS(199), 1,
      anon_sym_RPAREN,
  [1041] = 1,
    ACTIONS(201), 3,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym_singleWord,
  [1047] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(203), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1057] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(205), 1,
      anon_sym_RBRACK,
    STATE(82), 1,
      aux_sym_visitTypeVal_repeat1,
  [1067] = 1,
    ACTIONS(207), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1073] = 3,
    ACTIONS(173), 1,
      anon_sym_COMMA,
    ACTIONS(209), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      aux_sym_listVal_repeat1,
  [1083] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(211), 1,
      anon_sym_RBRACK,
    STATE(76), 1,
      aux_sym_sortByVal_repeat1,
  [1093] = 2,
    ACTIONS(213), 1,
      sym_choiceOp,
    STATE(98), 1,
      sym_listOp,
  [1100] = 1,
    ACTIONS(215), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1105] = 2,
    ACTIONS(217), 1,
      sym_number,
    STATE(43), 1,
      sym_numberVal,
  [1112] = 1,
    ACTIONS(219), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1117] = 2,
    ACTIONS(221), 1,
      sym_equalOp,
    STATE(48), 1,
      sym_patternOp,
  [1124] = 2,
    ACTIONS(223), 1,
      anon_sym_LBRACK,
    STATE(71), 1,
      sym_sortByVal,
  [1131] = 1,
    ACTIONS(225), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1136] = 2,
    ACTIONS(227), 1,
      sym_equalOp,
    STATE(60), 1,
      sym_booleanOp,
  [1143] = 2,
    ACTIONS(229), 1,
      anon_sym_LBRACK,
    STATE(45), 1,
      sym_visitTypeVal,
  [1150] = 1,
    ACTIONS(231), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1155] = 1,
    ACTIONS(233), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [1160] = 2,
    ACTIONS(235), 1,
      anon_sym_LBRACK,
    STATE(46), 1,
      sym_listVal,
  [1167] = 1,
    ACTIONS(237), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1172] = 2,
    ACTIONS(239), 1,
      sym_equalOp,
    STATE(92), 1,
      sym_sortByOp,
  [1179] = 2,
    ACTIONS(241), 1,
      sym_rangeOp,
    STATE(89), 1,
      sym_numericOp,
  [1186] = 2,
    ACTIONS(243), 1,
      sym_equalOp,
    STATE(95), 1,
      sym_visitTypeOp,
  [1193] = 2,
    ACTIONS(245), 1,
      sym_isoDateTime,
    STATE(26), 1,
      sym_dateVal,
  [1200] = 2,
    ACTIONS(247), 1,
      sym_rangeOp,
    STATE(103), 1,
      sym_dateOp,
  [1207] = 1,
    ACTIONS(249), 1,
      anon_sym_LBRACK,
  [1211] = 1,
    ACTIONS(251), 1,
      anon_sym_SQUOTE,
  [1215] = 1,
    ACTIONS(253), 1,
      sym_isoDateTime,
  [1219] = 1,
    ACTIONS(255), 1,
      anon_sym_DQUOTE,
  [1223] = 1,
    ACTIONS(152), 1,
      ts_builtin_sym_end,
  [1227] = 1,
    ACTIONS(257), 1,
      anon_sym_SQUOTE,
  [1231] = 1,
    ACTIONS(257), 1,
      anon_sym_DQUOTE,
  [1235] = 1,
    ACTIONS(259), 1,
      ts_builtin_sym_end,
  [1239] = 1,
    ACTIONS(255), 1,
      anon_sym_SQUOTE,
  [1243] = 1,
    ACTIONS(251), 1,
      anon_sym_DQUOTE,
  [1247] = 1,
    ACTIONS(261), 1,
      sym_number,
  [1251] = 1,
    ACTIONS(263), 1,
      ts_builtin_sym_end,
  [1255] = 1,
    ACTIONS(265), 1,
      sym_equalOp,
  [1259] = 1,
    ACTIONS(267), 1,
      anon_sym_LBRACK,
  [1263] = 1,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
  [1267] = 1,
    ACTIONS(269), 1,
      anon_sym_DQUOTE,
  [1271] = 1,
    ACTIONS(271), 1,
      anon_sym_LBRACK,
  [1275] = 1,
    ACTIONS(273), 1,
      anon_sym_SQUOTE,
  [1279] = 1,
    ACTIONS(273), 1,
      anon_sym_DQUOTE,
  [1283] = 1,
    ACTIONS(269), 1,
      anon_sym_SQUOTE,
  [1287] = 1,
    ACTIONS(275), 1,
      sym_number,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 51,
  [SMALL_STATE(4)] = 79,
  [SMALL_STATE(5)] = 118,
  [SMALL_STATE(6)] = 145,
  [SMALL_STATE(7)] = 184,
  [SMALL_STATE(8)] = 223,
  [SMALL_STATE(9)] = 250,
  [SMALL_STATE(10)] = 268,
  [SMALL_STATE(11)] = 286,
  [SMALL_STATE(12)] = 312,
  [SMALL_STATE(13)] = 330,
  [SMALL_STATE(14)] = 348,
  [SMALL_STATE(15)] = 365,
  [SMALL_STATE(16)] = 382,
  [SMALL_STATE(17)] = 399,
  [SMALL_STATE(18)] = 416,
  [SMALL_STATE(19)] = 427,
  [SMALL_STATE(20)] = 438,
  [SMALL_STATE(21)] = 449,
  [SMALL_STATE(22)] = 471,
  [SMALL_STATE(23)] = 480,
  [SMALL_STATE(24)] = 489,
  [SMALL_STATE(25)] = 498,
  [SMALL_STATE(26)] = 507,
  [SMALL_STATE(27)] = 516,
  [SMALL_STATE(28)] = 525,
  [SMALL_STATE(29)] = 534,
  [SMALL_STATE(30)] = 543,
  [SMALL_STATE(31)] = 552,
  [SMALL_STATE(32)] = 561,
  [SMALL_STATE(33)] = 570,
  [SMALL_STATE(34)] = 579,
  [SMALL_STATE(35)] = 588,
  [SMALL_STATE(36)] = 599,
  [SMALL_STATE(37)] = 608,
  [SMALL_STATE(38)] = 617,
  [SMALL_STATE(39)] = 626,
  [SMALL_STATE(40)] = 635,
  [SMALL_STATE(41)] = 644,
  [SMALL_STATE(42)] = 653,
  [SMALL_STATE(43)] = 662,
  [SMALL_STATE(44)] = 671,
  [SMALL_STATE(45)] = 688,
  [SMALL_STATE(46)] = 697,
  [SMALL_STATE(47)] = 706,
  [SMALL_STATE(48)] = 722,
  [SMALL_STATE(49)] = 738,
  [SMALL_STATE(50)] = 750,
  [SMALL_STATE(51)] = 762,
  [SMALL_STATE(52)] = 775,
  [SMALL_STATE(53)] = 786,
  [SMALL_STATE(54)] = 793,
  [SMALL_STATE(55)] = 800,
  [SMALL_STATE(56)] = 813,
  [SMALL_STATE(57)] = 826,
  [SMALL_STATE(58)] = 839,
  [SMALL_STATE(59)] = 846,
  [SMALL_STATE(60)] = 857,
  [SMALL_STATE(61)] = 865,
  [SMALL_STATE(62)] = 875,
  [SMALL_STATE(63)] = 881,
  [SMALL_STATE(64)] = 891,
  [SMALL_STATE(65)] = 901,
  [SMALL_STATE(66)] = 907,
  [SMALL_STATE(67)] = 917,
  [SMALL_STATE(68)] = 927,
  [SMALL_STATE(69)] = 933,
  [SMALL_STATE(70)] = 943,
  [SMALL_STATE(71)] = 953,
  [SMALL_STATE(72)] = 959,
  [SMALL_STATE(73)] = 965,
  [SMALL_STATE(74)] = 975,
  [SMALL_STATE(75)] = 985,
  [SMALL_STATE(76)] = 995,
  [SMALL_STATE(77)] = 1005,
  [SMALL_STATE(78)] = 1011,
  [SMALL_STATE(79)] = 1021,
  [SMALL_STATE(80)] = 1031,
  [SMALL_STATE(81)] = 1041,
  [SMALL_STATE(82)] = 1047,
  [SMALL_STATE(83)] = 1057,
  [SMALL_STATE(84)] = 1067,
  [SMALL_STATE(85)] = 1073,
  [SMALL_STATE(86)] = 1083,
  [SMALL_STATE(87)] = 1093,
  [SMALL_STATE(88)] = 1100,
  [SMALL_STATE(89)] = 1105,
  [SMALL_STATE(90)] = 1112,
  [SMALL_STATE(91)] = 1117,
  [SMALL_STATE(92)] = 1124,
  [SMALL_STATE(93)] = 1131,
  [SMALL_STATE(94)] = 1136,
  [SMALL_STATE(95)] = 1143,
  [SMALL_STATE(96)] = 1150,
  [SMALL_STATE(97)] = 1155,
  [SMALL_STATE(98)] = 1160,
  [SMALL_STATE(99)] = 1167,
  [SMALL_STATE(100)] = 1172,
  [SMALL_STATE(101)] = 1179,
  [SMALL_STATE(102)] = 1186,
  [SMALL_STATE(103)] = 1193,
  [SMALL_STATE(104)] = 1200,
  [SMALL_STATE(105)] = 1207,
  [SMALL_STATE(106)] = 1211,
  [SMALL_STATE(107)] = 1215,
  [SMALL_STATE(108)] = 1219,
  [SMALL_STATE(109)] = 1223,
  [SMALL_STATE(110)] = 1227,
  [SMALL_STATE(111)] = 1231,
  [SMALL_STATE(112)] = 1235,
  [SMALL_STATE(113)] = 1239,
  [SMALL_STATE(114)] = 1243,
  [SMALL_STATE(115)] = 1247,
  [SMALL_STATE(116)] = 1251,
  [SMALL_STATE(117)] = 1255,
  [SMALL_STATE(118)] = 1259,
  [SMALL_STATE(119)] = 1263,
  [SMALL_STATE(120)] = 1267,
  [SMALL_STATE(121)] = 1271,
  [SMALL_STATE(122)] = 1275,
  [SMALL_STATE(123)] = 1279,
  [SMALL_STATE(124)] = 1283,
  [SMALL_STATE(125)] = 1287,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 1),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 1),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 1),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 1),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 4, .production_id = 5),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 5, .production_id = 7),
  [67] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 3, .production_id = 4),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 3, .production_id = 3),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateFilter, 3, .production_id = 2),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 2),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 2),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boundedListFilter, 1),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter, 1, .production_id = 1),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 1),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 3, .production_id = 4),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 3),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 4, .production_id = 5),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 6, .production_id = 8),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateVal, 1),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternFilter, 3, .production_id = 2),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternVal, 1),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanVal, 1),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanFilter, 3, .production_id = 2),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberVal, 1),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numericFilter, 3, .production_id = 2),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 1),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeFilter, 3, .production_id = 2),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unboundedListFilter, 3, .production_id = 2),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [121] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_stringContent, 1),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_stringContent_repeat1, 2),
  [127] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_stringContent_repeat1, 2), SHIFT_REPEAT(50),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOptions, 2),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOptions, 1),
  [140] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeOptions, 1),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 4),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 6, .production_id = 8),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [160] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 5, .production_id = 7),
  [162] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(8),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 4, .production_id = 5),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortBy, 3, .production_id = 2),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit, 3, .production_id = 2),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 3, .production_id = 4),
  [189] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(44),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 2, .production_id = 6),
  [194] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(3),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternOp, 1),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 2),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 4),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 4, .production_id = 7),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 4, .production_id = 7),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 4),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanOp, 1),
  [235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 2, .production_id = 4),
  [239] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [243] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [247] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeOp, 1),
  [251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateOp, 1),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 5),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [263] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listOp, 1),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [271] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOp, 1),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [275] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numericOp, 1),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_swh_search_ql(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
