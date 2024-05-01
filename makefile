CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cres
SOURCES = src/util/log/log.c \
          src/app/set_app_by_general_args.c \
          src/app/config/json/read.c \
          src/app/config/set_app_by_config.c \
          src/app/status.c \
          src/help/help.c \
          src/run/run.c \
          src/build/build.c \
          src/header/header.c \
          src/set_app_command.c \
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