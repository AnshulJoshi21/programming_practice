CC := gcc
TARGET := app

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

SRC := main.c $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC)))

# Adjust these paths if raylib is elsewhere
RAYLIB_INC := /usr/local/include
RAYLIB_LIB := /usr/local/lib

CFLAGS := -Wall -Wextra -std=c11 -I$(INC_DIR) -I$(RAYLIB_INC)
LDFLAGS := -L$(RAYLIB_LIB) -lraylib -lm -ldl -lpthread -lX11

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

