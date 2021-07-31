#include "main_menu.h"

#include <QMenu>
#include <QMenuBar>
#include <QRect>
#include <QString>
#include <QWidget>

#include "board_model.h"
#include "submenu/edit_menu.h"
#include "submenu/file_menu.h"
#include "submenu/run_menu.h"
#include "submenu/view_menu.h"
#include "view.h"

MainMenu::MainMenu(quint64 width, quint64 height, QWidget* parent)
    : QMenuBar(parent),
      file_menu(new FileMenu(QMenu::tr("File"), this)),
      edit_menu(new EditMenu(QMenu::tr("Edit"), this)),
      view_menu(new ViewMenu(QMenu::tr("View"), this)),
      run_menu(new RunMenu(QMenu::tr("Run"), this)) {
  setGeometry(QRect(0, 0, width, height));
  add_tab_actions();
}

void MainMenu::link_board(const BoardModel* model) noexcept {
  run_menu->link_board(model);
  edit_menu->link_board(model);
}

void MainMenu::link_view(const View* view) noexcept {
  view_menu->link_view(view);
  edit_menu->link_view(view);
}

void MainMenu::add_tab_actions() {
  // add dropdown menu tab actions
  addAction(file_menu->menuAction());
  addAction(edit_menu->menuAction());
  addAction(view_menu->menuAction());
  addAction(run_menu->menuAction());
}
