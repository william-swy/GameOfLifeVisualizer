#include "board_status.h"

#include <QLabel>
#include <QString>
#include <QWidget>

#include "board_model.h"

BoardStatus::BoardStatus(QWidget* parent)
    : QStatusBar(parent), gen_num_display(new QLabel(this)), coordinate_display(new QLabel(this)) {
  addPermanentWidget(coordinate_display);
  addPermanentWidget(new QLabel, 1);
  addPermanentWidget(gen_num_display);
  gen_num_display->setText("Generation number: 0");
}

void BoardStatus::link_board(const BoardModel* model) noexcept {
  connect(model, &BoardModel::board_changed, this, &BoardStatus::update_gen_num);
}

void BoardStatus::update_gen_num(const BoardModel* model) {
  const auto num = QString::number(model->get_generation_number());
  gen_num_display->setText("Generation number: " + num);
}

void BoardStatus::set_coordinate(quint64 x_pos, quint64 y_pos) {
  const auto x_coord_str = QString::number(x_pos);
  const auto y_coord_str = QString::number(y_pos);
  coordinate_display->setText("Coord: (" + x_coord_str + "," + y_coord_str + ")");
}

void BoardStatus::remove_coordinate() { coordinate_display->setText("Coord:"); }
