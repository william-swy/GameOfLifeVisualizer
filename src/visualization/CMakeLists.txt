# Qt GUI application build

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
  board_model.cpp
  board_model.h
  board_scene.cpp
  board_scene.h
  board_status.cpp
  board_status.h
  cell.cpp
  cell.h
  GameOfLifeApp.qrc
  main.cpp
  main_menu.cpp
  main_menu.h
  main_window.cpp
  main_window.h
  popup/recording_viewer.cpp
  popup/recording_viewer.h
  popup/screenshot_viewer.cpp
  popup/screenshot_viewer.h
  submenu/edit_menu.cpp
  submenu/edit_menu.h
  submenu/file_menu.cpp
  submenu/file_menu.h
  submenu/run_menu.cpp
  submenu/run_menu.h
  submenu/view_menu.cpp
  submenu/view_menu.h
  view.cpp
  view.h
)

target_link_libraries(${APP_NAME} PUBLIC Qt5::Widgets cell_board gif_generator project_warnings
  project_options)
target_compile_features(${APP_NAME} PUBLIC cxx_nullptr cxx_lambdas)
