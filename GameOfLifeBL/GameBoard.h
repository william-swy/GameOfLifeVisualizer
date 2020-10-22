#pragma once
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

namespace game {
	/**
	 * The GameBoard class represents the current system of 
	 * Conway's Game of Life.
	 */
	class GameBoard
	{
		public:
			/**
			 * Constructor to create a blank game state.
			 */
			GameBoard();

			/**
			 * Constructor to create a game board of specified widith and height
			 * that has all dead cells.
			 * @param width The width of the board.
			 * @param height The height of the game board.
			 */
			GameBoard(int width, int height);

			/**
			 * Copy constructor. 
			 */
			GameBoard (const GameBoard &other);

			/**
			 * Destructor to free the gameBoard.
			 */
			~GameBoard();

			/**
			 * Changes the state of the cell at the specified coordinate.
			 * A dead cell is changed to alive and alive cell is changed to dead.
			 * A dead cell is represented as false and an alive cell is represented as true.
			 * @param x The x-coordinate of the cell to be inverted.
			 * @param y The y-coordinate of the cell to be inverted.
			 * @return The state of the cell after the inverting of state.
			 */
			bool insertPoint(int x, int y);

			/**
			 * Advances the current state of the system to the next state by
			 * using the following rules:
			 * 		alive cells with less than 2 or greater than 3 neighbours dies.
			 * 		alive cells with exactly 2 or 3 neighbours remain alive.
			 * 		dead cells with exactly 3 neighbours become an alive cell.
			 */
			void nextState();

			/**
			 * Gets the status of the cell with the specified x and y coordinates.
			 * status true for alive cell and status false for dead cell.
			 * @param x The x-coordinate of the cell.
			 * @param y The y-coordinate of the cell.
			 * @return The status of the cell. 
			 */
			bool getCell(int x, int y);

			/**
			 * @return The height of the gameBoard.
			 */
			int getBoardHeight();

			/**
			 * @return The width of the gameBoard.
			 */
			int getBoardWidth();

		private:
			int height;
			int width;
			bool** currGameState;
			bool** nextGameState;

			/**
			 * Copies the other gameBoard's currGameState, height and width into current GameBoard.
			 * @param other The gameBoard to copy from.
			 */
			void copyBoard(const GameBoard& other);

			/**
			 * Clears the memory associated with the currGameState and nextGameState.
			 */
			void clearBoard();
	};
}
#endif