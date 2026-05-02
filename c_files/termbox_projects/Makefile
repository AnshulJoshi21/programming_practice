CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c99
SRC = $(shell find . -name "*.c")
TARGET = game


$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


.PHONY clean run

clean:
	rm -rf game

run:
	./game
