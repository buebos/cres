#include "src/app/config/set_app_by_config.h"
#include "src/app/set_app_by_general_args.h"
#include "src/app/status.h"
#include "src/set_app_command.h"
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
    app.status = set_app_by_general_args(&app, &app.args);
    if (app.status != SUCCESS) {
        return app.status;
    }
    /** Notice that config may override params setted by cli args */
    app.status = set_app_by_config(&app, app.params.config_dir);
    if (app.status != SUCCESS) {
        return app.status;
    }

    /**
     * Find and set the command being executed
     */
    app.status = set_app_command(&app, &app.args);
    if (app.status != SUCCESS) {
        return app.status;
    }

    /**
     * Read and set args passed in specifically to the command
     * being executed.
     */
    app.status = app.command.handle_args(&app, &app.args);
    if (app.status != SUCCESS) {
        return app.status;
    }

    /**
     * The most important thing; after the setup is successful,
     * run the command.
     */
    return app.command.run(&app);
}