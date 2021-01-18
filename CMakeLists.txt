### works with 3.5
cmake_minimum_required(VERSION 3.5...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.19)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

### Requires out-of-source build
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory. Please make a build directory and rebuild. Feel free
    to remove CMakeCache.txt and CMakeFiles.")
endif ()

project(GameOfLifeApp
        VERSION 1.0
        DESCRIPTION  "Conway's Game of Life Visualizer"
        LANGUAGES CXX)

### Do only if this is the main project, not a subproject
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # include tests
    include(CTest)

    # library to handle game board
    add_subdirectory(src)

    # executable GUI code
    add_subdirectory(app)

    # tests
    add_subdirectory(tests)
endif()

