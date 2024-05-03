#include "build.h"

typedef enum ArgElementIdentifier {
    FIND_STRATEGY,
    FIND_STRATEGY_VALUE

} ArgElementIdentifier;

void build_setup_args(App* app, Args* args) {}

void build(App* app) {
    cres_log(LOG_WARN, "BUILD Command not implemented");
}

const Command BUILD_COMMAND = {
    .id = BUILD,
    .label = "build",
    .args = {

        {

            .id = FIND_STRATEGY,
            .aliases = {"-fs", "--find-strategy"},
            .params = {
                {.key = FIND_STRATEGY_VALUE, .value = NULL}

            }

        }

    },
    .run = build,
    .setup_args = build_setup_args

};
