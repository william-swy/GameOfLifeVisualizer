#pragma once

#include <QObject>

#include "cell_board.h"

namespace visualization {
  class CellBoardModel : public QObject {
    Q_OBJECT
  public:
    explicit CellBoardModel(quint64 board_width, quint64 board_height, QObject* parent = nullptr);

    void next_state() noexcept;

    bool get_cell(quint64 x_pos, quint64 y_pos) const;

  private:
    cell_board::CellBoard board;

  signals:
    void signal_board_update(CellBoardModel& model);

  private slots:
    void receive_cell_update(quint64 x_pos, quint64 y_pos);
  };
}  // namespace visualization