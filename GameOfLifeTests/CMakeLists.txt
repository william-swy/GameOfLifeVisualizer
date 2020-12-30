# Test suite for gameBoard


find_package(Catch2 REQUIRED)

set(TEST_NAME testGameBoard)
set(SOURCES tst_gameboardtest.cpp)

add_executable(${TEST_NAME} ${SOURCES})
target_include_directories(${TEST_NAME} PRIVATE ../GameOfLifeLogic)
target_link_libraries(${TEST_NAME} PRIVATE gameboard_library Catch2::Catch2)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})