#include "recording_viewer.h"

#include <QDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "gif_generator.h"

RecordingViewer::RecordingViewer(QWidget* parent)
    : QDialog(parent),
      img_label(new QLabel(this)),
      scroll_area(new QScrollArea(this)),
      discard(new QPushButton(tr("Discard"), this)),
      save_to_gif(new QPushButton(tr("Save to GIF"), this)),
      next(new QPushButton(tr("Next frame"), this)),
      previous(new QPushButton(tr("Previous frame"), this)),
      total_images(new QLabel(this)) {
  setWindowTitle(QDialog::tr("Screen Recording Result"));

  img_label->setBackgroundRole(QPalette::Base);
  img_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  img_label->setScaledContents(true);

  scroll_area->setBackgroundRole(QPalette::Dark);
  scroll_area->setWidget(img_label);

  auto main_layout = new QVBoxLayout(this);
  auto button_layout = new QHBoxLayout();
  button_layout->addWidget(discard);
  button_layout->addWidget(previous);
  button_layout->addStretch(250);
  button_layout->addWidget(total_images);
  button_layout->addStretch(250);
  button_layout->addWidget(next);
  button_layout->addWidget(save_to_gif);

  main_layout->addWidget(scroll_area);
  main_layout->addLayout(button_layout);

  connect_signal_slots();
}

void RecordingViewer::add_image(const QPixmap& img) noexcept { images.push_back(img.toImage()); }

void RecordingViewer::discard_previous_frames() noexcept { images.clear(); }

void RecordingViewer::display_results() noexcept {
  if (!images.empty()) {
    const auto img = QPixmap::fromImage(images[0]);
    resize(img.size());
    setWindowIcon(QIcon(img));
    curr_idx = 0;
    render_current_idx_img();
  }
  open();
}

void RecordingViewer::connect_signal_slots() noexcept {
  connect(discard, &QPushButton::clicked, this, &RecordingViewer::reject);
  connect(save_to_gif, &QPushButton::clicked, this, &RecordingViewer::save_images_to_gif);
  connect(previous, &QPushButton::clicked, this, &RecordingViewer::show_previous_image);
  connect(next, &QPushButton::clicked, this, &RecordingViewer::show_next_image);
}

void RecordingViewer::configure_next_previous() noexcept {
  if (images.size() <= 1) {
    // Disable both if there is only one image
    previous->setEnabled(false);
    next->setEnabled(false);
  } else {
    if (curr_idx == 0) {
      previous->setEnabled(false);
      next->setEnabled(true);
    } else if (curr_idx == (images.size() - 1)) {
      previous->setEnabled(true);
      next->setEnabled(false);
    } else {
      previous->setEnabled(true);
      next->setEnabled(true);
    }
  }
}

void RecordingViewer::render_current_idx_img() noexcept {
  const auto img = QPixmap::fromImage(images[curr_idx]);
  img_label->setPixmap(img);
  img_label->resize(img.size());
  configure_next_previous();
  total_images->setText(QString::number(curr_idx + 1) + " / " + QString::number(images.size()));
}

void RecordingViewer::show_next_image() {
  curr_idx++;
  render_current_idx_img();
}

void RecordingViewer::show_previous_image() {
  curr_idx--;
  render_current_idx_img();
}

void RecordingViewer::save_images_to_gif() {
  const auto save_file
      = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Images (*.gif)"));
  if (!save_file.isEmpty()) {
    std::vector<gif::image::ImageFrame> converted_imgs;
    converted_imgs.resize(images.size());  // Allocate space to place elements
    std::transform(images.begin(), images.end(), converted_imgs.begin(), [](const QImage& img) {
      // Convert to 8 bit representation of RGB with no alpha
      const auto transformed_img = img.convertToFormat(QImage::Format_RGB888);
      // std::cout << transformed_img.depth() << std::endl;
      // std::cout << transformed_img.hasAlphaChannel() << std::endl;
      // std::cout << transformed_img.format() << std::endl;
      // std::cout << transformed_img.width() << std::endl;
      // std::cout << transformed_img.height() << std::endl;
      // std::cout << transformed_img.sizeInBytes() << std::endl;
      std::cout << std::hex << transformed_img.constBits()[0] << std::endl;
      return gif::image::ImageFrame{
          transformed_img.constBits(),
          static_cast<std::size_t>(transformed_img.sizeInBytes()),
          static_cast<unsigned short>(transformed_img.width()),
          static_cast<unsigned short>(transformed_img.height()),
      };
    });

    // gif::write_to_gif(converted_imgs, save_file.toStdString());
    accept();
  }
}
