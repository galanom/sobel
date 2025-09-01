CC = gcc
CFLAGS = -Wall -Wextra -O3 -g3 -ggdb
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, bin/%.o, $(filter %.c,$(SRC)))
TARGET = bin/sobel

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

bin/%.o: src/%.c Makefile $(wildcard *.h) | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p $@

clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets
.PHONY: all clean

