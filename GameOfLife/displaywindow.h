#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "board_ui.h"
#include "cell.h"
#include "view.h"
#include "gameboard.h"

class DisplayWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();

private slots:
    // file menu options
    void newGameBoard();
    void exitApp();

    // run menu options
    //void stepForward();
    //void run();
    //void stop();
    //void increaseSpeed();
    //void decreaseSpeed();
    //void resetSpeed();

signals:
    // resets the zoom level to default
    void resetBoardZoom();
    //void resetCells();
    //void boardChanged(gameBoard::GameBoard* board);

//private slots:
//    void updateCellInfo(int x, int y);

private:
    Ui::Board_Ui* ui;
    View *view;
    QGraphicsScene *scene;
    gameBoard::GameBoard* board;
    bool isRunning;
    Cell** allCells;

    void connectAllSlots();
    void setupScene();
    // Generates the initial cells at default zoom level
    void populateScene();
};

#endif // DISPLAYWINDOW_H
