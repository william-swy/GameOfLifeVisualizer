#pragma once

#include <QMainWindow>

class MainView : public QMainWindow {
  Q_OBJECT
public:
  explicit MainView(QWidget* parent = nullptr) { showMaximized(); }
};