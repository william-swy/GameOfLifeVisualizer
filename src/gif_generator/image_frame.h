#pragma once

#include <array>
#include <cstddef>
#include <vector>

namespace gif {
  class Image {
  public:
    Image() = default;

    // Width and height are both unsigned short int as per GIF specifications as both image width
    // and image height must be stored as two bytes
    Image(const unsigned char* byte_data, std::size_t num_bytes, unsigned short width,
          unsigned short height, unsigned char depth, bool has_alpha);

    std::vector<char> LZW_compress() const noexcept;

    // Assumes that prev_img has the same width, height, depth and alpha.
    std::vector<char> LZW_compress(const Image& prev_img) const noexcept;

    std::vector<unsigned char> pixel_data;
    std::size_t width;
    std::size_t height;
    unsigned char depth;
    bool has_alpha;

  private:
    // Finds the number of changed pixels in current image compared to the previous image
    std::size_t num_changed_pixels(const Image& prev_img) const noexcept;
  };
}  // namespace gif