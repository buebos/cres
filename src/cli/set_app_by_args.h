#ifndef __GET_ARGS__
#define __GET_ARGS__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../util/app/app.h"

void set_app_by_args(App *app, int argc, char *argv[]);

char *get_args_error_msg(short status);

#endif /* __GET_ARGS__ */
