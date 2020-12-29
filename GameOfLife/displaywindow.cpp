#include <QApplication>
#include <QTimer>
#include "displaywindow.h"
#include "board_ui.h"
#include "cell.h"

const int SIZE = 10;
const int CELLNUM = 100;
const int TOTALCELLS = 2*CELLNUM;
const int TOTALWIDTH = CELLNUM*SIZE;

DisplayWindow::DisplayWindow(QWidget *parent) : QMainWindow(parent)
    ,ui(new Ui::Board_Ui), view(new View(this))
    ,board(new gameBoard::GameBoard(TOTALCELLS, TOTALCELLS)),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    setCentralWidget(this->view);
    setupScene();
    connectAllSlots();
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
    delete scene;
    delete board;
}

void DisplayWindow::setupScene()
{
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    scene->setSceneRect(-TOTALWIDTH, -TOTALWIDTH, 2*(TOTALWIDTH-CELLNUM), 2*(TOTALWIDTH-CELLNUM));
    populateScene();
}

void DisplayWindow::newGameBoard()
{
    if(board) {
        delete board;
    }
    board = new gameBoard::GameBoard(TOTALCELLS,TOTALCELLS);

    emit resetBoardZoom();
    emit resetAllCells();
}

void DisplayWindow::exitApp()
{
    QApplication::quit();
}

void DisplayWindow::stepForward()
{
    board->nextState();
    emit boardChanged(board);
}

void DisplayWindow::run()
{
    ui->stop->setEnabled(true);
    ui->run->setEnabled(false);
    ui->increaseSpeed->setEnabled(false);
    ui->decreaseSpeed->setEnabled(false);
    ui->resetSpeed->setEnabled(false);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseBoardGeneration()));
    timer->start(currDelayTime);
}

void DisplayWindow::stop()
{
    timer->stop();
    delete timer;
    ui->run->setEnabled(true);
    ui->stop->setEnabled(false);
    changeSpeedOptions();
}

void DisplayWindow::increaseSpeed()
{
    if (currDelayTime > minDelayTime) {
        currDelayTime /= timeFactor;
        changeSpeedOptions();
    }
}

void DisplayWindow::decreaseSpeed()
{
    if (currDelayTime < maxDelayTime) {
        currDelayTime *= timeFactor;
        changeSpeedOptions();;
    }
}

void DisplayWindow::resetSpeed()
{
    currDelayTime = delayTime;
    changeSpeedOptions();
}

void DisplayWindow::connectAllSlots()
{
    // file menu dropdown actions
    connect(ui->newBoard, SIGNAL(triggered()), this, SLOT(newGameBoard()));
    connect(this, SIGNAL(resetBoardZoom()), view, SLOT(resetZoom()));

    connect(ui->quit, SIGNAL(triggered()), this, SLOT(exitApp()));

    // view menu dropdown actions
    connect(ui->resetZoom, SIGNAL(triggered()), this->view, SLOT(resetZoom()));

    // run menu dropdown actions
    connect(ui->step, SIGNAL(triggered()), this, SLOT(stepForward()));
    connect(ui->run, SIGNAL(triggered()), this, SLOT(run()));
    connect(ui->stop, SIGNAL(triggered()), this, SLOT(stop()));
    connect(ui->increaseSpeed, SIGNAL(triggered()), this, SLOT(increaseSpeed()));
    connect(ui->decreaseSpeed, SIGNAL(triggered()), this, SLOT(decreaseSpeed()));
    connect(ui->resetSpeed, SIGNAL(triggered()), this, SLOT(resetSpeed()));
}

void DisplayWindow::updateCellInfo(int x, int y)
{
    board->insertPoint(x,y);
}

void DisplayWindow::populateScene()
{
    int x = 0;
    int y = 0;
    for (int i = -TOTALWIDTH; i < TOTALWIDTH; i+=SIZE) {
        for (int j = -TOTALWIDTH; j < TOTALWIDTH; j+=SIZE) {
            Cell *cell= new Cell(x, y, SIZE);
            connect(this, SIGNAL(resetAllCells()), cell, SLOT(resetCell()));
            connect(cell, SIGNAL(cellChanged(int,int)), this, SLOT(updateCellInfo(int,int)));
            connect(this, SIGNAL(boardChanged(gameBoard::GameBoard*)), cell, SLOT(updateCell(gameBoard::GameBoard*)));
            cell->setPos(QPointF(i ,j));
            scene->addItem(cell);
            x++;
        }
        x = 0;
        y++;
    }
}

void DisplayWindow::increaseBoardGeneration()
{
    stepForward();
}

void DisplayWindow::changeSpeedOptions()
{
    if (currDelayTime == minDelayTime) {
        ui->increaseSpeed->setEnabled(false);
        ui->decreaseSpeed->setEnabled(true);
    }
    else if(currDelayTime == maxDelayTime) {
        ui->increaseSpeed->setEnabled(true);
        ui->decreaseSpeed->setEnabled(false);
    }
    else {
        ui->increaseSpeed->setEnabled(true);
        ui->decreaseSpeed->setEnabled(true);
    }
    ui->resetSpeed->setEnabled(true);
}