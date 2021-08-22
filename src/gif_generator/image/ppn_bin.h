#pragma once

#include <cstddef>


namespace gif {
  namespace image {
    class Bin {
    public:
      Bin() noexcept;

      std::size_t idx;

      double red_channel_avg;          // Red average
      double green_channel_avg;        // Green average
      double blue_channel_avg;         // Blue average
      unsigned long long pixel_count;  // Total count

      // For indicies, a negative value implies that the value is not valid. Values should be
      // positive to represent a valid value.
      long long prev_idx;
      long long next_idx;
      long long heap_idx;

      // Cost to merge with next bin. For bins without a next bin, i.e. next_idx is -1, the distance
      // is set to double max.
      double distance_to_next;

      bool operator<(const Bin& other) const noexcept;

      void add_bin(const Bin& other) noexcept;
    };

    // Computes the increaase in mean squared error if bin1 and bin2 are merged.
    double MSE_increase(const Bin& bin1, const Bin& bin2) noexcept;
  }  // namespace image
}  // namespace gif