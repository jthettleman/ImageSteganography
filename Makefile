CC=gcc
CFLAGS = -O2 -Wall -g

all: steg text_to_binary binary_to_text

steg: CLI.c
	$(CC) $(CFLAGS) -o steg CLI.c

text_to_binary: text_to_binary.c
	$(CC) $(CFLAGS) -o ttb text_to_binary.c


binary_to_text: binary_to_text.c
	$(CC) $(CFLAGS) -o btt binary_to_text.c


clean:
	rm -f steg
