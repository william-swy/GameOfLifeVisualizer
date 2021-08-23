#include "image/ppn.h"

#include <array>
#include <catch2/catch.hpp>

TEST_CASE("No merging needed", "[part=ppn]") {
  SECTION("one bin one pixel", "[weight=1]") {
    // One pixel one bin, no merging needed
    constexpr std::size_t size = 3;
    constexpr std::array<unsigned char, size> data = {0xFF, 0x45, 0x50};
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 1, 1),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(1);

    REQUIRE(pallete.data.size() == 1);
    REQUIRE(pallete.data[0].red == 0x0F);
    REQUIRE(pallete.data[0].green == 0x04);
    REQUIRE(pallete.data[0].blue == 0x05);
  }

  SECTION("one bin multiple pixels", "[weight=1]") {
    // 3 pixels, all fit in one bin, no merging needed
    constexpr std::size_t size = 9;
    constexpr std::array<unsigned char, size> data
        = {0xFF, 0x45, 0x50, 0xF1, 0x46, 0x51, 0xF0, 0x41, 0x56};
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 3, 1),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(1);
    REQUIRE(pallete.data.size() == 1);
    REQUIRE(pallete.data[0].red == 0x0F);
    REQUIRE(pallete.data[0].green == 0x04);
    REQUIRE(pallete.data[0].blue == 0x05);
  }

  SECTION("multiple bin one pixel each", "[weight=1]") {
    // 5 pixels, all different bins, no merging needed
    constexpr std::size_t size = 15;
    constexpr std::array<unsigned char, size> data = {
        0xFF, 0x45, 0x50,  // bin 1
        0xA1, 0x46, 0x51,  // bin 2
        0xF0, 0x51, 0x56,  // bin 3
        0x01, 0x32, 0xAA,  // bin 4
        0xEE, 0x34, 0x5C   // bin 5
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 5, 1),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(5);
    REQUIRE(pallete.data.size() == 5);

    // Should be ordered via a zero based min heap using MSE_increase
    std::array<gif::image::RGBPixel, 5> expected{{{0x0F, 0x04, 0x05},
                                                  {0x0A, 0x04, 0x05},
                                                  {0x0E, 0x03, 0x05},
                                                  {0x00, 0x03, 0x0A},
                                                  {0x0F, 0x05, 0x05}

    }};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }

  SECTION("multiple bin multiple pixels each", "[weight=1]") {
    // 8 pixels, fits into 3 different bins, no merging needed
    constexpr std::size_t size = 24;
    constexpr std::array<unsigned char, size> data = {
        0xD3, 0x21, 0x08,  // bin 1
        0xD4, 0x26, 0x0E,  // bin 1
        0x12, 0x45, 0x90,  // bin 2
        0x67, 0x98, 0x23,  // bin 3
        0x17, 0x48, 0x95,  // bin 2
        0xD9, 0x21, 0x03,  // bin 1
        0x69, 0x91, 0x25,  // bin 3
        0x63, 0x95, 0x23   // bin 3
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 2, 4),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(3);
    REQUIRE(pallete.data.size() == 3);

    std::array<gif::image::RGBPixel, 3> expected{
        {{0x01, 0x04, 0x09}, {0x06, 0x09, 0x2}, {0x0D, 0x02, 0x0}}};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }
}

