#include "gameboard.h"


gameBoard::GameBoard::GameBoard(int boardWidth, int boardHeight) {
    this->width = boardWidth;
    this->height = boardHeight;
    this->generationNumber = 0;
    generateBoardArray(boardWidth, boardHeight);
}

gameBoard::GameBoard::GameBoard(const GameBoard &other) {
    copyBoard(other);
}

gameBoard::GameBoard::~GameBoard() {
    clearBoard();
}

gameBoard::GameBoard& gameBoard::GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        clearBoard();
        copyBoard(other);
    }
    return *this;
}
void gameBoard::GameBoard::nextState() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int aliveNeighbours = aliveNeighbourCount(j, i);
            if (getCell(j, i)) {
                // Alive cell with less than 2 neighbours dies from underpopulation.
                // Alive cell with more than 3 neighbours dies from overpopulation.
                if ((aliveNeighbours < 2) || (aliveNeighbours > 3)) {
                    nextGameState[j][i] = false;
                }
                // Otherwise cell stays alive
                else {
                    nextGameState[j][i] = true;
                }
            }
            else {
                // Dead cell with exactly 3 alive neigbours becomes alive.
                if (aliveNeighbours == 3) {
                    nextGameState[j][i] = true;
                }
            }
        }
    }
    // switch currGameState to nextGameState;
    bool** tmp = currGameState;
    currGameState = nextGameState;
    nextGameState = tmp;

    // advance generation number
    this->generationNumber++;
}

bool gameBoard::GameBoard::insertPoint(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        throw gameBoardOutOfBounds(x, y, __LINE__);
    }
    else {
        currGameState[x][y] = !currGameState[x][y];
        return currGameState[x][y];
    }
}

bool gameBoard::GameBoard::getCell(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        throw gameBoardOutOfBounds(x, y, __LINE__);
    }
    else {
        return currGameState[x][y];
    }
}

int gameBoard::GameBoard::getBoardHeight() {
    return height;
}

int gameBoard::GameBoard::getBoardWidth() {
    return width;
}

int gameBoard::GameBoard::getGenerationNumber() {
    return generationNumber;
}

void gameBoard::GameBoard::copyBoard(const GameBoard &other) {
    width = other.width;
    height = other.height;
    generateBoardArray(other.width, other.height);
}

void gameBoard::GameBoard::clearBoard() {
    for (int i = 0; i < width; i++) {
        delete[] currGameState[i];
        delete[] nextGameState[i];
    }
    delete[] currGameState;
    delete[] nextGameState;
}

void gameBoard::GameBoard::generateBoardArray(int boardWidth, int boardHeight) {
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

int gameBoard::GameBoard::aliveNeighbourCount(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        throw gameBoardOutOfBounds(x, y, __LINE__);
    }
    else {
        int aliveNeighbours = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                try {
                    bool state = getCell(i + x, j + y);
                    // don't count the current cell
                    if ((i == 0) && (j == 0)) {
                        continue;
                    }
                    if (state) {
                        aliveNeighbours++;
                    }
                }
                catch(gameBoardOutOfBounds& e) {
                    // aliveNeighbourCount stays the same
                }
            }
        }
        return aliveNeighbours;
    }
}
