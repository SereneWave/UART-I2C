CC = gcc
CFLAGS = -I./include
TARGET = uart-iic-app
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))

.PHONY: clean

$(shell mkdir -p build)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
