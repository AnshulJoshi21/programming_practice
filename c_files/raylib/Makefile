# Compiler and flags
CC      := gcc
CFLAGS  := -std=c17 -Wall -Wextra -Iinclude -O2
LDFLAGS := -lraylib -lm -lpthread -ldl -lrt -lX11

# Directories
SRC_DIR   := src
BUILD_DIR := build

# Output executable
TARGET := game

# Find all .c files recursively
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')

# Convert src/foo/bar.c -> build/foo/bar.o
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files into build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild
re: clean all

.PHONY: all clean re
