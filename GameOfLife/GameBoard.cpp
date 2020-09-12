#include "GameBoard.h"

game::GameBoard::GameBoard(int width, int height) {
	boardWidth = width;
	boardHeight = height;
	gameBoard = std::vector<std::vector<bool>>(boardWidth + 2, std::vector<bool>(boardHeight + 2, 0));
	states = std::vector<std::string>();
	generationNumber = 0;
}

void game::GameBoard::nextState() {
	for (unsigned i = 1; i < boardWidth + 1; i++) {
		for (unsigned j = 1; j < boardHeight + 1; j++) {
			unsigned aliveCells = 0;
			for (unsigned xIndex = i - 1; xIndex <= i + 1; xIndex++) {
				for (unsigned yIndex = j - 1; yIndex <= j + 1; yIndex++) {
					if (gameBoard[i + xIndex][j + yIndex]) {
						aliveCells++;
					}
				}
			}
			aliveCells -= gameBoard[i][j];
			if (gameBoard[i][j]) {
				if ((aliveCells < 2) | (aliveCells > 3)) {
					tmpBoard[i][j] = 0;
				}
				else {
					tmpBoard[i][j] = 1;
				}
			}
			else {
				tmpBoard[i][j] = gameBoard[i][j];
			}
		}
	}
	gameBoard = tmpBoard;
	generationNumber++;
}

void game::GameBoard::updateState() {
	state = "";
	for (unsigned i = 1; i < boardWidth + 1; i++) {
		for (unsigned j = 1; j < boardHeight + 1; j++) {
			if (gameBoard[i][j]) {
				state += "*";
			}
			else {
				state += ".";
			}
		}
		state += "\n";
	}
}

void game::GameBoard::insertPoint(unsigned x_pos, unsigned y_pos) {
	if ((0 <= x_pos && x_pos < boardWidth) | (0 <= y_pos && y_pos < boardHeight)) {
		gameBoard[x_pos+1][y_pos+1] = !gameBoard[x_pos+1][y_pos+1];	
	}
	else {
		throw BoardIndexOutOfBounds();
	}
}


std::vector<std::string> game::GameBoard::run() {
	updateState();
	states.push_back(state);
	for(unsigned i = 0; i < numberOfGenerationsToRun; i++) {
		nextState();
		updateState();
		states.push_back(state);
	}
	return states;
}

std::string game::GameBoard::getState() {
	updateState();
	return state;
}

void game::GameBoard::setTimesRun(unsigned times) {
	numberOfGenerationsToRun = times;
}

const char* game::BoardIndexOutOfBounds::what() const throw() {
	return "Value attempted to access out of bounds";
}