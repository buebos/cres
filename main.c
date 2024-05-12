#include "src/app/cli/app_handle_cli_error.h"
#include "src/app/config/app_setup_config.h"
#include "src/build/build.h"
#include "src/header/header.h"
#include "src/help/help.h"
#include "src/util/app.h"

Cli cli = {
    .name = "cres",
    .epilogue = "Cres application",

    .cmds_len = 3,
    .cmds = (CliCommand *[]){
        &Help,
        &Build,
        &Header,
    },

    .flags_len = 0,
    .flags = NULL,
};

int main(int argc, char *argv[]) {
    /** App initialization */
    App app = {
        .cli = &cli,
        .args = {
            .len = argc,
            .data = argv,
        },
    };

    /**
     * Parse the incoming string arguments using the declared
     * cli schema.
     */
    CliParseResult res = cli_parse(app.cli, app.args.len, app.args.data);

    if (res.status != CLI_PARSE_SUCCESS) {
        return app_handle_cli_error(&app, res);
    }

    /**
     * Skip the config file when the arguments are specified. Args
     * will be generally prior to the config file.
     */
    if (!cli_get(app.cli, "skip-config")) {
        app_setup_config(&app, (char *)cli_get(app.cli, "config-dir"));
    }

    /**
     * Get the target command called by the user.
     */
    CliCommand *target = cli_get_cmd(app.cli);

    return ((AppCmdRun)target->run)(&app);
}
