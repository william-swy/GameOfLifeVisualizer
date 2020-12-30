// GUI layout for application

#ifndef BOARD_UI_H
#define BOARD_UI_H

#include <QAction>
#include <QChar>
#include <QIcon>
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
        QMenu *menuFile, *menuEdit, *menuView, *menuRun;

        // actions under file menu tab
        QAction *newBoard, *save, *settings, *quit;

        // actions under edit menu tab
        QAction *takeSnapShot, *startRecording, *endRecording;

        // actions under view menu tab
        QAction *resetZoom, *viewResult;

        // actions under run menu tab
        QAction *step, *run, *stop, *increaseSpeed, *decreaseSpeed, *resetSpeed;

        // status bar and it's widgets
        QStatusBar *statusBar;
        QLabel* display;
        QLabel* coordDisplay;

        // set up determined settings for UI objects
        void setupUi(QMainWindow* MainWindow) {
            MainWindow->showMaximized();
            MainWindow->setWindowIcon(QIcon(":/Images/Icons/pulsar.ico"));
            createActions(MainWindow);
            createActionShortcuts();
            createMenus(MainWindow);
            setTitles(MainWindow);

            // initially set stop to disabled. Enable only if gameBoard is running
            stop->setEnabled(false);
            // status bar set up
            setupStatusBar(MainWindow);
            addIcons();
        }

        // initialize menu drop down actions
        void createActions(QMainWindow* MainWindow)
        {
            // create file menu tab actions
            newBoard        = new QAction(MainWindow);
            save            = new QAction(MainWindow);
            settings        = new QAction(MainWindow);
            quit            = new QAction(MainWindow);

            // create edit menu tab actions;
            takeSnapShot    = new QAction(MainWindow);
            startRecording  = new QAction(MainWindow);
            endRecording    = new QAction(MainWindow);

            // create view menu tab actions
            resetZoom       = new QAction(MainWindow);
            viewResult      = new QAction(MainWindow);

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
            menuEdit = new QMenu(menubar);
            menuView = new QMenu(menubar);
            menuRun = new QMenu(menubar);

            MainWindow->setMenuBar(menubar);

            // add dropdown menu tab actions
            menubar->addAction(menuFile->menuAction());
            menubar->addAction(menuEdit->menuAction());
            menubar->addAction(menuView->menuAction());
            menubar->addAction(menuRun->menuAction());

            // add file menu tab actions
            menuFile->addAction(newBoard);
            menuFile->addAction(save);
            menuFile->addAction(settings);
            menuFile->addAction(quit);

            // add edit menu tab actions
            menuEdit->addAction(takeSnapShot);
            menuEdit->addAction(startRecording);
            menuEdit->addAction(endRecording);

            // add view menu tab actions
            menuView->addAction(resetZoom);
            menuView->addAction(viewResult);

            // add run menu tab actions
            menuRun->addAction(step);
            menuRun->addAction(run);
            menuRun->addAction(stop);
            menuRun->addAction(increaseSpeed);
            menuRun->addAction(decreaseSpeed);
            menuRun->addAction(resetSpeed);
        }

        // set titles to widgets
        void setTitles(QMainWindow *MainWindow) const {
            // main window title
            MainWindow->setWindowTitle(QMainWindow::tr("Game Of Life"));

            // menu bar titles
            menuFile->setTitle(QMainWindow::tr("File"));
            menuEdit->setTitle(QMainWindow::tr("Edit"));
            menuView->setTitle(QMainWindow::tr("View"));
            menuRun->setTitle(QMainWindow::tr("Run"));

            // file menu action titles
            newBoard->setText(QMainWindow::tr("New Board"));
            save->setText(QMainWindow::tr("Save"));
            settings->setText(QMainWindow::tr("Settings"));
            quit->setText(QMainWindow::tr("Quit"));

            // edit menu action titles
            takeSnapShot->setText(QMainWindow::tr("Take Snip"));
            startRecording->setText(QMainWindow::tr("Start Recording"));
            endRecording->setText(QMainWindow::tr("End Recording"));

            // view menu action titles
            resetZoom->setText(QMainWindow::tr("Reset Zoom"));
            viewResult->setText(QMainWindow::tr("View Result"));

            // run menu action titles
            step->setText(QMainWindow::tr("Step Forward"));
            run->setText(QMainWindow::tr("Run"));
            stop->setText(QMainWindow::tr("Stop"));
            increaseSpeed->setText(QMainWindow::tr("Increase Speed"));
            decreaseSpeed->setText(QMainWindow::tr("Decrease Speed"));
            resetSpeed->setText(QMainWindow::tr("Reset Speed"));
        }

        // set action shortcut keys
        void createActionShortcuts() const {
            #if QT_CONFIG(shortcut)
                // file menu action shortcuts
                save->setShortcut(QMainWindow::tr("Ctrl+S"));
                settings->setShortcut(QMainWindow::tr("Ctrl+Alt+S"));
                quit->setShortcut(QMainWindow::tr("Ctrl+Q"));

                // run menu action shortcuts
                step->setShortcut(QMainWindow::tr("Ctrl+N"));
                run->setShortcut(QMainWindow::tr("Ctrl+Shift+R"));
                stop->setShortcut(QMainWindow::tr("Ctrl+Shift+S"));
            #endif
        }

        // set up status bar
        void setupStatusBar(QMainWindow* MainWindow) {
            statusBar = new QStatusBar(MainWindow);
            display = new QLabel();
            coordDisplay = new QLabel();

            statusBar->addPermanentWidget(coordDisplay);
            statusBar->addPermanentWidget(new QLabel,1);
            statusBar->addPermanentWidget(display);
            MainWindow->setStatusBar(statusBar);
        }

        // add icons to respective QActions
        void addIcons() const {
            // file menu icons
            save->setIcon(QIcon(":/Images/Icons/save.ico"));
            settings->setIcon(QIcon(":/Images/Icons/settings.ico"));

            // edit menu icons
            takeSnapShot->setIcon(QIcon(":/Images/Icons/screenshot.ico"));

            // view menu icons
            viewResult->setIcon(QIcon(":/Images/Icons/image.ico"));

            // run menu icons
            step->setIcon(QIcon(":/Images/Icons/arrow.ico"));
            run->setIcon(QIcon(":/Images/Icons/play.ico"));
            stop->setIcon(QIcon(":/Images/Icons/stop.ico"));
        }
    };
}
#endif // BOARD_UI_H
