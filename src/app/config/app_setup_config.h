#ifndef __CRES_GET_CONFIG_H__

#define __CRES_GET_CONFIG_H__

#include "../../util/app.h"
#include "../../util/log/log.h"

#define DEFAULT_CONFIG_DIR "./cres.json"

void app_setup_config(App* app, char* config_dir);

#endif