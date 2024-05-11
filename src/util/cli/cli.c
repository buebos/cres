#include "cli.h"

bool cli_tok_is_flag(char* tok) {
    return tok[0] == '-';
}

CliParam* cli_param_get_last(CliParam* param, size_t params_len) {
    /** Reach the last param that has not been set */
    while (param->_value) {
        param += 1;
    }

    return param;
}

CliFlag* cli_flag_get(CliCommand* cmd, char* tok) {
    while (cmd) {
        for (int i = 0; i < cmd->flags_len; i++) {
            CliFlag* flag = &cmd->flags[i];

            if (strcmp(flag->id, tok + CLI_FLAG_ID_PRE_LEN) == 0) {
                return flag;
            }

            for (int j = 0; j < flag->aliases_len; i++) {
                char* flag_alias = &flag->aliases[i];

                if (strcmp(flag_alias, tok + CLI_FLAG_ALIAS_PRE_LEN) == 0) {
                    return flag;
                }
            }
        }

        cmd = cmd->_command;
    }

    return NULL;
}

CliFlag* cli_cmd_get(CliCommand* cmd, char* tok) {
    for (int i = 0; i < cmd->flags_len; i++) {
        CliFlag* command = &cmd->cmds[i];

        if (strcmp(command->id, tok) == 0) {
            return command;
        }

        for (int j = 0; j < command->aliases_len; i++) {
            char* flag_alias = &command->aliases[i];

            if (strcmp(flag_alias, tok) == 0) {
                return command;
            }
        }
    }

    return NULL;
};

CliTok cli_tok(Cli* cli, CliCommand* cmd_current, CliFlag* flag_current, char* tok) {
    CliTok token = {
        .type = CLI_TOK_UNKNOWN,
        .match = {0},
        .value = tok,
    };

    CliFlag* flag_match = cli_flag_get(cli->root, tok);

    if (flag_match) {
        token.match.flag = flag_match;
        token.type = CLI_TOK_FLAG;
        return token;
    }

    CliCommand* cmd_match = cli_cmd_get(cmd_current, tok);

    if (cmd_match) {
        token.match.cmd = cmd_match;
        token.type = CLI_TOK_CMD;
        return token;
    }

    CliParam* param_match = NULL;

    if (flag_current) {
        param_match = cli_param_get_last(flag_current->params, flag_current->params_len);
    } else if (cmd_current) {
        param_match = cli_cmd_param_get_last(cmd_current->params, cmd_current->params_len);
    }

    if (param_match) {
        token.match.param = param_match;
        token.type = CLI_TOK_PARAM;
    }

    return token;
}

CliParseResult cli_param_parse_validate(CliParam* param) {
    char* value = param->_value;

    if (!value && !param->is_nullable) {
        return (CliParseResult){
            .status = CLI_PARSE_ERROR_PARAM_MISSING,
            .data = {0},
        };
    }

    switch (param->type) {
        case CLI_BOOL:
            if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
                break;
            }
            if (strcmp(value, "1") == 0 || strcmp(value, "0") == 0) {
                break;
            }

            return (CliParseResult){
                .status = CLI_PARSE_ERROR_PARAM_TYPE,
                .data = {0},
            };
        case CLI_INT:
        case CLI_FLOAT: {
            char* endptr;

            if (param->type == CLI_INT) {
                strtol(value, &endptr, 10);
            } else {
                strtod(value, &endptr);
            }

            if (*endptr != '\0') {
                return (CliParseResult){
                    .status = CLI_PARSE_ERROR_PARAM_TYPE,
                    .data = {0},
                };
            }

            break;
        }
        case CLI_PATH_DIR: {
            break;
        }
        case CLI_PATH_FILE: {
            break;
        }
        case CLI_STR:
        default:
            break;
    }

    if (param->value_constraints) {
        bool is_within_constraint = false;

        for (size_t i = 0; i < param->value_constraints_len; i++) {
            char* constraint = strlwr(&param->value_constraints[i]);

            if (strcmp(strlwr(value), constraint) == 0) {
                is_within_constraint = true;
                break;
            }
        }

        if (!is_within_constraint) {
            return (CliParseResult){
                .status = CLI_PARSE_ERROR_PARAM_OUT,
                .data = {0},
            };
        }
    }

    return (CliParseResult){.status = CLI_PARSE_SUCCESS, .data = {0}};
}

