#pragma once

#include "RGB_pixel.h"

// Enumerations of image formats
namespace gif {
  namespace image {
    // Target format for image
    enum class TargetFormat {
      RGB12,  // Red, Green, Blue 4 bits each
      RGB16,  // Red, Green, Blue, 5, 6, 5 bits respectively
      RGB24   // Red, Green, Blue 8 bits each
    };

    inline unsigned int RGB24(const RGBPixel& pixel) noexcept { return 0; };

    // Returns the value of the pixel interpreted in RGB format where each channel is 4 bits. The
    // return value is interpreted as 0x00000RGB
    inline unsigned int RGB12(const RGBPixel& pixel) noexcept {
      { return ((pixel.red >> 4) << 8) | (pixel.green & 0xf0) | (pixel.blue >> 4); }
    }

    inline unsigned int RGB16(const RGBPixel& pixel) noexcept { return 0; }

  }  // namespace image

}  // namespace gif