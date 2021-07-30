#pragma once

#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QWidget>

#include "board_model.h"
#include "dropdown_menu.h"

class MainMenu : public QMenuBar {
  Q_OBJECT
public:
  MainMenu(quint64 width, quint64 height, QWidget* parent = nullptr);

  void link_board(const BoardModel* model);

private:
  void add_tab_actions();

  FileMenu* file_menu;
  EditMenu* edit_menu;
  ViewMenu* view_menu;
  RunMenu* run_menu;
};