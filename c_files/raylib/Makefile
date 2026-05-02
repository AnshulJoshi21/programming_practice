# Compiler
CC = gcc

# Output
TARGET = game

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files (mapped to build/)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Flags
CFLAGS = -Wall -std=c99 -I$(SRC_DIR)
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11

# macOS (uncomment if needed)
# LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

# Windows MinGW (uncomment if needed)
# LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Default target
all: $(BUILD_DIR) $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link
$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile src/*.c → build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run
run: all
	./$(TARGET)
