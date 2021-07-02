CFLAGS:=-std=c11
CFLAGS+=-Wall -Werror
CFLAGS+=-g -O0

all: main

clean:
	$(RM) main
