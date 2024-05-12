CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cres
SOURCES = src/lib/source/clic/src/util/*.c \
         src/lib/source/clic/src/token/*.c \
         src/lib/source/clic/src/*.c \
         src/util/app.c \
         src/util/log/log.c \
         src/app/config/app_setup_config.c \
         src/app/cli/app_cli_handle_error.c \
         src/build/build.c \
         src/header/header.c \
         src/help/help.c \
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