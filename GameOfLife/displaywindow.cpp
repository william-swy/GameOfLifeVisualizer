#include "displaywindow.h"
#include "board_ui.h"

const int SIZE = 100;

DisplayWindow::DisplayWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::Board_Ui;
    ui->setupUi(this);
    connectAllSlots();
    board = new gameBoard::GameBoard(SIZE, SIZE);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::newGameBoard()
{
    return;
}

void DisplayWindow::openFile()
{
    return;
}

void DisplayWindow::saveState()
{
    return;
}

void DisplayWindow::exitApp()
{
    QApplication::quit();
}

void DisplayWindow::zoomIn()
{
    return;
}

void DisplayWindow::zoomOut()
{
    return;
}

void DisplayWindow::resetZoom()
{
    return;
}

void DisplayWindow::stepForward()
{
    return;
}

void DisplayWindow::run()
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
}

void DisplayWindow::connectAllSlots()
{
    // file menu dropdown actions
    connect(ui->newBoard, SIGNAL(triggered()), this, SLOT(newGameBoard()));
    connect(ui->open, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(saveState()));
    connect(ui->quit, SIGNAL(triggered()), this, SLOT(exitApp()));

    // view menu dropdown actions
    connect(ui->zoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->zoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->resetZoom, SIGNAL(triggered()), this, SLOT(resetZoom()));

    // run menu dropdown actions
    connect(ui->step, SIGNAL(triggered()), this, SLOT(stepForward()));
    connect(ui->run, SIGNAL(triggered()), this, SLOT(run()));
    connect(ui->stop, SIGNAL(triggered()), this, SLOT(stop()));
    connect(ui->increaseSpeed, SIGNAL(triggered()), this, SLOT(increaseSpeed()));
    connect(ui->decreaseSpeed, SIGNAL(triggered()), this, SLOT(decreaseSpeed()));
    connect(ui->resetSpeed, SIGNAL(triggered()), this, SLOT(resetSpeed()));
}