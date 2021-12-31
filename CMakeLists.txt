cmake_minimum_required(VERSION 3.17)

project(
  GameOfLifeVisualizer
  VERSION 0.1
  DESCRIPTION "Conway's Game of Life Visualizer"
  LANGUAGES CXX
)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

# Prohibit in source builds
include("cmake/PreventInSource.cmake")

# Include dev tools
include(cmake/scripts/dev-tools.cmake)

# "library" to set compile options i.e. the c++ standard
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# "library" to use the C language warnings specified in CompilerWarnings.cmake
include("${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake")
add_library(project_c_warnings INTERFACE)
set_project_warnings(project_c_warnings)


# Conan for dependency management
option(ENABLE_CONAN "Use Conan for dependency management" ON)
if(ENABLE_CONAN)
  include("${CMAKE_SOURCE_DIR}/cmake/Conan.cmake")
  run_conan()
endif()

add_subdirectory("src")

# Testing
option(ENABLE_TESTING "Enable Test Builds" ON)
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory("tests")
endif()
