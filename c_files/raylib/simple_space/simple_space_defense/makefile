# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 $(addprefix -I, $(shell find include -type d))
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN = game

# Source and object files
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(BIN)

# Link the final binary
$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Phony targets
.PHONY: all clean
