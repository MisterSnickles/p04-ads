all: p04
p04: removal main.o utility.o
	g++ -o p04 main.o utility.o
main.o: main.cpp
	g++ -c -g main.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
removal:
	rm -f *.o
