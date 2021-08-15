#include "colour_pallete.h"

namespace gif {
  namespace image {
    ColourPallete::ColourPallete(std::vector<Bin>& bins,
                                 std::vector<std::size_t>& valid_indicies) noexcept {
      for (const auto& idx : valid_indicies) {
        data.emplace_back(static_cast<unsigned char>(bins[idx].red_channel_avg),
                          static_cast<unsigned char>(bins[idx].green_channel_avg),
                          static_cast<unsigned char>(bins[idx].blue_channel_avg));

        move_pixels(0, data.size() - 1, 0);
      }
    }

    void ColourPallete::move_pixels(int low, int high, int dimension) noexcept {}
  }  // namespace image

}  // namespace gif