SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)


all: encrypt decrypt keygen


encrypt: encrypt.o ss.o randstate.o numtheory.o
	$(CC) -o $@ $^ $(LFLAGS)

decrypt: decrypt.o ss.o randstate.o numtheory.o
	$(CC) -o $@ $^ $(LFLAGS)

keygen: keygen.o ss.o randstate.o numtheory.o
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
		

clean:
	rm -f encrypt decrypt keygen *.o


format:
	clang-format -i -style=file *.[ch]

