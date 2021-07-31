#pragma once

#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QVector>
#include <QWidget>

class RecordingViewer : public QDialog {
  Q_OBJECT
public:
  explicit RecordingViewer(QWidget* parent = nullptr);

  void add_image(const QPixmap& img) noexcept;

  void discard_previous_frames() noexcept;

  void display_results() noexcept;

private:
  QLabel* img_label;
  QScrollArea* scroll_area;
  QPushButton* discard;
  QPushButton* save_to_gif;
  QPushButton* next;
  QPushButton* previous;
  QVector<QImage> images;
  quint64 curr_idx{0};
  QLabel* total_images;

  void connect_signal_slots() noexcept;

  void configure_next_previous() noexcept;

  void render_current_idx_img() noexcept;

private slots:
  // Precondition is that this can only be called with curr_idx is less than the last index of
  // images.
  void show_next_image();

  // Precondition is that this can only be called when curr_idx is greater than zero.
  void show_previous_image();

  void save_images_to_gif();
};