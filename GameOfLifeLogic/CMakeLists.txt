### Build for gameBoard logic and representation library


set(BOARD_LIB gameboard_library)
set(HEADERS gameboard.h)
set(SOURCES gameboard.cpp)

add_library(${BOARD_LIB} ${SOURCES} ${HEADERS})

target_compile_features(${BOARD_LIB} PUBLIC cxx_std_11)
