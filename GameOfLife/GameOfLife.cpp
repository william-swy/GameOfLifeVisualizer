#include <iostream>
#include <string>
#include "GameBoard.h"

int main()
{
    int width = 0;
    int height = 0;
    std::string input;
    while((0 >= width) | (0 >= height)) {
        std::cout << "Enter width of environment greater than 0:" << std::endl;
        std::cin >> width;
        std::cout << "Enter height of environment greater than 0:" << std::endl;
        std::cin >> height;
    }

    game::GameBoard gameBoard(width, height);
    
    while(input != "-d") {
        std::cout << "(x, y) to flip the coordinate value from cell to non-cell and vice-versa" << std::endl;
        std::cout << "-v : view environment" << std::endl;
        std::cout << "-d : run" <<std::endl;

        if (input == "-d") {
            std::cout << "running" << std::endl;
        }
        else if (input == "-v") {
            gameBoard.printState();
        } 
        else if (input.size() > 2 && input[0] == '(' && input[input.size() - 1] == ')') {
            input = input.substr(1, input.size()-2);
        }
        else {
            std::cout << "Not valid input" << std::endl;
        }
    }
    
    gameBoard.run();
}



