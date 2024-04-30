# TODO: This script should be able to run the project directly parsing the compile_commands JSON or something.

gcc src/cli/set_app_by_args.c src/util/log/log.c src/finder/get_relative_filepath.c src/header/create_header_file.c  main.c -o build/cres