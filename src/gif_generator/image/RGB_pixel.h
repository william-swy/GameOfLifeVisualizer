#pragma once

// Represents a RGBA pixel. This can also represent a RGB pixel by simply ignoring the alpha
// channel. For simplicity, RGB pixels are represented in RGBA format where the alpha channel is set
// to 255.
namespace gif {
  namespace image {
    class RGBPixel {
    public:
      unsigned char red;
      unsigned char green;
      unsigned char blue;

      RGBPixel(unsigned char red, unsigned char green, unsigned char blue) noexcept;
    };
  }  // namespace image
}  // namespace gif