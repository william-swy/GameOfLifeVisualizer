#pragma once

#pragma warning(push, 0)  // System header should have warnings
#include <tuple>
#pragma warning(pop)

namespace gif {
  namespace image {
    // Target format for image
    enum class TargetFormat {
      RGB12,  // Red, Green, Blue 4 bits each
      RGB16,  // Red, Green, Blue, 5, 6, 5 bits respectively
      RGB24   // Red, Green, Blue 8 bits each
    };

    // Represents a RGBA pixel. This can also represent a RGB pixel by simply ignoring the alpha
    // channel. For simplicity, RGB pixels are represented in RGBA format where the alpha channel is
    // set to 255.
    class RGBPixel {
    public:
      unsigned char red;
      unsigned char green;
      unsigned char blue;

      RGBPixel() = default;

      RGBPixel(unsigned char red, unsigned char green, unsigned char blue) noexcept;

      // Creates new pixel from the original pixel where the colour channels are each 8 bits in size
      // to create a pixel of a total of 24 bits. The unsigned int is the shifted OR of each channel
      // and is interpreted as 0x00RRGGBB
      std::tuple<unsigned int, RGBPixel> RGB24() const noexcept;

      // Creates new pixel from the original pixel where the colour channels are each 4 bits in size
      // to create a pixel of a total of 12 bits. The unsigned int is the shifted OR of each channel
      // and is interpreted as 0x00000RGB
      std::tuple<unsigned int, RGBPixel> RGB12() const noexcept;

      // Creates new pixel from the original pixel where the colour channels are 5 bits for red
      // channel, 6 bits for green channel and 5 bits for blue channel for a total of 16 bits. The
      // unsigned int is the shifted OR of each channel and is interpreted as
      // 0b0000000000000000RRRRRGGGGGGBBBBB
      std::tuple<unsigned int, RGBPixel> RGB16() const noexcept;
    };
  }  // namespace image
}  // namespace gif