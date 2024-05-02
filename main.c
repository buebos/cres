#include "src/app/app_setup_common_args.h"
#include "src/app/config/app_setup_config.h"
#include "src/app_set_command.h"
#include "src/util/app.h"
#include "src/util/log/log.h"

int main(int argc, char *argv[]) {
    App app = {0};

    /** App initialization */
    app.args.len = argc;
    app.args.data = argv;
    app.params.file_target = DEFAULT_FILE_TARGET;
    app.params.config_dir = DEFAULT_CONFIG_DIR;

    /**
     * Read and set data passed in by the user via args
     * or config file to initialize the app's general
     * context. The arguments read are be independent
     * from the command called.
     */
    app_setup_common_args(&app, &app.args);

    /** Notice that config may override params setted by cli args */
    if (!app.params.should_suppress_config) {
        app_setup_config(&app, app.params.config_dir);
    }

    /**
     * Find and set the command being executed
     */
    app_set_command(&app, &app.args);

    /**
     * Read and set args passed in specifically to the command
     * being executed.
     */
    app.command.setup_args(&app, &app.args);

    /**
     * The most important thing; after the setup is successful,
     * run the command.
     */
    app.command.run(&app);

    return SUCCESS;
}