#pragma once

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class BoardCell : public QGraphicsObject {
  Q_OBJECT
public:
  BoardCell(quint64 x_pos, quint64 y_pos, QGraphicsItem* parent = nullptr);

  [[nodiscard]] QRectF boundingRect() const noexcept override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};