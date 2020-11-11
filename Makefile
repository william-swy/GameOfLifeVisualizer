EXENAME = ./bin/gameOfLife
EXETEST = ./bin/testGameBoard
OBJS = main.o gameBoard.o
TESTOBJS = gameBoardTest.o gameBoard.o

CXX = g++
CXXFLAGS = -c -g -Wall -I ./include -I ./lib

all : $(OBJS)
	$(CXX) -o $(EXENAME) $(OBJS)

test: $(TESTOBJS)
	$(CXX) -o $(EXETEST) $(TESTOBJS)

gameBoardTest.o : ./source/source_tests/GameBoardTest.cpp ./lib/catch.hpp
	$(CXX) $(CXXFLAGS) ./source/source_tests/GameBoardTest.cpp

main.o : ./source/source_UI/main.cpp ./include/GameBoard.h
	$(CXX) $(CXXFLAGS) ./source/source_UI/main.cpp

gameBoard.o : ./source/source_BL/GameBoard.cpp ./include/GameBoard.h
	$(CXX) $(CXXFLAGS) ./source/source_BL/GameBoard.cpp

.PHONY : clean
clean :
	-rm -f *.o ./bin/*