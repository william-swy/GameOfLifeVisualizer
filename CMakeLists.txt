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

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed (uses vcpkg as a submodule)
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#if(UNIX) # Should trigger Linx or Apple ONLY
#    EXECUTE_PROCESS(${CMAKE_CURRENT_SOURCE_DIR}/extern//vcpkg/bootstrap-vcpkg.sh)
#else() # Should trigger MSVC or MINGW ONLY
#    EXECUTE_PROCESS(${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/bootstrap-vcpkg.bat)
#endif()

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

# Enable versioning
set(VCPKG_FEATURE_FLAGS versions)

project(GameOfLifeApp
        VERSION 1.0
        DESCRIPTION  "Conway's Game of Life Visualizer"
        LANGUAGES CXX)

### Do only if this is the main project, not a subproject
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 17)
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

