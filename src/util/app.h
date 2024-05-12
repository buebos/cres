#ifndef __APP_H__

#define __APP_H__

#include <stdbool.h>
#include <stdlib.h>

#include "../../module/clic/include/core.h"
#include "../../module/clic/include/get.h"
#include "../../module/clic/include/parse.h"

#define APP_NAME "cres"

#define DEFAULT_FILE_TARGET "./main.c"

typedef struct App App;

typedef enum AppStatus {
    SUCCESS,
    NO_TARGET_FILE_ERROR,
    NO_COMMAND_ERROR,
    UNKNOWN_COMMAND_ERROR,
    UNKNOWN_ARG_ERROR,
    ARG_MISSING_PARAM_ERROR
} AppStatus;

typedef AppStatus (*AppCmdRun)(App *app);

typedef struct AppError {
    AppStatus status;
    char *msg;
} AppError;

typedef struct Args {
    int len;
    char **data;
} Args;

typedef struct App {
    Args args;
    Cli *cli;
} App;

char *get_app_status_msg(AppStatus status);
void app_throw_error(AppError error, ...);

#endif