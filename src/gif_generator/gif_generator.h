#pragma once

#include <string>
#include <vector>

#include "image_frame.h"

namespace gif {
  // Assumes that each Image is of the same width and height all either include or exclude alpha
  // component from RGBA. Also assumes that there is at least one image in the vector of Images.
  // Simply does exactly as the description here: https://en.wikipedia.org/wiki/GIF
  void write_to_gif(const std::vector<ImageFrame>& image_sequence,
                    const std::string& file_name) noexcept;
}  // namespace gif