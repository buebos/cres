#ifndef __CLI_H__

#define __CLI_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../ds/stack.h"

/** The '--' chars before flags */
#define CLI_FLAG_ID_PRE_LEN 2
/** The '-' char before flag short aliases */
#define CLI_FLAG_ALIAS_PRE_LEN 1

#define CLI_ARGS(preargs)                                            \
    (&(CliFlag[]) {                                                  \
        CliFlag flags[] = preargs;                                   \
        for (int i = 0; i < sizeof(flags) / sizeof(flags[0]; i++)) { \
            CliFlag arg = flags[i];                                  \
        }                                                            \
        flags;                                                       \
    })

typedef struct CliParam CliParam;
typedef struct CliFlag CliFlag;
typedef struct CliCommand CliCommand;

typedef enum CliParseResStatus {
    CLI_PARSE_SUCCESS,
    CLI_PARSE_ERROR_PARAM_TYPE,
    CLI_PARSE_ERROR_UNKNOWN_TOK,
    CLI_PARSE_ERROR_PARAM_MISSING,
    CLI_PARSE_ERROR_PARAM_OUT,

    CLI_PARSE_ERROR_FLAG_MISSING,
} CliParseResStatus;

typedef struct CliParseUnknownTok {
    size_t good_until_index;
} CliParseUnknownTok;

typedef union CliParseResData {
    CliParseUnknownTok unknown_token;
} CliParseResData;

typedef struct CliParseResult {
    CliParseResStatus status;
    CliParseResData data;
} CliParseResult;

typedef enum CliParamType {
    CLI_BOOL,

    CLI_INT,
    CLI_FLOAT,

    CLI_STR,

    CLI_PATH_FILE,
    CLI_PATH_DIR,
} CliParamType;

typedef enum CliTokType {
    CLI_TOK_UNKNOWN,
    CLI_TOK_PARAM,
    CLI_TOK_FLAG,
    CLI_TOK_CMD,
} CliTokType;
typedef union CliTokMatch {
    CliParam* param;
    CliFlag* flag;
    CliCommand* cmd;
} CliTokMatch;
typedef struct CliTok {
    CliTokType type;
    CliTokMatch match;
    char* value;
} CliTok;

typedef struct CliParam {
    char* id;
    CliParamType type;

    bool is_list;
    bool is_nullable;

    char** value_constraints;
    size_t value_constraints_len;

    void* _value;
} CliParam;

typedef struct CliFlag {
    char* id;

    char** aliases;
    size_t aliases_len;

    CliParam* params;
    size_t params_len;

    bool is_nullable;
    bool _is_set;
} CliFlag;

typedef struct CliCommand {
    char* id;
    char** aliases;
    void* run;

    CliCommand* cmds;
    size_t cmds_len;

    CliParam* params;
    size_t params_len;

    CliFlag* flags;
    size_t flags_len;

    CliCommand* _command;
} CliCommand;

typedef struct Cli {
    char* name;
    char* epilogue;
    CliCommand* root;
} Cli;

CliParseResult cli_parse(Cli* cli, int argc, char** argv);
void* cli_arg_get(CliFlag* flags, char* arg_id);

#endif  // !__CLI_H__
