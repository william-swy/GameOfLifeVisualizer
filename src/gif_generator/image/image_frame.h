#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "RGB_pixel.h"

namespace gif {

  class ImageFrame {
  public:
    ImageFrame() = default;

    // Width and height are both unsigned short int as per GIF specifications as both image width
    // and image height must be stored as two bytes
    ImageFrame(const unsigned char* byte_data, std::size_t num_bytes, unsigned short width,
               unsigned short height);

    std::vector<char> LZW_compress() const noexcept;

    std::vector<image::RGBPixel> pixel_data;
    std::size_t width;
    std::size_t height;
    unsigned char depth;

  private:
    // Finds the number of changed pixels in current image compared to the previous image
    std::size_t num_changed_pixels(const ImageFrame& prev_img) const noexcept;
  };
}  // namespace gif