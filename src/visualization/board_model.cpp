#include "board_model.h"

#include <QObject>

BoardModel::BoardModel(quint64 board_width, quint64 board_height, QObject* parent)
    : QObject(parent),
      board(static_cast<std::size_t>(board_width), static_cast<std::size_t>(board_height)),
      width(board_width),
      height(board_height) {}

void BoardModel::next_state() noexcept { board.next_state(); }

bool BoardModel::get_cell(quint64 x_pos, quint64 y_pos) const {
  return board.get_cell(static_cast<std::size_t>(x_pos), static_cast<std::size_t>(y_pos));
}
