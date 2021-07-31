#include "edit_menu.h"

#include <QAction>
#include <QImage>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "../popup/recording_viewer.h"
#include "../popup/screenshot_viewer.h"

EditMenu::EditMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      take_snap_shot(new QAction(QIcon(":/Images/Icons/screenshot.ico"), QAction::tr("Take Snip"))),
      start_recording(new QAction(QAction::tr("Start Recording"))),
      end_recording(new QAction(QAction::tr("End Recording"))),
      screenshot_viewer(new ScreenshotViewer(this)),
      recording_viewer(new RecordingViewer(this)) {
  addAction(take_snap_shot);
  addAction(start_recording);
  addAction(end_recording);
  connect(take_snap_shot, &QAction::triggered, this, [=]() { emit request_screen_shot(); });
  connect(start_recording, &QAction::triggered, this, &EditMenu::start_board_recording);
  connect(end_recording, &QAction::triggered, this, &EditMenu::end_board_recording);
  end_recording->setEnabled(false);  // Only clickable after start recording.
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

void EditMenu::start_board_recording() {
  is_recording = true;
  recording_viewer->discard_previous_frames();  // Discard previous results
  emit request_screen_shot();  // Capture the first frame as it will not otherwise be captured
  take_snap_shot->setEnabled(false);
  start_recording->setEnabled(false);
  end_recording->setEnabled(true);
}

void EditMenu::end_board_recording() {
  is_recording = false;
  take_snap_shot->setEnabled(true);
  start_recording->setEnabled(true);
  recording_viewer->display_results();
  end_recording->setEnabled(false);
}

void EditMenu::receive_screen_shot(const QPixmap& img) {
  if (is_recording) {
    recording_viewer->add_image(img);
  } else {
    screenshot_viewer->set_display_image(img);
    screenshot_viewer->open();
  }
}
