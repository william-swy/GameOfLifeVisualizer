#include "cell_board_model.h"

#include <QObject>

visualization::CellBoardModel::CellBoardModel(quint64 board_width, quint64 board_height,
                                              QObject* parent)
    : QObject(parent),
      board(static_cast<std::size_t>(board_width), static_cast<std::size_t>(board_height)) {}

void visualization::CellBoardModel::next_state() noexcept {
  board.next_state();
  emit signal_board_update(*this);
}

bool visualization::CellBoardModel::get_cell(quint64 x_pos, quint64 y_pos) const {
  return board.get_cell(static_cast<std::size_t>(x_pos), static_cast<std::size_t>(y_pos));
}

void visualization::CellBoardModel::receive_cell_update(quint64 x_pos, quint64 y_pos) {
  board.insert_point(static_cast<std::size_t>(y_pos), static_cast<std::size_t>(y_pos));
}