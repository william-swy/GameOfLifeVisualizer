cmake_minimum_required(VERSION 3.5)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LOGIC_DIR ../GameOfLifeLogic)

# Find Qt specific packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${LOGIC_DIR})

# ENSURE THERE IS NO IN-SOURCE BUILD
MACRO(ENSURE_OUT_OF_SOURCE_BUILD MSG)
    STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
            "${CMAKE_BINARY_DIR}" insource)
    GET_FILENAME_COMPONENT(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
    STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
            "${PARENTDIR}" insourcesubdir)
    IF(insource OR insourcesubdir)
        MESSAGE(FATAL_ERROR "${MSG}")
    ENDIF(insource OR insourcesubdir)
ENDMACRO()

ENSURE_OUT_OF_SOURCE_BUILD( "${CMAKE_PROJECT_NAME} requires an out of source build.")

add_executable(${PROJECT_NAME}
        main.cpp
        displaywindow.cpp
        cell.cpp
        view.cpp
        ${LOGIC_DIR}/gameboard.cpp
        board_ui.h
        )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
