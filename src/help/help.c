#include "help.h"

CliCommand Help = {
    .id = "help",
    .run = help,

    .aliases_len = 0,
    .aliases = NULL,

    .params_len = 0,
    .params = NULL,

    .cmds_len = 0,
    .cmds = NULL,

    .flags_len = 0,
    .flags = NULL,
};

AppStatus help(App* app) {
    cres_log(LOG_WARN, "HELP Command not implemented");
}
