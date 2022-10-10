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
#define SYMBOL_COUNT 102
#define ALIAS_COUNT 0
#define TOKEN_COUNT 68
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
  anon_sym_archive = 25,
  anon_sym_aur = 26,
  anon_sym_bzr = 27,
  anon_sym_conda = 28,
  anon_sym_content = 29,
  anon_sym_cpan = 30,
  anon_sym_cran = 31,
  anon_sym_crates = 32,
  anon_sym_cvs = 33,
  anon_sym_deb = 34,
  anon_sym_deposit = 35,
  anon_sym_directory = 36,
  anon_sym_ftp = 37,
  anon_sym_hackage = 38,
  anon_sym_hg = 39,
  anon_sym_git = 40,
  anon_sym_golang = 41,
  anon_sym_maven = 42,
  anon_sym_nixguix = 43,
  anon_sym_npm = 44,
  anon_sym_opam = 45,
  anon_sym_pubdev = 46,
  anon_sym_puppet = 47,
  anon_sym_pypi = 48,
  anon_sym_rpm = 49,
  anon_sym_rubygems = 50,
  anon_sym_svn = 51,
  anon_sym_tar = 52,
  sym_listField = 53,
  sym_dateField = 54,
  sym_rangeOp = 55,
  sym_equalOp = 56,
  sym_containOp = 57,
  sym_choiceOp = 58,
  sym_isoDateTime = 59,
  sym_number = 60,
  sym_booleanTrue = 61,
  sym_booleanFalse = 62,
  sym_or = 63,
  sym_and = 64,
  sym_singleWord = 65,
  aux_sym_stringContent_token1 = 66,
  sym_escape_sequence = 67,
  sym_query = 68,
  sym_filters = 69,
  sym_sortBy = 70,
  sym_sortByOp = 71,
  sym_sortByVal = 72,
  sym_sortByOptions = 73,
  sym_limit = 74,
  sym_filter = 75,
  sym_patternFilter = 76,
  sym_patternOp = 77,
  sym_patternVal = 78,
  sym_booleanFilter = 79,
  sym_booleanOp = 80,
  sym_booleanVal = 81,
  sym_numericFilter = 82,
  sym_numericOp = 83,
  sym_numberVal = 84,
  sym_boundedListFilter = 85,
  sym_visitTypeFilter = 86,
  sym_visitTypeOp = 87,
  sym_visitTypeVal = 88,
  sym_visitTypeOptions = 89,
  sym_unboundedListFilter = 90,
  sym_listOp = 91,
  sym_listVal = 92,
  sym_dateFilter = 93,
  sym_dateOp = 94,
  sym_dateVal = 95,
  sym_string = 96,
  sym_stringContent = 97,
  aux_sym_sortByVal_repeat1 = 98,
  aux_sym_visitTypeVal_repeat1 = 99,
  aux_sym_listVal_repeat1 = 100,
  aux_sym_stringContent_repeat1 = 101,
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
  [anon_sym_archive] = "archive",
  [anon_sym_aur] = "aur",
  [anon_sym_bzr] = "bzr",
  [anon_sym_conda] = "conda",
  [anon_sym_content] = "content",
  [anon_sym_cpan] = "cpan",
  [anon_sym_cran] = "cran",
  [anon_sym_crates] = "crates",
  [anon_sym_cvs] = "cvs",
  [anon_sym_deb] = "deb",
  [anon_sym_deposit] = "deposit",
  [anon_sym_directory] = "directory",
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
  [anon_sym_puppet] = "puppet",
  [anon_sym_pypi] = "pypi",
  [anon_sym_rpm] = "rpm",
  [anon_sym_rubygems] = "rubygems",
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
  [anon_sym_archive] = anon_sym_archive,
  [anon_sym_aur] = anon_sym_aur,
  [anon_sym_bzr] = anon_sym_bzr,
  [anon_sym_conda] = anon_sym_conda,
  [anon_sym_content] = anon_sym_content,
  [anon_sym_cpan] = anon_sym_cpan,
  [anon_sym_cran] = anon_sym_cran,
  [anon_sym_crates] = anon_sym_crates,
  [anon_sym_cvs] = anon_sym_cvs,
  [anon_sym_deb] = anon_sym_deb,
  [anon_sym_deposit] = anon_sym_deposit,
  [anon_sym_directory] = anon_sym_directory,
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
  [anon_sym_puppet] = anon_sym_puppet,
  [anon_sym_pypi] = anon_sym_pypi,
  [anon_sym_rpm] = anon_sym_rpm,
  [anon_sym_rubygems] = anon_sym_rubygems,
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
  [anon_sym_archive] = {
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
  [anon_sym_conda] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_content] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cpan] = {
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
  [anon_sym_directory] = {
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
  [anon_sym_puppet] = {
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
  [anon_sym_rubygems] = {
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
      if (eof) ADVANCE(291);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(296);
      if (lookahead == '(') ADVANCE(292);
      if (lookahead == ')') ADVANCE(293);
      if (lookahead == ',') ADVANCE(298);
      if (lookahead == '-') ADVANCE(300);
      if (lookahead == ':') ADVANCE(349);
      if (lookahead == '<') ADVANCE(347);
      if (lookahead == '=') ADVANCE(346);
      if (lookahead == '>') ADVANCE(347);
      if (lookahead == '[') ADVANCE(295);
      if (lookahead == '\\') ADVANCE(266);
      if (lookahead == ']') ADVANCE(299);
      if (lookahead == 'a') ADVANCE(154);
      if (lookahead == 'b') ADVANCE(264);
      if (lookahead == 'c') ADVANCE(173);
      if (lookahead == 'd') ADVANCE(62);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'g') ADVANCE(110);
      if (lookahead == 'h') ADVANCE(24);
      if (lookahead == 'i') ADVANCE(155);
      if (lookahead == 'k') ADVANCE(63);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(20);
      if (lookahead == 'n') ADVANCE(111);
      if (lookahead == 'o') ADVANCE(182);
      if (lookahead == 'p') ADVANCE(241);
      if (lookahead == 'r') ADVANCE(183);
      if (lookahead == 's') ADVANCE(175);
      if (lookahead == 't') ADVANCE(29);
      if (lookahead == 'v') ADVANCE(114);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(289)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(359);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(4)
      if (lookahead == '"') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(296);
      if (lookahead == '\\') ADVANCE(266);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(367);
      if (lookahead != 0) ADVANCE(368);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(109);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(296);
      if (lookahead == ',') ADVANCE(298);
      if (lookahead == ']') ADVANCE(299);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '[') ADVANCE(366);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(296);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      END_STATE();
    case 5:
      if (lookahead == '(') ADVANCE(292);
      if (lookahead == '=') ADVANCE(348);
      if (lookahead == 'c') ADVANCE(196);
      if (lookahead == 'k') ADVANCE(63);
      if (lookahead == 'l') ADVANCE(38);
      if (lookahead == 'm') ADVANCE(73);
      if (lookahead == 'o') ADVANCE(195);
      if (lookahead == 'p') ADVANCE(242);
      if (lookahead == 's') ADVANCE(174);
      if (lookahead == 'v') ADVANCE(137);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(360);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(274);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(275);
      END_STATE();
    case 8:
      if (lookahead == ':') ADVANCE(276);
      END_STATE();
    case 9:
      if (lookahead == ':') ADVANCE(278);
      END_STATE();
    case 10:
      if (lookahead == '=') ADVANCE(346);
      END_STATE();
    case 11:
      if (lookahead == '_') ADVANCE(89);
      END_STATE();
    case 12:
      if (lookahead == '_') ADVANCE(253);
      END_STATE();
    case 13:
      if (lookahead == '_') ADVANCE(233);
      if (lookahead == 'e') ADVANCE(53);
      if (lookahead == 's') ADVANCE(301);
      END_STATE();
    case 14:
      if (lookahead == '_') ADVANCE(233);
      if (lookahead == 'e') ADVANCE(53);
      if (lookahead == 's') ADVANCE(312);
      END_STATE();
    case 15:
      if (lookahead == '_') ADVANCE(42);
      END_STATE();
    case 16:
      if (lookahead == '_') ADVANCE(94);
      END_STATE();
    case 17:
      if (lookahead == '_') ADVANCE(254);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(141);
      if (lookahead == 't') ADVANCE(181);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(157);
      if (lookahead == 'i') ADVANCE(47);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(251);
      if (lookahead == 'e') ADVANCE(232);
      if (lookahead == 'o') ADVANCE(57);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(161);
      if (lookahead == 'e') ADVANCE(30);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(319);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(310);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(46);
      if (lookahead == 'g') ADVANCE(330);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(60);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(151);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(160);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(166);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(189);
      if (lookahead == 'r') ADVANCE(244);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(235);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(203);
      if (lookahead == 'i') ADVANCE(152);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(234);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(104);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(237);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(207);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(105);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(208);
      END_STATE();
    case 38:
      if (lookahead == 'a') ADVANCE(158);
      if (lookahead == 'i') ADVANCE(47);
      END_STATE();
    case 39:
      if (lookahead == 'b') ADVANCE(325);
      if (lookahead == 'p') ADVANCE(180);
      END_STATE();
    case 40:
      if (lookahead == 'b') ADVANCE(59);
      if (lookahead == 'p') ADVANCE(185);
      END_STATE();
    case 41:
      if (lookahead == 'b') ADVANCE(262);
      END_STATE();
    case 42:
      if (lookahead == 'b') ADVANCE(260);
      END_STATE();
    case 43:
      if (lookahead == 'b') ADVANCE(146);
      END_STATE();
    case 44:
      if (lookahead == 'b') ADVANCE(144);
      END_STATE();
    case 45:
      if (lookahead == 'c') ADVANCE(106);
      END_STATE();
    case 46:
      if (lookahead == 'c') ADVANCE(140);
      END_STATE();
    case 47:
      if (lookahead == 'c') ADVANCE(80);
      if (lookahead == 'm') ADVANCE(120);
      END_STATE();
    case 48:
      if (lookahead == 'c') ADVANCE(238);
      END_STATE();
    case 49:
      if (lookahead == 'd') ADVANCE(365);
      END_STATE();
    case 50:
      if (lookahead == 'd') ADVANCE(365);
      if (lookahead == 'y') ADVANCE(314);
      END_STATE();
    case 51:
      if (lookahead == 'd') ADVANCE(306);
      END_STATE();
    case 52:
      if (lookahead == 'd') ADVANCE(344);
      END_STATE();
    case 53:
      if (lookahead == 'd') ADVANCE(311);
      END_STATE();
    case 54:
      if (lookahead == 'd') ADVANCE(307);
      END_STATE();
    case 55:
      if (lookahead == 'd') ADVANCE(308);
      END_STATE();
    case 56:
      if (lookahead == 'd') ADVANCE(345);
      END_STATE();
    case 57:
      if (lookahead == 'd') ADVANCE(112);
      END_STATE();
    case 58:
      if (lookahead == 'd') ADVANCE(22);
      if (lookahead == 't') ADVANCE(84);
      END_STATE();
    case 59:
      if (lookahead == 'd') ADVANCE(74);
      if (lookahead == 'l') ADVANCE(118);
      END_STATE();
    case 60:
      if (lookahead == 'd') ADVANCE(32);
      END_STATE();
    case 61:
      if (lookahead == 'd') ADVANCE(133);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(39);
      if (lookahead == 'i') ADVANCE(191);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(259);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(361);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(362);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(316);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(329);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(344);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(143);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(313);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(305);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(345);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(232);
      if (lookahead == 'o') ADVANCE(61);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(249);
      END_STATE();
    case 75:
      if (lookahead == 'e') ADVANCE(48);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(30);
      END_STATE();
    case 77:
      if (lookahead == 'e') ADVANCE(51);
      END_STATE();
    case 78:
      if (lookahead == 'e') ADVANCE(199);
      END_STATE();
    case 79:
      if (lookahead == 'e') ADVANCE(153);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(170);
      END_STATE();
    case 81:
      if (lookahead == 'e') ADVANCE(54);
      END_STATE();
    case 82:
      if (lookahead == 'e') ADVANCE(162);
      END_STATE();
    case 83:
      if (lookahead == 'e') ADVANCE(55);
      END_STATE();
    case 84:
      if (lookahead == 'e') ADVANCE(168);
      END_STATE();
    case 85:
      if (lookahead == 'e') ADVANCE(56);
      END_STATE();
    case 86:
      if (lookahead == 'e') ADVANCE(35);
      END_STATE();
    case 87:
      if (lookahead == 'e') ADVANCE(223);
      END_STATE();
    case 88:
      if (lookahead == 'e') ADVANCE(169);
      END_STATE();
    case 89:
      if (lookahead == 'e') ADVANCE(252);
      if (lookahead == 'r') ADVANCE(69);
      if (lookahead == 'v') ADVANCE(135);
      END_STATE();
    case 90:
      if (lookahead == 'e') ADVANCE(34);
      END_STATE();
    case 91:
      if (lookahead == 'e') ADVANCE(37);
      END_STATE();
    case 92:
      if (lookahead == 'e') ADVANCE(147);
      END_STATE();
    case 93:
      if (lookahead == 'e') ADVANCE(171);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(255);
      if (lookahead == 'r') ADVANCE(92);
      if (lookahead == 'v') ADVANCE(138);
      END_STATE();
    case 95:
      if (lookahead == 'f') ADVANCE(243);
      END_STATE();
    case 96:
      if (lookahead == 'f') ADVANCE(124);
      END_STATE();
    case 97:
      if (lookahead == 'f') ADVANCE(130);
      END_STATE();
    case 98:
      if (lookahead == 'f') ADVANCE(248);
      END_STATE();
    case 99:
      if (lookahead == 'g') ADVANCE(332);
      END_STATE();
    case 100:
      if (lookahead == 'g') ADVANCE(246);
      END_STATE();
    case 101:
      if (lookahead == 'g') ADVANCE(245);
      END_STATE();
    case 102:
      if (lookahead == 'g') ADVANCE(122);
      END_STATE();
    case 103:
      if (lookahead == 'g') ADVANCE(79);
      END_STATE();
    case 104:
      if (lookahead == 'g') ADVANCE(67);
      END_STATE();
    case 105:
      if (lookahead == 'g') ADVANCE(68);
      END_STATE();
    case 106:
      if (lookahead == 'h') ADVANCE(315);
      END_STATE();
    case 107:
      if (lookahead == 'h') ADVANCE(83);
      END_STATE();
    case 108:
      if (lookahead == 'h') ADVANCE(85);
      END_STATE();
    case 109:
      if (lookahead == 'i') ADVANCE(155);
      END_STATE();
    case 110:
      if (lookahead == 'i') ADVANCE(218);
      if (lookahead == 'o') ADVANCE(145);
      END_STATE();
    case 111:
      if (lookahead == 'i') ADVANCE(258);
      if (lookahead == 'o') ADVANCE(219);
      if (lookahead == 'p') ADVANCE(149);
      END_STATE();
    case 112:
      if (lookahead == 'i') ADVANCE(96);
      END_STATE();
    case 113:
      if (lookahead == 'i') ADVANCE(339);
      END_STATE();
    case 114:
      if (lookahead == 'i') ADVANCE(209);
      END_STATE();
    case 115:
      if (lookahead == 'i') ADVANCE(257);
      END_STATE();
    case 116:
      if (lookahead == 'i') ADVANCE(102);
      END_STATE();
    case 117:
      if (lookahead == 'i') ADVANCE(178);
      END_STATE();
    case 118:
      if (lookahead == 'i') ADVANCE(202);
      END_STATE();
    case 119:
      if (lookahead == 'i') ADVANCE(205);
      END_STATE();
    case 120:
      if (lookahead == 'i') ADVANCE(221);
      END_STATE();
    case 121:
      if (lookahead == 'i') ADVANCE(222);
      END_STATE();
    case 122:
      if (lookahead == 'i') ADVANCE(163);
      END_STATE();
    case 123:
      if (lookahead == 'i') ADVANCE(225);
      END_STATE();
    case 124:
      if (lookahead == 'i') ADVANCE(81);
      END_STATE();
    case 125:
      if (lookahead == 'i') ADVANCE(226);
      END_STATE();
    case 126:
      if (lookahead == 'i') ADVANCE(227);
      END_STATE();
    case 127:
      if (lookahead == 'i') ADVANCE(231);
      END_STATE();
    case 128:
      if (lookahead == 'i') ADVANCE(228);
      END_STATE();
    case 129:
      if (lookahead == 'i') ADVANCE(236);
      END_STATE();
    case 130:
      if (lookahead == 'i') ADVANCE(85);
      END_STATE();
    case 131:
      if (lookahead == 'i') ADVANCE(179);
      END_STATE();
    case 132:
      if (lookahead == 'i') ADVANCE(210);
      END_STATE();
    case 133:
      if (lookahead == 'i') ADVANCE(97);
      END_STATE();
    case 134:
      if (lookahead == 'i') ADVANCE(211);
      END_STATE();
    case 135:
      if (lookahead == 'i') ADVANCE(213);
      END_STATE();
    case 136:
      if (lookahead == 'i') ADVANCE(214);
      END_STATE();
    case 137:
      if (lookahead == 'i') ADVANCE(215);
      END_STATE();
    case 138:
      if (lookahead == 'i') ADVANCE(216);
      END_STATE();
    case 139:
      if (lookahead == 'i') ADVANCE(217);
      END_STATE();
    case 140:
      if (lookahead == 'k') ADVANCE(33);
      END_STATE();
    case 141:
      if (lookahead == 'l') ADVANCE(204);
      END_STATE();
    case 142:
      if (lookahead == 'l') ADVANCE(12);
      END_STATE();
    case 143:
      if (lookahead == 'l') ADVANCE(86);
      if (lookahead == 'v') ADVANCE(119);
      END_STATE();
    case 144:
      if (lookahead == 'l') ADVANCE(118);
      END_STATE();
    case 145:
      if (lookahead == 'l') ADVANCE(28);
      END_STATE();
    case 146:
      if (lookahead == 'l') ADVANCE(132);
      END_STATE();
    case 147:
      if (lookahead == 'l') ADVANCE(91);
      if (lookahead == 'v') ADVANCE(134);
      END_STATE();
    case 148:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 149:
      if (lookahead == 'm') ADVANCE(335);
      END_STATE();
    case 150:
      if (lookahead == 'm') ADVANCE(340);
      END_STATE();
    case 151:
      if (lookahead == 'm') ADVANCE(336);
      END_STATE();
    case 152:
      if (lookahead == 'm') ADVANCE(120);
      END_STATE();
    case 153:
      if (lookahead == 'm') ADVANCE(201);
      END_STATE();
    case 154:
      if (lookahead == 'n') ADVANCE(50);
      if (lookahead == 'r') ADVANCE(45);
      if (lookahead == 'u') ADVANCE(187);
      END_STATE();
    case 155:
      if (lookahead == 'n') ADVANCE(350);
      END_STATE();
    case 156:
      if (lookahead == 'n') ADVANCE(58);
      END_STATE();
    case 157:
      if (lookahead == 'n') ADVANCE(100);
      if (lookahead == 's') ADVANCE(220);
      END_STATE();
    case 158:
      if (lookahead == 'n') ADVANCE(100);
      if (lookahead == 's') ADVANCE(239);
      END_STATE();
    case 159:
      if (lookahead == 'n') ADVANCE(342);
      END_STATE();
    case 160:
      if (lookahead == 'n') ADVANCE(321);
      END_STATE();
    case 161:
      if (lookahead == 'n') ADVANCE(322);
      if (lookahead == 't') ADVANCE(78);
      END_STATE();
    case 162:
      if (lookahead == 'n') ADVANCE(333);
      END_STATE();
    case 163:
      if (lookahead == 'n') ADVANCE(310);
      END_STATE();
    case 164:
      if (lookahead == 'n') ADVANCE(304);
      END_STATE();
    case 165:
      if (lookahead == 'n') ADVANCE(345);
      END_STATE();
    case 166:
      if (lookahead == 'n') ADVANCE(99);
      END_STATE();
    case 167:
      if (lookahead == 'n') ADVANCE(49);
      END_STATE();
    case 168:
      if (lookahead == 'n') ADVANCE(224);
      END_STATE();
    case 169:
      if (lookahead == 'n') ADVANCE(230);
      END_STATE();
    case 170:
      if (lookahead == 'n') ADVANCE(206);
      END_STATE();
    case 171:
      if (lookahead == 'n') ADVANCE(240);
      END_STATE();
    case 172:
      if (lookahead == 'o') ADVANCE(57);
      END_STATE();
    case 173:
      if (lookahead == 'o') ADVANCE(156);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'r') ADVANCE(21);
      if (lookahead == 'v') ADVANCE(198);
      END_STATE();
    case 174:
      if (lookahead == 'o') ADVANCE(193);
      END_STATE();
    case 175:
      if (lookahead == 'o') ADVANCE(193);
      if (lookahead == 'v') ADVANCE(159);
      END_STATE();
    case 176:
      if (lookahead == 'o') ADVANCE(192);
      END_STATE();
    case 177:
      if (lookahead == 'o') ADVANCE(194);
      END_STATE();
    case 178:
      if (lookahead == 'o') ADVANCE(164);
      END_STATE();
    case 179:
      if (lookahead == 'o') ADVANCE(165);
      END_STATE();
    case 180:
      if (lookahead == 'o') ADVANCE(212);
      END_STATE();
    case 181:
      if (lookahead == 'p') ADVANCE(328);
      END_STATE();
    case 182:
      if (lookahead == 'p') ADVANCE(26);
      if (lookahead == 'r') ADVANCE(364);
      END_STATE();
    case 183:
      if (lookahead == 'p') ADVANCE(150);
      if (lookahead == 'u') ADVANCE(41);
      END_STATE();
    case 184:
      if (lookahead == 'p') ADVANCE(113);
      END_STATE();
    case 185:
      if (lookahead == 'p') ADVANCE(87);
      END_STATE();
    case 186:
      if (lookahead == 'p') ADVANCE(70);
      END_STATE();
    case 187:
      if (lookahead == 'r') ADVANCE(317);
      END_STATE();
    case 188:
      if (lookahead == 'r') ADVANCE(318);
      END_STATE();
    case 189:
      if (lookahead == 'r') ADVANCE(343);
      END_STATE();
    case 190:
      if (lookahead == 'r') ADVANCE(363);
      END_STATE();
    case 191:
      if (lookahead == 'r') ADVANCE(75);
      END_STATE();
    case 192:
      if (lookahead == 'r') ADVANCE(52);
      END_STATE();
    case 193:
      if (lookahead == 'r') ADVANCE(229);
      END_STATE();
    case 194:
      if (lookahead == 'r') ADVANCE(261);
      END_STATE();
    case 195:
      if (lookahead == 'r') ADVANCE(116);
      END_STATE();
    case 196:
      if (lookahead == 'r') ADVANCE(90);
      END_STATE();
    case 197:
      if (lookahead == 'r') ADVANCE(76);
      END_STATE();
    case 198:
      if (lookahead == 's') ADVANCE(324);
      END_STATE();
    case 199:
      if (lookahead == 's') ADVANCE(323);
      END_STATE();
    case 200:
      if (lookahead == 's') ADVANCE(301);
      END_STATE();
    case 201:
      if (lookahead == 's') ADVANCE(341);
      END_STATE();
    case 202:
      if (lookahead == 's') ADVANCE(107);
      END_STATE();
    case 203:
      if (lookahead == 's') ADVANCE(220);
      END_STATE();
    case 204:
      if (lookahead == 's') ADVANCE(65);
      END_STATE();
    case 205:
      if (lookahead == 's') ADVANCE(117);
      END_STATE();
    case 206:
      if (lookahead == 's') ADVANCE(68);
      END_STATE();
    case 207:
      if (lookahead == 's') ADVANCE(71);
      END_STATE();
    case 208:
      if (lookahead == 's') ADVANCE(72);
      END_STATE();
    case 209:
      if (lookahead == 's') ADVANCE(121);
      END_STATE();
    case 210:
      if (lookahead == 's') ADVANCE(108);
      END_STATE();
    case 211:
      if (lookahead == 's') ADVANCE(131);
      END_STATE();
    case 212:
      if (lookahead == 's') ADVANCE(123);
      END_STATE();
    case 213:
      if (lookahead == 's') ADVANCE(125);
      END_STATE();
    case 214:
      if (lookahead == 's') ADVANCE(126);
      END_STATE();
    case 215:
      if (lookahead == 's') ADVANCE(127);
      END_STATE();
    case 216:
      if (lookahead == 's') ADVANCE(128);
      END_STATE();
    case 217:
      if (lookahead == 's') ADVANCE(129);
      END_STATE();
    case 218:
      if (lookahead == 't') ADVANCE(331);
      END_STATE();
    case 219:
      if (lookahead == 't') ADVANCE(2);
      END_STATE();
    case 220:
      if (lookahead == 't') ADVANCE(11);
      END_STATE();
    case 221:
      if (lookahead == 't') ADVANCE(309);
      END_STATE();
    case 222:
      if (lookahead == 't') ADVANCE(13);
      END_STATE();
    case 223:
      if (lookahead == 't') ADVANCE(338);
      END_STATE();
    case 224:
      if (lookahead == 't') ADVANCE(320);
      END_STATE();
    case 225:
      if (lookahead == 't') ADVANCE(326);
      END_STATE();
    case 226:
      if (lookahead == 't') ADVANCE(302);
      END_STATE();
    case 227:
      if (lookahead == 't') ADVANCE(303);
      END_STATE();
    case 228:
      if (lookahead == 't') ADVANCE(345);
      END_STATE();
    case 229:
      if (lookahead == 't') ADVANCE(15);
      END_STATE();
    case 230:
      if (lookahead == 't') ADVANCE(95);
      END_STATE();
    case 231:
      if (lookahead == 't') ADVANCE(14);
      END_STATE();
    case 232:
      if (lookahead == 't') ADVANCE(25);
      END_STATE();
    case 233:
      if (lookahead == 't') ADVANCE(263);
      END_STATE();
    case 234:
      if (lookahead == 't') ADVANCE(23);
      END_STATE();
    case 235:
      if (lookahead == 't') ADVANCE(77);
      END_STATE();
    case 236:
      if (lookahead == 't') ADVANCE(200);
      END_STATE();
    case 237:
      if (lookahead == 't') ADVANCE(85);
      END_STATE();
    case 238:
      if (lookahead == 't') ADVANCE(177);
      END_STATE();
    case 239:
      if (lookahead == 't') ADVANCE(16);
      END_STATE();
    case 240:
      if (lookahead == 't') ADVANCE(98);
      END_STATE();
    case 241:
      if (lookahead == 'u') ADVANCE(40);
      if (lookahead == 'y') ADVANCE(184);
      END_STATE();
    case 242:
      if (lookahead == 'u') ADVANCE(43);
      END_STATE();
    case 243:
      if (lookahead == 'u') ADVANCE(142);
      END_STATE();
    case 244:
      if (lookahead == 'u') ADVANCE(64);
      END_STATE();
    case 245:
      if (lookahead == 'u') ADVANCE(115);
      END_STATE();
    case 246:
      if (lookahead == 'u') ADVANCE(36);
      END_STATE();
    case 247:
      if (lookahead == 'u') ADVANCE(44);
      END_STATE();
    case 248:
      if (lookahead == 'u') ADVANCE(148);
      END_STATE();
    case 249:
      if (lookahead == 'v') ADVANCE(337);
      END_STATE();
    case 250:
      if (lookahead == 'v') ADVANCE(66);
      END_STATE();
    case 251:
      if (lookahead == 'v') ADVANCE(82);
      END_STATE();
    case 252:
      if (lookahead == 'v') ADVANCE(88);
      END_STATE();
    case 253:
      if (lookahead == 'v') ADVANCE(136);
      END_STATE();
    case 254:
      if (lookahead == 'v') ADVANCE(138);
      END_STATE();
    case 255:
      if (lookahead == 'v') ADVANCE(93);
      END_STATE();
    case 256:
      if (lookahead == 'w') ADVANCE(176);
      END_STATE();
    case 257:
      if (lookahead == 'x') ADVANCE(334);
      END_STATE();
    case 258:
      if (lookahead == 'x') ADVANCE(101);
      END_STATE();
    case 259:
      if (lookahead == 'y') ADVANCE(256);
      END_STATE();
    case 260:
      if (lookahead == 'y') ADVANCE(294);
      END_STATE();
    case 261:
      if (lookahead == 'y') ADVANCE(327);
      END_STATE();
    case 262:
      if (lookahead == 'y') ADVANCE(103);
      END_STATE();
    case 263:
      if (lookahead == 'y') ADVANCE(186);
      END_STATE();
    case 264:
      if (lookahead == 'z') ADVANCE(188);
      END_STATE();
    case 265:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(265);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(269);
      END_STATE();
    case 266:
      if (lookahead == '"' ||
          lookahead == '\'' ||
          lookahead == '/' ||
          lookahead == '\\' ||
          lookahead == 'b' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't' ||
          lookahead == 'u') ADVANCE(369);
      END_STATE();
    case 267:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(7);
      END_STATE();
    case 268:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(355);
      END_STATE();
    case 269:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 270:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(353);
      END_STATE();
    case 271:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(351);
      END_STATE();
    case 272:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(352);
      END_STATE();
    case 273:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(354);
      END_STATE();
    case 274:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(267);
      END_STATE();
    case 275:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(268);
      END_STATE();
    case 276:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(270);
      END_STATE();
    case 277:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(272);
      END_STATE();
    case 278:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(271);
      END_STATE();
    case 279:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(273);
      END_STATE();
    case 280:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 281:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(280);
      END_STATE();
    case 282:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(279);
      END_STATE();
    case 283:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(281);
      END_STATE();
    case 284:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 285:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(284);
      END_STATE();
    case 286:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(282);
      END_STATE();
    case 287:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(286);
      END_STATE();
    case 288:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(287);
      END_STATE();
    case 289:
      if (eof) ADVANCE(291);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(296);
      if (lookahead == '(') ADVANCE(292);
      if (lookahead == ')') ADVANCE(293);
      if (lookahead == ',') ADVANCE(298);
      if (lookahead == '-') ADVANCE(300);
      if (lookahead == ':') ADVANCE(349);
      if (lookahead == '<') ADVANCE(347);
      if (lookahead == '=') ADVANCE(346);
      if (lookahead == '>') ADVANCE(347);
      if (lookahead == '[') ADVANCE(295);
      if (lookahead == ']') ADVANCE(299);
      if (lookahead == 'a') ADVANCE(154);
      if (lookahead == 'b') ADVANCE(264);
      if (lookahead == 'c') ADVANCE(173);
      if (lookahead == 'd') ADVANCE(62);
      if (lookahead == 'f') ADVANCE(18);
      if (lookahead == 'g') ADVANCE(110);
      if (lookahead == 'h') ADVANCE(24);
      if (lookahead == 'i') ADVANCE(155);
      if (lookahead == 'k') ADVANCE(63);
      if (lookahead == 'l') ADVANCE(19);
      if (lookahead == 'm') ADVANCE(20);
      if (lookahead == 'n') ADVANCE(111);
      if (lookahead == 'o') ADVANCE(182);
      if (lookahead == 'p') ADVANCE(241);
      if (lookahead == 'r') ADVANCE(183);
      if (lookahead == 's') ADVANCE(175);
      if (lookahead == 't') ADVANCE(29);
      if (lookahead == 'v') ADVANCE(114);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(289)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(359);
      END_STATE();
    case 290:
      if (eof) ADVANCE(291);
      if (lookahead == '!') ADVANCE(10);
      if (lookahead == '"') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(296);
      if (lookahead == ')') ADVANCE(293);
      if (lookahead == ',') ADVANCE(298);
      if (lookahead == '-') ADVANCE(300);
      if (lookahead == '<') ADVANCE(347);
      if (lookahead == '=') ADVANCE(346);
      if (lookahead == '>') ADVANCE(347);
      if (lookahead == ']') ADVANCE(299);
      if (lookahead == 'a') ADVANCE(167);
      if (lookahead == 'c') ADVANCE(197);
      if (lookahead == 'l') ADVANCE(31);
      if (lookahead == 'm') ADVANCE(172);
      if (lookahead == 'o') ADVANCE(190);
      if (lookahead == 'p') ADVANCE(247);
      if (lookahead == 's') ADVANCE(174);
      if (lookahead == 'v') ADVANCE(139);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(290)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(283);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_sortByField);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_visits);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_last_visit);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_last_eventful_visit);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_last_revision);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_last_release);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(anon_sym_created);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_modified);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_published);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(sym_limitField);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(sym_patternField);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_booleanField);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_numericField);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_visitTypeField);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(anon_sym_any);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(anon_sym_arch);
      if (lookahead == 'i') ADVANCE(250);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(anon_sym_archive);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(anon_sym_aur);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(anon_sym_bzr);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(anon_sym_conda);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(anon_sym_content);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(anon_sym_cpan);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(anon_sym_cran);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(anon_sym_crates);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(anon_sym_cvs);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(anon_sym_deb);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(anon_sym_deposit);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(anon_sym_directory);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(anon_sym_ftp);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(anon_sym_hackage);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(anon_sym_hg);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(anon_sym_git);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(anon_sym_golang);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(anon_sym_maven);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(anon_sym_nixguix);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(anon_sym_npm);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(anon_sym_opam);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(anon_sym_pubdev);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(anon_sym_puppet);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(anon_sym_pypi);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(anon_sym_rpm);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(anon_sym_rubygems);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(anon_sym_svn);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(anon_sym_tar);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_listField);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_dateField);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_rangeOp);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_rangeOp);
      if (lookahead == '=') ADVANCE(346);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_equalOp);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_containOp);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(sym_choiceOp);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(sym_isoDateTime);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(285);
      if (lookahead == '.') ADVANCE(288);
      if (lookahead == 'Z') ADVANCE(351);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(285);
      if (lookahead == ':') ADVANCE(277);
      if (lookahead == 'Z') ADVANCE(351);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '+') ADVANCE(285);
      if (lookahead == 'Z') ADVANCE(351);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(sym_isoDateTime);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 'T') ADVANCE(265);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(269);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '-') ADVANCE(274);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(360);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(356);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(357);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(358);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(360);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(sym_booleanTrue);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(sym_booleanFalse);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(sym_or);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(sym_or);
      if (lookahead == 'i') ADVANCE(102);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(sym_and);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(sym_singleWord);
      if (!sym_singleWord_character_set_1(lookahead)) ADVANCE(366);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(367);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(368);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(aux_sym_stringContent_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(368);
      END_STATE();
    case 369:
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
  [12] = {.lex_state = 290},
  [13] = {.lex_state = 290},
  [14] = {.lex_state = 290},
  [15] = {.lex_state = 290},
  [16] = {.lex_state = 290},
  [17] = {.lex_state = 290},
  [18] = {.lex_state = 290},
  [19] = {.lex_state = 290},
  [20] = {.lex_state = 290},
  [21] = {.lex_state = 290},
  [22] = {.lex_state = 290},
  [23] = {.lex_state = 290},
  [24] = {.lex_state = 290},
  [25] = {.lex_state = 290},
  [26] = {.lex_state = 290},
  [27] = {.lex_state = 290},
  [28] = {.lex_state = 290},
  [29] = {.lex_state = 290},
  [30] = {.lex_state = 290},
  [31] = {.lex_state = 290},
  [32] = {.lex_state = 290},
  [33] = {.lex_state = 290},
  [34] = {.lex_state = 290},
  [35] = {.lex_state = 290},
  [36] = {.lex_state = 290},
  [37] = {.lex_state = 290},
  [38] = {.lex_state = 290},
  [39] = {.lex_state = 290},
  [40] = {.lex_state = 290},
  [41] = {.lex_state = 290},
  [42] = {.lex_state = 290},
  [43] = {.lex_state = 290},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 290},
  [46] = {.lex_state = 290},
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
  [80] = {.lex_state = 290},
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
  [101] = {.lex_state = 290},
  [102] = {.lex_state = 5},
  [103] = {.lex_state = 290},
  [104] = {.lex_state = 290},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 290},
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
    [anon_sym_archive] = ACTIONS(1),
    [anon_sym_aur] = ACTIONS(1),
    [anon_sym_bzr] = ACTIONS(1),
    [anon_sym_conda] = ACTIONS(1),
    [anon_sym_content] = ACTIONS(1),
    [anon_sym_cpan] = ACTIONS(1),
    [anon_sym_cran] = ACTIONS(1),
    [anon_sym_crates] = ACTIONS(1),
    [anon_sym_cvs] = ACTIONS(1),
    [anon_sym_deb] = ACTIONS(1),
    [anon_sym_deposit] = ACTIONS(1),
    [anon_sym_directory] = ACTIONS(1),
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
    [anon_sym_puppet] = ACTIONS(1),
    [anon_sym_pypi] = ACTIONS(1),
    [anon_sym_rpm] = ACTIONS(1),
    [anon_sym_rubygems] = ACTIONS(1),
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
  [0] = 6,
    ACTIONS(17), 1,
      anon_sym_SQUOTE,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(25), 1,
      anon_sym_arch,
    STATE(96), 1,
      sym_visitTypeOptions,
    ACTIONS(21), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
    ACTIONS(23), 29,
      anon_sym_any,
      anon_sym_archive,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_conda,
      anon_sym_content,
      anon_sym_cpan,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_directory,
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
      anon_sym_puppet,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_rubygems,
      anon_sym_svn,
      anon_sym_tar,
  [48] = 6,
    ACTIONS(25), 1,
      anon_sym_arch,
    ACTIONS(27), 1,
      anon_sym_SQUOTE,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 29,
      anon_sym_any,
      anon_sym_archive,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_conda,
      anon_sym_content,
      anon_sym_cpan,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_directory,
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
      anon_sym_puppet,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_rubygems,
      anon_sym_svn,
      anon_sym_tar,
  [95] = 3,
    ACTIONS(25), 1,
      anon_sym_arch,
    STATE(106), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 29,
      anon_sym_any,
      anon_sym_archive,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_conda,
      anon_sym_content,
      anon_sym_cpan,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_directory,
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
      anon_sym_puppet,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_rubygems,
      anon_sym_svn,
      anon_sym_tar,
  [133] = 3,
    ACTIONS(25), 1,
      anon_sym_arch,
    STATE(114), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 29,
      anon_sym_any,
      anon_sym_archive,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_conda,
      anon_sym_content,
      anon_sym_cpan,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_directory,
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
      anon_sym_puppet,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_rubygems,
      anon_sym_svn,
      anon_sym_tar,
  [171] = 3,
    ACTIONS(25), 1,
      anon_sym_arch,
    STATE(111), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 29,
      anon_sym_any,
      anon_sym_archive,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_conda,
      anon_sym_content,
      anon_sym_cpan,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_directory,
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
      anon_sym_puppet,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_rubygems,
      anon_sym_svn,
      anon_sym_tar,
  [209] = 3,
    ACTIONS(25), 1,
      anon_sym_arch,
    STATE(110), 1,
      sym_visitTypeOptions,
    ACTIONS(23), 29,
      anon_sym_any,
      anon_sym_archive,
      anon_sym_aur,
      anon_sym_bzr,
      anon_sym_conda,
      anon_sym_content,
      anon_sym_cpan,
      anon_sym_cran,
      anon_sym_crates,
      anon_sym_cvs,
      anon_sym_deb,
      anon_sym_deposit,
      anon_sym_directory,
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
      anon_sym_puppet,
      anon_sym_pypi,
      anon_sym_rpm,
      anon_sym_rubygems,
      anon_sym_svn,
      anon_sym_tar,
  [247] = 15,
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
    ACTIONS(33), 1,
      sym_sortByField,
    ACTIONS(35), 1,
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
  [298] = 11,
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
  [337] = 11,
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
  [376] = 11,
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
  [415] = 6,
    ACTIONS(37), 1,
      anon_sym_SQUOTE,
    ACTIONS(39), 1,
      anon_sym_DQUOTE,
    ACTIONS(43), 1,
      anon_sym_DASH,
    STATE(88), 1,
      sym_sortByOptions,
    ACTIONS(41), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
    ACTIONS(45), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [442] = 6,
    ACTIONS(43), 1,
      anon_sym_DASH,
    ACTIONS(47), 1,
      anon_sym_SQUOTE,
    ACTIONS(49), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      anon_sym_RBRACK,
    STATE(86), 1,
      sym_sortByOptions,
    ACTIONS(45), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [468] = 3,
    ACTIONS(43), 1,
      anon_sym_DASH,
    STATE(108), 1,
      sym_sortByOptions,
    ACTIONS(45), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [485] = 3,
    ACTIONS(43), 1,
      anon_sym_DASH,
    STATE(123), 1,
      sym_sortByOptions,
    ACTIONS(45), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [502] = 3,
    ACTIONS(43), 1,
      anon_sym_DASH,
    STATE(122), 1,
      sym_sortByOptions,
    ACTIONS(45), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [519] = 3,
    ACTIONS(43), 1,
      anon_sym_DASH,
    STATE(113), 1,
      sym_sortByOptions,
    ACTIONS(45), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [536] = 1,
    ACTIONS(53), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [547] = 1,
    ACTIONS(55), 8,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      anon_sym_COMMA,
      anon_sym_RBRACK,
      sym_limitField,
      sym_or,
      sym_and,
  [558] = 1,
    ACTIONS(57), 8,
      anon_sym_visits,
      anon_sym_last_visit,
      anon_sym_last_eventful_visit,
      anon_sym_last_revision,
      anon_sym_last_release,
      anon_sym_created,
      anon_sym_modified,
      anon_sym_published,
  [569] = 7,
    ACTIONS(33), 1,
      sym_sortByField,
    ACTIONS(35), 1,
      sym_limitField,
    ACTIONS(59), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      sym_or,
    ACTIONS(63), 1,
      sym_and,
    STATE(51), 1,
      sym_sortBy,
    STATE(57), 1,
      sym_limit,
  [591] = 1,
    ACTIONS(65), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [600] = 1,
    ACTIONS(67), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [609] = 1,
    ACTIONS(69), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [618] = 1,
    ACTIONS(71), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [627] = 1,
    ACTIONS(73), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [636] = 1,
    ACTIONS(75), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [645] = 1,
    ACTIONS(77), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [654] = 1,
    ACTIONS(79), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [663] = 1,
    ACTIONS(81), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [672] = 1,
    ACTIONS(83), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [681] = 1,
    ACTIONS(85), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [690] = 1,
    ACTIONS(87), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [699] = 1,
    ACTIONS(89), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [708] = 2,
    ACTIONS(91), 1,
      sym_and,
    ACTIONS(71), 5,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
  [719] = 1,
    ACTIONS(93), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [728] = 1,
    ACTIONS(95), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [737] = 1,
    ACTIONS(97), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [746] = 1,
    ACTIONS(99), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [755] = 1,
    ACTIONS(101), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [764] = 1,
    ACTIONS(103), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [773] = 1,
    ACTIONS(105), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [782] = 1,
    ACTIONS(107), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [791] = 5,
    ACTIONS(109), 1,
      anon_sym_SQUOTE,
    ACTIONS(111), 1,
      anon_sym_DQUOTE,
    ACTIONS(115), 1,
      sym_singleWord,
    STATE(99), 1,
      sym_string,
    ACTIONS(113), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [808] = 1,
    ACTIONS(117), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [817] = 1,
    ACTIONS(119), 6,
      ts_builtin_sym_end,
      anon_sym_RPAREN,
      sym_sortByField,
      sym_limitField,
      sym_or,
      sym_and,
  [826] = 5,
    ACTIONS(109), 1,
      anon_sym_SQUOTE,
    ACTIONS(111), 1,
      anon_sym_DQUOTE,
    ACTIONS(115), 1,
      sym_singleWord,
    ACTIONS(121), 1,
      anon_sym_RBRACK,
    STATE(69), 1,
      sym_string,
  [842] = 5,
    ACTIONS(109), 1,
      anon_sym_SQUOTE,
    ACTIONS(111), 1,
      anon_sym_DQUOTE,
    ACTIONS(115), 1,
      sym_singleWord,
    STATE(38), 1,
      sym_patternVal,
    STATE(39), 1,
      sym_string,
  [858] = 3,
    STATE(50), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(123), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(125), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [870] = 3,
    STATE(50), 1,
      aux_sym_stringContent_repeat1,
    ACTIONS(127), 2,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
    ACTIONS(129), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [882] = 4,
    ACTIONS(35), 1,
      sym_limitField,
    ACTIONS(132), 1,
      ts_builtin_sym_end,
    ACTIONS(134), 1,
      sym_and,
    STATE(119), 1,
      sym_limit,
  [895] = 3,
    STATE(49), 1,
      aux_sym_stringContent_repeat1,
    STATE(124), 1,
      sym_stringContent,
    ACTIONS(136), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [906] = 1,
    ACTIONS(138), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [913] = 1,
    ACTIONS(140), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [920] = 4,
    ACTIONS(35), 1,
      sym_limitField,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
    ACTIONS(144), 1,
      sym_and,
    STATE(109), 1,
      sym_limit,
  [933] = 4,
    ACTIONS(33), 1,
      sym_sortByField,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
    ACTIONS(146), 1,
      sym_and,
    STATE(109), 1,
      sym_sortBy,
  [946] = 4,
    ACTIONS(33), 1,
      sym_sortByField,
    ACTIONS(132), 1,
      ts_builtin_sym_end,
    ACTIONS(148), 1,
      sym_and,
    STATE(119), 1,
      sym_sortBy,
  [959] = 1,
    ACTIONS(150), 4,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [966] = 3,
    STATE(49), 1,
      aux_sym_stringContent_repeat1,
    STATE(120), 1,
      sym_stringContent,
    ACTIONS(136), 2,
      aux_sym_stringContent_token1,
      sym_escape_sequence,
  [977] = 2,
    STATE(41), 1,
      sym_booleanVal,
    ACTIONS(152), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [985] = 3,
    ACTIONS(35), 1,
      sym_limitField,
    ACTIONS(154), 1,
      ts_builtin_sym_end,
    STATE(112), 1,
      sym_limit,
  [995] = 1,
    ACTIONS(156), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1001] = 3,
    ACTIONS(33), 1,
      sym_sortByField,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
    STATE(109), 1,
      sym_sortBy,
  [1011] = 3,
    ACTIONS(158), 1,
      anon_sym_COMMA,
    ACTIONS(160), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [1021] = 1,
    ACTIONS(162), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1027] = 3,
    ACTIONS(164), 1,
      anon_sym_COMMA,
    ACTIONS(167), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [1037] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(171), 1,
      anon_sym_RBRACK,
    STATE(73), 1,
      aux_sym_visitTypeVal_repeat1,
  [1047] = 1,
    ACTIONS(173), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1053] = 3,
    ACTIONS(175), 1,
      anon_sym_COMMA,
    ACTIONS(177), 1,
      anon_sym_RBRACK,
    STATE(85), 1,
      aux_sym_listVal_repeat1,
  [1063] = 3,
    ACTIONS(158), 1,
      anon_sym_COMMA,
    ACTIONS(179), 1,
      anon_sym_RBRACK,
    STATE(64), 1,
      aux_sym_sortByVal_repeat1,
  [1073] = 1,
    ACTIONS(181), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1079] = 1,
    ACTIONS(183), 3,
      ts_builtin_sym_end,
      sym_sortByField,
      sym_and,
  [1085] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(185), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1095] = 3,
    ACTIONS(35), 1,
      sym_limitField,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
    STATE(109), 1,
      sym_limit,
  [1105] = 3,
    ACTIONS(33), 1,
      sym_sortByField,
    ACTIONS(154), 1,
      ts_builtin_sym_end,
    STATE(112), 1,
      sym_sortBy,
  [1115] = 3,
    ACTIONS(158), 1,
      anon_sym_COMMA,
    ACTIONS(187), 1,
      anon_sym_RBRACK,
    STATE(66), 1,
      aux_sym_sortByVal_repeat1,
  [1125] = 1,
    ACTIONS(189), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1131] = 3,
    ACTIONS(191), 1,
      anon_sym_COMMA,
    ACTIONS(194), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      aux_sym_listVal_repeat1,
  [1141] = 3,
    ACTIONS(196), 1,
      anon_sym_COMMA,
    ACTIONS(199), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1151] = 3,
    ACTIONS(61), 1,
      sym_or,
    ACTIONS(91), 1,
      sym_and,
    ACTIONS(201), 1,
      anon_sym_RPAREN,
  [1161] = 1,
    ACTIONS(203), 3,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym_singleWord,
  [1167] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(205), 1,
      anon_sym_RBRACK,
    STATE(79), 1,
      aux_sym_visitTypeVal_repeat1,
  [1177] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(207), 1,
      anon_sym_RBRACK,
    STATE(82), 1,
      aux_sym_visitTypeVal_repeat1,
  [1187] = 1,
    ACTIONS(209), 3,
      ts_builtin_sym_end,
      sym_limitField,
      sym_and,
  [1193] = 3,
    ACTIONS(175), 1,
      anon_sym_COMMA,
    ACTIONS(211), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      aux_sym_listVal_repeat1,
  [1203] = 3,
    ACTIONS(158), 1,
      anon_sym_COMMA,
    ACTIONS(213), 1,
      anon_sym_RBRACK,
    STATE(76), 1,
      aux_sym_sortByVal_repeat1,
  [1213] = 2,
    ACTIONS(215), 1,
      sym_choiceOp,
    STATE(98), 1,
      sym_listOp,
  [1220] = 1,
    ACTIONS(217), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1225] = 2,
    ACTIONS(219), 1,
      sym_number,
    STATE(43), 1,
      sym_numberVal,
  [1232] = 1,
    ACTIONS(221), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1237] = 2,
    ACTIONS(223), 1,
      sym_containOp,
    STATE(48), 1,
      sym_patternOp,
  [1244] = 2,
    ACTIONS(225), 1,
      anon_sym_LBRACK,
    STATE(71), 1,
      sym_sortByVal,
  [1251] = 1,
    ACTIONS(227), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1256] = 2,
    ACTIONS(229), 1,
      sym_equalOp,
    STATE(60), 1,
      sym_booleanOp,
  [1263] = 2,
    ACTIONS(231), 1,
      anon_sym_LBRACK,
    STATE(45), 1,
      sym_visitTypeVal,
  [1270] = 1,
    ACTIONS(233), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1275] = 1,
    ACTIONS(235), 2,
      sym_booleanTrue,
      sym_booleanFalse,
  [1280] = 2,
    ACTIONS(237), 1,
      anon_sym_LBRACK,
    STATE(46), 1,
      sym_listVal,
  [1287] = 1,
    ACTIONS(239), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [1292] = 2,
    ACTIONS(241), 1,
      sym_equalOp,
    STATE(92), 1,
      sym_sortByOp,
  [1299] = 2,
    ACTIONS(243), 1,
      sym_rangeOp,
    STATE(89), 1,
      sym_numericOp,
  [1306] = 2,
    ACTIONS(245), 1,
      sym_equalOp,
    STATE(95), 1,
      sym_visitTypeOp,
  [1313] = 2,
    ACTIONS(247), 1,
      sym_isoDateTime,
    STATE(26), 1,
      sym_dateVal,
  [1320] = 2,
    ACTIONS(249), 1,
      sym_rangeOp,
    STATE(103), 1,
      sym_dateOp,
  [1327] = 1,
    ACTIONS(251), 1,
      anon_sym_LBRACK,
  [1331] = 1,
    ACTIONS(253), 1,
      anon_sym_SQUOTE,
  [1335] = 1,
    ACTIONS(255), 1,
      sym_isoDateTime,
  [1339] = 1,
    ACTIONS(257), 1,
      anon_sym_DQUOTE,
  [1343] = 1,
    ACTIONS(154), 1,
      ts_builtin_sym_end,
  [1347] = 1,
    ACTIONS(259), 1,
      anon_sym_SQUOTE,
  [1351] = 1,
    ACTIONS(259), 1,
      anon_sym_DQUOTE,
  [1355] = 1,
    ACTIONS(261), 1,
      ts_builtin_sym_end,
  [1359] = 1,
    ACTIONS(257), 1,
      anon_sym_SQUOTE,
  [1363] = 1,
    ACTIONS(253), 1,
      anon_sym_DQUOTE,
  [1367] = 1,
    ACTIONS(263), 1,
      sym_number,
  [1371] = 1,
    ACTIONS(265), 1,
      ts_builtin_sym_end,
  [1375] = 1,
    ACTIONS(267), 1,
      sym_equalOp,
  [1379] = 1,
    ACTIONS(269), 1,
      anon_sym_LBRACK,
  [1383] = 1,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
  [1387] = 1,
    ACTIONS(271), 1,
      anon_sym_DQUOTE,
  [1391] = 1,
    ACTIONS(273), 1,
      anon_sym_LBRACK,
  [1395] = 1,
    ACTIONS(275), 1,
      anon_sym_SQUOTE,
  [1399] = 1,
    ACTIONS(275), 1,
      anon_sym_DQUOTE,
  [1403] = 1,
    ACTIONS(271), 1,
      anon_sym_SQUOTE,
  [1407] = 1,
    ACTIONS(277), 1,
      sym_number,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 48,
  [SMALL_STATE(4)] = 95,
  [SMALL_STATE(5)] = 133,
  [SMALL_STATE(6)] = 171,
  [SMALL_STATE(7)] = 209,
  [SMALL_STATE(8)] = 247,
  [SMALL_STATE(9)] = 298,
  [SMALL_STATE(10)] = 337,
  [SMALL_STATE(11)] = 376,
  [SMALL_STATE(12)] = 415,
  [SMALL_STATE(13)] = 442,
  [SMALL_STATE(14)] = 468,
  [SMALL_STATE(15)] = 485,
  [SMALL_STATE(16)] = 502,
  [SMALL_STATE(17)] = 519,
  [SMALL_STATE(18)] = 536,
  [SMALL_STATE(19)] = 547,
  [SMALL_STATE(20)] = 558,
  [SMALL_STATE(21)] = 569,
  [SMALL_STATE(22)] = 591,
  [SMALL_STATE(23)] = 600,
  [SMALL_STATE(24)] = 609,
  [SMALL_STATE(25)] = 618,
  [SMALL_STATE(26)] = 627,
  [SMALL_STATE(27)] = 636,
  [SMALL_STATE(28)] = 645,
  [SMALL_STATE(29)] = 654,
  [SMALL_STATE(30)] = 663,
  [SMALL_STATE(31)] = 672,
  [SMALL_STATE(32)] = 681,
  [SMALL_STATE(33)] = 690,
  [SMALL_STATE(34)] = 699,
  [SMALL_STATE(35)] = 708,
  [SMALL_STATE(36)] = 719,
  [SMALL_STATE(37)] = 728,
  [SMALL_STATE(38)] = 737,
  [SMALL_STATE(39)] = 746,
  [SMALL_STATE(40)] = 755,
  [SMALL_STATE(41)] = 764,
  [SMALL_STATE(42)] = 773,
  [SMALL_STATE(43)] = 782,
  [SMALL_STATE(44)] = 791,
  [SMALL_STATE(45)] = 808,
  [SMALL_STATE(46)] = 817,
  [SMALL_STATE(47)] = 826,
  [SMALL_STATE(48)] = 842,
  [SMALL_STATE(49)] = 858,
  [SMALL_STATE(50)] = 870,
  [SMALL_STATE(51)] = 882,
  [SMALL_STATE(52)] = 895,
  [SMALL_STATE(53)] = 906,
  [SMALL_STATE(54)] = 913,
  [SMALL_STATE(55)] = 920,
  [SMALL_STATE(56)] = 933,
  [SMALL_STATE(57)] = 946,
  [SMALL_STATE(58)] = 959,
  [SMALL_STATE(59)] = 966,
  [SMALL_STATE(60)] = 977,
  [SMALL_STATE(61)] = 985,
  [SMALL_STATE(62)] = 995,
  [SMALL_STATE(63)] = 1001,
  [SMALL_STATE(64)] = 1011,
  [SMALL_STATE(65)] = 1021,
  [SMALL_STATE(66)] = 1027,
  [SMALL_STATE(67)] = 1037,
  [SMALL_STATE(68)] = 1047,
  [SMALL_STATE(69)] = 1053,
  [SMALL_STATE(70)] = 1063,
  [SMALL_STATE(71)] = 1073,
  [SMALL_STATE(72)] = 1079,
  [SMALL_STATE(73)] = 1085,
  [SMALL_STATE(74)] = 1095,
  [SMALL_STATE(75)] = 1105,
  [SMALL_STATE(76)] = 1115,
  [SMALL_STATE(77)] = 1125,
  [SMALL_STATE(78)] = 1131,
  [SMALL_STATE(79)] = 1141,
  [SMALL_STATE(80)] = 1151,
  [SMALL_STATE(81)] = 1161,
  [SMALL_STATE(82)] = 1167,
  [SMALL_STATE(83)] = 1177,
  [SMALL_STATE(84)] = 1187,
  [SMALL_STATE(85)] = 1193,
  [SMALL_STATE(86)] = 1203,
  [SMALL_STATE(87)] = 1213,
  [SMALL_STATE(88)] = 1220,
  [SMALL_STATE(89)] = 1225,
  [SMALL_STATE(90)] = 1232,
  [SMALL_STATE(91)] = 1237,
  [SMALL_STATE(92)] = 1244,
  [SMALL_STATE(93)] = 1251,
  [SMALL_STATE(94)] = 1256,
  [SMALL_STATE(95)] = 1263,
  [SMALL_STATE(96)] = 1270,
  [SMALL_STATE(97)] = 1275,
  [SMALL_STATE(98)] = 1280,
  [SMALL_STATE(99)] = 1287,
  [SMALL_STATE(100)] = 1292,
  [SMALL_STATE(101)] = 1299,
  [SMALL_STATE(102)] = 1306,
  [SMALL_STATE(103)] = 1313,
  [SMALL_STATE(104)] = 1320,
  [SMALL_STATE(105)] = 1327,
  [SMALL_STATE(106)] = 1331,
  [SMALL_STATE(107)] = 1335,
  [SMALL_STATE(108)] = 1339,
  [SMALL_STATE(109)] = 1343,
  [SMALL_STATE(110)] = 1347,
  [SMALL_STATE(111)] = 1351,
  [SMALL_STATE(112)] = 1355,
  [SMALL_STATE(113)] = 1359,
  [SMALL_STATE(114)] = 1363,
  [SMALL_STATE(115)] = 1367,
  [SMALL_STATE(116)] = 1371,
  [SMALL_STATE(117)] = 1375,
  [SMALL_STATE(118)] = 1379,
  [SMALL_STATE(119)] = 1383,
  [SMALL_STATE(120)] = 1387,
  [SMALL_STATE(121)] = 1391,
  [SMALL_STATE(122)] = 1395,
  [SMALL_STATE(123)] = 1399,
  [SMALL_STATE(124)] = 1403,
  [SMALL_STATE(125)] = 1407,
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
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 1),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 1),
  [55] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 1),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 4, .production_id = 5),
  [67] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 5, .production_id = 7),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 3, .production_id = 4),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 3, .production_id = 3),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateFilter, 3, .production_id = 2),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 2),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 2),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boundedListFilter, 1),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter, 1, .production_id = 1),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 1),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listVal, 3, .production_id = 4),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filters, 3),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 4, .production_id = 5),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeVal, 6, .production_id = 8),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateVal, 1),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternFilter, 3, .production_id = 2),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternVal, 1),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanVal, 1),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanFilter, 3, .production_id = 2),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numberVal, 1),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numericFilter, 3, .production_id = 2),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 1),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeFilter, 3, .production_id = 2),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unboundedListFilter, 3, .production_id = 2),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [123] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_stringContent, 1),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [127] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_stringContent_repeat1, 2),
  [129] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_stringContent_repeat1, 2), SHIFT_REPEAT(50),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOptions, 2),
  [140] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOptions, 1),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeOptions, 1),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 4),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 6, .production_id = 8),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 5, .production_id = 7),
  [164] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(12),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 6),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 4, .production_id = 5),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortBy, 3, .production_id = 2),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit, 3, .production_id = 2),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 3, .production_id = 4),
  [191] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(44),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 2, .production_id = 6),
  [196] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6), SHIFT_REPEAT(2),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 6),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_patternOp, 1),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByVal, 2),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [215] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 2, .production_id = 4),
  [219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_sortByVal_repeat1, 4, .production_id = 7),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 4, .production_id = 7),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_visitTypeVal_repeat1, 2, .production_id = 4),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_booleanOp, 1),
  [237] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [239] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_listVal_repeat1, 2, .production_id = 4),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [243] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [247] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visitTypeOp, 1),
  [253] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dateOp, 1),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 5),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [265] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_listOp, 1),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sortByOp, 1),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_numericOp, 1),
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
