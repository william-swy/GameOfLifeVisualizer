#pragma once

#include <QGraphicsScene>
#include <QWidget>

#include "board_model.h"

class BoardScene : public QGraphicsScene {
  Q_OBJECT
public:
  BoardScene(quint32 cell_width, QWidget* parent = nullptr);

  void link_board(const BoardModel* model) noexcept;

private:
  qint64 board_start_x_pos;  // X coordinate of board corner
  qint64 board_start_y_pos;  // Y coordinate of board corner
  quint32 num_cells_width;   // Number of cells that fit width-wise
  quint32 num_cells_height;  // Number of cells that fit height-wise
  quint32 cell_width;        // Width of cell (square) in pixels
};