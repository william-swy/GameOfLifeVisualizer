#include "cell.h"
#include "gameboard.h"

//Cell::Cell(QGraphicsItem *parent) : QGraphicsObject(parent) {}

Cell::Cell(int x, int y, int size, QGraphicsItem* parent) : QGraphicsObject(parent)
{
    this->xCoord = x;
    this->yCoord = y;
    this->size = size;
    setFlag(ItemIsSelectable);
}

QRectF Cell::boundingRect() const
{
    return QRectF(0,0,size,size);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF rect = boundingRect();
    QPen pen(Qt::black,1);
    painter->setPen(pen);
    painter->drawRect(rect);

    if (alive) {
        QBrush brush_black(Qt::black);
        painter->fillRect(rect, brush_black);
    }
    else {
        QBrush brush_white(Qt::white);
        painter->fillRect(rect, brush_white);
    }
}

void Cell::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    alive = !alive;
    update();
    emit cellChanged(xCoord, yCoord);
}

void Cell::resetCell()
{
    if (alive) {
        alive = false;
        update();
    }
}

void Cell::updateCell(gameBoard::GameBoard* board)
{
    if (alive != board->getCell(xCoord, yCoord)) {
        alive = !alive;
        update();
    }
}