#pragma once

#include <QLabel>
#include <QStatusBar>
#include <QWidget>

#include "board_model.h"

class BoardStatus : public QStatusBar {
public:
  explicit BoardStatus(QWidget* parent = nullptr);

  void link_board(const BoardModel* model) noexcept;

private:
  QLabel* gen_num_display;
  QLabel* coordinate_display;

public slots:
  void update_gen_num(const BoardModel* model);

  void set_coordinate(quint64 x_pos, quint64 y_pos);

  void remove_coordinate();
};