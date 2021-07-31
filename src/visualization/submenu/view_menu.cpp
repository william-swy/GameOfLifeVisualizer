#include "view_menu.h"

#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "../view.h"

ViewMenu::ViewMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent),
      reset_zoom(new QAction(QAction::tr("Reset Zoom"))),
      view_result(new QAction(QIcon(":/Images/Icons/image.ico"), QAction::tr("View Result"))) {
  addAction(reset_zoom);
  addAction(view_result);
}

void ViewMenu::link_view(const View* view) noexcept {
  connect(reset_zoom, SIGNAL(triggered()), view, SLOT(reset_zoom()));
}