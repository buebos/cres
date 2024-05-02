# TODO: This script should be able to build the project directly parsing the compile_commands JSON or something.

cmd.exe /C "gcc src/util/log/log.c src/util/app.c src/app/app_setup_common_args.c src/app/config/json/read.c src/app/config/app_setup_config.c src/help/help.c src/run/run.c src/build/build.c src/header/header.c src/app_set_command.c main.c -o build/cres"
