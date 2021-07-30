#include "board_model.h"

#include <QObject>

BoardModel::BoardModel(quint64 board_width, quint64 board_height, QObject* parent)
    : QObject(parent),
      board(static_cast<std::size_t>(board_width), static_cast<std::size_t>(board_height)),
      width(board_width),
      height(board_height) {}

void BoardModel::next_state() noexcept {
  board.next_state();
  emit board_changed(this);
}

bool BoardModel::get_cell(quint64 x_pos, quint64 y_pos) const {
  return board.get_cell(static_cast<std::size_t>(x_pos), static_cast<std::size_t>(y_pos));
}

quint64 BoardModel::get_generation_number() const noexcept {
  return static_cast<quint64>(board.get_generation_number());
}

void BoardModel::reset_board() {
  board = cell_board::CellBoard(static_cast<std::size_t>(width), static_cast<std::size_t>(height));
  emit board_changed(this);
}

void BoardModel::update_board(quint64 x_pos, quint64 y_pos) {
  board.insert_point(static_cast<std::size_t>(x_pos), static_cast<std::size_t>(y_pos));
}
