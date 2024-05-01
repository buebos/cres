#include "set_app_by_general_args.h"

Status set_app_by_general_args(App *app, Args *args) {
    app->env = PROD;

    return SUCCESS;
}
