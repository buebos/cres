#ifndef __CLI_H__

#define __CLI_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../ds/stack.h"

#define CLI_ARGS(preargs)                                          \
    (&(CliArg[]) {                                                 \
        CliArg args[] = preargs;                                   \
        for (int i = 0; i < sizeof(args) / sizeof(args[0]; i++)) { \
            CliArg arg = args[i];                                  \
        }                                                          \
        args;                                                      \
    })

typedef enum CliParseResStatus {
    CLI_PARSE_SUCCESS,
    CLI_UNKNOWN_TOK,
    CLI_INVALID_ARG_TYPE,
    CLI_MISSING_ARG,
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

typedef enum CliArgType {
    CLI_ARG_DELIMITER,
    CLI_ARG_POSITIONAL,
} CliArgType;

typedef enum CliValueType {
    CLI_BOOL,

    CLI_INT,
    CLI_FLOAT,

    CLI_STR,

    CLI_PATH_FILE,
    CLI_PATH_DIR,
} CliValueType;

typedef struct CliParam {
    char* id;
    CliValueType type;

    bool is_list;
    bool is_nullable;

    char** value_constraints;

    void* value;
} CliParam;

typedef struct CliArg {
    char* id;
    CliArgType type;
    CliParam* positional;

    CliParam* params;
    size_t params_len;
} CliArg;

typedef struct CliCommand {
    char* id;
    char** aliases;

    CliCommand* cmds;
    size_t cmds_len;

    CliArg* args;
    size_t args_len;

    CliCommand* _command;

    void* run;
} CliCommand;

typedef struct Cli {
    char* name;
    char* epilogue;
    CliCommand* root;
} Cli;

CliParseResult cli_parse(Cli* cli, int argc, char** argv);
void* cli_arg_get(CliArg* args, char* arg_id);

#endif  // !__CLI_H__