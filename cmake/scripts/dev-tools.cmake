# Get all source files
file(GLOB_RECURSE ALL_CXX_SOURCE_FILES src/*.cpp src/*.h tests/*.h tests/*.cpp)

set(ALL_CMAKE_FILES cmake/scripts/dev-tools.cmake tests/CMakeLists.txt src/CMakeLists.txt
                    src/visualization/CMakeLists.txt src/cell_board/CMakeLists.txt CMakeLists.txt
)
foreach(SOURCE_FILE ${ALL_CMAKE_FILES})
  list(APPEND ALL_CMAKE_SOURCE_FILES ${CMAKE_SOURCE_DIR}/${SOURCE_FILE})
endforeach()

# Adding clang-format target
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  message(STATUS "clang-format found. TARGET clang-format available.")
  add_custom_target(clang-format COMMAND clang-format -i -style=file ${ALL_CXX_SOURCE_FILES})
else()
  message(STATUS "clang-format not found. TARGET clang-format not available.")
endif()

# Adding clang-tidy target
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  message(STATUS "clang-tidy found. TARGET clang-tidy available.")
  add_custom_target(
    clang-tidy COMMAND clang-tidy ${ALL_CXX_SOURCE_FILES} -format-style=file -- -std=c++20
  )
else()
  message(STATUS "clang-tidy not found. TARGET clang-tidy not available.")
endif()

# Adding cmake-format target
find_program(CMAKE_FORMAT "cmake-format")
if(CMAKE_FORMAT)
  message(STATUS "cmake-format found. TARGET cmake-format available.")
  add_custom_target(
    cmake-format COMMAND cmake-format ${ALL_CMAKE_SOURCE_FILES} -i -c
                         ${CMAKE_SOURCE_DIR}/.cmake-format
  )
else()
  message(STATUS "cmake-format not found. TARGET cmake-format not available.")
endif()
