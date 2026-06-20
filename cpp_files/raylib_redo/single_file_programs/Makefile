CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -O2
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

# Default target
all:
	@echo "Usage: make <filename-without-.cpp>"

# Pattern rule
%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

# Cleanup
clean:
	rm -f *.o game test
