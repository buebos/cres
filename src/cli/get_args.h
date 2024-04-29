#ifndef __GET_ARGS__
#define __GET_ARGS__

#include <stdbool.h>
#include <stdlib.h>

#include "../util/app.h"

typedef enum {
    CORRECT,
    NO_FILE_ERROR
} GetArgsStatus;

Args get_args(App *app, int argc, char **argv);

char *get_args_error_msg(short status);

#endif /* __GET_ARGS__ */
