proj3 : Project4.o Account.o
	g++ -o proj4 Project4.o Account.o

Account.o : Account.cpp Account.h
	g++ -c -Wall Account.cpp

Project3.o : Project3.cpp Account.h
	g++ -c -Wall Project3.cpp

clean :
	rm *.o proj4