#include "view.h"

#include <QGraphicsView>
#include <QPainter>
#include <QWheelEvent>
#include <QtMath>

View::View(QWidget *parent)
    : QGraphicsView(parent), scale_factor(1.25), max_zoom_in_times(5), curr_zoom_in_times(0) {
  const auto init_zoom = qPow(scale_factor, max_zoom_in_times + 1);
  scale(init_zoom, init_zoom);
  setRenderHint(QPainter::Antialiasing);
  setOptimizationFlags(QGraphicsView::DontSavePainterState);
  setCacheMode(QGraphicsView::CacheBackground);
  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  setMouseTracking(true);
}

void View::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    if (curr_zoom_in_times < max_zoom_in_times) {
      scale(scale_factor, scale_factor);
      curr_zoom_in_times++;
    }
  } else {
    if (curr_zoom_in_times > -max_zoom_in_times) {
      scale(1 / scale_factor, 1 / scale_factor);
      curr_zoom_in_times--;
    }
  }
}

void View::reset_zoom() {
  const auto zoom_ratio = qPow(scale_factor, -curr_zoom_in_times);
  scale(zoom_ratio, zoom_ratio);
  curr_zoom_in_times = 0;
}
