## Test suite for gameBoard

# Catch2 as the unit testing framework.

find_package(Catch2 REQUIRED)

set(TEST_NAME test_game_board)
set(SOURCES gameboard_test.cpp)

add_executable(${TEST_NAME} ${SOURCES})
target_link_libraries(${TEST_NAME} PRIVATE gameboard_lib Catch2::Catch2)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})