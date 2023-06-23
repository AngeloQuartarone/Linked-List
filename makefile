SHELL=/bin/bash
CC=gcc
CFLAGS= -Wall -Wextra -pedantic -g
VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes -s 
.PHONY: clean run

run: example
	./example
default: example

example: example.o ./linkedlist.o
	$(CC) $^ -o $@ -pthread

example.o: example.c ./linkedlist.h
linkedlist.o: ./linkedlist.c ./linkedlist.h

clean:
	rm -f *.o example