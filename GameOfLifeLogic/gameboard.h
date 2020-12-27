#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include<exception>


namespace gameBoard {
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
             * Constructor to create a game board of specified width and height
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
             * Assignment operator
             * @param other The GameBoard to assign from
             */
            GameBoard& operator=(const GameBoard& other);

            /**
             * Changes the state of the cell at the specified coordinate.
             * A dead cell is changed to alive and alive cell is changed to dead.
             * A dead cell is represented as false and an alive cell is represented as true.
             * @param x The x-coordinate of the cell to be inverted.
             * @param y The y-coordinate of the cell to be inverted.
             * @return The state of the cell after the inverting of state.
             * @throw gameBoardOutOfBounds exception for indexes outside of the gameBoard.
             */
            bool insertPoint(int x, int y);

            /**
             * Advances the current state of the system to the next state by
             * using the following rules:
             * 		alive cells with less than 2 or greater than 3 neighbours dies.
             * 		alive cells with exactly 2 or 3 neighbours remain alive.
             * 		dead cells with exactly 3 neighbours become an alive cell.
             * Increases generation number by 1
             */
            void nextState();

            /**
             * Gets the status of the cell with the specified x and y coordinates.
             * status true for alive cell and status false for dead cell.
             * @param x The x-coordinate of the cell.
             * @param y The y-coordinate of the cell.
             * @return The status of the cell.
             * @throw gameBoardOutOfBounds exception for indexes outside of the gameBoard.
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

            /**
             * @return The generation number of the current cell state
             */
            int getGenerationNumber();

        private:
            int height = 0;
            int width = 0;
            bool** currGameState;
            bool** nextGameState;
            int generationNumber;

            /**
             * Copies the other gameBoard's currGameState, height and width into current GameBoard.
             * @param other The gameBoard to copy from.
             * @return Pointer to new gameBoard
             */
            void copyBoard(const GameBoard& other);

            /**
             * Clears the memory associated with the currGameState and nextGameState.
             */
            void clearBoard();

            /**
             * Generates the array which currGameState and nextGameState point to will all cells dead
             * @param width The width of the board to generate
             * @param height The height of the board to generate
             */
            void generateBoardArray(int width, int height);

            /**
             * Counts the number of alive neighbours surrounding the cell.
             * @param xCoord The x coordinate of the cell.
             * @param yCoord The y coordinate of the cell.
             * @return The number of alive cells surrounding the indexed cell
             * @throw gameBoardOutOfBounds exception for indexes outside of the gameBoard
             */
            int aliveNeighbourCount(int x, int y);
    };

    class gameBoardOutOfBounds: public std::exception {
        protected:
            int inputX;
            int inputY;
            int line;

        public:
            gameBoardOutOfBounds(const int x, const int y, const int line) {
                inputX = x;
                inputY = y;
                this->line = line;
            }
            int getInputX() {
                return inputX;
            }
            int getInputY() {
                return inputY;
            }
            int getLine() {
                return line;
            }
            const char* what() const throw() {
                return "gameBoardOutOfBounds Exception";
            }
    };
}

#endif // GAMEBOARD_H
