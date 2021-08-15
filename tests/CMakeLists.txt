# Test suites

find_package(Catch2 REQUIRED)

# Test suite
add_executable(
  test_suite cell_board_tests/cell_board_test.cpp gif_generator_tests/gif_writer_test.cpp
             gif_generator_tests/image_formats_test.cpp test_main.cpp
)
target_link_libraries(test_suite PRIVATE cell_board gif_generator Catch2::Catch2)
target_compile_features(test_suite PRIVATE cxx_std_20)

include(CTest)
add_test(test_suite test_suite)
