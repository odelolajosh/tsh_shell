CC      ?= cc
CFLAGS  ?= -std=gnu11 -Wall -Wextra -Werror -g
ASAN    := -fsanitize=address,undefined -fno-omit-frame-pointer

SRCS    := $(wildcard *.c)
HDRS    := $(wildcard *.h)
OBJS    := $(SRCS:%.c=build/%.o)
ASANOBJS:= $(SRCS:%.c=build/asan/%.o)

.PHONY: all asan test test-asan clean

all: tsh

tsh: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

tsh-asan: $(ASANOBJS)
	$(CC) $(CFLAGS) $(ASAN) $^ -o $@

asan: tsh-asan

build/%.o: %.c $(HDRS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/asan/%.o: %.c $(HDRS) | build/asan
	$(CC) $(CFLAGS) $(ASAN) -c $< -o $@

build build/asan:
	mkdir -p $@

test: tsh
	./tests/run.sh ./tsh

test-asan: tsh-asan
	ASAN_OPTIONS=detect_leaks=0 ./tests/run.sh ./tsh-asan

clean:
	rm -rf build tsh tsh-asan
