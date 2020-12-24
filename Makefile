# Compiler and linker
CXX := g++

# Targets
DEBUGEXE := gameOfLife
TESTEXE	:= testGameBoard

# Directories
BUILDDIR := bin
INCDIR := lib
BOARDDIR := gameBoard
DISPLAYDIR := display

# Flags, Includes
INC := -I $(INCDIR) -I $(BOARDDIR)
CXXFLAGS = -std=c++11 -c -g -Wall -Wextra -pedantic -O0 $(INC)

TESTOBJS := $(addprefix $(BUILDDIR)/, GameBoard.o GameBoardTest.o)
OBJS := $(addprefix $(BUILDDIR)/, GameBoard.o main.o)

all : $(DEBUGEXE) $(TESTEXE)

test : $(TESTEXE)

debug : $(DEBUGEXE)

$(DEBUGEXE) : $(OBJS)
	$(CXX) -o $(BUILDDIR)/$(DEBUGEXE) $(OBJS)

$(TESTEXE) : $(TESTOBJS)
	$(CXX) -o $(BUILDDIR)/$(TESTEXE) $(TESTOBJS)

$(BUILDDIR)/GameBoard.o : $(addprefix $(BOARDDIR)/, src/GameBoard.cpp GameBoard.h)
	$(CXX) $(CXXFLAGS) $(BOARDDIR)/src/GameBoard.cpp -o $@

$(BUILDDIR)/GameBoardTest.o : $(addprefix $(BOARDDIR)/, test/GameBoardTest.cpp GameBoard.h)
	$(CXX) $(CXXFLAGS) $(BOARDDIR)/test/GameBoardTest.cpp -o $@

$(BUILDDIR)/main.o : $(DISPLAYDIR)/main.cpp $(BOARDDIR)/GameBoard.h
	$(CXX) $(CXXFLAGS) $(DISPLAYDIR)/main.cpp -o $@

.PHONY : clean
clean :
	-rm -f ./bin/*