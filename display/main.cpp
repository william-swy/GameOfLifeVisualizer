#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "GameBoard.h"

int main()
{
   gameBoard::GameBoard board(5,5);
   board.insertPoint(0,4);
   board.insertPoint(1,4);
   board.insertPoint(2,2);
   board.insertPoint(3,2);
   board.insertPoint(2,3);
   std::cout << "initial state" << std::endl;
   for (int i = 0; i < board.getBoardHeight(); i++) {
      std::string row = "";
      for (int j = 0; j < board.getBoardWidth(); j++) {
         row += std::to_string(board.getCell(j,i));
      }
      std::cout << row << std::endl;
   }
   std::cout << "\n" << std::endl;
   board.nextState();
   std::cout << "next state" << std::endl;
   for (int i = 0; i < board.getBoardHeight(); i++) {
      std::string row = "";
      for (int j = 0; j < board.getBoardWidth(); j++) {
         row += std::to_string(board.getCell(j,i));
      }
      std::cout << row << std::endl;
   }
}



