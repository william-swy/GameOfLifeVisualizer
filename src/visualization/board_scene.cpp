#include "board_scene.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QPointF>
#include <QWidget>

#include "board_model.h"
#include "board_status.h"
#include "cell.h"
#include "cell_board.h"

BoardScene::BoardScene(quint32 cell_width, QWidget* parent)
    : QGraphicsScene(parent),
      cell_width(cell_width),
      board_start_x_pos(0),
      board_start_y_pos(0),
      num_cells_width(0),
      num_cells_height(0) {}

void BoardScene::link_board(const BoardModel* model) noexcept {
  // Remove existing items if any
  for each (const auto& item in items()) {
    removeItem(item);
  }

  // Compute new scene dimensions based from model size
  num_cells_width = model->width;
  num_cells_height = model->height;
  board_start_x_pos = -static_cast<qint64>(model->width * cell_width / 2);
  board_start_y_pos = -static_cast<qint64>(model->height * cell_width / 2);

  // Set the scene boundary
  const auto scene_width = (num_cells_width - 2) * cell_width;
  const auto scene_height = (num_cells_height - 2) * cell_width;
  setSceneRect(board_start_x_pos, board_start_y_pos, scene_width, scene_height);

  // Add all new items
  for (auto x_coord = 0; x_coord < num_cells_width; x_coord++) {
    for (auto y_coord = 0; y_coord < num_cells_height; y_coord++) {
      const auto eff_x_pos = board_start_x_pos + x_coord * cell_width;
      const auto eff_y_pos = board_start_y_pos + y_coord * cell_width;
      Cell* cell = new Cell(x_coord, y_coord, cell_width);
      cell->setPos(QPointF(eff_x_pos, eff_y_pos));
      addItem(cell);
      connect(cell, SIGNAL(cellChanged(quint64, quint64)), model,
              SLOT(update_board(quint64, quint64)));
      connect(model, SIGNAL(board_changed(const BoardModel*)), cell,
              SLOT(updateCell(const BoardModel*)));
      connect(cell, &Cell::mouseEntered, this,
              [=](quint64 x_pos, quint64 y_pos) { emit cell_entered(x_pos, y_pos); });
      connect(cell, &Cell::mouseLeft, this, [=]() { emit cell_left(); });
    }
  }
}

void BoardScene::link_status_bar(const BoardStatus* status) noexcept {
  connect(this, &BoardScene::cell_entered, status, &BoardStatus::set_coordinate);
  connect(this, &BoardScene::cell_left, status, &BoardStatus::remove_coordinate);
}
