
all : Main

Main : main.cpp ppmFunctions.cpp pgmFunctions.cpp tgm.cpp
	g++ -std=c++11 main.cpp tgm.cpp ppmFunctions.cpp pgmFunctions.cpp -lpthread -o LumDest


clean :
	rm -rf *.o
