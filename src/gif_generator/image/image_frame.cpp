#include "image_frame.h"

#include <array>
#include <cstddef>
#include <tuple>
#include <vector>

#include "colour_kd_tree.h"

namespace gif {
  ImageFrame::ImageFrame(const unsigned char* byte_data, std::size_t num_bytes,
                         unsigned short width, unsigned short height)
      : width(width), height(height) {
    for (std::size_t byte = 0; byte < num_bytes; byte += 3) {
      pixel_data.emplace_back(byte_data[byte + 0], byte_data[byte + 1], byte_data[byte + 2]);
    }
  }
}  // namespace gif