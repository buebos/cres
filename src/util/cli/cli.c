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

bool cli_tok_is_flag(char* tok) {
    return tok[0] == '-';
}
CliParseResult cli_parse_unknown_tok(int i) {
    return (CliParseResult){
        .status = CLI_PARSE_UNKNOWN_TOK,
        .data = {
            .unknown_token = {
                .good_until_index = i,
            },
        },
    };
}

CliFlag* cli_flag_get(CliCommand* cmd, char* tok) {
    for (int i = 0; i < cmd->flags_len; i++) {
        CliFlag* flag = &cmd->flags[i];

        if (strcmp(flag->id, tok) == 0) {
            return flag;
        }

        for (int j = 0; j < flag->aliases_len; i++) {
            char* flag_alias = &flag->aliases[i];

            if (strcmp(flag_alias, tok) == 0) {
                return flag;
            }
        }
    }

    return NULL;
}
CliParseResult cli_flag_validate_params(CliFlag* flag) {}

CliParseResult cli_parse(Cli* cli, int argc, char** argv) {
    if (!cli->root) {
        return (CliParseResult){
            .status = CLI_PARSE_SUCCESS,
            .data = {0},
        };
    }

    CliFlag* flag_current = NULL;
    CliCommand* cmd_current = cli->root;

    size_t cmd_params_cursor = 0;
    size_t flag_params_cursor = 0;

    for (int i = 1; i < argc; i++) {
        char* tok = argv[i];

        if (cli_tok_is_flag(tok)) {
            CliFlag* flag_match = cli_flag_get(cmd_current, tok);

            if (!flag_match) {
                return cli_parse_unknown_tok(i);
            }

            CliParseResult res = cli_flag_validate_params(flag_current);

            if (res.status != CLI_PARSE_SUCCESS) {
                return res;
            }

            flag_current = flag_match;

            continue;
        }

        CliCommand* cmd_match = cli_cmd_get(cmd_current, tok);
        CliParam* param_match = cli_param_get(cmd_current, tok);

        /** The token did not match any cmd or arg in scope */
        return cli_parse_unknown_tok(i);
    }
}
