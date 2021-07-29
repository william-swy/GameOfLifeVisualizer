#pragma once

#include <QAction>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "board_model.h"

class FileMenu : public QMenu {
  Q_OBJECT
public:
  FileMenu(const QString& title, QWidget* parent = nullptr);

private:
  QAction* save;
  QAction* settings;
  QAction* quit;
};

class EditMenu : public QMenu {
  Q_OBJECT
public:
  EditMenu(const QString& title, QWidget* parent = nullptr);

  QAction* take_snap_shot;
  QAction* start_recording;
  QAction* end_recording;
};

class ViewMenu : public QMenu {
  Q_OBJECT
public:
  ViewMenu(const QString& title, QWidget* parent = nullptr);

  QAction* reset_zoom;
  QAction* view_result;
};

class RunMenu : public QMenu {
  Q_OBJECT
public:
  RunMenu(const QString& title, QWidget* parent = nullptr);

  void link_board(const BoardModel* model) noexcept;

  QAction* step;
  QAction* run;
  QAction* stop;
  QAction* increase_speed;
  QAction* decrease_speed;
  QAction* reset_speed;
  QAction* reset_board;
};