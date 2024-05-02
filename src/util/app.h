#ifndef __APP_H__

#define __APP_H__

#include <stdbool.h>
#include <stdlib.h>

#include "command.h"

#define DEFAULT_FILE_TARGET "./main.c"
#define DEFAULT_CONFIG_DIR "./cres.json"

#define DEFAULT_COMMAND_ID HELP
#define DEFAULT_COMMAND_FN help

typedef enum AppStatus {
    SUCCESS,
    NO_TARGET_FILE_ERROR,
    NO_COMMAND_ERROR,
    UNKNOWN_COMMAND_ERROR
} AppStatus;

typedef enum Env {
    DEV,
    PROD
} Env;

typedef struct Args {
    int len;
    char **data;
} Args;

typedef struct Params {
    char *config_dir;
    char *file_target;

    bool should_suppress_config;
} Params;

typedef struct App {
    /** Original parameters */

    Env env;
    Args args;
    Command command;
    Params params;
} App;

char *get_app_status_msg(AppStatus status);
void app_throw_error(AppStatus error_status);

#endif