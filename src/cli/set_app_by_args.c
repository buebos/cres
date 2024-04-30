#include "set_app_by_args.h"

void set_app_by_args(App *app, int argc, char *argv[]) {
    /** Copy original parameters */
    app->env = PROD;
    app->params.argc = argc;
    app->params.argv = argv;

    for (int i = 0; i < argc; i++) {
        if (i == 2) {
            app->params.file_target = argv[i];
        }
    }
}
