### Build for gameBoard logic and representation library


set(LIB_NAME gameboard_library)
set(HEADERS gameboard.h)
set(SOURCES gameboard.cpp)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

target_compile_features(${LIB_NAME} PUBLIC cxx_std_11)

