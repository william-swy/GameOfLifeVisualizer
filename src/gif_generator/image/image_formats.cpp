#include "image_formats.h"

namespace gif {
  unsigned short RGB24_to_RGB12(unsigned char red, unsigned char green,
                                unsigned char blue) noexcept {
    return ((red >> 4) << 8) | (green & 0xf0) | (blue >> 4);
  }
}  // namespace gif
