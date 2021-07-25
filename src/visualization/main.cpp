#include <QApplication>

#include "main_view.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainView w;
  w.show();
  return app.exec();
}
