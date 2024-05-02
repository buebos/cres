#include "app_setup_common_args.h"

/** TODO: Structure code to avoid lots of if statements */
void app_setup_common_args(App *app, Args *args) {
    app->env = PROD;

    for (int i = 0; i < args->len; i++) {
        char *arg = args->data[i];

        if (strcmp(arg, "-sc") == 0 || strcmp(arg, "--skip-config") == 0) {
            app->params.should_suppress_config = true;
        }
    }
}
