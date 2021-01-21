#include "GameOfLife/gameboard.h"
#include "GameOfLife/gameboard_out_of_bounds.h"


gameboard::GameBoard::GameBoard() = default;

gameboard::GameBoard::GameBoard(int boardWidth, int boardHeight)
{
  this->width_ = boardWidth;
  this->height_ = boardHeight;
  generateBoardArray(boardWidth, boardHeight);
}

gameboard::GameBoard::GameBoard(const GameBoard &other) {
    copyBoard(other);
}

gameboard::GameBoard::~GameBoard() {
    clearBoard();
}

gameboard::GameBoard& gameboard::GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        clearBoard();
        copyBoard(other);
    }
    return *this;
}
void gameboard::GameBoard::nextState() {
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            int aliveNeighbours = aliveNeighbourCount(j, i);
            if (getCell(j, i)) {
                // Alive cell with less than 2 neighbours dies from underpopulation.
                // Alive cell with more than 3 neighbours dies from overpopulation.
                if ((aliveNeighbours < 2) || (aliveNeighbours > 3)) {
                    next_game_state_[j][i] = false;
                }
                // Otherwise cell stays alive
                else {
                    next_game_state_[j][i] = true;
                }
            }
            else {
                // Dead cell with exactly 3 alive neighbours becomes alive.
                if (aliveNeighbours == 3) {
                    next_game_state_[j][i] = true;
                }
                // Otherwise cell stays dead
                else {
                    next_game_state_[j][i] = false;
                }
            }
        }
    }
    // switch curr_game_state_ to next_game_state_;
    bool** tmp = curr_game_state_;
    curr_game_state_ = next_game_state_;
    next_game_state_ = tmp;

    // advance generation number
    this->generation_number_++;
}

bool gameboard::GameBoard::insertPoint(int x, int y) {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        throw gameBoardOutOfBounds(x, y, __LINE__);
    }
    else {
        curr_game_state_[x][y] = !curr_game_state_[x][y];
        return curr_game_state_[x][y];
    }
}

bool gameboard::GameBoard::getCell(int x, int y) {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        throw gameBoardOutOfBounds(x, y, __LINE__);
    }
    else {
        return curr_game_state_[x][y];
    }
}

int gameboard::GameBoard::getBoardHeight() const {
    return height_;
}

int gameboard::GameBoard::getBoardWidth() const {
    return width_;
}

int gameboard::GameBoard::getGenerationNumber() const {
    return generation_number_;
}

void gameboard::GameBoard::copyBoard(const GameBoard &other) {
    width_ = other.width_;
    height_ = other.height_;
    generateBoardArray(other.width_, other.height_);
}

void gameboard::GameBoard::clearBoard() {
    for (int i = 0; i < width_; i++) {
        delete[] curr_game_state_[i];
        delete[] next_game_state_[i];
    }
    delete[] curr_game_state_;
    delete[] next_game_state_;
}

void gameboard::GameBoard::generateBoardArray(int boardWidth, int boardHeight) {
    curr_game_state_ = new bool*[boardWidth];
    next_game_state_ = new bool*[boardWidth];
    for (int i = 0; i < boardWidth; i++) {
        curr_game_state_[i] = new bool[boardHeight];
        next_game_state_[i] = new bool[boardHeight];
        for (int j = 0; j < boardHeight; j++) {
            curr_game_state_[i][j] = false;
            next_game_state_[i][j] = false;
        }
    }

}

int gameboard::GameBoard::aliveNeighbourCount(int x, int y) {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
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
