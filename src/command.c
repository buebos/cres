#include "util/app/command.h"

#include "core/compile/compile.h"
#include "core/header/header.h"
#include "core/help/help.h"
#include "core/run/run.h"

Command command_factory(char* command_id) {
    if (command_id == NULL || strcmp(command_id, "help") == 0) {
        return (Command){HELP, help};
    }

    if (strcmp(command_id, "run") == 0) {
        return (Command){RUN, run};
    }

    if (strcmp(command_id, "compile") == 0) {
        return (Command){COMPILE, compile};
    }

    if (strcmp(command_id, "header") == 0) {
        return (Command){HEADER, header};
    }

    return (Command){UNKNOWN, NULL};
}