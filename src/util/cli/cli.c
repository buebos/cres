#include "cli.h"

bool arg_is_cmd(char *arg) {
    return arg[0] == '-';
}