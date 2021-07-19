#define CATCH_CONFIG_MAIN

#include "cell_board.h"

#include <catch2/catch.hpp>
#include <utility>
#include <vector>

constexpr unsigned REPEAT_TIMES = 10;

/**
 * Returns true if all cells in the board have the state false
 * @param test_board CellBoard to check
 * @return if all cells in testBoard dead
 */

bool check_initial_board_state(cell_board::CellBoard &test_board) {
  for (auto i = 0; i < test_board.get_board_height(); i++) {
    for (auto j = 0; j < test_board.get_board_width(); j++) {
      if (test_board.get_cell(i, j)) {
        return false;
      }
    }
  }
  return true;
}

/**
 * Returns true if all cells in the board have the same state as expected
 * @param test_board CellBoard to check
 * @param expected  expected CellBoard state
 * @return if CellBoard and expected match
 */
bool check_board_state(cell_board::CellBoard &test_board,
                       std::vector<std::vector<bool>> &expected) {
  for (int i = 0; i < test_board.get_board_width(); i++) {
    for (int j = 0; j < test_board.get_board_height(); j++) {
      if (test_board.get_cell(i, j) != expected[j][i]) {
        return false;
      }
    }
  }
  return true;
}

TEST_CASE("constructor square", "[weight=1][part=CellBoard]") {
  cell_board::CellBoard test_board(3, 3);
  REQUIRE(test_board.get_board_width() == 3);
  REQUIRE(test_board.get_board_height() == 3);
  CHECK(check_initial_board_state(test_board));
}

TEST_CASE("constructor wide rectangle", "[weight=1][part=CellBoard]") {
  cell_board::CellBoard test_board(5, 3);
  REQUIRE(test_board.get_board_width() == 5);
  REQUIRE(testBoard.getBoardHeight() == 3);
  CHECK(checkInitialBoardState(testBoard));
}

TEST_CASE("constructor tall rectangle", "[weight=1][part=CellBoard]") {
  gameBoard::GameBoard testBoard(3, 5);
  REQUIRE(testBoard.getBoardWidth() == 3);
  REQUIRE(testBoard.getBoardHeight() == 5);
  CHECK(checkInitialBoardState(testBoard));
}

TEST_CASE("getCell in bounds", "[weight=1][part=CellBoard]") {
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(0, 0);
  testBoard.insertPoint(4, 0);
  CHECK(testBoard.getCell(0, 0));
  CHECK_FALSE(testBoard.getCell(0, 4));
  CHECK(testBoard.getCell(4, 0));
  CHECK_FALSE(testBoard.getCell(4, 4));
  CHECK_FALSE(testBoard.getCell(2, 3));
}

TEST_CASE("getCell out of bounds", "[weight=1][part=CellBoard]") {
  std::vector<std::pair<int, int>> badPoints = {{-1, -1}, {-1, 5}, {5, -1}, {5, 5}};
  gameBoard::GameBoard testBoard(5, 5);
  for (std::pair<int, int> &point : badPoints) {
    try {
      testBoard.getCell(point.first, point.second);
      FAIL_CHECK("Expected gameBoardOutOfBounds exception to be thrown");
    } catch (const gameBoard::gameBoardOutOfBounds &e) {
      SUCCEED("gameBoardOutOfBounds exception thrown as expected");
    }
  }
}

TEST_CASE("insertPoint change value", "[weight=1][part=CellBoard]") {
  gameBoard::GameBoard testBoard(5, 5);
  CHECK_FALSE(testBoard.getCell(4, 3));
  testBoard.insertPoint(4, 3);
  CHECK(testBoard.getCell(4, 3));
  testBoard.insertPoint(4, 3);
  CHECK_FALSE(testBoard.getCell(4, 3));
}

TEST_CASE("insertPoint many in bounds", "[weight=1][part=CellBoard]") {
  std::vector<std::pair<int, int>> goodPoints = {{0, 0}, {2, 3}, {4, 4}, {3, 2}};
  gameBoard::GameBoard testBoard(5, 5);
  for (std::pair<int, int> &point : goodPoints) {
    try {
      testBoard.insertPoint(point.first, point.second);
      REQUIRE(testBoard.getCell(point.first, point.second) == true);
    } catch (const gameBoard::gameBoardOutOfBounds &e) {
      FAIL_CHECK("gameBoardOutOfBounds exception should not have been thrown");
    }
  }
}

