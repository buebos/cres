#ifndef __CLI_SCHEMA_H__

#define __CLI_SCHEMA_H__

#include <stdbool.h>
#include <stdlib.h>

#include "util/hashmap.h"

typedef enum CliSchemaType {
    CLI_SCHEMA_ARG,
    CLI_SCHEMA_ARG_PARAM,
    CLI_SCHEMA_CMD,
    CLI_SCHEMA_CMD_PARAM,
    CLI_SCHEMA_CMD_ARG,
    CLI_SCHEMA_CMD_ARG_PARAM
} CliSchemaType;

typedef enum CliParamType {
    CLI_INT,
    CLI_FLOAT,
    CLI_DOUBLE,

    CLI_ENUM,

    CLI_CHAR,
    CLI_STR,
    CLI_STR_LIST,

    CLI_STR_PATH_DIR,
    CLI_STR_PATH_FILE
} CliParamType;

/**
 * Due to circular dependency between the CliValidateStr
 * function and these structs they must be declared before
 * as prototypes.
 */
typedef struct CliSchema CliSchema;
typedef struct CliParamSchema CliParamSchema;
typedef struct CliRawArgs CliRawArgs;

typedef bool (*CliValidateParam)(CliSchema *cli, CliParamSchema *schema, char *param);
typedef bool (*CliValidateRaw)(CliSchema *cli, CliRawArgs *raw);

typedef struct CliRawArgs {
    int argc;
    char **argv;

    /**
     * Optional custom function for further validation.
     *
     * @param cli: reference to the cli owner of the param schema.
     * @param raw: the input to be validated.
     */
    CliValidateRaw is_valid;
} CliRawArgs;

typedef struct CliParamSchema {
    /** Recommendation: use enums */
    size_t index;

    /**
     * Will be used to try a cast to that type for
     * the value.
     */
    CliParamType type;

    /** Optional */
    char *name;

    /**
     * Optional. Meant to be used as a list for valid enum values,
     * but could be used other way.
     */
    char **value_constraints;

    bool is_optional;

    /**
     * Will match all following strings within argv to
     * this schema until it encounters an arg delimiter.
     */
    bool is_value_list;

    /**
     * Optional custom function for further validation.
     *
     * @param cli: reference to the cli owner of the param schema.
     * @param schema: reference to the schema instance calling the function.
     * @param str: the string to be validated.
     */
    CliValidateParam is_valid;
} CliParamSchema;

typedef struct CliArgSchema {
    /** Recommendation: use enums */
    size_t key;

    /**
     * Should be prefixed with '-' to delimit them
     * from params.
     */
    char **identifiers;

    /**
     * Params won't need to be prefixed by anything unlike
     * args which are generally prefixed with a dash
     * (e.g. '-a', '--arg').
     */
    CliParamSchema *params;
} CliArgSchema;

typedef struct CliCmdSchema {
    /** Recommendation: use enums */
    size_t key;

    char **identifiers;

    /**
     * Params won't need to be prefixed by anything unlike
     * args which are generally prefixed with a dash
     * (e.g. '-a', '--arg').
     */
    CliParamSchema *params;

    /** */
    CliArgSchema *args;
} CliCmdSchema;

typedef struct CliSchema {
    HashMap *commands;
    HashMap *args;
} CliSchema;

typedef struct CliCommand {
    char *value;
    HashMap *args;
} CliCommand;

typedef struct Cli {
    HashMap *args;
    CliCommand *command;
} Cli;

void cli_def_schema(CliSchema *cli, CliSchemaType type, void *schema);
void *cli_get_schema(CliSchema *cli, CliSchemaType type, size_t key);

Cli *cli_parse(CliSchema *cli, CliRawArgs *raw);

#endif
