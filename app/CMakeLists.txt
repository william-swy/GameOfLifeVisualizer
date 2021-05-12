## Qt GUI application build

set(APP_NAME game_of_life)
set(APP_ICON_RESOURCE ./game_of_life_app.qrc)

# Find Qt specific packages
find_package(Qt5 COMPONENTS Widgets Xml REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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
        Qt5::Widgets
        Qt5::Xml
        gameboard_lib)