TEST_CASE("insertPoint many out of bounds", "[weight=1][part=CellBoard]") {
  std::vector<std::pair<int, int>> badPoints = {{-1, -1}, {-1, 5}, {5, -1}, {5, 5}};
  gameBoard::GameBoard testBoard(5, 5);
  for (std::pair<int, int> &point : badPoints) {
    try {
      testBoard.insertPoint(point.first, point.second);
      FAIL_CHECK("gameBoardOutOfBounds exception should have been thrown");
    } catch (const gameBoard::gameBoardOutOfBounds &e) {
      SUCCEED("gameBoardOutOfBounds exception thrown");
    }
  }
}

TEST_CASE("nextState dead wasteland", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expected
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
  std::vector<int> generations = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  gameBoard::GameBoard testBoard(5, 5);
  for (int i = 0; i < REPEAT_TIMES; i++) {
    REQUIRE(testBoard.getGenerationNumber() == generations[i]);
    testBoard.nextState();
    CHECK(checkBoardState(testBoard, expected));
  }
}

TEST_CASE("nextState underpopulation corner", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expected
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(0, 0);
  testBoard.insertPoint(0, 1);
  CHECK(testBoard.getGenerationNumber() == 0);
  testBoard.nextState();
  CHECK(testBoard.getGenerationNumber() == 1);
  CHECK(checkBoardState(testBoard, expected));
}

TEST_CASE("nextState dead cells stay dead", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expected
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(3, 3);
  CHECK(testBoard.getGenerationNumber() == 0);
  for (int i = 0; i < REPEAT_TIMES; i++) {
    CHECK(testBoard.getGenerationNumber() == i);
    testBoard.nextState();
    CHECK(checkBoardState(testBoard, expected));
  }
}

TEST_CASE("nextState population growth", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expected
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 0}};
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(2, 2);
  testBoard.insertPoint(3, 2);
  testBoard.insertPoint(2, 3);
  CHECK(testBoard.getGenerationNumber() == 0);
  testBoard.nextState();
  CHECK(testBoard.getGenerationNumber() == 1);
  CHECK(checkBoardState(testBoard, expected));
}

TEST_CASE("nextState underpopulation corner with growth", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expected
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 1, 0, 0, 0}};
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(0, 4);
  testBoard.insertPoint(1, 4);
  testBoard.insertPoint(2, 2);
  testBoard.insertPoint(3, 2);
  testBoard.insertPoint(2, 3);
  CHECK(testBoard.getGenerationNumber() == 0);
  testBoard.nextState();
  CHECK(testBoard.getGenerationNumber() == 1);
  CHECK(checkBoardState(testBoard, expected));
}

TEST_CASE("nextState still life", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expected
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 0}};
  std::vector<int> generations = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(2, 2);
  testBoard.insertPoint(3, 2);
  testBoard.insertPoint(2, 3);
  testBoard.insertPoint(3, 3);
  for (int i = 0; i < REPEAT_TIMES; i++) {
    CHECK(testBoard.getGenerationNumber() == generations[i]);
    testBoard.nextState();
    CHECK(checkBoardState(testBoard, expected));
  }
}

TEST_CASE("nextState oscillator", "[weight=1][part=CellBoard]") {
  std::vector<std::vector<bool>> expectedEven
      = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
  std::vector<std::vector<bool>> expectedOdd
      = {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
  std::vector<int> generations = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  gameBoard::GameBoard testBoard(5, 5);
  testBoard.insertPoint(2, 1);
  testBoard.insertPoint(2, 2);
  testBoard.insertPoint(2, 3);
  for (int i = 0; i < REPEAT_TIMES; i++) {
    CHECK(testBoard.getGenerationNumber() == generations[i]);
    testBoard.nextState();
    if (i % 2 == 0) {
      CHECK(checkBoardState(testBoard, expectedEven));
    } else {
      CHECK(checkBoardState(testBoard, expectedOdd));
    }
  }
}
