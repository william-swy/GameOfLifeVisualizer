#include "GameBoard.h"

game::GameBoard::GameBoard(int boardWidth, int boardHeight) {
	this->width = boardWidth;
	this->height = boardHeight;
	generateBoardArray(boardWidth, boardHeight);
}

game::GameBoard::GameBoard(const GameBoard &other) {
	copyBoard(other);
}

game::GameBoard::~GameBoard() {
	clearBoard();
}

game::GameBoard& game::GameBoard::operator=(const GameBoard& other) {
	if (this != &other) {
		clearBoard();
		copyBoard(other);
	}
	return *this;
}
void game::GameBoard::nextState() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int aliveNeighbours = aliveNeighbourCount(i, j);
			if (getCell(i, j)) {
				// Alive cell with less than 2 neighbours dies from underpopulation. 
				// Alive cell with more than 3 neighbours dies from overpopulation.
				if ((aliveNeighbours < 2) || (aliveNeighbours > 3)) {
					nextGameState[i][j] = false;
				}
			}
			else {
				// Dead cell with exactly 3 alive neigbours becomes alive.
				if (aliveNeighbours == 3) {
					nextGameState[i][j] = true;
				}
			}
		}
	}
	// switch currGameState to nextGameState;
	bool** tmp = currGameState;
	currGameState = nextGameState;
	nextGameState = tmp;
}

bool game::GameBoard::insertPoint(int x, int y) {
	if (x < 0 || y < 0 || x >= width || y >= height) {
		throw gameBoardOutOfBounds(x, y, __LINE__);
	}
	else {
		currGameState[x][y] = !currGameState[x][y];
		return currGameState[x][y];
	}
}

bool game::GameBoard::getCell(int x, int y) {
	if (x < 0 || y < 0 || x >= width || y >= height) {
		throw gameBoardOutOfBounds(x, y, __LINE__);
	}
	else {
		return currGameState[x][y];
	}
}

int game::GameBoard::getBoardHeight() {
	return height;
}

int game::GameBoard::getBoardWidth() {
	return width;	
}

void game::GameBoard::copyBoard(const GameBoard &other) {
	width = other.width;
	height = other.height;
	generateBoardArray(other.width, other.height);
}

void game::GameBoard::clearBoard() {
	for (int i = 0; i < width; i++) {
		delete[] currGameState[i];
		delete[] nextGameState[i];
	}
	delete[] currGameState;
	delete[] nextGameState;
}

void game::GameBoard::generateBoardArray(int boardWidth, int boardHeight) {
	currGameState = new bool*[boardWidth];
	nextGameState = new bool*[boardWidth];
	for (int i = 0; i < boardWidth; i++) {
		currGameState[i] = new bool[boardHeight];
		nextGameState[i] = new bool[boardHeight];
		for (int j = 0; j < boardHeight; j++) {
			currGameState[i][j] = false;
			nextGameState[i][j] = false;
		}
	}

}

int game::GameBoard::aliveNeighbourCount(int x, int y) {
	if (x < 0 || y < 0 || x >= width || y >= height) {
		throw gameBoardOutOfBounds(x, y, __LINE__);
	}
	else {
		int aliveNeighbours = 0;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				try {
					bool state = getCell(i + x, j + y);
					if (state) {
						aliveNeighbours++;
					}
				}
				catch(gameBoardOutOfBounds& e) {
					// aliveNeighbourCount stays the same
				}
			}
		}
		// remove the cell itself from the aliveNeighbourCount
		aliveNeighbours--;
		return aliveNeighbours;
	}
}