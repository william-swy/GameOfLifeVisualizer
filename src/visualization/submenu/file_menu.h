#pragma once

#include <QAction>
#include <QMenu>
#include <QString>
#include <QWidget>

class FileMenu : public QMenu {
  Q_OBJECT
public:
  FileMenu(const QString& title, QWidget* parent = nullptr);

private slots:
  void quit_app();

private:
  QAction* save;
  QAction* settings;
  QAction* quit;

  void configure_shortcuts();
};