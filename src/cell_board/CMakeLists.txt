# Build for logic and representation library

set(LIB_NAME cell_board)
set(CELL_BOARD_TARGET_HEADERS cell_board.h)
set(CELL_BOARD_TARGET_SOURCES cell_board.cpp)

add_library(${LIB_NAME} ${CELL_BOARD_TARGET_SOURCES} ${CELL_BOARD_TARGET_HEADERS})
# Give access to header
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(${LIB_NAME} PRIVATE -Wall -Wpedantic -Wextra -Werror)
elseif(MSVC)
  target_compile_options(${LIB_NAME} PRIVATE /Wall /W3 /wd5045)
endif()

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)
