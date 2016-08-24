
main: main.cpp data.o head.h net.o
	g++ main.cpp data.o net.o -o main

data.o: data.cpp data.h head.h
	g++ -c data.cpp

net.o: net.cpp net.h
	g++ -c net.cpp
