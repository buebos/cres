#include "src/cli/set_app_by_args.h"
#include "src/config/set_app_by_config.h"
#include "src/util/app/app.h"
#include "src/util/app/status.h"
#include "src/util/app/command.h"
#include "src/util/log/log.h"

int main(int argc, char *argv[]) {
    App app = {0};

    app.params.config_dir = DEFAULT_CONFIG_DIR;
    app.params.file_target = DEFAULT_FILE_TARGET;

    app.command = command_factory(argc > 1 ? argv[1] : NULL);

    if (app.command.id == UNKNOWN) {
        cres_log(
            LOG_ERROR,
            get_app_status_msg(app.status = UNKNOWN_COMMAND)

        );
        return app.status;
    }

    /**
     * Use data passed in by the user via args or config
     * file to initialize the app's general context. Notice
     * that args will override params defined in the config
     * file.
     */
    set_app_by_config(&app, app.params.config_dir);
    set_app_by_args(&app, argc, argv);

    /** Validation of app context (params mainly) */
    set_app_status(&app);

    if (app.status != SUCCESS) {
        cres_log(LOG_ERROR, get_app_status_msg(app.status));
        return app.status;
    }

    return app.command.run(&app);
}