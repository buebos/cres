#include "run.h"

typedef enum ArgElementIdentifier {
    FIND_STRATEGY,
    FIND_STRATEGY_VALUE

} ArgElementIdentifier;

void run_setup_args(App* app, Args* args) {}

/**
 * @brief Resolves the dependencies of the specified file,
 * compiles and runs the executable output.
 *
 * @param app
 * @return void
 */
void run(App* app) {
    cres_log(LOG_WARN, "RUN Command not implemented");
}

const Command RUN_COMMAND = {
    .id = RUN,
    .label = "run",
    .args = {
        {

            .id = FIND_STRATEGY,
            .aliases = {"-fs", "--find-strategy"},
            .params = {
                {.key = FIND_STRATEGY_VALUE, .value = NULL}

            }

        }

    },
    .run = run,
    .setup_args = run_setup_args

};