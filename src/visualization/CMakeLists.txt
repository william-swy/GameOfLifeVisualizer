# Qt GUI application build

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(APP_NAME game_of_life)

set(APP_ICON_RESOURCE ./GameOfLifeApp.qrc)

# Find Qt specific packages
find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED
)

add_executable(${APP_NAME} main_view.h main.cpp ${APP_ICON_RESOURCE})

target_link_libraries(${APP_NAME} PRIVATE Qt5::Widgets cell_board)
