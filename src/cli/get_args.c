#include "get_args.h"

const char *UNKNOWN_ERROR = "An unknown error occurred, please report since this is probably bug.\n";

const char *ERROR_MESSAGES[] = {
    "Arguments are correct but still get_args_error_msg was called.\n",
    "Please provide the name of the entry file as first argument.\n"

};

Args get_args(App *app, int argc, char **argv) {
    Args args = {0};

    /** Copy original parameters */
    args.argc = argc;
    args.argv = argv;

    /**
     * Should contain at least one argument with the
     * filename of the entry file to compile
     */
    if (argc < 2) {
        app->status = NO_FILE_ERROR;
        return args;
    }

    args.filename = argv[1];
    args.should_gen_header_only = false;

    app->env = PROD;

    return args;
}

char *get_args_error_msg(short status) {
    /**
     * A substraction because all args errors start from 100,
     * the ERROR_MESSAGES array starts from 0
     */
    char *message = (char *)ERROR_MESSAGES[status];

    if (message == NULL) {
        message = (char *)UNKNOWN_ERROR;
    }

    return message;
}
