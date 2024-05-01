#include "set_app_command.h"

#include "build/build.h"
#include "header/header.h"
#include "help/help.h"
#include "run/run.h"

const char *COMMAND_IDS[] = {"help", "run", "build", "header"};
const size_t COMMAND_IDS_LEN = sizeof(COMMAND_IDS) / sizeof(COMMAND_IDS[0]);

Command command_factory(char *command_id) {
    if (strcmp(command_id, "help") == 0) {
        return (Command){HELP, help, help_handle_args};
    }

    if (strcmp(command_id, "run") == 0) {
        return (Command){RUN, run, help_handle_args};
    }

    if (strcmp(command_id, "build") == 0) {
        return (Command){BUILD, build, help_handle_args};
    }

    if (strcmp(command_id, "header") == 0) {
        return (Command){HEADER, header, help_handle_args};
    }

    return (Command){UNKNOWN, NULL, NULL};
}

Status set_app_command(App *app, Args *args) {
    /**
     * Special case: when called with the executable name
     * only, a cli tool should run a default command;
     * 'help' in most cases.
     */
    if (args->len == 1) {
        app->command = command_factory((char *)COMMAND_IDS[0]);
        return SUCCESS;
    }

    /**
     * Starts from the 2nd command since index 0 would be the
     * executable name called in the terminal.
     */
    for (int i = 1; i < args->len; i++) {
        char *arg = args->data[i];

        for (int j = 0; j < COMMAND_IDS_LEN; j++) {
            char *current_command = (char *)COMMAND_IDS[j];

            if (strcmp(arg, current_command) == 0) {
                app->command = command_factory(arg);
                return SUCCESS;
            }
        }
    }

    cres_log(LOG_ERROR, "Unknown command");

    return UNKNOWN_COMMAND;
}