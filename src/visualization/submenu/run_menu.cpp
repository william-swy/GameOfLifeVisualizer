#include "run_menu.h"

#include <QAction>
#include <QMenu>
#include <QTimer>
#include <QWidget>

#include "../board_model.h"

RunMenu::RunMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      step(new QAction(QIcon(":/Images/Icons/arrow.ico"), QAction::tr("Step Forward"))),
      run(new QAction(QIcon(":/Images/Icons/play.ico"), QAction::tr("Run"))),
      stop(new QAction(QIcon(":/Images/Icons/stop.ico"), QAction::tr("Stop"))),
      increase_speed(new QAction(QAction::tr("Increase Speed"))),
      decrease_speed(new QAction(QAction::tr("Decrease Speed"))),
      reset_speed(new QAction(QAction::tr("Reset Speed"))),
      reset_board(new QAction(QAction::tr("Reset Board"))),
      timer(new QTimer(this)),
      curr_delay_time(default_delay_time) {
  addAction(step);
  addAction(run);
  addAction(stop);
  addAction(increase_speed);
  addAction(decrease_speed);
  addAction(reset_speed);
  addAction(reset_board);
  connect(run, SIGNAL(triggered()), this, SLOT(run_automaton()));
  connect(stop, SIGNAL(triggered()), this, SLOT(stop_automaton()));
  stop->setEnabled(false);
  connect(increase_speed, SIGNAL(triggered()), this, SLOT(increase_run_speed()));
  connect(decrease_speed, SIGNAL(triggered()), this, SLOT(decrease_run_speed()));
  connect(reset_speed, SIGNAL(triggered()), this, SLOT(reset_run_speed()));
}

void RunMenu::link_board(const BoardModel* model) noexcept {
  connect(step, SIGNAL(triggered()), model, SLOT(next_state()));
  connect(reset_board, SIGNAL(triggered()), model, SLOT(reset_board()));
  connect(timer, SIGNAL(timeout()), model, SLOT(next_state()));
}

void RunMenu::run_automaton() {
  step->setEnabled(false);
  run->setEnabled(false);
  stop->setEnabled(true);
  increase_speed->setEnabled(false);
  decrease_speed->setEnabled(false);
  reset_speed->setEnabled(false);
  reset_board->setEnabled(false);

  timer->start(curr_delay_time);
}

void RunMenu::change_speed_option() noexcept {
  if (curr_delay_time == min_delay_time) {
    increase_speed->setEnabled(false);
    decrease_speed->setEnabled(true);
  } else if (curr_delay_time == max_delay_time) {
    increase_speed->setEnabled(true);
    decrease_speed->setEnabled(false);
  } else {
    increase_speed->setEnabled(true);
    decrease_speed->setEnabled(true);
  }
}

void RunMenu::stop_automaton() {
  timer->stop();
  step->setEnabled(true);
  run->setEnabled(true);
  stop->setEnabled(false);
  increase_speed->setEnabled(true);
  decrease_speed->setEnabled(true);
  reset_speed->setEnabled(true);
  reset_board->setEnabled(true);
}

void RunMenu::increase_run_speed() {
  if (curr_delay_time > min_delay_time) {
    curr_delay_time /= time_scaling_factor;
    change_speed_option();
  }
}

void RunMenu::decrease_run_speed() {
  if (curr_delay_time < max_delay_time) {
    curr_delay_time *= time_scaling_factor;
    change_speed_option();
  }
}

void RunMenu::reset_run_speed() {
  curr_delay_time = default_delay_time;
  change_speed_option();
}

void RunMenu::configure_shortcuts() {
#if QT_CONFIG(shortcut)
  step->setShortcut(QMenu::tr("Ctrl+N"));
  run->setShortcut(QMenu::tr("Ctrl+Shift+R"));
  stop->setShortcut(QMenu::tr("Ctrl+Shift+S"));
#endif
}