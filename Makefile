CC=gcc
CFLAGS = -O2 -Wall -g

all: steg

steg: head.h CLI.c ImageHandler.c TextFileHandler.c
	$(CC) $(CFLAGS) -o steg CLI.c ImageHandler.c head.h TextFileHandler.c

clean:
	rm -f steg
