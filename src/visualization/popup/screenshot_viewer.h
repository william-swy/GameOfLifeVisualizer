#pragma once

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>

class ScreenshotViewer : public QDialog {
  Q_OBJECT
public:
  explicit ScreenshotViewer(QWidget* parent = nullptr);

  void set_display_image(const QPixmap& img) noexcept;

private:
  QLabel* img_label;
  QScrollArea* scroll_area;
  QPushButton* discard;
  QPushButton* save;

  void connect_signal_slots() noexcept;

private slots:
  void save_displayed_img();
};