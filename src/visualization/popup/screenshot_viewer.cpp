#include "screenshot_viewer.h"

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

ScreenshotViewer::ScreenshotViewer(QWidget* parent)
    : QDialog(parent),
      img_label(new QLabel(this)),
      scroll_area(new QScrollArea(this)),
      discard(new QPushButton(QPushButton::tr("Discard"), this)),
      save(new QPushButton(QPushButton::tr("Save Image"), this)) {
  setWindowTitle(QDialog::tr("Screenshot Result"));
  setWindowIcon(QIcon(":/Images/Icons/pulsar.ico"));

  img_label->setBackgroundRole(QPalette::Base);
  img_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  img_label->setScaledContents(true);

  scroll_area->setBackgroundRole(QPalette::Dark);
  scroll_area->setWidget(img_label);

  auto main_layout = new QVBoxLayout(this);
  auto button_layout = new QHBoxLayout();
  button_layout->addWidget(discard);
  button_layout->addSpacing(100);
  button_layout->addWidget(save);

  main_layout->addWidget(scroll_area);
  main_layout->addLayout(button_layout);
}

void ScreenshotViewer::set_display_image(const QPixmap& img) noexcept {
  img_label->setPixmap(img);
  img_label->resize(img.size());
  resize(img.size());
}
