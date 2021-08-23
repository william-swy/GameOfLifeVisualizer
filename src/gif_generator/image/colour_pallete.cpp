#include "colour_pallete.h"

namespace gif {
  namespace image {
    ColourPallete::ColourPallete(std::vector<Bin>& bins) noexcept {
      for (const auto& bin : bins) {
        data.emplace_back(static_cast<unsigned char>(bin.red_channel_avg),
                          static_cast<unsigned char>(bin.green_channel_avg),
                          static_cast<unsigned char>(bin.blue_channel_avg));

        move_pixels(0, data.size() - 1, 0);
      }
    }

    void ColourPallete::move_pixels(int low, int high, int dimension) noexcept {}
  }  // namespace image

}  // namespace gif