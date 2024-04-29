#include "src/cli/get_args.h"
#include "src/finder/get_relative_filepath.h"
#include "src/header/create_header_file.h"
#include "src/util/app.h"
#include "src/util/log/log.h"

int main(int argc, char **argv) {
    App app = {0};

    /** TODO: Maybe refactor to a set_args function? */
    app.args = get_args(&app, argc, argv);

    if (app.status != CORRECT) {
        cres_log(ERROR, get_args_error_msg(app.status));
        return app.status;
    }

    /**
     * The args could contain a filename that is unique in the whole
     * source code root directory or a relative path that indicates
     * already where to find the entry file. Therefore the filepath
     * must be arranged from the args argument.
     */
    char *relative_filepath = get_relative_filepath(app.args.filename);

    if (app.args.should_gen_header_only) {
        /** Gen a header file for the c filename requested and end the program */
        create_header_file(&app, relative_filepath);
        return app.status;
    }

    return app.status;
}