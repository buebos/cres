#include "help.h"

typedef enum ArgElementIdentifier {
    FIND_STRATEGY,

} ArgElementIdentifier;

void help_setup_args(App* app, Args* args) {
}

void help(App* app) {
    cres_log(LOG_WARN, "HELP Command not implemented");
}

const Command HELP_COMMAND = {
    .id = HELP,
    .label = "help",
    .args = {

        {

            .id = FIND_STRATEGY,
            .aliases = {"-fs", "--find-strategy"},
            .params = {
                {.value = NULL}

            }

        }

    },
    .run = help,
    .setup_args = help_setup_args

};