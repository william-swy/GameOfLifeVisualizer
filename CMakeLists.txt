cmake_minimum_required(VERSION 3.18)

project(
  GameOfLifeApp
  VERSION 1.0
  DESCRIPTION "Conway's Game of Life Visualizer"
  LANGUAGES CXX
)

# Prohibit in source builds
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# Do only if this is the main project, not a subproject
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory("src")

  add_subdirectory("tests")

  # Include dev tools
  include(cmake/scripts/dev-tools.cmake)
endif()
