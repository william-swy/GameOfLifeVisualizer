#pragma once

#include <QGraphicsView>

namespace visualization {
  class BoardView : public QGraphicsView {
    Q_OBJECT
  public:
    explicit BoardView(QWidget* parent = nullptr);
  };
}  // namespace visualization