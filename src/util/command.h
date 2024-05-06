/**
 * @file command.h
 * @author Gael Herrera (hrac.gael@gmail.com)
 * @brief This file contains the schema for an application
 * command. It is used to determine the actions to run when
 * the program is called. To register a command the following
 * steps should be followed:
 *
 * 1. Add the CommandID enum member
 * 2. Add the command implementation at a new subdir on src
 * 3. Add the command creation logic at file src/app_set_command.c
 * @version 0.1
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __COMMAND_H__

#define __COMMAND_H__

/**
 * The maximum char len a command label can have. Usually
 * this are short: ('run': 3), ('build': 5). (+ Null terminators)
 */
#define MAX_COMMAND_STR_LEN 32
/**
 * The maximum char length a command arg key and default value
 * can have.
 */
#define MAX_COMMAND_ARG_STR_LEN 128
#define MAX_COMMAND_ARG_PARAMS 1
/**
 * The maximum identifier keys a command arg can have, for example
 * a version arg could have two keys: ['-v', '--version']. Most of
 * CLIs I've seen set two ids for each argument: a short and a
 * detailed one.
 */
#define MAX_COMMAND_ARG_ALIASES 2

#define MAX_COMMAND_PARAMS 8
#define MAX_COMMAND_ARGS 16

#include <stdlib.h>
#include <string.h>

/**
 * Some basic ideas I have for commands. Maybe some are
 * kind of useless (PREFIX, BUNDLE).
 */
typedef enum CommandID {
    /** The equivalent to call only the executable */
    CRES,

    /**
     * Resolve the C files to export as objects, link them,
     * write the output and run the resulting binary.
     */
    RUN,
    /**
     * Resolve the C files to export as objects, link them
     * and write the output.
     */
    BUILD,

    /**
     * Bundle all C files referenced by headers into a single
     * one except for the libraries.
     */
    BUNDLE,
    /**
     * Prefix all global identifiers of all files with a
     * string. The goal of this is to help users avoid naming
     * collisions between libs and their projects. This way they
     * can prefix a lib name of a function, struct, etc. and
     * use that in their files.
     */
    PREFIX,

    /**
     * Generate a header file for a given C file.
     */
    HEADER,

    /**
     * Display options and mini tutorial.
     */
    HELP
} CommandID;

typedef enum CommandParamType {
    CMD_PARAM_STR,
    CMD_PARAM_INT,
    CMD_PARAM_FLOAT,

    CMD_PARAM_ENUM,

    CMD_PARAM_DIR,
    CMD_PARAM_FILE
} CommandParamType;

/** This will be defined later inside app.h */
typedef struct Args Args;
typedef struct App App;

typedef void (*CommandRunOperation)(App* app);
typedef void (*CommandSetupArgsOperation)(App* app, Args* args);

typedef struct CommandParam {
    CommandParamType type;

    char* value;
    bool nullable;

    char value_constraints[MAX_COMMAND_PARAMS][MAX_COMMAND_ARG_STR_LEN];
} CommandParam;

typedef struct CommandArgParams {
    size_t len;
    CommandParam data[MAX_COMMAND_ARG_PARAMS];
} CommandArgParams;

typedef struct CommandArg {
    unsigned int id;

    char aliases[MAX_COMMAND_ARG_ALIASES][MAX_COMMAND_STR_LEN];

    short max_params_len;

    CommandArgParams params;
} CommandArg;

typedef struct Command {
    CommandID id;
    char label[MAX_COMMAND_STR_LEN];

    CommandParam params[MAX_COMMAND_PARAMS];
    CommandArg args[MAX_COMMAND_ARGS];

    CommandRunOperation run;
    CommandSetupArgsOperation setup_args;
} Command;

#endif
