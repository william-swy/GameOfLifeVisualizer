#define CATCH_CONFIG_MAIN

#include "cell_board.h"

#include <array>
#include <catch2/catch.hpp>
#include <utility>

constexpr size_t REPEAT_TIMES = 100;

/**
 * Returns true if all cells in the board have the state false
 * @param test_board CellBoard to check
 * @return if all cells in test_board dead
 */
bool check_initial_board_state(const cell_board::CellBoard &test_board) {
  for (auto i = 0; i < test_board.get_board_height(); i++) {
    for (auto j = 0; j < test_board.get_board_width(); j++) {
      if (test_board.get_cell(j, i)) {
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
template <std::size_t M, std::size_t N>
bool check_board_state(const cell_board::CellBoard &test_board,
                       const std::array<std::array<bool, N>, M> &expected) {
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
  REQUIRE(test_board.get_board_height() == 3);
  CHECK(check_initial_board_state(test_board));
}

TEST_CASE("constructor tall rectangle", "[weight=1][part=CellBoard]") {
  cell_board::CellBoard test_board(3, 5);
  REQUIRE(test_board.get_board_width() == 3);
  REQUIRE(test_board.get_board_height() == 5);
  CHECK(check_initial_board_state(test_board));
}

TEST_CASE("get_cell in bounds", "[weight=1][part=CellBoard]") {
  cell_board::CellBoard test_board(5, 5);
  test_board.insert_point(0, 0);
  test_board.insert_point(4, 0);
  CHECK(test_board.get_cell(0, 0));
  CHECK_FALSE(test_board.get_cell(0, 4));
  CHECK(test_board.get_cell(4, 0));
  CHECK_FALSE(test_board.get_cell(4, 4));
  CHECK_FALSE(test_board.get_cell(2, 3));
}

TEST_CASE("get_cell out of bounds", "[weight=1][part=CellBoard]") {
  constexpr std::array<std::pair<int, int>, 4> badPoints{{{-1, -1}, {-1, 5}, {5, -1}, {5, 5}}};
  cell_board::CellBoard test_board(5, 5);
  for (const std::pair<int, int> &point : badPoints) {
    try {
      const auto cell = test_board.get_cell(point.first, point.second);
      FAIL_CHECK("Expected gameBoardOutOfBounds exception to be thrown");
    } catch (const cell_board::BoardOutOfBounds &) {
      SUCCEED("gameBoardOutOfBounds exception thrown as expected");
    }
  }
}

TEST_CASE("insert_point change value", "[weight=1][part=CellBoard]") {
  cell_board::CellBoard test_board(5, 5);
  CHECK_FALSE(test_board.get_cell(4, 3));
  test_board.insert_point(4, 3);
  CHECK(test_board.get_cell(4, 3));
  test_board.insert_point(4, 3);
  CHECK_FALSE(test_board.get_cell(4, 3));
}

TEST_CASE("insert_point many in bounds", "[weight=1][part=CellBoard]") {
  constexpr std::array<std::pair<int, int>, 4> goodPoints{{{0, 0}, {2, 3}, {4, 4}, {3, 2}}};
  cell_board::CellBoard test_board(5, 5);
  for (const std::pair<int, int> &point : goodPoints) {
    try {
      test_board.insert_point(point.first, point.second);
      REQUIRE(test_board.get_cell(point.first, point.second) == true);
    } catch (const cell_board::BoardOutOfBounds &) {
      FAIL_CHECK("gameBoardOutOfBounds exception should not have been thrown");
    }
  }
}

TEST_CASE("insert_point many out of bounds", "[weight=1][part=CellBoard]") {
  constexpr std::array<std::pair<int, int>, 4> badPoints{{{-1, -1}, {-1, 5}, {5, -1}, {5, 5}}};
  cell_board::CellBoard test_board(5, 5);
  for (const std::pair<int, int> &point : badPoints) {
    try {
      test_board.insert_point(point.first, point.second);
      FAIL_CHECK("gameBoardOutOfBounds exception should have been thrown");
    } catch (const cell_board::BoardOutOfBounds &) {
      SUCCEED("gameBoardOutOfBounds exception thrown");
    }
  }
}

TEST_CASE("next_state dead wasteland", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected{
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}};

  cell_board::CellBoard test_board(5, 5);
  for (std::size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    REQUIRE(test_board.get_generation_number() == generation);
    test_board.next_state();
    CHECK(check_board_state(test_board, expected));
  }
}

TEST_CASE("next_state underpopulation corner", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected{
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}};
  cell_board::CellBoard test_board(5, 5);
  test_board.insert_point(0, 0);
  test_board.insert_point(0, 1);
  CHECK(test_board.get_generation_number() == 0);
  test_board.next_state();
  CHECK(test_board.get_generation_number() == 1);
  CHECK(check_board_state(test_board, expected));
}

TEST_CASE("next_state dead cells stay dead", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected
      = {{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}};
  cell_board::CellBoard test_board(5, 5);
  test_board.insert_point(3, 3);
  CHECK(test_board.get_generation_number() == 0);
  for (int i = 0; i < REPEAT_TIMES; i++) {
    CHECK(test_board.get_generation_number() == i);
    test_board.next_state();
    CHECK(check_board_state(test_board, expected));
  }
}

TEST_CASE("next_state population growth", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected{
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 0}}};
  cell_board::CellBoard test_board(5, 5);
  test_board.insert_point(2, 2);
  test_board.insert_point(3, 2);
  test_board.insert_point(2, 3);
  CHECK(test_board.get_generation_number() == 0);
  test_board.next_state();
  CHECK(test_board.get_generation_number() == 1);
  CHECK(check_board_state(test_board, expected));
}

