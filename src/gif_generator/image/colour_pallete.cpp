#include "colour_pallete.h"

#include <cmath>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

#include "RGB_pixel.h"

namespace gif {
  namespace image {
    // Should have no copies of the vector being made
    ColourPallete::ColourPallete(std::vector<RGBPixel>&& bins) noexcept : kd_tree(std::move(bins)) {
      move_pixels(0, static_cast<long long>(kd_tree.size() - 1), 0);
    }

    RGBPixel ColourPallete::find_nearest_neighbour(const RGBPixel& query) const noexcept {
      // is_valid is not needed to be checked because NN_pix should always be valid.
      const auto& [NN_pix, is_valid]
          = nearest_neighbour(query, 0, static_cast<long long>(kd_tree.size() - 1), 0);

      return NN_pix;
    }

    std::size_t ColourPallete::size() const noexcept {
      // Will never take log of 0 as the size always has at least one element.
      const auto val = std::log2(static_cast<double>(kd_tree.size()));
      return static_cast<std::size_t>(std::ceil(val));
    }

    // low and high are long long instead of std::size_t as middle -1 is called during the recursion
    // and will cause middle could wrap around when high is 1 and low is 0.
    void ColourPallete::move_pixels(long long low, long long high, std::size_t dimension) noexcept {
      if (high > low) {
        const auto middle = (high + low) / 2;
        quick_select(low, high, middle, dimension);

        const auto new_dimension = (dimension + 1) % 3;
        move_pixels(low, middle - 1, new_dimension);
        move_pixels(middle + 1, high, new_dimension);
      }
    }

    void ColourPallete::quick_select(long long start, long long end, long long k,
                                     std::size_t dimension) noexcept {
      if (start < end) {
        const auto pivot = partition(start, end, dimension);

        if (pivot < k) {
          quick_select(start, pivot - 1, k, dimension);
        } else if (k > pivot) {
          quick_select(pivot + 1, end, k, dimension);
        }
      }
    }

    long long ColourPallete::partition(long long low, long long high,
                                       std::size_t dimension) noexcept {
      auto pivot = low;
      for (auto i = low + 1; i <= high; i++) {
        if (RGB_smaller_by_dim(kd_tree[static_cast<std::size_t>(i)],
                               kd_tree[static_cast<std::size_t>(low)], dimension)) {
          pivot++;
          std::swap(kd_tree[static_cast<std::size_t>(pivot)], kd_tree[static_cast<std::size_t>(i)]);
        }
      }
      std::swap(kd_tree[static_cast<std::size_t>(low)], kd_tree[static_cast<std::size_t>(pivot)]);
      return pivot;
    }

    std::tuple<RGBPixel, bool> ColourPallete::nearest_neighbour(
        const RGBPixel& query, long long low, long long high,
        std::size_t dimension) const noexcept {
      if (high >= low) {
        const auto curr_index = (low + high) / 2;
        auto curr_pixel = kd_tree[static_cast<std::size_t>(curr_index)];

        // distance of query to current node
        auto dist_to_curr = RGB_euclidian_squared(query, curr_pixel);

        // distance of query to current plane
        const auto dist_to_plane = RGB_dim_distance_squared(query, curr_pixel, dimension);

        const auto next_dimension = (dimension + 1) % 3;

        if (RGB_smaller_by_dim(query, curr_pixel, dimension)) {
          const auto& [left, left_is_valid]
              = nearest_neighbour(query, low, curr_index - 1, next_dimension);
          if (left_is_valid) {
            const auto result_dist = RGB_euclidian_squared(query, left);
            if (result_dist < dist_to_curr) {
              curr_pixel = left;
              dist_to_curr = result_dist;
            }
            if (dist_to_plane < dist_to_curr) {
              const auto& [right_other, right_other_is_valid]
                  = search_other_branch(query, curr_index + 1, high, dist_to_curr);
              if (right_other_is_valid) {
                curr_pixel = right_other;
              }
            }
          }
        } else {
          const auto& [right, right_is_valid]
              = nearest_neighbour(query, curr_index + 1, high, next_dimension);
          if (right_is_valid) {
            const auto result_dist = RGB_euclidian_squared(query, right);
            if (result_dist < dist_to_curr) {
              curr_pixel = right;
              dist_to_curr = result_dist;
            }
            if (dist_to_plane < dist_to_curr) {
              const auto& [left_other, left_other_is_valid]
                  = search_other_branch(query, low, curr_index - 1, dist_to_curr);
              if (left_other_is_valid) {
                curr_pixel = left_other;
              }
            }
          }
        }
        return {std::move(curr_pixel), true};
      } else {
        // Invalid pixel
        return {RGBPixel(), false};
      }
    }

    std::tuple<RGBPixel, bool> ColourPallete::search_other_branch(
        const RGBPixel& query, long long low, long long high,
        std::size_t shortest_dist_sqrd) const noexcept {
      if (high >= low) {
        const auto curr_index = (high + low) / 2;
        const auto& curr_node = kd_tree[static_cast<std::size_t>(curr_index)];
        RGBPixel shortest_node;

        const auto curr_dist = RGB_euclidian_squared(query, curr_node);
        if (curr_dist < shortest_dist_sqrd) {
          shortest_dist_sqrd = curr_dist;
          shortest_node = curr_node;
        }
        const auto& [left, left_is_valid]
            = search_other_branch(query, low, curr_index - 1, shortest_dist_sqrd);
        const auto& [right, right_is_valid]
            = search_other_branch(query, curr_index + 1, high, shortest_dist_sqrd);

        if (left_is_valid) {
          const auto left_dist = RGB_euclidian_squared(query, left);
          if (left_dist < shortest_dist_sqrd) {
            shortest_dist_sqrd = left_dist;
            shortest_node = left;
          }
        }
        if (right_is_valid) {
          const auto right_dist = RGB_euclidian_squared(query, right);
          if (right_dist < shortest_dist_sqrd) {
            shortest_dist_sqrd = right_dist;
            shortest_node = right;
          }
        }
        return {std::move(shortest_node), true};
      } else {
        // Invalid pixel
        return {RGBPixel(), false};
      }
    }

  }  // namespace image

}  // namespace gif