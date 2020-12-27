TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

CONFIG += c++11

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
# set by Qt Creator wizard
isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="/usr/include"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

SOURCES +=\
    ../GameOfLifeLogic/gameboard.cpp \
    main.cpp \
    tst_gameboardtest.cpp

HEADERS += \
    ../GameOfLifeLogic/gameboard.h
