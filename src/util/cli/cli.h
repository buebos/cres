#ifndef __CLI_H__

#define __CLI_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../ds/stack.h"

#define CLI_ARGS(preargs)                                            \
    (&(CliFlag[]) {                                                  \
        CliFlag flags[] = preargs;                                   \
        for (int i = 0; i < sizeof(flags) / sizeof(flags[0]; i++)) { \
            CliFlag arg = flags[i];                                  \
        }                                                            \
        flags;                                                       \
    })

typedef enum CliParseResStatus {
    CLI_PARSE_SUCCESS,
    CLI_PARSE_UNKNOWN_TOK,
    CLI_PARSE_INVALID_ARG_TYPE,
    CLI_PARSE_MISSING_ARG,
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

typedef struct CliParam {
    char* id;
    CliParamType type;

    bool is_list;
    bool is_nullable;

    char** value_constraints;

    void* _value;
} CliParam;

typedef struct CliFlag {
    char* id;

    char** aliases;
    size_t aliases_len;

    CliParam* params;
    size_t params_len;
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