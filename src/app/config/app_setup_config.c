#include "app_setup_config.h"

/**
 * TODO: This should contain the main file to read the config
 * and assign it to app's context. Maybe this will even be removed
 * to app.h to kinda merge the configuration and arguments structure
 * to be able to decide the behavior of the program in a more efficient
 * and centrelized way on the app's context.
 */
void app_setup_config(App* app, char* config_dir) {
    if (config_dir == NULL) {
        config_dir = DEFAULT_CONFIG_DIR;
    }

    cres_log(LOG_WARN, "Config setup not implemented.");

    return;
}