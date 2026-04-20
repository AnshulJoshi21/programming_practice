# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -I./src
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Directories
SRC_DIR = src
BUILD_DIR = build

# Find all source files recursively
SRCS := $(shell find $(SRC_DIR) -name '*.c')

# Convert src/file.c -> build/file.o
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output binary
TARGET = game

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile (auto-creates subdirectories in build/)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
