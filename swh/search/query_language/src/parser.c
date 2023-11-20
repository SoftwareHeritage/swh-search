#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 109
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 70
#define ALIAS_COUNT 0
#define TOKEN_COUNT 38
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
  sym_listField = 23,
  sym_dateField = 24,
  sym_rangeOp = 25,
  sym_equalOp = 26,
  sym_containOp = 27,
  sym_choiceOp = 28,
  sym_isoDateTime = 29,
  sym_number = 30,
  sym_booleanTrue = 31,
  sym_booleanFalse = 32,
  sym_or = 33,
  sym_and = 34,
  sym_singleWord = 35,
  aux_sym_stringContent_token1 = 36,
  sym_escape_sequence = 37,
  sym_query = 38,
  sym_filters = 39,
  sym_sortBy = 40,
  sym_sortByOp = 41,
  sym_sortByVal = 42,
  sym_sortByOptions = 43,
  sym_limit = 44,
  sym_filter = 45,
  sym_patternFilter = 46,
  sym_patternOp = 47,
  sym_patternVal = 48,
  sym_booleanFilter = 49,
  sym_booleanOp = 50,
  sym_booleanVal = 51,
  sym_numericFilter = 52,
  sym_numericOp = 53,
  sym_numberVal = 54,
  sym_boundedListFilter = 55,
  sym_visitTypeFilter = 56,
  sym_visitTypeOp = 57,
  sym_visitTypeVal = 58,
  sym_unboundedListFilter = 59,
  sym_listOp = 60,
  sym_listVal = 61,
  sym_dateFilter = 62,
  sym_dateOp = 63,
  sym_dateVal = 64,
  sym_string = 65,
  sym_stringContent = 66,
  aux_sym_sortByVal_repeat1 = 67,
  aux_sym_visitTypeVal_repeat1 = 68,
  aux_sym_stringContent_repeat1 = 69,
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
  [sym_listField] = "listField",
  [sym_dateField] = "dateField",
  [sym_rangeOp] = "rangeOp",
  [sym_equalOp] = "equalOp",
  [sym_containOp] = "containOp",
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
  [sym_listField] = sym_listField,
  [sym_dateField] = sym_dateField,
  [sym_rangeOp] = sym_rangeOp,
  [sym_equalOp] = sym_equalOp,
  [sym_containOp] = sym_containOp,
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
  [sym_containOp] = {
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
      if (eof) ADVANCE(210);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(216);
      if (lookahead == '\'') ADVANCE(215);
      if (lookahead == '(') ADVANCE(211);
      if (lookahead == ')') ADVANCE(212);
      if (lookahead == ',') ADVANCE(217);
      if (lookahead == '-') ADVANCE(219);
      if (lookahead == ':') ADVANCE(238);
      if (lookahead == '<') ADVANCE(236);
      if (lookahead == '=') ADVANCE(235);
      if (lookahead == '>') ADVANCE(236);
      if (lookahead == '[') ADVANCE(214);
      if (lookahead == '\\') ADVANCE(185);
      if (lookahead == ']') ADVANCE(218);
      if (lookahead == 'a') ADVANCE(111);
      if (lookahead == 'c') ADVANCE(130);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'i') ADVANCE(112);
      if (lookahead == 'k') ADVANCE(44);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(45);
      if (lookahead == 'n') ADVANCE(122);
      if (lookahead == 'o') ADVANCE(128);
      if (lookahead == 'p') ADVANCE(170);
      if (lookahead == 's') ADVANCE(123);
      if (lookahead == 't') ADVANCE(131);
      if (lookahead == 'v') ADVANCE(77);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(208)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(248);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(4)
      if (lookahead == '"') ADVANCE(216);
      if (lookahead == '\'') ADVANCE(215);
      if (lookahead == '\\') ADVANCE(185);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(256);
      if (lookahead != 0) ADVANCE(257);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(79);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(216);
      if (lookahead == '\'') ADVANCE(215);
      if (lookahead == ',') ADVANCE(217);
      if (lookahead == ']') ADVANCE(218);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '[') ADVANCE(255);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(216);
      if (lookahead == '\'') ADVANCE(215);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      END_STATE();
    case 5:
      if (lookahead == '(') ADVANCE(211);
      if (lookahead == '=') ADVANCE(237);
      if (lookahead == 'c') ADVANCE(135);
      if (lookahead == 'k') ADVANCE(44);
      if (lookahead == 'l') ADVANCE(29);
      if (lookahead == 'm') ADVANCE(46);
      if (lookahead == 'o') ADVANCE(134);
      if (lookahead == 'p') ADVANCE(174);
      if (lookahead == 's') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(100);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(249);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(193);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(194);
      END_STATE();
    case 8:
      if (lookahead == ':') ADVANCE(195);
      END_STATE();
    case 9:
      if (lookahead == ':') ADVANCE(197);
      END_STATE();
    case 10:
      if (lookahead == '=') ADVANCE(235);
      END_STATE();
    case 11:
      if (lookahead == '_') ADVANCE(49);
      END_STATE();
    case 12:
      if (lookahead == '_') ADVANCE(31);
      END_STATE();
    case 13:
      if (lookahead == '_') ADVANCE(177);
      END_STATE();
    case 14:
      if (lookahead == '_') ADVANCE(163);
      if (lookahead == 'e') ADVANCE(37);
      if (lookahead == 's') ADVANCE(220);
      END_STATE();
    case 15:
      if (lookahead == '_') ADVANCE(163);
      if (lookahead == 'e') ADVANCE(37);
      if (lookahead == 's') ADVANCE(231);
      END_STATE();
    case 16:
      if (lookahead == '_') ADVANCE(67);
      END_STATE();
    case 17:
      if (lookahead == '_') ADVANCE(178);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(103);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(113);
      if (lookahead == 'i') ADVANCE(33);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(229);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(42);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(74);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(138);
      if (lookahead == 'i') ADVANCE(110);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(166);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(165);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(167);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(142);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(143);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(114);
      if (lookahead == 'i') ADVANCE(33);
      END_STATE();
    case 30:
      if (lookahead == 'b') ADVANCE(106);
      END_STATE();
    case 31:
      if (lookahead == 'b') ADVANCE(182);
      END_STATE();
    case 32:
      if (lookahead == 'b') ADVANCE(107);
      END_STATE();
    case 33:
      if (lookahead == 'c') ADVANCE(56);
      if (lookahead == 'm') ADVANCE(84);
      END_STATE();
    case 34:
      if (lookahead == 'd') ADVANCE(254);
      END_STATE();
    case 35:
      if (lookahead == 'd') ADVANCE(225);
      END_STATE();
    case 36:
      if (lookahead == 'd') ADVANCE(233);
      END_STATE();
    case 37:
      if (lookahead == 'd') ADVANCE(230);
      END_STATE();
    case 38:
      if (lookahead == 'd') ADVANCE(226);
      END_STATE();
    case 39:
      if (lookahead == 'd') ADVANCE(227);
      END_STATE();
    case 40:
      if (lookahead == 'd') ADVANCE(234);
      END_STATE();
    case 41:
      if (lookahead == 'd') ADVANCE(78);
      END_STATE();
    case 42:
      if (lookahead == 'd') ADVANCE(25);
      END_STATE();
    case 43:
      if (lookahead == 'd') ADVANCE(98);
      END_STATE();
    case 44:
      if (lookahead == 'e') ADVANCE(181);
      END_STATE();
    case 45:
      if (lookahead == 'e') ADVANCE(162);
      if (lookahead == 'o') ADVANCE(41);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(162);
      if (lookahead == 'o') ADVANCE(43);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(250);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(251);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(176);
      if (lookahead == 'r') ADVANCE(51);
      if (lookahead == 'v') ADVANCE(97);
      END_STATE();
    case 50:
      if (lookahead == 'e') ADVANCE(233);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(105);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(232);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(224);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(234);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(119);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(35);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(118);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(27);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(38);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(39);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(40);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(26);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(28);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(108);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(120);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(179);
      if (lookahead == 'r') ADVANCE(65);
      if (lookahead == 'v') ADVANCE(101);
      END_STATE();
    case 68:
      if (lookahead == 'f') ADVANCE(171);
      END_STATE();
    case 69:
      if (lookahead == 'f') ADVANCE(86);
      END_STATE();
    case 70:
      if (lookahead == 'f') ADVANCE(92);
      END_STATE();
    case 71:
      if (lookahead == 'f') ADVANCE(175);
      END_STATE();
    case 72:
      if (lookahead == 'g') ADVANCE(172);
      END_STATE();
    case 73:
      if (lookahead == 'g') ADVANCE(83);
      END_STATE();
    case 74:
      if (lookahead == 'g') ADVANCE(50);
      END_STATE();
    case 75:
      if (lookahead == 'h') ADVANCE(61);
      END_STATE();
    case 76:
      if (lookahead == 'h') ADVANCE(62);
      END_STATE();
    case 77:
      if (lookahead == 'i') ADVANCE(145);
      END_STATE();
    case 78:
      if (lookahead == 'i') ADVANCE(69);
      END_STATE();
    case 79:
      if (lookahead == 'i') ADVANCE(112);
      END_STATE();
    case 80:
      if (lookahead == 'i') ADVANCE(73);
      END_STATE();
    case 81:
      if (lookahead == 'i') ADVANCE(125);
      END_STATE();
    case 82:
      if (lookahead == 'i') ADVANCE(136);
      END_STATE();
    case 83:
      if (lookahead == 'i') ADVANCE(115);
      END_STATE();
    case 84:
      if (lookahead == 'i') ADVANCE(154);
      END_STATE();
    case 85:
      if (lookahead == 'i') ADVANCE(155);
      END_STATE();
    case 86:
      if (lookahead == 'i') ADVANCE(60);
      END_STATE();
    case 87:
      if (lookahead == 'i') ADVANCE(156);
      END_STATE();
    case 88:
      if (lookahead == 'i') ADVANCE(157);
      END_STATE();
    case 89:
      if (lookahead == 'i') ADVANCE(161);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(158);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(164);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(62);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(140);
      END_STATE();
    case 94:
      if (lookahead == 'i') ADVANCE(126);
      END_STATE();
    case 95:
      if (lookahead == 'i') ADVANCE(144);
      END_STATE();
    case 96:
      if (lookahead == 'i') ADVANCE(146);
      END_STATE();
    case 97:
      if (lookahead == 'i') ADVANCE(147);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(70);
      END_STATE();
    case 99:
      if (lookahead == 'i') ADVANCE(148);
      END_STATE();
    case 100:
      if (lookahead == 'i') ADVANCE(149);
      END_STATE();
    case 101:
      if (lookahead == 'i') ADVANCE(150);
      END_STATE();
    case 102:
      if (lookahead == 'i') ADVANCE(151);
      END_STATE();
    case 103:
      if (lookahead == 'l') ADVANCE(139);
      END_STATE();
    case 104:
      if (lookahead == 'l') ADVANCE(13);
      END_STATE();
    case 105:
      if (lookahead == 'l') ADVANCE(59);
      if (lookahead == 'v') ADVANCE(93);
      END_STATE();
    case 106:
      if (lookahead == 'l') ADVANCE(82);
      END_STATE();
    case 107:
      if (lookahead == 'l') ADVANCE(95);
      END_STATE();
    case 108:
      if (lookahead == 'l') ADVANCE(64);
      if (lookahead == 'v') ADVANCE(96);
      END_STATE();
    case 109:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 110:
      if (lookahead == 'm') ADVANCE(84);
      END_STATE();
    case 111:
      if (lookahead == 'n') ADVANCE(34);
      END_STATE();
    case 112:
      if (lookahead == 'n') ADVANCE(239);
      END_STATE();
    case 113:
      if (lookahead == 'n') ADVANCE(72);
      if (lookahead == 's') ADVANCE(153);
      END_STATE();
    case 114:
      if (lookahead == 'n') ADVANCE(72);
      if (lookahead == 's') ADVANCE(168);
      END_STATE();
    case 115:
      if (lookahead == 'n') ADVANCE(229);
      END_STATE();
    case 116:
      if (lookahead == 'n') ADVANCE(223);
      END_STATE();
    case 117:
      if (lookahead == 'n') ADVANCE(234);
      END_STATE();
    case 118:
      if (lookahead == 'n') ADVANCE(160);
      END_STATE();
    case 119:
      if (lookahead == 'n') ADVANCE(141);
      END_STATE();
    case 120:
      if (lookahead == 'n') ADVANCE(169);
      END_STATE();
    case 121:
      if (lookahead == 'o') ADVANCE(41);
      END_STATE();
    case 122:
      if (lookahead == 'o') ADVANCE(152);
      END_STATE();
    case 123:
      if (lookahead == 'o') ADVANCE(132);
      END_STATE();
    case 124:
      if (lookahead == 'o') ADVANCE(133);
      END_STATE();
    case 125:
      if (lookahead == 'o') ADVANCE(116);
      END_STATE();
    case 126:
      if (lookahead == 'o') ADVANCE(117);
      END_STATE();
    case 127:
      if (lookahead == 'p') ADVANCE(52);
      END_STATE();
    case 128:
      if (lookahead == 'r') ADVANCE(253);
      END_STATE();
    case 129:
      if (lookahead == 'r') ADVANCE(252);
      END_STATE();
    case 130:
      if (lookahead == 'r') ADVANCE(55);
      END_STATE();
    case 131:
      if (lookahead == 'r') ADVANCE(173);
      END_STATE();
    case 132:
      if (lookahead == 'r') ADVANCE(159);
      END_STATE();
    case 133:
      if (lookahead == 'r') ADVANCE(36);
      END_STATE();
    case 134:
      if (lookahead == 'r') ADVANCE(80);
      END_STATE();
    case 135:
      if (lookahead == 'r') ADVANCE(63);
      END_STATE();
    case 136:
      if (lookahead == 's') ADVANCE(75);
      END_STATE();
    case 137:
      if (lookahead == 's') ADVANCE(220);
      END_STATE();
    case 138:
      if (lookahead == 's') ADVANCE(153);
      END_STATE();
    case 139:
      if (lookahead == 's') ADVANCE(48);
      END_STATE();
    case 140:
      if (lookahead == 's') ADVANCE(81);
      END_STATE();
    case 141:
      if (lookahead == 's') ADVANCE(50);
      END_STATE();
    case 142:
      if (lookahead == 's') ADVANCE(53);
      END_STATE();
    case 143:
      if (lookahead == 's') ADVANCE(54);
      END_STATE();
    case 144:
      if (lookahead == 's') ADVANCE(76);
      END_STATE();
    case 145:
      if (lookahead == 's') ADVANCE(85);
      END_STATE();
    case 146:
      if (lookahead == 's') ADVANCE(94);
      END_STATE();
    case 147:
      if (lookahead == 's') ADVANCE(87);
      END_STATE();
    case 148:
      if (lookahead == 's') ADVANCE(88);
      END_STATE();
    case 149:
      if (lookahead == 's') ADVANCE(89);
      END_STATE();
    case 150:
      if (lookahead == 's') ADVANCE(90);
      END_STATE();
    case 151:
      if (lookahead == 's') ADVANCE(91);
      END_STATE();
    case 152:
      if (lookahead == 't') ADVANCE(2);
      END_STATE();
    case 153:
      if (lookahead == 't') ADVANCE(11);
      END_STATE();
    case 154:
      if (lookahead == 't') ADVANCE(228);
      END_STATE();
    case 155:
      if (lookahead == 't') ADVANCE(14);
      END_STATE();
    case 156:
      if (lookahead == 't') ADVANCE(221);
      END_STATE();
    case 157:
      if (lookahead == 't') ADVANCE(222);
      END_STATE();
    case 158:
      if (lookahead == 't') ADVANCE(234);
      END_STATE();
    case 159:
      if (lookahead == 't') ADVANCE(12);
      END_STATE();
    case 160:
      if (lookahead == 't') ADVANCE(68);
      END_STATE();
    case 161:
      if (lookahead == 't') ADVANCE(15);
      END_STATE();
    case 162:
      if (lookahead == 't') ADVANCE(21);
      END_STATE();
    case 163:
      if (lookahead == 't') ADVANCE(183);
      END_STATE();
    case 164:
      if (lookahead == 't') ADVANCE(137);
      END_STATE();
    case 165:
      if (lookahead == 't') ADVANCE(20);
      END_STATE();
    case 166:
      if (lookahead == 't') ADVANCE(57);
      END_STATE();
    case 167:
      if (lookahead == 't') ADVANCE(62);
      END_STATE();
    case 168:
      if (lookahead == 't') ADVANCE(16);
      END_STATE();
    case 169:
      if (lookahead == 't') ADVANCE(71);
      END_STATE();
    case 170:
      if (lookahead == 'u') ADVANCE(30);
      END_STATE();
    case 171:
      if (lookahead == 'u') ADVANCE(104);
      END_STATE();
    case 172:
      if (lookahead == 'u') ADVANCE(22);
      END_STATE();
    case 173:
      if (lookahead == 'u') ADVANCE(47);
      END_STATE();
    case 174:
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 175:
      if (lookahead == 'u') ADVANCE(109);
      END_STATE();
    case 176:
      if (lookahead == 'v') ADVANCE(58);
      END_STATE();
    case 177:
      if (lookahead == 'v') ADVANCE(99);
      END_STATE();
    case 178:
      if (lookahead == 'v') ADVANCE(101);
      END_STATE();
    case 179:
      if (lookahead == 'v') ADVANCE(66);
      END_STATE();
    case 180:
      if (lookahead == 'w') ADVANCE(124);
      END_STATE();
    case 181:
      if (lookahead == 'y') ADVANCE(180);
      END_STATE();
    case 182:
      if (lookahead == 'y') ADVANCE(213);
      END_STATE();
    case 183:
      if (lookahead == 'y') ADVANCE(127);
      END_STATE();
    case 184:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(188);
      END_STATE();
    case 185:
      if (lookahead == '"' ||
          lookahead == '\'' ||
          lookahead == '/' ||
          lookahead == '\\' ||
          lookahead == 'b' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't' ||
          lookahead == 'u') ADVANCE(258);
      END_STATE();
    case 186:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(7);
      END_STATE();
    case 187:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(244);
      END_STATE();
    case 188:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 189:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(242);
      END_STATE();
    case 190:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(240);
      END_STATE();
    case 191:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(241);
      END_STATE();
    case 192:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(243);
      END_STATE();
    case 193:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(186);
      END_STATE();
    case 194:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(187);
      END_STATE();
    case 195:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(189);
      END_STATE();
    case 196:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(191);
      END_STATE();
    case 197:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(190);
      END_STATE();
    case 198:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(192);
      END_STATE();
    case 199:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 200:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      END_STATE();
    case 201:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      END_STATE();
    case 202:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      END_STATE();
    case 203:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 204:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(203);
      END_STATE();
    case 205:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      END_STATE();
    case 206:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(205);
      END_STATE();
    case 207:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(206);
      END_STATE();
    case 208:
      if (eof) ADVANCE(210);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(216);
      if (lookahead == '\'') ADVANCE(215);
      if (lookahead == '(') ADVANCE(211);
      if (lookahead == ')') ADVANCE(212);
      if (lookahead == ',') ADVANCE(217);
      if (lookahead == '-') ADVANCE(219);
      if (lookahead == ':') ADVANCE(238);
      if (lookahead == '<') ADVANCE(236);
      if (lookahead == '=') ADVANCE(235);
      if (lookahead == '>') ADVANCE(236);
      if (lookahead == '[') ADVANCE(214);
      if (lookahead == ']') ADVANCE(218);
      if (lookahead == 'a') ADVANCE(111);
      if (lookahead == 'c') ADVANCE(130);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'i') ADVANCE(112);
      if (lookahead == 'k') ADVANCE(44);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(45);
      if (lookahead == 'n') ADVANCE(122);
      if (lookahead == 'o') ADVANCE(128);
      if (lookahead == 'p') ADVANCE(170);
      if (lookahead == 's') ADVANCE(123);
      if (lookahead == 't') ADVANCE(131);
      if (lookahead == 'v') ADVANCE(77);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(208)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(248);
      END_STATE();
    case 209:
      if (eof) ADVANCE(210);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(216);
      if (lookahead == '\'') ADVANCE(215);
      if (lookahead == ')') ADVANCE(212);
      if (lookahead == ',') ADVANCE(217);
      if (lookahead == '-') ADVANCE(219);
      if (lookahead == '<') ADVANCE(236);
      if (lookahead == '=') ADVANCE(235);
      if (lookahead == '>') ADVANCE(236);
      if (lookahead == ']') ADVANCE(218);
      if (lookahead == 'a') ADVANCE(111);
      if (lookahead == 'c') ADVANCE(130);
      if (lookahead == 'l') ADVANCE(23);
      if (lookahead == 'm') ADVANCE(121);
      if (lookahead == 'o') ADVANCE(129);
      if (lookahead == 'p') ADVANCE(170);
      if (lookahead == 's') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(102);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(209)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(202);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(sym_sortByField);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_visits);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_last_visit);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_last_eventful_visit);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_last_revision);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(anon_sym_last_release);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(anon_sym_created);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(anon_sym_modified);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(anon_sym_published);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_limitField);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_patternField);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_booleanField);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_numericField);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_visitTypeField);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_listField);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_dateField);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_rangeOp);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_rangeOp);
      if (lookahead == '=') ADVANCE(235);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_equalOp);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_containOp);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_choiceOp);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_isoDateTime);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(204);
      if (lookahead == '.') ADVANCE(207);
      if (lookahead == 'Z') ADVANCE(240);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(204);
      if (lookahead == ':') ADVANCE(196);
      if (lookahead == 'Z') ADVANCE(240);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(204);
      if (lookahead == 'Z') ADVANCE(240);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(188);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(193);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(249);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(245);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(246);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(247);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(249);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(sym_booleanTrue);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(sym_booleanFalse);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(sym_or);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(sym_or);
      if (lookahead == 'i') ADVANCE(73);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym_and);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(sym_singleWord);
      if (!sym_singleWord_character_set_1(lookahead)) ADVANCE(255);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(256);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(257);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(257);
      END_STATE();
    case 258:
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
  [3] = {.lex_state = 5},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 5},
  [6] = {.lex_state = 209},
  [7] = {.lex_state = 209},
  [8] = {.lex_state = 209},
  [9] = {.lex_state = 209},
  [10] = {.lex_state = 209},
  [11] = {.lex_state = 209},
  [12] = {.lex_state = 209},
  [13] = {.lex_state = 209},
  [14] = {.lex_state = 209},
  [15] = {.lex_state = 209},
  [16] = {.lex_state = 209},
  [17] = {.lex_state = 209},
  [18] = {.lex_state = 209},
  [19] = {.lex_state = 209},
  [20] = {.lex_state = 209},
  [21] = {.lex_state = 209},
  [22] = {.lex_state = 209},
  [23] = {.lex_state = 209},
  [24] = {.lex_state = 209},
  [25] = {.lex_state = 3},
  [26] = {.lex_state = 209},
  [27] = {.lex_state = 209},
  [28] = {.lex_state = 209},
  [29] = {.lex_state = 209},
  [30] = {.lex_state = 209},
  [31] = {.lex_state = 209},
  [32] = {.lex_state = 209},
  [33] = {.lex_state = 209},
  [34] = {.lex_state = 209},
  [35] = {.lex_state = 209},
  [36] = {.lex_state = 209},
  [37] = {.lex_state = 209},
  [38] = {.lex_state = 209},
  [39] = {.lex_state = 3},
  [40] = {.lex_state = 1},
  [41] = {.lex_state = 3},
  [42] = {.lex_state = 1},
  [43] = {.lex_state = 3},
  [44] = {.lex_state = 1},
  [45] = {.lex_state = 1},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 209},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 3},
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
  [76] = {.lex_state = 5},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 5},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 209},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 5},
  [86] = {.lex_state = 209},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 209},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 5},
  [92] = {.lex_state = 5},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 5},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 209},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 5},
  [108] = {.lex_state = 0},
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
    [sym_listField] = ACTIONS(1),
    [sym_dateField] = ACTIONS(1),
    [sym_rangeOp] = ACTIONS(1),
    [sym_equalOp] = ACTIONS(1),
    [sym_containOp] = ACTIONS(1),
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
    [sym_query] = STATE(108),
    [sym_filters] = STATE(15),
    [sym_filter] = STATE(27),
    [sym_patternFilter] = STATE(28),
    [sym_booleanFilter] = STATE(28),
    [sym_numericFilter] = STATE(28),
    [sym_boundedListFilter] = STATE(28),
    [sym_visitTypeFilter] = STATE(30),
    [sym_unboundedListFilter] = STATE(28),
    [sym_dateFilter] = STATE(28),
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
    STATE(16), 1,
      sym_filters,
    STATE(27), 1,
      sym_filter,
    STATE(30), 1,
      sym_visitTypeFilter,
    STATE(46), 1,
      sym_sortBy,
    STATE(50), 1,
      sym_limit,
    STATE(28), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [51] = 11,
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
    STATE(16), 1,
      sym_filters,
    STATE(27), 1,
      sym_filter,
    STATE(30), 1,
      sym_visitTypeFilter,
    STATE(28), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [90] = 11,
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
    STATE(27), 1,
      sym_filter,
    STATE(30), 1,
      sym_visitTypeFilter,
    STATE(56), 1,
      sym_filters,
    STATE(28), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [129] = 11,
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
    STATE(18), 1,
      sym_filters,
    STATE(27), 1,
      sym_filter,
    STATE(30), 1,
      sym_visitTypeFilter,
    STATE(28), 6,
      sym_patternFilter,
      sym_booleanFilter,
      sym_numericFilter,
      sym_boundedListFilter,
      sym_unboundedListFilter,
      sym_dateFilter,
  [168] = 6,
    ACTIONS(21), 1,
      anon_sym_SQUOTE,
    ACTIONS(23), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_DASH,
    STATE(84), 1,
      sym_sortByOptions,
    ACTIONS(25), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
    ACTIONS(29), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [195] = 6,
    ACTIONS(27), 1,
      anon_sym_DASH,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      anon_sym_DQUOTE,
    ACTIONS(35), 1,
      anon_sym_RBRACK,
    STATE(71), 1,
      sym_sortByOptions,
    ACTIONS(29), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [221] = 3,
    ACTIONS(27), 1,
      anon_sym_DASH,
    STATE(106), 1,
      sym_sortByOptions,
    ACTIONS(29), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [238] = 3,
    ACTIONS(27), 1,
      anon_sym_DASH,
    STATE(105), 1,
      sym_sortByOptions,
    ACTIONS(29), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [255] = 3,
    ACTIONS(27), 1,
      anon_sym_DASH,
    STATE(93), 1,
      sym_sortByOptions,
    ACTIONS(29), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [272] = 3,
    ACTIONS(27), 1,
      anon_sym_DASH,
    STATE(96), 1,
      sym_sortByOptions,
    ACTIONS(29), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [289] = 1,
    ACTIONS(37), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [300] = 1,
    ACTIONS(39), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [311] = 1,
    ACTIONS(41), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [322] = 7,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(43), 1,
      ts_builtin_sym_end,
    ACTIONS(45), 1,
      sym_or,
    ACTIONS(47), 1,
      sym_and,
    STATE(47), 1,
      sym_limit,
    STATE(48), 1,
      sym_sortBy,
  [344] = 1,
    ACTIONS(49), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [353] = 1,
    ACTIONS(51), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [362] = 2,
    ACTIONS(53), 1,
      sym_and,
    ACTIONS(49), 5,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
  [373] = 1,
    ACTIONS(55), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [382] = 1,
    ACTIONS(57), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [391] = 1,
    ACTIONS(59), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [400] = 1,
    ACTIONS(61), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [409] = 1,
    ACTIONS(63), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [418] = 1,
    ACTIONS(65), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [427] = 5,
    ACTIONS(67), 1,
      anon_sym_SQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(73), 1,
      sym_singleWord,
    STATE(87), 1,
      sym_string,
    ACTIONS(71), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [444] = 1,
    ACTIONS(75), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [453] = 1,
    ACTIONS(77), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [462] = 1,
    ACTIONS(79), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [471] = 1,
    ACTIONS(81), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [480] = 1,
    ACTIONS(83), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [489] = 1,
    ACTIONS(85), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [498] = 1,
    ACTIONS(87), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [507] = 1,
    ACTIONS(89), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [516] = 1,
    ACTIONS(91), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [525] = 1,
    ACTIONS(93), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [534] = 1,
    ACTIONS(95), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [543] = 1,
    ACTIONS(97), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [552] = 1,
    ACTIONS(99), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [561] = 5,
    ACTIONS(67), 1,
      anon_sym_SQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(73), 1,
      sym_singleWord,
    ACTIONS(101), 1,
      anon_sym_RBRACK,
    STATE(52), 1,
      sym_string,
  [577] = 3,
    STATE(42), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(103), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(105), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [589] = 5,
    ACTIONS(67), 1,
      anon_sym_SQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(73), 1,
      sym_singleWord,
    ACTIONS(107), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      sym_string,
  [605] = 3,
    STATE(42), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(109), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(111), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [617] = 5,
    ACTIONS(67), 1,
      anon_sym_SQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(73), 1,
      sym_singleWord,
    STATE(37), 1,
      sym_string,
    STATE(38), 1,
      sym_patternVal,
  [633] = 3,
    STATE(40), 1,
      aux_sym_stringContent_repeat1,
    STATE(97), 1,
      sym_stringContent,
    ACTIONS(114), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [644] = 3,
    STATE(40), 1,
      aux_sym_stringContent_repeat1,
    STATE(102), 1,
      sym_stringContent,
    ACTIONS(114), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [655] = 4,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(116), 1,
      ts_builtin_sym_end,
    ACTIONS(118), 1,
      sym_and,
    STATE(100), 1,
      sym_limit,
  [668] = 4,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(120), 1,
      ts_builtin_sym_end,
    ACTIONS(122), 1,
      sym_and,
    STATE(103), 1,
      sym_sortBy,
  [681] = 4,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(120), 1,
      ts_builtin_sym_end,
    ACTIONS(124), 1,
      sym_and,
    STATE(103), 1,
      sym_limit,
  [694] = 1,
    ACTIONS(126), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [701] = 4,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(116), 1,
      ts_builtin_sym_end,
    ACTIONS(128), 1,
      sym_and,
    STATE(100), 1,
      sym_sortBy,
  [714] = 1,
    ACTIONS(130), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [721] = 3,
    ACTIONS(132), 1,
      anon_sym_COMMA,
    ACTIONS(134), 1,
      anon_sym_RBRACK,
    STATE(75), 1,
      aux_sym_visitTypeVal_repeat1,
  [731] = 3,
    ACTIONS(136), 1,
      anon_sym_COMMA,
    ACTIONS(138), 1,
      anon_sym_RBRACK,
    STATE(60), 1,
      aux_sym_sortByVal_repeat1,
  [741] = 1,
    ACTIONS(140), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [747] = 3,
    ACTIONS(136), 1,
      anon_sym_COMMA,
    ACTIONS(142), 1,
      anon_sym_RBRACK,
    STATE(60), 1,
      aux_sym_sortByVal_repeat1,
  [757] = 3,
    ACTIONS(45), 1,
      sym_or,
    ACTIONS(53), 1,
      sym_and,
    ACTIONS(144), 1,
      anon_sym_RPAREN,
  [767] = 3,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(116), 1,
      ts_builtin_sym_end,
    STATE(100), 1,
      sym_limit,
  [777] = 1,
    ACTIONS(146), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [783] = 3,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(116), 1,
      ts_builtin_sym_end,
    STATE(100), 1,
      sym_sortBy,
  [793] = 3,
    ACTIONS(148), 1,
      anon_sym_COMMA,
    ACTIONS(151), 1,
      anon_sym_RBRACK,
    STATE(60), 1,
      aux_sym_sortByVal_repeat1,
  [803] = 1,
    ACTIONS(153), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [809] = 3,
    ACTIONS(136), 1,
      anon_sym_COMMA,
    ACTIONS(155), 1,
      anon_sym_RBRACK,
    STATE(55), 1,
      aux_sym_sortByVal_repeat1,
  [819] = 1,
    ACTIONS(157), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [825] = 1,
    ACTIONS(159), 3,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym_singleWord,
  [831] = 3,
    ACTIONS(161), 1,
      anon_sym_COMMA,
    ACTIONS(164), 1,
      anon_sym_RBRACK,
    STATE(65), 1,
      aux_sym_visitTypeVal_repeat1,
  [841] = 3,
    ACTIONS(132), 1,
      anon_sym_COMMA,
    ACTIONS(166), 1,
      anon_sym_RBRACK,
    STATE(74), 1,
      aux_sym_visitTypeVal_repeat1,
  [851] = 2,
    STATE(17), 1,
      sym_booleanVal,
    ACTIONS(168), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [859] = 1,
    ACTIONS(170), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [865] = 1,
    ACTIONS(172), 3,
      ts_builtin_sym_end,
      sym_sortByField,
      sym_and,
  [871] = 3,
    ACTIONS(19), 1,
      sym_limitField,
    ACTIONS(174), 1,
      ts_builtin_sym_end,
    STATE(99), 1,
      sym_limit,
  [881] = 3,
    ACTIONS(136), 1,
      anon_sym_COMMA,
    ACTIONS(176), 1,
      anon_sym_RBRACK,
    STATE(53), 1,
      aux_sym_sortByVal_repeat1,
  [891] = 3,
    ACTIONS(17), 1,
      sym_sortByField,
    ACTIONS(174), 1,
      ts_builtin_sym_end,
    STATE(99), 1,
      sym_sortBy,
  [901] = 1,
    ACTIONS(178), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [907] = 3,
    ACTIONS(132), 1,
      anon_sym_COMMA,
    ACTIONS(180), 1,
      anon_sym_RBRACK,
    STATE(65), 1,
      aux_sym_visitTypeVal_repeat1,
  [917] = 3,
    ACTIONS(132), 1,
      anon_sym_COMMA,
    ACTIONS(182), 1,
      anon_sym_RBRACK,
    STATE(65), 1,
      aux_sym_visitTypeVal_repeat1,
  [927] = 2,
    ACTIONS(184), 1,
      sym_equalOp,
    STATE(88), 1,
      sym_sortByOp,
  [934] = 2,
    ACTIONS(186), 1,
      anon_sym_LBRACK,
    STATE(32), 1,
      sym_visitTypeVal,
  [941] = 2,
    ACTIONS(188), 1,
      sym_number,
    STATE(33), 1,
      sym_numberVal,
  [948] = 1,
    ACTIONS(190), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [953] = 2,
    ACTIONS(192), 1,
      sym_containOp,
    STATE(43), 1,
      sym_patternOp,
  [960] = 2,
    ACTIONS(194), 1,
      sym_rangeOp,
    STATE(89), 1,
      sym_dateOp,
  [967] = 2,
    ACTIONS(196), 1,
      anon_sym_LBRACK,
    STATE(26), 1,
      sym_listVal,
  [974] = 2,
    ACTIONS(198), 1,
      sym_choiceOp,
    STATE(82), 1,
      sym_listOp,
  [981] = 1,
    ACTIONS(200), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [986] = 2,
    ACTIONS(202), 1,
      sym_equalOp,
    STATE(67), 1,
      sym_booleanOp,
  [993] = 2,
    ACTIONS(204), 1,
      sym_rangeOp,
    STATE(78), 1,
      sym_numericOp,
  [1000] = 1,
    ACTIONS(206), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1005] = 2,
    ACTIONS(208), 1,
      anon_sym_LBRACK,
    STATE(68), 1,
      sym_sortByVal,
  [1012] = 2,
    ACTIONS(210), 1,
      sym_isoDateTime,
    STATE(20), 1,
      sym_dateVal,
  [1019] = 1,
    ACTIONS(212), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [1024] = 2,
    ACTIONS(214), 1,
      sym_equalOp,
    STATE(77), 1,
      sym_visitTypeOp,
  [1031] = 1,
    ACTIONS(216), 1,
      sym_number,
  [1035] = 1,
    ACTIONS(218), 1,
      anon_sym_DQUOTE,
  [1039] = 1,
    ACTIONS(220), 1,
      anon_sym_LBRACK,
  [1043] = 1,
    ACTIONS(222), 1,
      sym_equalOp,
  [1047] = 1,
    ACTIONS(218), 1,
      anon_sym_SQUOTE,
  [1051] = 1,
    ACTIONS(224), 1,
      anon_sym_DQUOTE,
  [1055] = 1,
    ACTIONS(226), 1,
      sym_isoDateTime,
  [1059] = 1,
    ACTIONS(228), 1,
      ts_builtin_sym_end,
  [1063] = 1,
    ACTIONS(174), 1,
      ts_builtin_sym_end,
  [1067] = 1,
    ACTIONS(230), 1,
      anon_sym_LBRACK,
  [1071] = 1,
    ACTIONS(224), 1,
      anon_sym_SQUOTE,
  [1075] = 1,
    ACTIONS(116), 1,
      ts_builtin_sym_end,
  [1079] = 1,
    ACTIONS(232), 1,
      anon_sym_LBRACK,
  [1083] = 1,
    ACTIONS(234), 1,
      anon_sym_SQUOTE,
  [1087] = 1,
    ACTIONS(234), 1,
      anon_sym_DQUOTE,
  [1091] = 1,
    ACTIONS(236), 1,
      sym_number,
  [1095] = 1,
    ACTIONS(238), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 51,
  [SMALL_STATE(4)] = 90,
  [SMALL_STATE(5)] = 129,
  [SMALL_STATE(6)] = 168,
  [SMALL_STATE(7)] = 195,
  [SMALL_STATE(8)] = 221,
  [SMALL_STATE(9)] = 238,
  [SMALL_STATE(10)] = 255,
  [SMALL_STATE(11)] = 272,
  [SMALL_STATE(12)] = 289,
  [SMALL_STATE(13)] = 300,
  [SMALL_STATE(14)] = 311,
  [SMALL_STATE(15)] = 322,
  [SMALL_STATE(16)] = 344,
  [SMALL_STATE(17)] = 353,
  [SMALL_STATE(18)] = 362,
  [SMALL_STATE(19)] = 373,
  [SMALL_STATE(20)] = 382,
  [SMALL_STATE(21)] = 391,
  [SMALL_STATE(22)] = 400,
  [SMALL_STATE(23)] = 409,
  [SMALL_STATE(24)] = 418,
  [SMALL_STATE(25)] = 427,
  [SMALL_STATE(26)] = 444,
  [SMALL_STATE(27)] = 453,
  [SMALL_STATE(28)] = 462,
  [SMALL_STATE(29)] = 471,
  [SMALL_STATE(30)] = 480,
  [SMALL_STATE(31)] = 489,
  [SMALL_STATE(32)] = 498,
  [SMALL_STATE(33)] = 507,
  [SMALL_STATE(34)] = 516,
  [SMALL_STATE(35)] = 525,
  [SMALL_STATE(36)] = 534,
  [SMALL_STATE(37)] = 543,
  [SMALL_STATE(38)] = 552,
  [SMALL_STATE(39)] = 561,
  [SMALL_STATE(40)] = 577,
  [SMALL_STATE(41)] = 589,
  [SMALL_STATE(42)] = 605,
  [SMALL_STATE(43)] = 617,
  [SMALL_STATE(44)] = 633,
  [SMALL_STATE(45)] = 644,
  [SMALL_STATE(46)] = 655,
  [SMALL_STATE(47)] = 668,
  [SMALL_STATE(48)] = 681,
  [SMALL_STATE(49)] = 694,
  [SMALL_STATE(50)] = 701,
  [SMALL_STATE(51)] = 714,
  [SMALL_STATE(52)] = 721,
  [SMALL_STATE(53)] = 731,
  [SMALL_STATE(54)] = 741,
  [SMALL_STATE(55)] = 747,
  [SMALL_STATE(56)] = 757,
  [SMALL_STATE(57)] = 767,
  [SMALL_STATE(58)] = 777,
  [SMALL_STATE(59)] = 783,
  [SMALL_STATE(60)] = 793,
  [SMALL_STATE(61)] = 803,
  [SMALL_STATE(62)] = 809,
  [SMALL_STATE(63)] = 819,
  [SMALL_STATE(64)] = 825,
  [SMALL_STATE(65)] = 831,
  [SMALL_STATE(66)] = 841,
  [SMALL_STATE(67)] = 851,
  [SMALL_STATE(68)] = 859,
  [SMALL_STATE(69)] = 865,
  [SMALL_STATE(70)] = 871,
  [SMALL_STATE(71)] = 881,
  [SMALL_STATE(72)] = 891,
  [SMALL_STATE(73)] = 901,
  [SMALL_STATE(74)] = 907,
  [SMALL_STATE(75)] = 917,
  [SMALL_STATE(76)] = 927,
  [SMALL_STATE(77)] = 934,
  [SMALL_STATE(78)] = 941,
  [SMALL_STATE(79)] = 948,
  [SMALL_STATE(80)] = 953,
  [SMALL_STATE(81)] = 960,
  [SMALL_STATE(82)] = 967,
  [SMALL_STATE(83)] = 974,
  [SMALL_STATE(84)] = 981,
  [SMALL_STATE(85)] = 986,
  [SMALL_STATE(86)] = 993,
  [SMALL_STATE(87)] = 1000,
  [SMALL_STATE(88)] = 1005,
  [SMALL_STATE(89)] = 1012,
  [SMALL_STATE(90)] = 1019,
  [SMALL_STATE(91)] = 1024,
  [SMALL_STATE(92)] = 1031,
  [SMALL_STATE(93)] = 1035,
  [SMALL_STATE(94)] = 1039,
  [SMALL_STATE(95)] = 1043,
  [SMALL_STATE(96)] = 1047,
  [SMALL_STATE(97)] = 1051,
  [SMALL_STATE(98)] = 1055,
  [SMALL_STATE(99)] = 1059,
  [SMALL_STATE(100)] = 1063,
  [SMALL_STATE(101)] = 1067,
  [SMALL_STATE(102)] = 1071,
  [SMALL_STATE(103)] = 1075,
  [SMALL_STATE(104)] = 1079,
  [SMALL_STATE(105)] = 1083,
  [SMALL_STATE(106)] = 1087,
  [SMALL_STATE(107)] = 1091,
  [SMALL_STATE(108)] = 1095,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 1),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 1),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 1),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 3, .production_id = 3),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanFilter, 3, .production_id = 2),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [55] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 4, .production_id = 5),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateFilter, 3, .production_id = 2),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 4, .production_id = 5),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateVal, 1),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 3, .production_id = 4),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 3, .production_id = 4),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 1),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unboundedListFilter, 3, .production_id = 2),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 1),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter, 1, .production_id = 1),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 2),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boundedListFilter, 1),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 2),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeFilter, 3, .production_id = 2),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numericFilter, 3, .production_id = 2),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberVal, 1),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 3),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanVal, 1),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternVal, 1),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternFilter, 3, .production_id = 2),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [103] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_stringContent, 1),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_stringContent_repeat1, 2),
  [111] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_stringContent_repeat1, 2), SHIFT_REPEAT(42),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOptions, 1),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOptions, 2),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [140] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 6, .production_id = 8),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 5, .production_id = 7),
  [148] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(6),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 4, .production_id = 5),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 3, .production_id = 4),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternOp, 1),
  [161] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(25),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortBy, 3, .production_id = 2),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit, 3, .production_id = 2),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 4),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [178] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 2),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 4, .production_id = 7),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 4),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 4),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanOp, 1),
  [214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numericOp, 1),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listOp, 1),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateOp, 1),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 5),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOp, 1),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeOp, 1),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [238] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
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
