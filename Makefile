TARGET   = build/raybird
CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS  =

RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS   = $(shell pkg-config --libs raylib)

SRCDIR   = src

SOURCES  = $(wildcard $(SRCDIR)/*.c)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS) $(RAYLIB_LIBS)

clean:
	rm -rf $(TARGET) compile_commands.json

.PHONY: all run clean
