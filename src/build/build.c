#include "build.h"

typedef enum ArgID {
    BUILD_TARGET,
    BUILD_DEFINES,

    BUILD_RESOLVER_SHORTCUT,
    BUILD_RESOLVER_SEARCHES,

    BUILD_OUT_DIR,
    BUILD_OUT_TEMPDIR,
    BUILD_OUT_FILENAME,
    BUILD_OUT_LIB,

    BUILD_COPIES,

    BUILD_SOURCE_INCLUDES,
    BUILD_SOURCE_EXCLUDES,

    BUILD_LIB_STATICS,
    BUILD_LIB_DYNAMICS,

    BUILD_VARIANT

} ArgID;

void build_setup_args(App* app, Args* args) {}

void build(App* app) {
    cres_log(LOG_WARN, "BUILD Command not implemented");
}

const Command BUILD_COMMAND = {
    .id = BUILD,
    .label = "build",
    .run = build,
    .setup_args = build_setup_args,
    .params = {
        {
            .type = CMD_PARAM_FILE,
            .value = NULL,
            .nullable = false,
        },
    },
    .args = {
        {
            .id = BUILD_TARGET,
            .aliases = {"-t", "--target"},
            .max_params_len = 1,
            .params = {
                .len = 1,
                .data = {
                    {
                        .type = CMD_PARAM_ENUM,
                        .value = NULL,
                        .nullable = false,
                        .value_constraints = {"WIN64", "WIN32", "MACOS", "LINUX"},
                    },
                },
            },
        },
        {
            .id = BUILD_DEFINES,
            .aliases = {"-d", "--defines"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_RESOLVER_SHORTCUT,
            .aliases = {"-rsct", "--resolver-shortcut"},
            .max_params_len = 1,
            .params = {
                .len = 1,
                .data = {
                    {
                        .type = CMD_PARAM_ENUM,
                        .nullable = true,
                        .value = "RELATIVE_TO_DEF",
                        .value_constraints = {"RELATIVE_TO_DEF"},
                    },
                },
            },
        },
        {
            .id = BUILD_RESOLVER_SEARCHES,
            .aliases = {"-rsch", "--resolver-searches"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_OUT_DIR,
            .aliases = {"-od", "--out-dir"},
            .max_params_len = 1,
            .params = {
                .len = 1,
                .data = {{.type = CMD_PARAM_DIR, .value = NULL, .nullable = true}},
            },
        },
        {
            .id = BUILD_OUT_TEMPDIR,
            .aliases = {"-tmp", "--out-temp-dir"},
            .max_params_len = 1,
            .params = {
                .len = 1,
                .data = {{.type = CMD_PARAM_DIR, .value = NULL, .nullable = true}},
            },
        },
        {
            .id = BUILD_OUT_FILENAME,
            .aliases = {NULL, NULL},
            .max_params_len = 1,
            .params = {
                .len = 1,
                .data = {{.type = CMD_PARAM_STR, .value = NULL, .nullable = true}},
            },
        },
        {
            .id = BUILD_OUT_LIB,
            .aliases = {"-l", "--lib"},
            .max_params_len = 0,
            .params = {0},
        },
        {
            .id = BUILD_COPIES,
            .aliases = {"-c", "--copies"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_SOURCE_INCLUDES,
            .aliases = {"-srci", "--source-includes"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_SOURCE_EXCLUDES,
            .aliases = {"-srce", "--source-excludes"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_LIB_STATICS,
            .aliases = {"-libs", "--lib-statics"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_LIB_DYNAMICS,
            .aliases = {"-libs", "--lib-dynamics"},
            .max_params_len = -1,
            .params = {0},
        },
        {
            .id = BUILD_VARIANT,
            .aliases = {"-v", "--variant"},
            .max_params_len = 1,
            .params = {
                .len = 1,
                .data = {{.type = CMD_PARAM_STR, .value = NULL, .nullable = false}},
            },
        },
    }};