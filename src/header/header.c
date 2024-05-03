#include "header.h"

typedef enum ArgElementIdentifier {
    FIND_STRATEGY,
    FIND_STRATEGY_VALUE

} ArgElementIdentifier;

void header_setup_args(App* app, Args* args) {}

/**
 * Generates a header file for the c file requested.
 *
 * @param relative_path The relative path as a char pointer to the
 * c file that needs to generate a header file.
 * @param params The arguments struct that was constructed from the
 * call to the executable command
 */
void header(App* app) {
    cres_log(LOG_WARN, "HEADER Command not implemented");
}

const Command HEADER_COMMAND = {
    .id = HEADER,
    .label = "header",
    .args = {

        {

            .id = FIND_STRATEGY,
            .aliases = {"-fs", "--find-strategy"},
            .params = {
                {.key = FIND_STRATEGY_VALUE, .value = NULL}

            }

        }

    },
    .run = header,
    .setup_args = header_setup_args

};