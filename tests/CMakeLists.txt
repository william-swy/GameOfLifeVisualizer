# Test suites

find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

# Compiles a static lib from the Catch2 header to shorten the entire build process
add_library(catch_main STATIC "test_main.cpp")
target_link_libraries(catch_main PUBLIC Catch2::Catch2)
target_link_libraries(catch_main PRIVATE project_options project_warnings)

# Test suite
add_executable(
  test_suite
  "gif_generator_tests/gif_writer_test.cpp"
  "gif_generator_tests/ppn_test.cpp"
  "gif_generator_tests/RGB_pixel_test.cpp"
  "gif_generator_tests/colour_pallete_test.cpp"
  "cell_board_tests/cell_board_test.cpp"
)
target_link_libraries(test_suite PRIVATE cell_board gif_generator Catch2::Catch2 project_options project_warnings)


catch_discover_tests(
  test_suite
  TEST_PREFIX
  "unittests."
  REPORTER
  xml
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)
