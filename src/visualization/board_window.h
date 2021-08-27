#pragma once

#include <QMainWindow>
#include <QWidget>

#include "board_scene.h"
#include "board_view.h"
#include "cell_board_model.h"

namespace visualization {
  constexpr quint32 BOARD_WIDTH = 200;
  constexpr quint32 BOARD_HEIGHT = 200;

  class BoardWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit BoardWindow(QWidget* parent = nullptr);

  private:
    CellBoardModel* cell_board;
    BoardView* view;
    BoardScene* scene;
  };
}  // namespace visualization
