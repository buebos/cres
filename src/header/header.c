#include "header.h"

CliCommand Header = {
    .id = "help",
    .run = header,

    .aliases_len = 0,
    .aliases = NULL,

    .params_len = 0,
    .params = NULL,

    .cmds_len = 0,
    .cmds = NULL,

    .flags_len = 0,
    .flags = NULL,
};

/**
 * Generates a header file for the c file requested.
 *
 * @param relative_path The relative path as a char pointer to the
 * c file that needs to generate a header file.
 * @param params The arguments struct that was constructed from the
 * call to the executable command
 */
AppStatus header(App* app) {
    cres_log(LOG_WARN, "HEADER Command not implemented");
}