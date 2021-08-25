#pragma once

#include <cstddef>
#include <tuple>
#include <vector>

#include "RGB_pixel.h"

namespace gif {
  namespace image {
    class ColourPallete {
    public:
      ColourPallete() = default;

      // Will take ownership of the vector of pixels. The vector of pixels should be the reduced
      // amount of pixels. Precondition is that the bins have a size of at least 1.
      ColourPallete(std::vector<RGBPixel>&& bins) noexcept;

      // Precondition is that the tree has at least one element.
      RGBPixel find_nearest_neighbour(const RGBPixel& query) const noexcept;

    private:
      std::vector<RGBPixel> kd_tree;

      void move_pixels(long long low, long long high, std::size_t dimension) noexcept;

      void quick_select(long long start, long long end, long long k,
                        std::size_t dimension) noexcept;

      long long partition(long long low, long long high, std::size_t dimension) noexcept;

      // First element of tuple is the nearest_neighour pixel, Second element of tuple is a flag
      // indicating if the pixel is valid.
      std::tuple<RGBPixel, bool> nearest_neighbour(const RGBPixel& query, long long low,
                                                   long long high,
                                                   std::size_t dimension) const noexcept;

      // First element of tuple is the pixel from the other branch of the KD-tree, Second element of
      // tuple is a flag indicating if the pixel is valid.
      std::tuple<RGBPixel, bool> search_other_branch(const RGBPixel& query, long long low,
                                                     long long high,
                                                     std::size_t shortest_dist_sqrd) const noexcept;
    };

  }  // namespace image

}  // namespace gif