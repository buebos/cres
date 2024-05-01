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
 * 3. Add the command creation logic at file src/set_app_command.c
 * @version 0.1
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __COMMAND_H__

#define __COMMAND_H__

#include <stdlib.h>
#include <string.h>

/**
 * Some basic ideas I have for commands. Maybe some are
 * kind of useless (PREFIX, BUNDLE).
 */
typedef enum CommandID {
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
    HELP,

    /**
     * Used when a given string or input doesn't match any of
     * these enum members.
     */
    UNKNOWN
} CommandID;

/** This will be defined later inside app.h */
typedef struct Args Args;
typedef struct App App;

typedef enum Status (*RunCommandOperation)(App* app);
typedef enum Status (*HandleArgsOperation)(App* app, Args* args);

typedef struct Command {
    CommandID id;
    RunCommandOperation run;
    HandleArgsOperation handle_args;
} Command;

#endif