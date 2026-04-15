CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
SRCS    = src/main.c src/mersenne.c src/utils.c
OBJS    = $(SRCS:.c=.o)
TARGET  = mersenne

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c include/mersenne.h include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
