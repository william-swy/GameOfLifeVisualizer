# Qt GUI application build

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(APP_NAME game_of_life)

# Find Qt specific packages
find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED
)

add_executable(
  ${APP_NAME}
  #board_ui.h
  board_model.h
  board_model.cpp
  board_scene.h
  board_scene.cpp
  cell.cpp
  cell.h
  #displaywindow.cpp
  #displaywindow.h
  GameOfLifeApp.qrc
  main.cpp
  main_menu.h
  main_menu.cpp
  main_window.h
  main_window.cpp
  view.cpp
  view.h
 dropdown_menu.h dropdown_menu.cpp)

target_link_libraries(${APP_NAME} PRIVATE Qt5::Widgets cell_board)
