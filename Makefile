all: begin

begin: main.o AbstractBoard.o BoardVector.o BoardArray2D.o BoardArray1D.o
	  g++  main.o AbstractBoard.o BoardVector.o BoardArray2D.o BoardArray1D.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

AbstractBoard.o: AbstractBoard.cpp
	g++ -std=c++11 -c AbstractBoard.cpp

BoardVector.o: BoardVector.cpp
	g++ -std=c++11 -c BoardVector.cpp 

BoardArray2D.o: BoardArray2D.cpp
	g++ -std=c++11 -c BoardArray2D.cpp 

BoardArray1D.o: BoardArray1D.cpp
	g++ -std=c++11 -c BoardArray1D.cpp 	

clean:
	rm *.o exe
