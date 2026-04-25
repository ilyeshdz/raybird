TARGET   = build/raybird
CC       = gcc
CFLAGS   = -Wall -Wextra -Wpedantic -Werror -std=c11 -Iinclude
LDFLAGS  =

RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS   = $(shell pkg-config --libs raylib)

SRCDIR   = src
OBJDIR   = build/obj

SOURCES  = $(wildcard $(SRCDIR)/*.c)
OBJECTS  = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

run-debug: CFLAGS += -DDEBUG
run-debug: clean $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p build
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(RAYLIB_LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -c $< -o $@

clean:
	rm -rf build compile_commands.json

.PHONY: all run run-debug clean
