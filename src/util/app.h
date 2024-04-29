#ifndef __ENV_H__

#define __ENV_H__

typedef enum {
    DEV,
    PROD
} RunEnv;

typedef struct {
    int argc;
    char **argv;

    char *filename;

    bool should_gen_header_only;
} Args;

typedef struct {
    /** Original parameters */

    RunEnv env;

    Args args;

    short status;
} App;

#endif