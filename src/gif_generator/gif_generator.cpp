#include "gif_generator.h"

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>

#include "colour_kd_tree.h"
#include "gif.h"

namespace gif {
  // Some private helper functions
  //namespace {
  //  void gif_append_number_hex(std::vector<char>& bin_data, unsigned short num) noexcept {
  //    bin_data.push_back(static_cast<char>(static_cast<unsigned int>(num) & 0x00FF));
  //    bin_data.push_back(static_cast<char>((static_cast<unsigned int>(num) >> 8) & 0x00FF));
  //  }

  //  void gif_append_rbg_color(std::vector<char>& bin_data,
  //                            std::tuple<char, char, char> colour) noexcept {
  //    auto& [red, green, blue] = colour;
  //    bin_data.push_back(red);
  //    bin_data.push_back(green);
  //    bin_data.push_back(blue);
  //  }

  //  void gif_append_mass_data(std::vector<char>& bin_data, const char* append_data,
  //                            std::size_t data_len) {
  //    const auto curr_vec_size = bin_data.size();
  //    bin_data.resize(curr_vec_size + data_len);
  //    // Paste the contents of the string to the end of the current data of vector
  //    std::memcpy(bin_data.data() + curr_vec_size, append_data, data_len);
  //  }

  //  void gif_append_string(std::vector<char>& bin_data, std::string& str) noexcept {
  //    gif_append_mass_data(bin_data, str.data(), str.size());
  //  }

  //  void gif_append_vector(std::vector<char>& bin_data, const std::vector<char>& append_data) {
  //    gif_append_mass_data(bin_data, append_data.data(), append_data.size());
  //  }

  //  void gif_start_data(std::vector<char>& bin_data, unsigned short width,
  //                      unsigned short height) noexcept {
  //    // Write out screen descriptor
  //    std::string descriptor("GIF89a");
  //    gif_append_string(bin_data, descriptor);

  //    // Write out the width
  //    gif_append_number_hex(bin_data, width);

  //    // Write out the height
  //    gif_append_number_hex(bin_data, height);

  //    // Indicate there is a global colour palette of two entries
  //    bin_data.push_back(0xf0);

  //    // background color
  //    bin_data.push_back(0);

  //    // Specify that pixels are square
  //    bin_data.push_back(0);

  //    // Colours for global colour palette
  //    // First colour is black
  //    gif_append_rbg_color(bin_data, {0, 0, 0});
  //    // Second colour is black
  //    gif_append_rbg_color(bin_data, {0, 0, 0});

  //    // Always going to indicate that there is an animation even if there is only one frame hence
  //    // an animation header is always going to be added
  //    bin_data.push_back(0x21);
  //    bin_data.push_back(0xff);
  //    bin_data.push_back(11);
  //    std::string app_name("NETSCAPE2.0");
  //    gif_append_string(bin_data, app_name);
  //    bin_data.push_back(3);

  //    bin_data.push_back(1);
  //    // Indefinate loop
  //    bin_data.push_back(0);
  //    bin_data.push_back(0);

  //    // Terminator
  //    bin_data.push_back(0);
  //  }

  //  // Meant for the first image in the sequence
  //  void gif_image_data(std::vector<char>& bin_data, const gif::Image& curr_img) noexcept {
  //    gif_append_vector(bin_data, curr_img.LZW_compress());
  //  }

  //  // Meant for every image after the first image in the sequence
  //  void gif_image_data(std::vector<char>& bin_data, const gif::Image& curr_img,
  //                      const gif::Image& prev_img) noexcept {
  //    gif_append_vector(bin_data, curr_img.LZW_compress(prev_img));
  //  }

  //  void gif_end_data(std::vector<char>& bin_data) noexcept {
  //    // Signal EOF
  //    bin_data.push_back(0x3b);
  //  }
  //}  // namespace

  // Consists of three steps: Write the header, write all the images and write the EOF
  void write_to_gif(const std::vector<Image>& image_sequence,
                    const std::string& file_name) noexcept {
    //std::vector<char> bin_data;

    //// Since it is assumed that each image has same dimensions and format, thus the first image is
    //// used to get information about the entire list of images.
    //gif_start_data(bin_data, image_sequence[0].width, image_sequence[0].height);

    //// Write each image to file
    //for (std::size_t img_idx = 0; img_idx < image_sequence.size(); img_idx++) {
    //  if (img_idx == 0) {
    //    gif_image_data(bin_data, image_sequence[img_idx]);
    //  } else {
    //    gif_image_data(bin_data, image_sequence[img_idx], image_sequence[img_idx - 1]);
    //  }
    //}

    //// Write to file
    //std::ofstream output_file(file_name, std::ios::binary);
    //std::ostreambuf_iterator<char> output(output_file);
    //std::copy(bin_data.begin(), bin_data.end(), output);
    int delay = 100;
    std::size_t width = image_sequence[0].width;
    std::size_t height = image_sequence[0].height;
    GifWriter g;
    GifBegin(&g, file_name.data(), width, height, delay);
    for (const auto& img : image_sequence) {
      GifWriteFrame(&g, img.pixel_data.data(), width, height, delay);
    }
    GifEnd(&g);
  }
}  // namespace gif
