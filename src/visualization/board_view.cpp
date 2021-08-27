#include "board_view.h"

#include <QGraphicsView>
#include <QWidget>

visualization::BoardView::BoardView(QWidget* parent) : QGraphicsView(parent) {
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
}