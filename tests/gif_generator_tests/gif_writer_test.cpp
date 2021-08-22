#include "gif_writer.h"

#include <array>
#include <catch2/catch.hpp>
#include <utility>

// Check that the start data of the GIF encoding is correct
void check_start_data(const std::vector<unsigned char>& data, unsigned short width,
                      unsigned short height) {
  constexpr std::size_t expected_len = 38;
  REQUIRE(data.size() == expected_len);

  std::array<unsigned char, expected_len> expected_data{
      {'G',
       'I',
       'F',
       '8',
       '9',
       'a',
       static_cast<unsigned char>(static_cast<unsigned int>(width) & 0x00FF),
       static_cast<unsigned char>((static_cast<unsigned int>(width) & 0xFF00) >> 8),
       static_cast<unsigned char>(static_cast<unsigned int>(height) & 0x00FF),
       static_cast<unsigned char>((static_cast<unsigned int>(height) & 0xFF00) >> 8),
       0xF0,
       0x00,
       0x00,
       0x00,
       0x00,
       0x00,
       0xFF,
       0xFF,
       0xFF,
       0x21,
       0xFF,
       0x0B,
       'N',
       'E',
       'T',
       'S',
       'C',
       'A',
       'P',
       'E',
       '2',
       '.',
       '0',
       0x03,
       0x01,
       0x00,
       0x00,
       0x00}};

  for (auto idx = 0; idx < data.size(); idx++) {
    REQUIRE(data[idx] == expected_data[idx]);
  }
}

TEST_CASE("write start data once", "[weight=1][part=GifWriter]") {
  constexpr unsigned short width = 200;
  constexpr unsigned short height = 500;
  gif::GifWriter writer;
  writer.write_start_data(width, height);
  check_start_data(writer.get_buffer(), width, height);
}

TEST_CASE("write start data many dimensions", "[weight=1][part=GifWriter]") {
  constexpr std::array<std::pair<unsigned short, unsigned short>, 5> dimensions{
      {{100, 50}, {50, 75}, {400, 300}, {1500, 3000}, {7852, 9124}}};

  for (const auto& dim : dimensions) {
    const auto& [width, height] = dim;
    gif::GifWriter writer;
    writer.write_start_data(width, height);
    check_start_data(writer.get_buffer(), width, height);
  }
}