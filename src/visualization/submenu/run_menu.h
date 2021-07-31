#pragma once

#include <QAction>
#include <QMenu>
#include <QTimer>
#include <QWidget>

#include "../board_model.h"

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

  void configure_shortcuts();

private slots:
  void run_automaton();

  void stop_automaton();

  void increase_run_speed();

  void decrease_run_speed();

  void reset_run_speed();
};