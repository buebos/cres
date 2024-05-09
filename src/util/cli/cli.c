#include "cli.h"

const CliCommand Build = {
    .id = "build",
    .aliases = NULL,

    .cmds_len = 0,
    .cmds = NULL,

    .run = NULL,

    .args_len = 3,
    .args = &(CliArg[]){
        {
            .id = "entry",
            .type = CLI_ARG_POSITIONAL,
            .params_len = 0,
            .params = NULL,
            .positional = &(CliValue){
                .id = "entry",
                .type = CLI_PATH_FILE,
                .is_list = false,
                .is_nullable = true,
                .value_constraints = NULL,
            },
        },
        {
            .id = "variant",
            .type = CLI_ARG_FLAG,
            .params_len = 1,
            .params = &(CliValue[]){
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
            .type = CLI_ARG_FLAG,
            .params_len = 1,
            .params = &(CliValue[]){
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

bool cli_is_flag_delimiter(char* tok) {
    return tok[0] == '-';
}

CliParseResult cli_parse(Cli* cli, int argc, char** argv) {
    CliArg* arg_current = NULL;
    CliCommand* cmd_current = cli->root;

    /** For positional arguments assignment */
    size_t arg_cursor = 0;

    for (int i = 1; i < argc; i++) {
        char* tok = argv[i];

        if (cli_is_flag_delimiter(tok)) {
        }

        /** The token did not match any cmd or arg in scope */
        return (CliParseResult){
            .status = CLI_UNKNOWN_TOK,
            .data = {
                .unknown_token = {
                    .good_until_index = i,
                },
            },
        };
    }

    arg_current = NULL;
    cmd_current = cli->root;

    while (cmd_current != NULL) {
    }
}
