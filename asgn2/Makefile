SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: mathlib-test

mathlib-test: e.o mathlib-test.o euler.o newton.o madhava.o bbp.o viete.o
	$(CC) -o mathlib-test -lm e.c mathlib-test.c euler.c newton.c madhava.c bbp.c viete.c
		
mathlib-test.o: *.c
	$(CC) $(CFLAGS) -c *.c
	

test1: e.o test1.o euler.o newton.o madhava.o bbp.o viete.o
	$(CC) -o test1 -lm e.c test1.c euler.c newton.c madhava.c bbp.c viete.c
	
test1.o: *.c
	$(CC) $(CFLAGS) -c *.c
	
clean:
	rm -f mathlib-test *.o

format:
	clang-format -i -style=file *.[ch]


