#pragma once
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<exception>
#include<string>
#include<vector>

namespace game {
	class GameBoard
	{
	public:
		GameBoard(int width, int height);
		void insertPoint(unsigned x, unsigned y);
		std::vector<std::string> run();
		std::string getState();
		void setTimesRun(unsigned times);

	private:
		std::vector<std::vector<bool>> gameBoard;
		std::vector<std::vector<bool>> tmpBoard;
		std::vector<std::string> states;
		std::string state;
		unsigned boardWidth;
		unsigned boardHeight;
		unsigned generationNumber;
		unsigned numberOfGenerationsToRun;

		void nextState();
		void updateState();
	};

	class BoardIndexOutOfBounds : public std::exception {
		const char *what() const throw();
	};
}
#endif