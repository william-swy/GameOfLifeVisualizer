//
// A Graphical representation of a cell on the game board
//

#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QGraphicsItem{
public:
    Cell(int x, int y);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int xCoord;
    int yCoord;
    bool alive;
};


#endif //CELL_H
