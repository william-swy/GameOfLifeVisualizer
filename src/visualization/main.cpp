#include <QApplication>

#include "displaywindow.h"
#include "main_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow w;
  //DisplayWindow w;
  w.show();
  return app.exec();
}