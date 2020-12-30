### Qt GUI application build


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(APP_NAME GameOfLife)

set(APP_ICON_RESOURCE ./GameOfLifeApp.qrc)

# Find Qt specific packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


set(HEADERS
        board_ui.h
        cell.h
        displaywindow.h
        view.h)

set(SOURCES
        cell.cpp
        displaywindow.cpp
        main.cpp
        view.cpp)

add_executable(${APP_NAME}
        ${SOURCES}
        ${HEADERS}
        ${APP_ICON_RESOURCE}
        )

target_include_directories(${APP_NAME} PRIVATE ../GameOfLifeLogic)
target_link_libraries(${APP_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets gameboard_library)
