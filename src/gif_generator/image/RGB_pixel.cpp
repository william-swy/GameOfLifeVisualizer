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

      const auto channel_OR
          = static_cast<unsigned int>((new_red << 8) | (new_green << 4) | new_blue);

      return {channel_OR, {new_red, new_green, new_blue}};
    }

    std::tuple<unsigned int, RGBPixel> RGBPixel::RGB16() const noexcept {
      const auto new_red = static_cast<unsigned char>(red >> 3);
      const auto new_green = static_cast<unsigned char>(green >> 2);
      const auto new_blue = static_cast<unsigned char>(blue >> 3);

      const auto channel_OR
          = static_cast<unsigned int>((new_red << 11) | (new_green << 5) | new_blue);

      return {channel_OR, {new_red, new_green, new_blue}};
    }

    bool RGBPixel::operator<(const RGBPixel& other) const noexcept {
      if (red < other.red) {
        return true;
      } else if ((red == other.red) && (green < other.green)) {
        return true;
      } else if ((red == other.red) && (green == other.green) && (blue < other.blue)) {
        return true;
      }

      return false;
    }

    bool RGB_smaller_by_dim(const RGBPixel& first, const RGBPixel& second,
                            std::size_t dimension) noexcept {
      if (dimension == 0) {
        if (first.red < second.red) {
          return true;
        } else if (first.red == second.red) {
          return first < second;
        } else {
          return false;
        }
      } else if (dimension == 1) {
        if (first.green < second.green) {
          return true;
        } else if (first.green == second.green) {
          return first < second;
        } else {
          return false;
        }
      } else {
        if (first.blue < second.blue) {
          return true;
        } else if (first.blue == second.blue) {
          return first < second;
        } else {
          return false;
        }
      }
    }

    std::size_t RGB_euclidian_squared(const RGBPixel& first, const RGBPixel& second) noexcept {
      const auto delta_red = RGB_dim_distance_squared(first, second, 0);
      const auto delta_green = RGB_dim_distance_squared(first, second, 1);
      const auto delta_blue = RGB_dim_distance_squared(first, second, 2);

      return delta_red + delta_green + delta_blue;
    }

    std::size_t RGB_dim_distance_squared(const RGBPixel& first, const RGBPixel& second,
                                         std::size_t dimension) noexcept {
      long long distance;
      if (dimension == 0) {
        distance = static_cast<long long>(first.red) - static_cast<long long>(second.red);
      } else if (dimension == 1) {
        distance = static_cast<long long>(first.green) - static_cast<long long>(second.green);
      } else {
        distance = static_cast<long long>(first.blue) - static_cast<long long>(second.blue);
      }
      // Impossible for sign mismatch. Always greater than or equal to 0.
      return static_cast<std::size_t>(distance * distance);
    }
  }  // namespace image
}  // namespace gif
