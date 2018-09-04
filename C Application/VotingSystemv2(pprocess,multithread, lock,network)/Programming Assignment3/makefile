make: all

all: votecounter

votecounter: votecounter.c util.h
	gcc -std=c99 -pthread -D_BSD_SOURCE -o votecounter votecounter.c

clean:
	rm votecounter
