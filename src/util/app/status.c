#include "status.h"

const char *UNKNOWN_ERROR = "An unknown error occurred, please report since this is probably bug.";

const char *ERROR_MESSAGES[] = {
    "Arguments are correct but still get_args_error_msg was called.",
    "Please provide the name of the entry file as first argument.",
    "Unknown command, run 'cres help' for more information."

};
const size_t ERROR_MESSAGES_LEN = sizeof(ERROR_MESSAGES) / sizeof(char *);

/**
 * @brief Validate the app state and set the corresponding status
 * on it.
 *
 * @param app
 */
void set_app_status(App *app) {
    if (!app->command.run) {
        app->status = NO_COMMAND_ERROR;
    } else if (!app->params.file_target) {
        app->status = NO_TARGET_FILE_ERROR;
    }
}

char *get_app_status_msg(Status status) {
    for (size_t i = 0; i < ERROR_MESSAGES_LEN; i++) {
        if (i + 1 == status) {
            return (char *)ERROR_MESSAGES[i];
        }
    }

    return (char *)UNKNOWN_ERROR;
}
