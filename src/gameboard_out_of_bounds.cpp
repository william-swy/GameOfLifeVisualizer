#include "GameOfLife/gameboard_out_of_bounds.h"


gameboard::gameBoardOutOfBounds::gameBoardOutOfBounds(int x, int y, int line)
{
  input_x_ = x;
  input_y_ = y;
  line_ = line;
}

int gameboard::gameBoardOutOfBounds::x_coord() const {
  return input_x_;
}

int gameboard::gameBoardOutOfBounds::y_coord() const {
  return input_y_;
}

int gameboard::gameBoardOutOfBounds::line() const
{
  return line_;
}

const char* gameboard::gameBoardOutOfBounds::what() const noexcept
{
  return "gameBoardOutOfBounds Exception";
}