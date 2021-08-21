#include "RGB_pixel.h"

namespace gif {
  namespace image {
    RGBPixel::RGBPixel(unsigned char red, unsigned char green, unsigned char blue) noexcept
        : red(red), green(green), blue(blue) {}

    std::tuple<unsigned int, RGBPixel> gif::image::RGBPixel::RGB24() const noexcept {
        // Char is already 8 bits, therefore no shifting is needed
      const auto channel_OR = static_cast<unsigned int>((red << 16) | (green << 8) | blue);  
      return {channel_OR, {red, green, blue}};
    }

    std::tuple<unsigned int, RGBPixel> RGBPixel::RGB12() const noexcept {
      const auto new_red = static_cast<unsigned char>(red >> 4);
      const auto new_green = static_cast<unsigned char>(green >> 4);
      const auto new_blue = static_cast<unsigned char>(blue >> 4);

      const auto channel_OR = static_cast<unsigned int>((new_red << 8) | (new_green << 4) | new_blue);

      return {channel_OR, {new_red, new_green, new_blue}};
    }

    std::tuple<unsigned int, RGBPixel> RGBPixel::RGB16() const noexcept {
      const auto new_red = static_cast<unsigned char>(red >> 3);
      const auto new_green = static_cast<unsigned char>(green >> 2);
      const auto new_blue = static_cast<unsigned char>(blue >> 3);

      const auto channel_OR = static_cast<unsigned int>((new_red << 11) | (new_green << 5) | new_blue);

      return {channel_OR, {new_red, new_green, new_blue}};
    }
  }  // namespace image
}  // namespace gif
