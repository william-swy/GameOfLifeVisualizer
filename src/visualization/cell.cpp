#include "cell.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "board_model.h"

Cell::Cell(quint64 x_pos, quint64 y_pos, quint64 size, QGraphicsItem *parent)
    : QGraphicsObject(parent), x_coord(x_pos), y_coord(y_pos), size(size) {
  setFlag(ItemIsSelectable);
  setAcceptHoverEvents(true);
}

QRectF Cell::boundingRect() const { return QRectF(0, 0, size, size); }

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
  QRectF rect = boundingRect();
  QPen pen(Qt::black, 1);
  painter->setPen(pen);
  painter->drawRect(rect);

  if (alive) {
    QBrush brush_black(Qt::black);
    painter->fillRect(rect, brush_black);
  } else {
    QBrush brush_white(Qt::white);
    painter->fillRect(rect, brush_white);
  }
}

void Cell::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
  alive = !alive;
  update();
  emit cellChanged(x_coord, y_coord);
}

void Cell::resetCell() {
  if (alive) {
    alive = false;
    update();
  }
}

void Cell::updateCell(const BoardModel* board) {
  if (alive != board->get_cell(x_coord, y_coord)) {
    alive = !alive;
    update();
  }
}

void Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *) { emit mouseEntered(x_coord, y_coord); }

void Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *) { emit mouseLeft(); }