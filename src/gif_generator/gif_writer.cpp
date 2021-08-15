#include "gif_writer.h"

void gif::GifWriter::write_start_data(unsigned short width, unsigned short height) noexcept {
  // screen descriptor
  std::string descriptor("GIF89a");
  append_data(descriptor);

  // width
  append_data(width);

  // height
  append_data(height);

  // Indicate there is a global colour palette of two entries
  buffer.push_back(0xf0);

  // background color
  buffer.push_back(0x00);

  // Specify that pixels are square
  buffer.push_back(0x00);

  // Colours for global colour palette
  // First colour is black
  append_data({0, 0, 0});
  // Second colour is white
  append_data({255, 255, 255});

  // Always going to indicate that there is an animation even if there is only one frame hence
  // an animation header is always going to be added
  buffer.push_back(0x21);             // Extension label
  buffer.push_back(0xff);             // Application extension label
  buffer.push_back(0x0B);             // Block size
  std::string app_id("NETSCAPE2.0");  // Application identifier + Application auth code
  append_data(app_id);
  buffer.push_back(0x03);  // sub-block data size

  buffer.push_back(0x01);  // sub-block id
  // Indefinate loop
  buffer.push_back(0x00);
  buffer.push_back(0x00);

  // Terminator
  buffer.push_back(0x0);
}

void gif::GifWriter::write_image_frame(const ImageFrame& img) noexcept {
  // Graphics control extension
  constexpr unsigned short delay_time = 100;  // Time in hundredth of second
  constexpr unsigned char trans_idx = 0;
  buffer.push_back(0x21);   // Extension introducer
  buffer.push_back(0xf9);   // Graphics control label
  buffer.push_back(0x04);   // Block size
  buffer.push_back(0x05);   // Do no dispose of previous frame. Transparent index is given
  append_data(delay_time);  // Delay time
  buffer.push_back(trans_idx);
  buffer.push_back(0x0);  // Terminator

  // Image descriptor
  constexpr unsigned short left_pos = 0;
  constexpr unsigned short top_pos = 0;
  buffer.push_back(0x2C);                  // Image seperator
  append_data(left_pos);                   // Image left position
  append_data(top_pos);                    // Image top position
  append_data(img.width);                  // Image width
  append_data(img.height);                 // Image height
  buffer.push_back(0x80 + img.depth - 1);  // Local colour table present. 2^depth entries
}

void gif::GifWriter::write_end_data() noexcept {
  // Signal EOF
  buffer.push_back(0x3b);
}

const std::vector<unsigned char>& gif::GifWriter::get_buffer() const noexcept { return buffer; }

void gif::GifWriter::append_data(unsigned short num, bool little_endian) noexcept {
  const auto least_sig = static_cast<unsigned char>(static_cast<unsigned int>(num) & 0x00FF);
  const auto most_sig = static_cast<unsigned char>((static_cast<unsigned int>(num) >> 8) & 0x00FF);
  if (little_endian) {
    buffer.push_back(least_sig);
    buffer.push_back(most_sig);
  } else {
    buffer.push_back(most_sig);
    buffer.push_back(least_sig);
  }
}

void gif::GifWriter::append_data(std::tuple<char, char, char> colour) noexcept {
  const auto& [red, green, blue] = colour;
  buffer.push_back(red);
  buffer.push_back(green);
  buffer.push_back(blue);
}

void gif::GifWriter::append_data(std::vector<unsigned char>& bin_data) noexcept {
  append_data(bin_data.data(), bin_data.size());
}

void gif::GifWriter::append_data(std::string& str) noexcept { append_data(reinterpret_cast<unsigned char*>(str.data()), str.size()); }

inline void gif::GifWriter::append_data(const unsigned char* append_data, std::size_t data_len) noexcept {
  const auto curr_vec_size = buffer.size();
  buffer.resize(curr_vec_size + data_len);
  // Paste the contents of the string to the end of the current data of vector
  std::memcpy(buffer.data() + curr_vec_size, append_data, data_len);
}