TEST_CASE("Merging needed", "[part=ppn]") {
  SECTION("merge once, one pixel per bin, merge bin middle", "[weight=1]") {
    // 4 pixels, merge to 3 pixels
    constexpr std::size_t size = 12;
    constexpr std::array<unsigned char, size> data = {
        0xE4, 0x3F, 0x51,  // Pixel 1
        0x41, 0xC5, 0x23,  // Pixel 2
        0x90, 0x8A, 0x45,  // Pixel 3
        0x01, 0x21, 0x89   // Pixel 4
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 2, 2),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(3);
    REQUIRE(pallete.data.size() == 3);

    std::array<gif::image::RGBPixel, 3> expected{
        {{0x6, 0xA, 0x3}, {0x0, 0x2, 0x8}, {0xE, 0x3, 0x5}}};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }

  SECTION("merge once, one pixel per bin, merge bin front", "[weight=1]") {
    // 4 pixels, merge to 3 pixels
    constexpr std::size_t size = 12;
    constexpr std::array<unsigned char, size> data = {
        0x84, 0x2F, 0x12,  // Pixel 1
        0x19, 0x12, 0x34,  // Pixel 2
        0x96, 0x81, 0x19,  // Pixel 3
        0x12, 0x18, 0x28   // Pixel 4
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 2, 2),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(3);
    REQUIRE(pallete.data.size() == 3);

    std::array<gif::image::RGBPixel, 3> expected{
        {{0x8, 0x2, 0x1}, {0x1, 0x1, 0x2}, {0x9, 0x8, 0x1}}};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }

  SECTION("merge once, one pixel per bin, merge bin end", "[weight=1]") {
    // 4 pixels, merge to 3 pixels
    constexpr std::size_t size = 12;
    constexpr std::array<unsigned char, size> data = {
        0xF1, 0x98, 0x23,  // Pixel 1
        0xFF, 0xA1, 0x23,  // Pixel 2
        0x90, 0x8A, 0x45,  // Pixel 3
        0x01, 0x21, 0x89   // Pixel 4
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 2, 2),
                                        gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(3);
    REQUIRE(pallete.data.size() == 3);

    std::array<gif::image::RGBPixel, 3> expected{
        {{0x9, 0x8, 0x4}, {0x0, 0x2, 0x8}, {0xF, 0xA, 0x2}}};
  }

  SECTION("merge once, assorted pixel count per bin", "[weight=1]") {
    // 9 pixels, 5 bins, merge to 4 pixels
    constexpr std::size_t size = 27;
    constexpr std::array<unsigned char, size> data = {
        0xF1, 0x98, 0x23,  // Pixel 1, bin 1
        0xFF, 0xA1, 0x23,  // Pixel 2, bin 2
        0x90, 0x8A, 0x45,  // Pixel 3, bin 3
        0x01, 0x21, 0x89,  // Pixel 4, bin 4
        0xF0, 0x95, 0x29,  // Pixel 5, bin 1
        0xFF, 0x90, 0x25,  // Pixel 6, bin 1
        0x91, 0x8C, 0x4A,  // Pixel 7, bin 3
        0xFC, 0xAA, 0x2F,  // Pixel 8, bin 2
        0x45, 0x23, 0xE1   // Pixel 9, bin 5
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 3, 3),
                                        gif::image::TargetFormat::RGB12);

    constexpr std::size_t target_size = 4;
    const auto pallete = ppn.merge_to_size(target_size);
    REQUIRE(pallete.data.size() == target_size);

    std::array<gif::image::RGBPixel, target_size> expected{
        {{0x0, 0x2, 0x8}, {0x4, 0x2, 0xE}, {0x9, 0x8, 0x4}, {0xF, 0x9, 0x2}}};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }

  SECTION("merge multiple, one pixel per bin", "[weight=1]") {
    // 7 pixels, 7 bins, merge 3 times to a total of 4 bins
    constexpr std::size_t size = 21;
    constexpr std::array<unsigned char, size> data = {
        0x00, 0xF3, 0x81,  // pixel 1
        0x1A, 0x18, 0x11,  // pixel 2
        0xF5, 0xEF, 0x95,  // pixel 3
        0x3C, 0x29, 0x13,  // pixel 4
        0xEE, 0xDF, 0xA6,  // pixel 5
        0x58, 0x30, 0x23,  // pixel 6
        0xDB, 0xC2, 0xB1   // pixel 7
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 7, 1),
                                        gif::image::TargetFormat::RGB12);

    constexpr std::size_t target_size = 4;
    const auto pallete = ppn.merge_to_size(target_size);
    REQUIRE(pallete.data.size() == target_size);

    std::array<gif::image::RGBPixel, target_size> expected{
        {{0x2, 0x1, 0x1}, {0x0, 0xF, 0x8}, {0xE, 0xD, 0xA}, {0x5, 0x3, 0x2}}};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }

  SECTION("merge multiple, assorted pixel count per bin", "[weight=1]") {
    // 12 pixels, 7 bins, merge 2 times to a total of 5 bins
    constexpr std::size_t size = 36;
    constexpr std::array<unsigned char, size> data = {
        0x00, 0xF3, 0x81,  // pixel 1,  bin 1
        0x0F, 0xF1, 0x85,  // pixel 2,  bin 1
        0xF5, 0xEF, 0x95,  // pixel 3,  bin 2
        0x3C, 0x29, 0x13,  // pixel 4,  bin 3
        0xEE, 0xDF, 0xA6,  // pixel 5,  bin 4
        0x38, 0x20, 0x13,  // pixel 6,  bin 3
        0xDB, 0xC2, 0xB1,  // pixel 7,  bin 5
        0x10, 0xD3, 0x21,  // pixel 8,  bin 6
        0x4A, 0x58, 0x61,  // pixel 9,  bin 7
        0xD5, 0xCF, 0xB5,  // pixel 10, bin 5
        0xDC, 0xC9, 0xB3,  // pixel 11, bin 5
        0x4E, 0x5F, 0x66   // pixel 12, bin 7
    };
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data.data(), size, 3, 4),
                                        gif::image::TargetFormat::RGB12);

    constexpr std::size_t target_size = 5;
    const auto pallete = ppn.merge_to_size(target_size);
    REQUIRE(pallete.data.size() == target_size);

    std::array<gif::image::RGBPixel, target_size> expected{
        {{0x0, 0xF, 0x8}, {0x1, 0xD, 0x2}, {0x3, 0x2, 0x1}, {0x4, 0x5, 0x6}, {0xD, 0xC, 0xA}}};

    for (std::size_t idx = 0; idx < expected.size(); idx++) {
      REQUIRE(pallete.data[idx].red == expected[idx].red);
      REQUIRE(pallete.data[idx].green == expected[idx].green);
      REQUIRE(pallete.data[idx].blue == expected[idx].blue);
    }
  }
}