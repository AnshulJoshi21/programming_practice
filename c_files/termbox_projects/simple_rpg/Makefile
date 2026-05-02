# Compiler
CC = gcc

# Flags
CFLAGS = -O2 -Wall -Wextra -std=c99 -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:.o=.d)

# Output binary
TARGET = game

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile step (creates build directories automatically)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files
-include $(DEP)

# Phony targets
.PHONY: all clean run

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
