CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cres
SOURCES = src/util/log/log.c \
          src/util/finder/get_relative_filepath.c \
          src/util/app/status.c \
          src/cli/set_app_by_args.c \
          src/config/json/read.c \
          src/config/set_app_by_config.c \
          src/core/help/help.c \
          src/core/header/header.c \
          src/core/run/run.c \
          src/core/compile/compile.c \
          src/command.c \
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