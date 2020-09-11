#include <iostream>
#include "GameBoard.h"

game::GameBoard::GameBoard(unsigned width, unsigned height) {
	boardWidth = width;
	boardHeight = height;
	gameBoard = std::vector<std::vector<bool>>(boardWidth + 2, std::vector<bool>(boardHeight + 2, 0));
	generationNumber = 0;
}

void game::GameBoard::nextState() {
	for (unsigned i = 1; i < boardWidth + 1; i++) {
		for (unsigned j = 1; j < boardHeight + 1; j++) {
			unsigned aliveCells = 0;
			for (unsigned xIndex = i - 1; xIndex <= i + 1; xIndex++) {
				for (unsigned yIndex = j - 1; yIndex <= j + 1; yIndex) {
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

void game::GameBoard::printState() {
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

void game::GameBoard::insertPoint(int x_pos, int y_pos) {
	try
	{
		gameBoard[x_pos][y_pos] = !gameBoard[x_pos][y_pos];
	}
	catch (const std::out_of_range&)
	{
		std::cout << "Oops the point (" << x_pos << " and " << y_pos << ") are not a valid input" << std::endl;
	}
}

void game::GameBoard::printGeneration() {
	printState();
	std::cout << "Generation " << generationNumber << std::endl;
	std::cout << state << std::endl;
}

void game::GameBoard::run() {
	for(unsigned i = 0; i < numberOfGenerationsToRun; i++) {
		printGeneration();
		nextState();
	}
	printGeneration();
}

void game::GameBoard::setTimesRun(unsigned times) {
	numberOfGenerationsToRun = times;
}