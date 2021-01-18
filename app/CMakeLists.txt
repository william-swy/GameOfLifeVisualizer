## Qt GUI application build

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(APP_NAME game_of_life)
set(APP_ICON_RESOURCE ./game_of_life_app.qrc)

# Find Qt specific packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Xml REQUIRED)

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

target_link_libraries(${APP_NAME}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Xml
        gameboard_lib)