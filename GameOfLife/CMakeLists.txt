### Qt GUI application build


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(APP_NAME GameOfLife)

set(INCLUDES ../GameOfLifeLogic)
set(APP_ICON_RESOURCE ./GameOfLifeApp.qrc)

# Find Qt specific packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


set(HEADERS
        board_ui.h
        cell.h
        colortab.h
        displaywindow.h
        screenshotdialog.h
        screenshottab.h
        settingsdialog.h
        view.h)

set(SOURCES
        cell.cpp
        colortab.cpp
        displaywindow.cpp
        main.cpp
        screenshotdialog.cpp
        screenshottab.cpp
        settingsdialog.cpp
        view.cpp)

add_executable(${APP_NAME}
        ${SOURCES}
        ${HEADERS}
        ${APP_ICON_RESOURCE})

target_include_directories(${APP_NAME} PRIVATE ${INCLUDES})
target_link_libraries(${APP_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets gameboard_library)
