#pragma once

#include <QMainWindow>
#include <QWidget>

#include "view.h"
#include "board_scene.h"
#include "board_model.h"
#include "main_menu.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);

private:
  View* view;
  BoardScene* scene;
  BoardModel* model;
  MainMenu* menu;
};