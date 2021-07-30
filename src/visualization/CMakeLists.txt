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
  # board_ui.h
  board_model.cpp
  board_model.h
  board_scene.cpp
  board_scene.h
  board_status.cpp
  board_status.h
  cell.cpp
  cell.h
  # displaywindow.cpp
  # displaywindow.h
  dropdown_menu.cpp
  dropdown_menu.h
  GameOfLifeApp.qrc
  main.cpp
  main_menu.cpp
  main_menu.h
  main_window.cpp
  main_window.h
  view.cpp
  view.h
)

target_link_libraries(${APP_NAME} PRIVATE Qt5::Widgets cell_board)
