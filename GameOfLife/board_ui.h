/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BOARD_UI_H
#define BOARD_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

const int INITWIDTH = 800;
const int INITHEIGHT = 600;

namespace Ui {
    class Board_Ui {
    public:
        QWidget* centralwidget;

        // menu bar
        QMenuBar *menubar;

        // menu bar tabs
        QMenu *menuFile, *menuView, *menuRun;

        QStatusBar* statusbar;

        // actions under file menu tab
        QAction *newBoard, *open, *save, *quit;

        // actions under view menu tab
        QAction *zoomIn, *zoomOut, *resetZoom;

        // actions under run menu tab
        QAction *step, *run, *stop, *increaseSpeed, *decreaseSpeed, *resetSpeed;

        // set up determined settings for UI objects
        void setupUi(QMainWindow* MainWindow) {
            MainWindow->resize(INITWIDTH, INITHEIGHT);
            createActions(MainWindow);
            createActionShortcuts();
            createMenus(MainWindow);
            setTitles(MainWindow);
        }

        // initialize menu drop down actions
        void createActions(QMainWindow* MainWindow)
        {
            // create file menu tab actions
            newBoard        = new QAction(MainWindow);
            open            = new QAction(MainWindow);
            save            = new QAction(MainWindow);
            quit            = new QAction(MainWindow);

            // create view menu tab actions
            zoomIn          = new QAction(MainWindow);
            zoomOut         = new QAction(MainWindow);
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
            menubar->setGeometry(QRect(0, 0, INITWIDTH, INITHEIGHT/24));

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
            menuFile->addAction(open);
            menuFile->addAction(save);
            menuFile->addAction(quit);

            // add view menu tab actions
            menuView->addAction(zoomIn);
            menuView->addAction(zoomOut);
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
            open->setText(QMainWindow::tr("Open"));
            save->setText(QMainWindow::tr("Save"));
            quit->setText(QMainWindow::tr("Quit"));

            // view menu action titles
            zoomIn->setText(QMainWindow::tr("Zoom In"));
            zoomOut->setText(QMainWindow::tr("Zoom Out"));
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
                open->setShortcut(QMainWindow::tr("Ctrl+O"));
                save->setShortcut(QMainWindow::tr("Ctrl+S"));
                quit->setShortcut(QMainWindow::tr("Ctrl+Q"));

                // view menu action shortcuts
                zoomIn->setShortcut(QMainWindow::tr("Ctrl+="));
                zoomOut->setShortcut(QMainWindow::tr("Ctrl+-"));

                // run menu action shortcuts
                step->setShortcut(QMainWindow::tr("Ctrl+N"));
                run->setShortcut(QMainWindow::tr("Ctrl+Shift+R"));
                stop->setShortcut(QMainWindow::tr("Ctrl+Shift+S"));
            #endif
        }
    };
}
#endif // BOARD_UI_H
