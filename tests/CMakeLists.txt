## Test suite for gameBoard

# Catch2 as the unit testing framework.
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

set(TEST_NAME test_game_board)
set(SOURCES gameboard_test.cpp)

add_executable(${TEST_NAME} ${SOURCES})
target_link_libraries(${TEST_NAME} PRIVATE gameboard_lib Catch2::Catch2)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})