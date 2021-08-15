#include "ppn_bin.h"

#include <algorithm>
#include <limits>

namespace gif {
  namespace ppn {
    double MSE_increase(const Bin& bin1, const Bin& bin2) noexcept {
      double mse = 0.0;

      const auto red_diff = std::max(bin1.red_channel_avg, bin2.red_channel_avg)
                            - std::min(bin1.red_channel_avg, bin2.red_channel_avg);

      const auto green_diff = std::max(bin1.green_channel_avg, bin2.green_channel_avg)
                              - std::min(bin1.green_channel_avg, bin2.green_channel_avg);

      const auto blue_diff = std::max(bin1.blue_channel_avg, bin2.blue_channel_avg)
                             - std::min(bin1.blue_channel_avg, bin2.blue_channel_avg);

      const auto alpha_diff = std::max(bin1.alpha_channel_avg, bin2.alpha_channel_avg)
                              - std::min(bin1.alpha_channel_avg, bin2.alpha_channel_avg);

      mse += static_cast<double>(red_diff * red_diff + green_diff * green_diff
                                 + blue_diff * blue_diff + alpha_diff * alpha_diff);

      mse *= static_cast<double>(bin1.pixel_count * bin2.pixel_count)
             / static_cast<double>(bin1.pixel_count + bin2.pixel_count);

      return mse;
    }

    Bin::Bin() noexcept
        : idx(0),
          alpha_channel_avg(0),
          red_channel_avg(0),
          green_channel_avg(0),
          blue_channel_avg(0),
          pixel_count(0),
          prev_idx(-1),
          next_idx(-1),
          heap_idx(-1),
          distance_to_next(std::numeric_limits<double>::max()) {}

    bool Bin::operator<(const Bin& other) const noexcept {
      return distance_to_next < other.distance_to_next;
    }
    void Bin::add_bin(const Bin& other) noexcept {
      red_channel_avg = (red_channel_avg * pixel_count + other.red_channel_avg * other.pixel_count)
                        / (pixel_count + other.pixel_count);
      green_channel_avg
          = (green_channel_avg * pixel_count + other.green_channel_avg * other.pixel_count)
            / (pixel_count + other.pixel_count);
      blue_channel_avg
          = (blue_channel_avg * pixel_count + other.blue_channel_avg * other.pixel_count)
            / (pixel_count + other.pixel_count);
      alpha_channel_avg
          = (alpha_channel_avg * pixel_count + other.alpha_channel_avg * other.pixel_count)
            / (pixel_count + other.pixel_count);
      pixel_count += other.pixel_count;
    }
  }  // namespace ppn
}  // namespace gif