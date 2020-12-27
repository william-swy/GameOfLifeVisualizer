cmake_minimum_required(VERSION 3.5)

project(GameOfLifeLogic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES main.cpp gameboard.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# ENSURE THERE IS NO IN SOURCE BUILD
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


add_executable(${PROJECT_NAME} ${SOURCES})

