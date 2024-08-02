CC = gcc
CFLAGS = -Wall -Wextra -O0 -g3 -ggdb
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean

