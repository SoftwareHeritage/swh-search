#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 126
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 95
#define ALIAS_COUNT 0
#define TOKEN_COUNT 61
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
  anon_sym_arch = 24,
  anon_sym_aur = 25,
  anon_sym_bzr = 26,
  anon_sym_cran = 27,
  anon_sym_crates = 28,
  anon_sym_cvs = 29,
  anon_sym_deb = 30,
  anon_sym_deposit = 31,
  anon_sym_ftp = 32,
  anon_sym_hackage = 33,
  anon_sym_hg = 34,
  anon_sym_git = 35,
  anon_sym_golang = 36,
  anon_sym_maven = 37,
  anon_sym_nixguix = 38,
  anon_sym_npm = 39,
  anon_sym_opam = 40,
  anon_sym_pubdev = 41,
  anon_sym_pypi = 42,
  anon_sym_rpm = 43,
  anon_sym_svn = 44,
  anon_sym_tar = 45,
  sym_listField = 46,
  sym_dateField = 47,
  sym_rangeOp = 48,
  sym_equalOp = 49,
  sym_containOp = 50,
  sym_choiceOp = 51,
  sym_isoDateTime = 52,
  sym_number = 53,
  sym_booleanTrue = 54,
  sym_booleanFalse = 55,
  sym_or = 56,
  sym_and = 57,
  sym_singleWord = 58,
  aux_sym_stringContent_token1 = 59,
  sym_escape_sequence = 60,
  sym_query = 61,
  sym_filters = 62,
  sym_sortBy = 63,
  sym_sortByOp = 64,
  sym_sortByVal = 65,
  sym_sortByOptions = 66,
  sym_limit = 67,
  sym_filter = 68,
  sym_patternFilter = 69,
  sym_patternOp = 70,
  sym_patternVal = 71,
  sym_booleanFilter = 72,
  sym_booleanOp = 73,
  sym_booleanVal = 74,
  sym_numericFilter = 75,
  sym_numericOp = 76,
  sym_numberVal = 77,
  sym_boundedListFilter = 78,
  sym_visitTypeFilter = 79,
  sym_visitTypeOp = 80,
  sym_visitTypeVal = 81,
  sym_visitTypeOptions = 82,
  sym_unboundedListFilter = 83,
  sym_listOp = 84,
  sym_listVal = 85,
  sym_dateFilter = 86,
  sym_dateOp = 87,
  sym_dateVal = 88,
  sym_string = 89,
  sym_stringContent = 90,
  aux_sym_sortByVal_repeat1 = 91,
  aux_sym_visitTypeVal_repeat1 = 92,
  aux_sym_listVal_repeat1 = 93,
  aux_sym_stringContent_repeat1 = 94,
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
  [anon_sym_arch] = "arch",
  [anon_sym_aur] = "aur",
  [anon_sym_bzr] = "bzr",
  [anon_sym_cran] = "cran",
  [anon_sym_crates] = "crates",
  [anon_sym_cvs] = "cvs",
  [anon_sym_deb] = "deb",
  [anon_sym_deposit] = "deposit",
  [anon_sym_ftp] = "ftp",
  [anon_sym_hackage] = "hackage",
  [anon_sym_hg] = "hg",
  [anon_sym_git] = "git",
  [anon_sym_golang] = "golang",
  [anon_sym_maven] = "maven",
  [anon_sym_nixguix] = "nixguix",
  [anon_sym_npm] = "npm",
  [anon_sym_opam] = "opam",
  [anon_sym_pubdev] = "pubdev",
  [anon_sym_pypi] = "pypi",
  [anon_sym_rpm] = "rpm",
  [anon_sym_svn] = "svn",
  [anon_sym_tar] = "tar",
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
  [anon_sym_arch] = anon_sym_arch,
  [anon_sym_aur] = anon_sym_aur,
  [anon_sym_bzr] = anon_sym_bzr,
  [anon_sym_cran] = anon_sym_cran,
  [anon_sym_crates] = anon_sym_crates,
  [anon_sym_cvs] = anon_sym_cvs,
  [anon_sym_deb] = anon_sym_deb,
  [anon_sym_deposit] = anon_sym_deposit,
  [anon_sym_ftp] = anon_sym_ftp,
  [anon_sym_hackage] = anon_sym_hackage,
  [anon_sym_hg] = anon_sym_hg,
  [anon_sym_git] = anon_sym_git,
  [anon_sym_golang] = anon_sym_golang,
  [anon_sym_maven] = anon_sym_maven,
  [anon_sym_nixguix] = anon_sym_nixguix,
  [anon_sym_npm] = anon_sym_npm,
  [anon_sym_opam] = anon_sym_opam,
  [anon_sym_pubdev] = anon_sym_pubdev,
  [anon_sym_pypi] = anon_sym_pypi,
  [anon_sym_rpm] = anon_sym_rpm,
  [anon_sym_svn] = anon_sym_svn,
  [anon_sym_tar] = anon_sym_tar,
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
  [anon_sym_arch] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_aur] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bzr] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cran] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_crates] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cvs] = {
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
  [anon_sym_hackage] = {
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
  [anon_sym_golang] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_maven] = {
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
  [anon_sym_opam] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pubdev] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pypi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rpm] = {
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
      if (eof) ADVANCE(265);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(271);
      if (lookahead == '\'') ADVANCE(270);
      if (lookahead == '(') ADVANCE(266);
      if (lookahead == ')') ADVANCE(267);
      if (lookahead == ',') ADVANCE(272);
      if (lookahead == '-') ADVANCE(274);
      if (lookahead == ':') ADVANCE(316);
      if (lookahead == '<') ADVANCE(314);
      if (lookahead == '=') ADVANCE(313);
      if (lookahead == '>') ADVANCE(314);
      if (lookahead == '[') ADVANCE(269);
      if (lookahead == '\\') ADVANCE(240);
      if (lookahead == ']') ADVANCE(273);
      if (lookahead == 'a') ADVANCE(142);
      if (lookahead == 'b') ADVANCE(238);
      if (lookahead == 'c') ADVANCE(169);
      if (lookahead == 'd') ADVANCE(57);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'g') ADVANCE(99);
      if (lookahead == 'h') ADVANCE(23);
      if (lookahead == 'i') ADVANCE(143);
      if (lookahead == 'k') ADVANCE(58);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(20);
      if (lookahead == 'n') ADVANCE(100);
      if (lookahead == 'o') ADVANCE(164);
      if (lookahead == 'p') ADVANCE(218);
      if (lookahead == 'r') ADVANCE(166);
      if (lookahead == 's') ADVANCE(159);
      if (lookahead == 't') ADVANCE(27);
      if (lookahead == 'v') ADVANCE(103);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(263)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(326);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(4)
      if (lookahead == '"') ADVANCE(271);
      if (lookahead == '\'') ADVANCE(270);
      if (lookahead == '\\') ADVANCE(240);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(334);
      if (lookahead != 0) ADVANCE(335);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(98);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(271);
      if (lookahead == '\'') ADVANCE(270);
      if (lookahead == ',') ADVANCE(272);
      if (lookahead == ']') ADVANCE(273);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '[') ADVANCE(333);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(271);
      if (lookahead == '\'') ADVANCE(270);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      END_STATE();
    case 5:
      if (lookahead == '(') ADVANCE(266);
      if (lookahead == '=') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(177);
      if (lookahead == 'k') ADVANCE(58);
      if (lookahead == 'l') ADVANCE(36);
      if (lookahead == 'm') ADVANCE(67);
      if (lookahead == 'o') ADVANCE(176);
      if (lookahead == 'p') ADVANCE(220);
      if (lookahead == 's') ADVANCE(158);
      if (lookahead == 'v') ADVANCE(126);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(327);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(248);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(249);
      END_STATE();
    case 8:
      if (lookahead == ':') ADVANCE(250);
      END_STATE();
    case 9:
      if (lookahead == ':') ADVANCE(252);
      END_STATE();
    case 10:
      if (lookahead == '=') ADVANCE(313);
      END_STATE();
    case 11:
      if (lookahead == '_') ADVANCE(79);
      END_STATE();
    case 12:
      if (lookahead == '_') ADVANCE(39);
      END_STATE();
    case 13:
      if (lookahead == '_') ADVANCE(229);
      END_STATE();
    case 14:
      if (lookahead == '_') ADVANCE(210);
      if (lookahead == 'e') ADVANCE(49);
      if (lookahead == 's') ADVANCE(275);
      END_STATE();
    case 15:
      if (lookahead == '_') ADVANCE(210);
      if (lookahead == 'e') ADVANCE(49);
      if (lookahead == 's') ADVANCE(286);
      END_STATE();
    case 16:
      if (lookahead == '_') ADVANCE(84);
      END_STATE();
    case 17:
      if (lookahead == '_') ADVANCE(230);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(130);
      if (lookahead == 't') ADVANCE(165);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(144);
      if (lookahead == 'i') ADVANCE(44);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(227);
      if (lookahead == 'e') ADVANCE(211);
      if (lookahead == 'o') ADVANCE(53);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(147);
      if (lookahead == 'e') ADVANCE(29);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(284);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(43);
      if (lookahead == 'g') ADVANCE(299);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(54);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(152);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(140);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(172);
      if (lookahead == 'r') ADVANCE(221);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(93);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(213);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(183);
      if (lookahead == 'i') ADVANCE(141);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(212);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(94);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(215);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(187);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(188);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(145);
      if (lookahead == 'i') ADVANCE(44);
      END_STATE();
    case 37:
      if (lookahead == 'b') ADVANCE(295);
      if (lookahead == 'p') ADVANCE(163);
      END_STATE();
    case 38:
      if (lookahead == 'b') ADVANCE(55);
      END_STATE();
    case 39:
      if (lookahead == 'b') ADVANCE(236);
      END_STATE();
    case 40:
      if (lookahead == 'b') ADVANCE(135);
      END_STATE();
    case 41:
      if (lookahead == 'b') ADVANCE(134);
      END_STATE();
    case 42:
      if (lookahead == 'c') ADVANCE(95);
      END_STATE();
    case 43:
      if (lookahead == 'c') ADVANCE(129);
      END_STATE();
    case 44:
      if (lookahead == 'c') ADVANCE(71);
      if (lookahead == 'm') ADVANCE(110);
      END_STATE();
    case 45:
      if (lookahead == 'd') ADVANCE(332);
      END_STATE();
    case 46:
      if (lookahead == 'd') ADVANCE(332);
      if (lookahead == 'y') ADVANCE(288);
      END_STATE();
    case 47:
      if (lookahead == 'd') ADVANCE(280);
      END_STATE();
    case 48:
      if (lookahead == 'd') ADVANCE(311);
      END_STATE();
    case 49:
      if (lookahead == 'd') ADVANCE(285);
      END_STATE();
    case 50:
      if (lookahead == 'd') ADVANCE(281);
      END_STATE();
    case 51:
      if (lookahead == 'd') ADVANCE(282);
      END_STATE();
    case 52:
      if (lookahead == 'd') ADVANCE(312);
      END_STATE();
    case 53:
      if (lookahead == 'd') ADVANCE(101);
      END_STATE();
    case 54:
      if (lookahead == 'd') ADVANCE(31);
      END_STATE();
    case 55:
      if (lookahead == 'd') ADVANCE(68);
      if (lookahead == 'l') ADVANCE(107);
      END_STATE();
    case 56:
      if (lookahead == 'd') ADVANCE(122);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(37);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(235);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(328);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(329);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(298);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(311);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(133);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(287);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(279);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(312);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(211);
      if (lookahead == 'o') ADVANCE(56);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(226);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(29);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(47);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(155);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(180);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(148);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(50);
      END_STATE();
    case 75:
      if (lookahead == 'e') ADVANCE(154);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(51);
      END_STATE();
    case 77:
      if (lookahead == 'e') ADVANCE(52);
      END_STATE();
    case 78:
      if (lookahead == 'e') ADVANCE(34);
      END_STATE();
    case 79:
      if (lookahead == 'e') ADVANCE(228);
      if (lookahead == 'r') ADVANCE(63);
      if (lookahead == 'v') ADVANCE(124);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(33);
      END_STATE();
    case 81:
      if (lookahead == 'e') ADVANCE(35);
      END_STATE();
    case 82:
      if (lookahead == 'e') ADVANCE(136);
      END_STATE();
    case 83:
      if (lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 84:
      if (lookahead == 'e') ADVANCE(231);
      if (lookahead == 'r') ADVANCE(82);
      if (lookahead == 'v') ADVANCE(127);
      END_STATE();
    case 85:
      if (lookahead == 'f') ADVANCE(219);
      END_STATE();
    case 86:
      if (lookahead == 'f') ADVANCE(113);
      END_STATE();
    case 87:
      if (lookahead == 'f') ADVANCE(119);
      END_STATE();
    case 88:
      if (lookahead == 'f') ADVANCE(225);
      END_STATE();
    case 89:
      if (lookahead == 'g') ADVANCE(301);
      END_STATE();
    case 90:
      if (lookahead == 'g') ADVANCE(223);
      END_STATE();
    case 91:
      if (lookahead == 'g') ADVANCE(222);
      END_STATE();
    case 92:
      if (lookahead == 'g') ADVANCE(108);
      END_STATE();
    case 93:
      if (lookahead == 'g') ADVANCE(61);
      END_STATE();
    case 94:
      if (lookahead == 'g') ADVANCE(62);
      END_STATE();
    case 95:
      if (lookahead == 'h') ADVANCE(289);
      END_STATE();
    case 96:
      if (lookahead == 'h') ADVANCE(76);
      END_STATE();
    case 97:
      if (lookahead == 'h') ADVANCE(77);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(143);
      END_STATE();
    case 99:
      if (lookahead == 'i') ADVANCE(198);
      if (lookahead == 'o') ADVANCE(131);
      END_STATE();
    case 100:
      if (lookahead == 'i') ADVANCE(234);
      if (lookahead == 'o') ADVANCE(199);
      if (lookahead == 'p') ADVANCE(138);
      END_STATE();
    case 101:
      if (lookahead == 'i') ADVANCE(86);
      END_STATE();
    case 102:
      if (lookahead == 'i') ADVANCE(307);
      END_STATE();
    case 103:
      if (lookahead == 'i') ADVANCE(189);
      END_STATE();
    case 104:
      if (lookahead == 'i') ADVANCE(233);
      END_STATE();
    case 105:
      if (lookahead == 'i') ADVANCE(92);
      END_STATE();
    case 106:
      if (lookahead == 'i') ADVANCE(161);
      END_STATE();
    case 107:
      if (lookahead == 'i') ADVANCE(182);
      END_STATE();
    case 108:
      if (lookahead == 'i') ADVANCE(149);
      END_STATE();
    case 109:
      if (lookahead == 'i') ADVANCE(185);
      END_STATE();
    case 110:
      if (lookahead == 'i') ADVANCE(201);
      END_STATE();
    case 111:
      if (lookahead == 'i') ADVANCE(202);
      END_STATE();
    case 112:
      if (lookahead == 'i') ADVANCE(203);
      END_STATE();
    case 113:
      if (lookahead == 'i') ADVANCE(74);
      END_STATE();
    case 114:
      if (lookahead == 'i') ADVANCE(204);
      END_STATE();
    case 115:
      if (lookahead == 'i') ADVANCE(205);
      END_STATE();
    case 116:
      if (lookahead == 'i') ADVANCE(209);
      END_STATE();
    case 117:
      if (lookahead == 'i') ADVANCE(206);
      END_STATE();
    case 118:
      if (lookahead == 'i') ADVANCE(214);
      END_STATE();
    case 119:
      if (lookahead == 'i') ADVANCE(77);
      END_STATE();
    case 120:
      if (lookahead == 'i') ADVANCE(162);
      END_STATE();
    case 121:
      if (lookahead == 'i') ADVANCE(190);
      END_STATE();
    case 122:
      if (lookahead == 'i') ADVANCE(87);
      END_STATE();
    case 123:
      if (lookahead == 'i') ADVANCE(191);
      END_STATE();
    case 124:
      if (lookahead == 'i') ADVANCE(193);
      END_STATE();
    case 125:
      if (lookahead == 'i') ADVANCE(194);
      END_STATE();
    case 126:
      if (lookahead == 'i') ADVANCE(195);
      END_STATE();
    case 127:
      if (lookahead == 'i') ADVANCE(196);
      END_STATE();
    case 128:
      if (lookahead == 'i') ADVANCE(197);
      END_STATE();
    case 129:
      if (lookahead == 'k') ADVANCE(28);
      END_STATE();
    case 130:
      if (lookahead == 'l') ADVANCE(184);
      END_STATE();
    case 131:
      if (lookahead == 'l') ADVANCE(25);
      END_STATE();
    case 132:
      if (lookahead == 'l') ADVANCE(13);
      END_STATE();
    case 133:
      if (lookahead == 'l') ADVANCE(78);
      if (lookahead == 'v') ADVANCE(109);
      END_STATE();
    case 134:
      if (lookahead == 'l') ADVANCE(107);
      END_STATE();
    case 135:
      if (lookahead == 'l') ADVANCE(121);
      END_STATE();
    case 136:
      if (lookahead == 'l') ADVANCE(81);
      if (lookahead == 'v') ADVANCE(123);
      END_STATE();
    case 137:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 138:
      if (lookahead == 'm') ADVANCE(304);
      END_STATE();
    case 139:
      if (lookahead == 'm') ADVANCE(308);
      END_STATE();
    case 140:
      if (lookahead == 'm') ADVANCE(305);
      END_STATE();
    case 141:
      if (lookahead == 'm') ADVANCE(110);
      END_STATE();
    case 142:
      if (lookahead == 'n') ADVANCE(46);
      if (lookahead == 'r') ADVANCE(42);
      if (lookahead == 'u') ADVANCE(170);
      END_STATE();
    case 143:
      if (lookahead == 'n') ADVANCE(317);
      END_STATE();
    case 144:
      if (lookahead == 'n') ADVANCE(90);
      if (lookahead == 's') ADVANCE(200);
      END_STATE();
    case 145:
      if (lookahead == 'n') ADVANCE(90);
      if (lookahead == 's') ADVANCE(216);
      END_STATE();
    case 146:
      if (lookahead == 'n') ADVANCE(309);
      END_STATE();
    case 147:
      if (lookahead == 'n') ADVANCE(292);
      if (lookahead == 't') ADVANCE(72);
      END_STATE();
    case 148:
      if (lookahead == 'n') ADVANCE(302);
      END_STATE();
    case 149:
      if (lookahead == 'n') ADVANCE(284);
      END_STATE();
    case 150:
      if (lookahead == 'n') ADVANCE(278);
      END_STATE();
    case 151:
      if (lookahead == 'n') ADVANCE(312);
      END_STATE();
    case 152:
      if (lookahead == 'n') ADVANCE(89);
      END_STATE();
    case 153:
      if (lookahead == 'n') ADVANCE(45);
      END_STATE();
    case 154:
      if (lookahead == 'n') ADVANCE(208);
      END_STATE();
    case 155:
      if (lookahead == 'n') ADVANCE(186);
      END_STATE();
    case 156:
      if (lookahead == 'n') ADVANCE(217);
      END_STATE();
    case 157:
      if (lookahead == 'o') ADVANCE(53);
      END_STATE();
    case 158:
      if (lookahead == 'o') ADVANCE(175);
      END_STATE();
    case 159:
      if (lookahead == 'o') ADVANCE(175);
      if (lookahead == 'v') ADVANCE(146);
      END_STATE();
    case 160:
      if (lookahead == 'o') ADVANCE(174);
      END_STATE();
    case 161:
      if (lookahead == 'o') ADVANCE(150);
      END_STATE();
    case 162:
      if (lookahead == 'o') ADVANCE(151);
      END_STATE();
    case 163:
      if (lookahead == 'o') ADVANCE(192);
      END_STATE();
    case 164:
      if (lookahead == 'p') ADVANCE(26);
      if (lookahead == 'r') ADVANCE(331);
      END_STATE();
    case 165:
      if (lookahead == 'p') ADVANCE(297);
      END_STATE();
    case 166:
      if (lookahead == 'p') ADVANCE(139);
      END_STATE();
    case 167:
      if (lookahead == 'p') ADVANCE(102);
      END_STATE();
    case 168:
      if (lookahead == 'p') ADVANCE(64);
      END_STATE();
    case 169:
      if (lookahead == 'r') ADVANCE(21);
      if (lookahead == 'v') ADVANCE(179);
      END_STATE();
    case 170:
      if (lookahead == 'r') ADVANCE(290);
      END_STATE();
    case 171:
      if (lookahead == 'r') ADVANCE(291);
      END_STATE();
    case 172:
      if (lookahead == 'r') ADVANCE(310);
      END_STATE();
    case 173:
      if (lookahead == 'r') ADVANCE(330);
      END_STATE();
    case 174:
      if (lookahead == 'r') ADVANCE(48);
      END_STATE();
    case 175:
      if (lookahead == 'r') ADVANCE(207);
      END_STATE();
    case 176:
      if (lookahead == 'r') ADVANCE(105);
      END_STATE();
    case 177:
      if (lookahead == 'r') ADVANCE(80);
      END_STATE();
    case 178:
      if (lookahead == 'r') ADVANCE(69);
      END_STATE();
    case 179:
      if (lookahead == 's') ADVANCE(294);
      END_STATE();
    case 180:
      if (lookahead == 's') ADVANCE(293);
      END_STATE();
    case 181:
      if (lookahead == 's') ADVANCE(275);
      END_STATE();
    case 182:
      if (lookahead == 's') ADVANCE(96);
      END_STATE();
    case 183:
      if (lookahead == 's') ADVANCE(200);
      END_STATE();
    case 184:
      if (lookahead == 's') ADVANCE(60);
      END_STATE();
    case 185:
      if (lookahead == 's') ADVANCE(106);
      END_STATE();
    case 186:
      if (lookahead == 's') ADVANCE(62);
      END_STATE();
    case 187:
      if (lookahead == 's') ADVANCE(65);
      END_STATE();
    case 188:
      if (lookahead == 's') ADVANCE(66);
      END_STATE();
    case 189:
      if (lookahead == 's') ADVANCE(111);
      END_STATE();
    case 190:
      if (lookahead == 's') ADVANCE(97);
      END_STATE();
    case 191:
      if (lookahead == 's') ADVANCE(120);
      END_STATE();
    case 192:
      if (lookahead == 's') ADVANCE(112);
      END_STATE();
    case 193:
      if (lookahead == 's') ADVANCE(114);
      END_STATE();
    case 194:
      if (lookahead == 's') ADVANCE(115);
      END_STATE();
    case 195:
      if (lookahead == 's') ADVANCE(116);
      END_STATE();
    case 196:
      if (lookahead == 's') ADVANCE(117);
      END_STATE();
    case 197:
      if (lookahead == 's') ADVANCE(118);
      END_STATE();
    case 198:
      if (lookahead == 't') ADVANCE(300);
      END_STATE();
    case 199:
      if (lookahead == 't') ADVANCE(2);
      END_STATE();
    case 200:
      if (lookahead == 't') ADVANCE(11);
      END_STATE();
    case 201:
      if (lookahead == 't') ADVANCE(283);
      END_STATE();
    case 202:
      if (lookahead == 't') ADVANCE(14);
      END_STATE();
    case 203:
      if (lookahead == 't') ADVANCE(296);
      END_STATE();
    case 204:
      if (lookahead == 't') ADVANCE(276);
      END_STATE();
    case 205:
      if (lookahead == 't') ADVANCE(277);
      END_STATE();
    case 206:
      if (lookahead == 't') ADVANCE(312);
      END_STATE();
    case 207:
      if (lookahead == 't') ADVANCE(12);
      END_STATE();
    case 208:
      if (lookahead == 't') ADVANCE(85);
      END_STATE();
    case 209:
      if (lookahead == 't') ADVANCE(15);
      END_STATE();
    case 210:
      if (lookahead == 't') ADVANCE(237);
      END_STATE();
    case 211:
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 212:
      if (lookahead == 't') ADVANCE(22);
      END_STATE();
    case 213:
      if (lookahead == 't') ADVANCE(70);
      END_STATE();
    case 214:
      if (lookahead == 't') ADVANCE(181);
      END_STATE();
    case 215:
      if (lookahead == 't') ADVANCE(77);
      END_STATE();
    case 216:
      if (lookahead == 't') ADVANCE(16);
      END_STATE();
    case 217:
      if (lookahead == 't') ADVANCE(88);
      END_STATE();
    case 218:
      if (lookahead == 'u') ADVANCE(38);
      if (lookahead == 'y') ADVANCE(167);
      END_STATE();
    case 219:
      if (lookahead == 'u') ADVANCE(132);
      END_STATE();
    case 220:
      if (lookahead == 'u') ADVANCE(40);
      END_STATE();
    case 221:
      if (lookahead == 'u') ADVANCE(59);
      END_STATE();
    case 222:
      if (lookahead == 'u') ADVANCE(104);
      END_STATE();
    case 223:
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 224:
      if (lookahead == 'u') ADVANCE(41);
      END_STATE();
    case 225:
      if (lookahead == 'u') ADVANCE(137);
      END_STATE();
    case 226:
      if (lookahead == 'v') ADVANCE(306);
      END_STATE();
    case 227:
      if (lookahead == 'v') ADVANCE(73);
      END_STATE();
    case 228:
      if (lookahead == 'v') ADVANCE(75);
      END_STATE();
    case 229:
      if (lookahead == 'v') ADVANCE(125);
      END_STATE();
    case 230:
      if (lookahead == 'v') ADVANCE(127);
      END_STATE();
    case 231:
      if (lookahead == 'v') ADVANCE(83);
      END_STATE();
    case 232:
      if (lookahead == 'w') ADVANCE(160);
      END_STATE();
    case 233:
      if (lookahead == 'x') ADVANCE(303);
      END_STATE();
    case 234:
      if (lookahead == 'x') ADVANCE(91);
      END_STATE();
    case 235:
      if (lookahead == 'y') ADVANCE(232);
      END_STATE();
    case 236:
      if (lookahead == 'y') ADVANCE(268);
      END_STATE();
    case 237:
      if (lookahead == 'y') ADVANCE(168);
      END_STATE();
    case 238:
      if (lookahead == 'z') ADVANCE(171);
      END_STATE();
    case 239:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(239);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(243);
      END_STATE();
    case 240:
      if (lookahead == '"' ||
          lookahead == '\'' ||
          lookahead == '/' ||
          lookahead == '\\' ||
          lookahead == 'b' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't' ||
          lookahead == 'u') ADVANCE(336);
      END_STATE();
    case 241:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(7);
      END_STATE();
    case 242:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(322);
      END_STATE();
    case 243:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 244:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(320);
      END_STATE();
    case 245:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(318);
      END_STATE();
    case 246:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(319);
      END_STATE();
    case 247:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(321);
      END_STATE();
    case 248:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(241);
      END_STATE();
    case 249:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(242);
      END_STATE();
    case 250:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(244);
      END_STATE();
    case 251:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(246);
      END_STATE();
    case 252:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(245);
      END_STATE();
    case 253:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(247);
      END_STATE();
    case 254:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 255:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(254);
      END_STATE();
    case 256:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(253);
      END_STATE();
    case 257:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(255);
      END_STATE();
    case 258:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 259:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(258);
      END_STATE();
    case 260:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(256);
      END_STATE();
    case 261:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(260);
      END_STATE();
    case 262:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(261);
      END_STATE();
    case 263:
      if (eof) ADVANCE(265);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(271);
      if (lookahead == '\'') ADVANCE(270);
      if (lookahead == '(') ADVANCE(266);
      if (lookahead == ')') ADVANCE(267);
      if (lookahead == ',') ADVANCE(272);
      if (lookahead == '-') ADVANCE(274);
      if (lookahead == ':') ADVANCE(316);
      if (lookahead == '<') ADVANCE(314);
      if (lookahead == '=') ADVANCE(313);
      if (lookahead == '>') ADVANCE(314);
      if (lookahead == '[') ADVANCE(269);
      if (lookahead == ']') ADVANCE(273);
      if (lookahead == 'a') ADVANCE(142);
      if (lookahead == 'b') ADVANCE(238);
      if (lookahead == 'c') ADVANCE(169);
      if (lookahead == 'd') ADVANCE(57);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'g') ADVANCE(99);
      if (lookahead == 'h') ADVANCE(23);
      if (lookahead == 'i') ADVANCE(143);
      if (lookahead == 'k') ADVANCE(58);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(20);
      if (lookahead == 'n') ADVANCE(100);
      if (lookahead == 'o') ADVANCE(164);
      if (lookahead == 'p') ADVANCE(218);
      if (lookahead == 'r') ADVANCE(166);
      if (lookahead == 's') ADVANCE(159);
      if (lookahead == 't') ADVANCE(27);
      if (lookahead == 'v') ADVANCE(103);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(263)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(326);
      END_STATE();
    case 264:
      if (eof) ADVANCE(265);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(271);
      if (lookahead == '\'') ADVANCE(270);
      if (lookahead == ')') ADVANCE(267);
      if (lookahead == ',') ADVANCE(272);
      if (lookahead == '-') ADVANCE(274);
      if (lookahead == '<') ADVANCE(314);
      if (lookahead == '=') ADVANCE(313);
      if (lookahead == '>') ADVANCE(314);
      if (lookahead == ']') ADVANCE(273);
      if (lookahead == 'a') ADVANCE(153);
      if (lookahead == 'c') ADVANCE(178);
      if (lookahead == 'l') ADVANCE(30);
      if (lookahead == 'm') ADVANCE(157);
      if (lookahead == 'o') ADVANCE(173);
      if (lookahead == 'p') ADVANCE(224);
      if (lookahead == 's') ADVANCE(158);
      if (lookahead == 'v') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(264)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(257);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(sym_sortByField);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(anon_sym_visits);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(anon_sym_last_visit);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(anon_sym_last_eventful_visit);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(anon_sym_last_revision);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(anon_sym_last_release);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(anon_sym_created);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(anon_sym_modified);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(anon_sym_published);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_limitField);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_patternField);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_booleanField);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_numericField);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_visitTypeField);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(anon_sym_any);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(anon_sym_arch);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(anon_sym_aur);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(anon_sym_bzr);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(anon_sym_cran);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_crates);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(anon_sym_cvs);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(anon_sym_deb);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(anon_sym_deposit);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_ftp);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(anon_sym_hackage);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(anon_sym_hg);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_git);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_golang);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_maven);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_nixguix);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_npm);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_opam);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(anon_sym_pubdev);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_pypi);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_rpm);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(anon_sym_svn);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(anon_sym_tar);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_listField);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_dateField);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_rangeOp);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_rangeOp);
      if (lookahead == '=') ADVANCE(313);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(sym_equalOp);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(sym_containOp);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(sym_choiceOp);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(sym_isoDateTime);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(259);
      if (lookahead == '.') ADVANCE(262);
      if (lookahead == 'Z') ADVANCE(318);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(259);
      if (lookahead == ':') ADVANCE(251);
      if (lookahead == 'Z') ADVANCE(318);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(259);
      if (lookahead == 'Z') ADVANCE(318);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(239);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(243);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(248);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(327);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(323);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(324);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(325);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(327);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(sym_booleanTrue);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(sym_booleanFalse);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(sym_or);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(sym_or);
      if (lookahead == 'i') ADVANCE(92);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_and);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_singleWord);
      if (!sym_singleWord_character_set_1(lookahead)) ADVANCE(333);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(334);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(335);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(335);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 5},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 5},
  [9] = {.lex_state = 5},
  [10] = {.lex_state = 5},
  [11] = {.lex_state = 5},
  [12] = {.lex_state = 264},
  [13] = {.lex_state = 264},
  [14] = {.lex_state = 264},
  [15] = {.lex_state = 264},
  [16] = {.lex_state = 264},
  [17] = {.lex_state = 264},
  [18] = {.lex_state = 264},
  [19] = {.lex_state = 264},
  [20] = {.lex_state = 264},
  [21] = {.lex_state = 264},
  [22] = {.lex_state = 264},
  [23] = {.lex_state = 264},
  [24] = {.lex_state = 264},
  [25] = {.lex_state = 264},
  [26] = {.lex_state = 264},
  [27] = {.lex_state = 264},
  [28] = {.lex_state = 264},
  [29] = {.lex_state = 264},
  [30] = {.lex_state = 264},
  [31] = {.lex_state = 264},
  [32] = {.lex_state = 264},
  [33] = {.lex_state = 264},
  [34] = {.lex_state = 264},
  [35] = {.lex_state = 264},
  [36] = {.lex_state = 264},
  [37] = {.lex_state = 264},
  [38] = {.lex_state = 264},
  [39] = {.lex_state = 264},
  [40] = {.lex_state = 264},
  [41] = {.lex_state = 264},
  [42] = {.lex_state = 264},
  [43] = {.lex_state = 264},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 264},
  [46] = {.lex_state = 264},
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
  [80] = {.lex_state = 264},
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
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 5},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 5},
  [101] = {.lex_state = 264},
  [102] = {.lex_state = 5},
  [103] = {.lex_state = 264},
  [104] = {.lex_state = 264},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 264},
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
    [anon_sym_arch] = ACTIONS(1),
    [anon_sym_aur] = ACTIONS(1),
    [anon_sym_bzr] = ACTIONS(1),
    [anon_sym_cran] = ACTIONS(1),
    [anon_sym_crates] = ACTIONS(1),
    [anon_sym_cvs] = ACTIONS(1),
    [anon_sym_deb] = ACTIONS(1),
    [anon_sym_deposit] = ACTIONS(1),
    [anon_sym_ftp] = ACTIONS(1),
    [anon_sym_hackage] = ACTIONS(1),
    [anon_sym_hg] = ACTIONS(1),
    [anon_sym_git] = ACTIONS(1),
    [anon_sym_golang] = ACTIONS(1),
    [anon_sym_maven] = ACTIONS(1),
    [anon_sym_nixguix] = ACTIONS(1),
    [anon_sym_npm] = ACTIONS(1),
    [anon_sym_opam] = ACTIONS(1),
    [anon_sym_pubdev] = ACTIONS(1),
    [anon_sym_pypi] = ACTIONS(1),
    [anon_sym_rpm] = ACTIONS(1),
    [anon_sym_svn] = ACTIONS(1),
    [anon_sym_tar] = ACTIONS(1),
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
  [0] = 5,
    ACTIONS(17), 1,
      anon_sym_SQUOTE,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    STATE(96), 1,
      sym_visitTypeOptions,
    ACTIONS(21), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
    ACTIONS(23), 23,
      anon_sym_any,
      anon_sym_arch,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hackage,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_golang,
      anon_sym_maven,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_opam,
      anon_sym_pubdev,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_svn,
      anon_sym_tar,
  [39] = 5,
    ACTIONS(25), 1,
      anon_sym_SQUOTE,
    ACTIONS(27), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 23,
      anon_sym_any,
      anon_sym_arch,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hackage,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_golang,
      anon_sym_maven,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_opam,
      anon_sym_pubdev,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_svn,
      anon_sym_tar,
  [77] = 2,
    STATE(106), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 23,
      anon_sym_any,
      anon_sym_arch,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hackage,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_golang,
      anon_sym_maven,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_opam,
      anon_sym_pubdev,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_svn,
      anon_sym_tar,
  [106] = 2,
    STATE(114), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 23,
      anon_sym_any,
      anon_sym_arch,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hackage,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_golang,
      anon_sym_maven,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_opam,
      anon_sym_pubdev,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_svn,
      anon_sym_tar,
  [135] = 2,
    STATE(111), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 23,
      anon_sym_any,
      anon_sym_arch,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hackage,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_golang,
      anon_sym_maven,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_opam,
      anon_sym_pubdev,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_svn,
      anon_sym_tar,
  [164] = 2,
    STATE(110), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 23,
      anon_sym_any,
      anon_sym_arch,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_ftp,
      anon_sym_hackage,
      anon_sym_hg,
      anon_sym_git,
      anon_sym_golang,
      anon_sym_maven,
      anon_sym_nixguix,
      anon_sym_npm,
      anon_sym_opam,
      anon_sym_pubdev,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_svn,
      anon_sym_tar,
  [193] = 15,
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
    ACTIONS(31), 1,
      sym_sortByField,
    ACTIONS(33), 1,
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
  [244] = 11,
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
  [283] = 11,
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
  [322] = 11,
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
  [361] = 6,
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
  [388] = 6,
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
  [414] = 3,
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
  [431] = 3,
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
  [448] = 3,
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
  [465] = 3,
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
  [482] = 1,
    ACTIONS(51), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [493] = 1,
    ACTIONS(53), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [504] = 1,
    ACTIONS(55), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [515] = 7,
    ACTIONS(31), 1,
      sym_sortByField,
    ACTIONS(33), 1,
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
  [537] = 1,
    ACTIONS(63), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [546] = 1,
    ACTIONS(65), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [555] = 1,
    ACTIONS(67), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [564] = 1,
    ACTIONS(69), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [573] = 1,
    ACTIONS(71), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [582] = 1,
    ACTIONS(73), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [591] = 1,
    ACTIONS(75), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [600] = 1,
    ACTIONS(77), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [609] = 1,
    ACTIONS(79), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [618] = 1,
    ACTIONS(81), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [627] = 1,
    ACTIONS(83), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [636] = 1,
    ACTIONS(85), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [645] = 1,
    ACTIONS(87), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [654] = 2,
    ACTIONS(89), 1,
      sym_and,
    ACTIONS(69), 5,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
  [665] = 1,
    ACTIONS(91), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [674] = 1,
    ACTIONS(93), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [683] = 1,
    ACTIONS(95), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [692] = 1,
    ACTIONS(97), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [701] = 1,
    ACTIONS(99), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [710] = 1,
    ACTIONS(101), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [719] = 1,
    ACTIONS(103), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [728] = 1,
    ACTIONS(105), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [737] = 5,
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
  [754] = 1,
    ACTIONS(115), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [763] = 1,
    ACTIONS(117), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [772] = 5,
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
  [788] = 5,
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
  [804] = 3,
    STATE(50), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(121), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(123), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [816] = 3,
    STATE(50), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(125), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(127), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [828] = 4,
    ACTIONS(33), 1,
      sym_limitField,
    ACTIONS(130), 1,
      ts_builtin_sym_end,
    ACTIONS(132), 1,
      sym_and,
    STATE(119), 1,
      sym_limit,
  [841] = 3,
    STATE(49), 1,
      aux_sym_stringContent_repeat1,
    STATE(124), 1,
      sym_stringContent,
    ACTIONS(134), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [852] = 1,
    ACTIONS(136), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [859] = 1,
    ACTIONS(138), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [866] = 4,
    ACTIONS(33), 1,
      sym_limitField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(142), 1,
      sym_and,
    STATE(109), 1,
      sym_limit,
  [879] = 4,
    ACTIONS(31), 1,
      sym_sortByField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(144), 1,
      sym_and,
    STATE(109), 1,
      sym_sortBy,
  [892] = 4,
    ACTIONS(31), 1,
      sym_sortByField,
    ACTIONS(130), 1,
      ts_builtin_sym_end,
    ACTIONS(146), 1,
      sym_and,
    STATE(119), 1,
      sym_sortBy,
  [905] = 1,
    ACTIONS(148), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [912] = 3,
    STATE(49), 1,
      aux_sym_stringContent_repeat1,
    STATE(120), 1,
      sym_stringContent,
    ACTIONS(134), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [923] = 2,
    STATE(41), 1,
      sym_booleanVal,
    ACTIONS(150), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [931] = 3,
    ACTIONS(33), 1,
      sym_limitField,
    ACTIONS(152), 1,
      ts_builtin_sym_end,
    STATE(112), 1,
      sym_limit,
  [941] = 1,
    ACTIONS(154), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [947] = 3,
    ACTIONS(31), 1,
      sym_sortByField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    STATE(109), 1,
      sym_sortBy,
  [957] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(158), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [967] = 1,
    ACTIONS(160), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [973] = 3,
    ACTIONS(162), 1,
      anon_sym_COMMA,
    ACTIONS(165), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [983] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(169), 1,
      anon_sym_RBRACK,
    STATE(73), 1,
      aux_sym_visitTypeVal_repeat1,
  [993] = 1,
    ACTIONS(171), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [999] = 3,
    ACTIONS(173), 1,
      anon_sym_COMMA,
    ACTIONS(175), 1,
      anon_sym_RBRACK,
    STATE(85), 1,
      aux_sym_listVal_repeat1,
  [1009] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(177), 1,
      anon_sym_RBRACK,
    STATE(64), 1,
      aux_sym_sortByVal_repeat1,
  [1019] = 1,
    ACTIONS(179), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1025] = 1,
    ACTIONS(181), 3,
      ts_builtin_sym_end,
      sym_sortByField,
      sym_and,
  [1031] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(183), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1041] = 3,
    ACTIONS(33), 1,
      sym_limitField,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    STATE(109), 1,
      sym_limit,
  [1051] = 3,
    ACTIONS(31), 1,
      sym_sortByField,
    ACTIONS(152), 1,
      ts_builtin_sym_end,
    STATE(112), 1,
      sym_sortBy,
  [1061] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(185), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [1071] = 1,
    ACTIONS(187), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1077] = 3,
    ACTIONS(189), 1,
      anon_sym_COMMA,
    ACTIONS(192), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      aux_sym_listVal_repeat1,
  [1087] = 3,
    ACTIONS(194), 1,
      anon_sym_COMMA,
    ACTIONS(197), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1097] = 3,
    ACTIONS(59), 1,
      sym_or,
    ACTIONS(89), 1,
      sym_and,
    ACTIONS(199), 1,
      anon_sym_RPAREN,
  [1107] = 1,
    ACTIONS(201), 3,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym_singleWord,
  [1113] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(203), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1123] = 3,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    ACTIONS(205), 1,
      anon_sym_RBRACK,
    STATE(82), 1,
      aux_sym_visitTypeVal_repeat1,
  [1133] = 1,
    ACTIONS(207), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1139] = 3,
    ACTIONS(173), 1,
      anon_sym_COMMA,
    ACTIONS(209), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      aux_sym_listVal_repeat1,
  [1149] = 3,
    ACTIONS(156), 1,
      anon_sym_COMMA,
    ACTIONS(211), 1,
      anon_sym_RBRACK,
    STATE(76), 1,
      aux_sym_sortByVal_repeat1,
  [1159] = 2,
    ACTIONS(213), 1,
      sym_choiceOp,
    STATE(98), 1,
      sym_listOp,
  [1166] = 1,
    ACTIONS(215), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1171] = 2,
    ACTIONS(217), 1,
      sym_number,
    STATE(43), 1,
      sym_numberVal,
  [1178] = 1,
    ACTIONS(219), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1183] = 2,
    ACTIONS(221), 1,
      sym_containOp,
    STATE(48), 1,
      sym_patternOp,
  [1190] = 2,
    ACTIONS(223), 1,
      anon_sym_LBRACK,
    STATE(71), 1,
      sym_sortByVal,
  [1197] = 1,
    ACTIONS(225), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1202] = 2,
    ACTIONS(227), 1,
      sym_equalOp,
    STATE(60), 1,
      sym_booleanOp,
  [1209] = 2,
    ACTIONS(229), 1,
      anon_sym_LBRACK,
    STATE(45), 1,
      sym_visitTypeVal,
  [1216] = 1,
    ACTIONS(231), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1221] = 1,
    ACTIONS(233), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [1226] = 2,
    ACTIONS(235), 1,
      anon_sym_LBRACK,
    STATE(46), 1,
      sym_listVal,
  [1233] = 1,
    ACTIONS(237), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1238] = 2,
    ACTIONS(239), 1,
      sym_equalOp,
    STATE(92), 1,
      sym_sortByOp,
  [1245] = 2,
    ACTIONS(241), 1,
      sym_rangeOp,
    STATE(89), 1,
      sym_numericOp,
  [1252] = 2,
    ACTIONS(243), 1,
      sym_equalOp,
    STATE(95), 1,
      sym_visitTypeOp,
  [1259] = 2,
    ACTIONS(245), 1,
      sym_isoDateTime,
    STATE(26), 1,
      sym_dateVal,
  [1266] = 2,
    ACTIONS(247), 1,
      sym_rangeOp,
    STATE(103), 1,
      sym_dateOp,
  [1273] = 1,
    ACTIONS(249), 1,
      anon_sym_LBRACK,
  [1277] = 1,
    ACTIONS(251), 1,
      anon_sym_SQUOTE,
  [1281] = 1,
    ACTIONS(253), 1,
      sym_isoDateTime,
  [1285] = 1,
    ACTIONS(255), 1,
      anon_sym_DQUOTE,
  [1289] = 1,
    ACTIONS(152), 1,
      ts_builtin_sym_end,
  [1293] = 1,
    ACTIONS(257), 1,
      anon_sym_SQUOTE,
  [1297] = 1,
    ACTIONS(257), 1,
      anon_sym_DQUOTE,
  [1301] = 1,
    ACTIONS(259), 1,
      ts_builtin_sym_end,
  [1305] = 1,
    ACTIONS(255), 1,
      anon_sym_SQUOTE,
  [1309] = 1,
    ACTIONS(251), 1,
      anon_sym_DQUOTE,
  [1313] = 1,
    ACTIONS(261), 1,
      sym_number,
  [1317] = 1,
    ACTIONS(263), 1,
      ts_builtin_sym_end,
  [1321] = 1,
    ACTIONS(265), 1,
      sym_equalOp,
  [1325] = 1,
    ACTIONS(267), 1,
      anon_sym_LBRACK,
  [1329] = 1,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
  [1333] = 1,
    ACTIONS(269), 1,
      anon_sym_DQUOTE,
  [1337] = 1,
    ACTIONS(271), 1,
      anon_sym_LBRACK,
  [1341] = 1,
    ACTIONS(273), 1,
      anon_sym_SQUOTE,
  [1345] = 1,
    ACTIONS(273), 1,
      anon_sym_DQUOTE,
  [1349] = 1,
    ACTIONS(269), 1,
      anon_sym_SQUOTE,
  [1353] = 1,
    ACTIONS(275), 1,
      sym_number,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 39,
  [SMALL_STATE(4)] = 77,
  [SMALL_STATE(5)] = 106,
  [SMALL_STATE(6)] = 135,
  [SMALL_STATE(7)] = 164,
  [SMALL_STATE(8)] = 193,
  [SMALL_STATE(9)] = 244,
  [SMALL_STATE(10)] = 283,
  [SMALL_STATE(11)] = 322,
  [SMALL_STATE(12)] = 361,
  [SMALL_STATE(13)] = 388,
  [SMALL_STATE(14)] = 414,
  [SMALL_STATE(15)] = 431,
  [SMALL_STATE(16)] = 448,
  [SMALL_STATE(17)] = 465,
  [SMALL_STATE(18)] = 482,
  [SMALL_STATE(19)] = 493,
  [SMALL_STATE(20)] = 504,
  [SMALL_STATE(21)] = 515,
  [SMALL_STATE(22)] = 537,
  [SMALL_STATE(23)] = 546,
  [SMALL_STATE(24)] = 555,
  [SMALL_STATE(25)] = 564,
  [SMALL_STATE(26)] = 573,
  [SMALL_STATE(27)] = 582,
  [SMALL_STATE(28)] = 591,
  [SMALL_STATE(29)] = 600,
  [SMALL_STATE(30)] = 609,
  [SMALL_STATE(31)] = 618,
  [SMALL_STATE(32)] = 627,
  [SMALL_STATE(33)] = 636,
  [SMALL_STATE(34)] = 645,
  [SMALL_STATE(35)] = 654,
  [SMALL_STATE(36)] = 665,
  [SMALL_STATE(37)] = 674,
  [SMALL_STATE(38)] = 683,
  [SMALL_STATE(39)] = 692,
  [SMALL_STATE(40)] = 701,
  [SMALL_STATE(41)] = 710,
  [SMALL_STATE(42)] = 719,
  [SMALL_STATE(43)] = 728,
  [SMALL_STATE(44)] = 737,
  [SMALL_STATE(45)] = 754,
  [SMALL_STATE(46)] = 763,
  [SMALL_STATE(47)] = 772,
  [SMALL_STATE(48)] = 788,
  [SMALL_STATE(49)] = 804,
  [SMALL_STATE(50)] = 816,
  [SMALL_STATE(51)] = 828,
  [SMALL_STATE(52)] = 841,
  [SMALL_STATE(53)] = 852,
  [SMALL_STATE(54)] = 859,
  [SMALL_STATE(55)] = 866,
  [SMALL_STATE(56)] = 879,
  [SMALL_STATE(57)] = 892,
  [SMALL_STATE(58)] = 905,
  [SMALL_STATE(59)] = 912,
  [SMALL_STATE(60)] = 923,
  [SMALL_STATE(61)] = 931,
  [SMALL_STATE(62)] = 941,
  [SMALL_STATE(63)] = 947,
  [SMALL_STATE(64)] = 957,
  [SMALL_STATE(65)] = 967,
  [SMALL_STATE(66)] = 973,
  [SMALL_STATE(67)] = 983,
  [SMALL_STATE(68)] = 993,
  [SMALL_STATE(69)] = 999,
  [SMALL_STATE(70)] = 1009,
  [SMALL_STATE(71)] = 1019,
  [SMALL_STATE(72)] = 1025,
  [SMALL_STATE(73)] = 1031,
  [SMALL_STATE(74)] = 1041,
  [SMALL_STATE(75)] = 1051,
  [SMALL_STATE(76)] = 1061,
  [SMALL_STATE(77)] = 1071,
  [SMALL_STATE(78)] = 1077,
  [SMALL_STATE(79)] = 1087,
  [SMALL_STATE(80)] = 1097,
  [SMALL_STATE(81)] = 1107,
  [SMALL_STATE(82)] = 1113,
  [SMALL_STATE(83)] = 1123,
  [SMALL_STATE(84)] = 1133,
  [SMALL_STATE(85)] = 1139,
  [SMALL_STATE(86)] = 1149,
  [SMALL_STATE(87)] = 1159,
  [SMALL_STATE(88)] = 1166,
  [SMALL_STATE(89)] = 1171,
  [SMALL_STATE(90)] = 1178,
  [SMALL_STATE(91)] = 1183,
  [SMALL_STATE(92)] = 1190,
  [SMALL_STATE(93)] = 1197,
  [SMALL_STATE(94)] = 1202,
  [SMALL_STATE(95)] = 1209,
  [SMALL_STATE(96)] = 1216,
  [SMALL_STATE(97)] = 1221,
  [SMALL_STATE(98)] = 1226,
  [SMALL_STATE(99)] = 1233,
  [SMALL_STATE(100)] = 1238,
  [SMALL_STATE(101)] = 1245,
  [SMALL_STATE(102)] = 1252,
  [SMALL_STATE(103)] = 1259,
  [SMALL_STATE(104)] = 1266,
  [SMALL_STATE(105)] = 1273,
  [SMALL_STATE(106)] = 1277,
  [SMALL_STATE(107)] = 1281,
  [SMALL_STATE(108)] = 1285,
  [SMALL_STATE(109)] = 1289,
  [SMALL_STATE(110)] = 1293,
  [SMALL_STATE(111)] = 1297,
  [SMALL_STATE(112)] = 1301,
  [SMALL_STATE(113)] = 1305,
  [SMALL_STATE(114)] = 1309,
  [SMALL_STATE(115)] = 1313,
  [SMALL_STATE(116)] = 1317,
  [SMALL_STATE(117)] = 1321,
  [SMALL_STATE(118)] = 1325,
  [SMALL_STATE(119)] = 1329,
  [SMALL_STATE(120)] = 1333,
  [SMALL_STATE(121)] = 1337,
  [SMALL_STATE(122)] = 1341,
  [SMALL_STATE(123)] = 1345,
  [SMALL_STATE(124)] = 1349,
  [SMALL_STATE(125)] = 1353,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 1),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
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
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
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
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
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
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [160] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 5, .production_id = 7),
  [162] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(12),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
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
  [194] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(2),
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
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 4, .production_id = 7),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
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
