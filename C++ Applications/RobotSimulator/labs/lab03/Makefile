C = g++
CXX = -Wall -c -std=c++11

all:lab03.out

lab03.out: main.o Duck.o MallardDuck.o DecoyDuck.o RubberDuck.o Quack.o MuteQuack.o QuackBehavior.o Squeak.o
	$(C) -o lab03.out main.o Duck.o MallardDuck.o DecoyDuck.o RubberDuck.o Quack.o MuteQuack.o QuackBehavior.o Squeak.o


main.o: main.cpp
	$(C) $(CXX) main.cpp

Duck.o: Duck.h Duck.cpp
	$(C) $(CXX) Duck.cpp

MallardDuck.o: MallardDuck.h MallardDuck.cpp
	$(C) $(CXX) MallardDuck.cpp

DecoyDuck.o: DecoyDuck.h DecoyDuck.cpp
	$(C) $(CXX)  DecoyDuck.cpp

RubberDuck.o: RubberDuck.h RubberDuck.cpp
	$(C) $(CXX) RubberDuck.cpp

Quack.o: Quack.h Quack.cpp
	$(C) $(CXX) Quack.cpp

MuteQuack.o: MuteQuack.h MuteQuack.cpp
	$(C) $(CXX) MuteQuack.cpp

QuackBehavior.o: QuackBehavior.h QuackBehavior.cpp
	$(C) $(CXX) QuackBehavior.cpp

Squeak.o: Squeak.h Squeak.cpp
	$(C) $(CXX) Squeak.cpp

clean:
	rm *.o *.out	


