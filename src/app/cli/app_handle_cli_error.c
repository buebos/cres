#include "app_handle_cli_error.h"

int app_handle_cli_error(App* app, CliParseResult err) {
    switch (err.status) {
        case CLI_PARSE_ERROR_UNKNOWN_TOK:
            cres_log(
                LOG_ERROR,
                "Unknown token: '%s'. The input is not a valid command, flag or parameter.",
                app->args.data[err.data.unknown_token.index]

            );

            break;
        default:
            cres_log(LOG_ERROR, "An unexpected error occurred while parsing the cli args, error code: %d.", err.status);
    }

    return err.status;
}
