#include <QApplication>
#include "displaywindow.h"
#include "board_ui.h"
#include "cell.h"
#include <iostream>

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

/*void DisplayWindow::run()
{
    return;
}

void DisplayWindow::stop()
{
    return;
}

void DisplayWindow::increaseSpeed()
{
    return;
}

void DisplayWindow::decreaseSpeed()
{
    return;
}

void DisplayWindow::resetSpeed()
{
    return;
}*/

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
    //connect(ui->run, SIGNAL(triggered()), this, SLOT(run()));
    //connect(ui->stop, SIGNAL(triggered()), this, SLOT(stop()));
    //connect(ui->increaseSpeed, SIGNAL(triggered()), this, SLOT(increaseSpeed()));
    //connect(ui->decreaseSpeed, SIGNAL(triggered()), this, SLOT(decreaseSpeed()));
    //connect(ui->resetSpeed, SIGNAL(triggered()), this, SLOT(resetSpeed()));
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