TEST_CASE("next_state underpopulation corner with growth", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected{
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 1, 0, 0, 0}}};
  cell_board::CellBoard test_board(5, 5);
  test_board.insert_point(0, 4);
  test_board.insert_point(1, 4);
  test_board.insert_point(2, 2);
  test_board.insert_point(3, 2);
  test_board.insert_point(2, 3);
  CHECK(test_board.get_generation_number() == 0);
  test_board.next_state();
  CHECK(test_board.get_generation_number() == 1);
  CHECK(check_board_state(test_board, expected));
}

TEST_CASE("next_state still life box", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected{
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 0}}};
  cell_board::CellBoard test_board(5, 5);
  test_board.insert_point(2, 2);
  test_board.insert_point(3, 2);
  test_board.insert_point(2, 3);
  test_board.insert_point(3, 3);
  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    CHECK(check_board_state(test_board, expected));
  }
}

TEST_CASE("next_state still life beehive", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 6;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> beehive = {{{0, 0, 0, 0, 0, 0},
                                                                    {0, 0, 1, 1, 0, 0},
                                                                    {0, 1, 0, 0, 1, 0},
                                                                    {0, 0, 1, 1, 0, 0},
                                                                    {0, 0, 0, 0, 0, 0}}};
  cell_board::CellBoard test_board(width, height);
  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (beehive[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    CHECK(check_board_state(test_board, beehive));
  }
}

TEST_CASE("next_state still life loaf", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 6;
  constexpr std::size_t height = 6;
  constexpr std::array<std::array<bool, width>, height> loaf{{{0, 0, 0, 0, 0, 0},
                                                              {0, 0, 1, 1, 0, 0},
                                                              {0, 1, 0, 0, 1, 0},
                                                              {0, 0, 1, 0, 1, 0},
                                                              {0, 0, 0, 1, 0, 0},
                                                              {0, 0, 0, 0, 0, 0}}};

  cell_board::CellBoard test_board(width, height);
  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (loaf[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    CHECK(check_board_state(test_board, loaf));
  }
}

TEST_CASE("next_state still life boat", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> loaf{{
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 0, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
  }};

  cell_board::CellBoard test_board(width, height);
  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (loaf[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    CHECK(check_board_state(test_board, loaf));
  }
}

TEST_CASE("next_state still life tub", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> loaf{{
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 0, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
  }};

  cell_board::CellBoard test_board(width, height);
  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (loaf[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    CHECK(check_board_state(test_board, loaf));
  }
}

TEST_CASE("next_state oscillator blinker", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 5;
  constexpr std::size_t height = 5;
  constexpr std::array<std::array<bool, width>, height> expected_even{
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}};
  constexpr std::array<std::array<bool, width>, height> expected_odd{
      {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}}};

  cell_board::CellBoard test_board(width, height);
  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (expected_even[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    if (generation % 2) {
      CHECK(check_board_state(test_board, expected_even));
    } else {
      CHECK(check_board_state(test_board, expected_odd));
    }
  }
}

TEST_CASE("next_state oscillator toad", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 6;
  constexpr std::size_t height = 6;
  constexpr std::array<std::array<bool, width>, height> expected_even{{{0, 0, 0, 0, 0, 0},
                                                                       {0, 0, 0, 0, 0, 0},
                                                                       {0, 0, 1, 1, 1, 0},
                                                                       {0, 1, 1, 1, 0, 0},
                                                                       {0, 0, 0, 0, 0, 0},
                                                                       {0, 0, 0, 0, 0, 0}}};
  constexpr std::array<std::array<bool, width>, height> expected_odd{{{0, 0, 0, 0, 0, 0},
                                                                      {0, 0, 0, 1, 0, 0},
                                                                      {0, 1, 0, 0, 1, 0},
                                                                      {0, 1, 0, 0, 1, 0},
                                                                      {0, 0, 1, 0, 0, 0},
                                                                      {0, 0, 0, 0, 0, 0}}};

  cell_board::CellBoard test_board(width, height);

  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (expected_even[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    if (generation % 2) {
      CHECK(check_board_state(test_board, expected_even));
    } else {
      CHECK(check_board_state(test_board, expected_odd));
    }
  }
}

TEST_CASE("next_state oscillator beacon", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 6;
  constexpr std::size_t height = 6;
  constexpr std::array<std::array<bool, width>, height> expected_even{{{0, 0, 0, 0, 0, 0},
                                                                       {0, 1, 1, 0, 0, 0},
                                                                       {0, 1, 1, 0, 0, 0},
                                                                       {0, 0, 0, 1, 1, 0},
                                                                       {0, 0, 0, 1, 1, 0},
                                                                       {0, 0, 0, 0, 0, 0}}};
  constexpr std::array<std::array<bool, width>, height> expected_odd{{{0, 0, 0, 0, 0, 0},
                                                                      {0, 1, 1, 0, 0, 0},
                                                                      {0, 1, 0, 0, 0, 0},
                                                                      {0, 0, 0, 0, 1, 0},
                                                                      {0, 0, 0, 1, 1, 0},
                                                                      {0, 0, 0, 0, 0, 0}}};

  cell_board::CellBoard test_board(width, height);

  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (expected_even[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);
    test_board.next_state();
    if (generation % 2) {
      CHECK(check_board_state(test_board, expected_even));
    } else {
      CHECK(check_board_state(test_board, expected_odd));
    }
  }
}

// Madlad test case to write
TEST_CASE("next_state oscillator pulsar", "[weight=1][part=CellBoard]") {
  constexpr std::size_t width = 17;
  constexpr std::size_t height = 17;
  constexpr std::array<std::array<bool, width>, height> expected_first_state{
      {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0},
       {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
       {0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};
  constexpr std::array<std::array<bool, width>, height> expected_second_state{
      {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0},
       {0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0},
       {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
       {0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0},
       {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0},
       {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};
  constexpr std::array<std::array<bool, width>, height> expected_third_state{
      {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

  cell_board::CellBoard test_board(width, height);

  for (auto x_pos = 0; x_pos < width; x_pos++) {
    for (auto y_pos = 0; y_pos < height; y_pos++) {
      if (expected_first_state[y_pos][x_pos]) {
        test_board.insert_point(x_pos, y_pos);
      }
    }
  }

  for (size_t generation = 0; generation < REPEAT_TIMES; generation++) {
    CHECK(test_board.get_generation_number() == generation);

    if (generation % 3 == 0) {
      CHECK(check_board_state(test_board, expected_first_state));
    } else if (generation % 3 == 1) {
      CHECK(check_board_state(test_board, expected_second_state));
    } else {
      CHECK(check_board_state(test_board, expected_third_state));
    }
    test_board.next_state();
  }
}
