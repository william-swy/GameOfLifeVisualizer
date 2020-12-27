#include "gameboard.h"
#include <iostream>
#include <limits>
#include <string>

/**
 * Simple console program that uses the gameBoard to show cell states
 * with "*" being alive and "." being dead.
 */

using std::cin;
using std::cout;
using std::endl;

gameBoard::GameBoard *board = nullptr;

void showNoBoardOptions()
{
    cout <<
        "b - New board\n"
        "q - Quit"
        << endl;
}

void showExistingBoardOptions()
{
    cout <<
        "n - Next generation\n"
        "c - Change cell state\n"
        "s - Show cells\n"
        "g - Generation number"
        << endl;
    showNoBoardOptions();
}

void showStartOptions()
{
    cout <<
         "Options:\n"
         "s - Start\n"
         "q - Quit\n"
         << endl;
}

void showGameOptions()
{
    cout << "Options:" << endl;
    if (board) {
        showExistingBoardOptions();
    }
    else {
        showNoBoardOptions();
    }
}

void printCells()
{
    int width = board->getBoardWidth();
    int height = board->getBoardHeight();

    std::string matrix = "";
    for (int i = 0; i < height; i++) {
        std::string row = "";
        for (int j = 0; j < width; j++) {
            bool cell = board->getCell(j,i);
            if (cell) {
                row += "*";
            }
            else {
                row += ".";
            }
        }
        row += "\n";
        matrix += row;
    }
    cout << matrix << endl;
}

int getIntInput() {
    bool invalid = true;
    int value = 0;

    while(invalid) {
        cin >> value;
        if (cin.good()) {
            invalid = false;
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout << "Invalid input, please re-enter" << endl;
        }
    }

    return value;
}

int getPositiveInt() {
    int i = -1;
    while(i < 0) {
        i = getIntInput();
        if (i < 0) {
            cout << "Enter a value 0 or higher" << endl;
        }
    }
    return i;
}

void changeCell()
{
    cout << "Input x coordinate" << endl;
    int x = getPositiveInt();
    cout << "Input y coordinate" << endl;
    int y = getPositiveInt();
    try {
        board->insertPoint(x,y);
        cout << "Cell changed successfully" << endl;
    }
    catch (const gameBoard::gameBoardOutOfBounds &e) {
        cout << "Coordinate (" << x << "," << y << ") out of bounds" << endl;
    }
}

void createBoard()
{
    if (board) {
        delete board;
    }
    int width;
    int height;

    cout << "Enter width:" << endl;
    width = getPositiveInt();
    cout << "Enter height" << endl;
    height = getPositiveInt();

    board = new gameBoard::GameBoard(width, height);
}

void startGame()
{
    while (true) {
        showGameOptions();
        char choice;
        cin >> choice;
        if (board) {
            switch (choice) {
                case 'n':
                    board->nextState();
                    cout << "Advanced to generation " << board->getGenerationNumber() << endl;
                    continue;
                case 'c':
                    changeCell();
                    continue;
                case 's':
                    printCells();
                    continue;
                case 'g':
                    cout << "Generation " << board->getGenerationNumber() << endl;
                    continue;
                default:
                    break;
            }
        }
        switch (choice) {
            case 'b':
                createBoard();
                continue;
            case 'q':
                return;
            default:
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << "Invalid input " << choice << ". Try again" << endl;
        }
    }
}

int main()
{
    cout <<
    "Game Of Life\n"
    "_________________\n"
    << endl;

    while(true) {
        showStartOptions();

        char input;
        cin >> input;
        switch (input) {
            case 's':
                startGame();
            case 'q':
                cout << "Bye" << endl;
                return 0;
            default:
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << "Invalid input " << input << ". Try again" << endl;
        }
    }
}
