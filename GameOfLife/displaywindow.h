// Main display window. Shows and changes the gameBoard

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

    ~DisplayWindow() override;

private slots:
    // slots for "file" dropdown menu options

    /**
     * Creates a new gameBoard with all cells reset and zoom also reset
     * REQUIRES that the game cannot be currently running to be called
     */
    void newGameBoard();

    static void exitApp();

    // slots for "run" dropdown menu options

    /**
     * Advances the current gameBoard state forward one generation. Will update all cells with new data. Will update
     * status bar with new generation number.
     */
    void stepForward();

    /*
     * Repeatedly advances the current gameBoard state forward one generation until the user clicks stop.
     * REQUIRES that the game cannot be currently advancing (stopped) to call this function
     */
    void run();

    /**
     * Stops the repeated advance of the gameBoard state.
     * REQUIRES that the gameBoard must be currently running to call this function
     */
    void stop();

    /**
     * Makes the game ticker update `timeFactor` times faster.
     * Cannot further decrease ticker delay time if current time is at `minDelayTime`.
     * REQUIRES that the gameBoard must be currently stopped to execute this function
     */
    void increaseSpeed();

    /**
     * Makes the game ticker update `timeFactor` times slower.
     * Cannot further increase ticker delay time if current time is at `maxDelayTime`.
     * REQUIRES that the gameBoard must be currently stopped to execute this function.
     */
    void decreaseSpeed();

    /**
     * Makes the game ticker reset to original value of `delayTime`.
     * REQUIRES that the gameBoard must be currently stopped to execute this function.
     */
    void resetSpeed();

    // slots for managing the gameBoard

    /**
     * Flips the state of the cell at coordinate (x, y).
     *
     * @param x The x coordinate of the cell to change state.
     * @param y The y coordinate of the cell to change state.
     */
    void updateCellInfo(int x, int y);

    /**
     * Advances the board one generation forward.
     */
    void increaseBoardGeneration();

    /**
     * Sets the current mouse coordinate display to (x,y).
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    void setCoordinate(int x, int y);

    /**
     * Removes the current mouse coordinate display
     */
    void removeCoordinate();

signals:
    /**
     * A signal to notify the QGraphicsView object to reset scene zoom level to default.
     */
    void resetBoardZoom();

    /**
     * A signal to notify all Cells to update themselves to dead status.
     */
    void resetAllCells();

    /**
     * A signal to notify all Cells that the board state has changed and they should update themselves if necessary.
     * @param board Current gameBoard.
     */
    void boardChanged(gameBoard::GameBoard* board);

private:
    Ui::Board_Ui* ui;
    View *view;
    QGraphicsScene *scene;
    gameBoard::GameBoard* board;
    QTimer* timer = nullptr;
    int delayTime = 1000;
    int currDelayTime = delayTime;  // game ticker delay time
    int minDelayTime = 125;
    int maxDelayTime = 8000;
    int timeFactor = 2;

    /**
     * Connects all QActions to slots provided by this class
     */
    void connectAllSlots();

    /**
     * Configures the scene variable parameters
     */
    void setupScene();

    /**
     * Generates the initial cells at default zoom level
     */
    void populateScene();

    /**
     * Checks if gameBoard running speed manipulation buttons can be clicked. If so, they are set to enabled. If not
     * they are set to disabled.
     */
    void changeSpeedOptions();

    /**
     * Updates the status bar with the current generation number.
     */
    void updateStatusBar();

};

#endif // DISPLAYWINDOW_H
