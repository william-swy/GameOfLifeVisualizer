# Test suite for cell board

include(CTest)

find_package(Catch2 REQUIRED)

set(TEST_NAME test_cell_board)
set(TEST_SOURCES cell_board_test.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_NAME} PRIVATE cell_board Catch2::Catch2)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
