SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: life 


life: life.o universe.o 
	$(CC) -o life -lncurses universe.c life.c 
	
life.o: *.c
	$(CC) $(CFLAGS) -c *.c
	
		

clean:
	rm -f life *.o


format:
	clang-format -i -style=file *.[ch]

