#include "file_menu.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QString>
#include <QWidget>

FileMenu::FileMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      save(new QAction(QIcon(":/Images/Icons/save.ico"), QAction::tr("Save"))),
      settings(new QAction(QIcon(":/Images/Icons/settings.ico"), QAction::tr("Settings"))),
      quit(new QAction(QAction::tr("Quit"))) {
  addAction(save);
  addAction(settings);
  addAction(quit);
  connect(quit, SIGNAL(triggered()), this, SLOT(quit_app()));
}

void FileMenu::quit_app() { QApplication::quit(); }

void FileMenu::configure_shortcuts() {
#if QT_CONFIG(shortcut)
  save->setShortcut(QMenu::tr("Ctrl+S"));
  settings->setShortcut(QMenu::tr("Ctrl+Alt+S"));
  quit->setShortcut(QMenu::tr("Ctrl+Q"));
#endif
}