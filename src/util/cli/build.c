#include "cli.h"

const CliCommand Build = {
    .id = "build",
    .aliases = NULL,
    .run = NULL,

    .cmds_len = 0,
    .cmds = NULL,

    .params_len = 1,
    .params = &(CliParam){
        .id = "entry",
        .type = CLI_STR,
        .is_list = false,
        .is_nullable = true,
        .value_constraints = NULL,
    },

    .flags_len = 3,
    .flags = &(CliFlag[]){
        {
            .id = "variant",
            .aliases_len = 1,
            .aliases = &(char*[]){"var"},
            .params_len = 1,
            .params = &(CliParam[]){
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
            .aliases = &(char*[]){"tgs"},
            .params_len = 1,
            .params = &(CliParam[]){
                {
                    .id = "targets",
                    .type = CLI_STR,
                    .is_list = true,
                    .is_nullable = false,
                    .value_constraints = &(char*[]){
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