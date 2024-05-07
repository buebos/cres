#include "cli_schema.h"

typedef enum CliParseCurrentState {
    CLI_STATE_START,

    CLI_STATE_ARG,
    CLI_STATE_ARG_PARAM,

    CLI_STATE_CMD,
    CLI_STATE_CMD_PARAM,
    CLI_STATE_CMD_ARG,
    CLI_STATE_CMD_ARG_PARAM,
} CliParseCurrentState;

typedef struct CliParseState CliParseState;
typedef void (*CliStateHandleTok)(CliParseState *state, CliSchema *schema, Cli *map, char *token);

typedef struct CliParseState {
    CliParseCurrentState current;
    CliStateHandleTok handle_token;
} CliParseState;

void cli_arg_handle_tok(CliParseState *state, CliSchema *schema, Cli *cli, char *token);
void cli_cmd_handle_tok(CliParseState *state, CliSchema *schema, Cli *cli, char *token);

void cli_start_handle_tok(CliParseState *state, CliSchema *schema, Cli *cli, char *token) {
    CliSchemaType type = cli_get_type(schema, token);

    switch (type) {
        case CLI_SCHEMA_ARG:
            state->current = CLI_STATE_ARG;
            state->handle_token = cli_arg_handle_tok;
            cli_set_arg(cli, token);
            return;
        case CLI_SCHEMA_CMD:
            state->current = CLI_STATE_CMD;
            state->handle_token = cli_cmd_handle_tok;
            cli_set_cmd(cli, token);
            return;
        default:
            exit(1); /** TODO: Handle parsing error */
    }
}

Cli *cli_parse(CliSchema *schema, CliRawArgs *raw) {
    if (raw->is_valid != NULL && !raw->is_valid(schema, raw)) {
        return NULL;
    }

    Cli *map = NULL;
    CliParseState state = {.current = CLI_STATE_START, .handle_token = cli_start_handle_tok};

    for (int i = 0; i < raw->argc; i++) {
        char *arg = raw->argv[i];

        state.handle_token(&state, &map, schema, arg);
    }

    return map;
}
