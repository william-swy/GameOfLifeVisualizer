#include "cell_board.h"

// Extra two each dimension for boarder
cell_board::CellBoard::CellBoard()
    : generation_number(0),
      curr_board_state(default_height, std::vector<bool>(default_width + 2, false)),
      next_board_state(default_height, std::vector<bool>(default_width + 2, false)) {}

// Extra two for each dimension for boarder
cell_board::CellBoard::CellBoard(size_t width, size_t height)
    : generation_number(0),
      curr_board_state(default_height, std::vector<bool>(width + 2, false)),
      next_board_state(default_height, std::vector<bool>(height + 2, false)) {}

bool cell_board::CellBoard::insert_point(size_t x, size_t y) {
  const auto effective_x = x + 1;
  const auto effective_y = y + 1;

  if (effective_y >= (curr_board_state.size() - 1)) {
    throw BoardOutOfBounds();
  }

  if (effective_x >= curr_board_state[0].size() - 1) {
    throw BoardOutOfBounds();
  }

  curr_board_state[effective_y][effective_x] = !curr_board_state[effective_y][effective_x];

  return curr_board_state[effective_y][effective_x];
}

void cell_board::CellBoard::next_state() {
  for (auto x = 1; x < curr_board_state[0].size() - 1; x++) {
    for (int y = 1; y < curr_board_state.size() - 1; y++) {
      auto alive_neighbours = alive_neighbour_count(x, y);
      if (get_cell(x, y)) {
        // Alive cell with less than 2 neighbours dies from underpopulation.
        // Alive cell with more than 3 neighbours dies from overpopulation.
        if ((alive_neighbours < 2) || (alive_neighbours > 3)) {
          next_board_state[y][x] = false;
        }
        // Otherwise cell stays alive
        else {
          next_board_state[y][x] = true;
        }
      } else {
        // Dead cell with exactly 3 alive neigbours becomes alive.
        if (alive_neighbours == 3) {
          next_board_state[y][x] = true;
        }
        // Otherwise cell stays dead
        else {
          next_board_state[y][x] = false;
        }
      }
    }
  }
  // swap board states;
  curr_board_state.swap(next_board_state);

  // advance generation number
  generation_number++;
}

bool cell_board::CellBoard::get_cell(size_t x, size_t y) const {
  const auto effective_x = x + 1;
  const auto effective_y = y + 1;

  if (effective_y >= (curr_board_state.size() - 1)) {
    throw BoardOutOfBounds();
  }

  if (effective_x >= curr_board_state[0].size() - 1) {
    throw BoardOutOfBounds();
  }

  return curr_board_state[effective_y][effective_x];
}

size_t cell_board::CellBoard::get_board_height() const noexcept {
  return curr_board_state.size() - 2;
}

size_t cell_board::CellBoard::get_board_width() const noexcept {
  return curr_board_state[0].size() - 2;
}

size_t cell_board::CellBoard::get_generation_number() const noexcept { return generation_number; }

size_t cell_board::CellBoard::alive_neighbour_count(size_t x, size_t y) const {
  size_t alive_neighbours = 0;

  const auto effective_x = x + 1;
  const auto effective_y = y + 1;

  for (auto i = effective_x - 1; i <= effective_x + 1; i++) {
    for (auto j = effective_y - 1; j <= effective_y + 1; j++) {
      const bool state = get_cell(i, j);
      // don't count the current cell
      if ((i == 0) && (j == 0)) {
        continue;
      }
      if (state) {
        alive_neighbours++;
      }
    }
  }
  return alive_neighbours;
}
