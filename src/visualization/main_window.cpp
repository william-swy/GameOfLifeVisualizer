#include "main_window.h"

#include <QIcon>
#include <QMainWindow>
#include <QWidget>

#include "board_model.h"
#include "board_scene.h"
#include "main_menu.h"
#include "view.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      view(new View(this)),
      scene(new BoardScene(10, this)),
      model(new BoardModel(200, 200, this)),
      menu(new MainMenu(800, 25)),
      status_bar(new BoardStatus(this)) {
  setCentralWidget(view);
  view->setScene(scene);
  scene->link_board(model);
  scene->link_status_bar(status_bar);
  menu->link_board(model);
  status_bar->link_board(model);
  setMenuBar(menu);
  setStatusBar(status_bar);
  setWindowTitle(QMainWindow::tr("Game Of Life"));
  setWindowIcon(QIcon(":/Images/Icons/pulsar.ico"));
  showMaximized();
}