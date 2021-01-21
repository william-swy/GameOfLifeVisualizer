### Build for gameBoard logic and representation library

set(BOARD_LIB gameboard_lib)
set(SOURCES gameboard.cpp gameboard_out_of_bounds.cpp)

add_library(${BOARD_LIB} ${SOURCES})
target_include_directories(${BOARD_LIB} PUBLIC ../include)

target_compile_features(${BOARD_LIB} PUBLIC cxx_std_11)