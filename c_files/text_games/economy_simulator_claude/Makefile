CC      = gcc
CFLAGS  = -std=c11 -O2 -Wall -Wextra -Wpedantic \
           -Iinclude \
           -fno-strict-aliasing
LDFLAGS = -lm

SRC     = src/main.c \
          src/world_init.c \
          src/systems/production_system.c \
          src/systems/demand_system.c \
          src/systems/price_system.c \
          src/systems/trade_system.c \
          src/systems/macro_system.c

OUT     = economy_sim

.PHONY: all clean

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OUT)
