#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "board_ui.h"
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
    void openFile();
    void saveState();
    void exitApp();

    // view menu options
    void zoomIn();
    void zoomOut();
    void resetZoom();

    // run menu options
    void stepForward();
    void run();
    void stop();
    void increaseSpeed();
    void decreaseSpeed();
    void resetSpeed();

private:
    Ui::Board_Ui* ui;
    QGraphicsScene *scene;
    gameBoard::GameBoard* board;

    void connectAllSlots();
    void populateScene();
};

#endif // DISPLAYWINDOW_H
