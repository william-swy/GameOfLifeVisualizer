// GUI layout for application

#ifndef BOARD_UI_H
#define BOARD_UI_H

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

const int INIT_WIDTH = 800;
const int INIT_HEIGHT = 600;

namespace Ui {
    class Board_Ui {
    public:
        // menu bar
        QMenuBar *menubar;

        // menu bar tabs
        QMenu *menuFile, *menuView, *menuRun;

        // actions under file menu tab
        QAction *newBoard, *quit;

        // actions under view menu tab
        QAction *resetZoom;

        // actions under run menu tab
        QAction *step, *run, *stop, *increaseSpeed, *decreaseSpeed, *resetSpeed;

        // status bar and it's widgets
        QStatusBar *statusBar;
        QLabel* display;

        // set up determined settings for UI objects
        void setupUi(QMainWindow* MainWindow) {
            MainWindow->showMaximized();
            createActions(MainWindow);
            createActionShortcuts();
            createMenus(MainWindow);
            setTitles(MainWindow);

            // initially set stop to disabled. Enable only if gameBoard is running
            stop->setEnabled(false);

            // status bar set up
            statusBar = new QStatusBar(MainWindow);
            display = new QLabel();
            statusBar->addPermanentWidget(display);
            MainWindow->setStatusBar(statusBar);
        }

        // initialize menu drop down actions
        void createActions(QMainWindow* MainWindow)
        {
            // create file menu tab actions
            newBoard        = new QAction(MainWindow);
            quit            = new QAction(MainWindow);

            // create view menu tab actions
            resetZoom       = new QAction(MainWindow);

            // create run menu tab options
            step            = new QAction(MainWindow);
            run             = new QAction(MainWindow);
            stop            = new QAction(MainWindow);
            increaseSpeed   = new QAction(MainWindow);
            decreaseSpeed   = new QAction(MainWindow);
            resetSpeed      = new QAction(MainWindow);
        }

        // create menu bar and its buttons
        void createMenus(QMainWindow* MainWindow)
        {
            menubar = new QMenuBar(MainWindow);
            menubar->setGeometry(QRect(0, 0, INIT_WIDTH, INIT_HEIGHT/24));

            menuFile = new QMenu(menubar);
            menuView = new QMenu(menubar);
            menuRun = new QMenu(menubar);

            MainWindow->setMenuBar(menubar);

            // add dropdown menu tab actions
            menubar->addAction(menuFile->menuAction());
            menubar->addAction(menuView->menuAction());
            menubar->addAction(menuRun->menuAction());

            // add file menu tab actions
            menuFile->addAction(newBoard);
            menuFile->addAction(quit);

            // add view menu tab actions
            menuView->addAction(resetZoom);

            // add run menu tab actions
            menuRun->addAction(step);
            menuRun->addAction(run);
            menuRun->addAction(stop);
            menuRun->addAction(increaseSpeed);
            menuRun->addAction(decreaseSpeed);
            menuRun->addAction(resetSpeed);
        }

        // set titles to widgets
        void setTitles(QMainWindow *MainWindow) {
            // main window title
            MainWindow->setWindowTitle(QMainWindow::tr("Game Of Life"));

            // menu bar titles
            menuFile->setTitle(QMainWindow::tr("File"));
            menuView->setTitle(QMainWindow::tr("View"));
            menuRun->setTitle(QMainWindow::tr("Run"));

            // file menu action titles
            newBoard->setText(QMainWindow::tr("New Board"));
            quit->setText(QMainWindow::tr("Quit"));

            // view menu action titles
            resetZoom->setText(QMainWindow::tr("Reset Zoom"));

            // run menu action titles
            step->setText(QMainWindow::tr("Step Forward"));
            run->setText(QMainWindow::tr("Run"));
            stop->setText(QMainWindow::tr("Stop"));
            increaseSpeed->setText(QMainWindow::tr("Increase Speed"));
            decreaseSpeed->setText(QMainWindow::tr("Decrease Speed"));
            resetSpeed->setText(QMainWindow::tr("Reset Speed"));
        }

        // set action shortcut keys
        void createActionShortcuts() {
            #if QT_CONFIG(shortcut)
                // file menu action shortcuts
                quit->setShortcut(QMainWindow::tr("Ctrl+Q"));

                // run menu action shortcuts
                step->setShortcut(QMainWindow::tr("Ctrl+N"));
                run->setShortcut(QMainWindow::tr("Ctrl+Shift+R"));
                stop->setShortcut(QMainWindow::tr("Ctrl+Shift+S"));
            #endif
        }
    };
}
#endif // BOARD_UI_H
