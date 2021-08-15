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
}  // namespace gif