CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cres
SOURCES = src/util/log/log.c \
        src/util/app.c \
        src/app/app_setup_common_args.c \
        src/app/config/json/read.c \
        src/app/config/app_setup_config.c \
        src/help/help.c \
        src/run/run.c \
        src/build/build.c \
        src/header/header.c \
        src/app_set_command.c \
        main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean