//
// A Graphical representation of a cell on the game board
//
#ifndef CELL_H
#define CELL_H

#include <QPainter>
#include <QGraphicsItem>

class Cell : public QGraphicsItem {

public:
    Cell(int x, int y, int size);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void changeStatus(bool status);

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
