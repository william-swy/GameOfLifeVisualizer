#include "edit_menu.h"

#include <QAction>
#include <QImage>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "../popup/screenshot_viewer.h"

EditMenu::EditMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      take_snap_shot(new QAction(QIcon(":/Images/Icons/screenshot.ico"), QAction::tr("Take Snip"))),
      start_recording(new QAction(QAction::tr("Start Recording"))),
      end_recording(new QAction(QAction::tr("End Recording"))),
      screenshot_viewer(new ScreenshotViewer(this)) {
  addAction(take_snap_shot);
  addAction(start_recording);
  addAction(end_recording);
  connect(take_snap_shot, &QAction::triggered, this, [=]() {
    emit request_screen_shot();
  });
}

void EditMenu::link_board(const BoardModel* model) noexcept {
  connect(model, &BoardModel::board_changed, this, [=](const BoardModel*) {
    if (is_recording) emit request_screen_shot();
  });
}

void EditMenu::link_view(const View* view) noexcept {
  connect(this, &EditMenu::request_screen_shot, view, &View::receive_screenshot_request);
  connect(view, &View::send_screenshot, this, &EditMenu::receive_screen_shot);
}

void EditMenu::receive_screen_shot(const QPixmap& img) {
  if (is_recording) {
  } else {
    //auto h = img.height();
    //auto w = img.width();
    screenshot_viewer->set_display_image(img);
    screenshot_viewer->exec();
  }
}
