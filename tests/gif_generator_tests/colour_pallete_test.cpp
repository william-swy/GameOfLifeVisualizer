#include "image/colour_pallete.h"

#include <catch2/catch.hpp>
#include <utility>
#include <vector>

TEST_CASE("nearest_neighbour size 1", "[weight=1][part=colour_pallete]") {
  std::vector<gif::image::RGBPixel> test_pixels = {
      {100, 50, 200},
  };

  const gif::image::ColourPallete test_pallete(std::move(test_pixels));
  const auto result = test_pallete.find_nearest_neighbour({30, 20, 10});
  const auto expected = gif::image::RGBPixel(100, 50, 200);

  REQUIRE(result.red == expected.red);
  REQUIRE(result.green == expected.green);
  REQUIRE(result.blue == expected.blue);
}

TEST_CASE("nearest_neighbour no other branch search", "[weight=1][part=colour_pallete]") {
  const gif::image::RGBPixel search_pixel(20, 10, 100);
  const gif::image::RGBPixel result_pixel(20, 30, 100);

  std::vector<gif::image::RGBPixel> test_pixels = {
      {50, 40, 100}, {20, 30, 100}, {70, 20, 100}, {40, 70, 100}, {80, 10, 100}, {90, 60, 100},
  };
  const gif::image::ColourPallete test_pallete(std::move(test_pixels));

  const auto search_result = test_pallete.find_nearest_neighbour(search_pixel);

  REQUIRE(search_result.red == result_pixel.red);
  REQUIRE(search_result.green == result_pixel.green);
  REQUIRE(search_result.blue == result_pixel.blue);
}

TEST_CASE("nearest_neighbour other branch search", "[weight=1][part=colour_pallete]") {
  const gif::image::RGBPixel search_pixel(60, 70, 100);
  const gif::image::RGBPixel result_pixel(40, 70, 100);

  std::vector<gif::image::RGBPixel> test_pixels = {
      {50, 40, 100}, {20, 30, 100}, {70, 20, 100}, {40, 70, 100}, {80, 10, 100}, {90, 60, 100},
  };
  const gif::image::ColourPallete test_pallete(std::move(test_pixels));

  const auto search_result = test_pallete.find_nearest_neighbour(search_pixel);

  REQUIRE(search_result.red == result_pixel.red);
  REQUIRE(search_result.green == result_pixel.green);
  REQUIRE(search_result.blue == result_pixel.blue);
}

TEST_CASE("nearest_neighbour identical value", "[weight=1][part=colour_pallete]") {
  gif::image::RGBPixel search_pixel(240, 160, 254);

  std::vector<gif::image::RGBPixel> test_pixels = {
      {8, 128, 212},   {68, 246, 97},   {96, 9, 16},     {160, 62, 50},   {160, 146, 223},
      {80, 138, 10},   {64, 6, 2},      {55, 205, 164},  {71, 13, 183},   {145, 172, 62},
      {183, 160, 188}, {149, 187, 137}, {148, 109, 167}, {223, 181, 196}, {3, 235, 252},
      {26, 234, 96},   {0, 83, 90},     {161, 91, 56},   {211, 144, 97},  {240, 160, 254},
      {242, 225, 174},
  };

  const gif::image::ColourPallete test_pallete(std::move(test_pixels));
  const auto search_result = test_pallete.find_nearest_neighbour(search_pixel);

  REQUIRE(search_result.red == search_pixel.red);
  REQUIRE(search_result.green == search_pixel.green);
  REQUIRE(search_result.blue == search_pixel.blue);
}

TEST_CASE("nearestNeighour big search", "[weight=1][part=colour_pallete]") {
  gif::image::RGBPixel search_pixel(222, 195, 64);
  gif::image::RGBPixel result_pixel(207, 149, 102);

  std::vector<gif::image::RGBPixel> test_pixels = {
      {207, 149, 102}, {83, 109, 216},  {19, 111, 39},   {163, 159, 59}, {199, 22, 155},
      {17, 216, 220},  {231, 100, 126}, {230, 231, 216}, {48, 222, 148}, {10, 249, 133},
      {142, 46, 54},   {202, 45, 245},  {117, 63, 145},  {121, 132, 36},
  };

  const gif::image::ColourPallete test_pallete(std::move(test_pixels));
  const auto search_result = test_pallete.find_nearest_neighbour(search_pixel);

  REQUIRE(search_result.red == result_pixel.red);
  REQUIRE(search_result.green == result_pixel.green);
  REQUIRE(search_result.blue == result_pixel.blue);
}