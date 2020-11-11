#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "GameBoard.h"


TEST_CASE("constructor square", "[weight=1][part=GameBoard")
{
    game::GameBoard testBoard(3,3);
    REQUIRE(testBoard.getBoardWidth() == 3);
    REQUIRE(testBoard.getBoardHeight() == 3);
}

TEST_CASE("constructor wide rectangle", "[weight=1][part=GameBoard")
{
    game::GameBoard testBoard(5,3);
    REQUIRE(testBoard.getBoardWidth() == 5);
    REQUIRE(testBoard.getBoardHeight() == 3);
}

TEST_CASE("constructor tall rectangle", "[weight=1][part=gameBoard")
{
    game::GameBoard testBoard(3,5);
    REQUIRE(testBoard.getBoardWidth() == 3);
    REQUIRE(testBoard.getBoardHeight() == 5);
}

