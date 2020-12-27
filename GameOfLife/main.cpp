#include <QApplication>

#include "displaywindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DisplayWindow w;
    w.show();

    return app.exec();
}
