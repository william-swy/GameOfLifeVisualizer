#include "image_formats.h"

namespace gif {
  unsigned short RGB24_to_RGB12(unsigned char red, unsigned char green,
                                unsigned char blue) noexcept {
    return ((red >> 4) << 8) | (green & 0xf0) | (blue >> 4);
  }
  Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue) noexcept
      : red(red), green(green), blue(blue), alpha(0), has_alpha(false) {}

  Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue,
               unsigned char alpha) noexcept
      : red(red), green(green), blue(blue), alpha(alpha), has_alpha(true) {}

  unsigned short Pixel::RGB24_to_RGB12() const noexcept {
    return ((red >> 4) << 8) | (green & 0xf0) | (blue >> 4);
  }
}  // namespace gif
