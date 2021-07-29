#include "dropdown_menu.h"

#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QString>
#include <QWidget>

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
      reset_board(new QAction(QAction::tr("Reset Board"))) {
  addAction(step);
  addAction(run);
  addAction(stop);
  addAction(increase_speed);
  addAction(decrease_speed);
  addAction(reset_speed);
  addAction(reset_board);
}

void RunMenu::link_board(const BoardModel* model) noexcept {
  connect(step, SIGNAL(triggered()), model, SLOT(next_state()));
}
