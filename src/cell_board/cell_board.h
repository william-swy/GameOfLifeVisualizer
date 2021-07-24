#pragma once
#include <stdexcept>
#include <vector>

namespace cell_board {
  constexpr size_t default_width = 100;
  constexpr size_t default_height = 100;
  /**
   * The CellBoard class represents the current system of
   * Conway's Game of Life.
   */
  class CellBoard {
  public:
    /**
     * Constructor to create a blank cell board state.
     */
    CellBoard();

    /**
     * Constructor to create a cell board of specified width and height
     * that has all dead cells.
     * @param width The width of the board. Precondition is that it must be greater than 0.
     * @param height The height of the oard. Precondition is that it must be greater than 0.
     */
    CellBoard(size_t width, size_t height);

    /**
     * Changes the state of the cell at the specified coordinate.
     * A dead cell is changed to alive and alive cell is changed to dead.
     * A dead cell is represented as false and an alive cell is represented as true.
     * @param x_pos The x-coordinate of the cell to be inverted.
     * @param y_pos The y-coordinate of the cell to be inverted.
     * @return The state of the cell after the inverting of state.
     * @throw BoardOutOfBounds exception for indexes outside of the CellBoard.
     */
    bool insert_point(size_t x_pos, size_t y_pos);

    /**
     * Advances the current state of the system to the next state by
     * using the following rules:
     * 		alive cells with less than 2 or greater than 3 neighbours dies.
     * 		alive cells with exactly 2 or 3 neighbours remain alive.
     * 		dead cells with exactly 3 neighbours become an alive cell.
     * Increases generation number by 1
     */
    void next_state();

    /**
     * Gets the status of the cell with the specified x and y coordinates.
     * status true for alive cell and status false for dead cell.
     * @param x_pos The x-coordinate of the cell.
     * @param y_pos The y-coordinate of the cell.
     * @return The status of the cell.
     * @throw BoardOutOfBounds exception for indexes outside of the CellBoard.
     */
    [[nodiscard]] bool get_cell(size_t x_pos, size_t y_pos) const;

    /**
     * @return The height of the cell board.
     */
    [[nodiscard]] size_t get_board_height() const noexcept;

    /**
     * @return The width of the cell board.
     */
    [[nodiscard]] size_t get_board_width() const noexcept;

    /**
     * @return The generation number of the current cell state
     */
    [[nodiscard]] size_t get_generation_number() const noexcept;

  private:
    std::vector<std::vector<bool>> curr_board_state;
    std::vector<std::vector<bool>> next_board_state;

    size_t generation_number;

    /**
     * Counts the number of alive neighbours surrounding the cell.
     * Precondition: x_pos and y_pos are both valid board cell entries. Neither are out of bounds.
     * @param x_pos The x coordinate of the cell.
     * @param y_pos The y coordinate of the cell.
     * @return The number of alive cells surrounding the indexed cell
     * @throw BoardOutOfBounds exception for indexes outside of the CellBoard.
     */
    [[nodiscard]] size_t alive_neighbour_count(size_t x_pos, size_t y_pos) const noexcept;
  };

  class BoardOutOfBounds : public std::exception {
    virtual const char* what() const noexcept { return "Index out of bounds\n"; }
  };
}  // namespace cell_board
