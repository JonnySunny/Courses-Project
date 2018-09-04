
date:	main.cpp Date.o Exceptions.o
	g++ -g -Wall -o date main.cpp Date.o Exceptions.o

Date.o:	Date.cpp Date.h Debug.h
	g++ -g -Wall -c -o Date.o Date.cpp

Exceptions.o:	Exceptions.cpp Exceptions.h
	g++ -g -Wall -c -o Exceptions.o Exceptions.cpp

clean:
	rm -f date *.o