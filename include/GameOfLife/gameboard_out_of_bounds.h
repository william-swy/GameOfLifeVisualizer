//
// An exception representing an attempt to grab a board coordinate that is
// not contained in the gameboard.
//

#ifndef GAMEOFLIFEAPP_GAMEBOARD_OUT_OF_BOUNDS_H
#define GAMEOFLIFEAPP_GAMEBOARD_OUT_OF_BOUNDS_H

#include<exception>


namespace gameboard {

class gameBoardOutOfBounds: public std::exception {

public:
  gameBoardOutOfBounds(int x, int y, int line);

  int x_coord() const;

  int y_coord() const;

  int line() const;

  const char* what() const noexcept override;

protected:
  int input_x_;
  int input_y_;
  int line_;
};

} // end namespace gameboard

#endif // GAMEOFLIFEAPP_GAMEBOARD_OUT_OF_BOUNDS_H
