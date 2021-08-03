#include "colour_kd_tree.h"

#include <cmath>
#include <tuple>
#include <vector>

namespace colour_kd_tree {
  ColourKDTree::ColourKDTree(const std::vector<char>& data, std::size_t num_pixels,
                             unsigned char depth)
      : depth(depth) {
    const std::size_t last_elt = static_cast<std::size_t>(1 << depth);
    const std::size_t split_elt = last_elt / 2;
    const std::size_t split_dist = split_elt / 2;

    tree_split[static_cast<std::size_t>(1 << (depth - 1))] = 0;
    tree_split_elt[static_cast<std::size_t>(1 << (depth - 1))] = 0;

    // Get mutable version of input vector
    std::vector<char> mut_data(data.begin(), data.end());
    split_colours(mut_data.data(), num_pixels, 1, last_elt, split_elt, split_dist, 1);

    red[0] = 0;
    green[0] = 0;
    blue[0] = 0;
  }

  void ColourKDTree::closest_colour(std::tuple<int, int, int> colour, int& best_idx, int& best_diff,
                                    int tree_root) const noexcept {
    const auto& [red_val, green_val, blue_val] = colour;
    if (tree_root > (1 << depth) - 1) {
      int ind = tree_root - (1 << depth);
      if (ind == 0) return;

      int r_err = red_val - static_cast<int>(red[ind]);
      int g_err = green_val - static_cast<int>(green[ind]);
      int b_err = blue_val - static_cast<int>(blue[ind]);
      int diff = std::abs(r_err) + std::abs(g_err) + std::abs(b_err);

      if (diff < best_diff) {
        best_idx = ind;
        best_diff = diff;
      }

      return;
    }

    int split_comp;
    if (tree_split_elt[tree_root] == 0) {
      split_comp = red_val;
    } else if (tree_split_elt[tree_root] == 1) {
      split_comp = green_val;
    } else if (tree_split_elt[tree_root] == 2) {
      split_comp = blue_val;
    }  // Should not match anything else

    int split_pos = tree_split[tree_root];
    if (split_pos > split_comp) {
      closest_colour(colour, best_idx, best_diff, tree_root * 2);
      if (best_diff > split_pos - split_comp) {
        closest_colour(colour, best_idx, best_diff, tree_root * 2 + 1);
      }
    } else {
      closest_colour(colour, best_idx, best_diff, tree_root * 2 + 1);
      if (best_diff > split_comp - split_pos) {
        closest_colour(colour, best_idx, best_diff, tree_root * 2);
      }
    }
  }

  void ColourKDTree::split_colours(char* data, std::size_t num_pixels, std::size_t first_elt,
                                   std::size_t last_elt, std::size_t split_elt,
                                   std::size_t split_dist, std::size_t tree_node) noexcept {
    if (last_elt <= first_elt || num_pixels == 0) return;

    if (last_elt == first_elt + 1) {
      std::size_t r_value = 0;  // Red value
      std::size_t g_value = 0;  // Green value
      std::size_t b_value = 0;  // Blue value
      for (std::size_t idx = 0; idx < num_pixels; ++idx) {
        r_value += data[idx * 4 + 0];
        g_value += data[idx * 4 + 1];
        b_value += data[idx * 4 + 2];
      }

      r_value += static_cast<std::size_t>(num_pixels / 2);
      g_value += static_cast<std::size_t>(num_pixels / 2);
      b_value += static_cast<std::size_t>(num_pixels / 2);

      r_value /= static_cast<std::size_t>(num_pixels);
      g_value /= static_cast<std::size_t>(num_pixels);
      b_value /= static_cast<std::size_t>(num_pixels);

      red[first_elt] = static_cast<char>(r_value);
      green[first_elt] = static_cast<char>(g_value);
      blue[first_elt] = static_cast<char>(b_value);
    } else {
      auto min_red = 255, max_red = 0;
      auto min_green = 255, max_green = 0;
      auto min_blue = 255, max_blue = 0;
      for (int idx = 0; idx < num_pixels; ++idx) {
        int red_val = data[idx * 4 + 0];
        int green_val = data[idx * 4 + 1];
        int blue_val = data[idx * 4 + 2];

        if (red_val > max_red) max_red = red_val;
        if (red_val < min_red) min_red = red_val;

        if (green_val > max_green) max_green = green_val;
        if (green_val < min_green) min_green = green_val;

        if (blue_val > max_blue) max_blue = blue_val;
        if (blue_val < min_blue) min_blue = blue_val;
      }

      int red_range = max_red - min_red;
      int green_range = max_green - min_green;
      int blue_range = max_blue - min_blue;

      int split_com = 1;
      if (blue_range > green_range) split_com = 2;
      if (red_range > blue_range && red_range > green_range) split_com = 0;

      int sub_pixels_a
          = static_cast<int>(num_pixels * (split_elt - first_elt) / (last_elt - first_elt));
      int sub_pixels_b = static_cast<int>(num_pixels) - sub_pixels_a;

      partition_median(data, 0, static_cast<int>(num_pixels), split_com, sub_pixels_a);

      tree_split_elt[tree_node] = static_cast<char>(split_com);
      tree_split[tree_node] = data[sub_pixels_a * 4 + split_com];

      split_colours(data, sub_pixels_a, first_elt, split_elt, split_elt - split_dist,
                    split_dist / 2, tree_node * 2);
      split_colours(data + sub_pixels_a * 4, sub_pixels_b, split_elt, last_elt,
                    split_elt + split_dist, split_dist / 2, tree_node * 2 + 1);
    }
  }

  void ColourKDTree::partition_median(char* image, int left, int right, int com,
                                      int needed_center) const noexcept {
    if (left < right - 1) {
      int pivot_index = left + (right - left) / 2;

      pivot_index = partition(image, left, right, com, pivot_index);

      if (pivot_index > needed_center) {
        partition_median(image, left, pivot_index, com, needed_center);
      }

      if (pivot_index < needed_center) {
        partition_median(image, pivot_index + 1, right, com, needed_center);
      }
    }
  }

  int ColourKDTree::partition(char* image, const int left, const int right, const int elt,
                              int pivot_index) const noexcept {
    const int pivot_value = image[(pivot_index)*4 + elt];
    swap_pixels(image, pivot_index, right - 1);
    int store_index = left;
    bool split = 0;
    for (int ii = left; ii < right - 1; ++ii) {
      int array_val = image[ii * 4 + elt];
      if (array_val < pivot_value) {
        swap_pixels(image, ii, store_index);
        ++store_index;
      } else if (array_val == pivot_value) {
        if (split) {
          swap_pixels(image, ii, store_index);
          ++store_index;
        }
        split = !split;
      }
    }
    swap_pixels(image, store_index, right - 1);
    return store_index;
  }

  void ColourKDTree::swap_pixels(char* image, int pixA, int pixB) const noexcept {
    const std::tuple<char, char, char, char> pixel_a{image[pixA * 4], image[pixA * 4 + 1],
                                                     image[pixA * 4 + 2], image[pixA * 4 + 3]};

    const std::tuple<char, char, char, char> pixel_b{image[pixB * 4], image[pixB * 4 + 1],
                                                     image[pixB * 4 + 2], image[pixA * 4 + 3]};

    std::tie(image[pixA * 4], image[pixA * 4 + 1], image[pixA * 4 + 2], image[pixA * 4 + 3])
        = pixel_b;
    std::tie(image[pixB * 4], image[pixB * 4 + 1], image[pixB * 4 + 2], image[pixB * 4 + 3])
        = pixel_a;
  }
}  // namespace colour_kd_tree
