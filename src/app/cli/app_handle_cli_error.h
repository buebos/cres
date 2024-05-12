#ifndef __APP_CLI_HANDLE_ERROR_H__

#define __APP_CLI_HANDLE_ERROR_

#include "../../../module/clic/include/parse.h"
#include "../../util/app.h"
#include "../../util/log/log.h"

int app_handle_cli_error(App* app, CliParseResult err);

#endif  // !__APP_CLI_HANDLE_ERROR_H__