#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "image_formats.h"

namespace gif {

  class ImageFrame {
  public:
    ImageFrame() = default;

    // Width and height are both unsigned short int as per GIF specifications as both image width
    // and image height must be stored as two bytes
    ImageFrame(const unsigned char* byte_data, std::size_t num_bytes, unsigned short width,
               unsigned short height, ImageFormat format);

    std::vector<char> LZW_compress() const noexcept;

    // Assumes that prev_img has the same width, height, depth and alpha.
    std::vector<char> LZW_compress(const ImageFrame& prev_img) const noexcept;

    std::vector<unsigned char> pixel_data;
    std::size_t width;
    std::size_t height;
    unsigned char depth;
    ImageFormat format;

  private:
    // Finds the number of changed pixels in current image compared to the previous image
    std::size_t num_changed_pixels(const ImageFrame& prev_img) const noexcept;
  };
}  // namespace gif