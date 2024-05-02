#include "app.h"

#include "log/log.h"

const char *UNKNOWN_ERROR = "An unknown error occurred, please report since this is probably bug.";

const char *ERROR_MESSAGES[] = {
    "Arguments are correct but still get_app_status_msg was called.",
    "Please provide the name of the entry file as first argument.",
    "Unknown command, run 'cres help' for more information."

};
const size_t ERROR_MESSAGES_LEN = sizeof(ERROR_MESSAGES) / sizeof(char *);

char *get_app_status_msg(AppStatus status) {
    for (size_t i = 0; i < ERROR_MESSAGES_LEN; i++) {
        if (i + 1 == status) {
            return (char *)ERROR_MESSAGES[i];
        }
    }

    return (char *)UNKNOWN_ERROR;
}

void app_throw_error(AppStatus error_status) {
    cres_log(LOG_ERROR, get_app_status_msg(error_status));
    exit(error_status);
}