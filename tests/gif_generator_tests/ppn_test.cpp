#include "image/ppn.h"

#include <catch2/catch.hpp>

TEST_CASE("No merging needed", "[part=ppn]") {
  SECTION("one bin one pixel", "[weight=1]") {
    constexpr std::size_t size = 3;
    const unsigned char data[size] = {0xFF, 0x45, 0x50};
    auto ppn = gif::image::PPNThreshold(gif::image::ImageFrame(data, size, 1, 1),
                                              gif::image::TargetFormat::RGB12);

    const auto pallete = ppn.merge_to_size(1);

    REQUIRE(pallete.data.size() == 1);
    REQUIRE(pallete.data[0].red == 0x0F);
    REQUIRE(pallete.data[0].green == 0x04);
    REQUIRE(pallete.data[0].blue == 0x05);
  }

  SECTION("one bin multiple pixels", "[weight=1]") {}

  SECTION("multiple bin one pixel each", "[weight=1]") {}

  SECTION("multiple bin multiple pixels each", "[weight=1]") {}
}

TEST_CASE("Merging needed", "[part=ppn]") {}