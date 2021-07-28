#pragma once

#include <QObject>

#include "cell_board.h"

class BoardModel : public QObject {
  Q_OBJECT
public:
  BoardModel(quint64 board_width, quint64 board_height, QObject* parent = nullptr);

  void next_state() noexcept;

  bool get_cell(quint64 x_pos, quint64 y_pos) const;

  quint64 width;

  quint64 height;

private:
  cell_board::CellBoard board;
};