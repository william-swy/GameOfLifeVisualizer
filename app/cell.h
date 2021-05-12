//
// A Graphical representation of a cell on the game board
//
#ifndef CELL_H
#define CELL_H

#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include "GameOfLife/gameboard.h"

namespace Cell {
    /**
    * Cells have three possible attributes. The outline that is used to distinguish them, Dead state
    * and alive state.
    */
    enum CellAttributes {OUTLINE = 0, DEAD = 1, ALIVE = 2};

    class Cell : public QGraphicsObject {
        Q_OBJECT
    public:
        Cell(int x, int y, int size, QColor& outline, QColor& dead, QColor& alive, QGraphicsItem* parent = nullptr);

        /**
         * Returns the bounding box of the current cell.
         *
         * @return A QRectF that represents the current cell's bounding box
         */
        QRectF boundingRect() const override;

        /**
         * Paints the current cell with a black boarder. If the cell state is dead ('alive == false`), the inside of the
         * cell is painted white. If the cell state is alive (`alive == true`), the inside of the cell is painted black.
         * @param painter
         * @param option
         * @param widget
         */
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    public slots:
        /**
         * Resets the current cell state to dead. Redraws changes if necessary.
         */
        void resetCell();

        /**
         * Updates the current cell state by checking the board cell at coordinates (xCoord, yCoord).
         * Redraws the changes if necessary.
         *
         * @param board The gameBoard to check if the current cell has changed states.
         */
        void updateCell(gameboard::GameBoard* board);

    signals:
        /**
         * A signal notifying that this cell has changed state.
         *
         * @param x The x coordinate of this cell.
         * @param y The y coordinate of this cell.
         */
        void cellChanged(int x, int y);


        /**
         * A signal notifying that the mouse has entered the current cell.
         *
         * @param x The x coordinate of this cell.
         * @param y The y coordinate of this cell.
         */
        void mouseEntered(int x, int y);

        /**
         * A signal notifying that the mouse has left the current cell.
         */
        void mouseLeft();

    protected:
        /**
         * Handles the event where this cell object is double clicked by mouse. Flips the current state of this cell and
         * re-draws.
         *
         * @param event The double mouse click event.
         */
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

        /**
         * Signals that the mouse has entered the current cell.
         *
         * @param event The mouse hover event .
         */
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

        /**
         * Signals that the mouse has left the current cell.
         * @param event
         */
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    private:
        int size;
        int xCoord;
        int yCoord;
        bool alive = false;
        QColor* outlineColor;
        QColor* deadColor;
        QColor* aliveColor;
    };
}


#endif //CELL_H
