#pragma once

#include <array>
#include <vector>
#include <tuple>

namespace colour_kd_tree {
  class ColourKDTree {
  public:
    ColourKDTree(const std::vector<char>& data, std::size_t num_pixels, unsigned char depth);

    std::array<char, 256> red;
    std::array<char, 256> green;
    std::array<char, 256> blue;

    std::array<char, 256> tree_split_elt;
    std::array<char, 256> tree_split;

    unsigned char depth;

    void closest_colour(std::tuple<int, int, int> colour, int& best_idx, int& best_diff,
                        int tree_root) const noexcept;

  private:
    void split_colours(char* data, std::size_t num_pixels, std::size_t first_elt,
                       std::size_t last_elt, std::size_t split_elt, std::size_t split_dist,
                       std::size_t tree_node) noexcept;

    void partition_median(char* image, int left, int right, int com,
                          int needed_center) const noexcept;

    int partition(char* image, const int left, const int right, const int elt,
                  int pivot_index) const noexcept;

    void swap_pixels(char* image, int pixA, int pixB) const noexcept;
  };
}  // namespace colour_kd_tree