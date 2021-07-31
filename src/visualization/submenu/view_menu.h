#pragma once

#include <QAction>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "../view.h"

class ViewMenu : public QMenu {
  Q_OBJECT
public:
  ViewMenu(const QString& title, QWidget* parent = nullptr);

  void link_view(const View* view) noexcept;

  QAction* reset_zoom;
  QAction* view_result;
};