QT += core gui \
    widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += ../GameOfLifeLogic

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../GameOfLifeLogic/gameboard.cpp \
    displaywindow.cpp \
    cell.cpp \
    view.cpp \
    main.cpp

HEADERS += \
    ../GameOfLifeLogic/gameboard.h \
    displaywindow.h \
    cell.h \
    view.h \
    board_ui.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    GameOfLifeApp.qrc
