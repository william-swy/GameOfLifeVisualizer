#include "main_window.h"

#include <QMainWindow>
#include <QWidget>

#include "board_model.h"
#include "board_scene.h"
#include "view.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      view(new View(this)),
      scene(new BoardScene(10, this)),
      model(new BoardModel(200, 200, this)) {
  showMaximized();
  setCentralWidget(view);
  view->setScene(scene);
  scene->link_board(model);
}