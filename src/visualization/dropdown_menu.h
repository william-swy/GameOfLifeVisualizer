#pragma once

#include <QAction>
#include <QMenu>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "board_model.h"
#include "view.h"

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

  void link_view(const View* view) noexcept;

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

private:
  QTimer* timer;
  quint64 default_delay_time{1000};
  quint64 curr_delay_time;
  quint64 min_delay_time{125};
  quint64 max_delay_time{8000};
  quint64 time_scaling_factor{2};

  void change_speed_option() noexcept;

private slots:
  void run_automaton();

  void stop_automaton();

  void increase_run_speed();

  void decrease_run_speed();

  void reset_run_speed();
};