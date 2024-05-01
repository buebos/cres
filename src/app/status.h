#ifndef __STATUS_H__

#define __STATUS_H__

#include "../util/app.h"

void set_app_status(App *app);

char *get_app_status_msg(Status status);

#endif  // !__STATUS_H__