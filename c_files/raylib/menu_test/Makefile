CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c17 -O2
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

# Default target
all:
	@echo "Usage: make <filename-without-.c>"

# Pattern rule
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

# Cleanup
clean:
	rm -f *.o game test
