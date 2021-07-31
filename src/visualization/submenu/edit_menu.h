#pragma once

#include <QMenu>
#include <QWidget>
#include <QString>
#include <QAction>

class EditMenu : public QMenu {
  Q_OBJECT
public:
  EditMenu(const QString& title, QWidget* parent = nullptr);

  QAction* take_snap_shot;
  QAction* start_recording;
  QAction* end_recording;
};