#include "cell_board.h"

#include <algorithm>

// Extra two each dimension for boarder
cell_board::CellBoard::CellBoard()
    : generation_number(0),
      curr_board_state(default_height, std::vector<bool>(default_width, false)),
      next_board_state(default_height, std::vector<bool>(default_width, false)) {}

// Extra two for each dimension for boarder
cell_board::CellBoard::CellBoard(size_t width, size_t height)
    : generation_number(0),
      curr_board_state(height, std::vector<bool>(width, false)),
      next_board_state(height, std::vector<bool>(width, false)) {}

bool cell_board::CellBoard::insert_point(size_t x_pos, size_t y_pos) {
  if (y_pos >= (curr_board_state.size())) {
    throw BoardOutOfBounds();
  }

  // Will always have at least one element due to precondition.
  if (x_pos >= curr_board_state[0].size()) {
    throw BoardOutOfBounds();
  }

  curr_board_state[y_pos][x_pos] = !curr_board_state[y_pos][x_pos];

  return curr_board_state[y_pos][x_pos];
}

void cell_board::CellBoard::next_state() {
  for (auto x_pos = 0; x_pos < curr_board_state[0].size(); x_pos++) {
    for (int y_pos = 0; y_pos < curr_board_state.size(); y_pos++) {
      const auto alive_neighbours = alive_neighbour_count(x_pos, y_pos);
      if (get_cell(x_pos, y_pos)) {
        // Alive cell with less than 2 neighbours dies from underpopulation.
        // Alive cell with more than 3 neighbours dies from overpopulation.
        if ((alive_neighbours < 2) || (alive_neighbours > 3)) {
          next_board_state[y_pos][x_pos] = false;
        }
        // Otherwise cell stays alive
        else {
          next_board_state[y_pos][x_pos] = true;
        }
      } else {
        // Dead cell with exactly 3 alive neigbours becomes alive.
        if (alive_neighbours == 3) {
          next_board_state[y_pos][x_pos] = true;
        }
        // Otherwise cell stays dead
        else {
          next_board_state[y_pos][x_pos] = false;
        }
      }
    }
  }
  // swap board states;
  curr_board_state.swap(next_board_state);

  // advance generation number
  generation_number++;
}

bool cell_board::CellBoard::get_cell(size_t x_pos, size_t y_pos) const {
  if (y_pos >= (curr_board_state.size())) {
    throw BoardOutOfBounds();
  }

  if (x_pos >= curr_board_state[0].size()) {
    throw BoardOutOfBounds();
  }

  return curr_board_state[y_pos][x_pos];
}

size_t cell_board::CellBoard::get_board_height() const noexcept { return curr_board_state.size(); }

size_t cell_board::CellBoard::get_board_width() const noexcept {
  // Always at least one element because of precondition.
  return curr_board_state[0].size();
}

size_t cell_board::CellBoard::get_generation_number() const noexcept { return generation_number; }

size_t cell_board::CellBoard::alive_neighbour_count(size_t x_pos, size_t y_pos) const noexcept {
  size_t alive_neighbours = 0;

  // Compute stencil boundaries
  const auto start_x_pos = x_pos > 0 ? x_pos - 1 : x_pos;
  const auto end_x_pos = std::min(x_pos + 1, get_board_width() - 1);

  const auto start_y_pos = y_pos > 0 ? y_pos - 1 : y_pos;
  const auto end_y_pos = std::min(y_pos + 1, get_board_height() - 1);

  // Compute stencil
  for (auto x_pos_eff = start_x_pos; x_pos_eff <= end_x_pos; x_pos_eff++) {
    for (auto y_pos_eff = start_y_pos; y_pos_eff <= end_y_pos; y_pos_eff++) {
      const bool state = get_cell(x_pos_eff, y_pos_eff);
      // don't count the current cell
      if ((x_pos_eff == x_pos) && (y_pos_eff == y_pos)) {
        continue;
      }
      if (state) {
        alive_neighbours++;
      }
    }
  }
  return alive_neighbours;
}
