# TODO: This script should be able to build the project directly parsing the compile_commands JSON or something.
kernel_release="$(uname -r)"

if [[ "$kernel_release" == *"Microsoft"* || "$kernel_release" == *"microsoft"* ]]; then
    is_windows=true
fi

if [[ $is_windows ]]; then
    cmd.exe /C "gcc module/clic/src/util/*.c module/clic/src/token/*.c module/clic/src/*.c src/util/app.c src/util/log/log.c src/app/config/app_setup_config.c src/app/cli/app_handle_cli_error.c src/build/build.c src/header/header.c src/help/help.c main.c -o build/cres"
else
    gcc module/clic/src/util/*.c module/clic/src/token/*.c module/clic/src/*.c src/util/app.c src/util/log/log.c src/app/config/app_setup_config.c src/app/cli/app_handle_cli_error.c src/build/build.c src/header/header.c src/help/help.c main.c -o build/cres
fi
