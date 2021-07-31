#include "edit_menu.h"

#include <QMenu>
#include <QWidget>
#include <QString>
#include <QAction>

EditMenu::EditMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      take_snap_shot(new QAction(QIcon(":/Images/Icons/screenshot.ico"), QAction::tr("Take Snip"))),
      start_recording(new QAction(QAction::tr("Start Recording"))),
      end_recording(new QAction(QAction::tr("End Recording"))) {
  addAction(take_snap_shot);
  addAction(start_recording);
  addAction(end_recording);
}