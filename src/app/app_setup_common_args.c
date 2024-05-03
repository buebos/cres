#include "app_setup_common_args.h"

typedef struct ArgHandler {
    char *arg;
    void (*handler)(App *app, size_t *arg_index);
} ArgHandler;

void handle_skip_config(App *app, size_t *_) {
    app->params.should_skip_config = true;
}

void handle_config_dir(App *app, size_t *i) {
    if (*i >= app->args.len - 1) {
        app_throw_error(
            (AppError){
                ARG_MISSING_PARAM_ERROR,
                "Missing config directory right after '%s' argument, e.g.: '%s %s ./example/dir/cres.json ...'."

            },
            app->args.data[*i],
            APP_NAME,
            app->args.data[*i]

        );
    }

    app->params.config_dir = app->args.data[*i + 1];
    *i += 1;
}

static const ArgHandler HANDLERS[] = {
    {"--skip-config", handle_skip_config},
    {"-sc", handle_skip_config},
    {"--config-dir", handle_config_dir},
    {"-cfd", handle_config_dir},
};

void app_setup_common_args(App *app, Args *args) {
    for (size_t i = 1; i < args->len; i++) {
        char *arg = args->data[i];
        bool handled = false;

        for (size_t j = 0; j < sizeof(HANDLERS) / sizeof(ArgHandler); j++) {
            if (strcmp(arg, HANDLERS[j].arg) != 0) {
                continue;
            }

            HANDLERS[j].handler(app, &i);
            handled = true;
        }

        if (handled) {
            continue;
        }

        app_throw_error(
            (AppError){UNKNOWN_ARG_ERROR, "Unknown argument: '%s'."},
            arg

        );
    }
}
