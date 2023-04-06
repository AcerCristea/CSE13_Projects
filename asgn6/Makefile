SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: encode decode


encode: word.o encode.o trie.o io.o
	$(CC) -o encode -lm word.c trie.c io.c encode.c



decode: trie.o word.o io.o decode.o
	$(CC) -o decode -lm word.c trie.c io.c decode.c


%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f encode decode *.o


format:
	clang-format -i -style=file *.[ch]

