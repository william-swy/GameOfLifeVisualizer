#pragma once

#pragma warning(push, 0)  // System header should have warnings
#include <cstddef>
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

      bool operator<(const RGBPixel& other) const noexcept;
    };

    // Checks if the first pixel is smaller than the second pixel. Uses the dimension to compare the
    // pixels. A dimension value of 0 corresponds to the red channel, a dimension of 1 corresponds
    // to the green channel and a dimension of 2 corresponds to the blue channel. The precondition
    // is that dimension must be between 0 and 2 inclusive. If the channel of the specified
    // dimension is equal, operator< is used to resolve the tie.
    bool RGB_smaller_by_dim(const RGBPixel& first, const RGBPixel& second,
                            std::size_t dimension) noexcept;

    // Computes the square of the euclidian distance between the two pixels. The two pixels are
    // treated as two vectors in R^3.
    std::size_t RGB_euclidian_squared(const RGBPixel& first, const RGBPixel& second) noexcept;

    // Computes the square of the distance between the specified dimension of the two pixels.
    // Precondition is that dimension should be between 0 and 2 inclusive.
    std::size_t RGB_dim_distance_squared(const RGBPixel& first, const RGBPixel& second,
                                         std::size_t dimension) noexcept;
  }  // namespace image
}  // namespace gif