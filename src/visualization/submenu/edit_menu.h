#pragma once

#include <QAction>
#include <QImage>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "../board_model.h"
#include "../view.h"
#include "../popup/screenshot_viewer.h"

class EditMenu : public QMenu {
  Q_OBJECT
public:
  EditMenu(const QString& title, QWidget* parent = nullptr);

  void link_board(const BoardModel* model) noexcept;

  void link_view(const View* view) noexcept;

  QAction* take_snap_shot;
  QAction* start_recording;
  QAction* end_recording;

  ScreenshotViewer* screenshot_viewer;

signals:
  void request_screen_shot();

private slots:
  void receive_screen_shot(const QPixmap& img);

private:
  bool is_recording{false};
};