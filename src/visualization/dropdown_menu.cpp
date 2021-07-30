#include "dropdown_menu.h"

#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "board_model.h"
#include "view.h"

FileMenu::FileMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      save(new QAction(QIcon(":/Images/Icons/save.ico"), QAction::tr("Save"))),
      settings(new QAction(QIcon(":/Images/Icons/settings.ico"), QAction::tr("Settings"))),
      quit(new QAction(QAction::tr("Quit"))) {
  addAction(save);
  addAction(settings);
  addAction(quit);
}

EditMenu::EditMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      take_snap_shot(new QAction(QIcon(":/Images/Icons/screenshot.ico"), QAction::tr("Take Snip"))),
      start_recording(new QAction(QAction::tr("Start Recording"))),
      end_recording(new QAction(QAction::tr("End Recording"))) {
  addAction(take_snap_shot);
  addAction(start_recording);
  addAction(end_recording);
}

ViewMenu::ViewMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      reset_zoom(new QAction(QAction::tr("Reset Zoom"))),
      view_result(new QAction(QIcon(":/Images/Icons/image.ico"), QAction::tr("View Result"))) {
  addAction(reset_zoom);
  addAction(view_result);
}

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

void ViewMenu::link_view(const View* view) noexcept {
  connect(reset_zoom, SIGNAL(triggered()), view, SLOT(reset_zoom()));
}
