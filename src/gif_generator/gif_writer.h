#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "image/image_frame.h"

namespace gif {
  class GifWriter {
  public:
    GifWriter() = default;

    void write_start_data(unsigned short width, unsigned short height) noexcept;

    void write_image_frame(const image::ImageFrame& img) noexcept;

    void write_end_data() noexcept;

    [[nodiscard]] const std::vector<unsigned char>& get_buffer() const noexcept;

  private:
    std::vector<unsigned char> buffer;

    void append_data(unsigned short num, bool little_endian = true) noexcept;

    void append_data(std::tuple<char, char, char> colour) noexcept;

    void append_data(std::vector<unsigned char>& bin_data) noexcept;

    void append_data(std::string& str) noexcept;

    void append_data(const unsigned char* append_data, std::size_t data_len) noexcept;
  };
}  // namespace gif