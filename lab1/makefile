FLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm

all: main.o
	g++ $(FLAGS) main.o -o solution

main: main.cpp vector.hpp
	g++ $(FLAGS) -c main.cpp

clean:
	rm -rf *.o