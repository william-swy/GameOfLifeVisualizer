#pragma once

#include <vector>

#include "image_formats.h"
#include "image_frame.h"

namespace gif {

  class ColourPallete {
  public:
    ColourPallete() = default;

    ColourPallete(std::vector<unsigned char>& data, bool has_alpha);

    std::size_t step_size;
    std::vector<unsigned char> data;
  };

  ColourPallete quantize(ImageFrame& img, TargetFormat format);
}  // namespace gif