#include "build.h"

CliCommand Build = {
    .id = "build",
    .aliases_len = 0,
    .aliases = NULL,
    .run = build,

    .cmds_len = 0,
    .cmds = NULL,

    .params_len = 1,
    .params = (CliParam[]){
        {
            .id = "entry",
            .type = CLI_STR,
            .is_list = false,
            .is_nullable = true,
            .value_constraints = NULL,
        },
    },

    .flags_len = 3,
    .flags = (CliFlag[]){
        {
            .id = "variant",
            .aliases_len = 1,
            .aliases = (char*[]){"var"},
            .params_len = 1,
            .params = (CliParam[]){
                {
                    .id = "variant",
                    .type = CLI_STR,
                    .is_nullable = false,
                    .is_list = false,
                    .value_constraints = NULL,
                },
            },
        },
        {
            .id = "targets",
            .aliases_len = 1,
            .aliases = (char*[]){"tgs"},
            .params_len = 1,
            .params = (CliParam[]){
                {
                    .id = "targets",
                    .type = CLI_STR,
                    .is_list = true,
                    .is_nullable = false,
                    .value_constraints = (char*[]){
                        "win64",
                        "win32",
                        "macosx",
                        "linux",
                    },
                },
            },
        },
    },
};

AppStatus build(App* app) {
    cres_log(LOG_WARN, "BUILD Command not implemented");

    char* entry = cli_get(app->cli, "entry");

    printf("Entry: %s\n", entry);

    return SUCCESS;
}
