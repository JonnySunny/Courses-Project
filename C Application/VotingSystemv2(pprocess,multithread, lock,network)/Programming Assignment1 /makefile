all: votecounter_

votecounter_: votecounter.c makeargv.h open_read.o
	gcc -std=c99 -g votecounter.c open_read.o -o votecounter

clean:
	rm votecounter

