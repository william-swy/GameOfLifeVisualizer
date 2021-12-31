# Build for logic and representation library

set(LIB_NAME cell_board)
set(CELL_BOARD_TARGET_HEADERS cell_board.h)
set(CELL_BOARD_TARGET_SOURCES cell_board.cpp)

add_library(${LIB_NAME} STATIC ${CELL_BOARD_TARGET_SOURCES} ${CELL_BOARD_TARGET_HEADERS})
# Give access to header
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIB_NAME} PRIVATE project_options project_warnings)
