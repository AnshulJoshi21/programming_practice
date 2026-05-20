# Compiler
CC := gcc

# Output binary
TARGET := game

# Directories
SRC_DIR := src
BUILD_DIR := build

# Compiler flags
CFLAGS := -Wall -Wextra -std=c17
CPPFLAGS := $(shell find $(SRC_DIR) -type d | sed 's/^/-I/')

# Linker flags
LDFLAGS := -lraylib -lm -lpthread -ldl -lrt -lX11

# Find all source files recursively
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')

# Map src/foo/bar.c -> build/foo/bar.o
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Dependency files
DEP_FILES := $(OBJ_FILES:.o=.d)

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEP_FILES)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run executable
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean run
