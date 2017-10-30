CC = gcc
CFLAGS = -g -Wall

all: library main.c
	$(CC) $(CFLAGS) main.c biquad.o -o program

library: library.c biquad.h
	$(CC) $(CFLAGS) -c library.c -o biquad.o