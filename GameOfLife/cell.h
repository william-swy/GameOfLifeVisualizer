//
// A Graphical representation of a cell on the game board
//
#ifndef CELL_H
#define CELL_H

#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include "gameboard.h"

class Cell : public QGraphicsObject {
    Q_OBJECT
public:
    Cell(int x, int y, int size, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

public slots:
    void resetCell();
    void updateCell(gameBoard::GameBoard* board);

signals:
    void cellChanged(int x, int y);

protected:
    //void advance(int phase) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int size;
    int xCoord;
    int yCoord;
    bool alive = false;
};

#endif //CELL_H
