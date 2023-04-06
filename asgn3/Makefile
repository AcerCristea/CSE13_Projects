SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: sorting 


sorting: sorting.o stats.o shell.o quick.o heap.o batcher.o set.o
	$(CC) -o sorting shell.c sorting.c stats.c quick.c heap.c batcher.c set.c
	
sorting.o: *.c
	$(CC) $(CFLAGS) -c *.c


test2: test2.o stats.o shell.o quick.o heap.o batcher.o
	$(CC) -o test2 -lm shell.c test2.c stats.c quick.c heap.c batcher.c
	
test2.o: *.c
	$(CC) $(CFLAGS) -c *.c
	
clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.[ch]

