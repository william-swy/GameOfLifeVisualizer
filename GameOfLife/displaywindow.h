#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
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
    void stepForward();
    void run();
    void stop();
    void increaseSpeed();
    void decreaseSpeed();
    void resetSpeed();

signals:
    // resets the zoom level to default
    void resetBoardZoom();
    // resets all cells to dead
    void resetAllCells();
    // signals all cells that board has changed, update if necessary
    void boardChanged(gameBoard::GameBoard* board);

private slots:
    void updateCellInfo(int x, int y);
    void increaseBoardGeneration();

private:
    Ui::Board_Ui* ui;
    View *view;
    QGraphicsScene *scene;
    gameBoard::GameBoard* board;
    QTimer* timer;
    int delayTime = 1000;
    int currDelayTime = delayTime;
    int minDelayTime = 125;
    int maxDelayTime = 8000;
    int timeFactor = 2;

    void connectAllSlots();
    void setupScene();
    // Generates the initial cells at default zoom level
    void populateScene();
    // checks if run speed can be changed. If it enables them
    void changeSpeedOptions();
    // Updates status bar with current generation number
    void updateStatusBar();
};

#endif // DISPLAYWINDOW_H
