#include "image/image_formats.h"

#include <array>
#include <catch2/catch.hpp>

TEST_CASE("RGB24 to RGB12", "[part=image_formats]") {
  SECTION("red channel only, less than 16", "[weight=1]") {
    constexpr unsigned char red = 0x0F;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x00;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    // The red should be bitshifted that it becomes zero
    REQUIRE(result == 0b0000000000000000);
  }

  SECTION("red channel only, greater than 16", "[weight=1]") {
    constexpr unsigned char red = 0x6E;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x00;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000011000000000);
  }

  SECTION("green channel only, less than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x05;
    constexpr unsigned char blue = 0x00;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000000000000000);
  }

  SECTION("green channel only, greater than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x40;
    constexpr unsigned char blue = 0x00;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000000001000000);
  }

  SECTION("blue channel only, less than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x03;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000000000000000);
  }

  SECTION("blue channel only, greater than 16", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0xFF;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000000000001111);
  }

  SECTION("red green channel only", "[weight=1]") {
    constexpr unsigned char red = 0x8A;
    constexpr unsigned char green = 0x34;
    constexpr unsigned char blue = 0x00;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000100000110000);
  }

  SECTION("red blue channel only", "[weight=1]") {
    constexpr unsigned char red = 0x07;
    constexpr unsigned char green = 0x00;
    constexpr unsigned char blue = 0x12;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000000000000001);
  }

  SECTION("green blue channel only", "[weight=1]") {
    constexpr unsigned char red = 0x00;
    constexpr unsigned char green = 0x78;
    constexpr unsigned char blue = 0x36;

    const auto result = gif::RGB24_to_RGB12(red,green,blue);;

    REQUIRE(result == 0b0000000001110011);
  }

  SECTION("assorted combinations", "[weight=1]") {
    struct combination {
      unsigned char red;
      unsigned char green;
      unsigned char blue;
      unsigned short result;
    };

    constexpr std::array<combination, 10> cases = {{{0xaa, 0x58, 0x0a, 0b0000101001010000},
                                                    {0x5a, 0xb0, 0x7f, 0b0000010110110111},
                                                    {0xda, 0x65, 0xb3, 0b0000110101101011},
                                                    {0x18, 0x3f, 0xfb, 0b0000000100111111},
                                                    {0xa0, 0x61, 0xca, 0b0000101001101100},
                                                    {0x45, 0xd3, 0x98, 0b0000010011011001},
                                                    {0x7d, 0x61, 0x57, 0b0000011101100101},
                                                    {0xb1, 0xc9, 0xdb, 0b0000101111001101},
                                                    {0x49, 0x3b, 0x6f, 0b0000010000110110},
                                                    {0x53, 0xa5, 0x73, 0b0000010110100111}}};

    for (const auto& comb : cases) {
      const auto result = gif::RGB24_to_RGB12(comb.red, comb.green, comb.blue);
      REQUIRE(result == comb.result);
    }
  }
}
