#include "image/RGB_pixel.h"

#include <array>
#include <catch2/catch.hpp>

TEST_CASE("To RGB12", "[part=image_formats]") {
  SECTION("red channel only, less than 16", "[weight=1]") {
    constexpr unsigned char red = 0x0F;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x00;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    // The red should be bitshifted that it becomes zero
    REQUIRE(channel_OR == 0b0000000000000000);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x00);
    REQUIRE(pix.blue == 0x00);
  }

  SECTION("red channel only, greater than 16", "[weight=1]") {
    constexpr unsigned char red = 0x6E;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x00;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000011000000000);
    REQUIRE(pix.red == 0x06);
    REQUIRE(pix.green == 0x00);
    REQUIRE(pix.blue == 0x00);
  }

  SECTION("green channel only, less than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x05;
    constexpr unsigned char blue = 0x00;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000000000000000);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x00);
    REQUIRE(pix.blue == 0x00);
  }

  SECTION("green channel only, greater than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x40;
    constexpr unsigned char blue = 0x00;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000000001000000);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x04);
    REQUIRE(pix.blue == 0x00);
  }

  SECTION("blue channel only, less than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x03;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000000000000000);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x00);
    REQUIRE(pix.blue == 0x00);
  }

  SECTION("blue channel only, greater than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0xFF;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000000000001111);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x00);
    REQUIRE(pix.blue == 0x0F);
  }

  SECTION("red green channel only", "[weight=1]") {
    constexpr unsigned char red = 0x8A;
    constexpr unsigned char green = 0x34;
    constexpr unsigned char blue = 0x00;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000100000110000);
    REQUIRE(pix.red == 0x08);
    REQUIRE(pix.green == 0x03);
    REQUIRE(pix.blue == 0x00);
  }

  SECTION("red blue channel only", "[weight=1]") {
    constexpr unsigned char red = 0x07;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x12;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000000000000001);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x00);
    REQUIRE(pix.blue == 0x01);
  }

  SECTION("green blue channel only", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x78;
    constexpr unsigned char blue = 0x36;
    const gif::image::RGBPixel test_pixel{red, green, blue};
    const auto& [channel_OR, pix] = test_pixel.RGB12();

    REQUIRE(channel_OR == 0b0000000001110011);
    REQUIRE(pix.red == 0x00);
    REQUIRE(pix.green == 0x07);
    REQUIRE(pix.blue == 0x03);
  }

  SECTION("assorted combinations", "[weight=1]") {
    struct combination {
      unsigned char red;
      unsigned char green;
      unsigned char blue;
      unsigned short channel_OR_result;
      unsigned char red_result;
      unsigned char green_result;
      unsigned char blue_result;
    };

    constexpr std::array<combination, 10> cases
        = {{{0xaa, 0x58, 0x0a, 0b0000101001010000, 0x0a, 0x05, 0x00},
            {0x5a, 0xb0, 0x7f, 0b0000010110110111, 0x05, 0x0b, 0x07},
            {0xda, 0x65, 0xb3, 0b0000110101101011, 0x0d, 0x06, 0x0b},
            {0x18, 0x3f, 0xfb, 0b0000000100111111, 0x01, 0x03, 0x0f},
            {0xa0, 0x61, 0xca, 0b0000101001101100, 0x0a, 0x06, 0x0c},
            {0x45, 0xd3, 0x98, 0b0000010011011001, 0x04, 0x0d, 0x09},
            {0x7d, 0x61, 0x57, 0b0000011101100101, 0x07, 0x06, 0x05},
            {0xb1, 0xc9, 0xdb, 0b0000101111001101, 0x0b, 0x0c, 0x0d},
            {0x49, 0x3b, 0x6f, 0b0000010000110110, 0x04, 0x03, 0x06},
            {0x53, 0xa5, 0x73, 0b0000010110100111, 0x05, 0x0a, 0x07}}};

    for (const auto& comb : cases) {
      const gif::image::RGBPixel test_pixel{comb.red, comb.green, comb.blue};
      const auto& [channel_OR, pix] = test_pixel.RGB12();
      REQUIRE(channel_OR == comb.channel_OR_result);
      REQUIRE(pix.red == comb.red_result);
      REQUIRE(pix.green == comb.green_result);
      REQUIRE(pix.blue == comb.blue_result);
    }
  }
}
