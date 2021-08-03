#include "image_frame.h"

#include <array>
#include <cstddef>
#include <tuple>
#include <vector>

#include "colour_kd_tree.h"

namespace gif {
  //namespace {
  //  void threshold_no_pixel_match(std::vector<char>& buffer, std::size_t idx,
  //                                std::tuple<int, int, int> colour,
  //                                const colour_kd_tree::ColourKDTree& tree) noexcept {
  //    auto best_diff = 1000000;
  //    auto best_idx = 1;
  //    tree.closest_colour(colour, best_idx, best_diff, 1);
  //    buffer[idx + 0] = tree.red[best_idx];
  //    buffer[idx + 1] = tree.green[best_idx];
  //    buffer[idx + 2] = tree.blue[best_idx];
  //    buffer[idx + 3] = static_cast<char>(best_idx);
  //  }

  //  std::vector<char> threshold_image(const Image& img,
  //                                    const colour_kd_tree::ColourKDTree& tree) noexcept {
  //    std::vector<char> out_buff(img.pixel_data.size(), 0);
  //    for (std::size_t idx = 0; idx < out_buff.size(); idx += 4) {
  //      threshold_no_pixel_match(
  //          out_buff, idx,
  //          {img.pixel_data[idx + 0], img.pixel_data[idx + 1], img.pixel_data[idx + 2]}, tree);
  //    }
  //    return out_buff;
  //  }

  //  std::vector<char> threshold_image(const Image& img, const Image& prev,
  //                                    const colour_kd_tree::ColourKDTree& tree) noexcept {
  //    std::vector<char> out_buff(img.pixel_data.size(), 0);
  //    for (std::size_t idx = 0; idx < out_buff.size(); idx += 4) {
  //      if (img.pixel_data[idx + 0] == prev.pixel_data[idx + 0]
  //          && img.pixel_data[idx + 1] == prev.pixel_data[idx + 1]
  //          && img.pixel_data[idx + 2] == prev.pixel_data[idx + 2]) {
  //        out_buff[idx + 0] = prev.pixel_data[idx + 0];
  //        out_buff[idx + 1] = prev.pixel_data[idx + 1];
  //        out_buff[idx + 2] = prev.pixel_data[idx + 2];
  //        out_buff[idx + 3] = 0;
  //      } else {
  //        threshold_no_pixel_match(
  //            out_buff, idx,
  //            {img.pixel_data[idx + 0], img.pixel_data[idx + 1], img.pixel_data[idx + 2]}, tree);
  //      }
  //    }
  //    return out_buff;
  //  }

  //  std::vector<char> LZW_buff_data(std::vector<char>& img, std::size_t left, std::size_t top,
  //                                  uint32_t width, std::size_t height, std::size_t delay,
  //                                  const colour_kd_tree::ColourKDTree& tree) noexcept {
  //    std::vector<char> buffer;

  //    return buffer;
  //  }
  //}  // namespace
  Image::Image(const unsigned char* byte_data, std::size_t num_bytes, unsigned short width,
               unsigned short height, unsigned char depth, bool has_alpha)
      : pixel_data(), width(width), height(height), depth(depth), has_alpha(has_alpha) {
    pixel_data.resize(num_bytes);
    std::memcpy(pixel_data.data(), byte_data, num_bytes);
  }

  //std::vector<char> Image::LZW_compress() const noexcept {
  //  const std::size_t num_pixels = width * height;
  //  colour_kd_tree::ColourKDTree tree(pixel_data, num_pixels, depth);
  //  std::vector<char> pixel_buffer(pixel_data.size(), 0);
  //  threshold_image(*this, tree);
  //  return pixel_buffer;
  //}

  //std::vector<char> Image::LZW_compress(const Image& prev_img) const noexcept {
  //  const std::size_t num_pixels = num_changed_pixels(prev_img);
  //  colour_kd_tree::ColourKDTree tree{pixel_data, num_pixels, depth};
  //  std::vector<char> pixel_buffer(pixel_data.size(), 0);
  //  threshold_image(*this, prev_img, tree);
  //  return pixel_buffer;
  //}

  //std::size_t Image::num_changed_pixels(const Image& prev_img) const noexcept {
  //  std::size_t num_changed = 0;
  //  // Alpha component means 4 bytes per pixel while no alpha means 3 bytes per pixel
  //  std::size_t step_size = has_alpha ? 4 : 3;

  //  for (std::size_t pixel_idx = 0; pixel_idx < pixel_data.size(); pixel_idx += step_size) {
  //    if (prev_img.pixel_data[pixel_idx + 0] != pixel_data[pixel_idx + 0]
  //        || prev_img.pixel_data[pixel_idx + 1] != pixel_data[pixel_idx + 1]
  //        || prev_img.pixel_data[pixel_idx + 2] != pixel_data[pixel_idx + 2]) {
  //      num_changed++;
  //    }
  //  }
  //  return num_changed;
  //}
}  // namespace gif