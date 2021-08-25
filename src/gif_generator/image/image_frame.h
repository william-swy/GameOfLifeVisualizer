#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "RGB_pixel.h"

namespace gif {
  namespace image {
    class ImageFrame {
    public:
      ImageFrame() = default;

      // Width and height are both unsigned short int as per GIF specifications as both image width
      // and image height must be stored as two bytes
      ImageFrame(const unsigned char* byte_data, std::size_t num_bytes, unsigned short width,
                 unsigned short height);

      void quantize(TargetFormat target_format) noexcept;

      std::vector<unsigned char> LZW_compress() const noexcept;

      std::vector<image::RGBPixel> pixel_data;
      std::size_t width;
      std::size_t height;
      unsigned char depth;
    };
  }  // namespace image

}  // namespace gif