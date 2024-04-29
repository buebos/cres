#include "log.h"

void cres_log(LogLevel log_level, char* msg, ...) {
    va_list args;
    char log_prefix[16] = {0};

    switch (log_level) {
        case DEBUG:
            strcat(log_prefix, "DEBUG");
            break;
        case INFO:
            strcat(log_prefix, "INFO");
            break;
        case WARN:
            strcat(log_prefix, "WARN");
            break;
        default:
            strcat(log_prefix, "ERROR");
    }

    va_start(args, msg);

    printf(AC_RED "[%s]: " AC_CYAN, log_prefix);
    printf(msg, args);
    printf(AC_RESET "\n");

    va_end(args);
}
