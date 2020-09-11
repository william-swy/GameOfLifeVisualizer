#pragma once
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<string>
#include<vector>

namespace game {
	class GameBoard
	{
	public:
		GameBoard(unsigned width, unsigned height);
		void nextState();
		void printState();
		void insertPoint(int x, int y);
		void printGeneration();
		void run();
		void setTimesRun(unsigned times);

	private:
		std::vector<std::vector<bool>> gameBoard;
		std::vector<std::vector<bool>> tmpBoard;
		std::string state;
		unsigned boardWidth;
		unsigned boardHeight;
		unsigned generationNumber;
		unsigned numberOfGenerationsToRun;
	};
}
#endif