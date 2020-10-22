#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "GameBoard.h"

int main()
{
    int width = 0;
    int height = 0;
    int times = 0;
    std::string input;

    while((0 >= width) | (0 >= height)) {
        std::cout << "Enter width of environment greater than 0:" << std::endl;
        std::cin >> width;
        std::cout << "Enter height of environment greater than 0:" << std::endl;
        std::cin >> height;
    }

    game::GameBoard gameBoard(width, height);
    
    while(input != "-d") {
        std::cout << "-c 'x' 'y' flip the coordinate value from cell to non-cell and vice-versa" << std::endl;
        std::cout << "-v : view environment" << std::endl;
        std::cout << "-d : done" <<std::endl;

        std::cin >> input;

        if (input == "-d") {
            break;
        }
        else if (input == "-v") {
            std::cout << gameBoard.getState() << std::endl;
        } 
        else if (input == "-c") {
            int x;
            int y;
            std::cin >> x;
            std::cin >> y;
            if (x >= 0 && y >= 0) {
                try {
                    gameBoard.insertPoint(x, y);
                }
                catch (std::out_of_range &e) {
                    std::cout << "Oops the point (" << x << " and " << y << ") seems to not be on the environment" << std::endl;
                }
            }
            else {
                std::cout << x << " " << y << " is not valid position" << std::endl;
            }
        }
        else {
            std::cout << "Not valid input" << std::endl;
        }
    }

    while(times <= 0) {
        std::cout << "Generations to run:" << std::endl;
        std::cin >> times;
    }

    gameBoard.setTimesRun(times);
    
    std::vector<std::string> result = gameBoard.run();
    
    for (unsigned i = 0; i < result.size(); i++) {
        std::cout << "Generation " << i << std::endl;
        std::cout << result[i] << "\n" << std::endl;
    }
}



