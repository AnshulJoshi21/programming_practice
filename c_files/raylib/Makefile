CC := gcc

TARGET := game

SRC_DIR := src
BUILD_DIR := build

SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')

# Convert:
#   src/player.c
# into:
#   build/release/player.o
RELEASE_OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/release/%.o)

# Convert:
#   src/player.c
# into:
#   build/debug/player.o
DEBUG_OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/debug/%.o)


# ============================================================
# Common flags
# ============================================================

COMMON_CFLAGS := -Wall -Wextra -std=c17

LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


# ============================================================
# Release
# ============================================================

RELEASE_CFLAGS := $(COMMON_CFLAGS) -O2


# ============================================================
# Debug
# ============================================================

DEBUG_CFLAGS := $(COMMON_CFLAGS) \
	-O0 \
	-g \
	-fsanitize=address \
	-fno-omit-frame-pointer

DEBUG_LDFLAGS := -fsanitize=address


# ============================================================
# Targets
# ============================================================

.PHONY: all release debug run debug-run clean

all: release


# ============================================================
# Release build
# ============================================================

release: $(TARGET)

$(TARGET): $(RELEASE_OBJS)
	$(CC) $(RELEASE_OBJS) -o $@ $(LDLIBS)

$(BUILD_DIR)/release/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(RELEASE_CFLAGS) -MMD -MP -I$(SRC_DIR) -c $< -o $@


# ============================================================
# Debug build
# ============================================================

debug: $(TARGET)-debug

$(TARGET)-debug: $(DEBUG_OBJS)
	$(CC) $(DEBUG_OBJS) $(DEBUG_LDFLAGS) -o $@ $(LDLIBS)

$(BUILD_DIR)/debug/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_CFLAGS) -MMD -MP -I$(SRC_DIR) -c $< -o $@


# ============================================================
# Dependency files
# ============================================================

RELEASE_DEPS := $(RELEASE_OBJS:.o=.d)
DEBUG_DEPS := $(DEBUG_OBJS:.o=.d)

-include $(RELEASE_DEPS)
-include $(DEBUG_DEPS)


# ============================================================
# Run
# ============================================================

run: release
	./$(TARGET)

debug-run: debug
	./$(TARGET)-debug


# ============================================================
# Clean
# ============================================================

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET)-debug
