#include "view.h"

#include <QPainter>
#include <QWheelEvent>
#include <QtMath>

View::View(QWidget *parent) : QGraphicsView(parent) {
  this->scaleFactor = 1.25;
  this->maxZoomInTimes = 5;
  this->currZoomInTimes = 0;
  double initZoom = qPow(scaleFactor, maxZoomInTimes + 1);
  scale(initZoom, initZoom);
  setRenderHint(QPainter::Antialiasing);
  setOptimizationFlags(QGraphicsView::DontSavePainterState);
  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  setMouseTracking(true);
}

void View::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    if (currZoomInTimes < maxZoomInTimes) {
      scale(scaleFactor, scaleFactor);
      currZoomInTimes++;
    }
  } else {
    if (currZoomInTimes > -maxZoomInTimes) {
      scale(1 / scaleFactor, 1 / scaleFactor);
      currZoomInTimes--;
    }
  }
}

void View::resetZoom() {
  double zoomRatio = qPow(scaleFactor, -currZoomInTimes);
  scale(zoomRatio, zoomRatio);
  currZoomInTimes = 0;
}
