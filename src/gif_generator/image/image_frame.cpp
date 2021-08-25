#include "image_frame.h"

#include <array>
#include <cstddef>
#include <tuple>
#include <vector>

#include "colour_pallete.h"
#include "ppn.h"

namespace gif {
  namespace image {
    ImageFrame::ImageFrame(const unsigned char* byte_data, std::size_t num_bytes,
                           unsigned short width, unsigned short height)
        : width(width), height(height), depth(7) {
      constexpr std::size_t step_size = 3;
      pixel_data.reserve(num_bytes / step_size);
      for (std::size_t byte = 0; byte < num_bytes; byte += step_size) {
        pixel_data.emplace_back(byte_data[byte + 0], byte_data[byte + 1], byte_data[byte + 2]);
      }
    }

    void ImageFrame::quantize(TargetFormat target_format) noexcept {
    
    
    }
  }  // namespace image

}  // namespace gif