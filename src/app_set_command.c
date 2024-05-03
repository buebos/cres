#include "app_set_command.h"

#include "build/build.h"
#include "header/header.h"
#include "help/help.h"
#include "run/run.h"

const Command const *COMMANDS[] = {
    &HELP_COMMAND,
    &RUN_COMMAND,
    &BUILD_COMMAND,
    &HELP_COMMAND

};
const size_t COMMANDS_LEN = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

void app_set_command(App *app, Args *args) {
    /**
     * Special case: when called with the executable name
     * only, a cli tool should run a default command;
     * 'help' in most cases.
     */
    if (args->len == 1) {
        app->command = &HELP_COMMAND;
        return;
    }

    /**
     * Starts from the 2nd command since index 0 would be the
     * executable name called in the terminal.
     */
    for (int i = 1; i < args->len; i++) {
        char *arg = args->data[i];

        for (int j = 0; j < COMMANDS_LEN; j++) {
            const Command *current_command = COMMANDS[j];

            if (strcmp(arg, current_command->label) == 0) {
                app->command = current_command;
                return;
            }
        }
    }

    app_throw_error((AppError){
        UNKNOWN_COMMAND_ERROR,
        "No command specified, type help for more information."

    });
}