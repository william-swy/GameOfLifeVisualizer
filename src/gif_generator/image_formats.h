#pragma once

// Enumerations of image formats
namespace gif {
  // Original format of image
  enum class ImageFormat {
    RGB24,  // Red, Green, Blue. 8 bits each
    ARGB32  // Alpha, Red, Green, Blue. 8 bits each
  };

  // Target format for image
  enum class TargetFormat {
    RGB12,  // Red, Green, Blue 4 bits each
    RGBA16  // Red, Green, Blue, Alpha 4 bits each
  };

  unsigned short RGB24_to_RGB12(unsigned char red, unsigned char green,
                                unsigned char blue) noexcept;

  // The alpha channel is set at a default of 255 such that conversions can
  // be made from pixel formats without alpha channel to pixel formats with alpha channel. This
  // value can be overridden for a custom value.
  unsigned short RGB24_to_RGBA16(unsigned char red, unsigned char green, unsigned char blue,
                                 unsigned char alpha = 225) noexcept;

  unsigned short ARGB32_to_RGB12(unsigned char alpha, unsigned char red, unsigned char green,
                                 unsigned char blue) noexcept;

  unsigned short ARGB32_to_RGBA15(unsigned char alpha, unsigned char red, unsigned char green,
                                  unsigned char blue) noexcept;

  class Pixel {
  public:
    Pixel(unsigned char red, unsigned char green, unsigned char blue) noexcept;

    Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) noexcept;

    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    bool has_alpha;

    // Converts RGB channels of 8 bits each to RGB channels of 4 bits each. Note that it is assumed
    // that the pixel is in RGB format where each channel is 8 bits. It becomes the users
    // responsibility to ensure that this is true or at least the conversion is safe. The original
    // pixel is not mutated but the converted pixel is returned in the format of 0x0RGB which is
    // also the size of a unsigned short.
    unsigned short RGB24_to_RGB12() const noexcept;
  };
}  // namespace gif