CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cres
SOURCES = src/util/log/log.c \
          src/cli/get_args.c \
          src/finder/get_relative_filepath.c \
          src/header/create_header_file.c \
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