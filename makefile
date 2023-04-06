CC = gcc
CFLAGS = -Wall -std=c99 

all: linker

linker: linker.o
	$(CC) $(CFLAGS) -o linker linker.o

linker.o: linker.c
	$(CC) $(CFLAGS) -c linker.c

clean:
	rm -f linker
