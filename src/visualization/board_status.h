#pragma once

#include <QStatusBar>
#include <QLabel>
#include <QWidget>

class BoardStatus : public QStatusBar {
public:
  explicit BoardStatus(QWidget* parent = nullptr);

private:
  QLabel* gen_num_display;
  QLabel* coordinate_display;

  private slots:
  void update_gen_num();

  void set_coordinate(quint64 x_pos, quint64 y_pos);

  void remove_coordinate();
};