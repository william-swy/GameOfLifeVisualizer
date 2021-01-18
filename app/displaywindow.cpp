#include <QApplication>
#include <QString>
#include <QTimer>
#include "displaywindow.h"
#include "board_ui.h"
#include "cell.h"

const int SIZE = 10;
const int CELL_NUM = 100;
const int TOTAL_CELLS = 2 * CELL_NUM;
const int TOTAL_WIDTH = CELL_NUM * SIZE;

DisplayWindow::DisplayWindow(QWidget *parent) : QMainWindow(parent)
    ,ui(new Ui::Board_Ui), view(new View(this))
    ,board(new gameBoard::GameBoard(TOTAL_CELLS, TOTAL_CELLS)),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    setCentralWidget(this->view);
    setupScene();
    updateStatusBar();

    outline = QColor(Qt::black);
    dead = QColor(Qt::white);
    alive = QColor(Qt::black);

    this->settingsDialog = new Ui::SettingsDialog(outline, dead, alive, this);

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
    scene->setSceneRect(-TOTAL_WIDTH, -TOTAL_WIDTH, 2 * (TOTAL_WIDTH - CELL_NUM), 2 * (TOTAL_WIDTH - CELL_NUM));
    populateScene();
}

void DisplayWindow::newGameBoard()
{
    delete board;
    board = new gameBoard::GameBoard(TOTAL_CELLS, TOTAL_CELLS);

    emit resetBoardZoom();
    emit resetAllCells();
    updateStatusBar();
}

void DisplayWindow::exitApp()
{
    QApplication::quit();
}

void DisplayWindow::stepForward()
{
    board->nextState();
    emit boardChanged(board);
    updateStatusBar();
}

void DisplayWindow::run()
{
    ui->newBoard->setEnabled(false);
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
    if (timer) {
        timer->stop();
    }
    delete timer;
    ui->newBoard->setEnabled(true);
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

    // dialog related actions
    connect(ui->settings, SIGNAL(triggered()), this, SLOT(showSettings()));

    // settings changes
    connect(settingsDialog, SIGNAL(updateChanges()), this, SLOT(updateSettingsChanges()));
}

void DisplayWindow::updateCellInfo(int x, int y)
{
    board->insertPoint(x,y);
}

void DisplayWindow::populateScene()
{
    int x = 0;
    int y = 0;
    for (int i = -TOTAL_WIDTH; i < TOTAL_WIDTH; i+=SIZE) {
        for (int j = -TOTAL_WIDTH; j < TOTAL_WIDTH; j+=SIZE) {
            auto *cell= new Cell::Cell(x, y, SIZE, outline, dead, alive);
            connect(this, SIGNAL(resetAllCells()), cell, SLOT(resetCell()));
            connect(cell, SIGNAL(cellChanged(int,int)), this, SLOT(updateCellInfo(int,int)));
            connect(this, SIGNAL(boardChanged(gameBoard::GameBoard*)), cell, SLOT(updateCell(gameBoard::GameBoard*)));
            connect(cell, SIGNAL(mouseEntered(int, int)), this, SLOT(setCoordinate(int, int)));
            connect(cell, SIGNAL(mouseLeft()), this, SLOT(removeCoordinate()));
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

void DisplayWindow::updateStatusBar()
{
    QString num = QString::number(board->getGenerationNumber());
    ui->display->setText("Generation number: " + num);
}

void DisplayWindow::setCoordinate(int x, int y)
{
    QString xCoord = QString::number(x);
    QString yCoord = QString::number(y);
    ui->coordDisplay->setText("Coord: (" + xCoord + "," + yCoord + ")");
}

void DisplayWindow::removeCoordinate()
{
    ui->coordDisplay->setText("Coord");
}

void DisplayWindow::showSettings() {
    settingsDialog->exec();
}

void DisplayWindow::updateSettingsChanges()
{
    scene->update();
}
