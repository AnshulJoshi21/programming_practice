CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c17 -Wno-missing-braces
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# This rule allows you to type 'make filename' for any 'filename.c'
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
