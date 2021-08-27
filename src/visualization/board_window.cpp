#include "board_window.h"

#include <QMainWindow>
#include <QWidget>

visualization::BoardWindow::BoardWindow(QWidget* parent)
    : QMainWindow(parent),
      cell_board(new CellBoardModel(BOARD_WIDTH, BOARD_HEIGHT, this)),
      view(new BoardView(this)),
      scene(new BoardScene(BOARD_WIDTH, BOARD_HEIGHT, this)) {
  showMaximized();
  setCentralWidget(view);
  view->setScene(scene);
  scene->setup_scene(*cell_board);
}
