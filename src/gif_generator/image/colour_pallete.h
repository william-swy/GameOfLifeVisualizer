#pragma once

#include <vector>

#include "image_formats.h"
#include "image_frame.h"
#include "RGB_pixel.h"
#include "ppn_bin.h"

namespace gif {
  namespace image {
    class ColourPallete {
    public:
      ColourPallete() = default;

      ColourPallete(std::vector<Bin>& bins, std::vector<std::size_t>& valid_indicies) noexcept;

      std::vector<RGBPixel> data;

      private:
      void move_pixels(int low, int high, int dimension) noexcept;
    };

  }  // namespace image

}  // namespace gif