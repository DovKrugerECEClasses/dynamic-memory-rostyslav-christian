fraction: Fraction.o main.o
	g++ Fraction.o main.o -o fraction

Fraction.o: Fraction.hh Fraction.cpp
	g++ -c Fraction.cpp

main.o: Fraction.hh main.cpp
	g++ -c main.cpp