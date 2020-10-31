EXENAME = gameOfLife
OBJS = main.o GameBoard.o

CXX = g++
CXXFLAGS = -c -g -Wall

all : $(OBJS)
	$(CXX) -o $(EXENAME) $(OBJS)

main.o : main.cpp GameBoard.h
	$(CXX) $(CXXFLAGS) main.cpp

GameBoard.o : GameBoard.cpp GameBoard.h
	$(CXX) $(CXXFLAGS) GameBoard.cpp

clean :
	-rm -f *.o $(EXENAME)