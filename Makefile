CC=gcc
CFLAGS = -O2 -Wall -g 

all: steg

steg: CLI.c 
	$(CC) $(CFLAGS) -o steg CLI.c

clean:
	rm -f steg