CliParseResult cli_flag_parse_validate(CliFlag* flag) {
    if (!flag->_is_set && !flag->is_nullable) {
        return (CliParseResult){
            .status = CLI_PARSE_ERROR_FLAG_MISSING,
            .data = {0},
        };
    }

    for (size_t i = 0; i < flag->params; i++) {
        CliParseResult res = cli_param_parse_validate(&flag->params[i]);

        if (res.status != CLI_PARSE_SUCCESS) {
            return res;
        }
    }

    return (CliParseResult){.status = CLI_PARSE_SUCCESS, .data = {0}};
}

CliParseResult cli_cmd_parse_validate(CliCommand* cmd) {
    while (cmd) {
        for (size_t i = 0; i < cmd->params; i++) {
            CliParseResult res = cli_param_parse_validate(&cmd->params[i]);

            if (res.status != CLI_PARSE_SUCCESS) {
                return res;
            }
        }

        for (size_t i = 0; i < cmd->flags; i++) {
            CliParseResult res = cli_flag_parse_validate(&cmd->flags[i]);

            if (res.status != CLI_PARSE_SUCCESS) {
                return res;
            }
        }

        cmd = cmd->_command;
    }

    return (CliParseResult){.status = CLI_PARSE_SUCCESS, .data = {0}};
}

CliParseResult cli_parse(Cli* cli, int argc, char** argv) {
    if (!cli->root) {
        return (CliParseResult){.status = CLI_PARSE_SUCCESS, .data = {0}};
    }

    CliCommand* cmd_current = cli->root;
    CliFlag* flag_current = NULL;

    for (int i = 1; i < argc; i++) {
        CliTok tok = cli_tok(cli, cmd_current, flag_current, argv[i]);

        if (tok.type != CLI_TOK_PARAM && flag_current) {
            CliParseResult res = cli_flag_parse_validate(flag_current);

            if (res.status != CLI_PARSE_SUCCESS) {
                return res;
            }
        }

        switch (tok.type) {
            case CLI_TOK_PARAM:
                tok.match.param->_value = tok.value;

                CliParseResult res = cli_param_parse_validate(tok.match.param);

                if (res.status != CLI_PARSE_SUCCESS) {
                    return res;
                }

                break;
            case CLI_TOK_FLAG:
                tok.match.flag->_is_set = true;

                if (tok.match.flag->params && tok.match.flag->params_len) {
                    flag_current = tok.match.flag;
                } else {
                    flag_current = NULL;
                }

                break;
            case CLI_TOK_CMD:
                if (cmd_current) {
                    CliParseResult res = cli_cmd_parse_validate(cmd_current);
                    if (res.status != CLI_PARSE_SUCCESS) {
                        return res;
                    }
                }

                flag_current = NULL;
                tok.match.cmd->_command = NULL;

                cmd_current->_command = tok.match.cmd;
                cmd_current = tok.match.cmd;

                break;
            default:
                return (CliParseResult){
                    .status = CLI_PARSE_ERROR_UNKNOWN_TOK,
                    .data = {
                        .unknown_token = {
                            .good_until_index = i,
                        },
                    },
                };
        }
    }

    if (flag_current) {
        CliParseResult res = cli_flag_parse_validate(flag_current);
        if (res.status != CLI_PARSE_SUCCESS) {
            return res;
        }
    }

    if (cmd_current) {
        CliParseResult res = cli_cmd_parse_validate(cmd_current);
        if (res.status != CLI_PARSE_SUCCESS) {
            return res;
        }
    }

    return (CliParseResult){
        .status = CLI_PARSE_SUCCESS,
        .data = {0},
    };
}
