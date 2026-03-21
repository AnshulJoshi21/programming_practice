CC := gcc
TARGET := game

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Recursively find all .c files inside src/
SRC := $(shell find $(SRC_DIR) -name '*.c')

# Convert src/foo/bar.c -> build/foo/bar.o
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Recursively add all include subdirectories
INC_FLAGS := $(shell find $(INC_DIR) -type d | sed 's/^/-I/')

# Adjust these paths if raylib is elsewhere
RAYLIB_INC := /usr/local/include
RAYLIB_LIB := /usr/local/lib

CFLAGS := -Wall -Wextra -Wpedantic -std=c2x $(INC_FLAGS) -I$(RAYLIB_INC)
LDFLAGS := -L$(RAYLIB_LIB) -lraylib -lm -ldl -lpthread -lX11

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile rule (preserves folder structure)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

