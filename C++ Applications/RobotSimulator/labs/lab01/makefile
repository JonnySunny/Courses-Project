# CSCI3081 Lab01 makefile

CC = g++
DEBUG = -g
CFLAGS = -Wall -std=c++11 -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: main.o
	$(CC) $(LFLAGS) main.o -o lab01.out

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o *.*~ lab01.out
