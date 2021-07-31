#pragma once

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <QPushButton>

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
};