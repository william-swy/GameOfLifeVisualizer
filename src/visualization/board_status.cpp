#include "board_status.h"

#include <QLabel>
#include <QWidget>

BoardStatus::BoardStatus(QWidget* parent)
    : QStatusBar(parent), gen_num_display(new QLabel(this)), coordinate_display(new QLabel(this)) {
  addPermanentWidget(coordinate_display);
  addPermanentWidget(new QLabel, 1);
  addPermanentWidget(gen_num_display);
}
