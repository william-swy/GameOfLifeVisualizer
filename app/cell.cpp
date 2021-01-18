#include "cell.h"
#include "game_of_life/gameboard.h"


Cell::Cell::Cell(int x, int y, int size, QColor& outline, QColor& dead, QColor& alive, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    this->xCoord = x;
    this->yCoord = y;
    this->size = size;
    this->outlineColor = &outline;
    this->deadColor = &dead;
    this->aliveColor = &alive;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF Cell::Cell::boundingRect() const
{
    return QRectF(0,0,size,size);
}

void Cell::Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF rect = boundingRect();
    const QColor outlineCol = *outlineColor;
    QPen pen(outlineCol, 1);
    painter->setPen(pen);
    painter->drawRect(rect);

    if (alive) {
        const QColor aliveCol = *aliveColor;
        QBrush brush_black(aliveCol);
        painter->fillRect(rect, brush_black);
    }
    else {
        const QColor deadCol = *deadColor;
        QBrush brush_white(deadCol);
        painter->fillRect(rect, brush_white);
    }
}

void Cell::Cell::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    alive = !alive;
    update();
    emit cellChanged(xCoord, yCoord);
}

void Cell::Cell::resetCell()
{
    if (alive) {
        alive = false;
        update();
    }
}

void Cell::Cell::updateCell(gameBoard::GameBoard* board)
{
    if (alive != board->getCell(xCoord, yCoord)) {
        alive = !alive;
        update();
    }
}

void Cell::Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit mouseEntered(xCoord, yCoord);
}

void Cell::Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit mouseLeft();
}
