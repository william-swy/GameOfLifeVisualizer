#include "ppn.h"

#include <algorithm>
#include <climits>

namespace gif {
  namespace ppn {

    std::vector<char> ppn_threshold(std::vector<unsigned char>& data, ImageFormat img_format,
                                    TargetFormat target_format) noexcept {
      return std::vector<char>();
    }

    PPNThreshold::PPNThreshold(const std::vector<unsigned char>& data, ImageFormat img_format,
                               TargetFormat target_format) noexcept {
      const std::size_t bin_count = img_format == ImageFormat::RGB24 ? 4096 : 65536;
      const std::size_t data_step_size = img_format == ImageFormat::RGB24 ? 3 : 4;
      has_alpha = img_format == ImageFormat::RGB24;
      bins = std::vector<Bin>(bin_count);

      for (std::size_t idx = 0; idx < data.size(); idx += data_step_size) {
        // For now assume branch predictor is very good
        if (img_format == ImageFormat::RGB24 && target_format == TargetFormat::RGB12) {
          const auto red = data[idx + 0];
          const auto green = data[idx + 1];
          const auto blue = data[idx + 2];
          const auto index = RGB24_to_RGB12(red, green, blue);

          bins[index].red_channel_avg += red;
          bins[index].green_channel_avg += green;
          bins[index].blue_channel_avg += blue;
          bins[index].pixel_count++;

        } else if (img_format == ImageFormat::RGB24 && target_format == TargetFormat::RGBA16) {
          // TODO
        } else if (img_format == ImageFormat::ARGB32 && target_format == TargetFormat::RGB12) {
          // TODO
        } else if (img_format == ImageFormat::ARGB32 && target_format == TargetFormat::RGBA16) {
          // TODO
        }
        // Execution should never reach here
      }

      // Compute average
      // Average is computed regardless if there is an alpha component or not as the average of a
      // sum of zero is still zero.
      std::for_each(bins.begin(), bins.end(), [](Bin& bin) -> void {
        if (bin.pixel_count > 0) {
          const auto scaling_fac = 1.0 / static_cast<double>(bin.pixel_count);
          bin.alpha_channel_avg *= scaling_fac;
          bin.red_channel_avg *= scaling_fac;
          bin.green_channel_avg *= scaling_fac;
          bin.blue_channel_avg *= scaling_fac;
        }
      });

      // Move all empty bins to the end of the vector and remove
      std::size_t max_bins = 0;
      for (std::size_t idx = 0; idx < bins.size(); ++idx) {
        const auto bin = bins[idx];
        if (bin.pixel_count != 0) {
          bins[max_bins++] = bin;
        }
      }
      bins.resize(max_bins + 1);

      // Connect next and previous indicies and set MSE
      for (std::size_t idx = 0; idx < bins.size() - 1; idx++) {
        bins[idx].next_idx = idx + 1;
        bins[idx + 1].prev_idx = idx;
        bins[idx].distance_to_next = MSE_increase(bins[idx], bins[idx + 1]);
      }

      bin_heap = std::vector<std::size_t>(bins.size());
      for (std::size_t idx = 0; idx < bins.size(); idx++) {
        bin_heap[idx] = idx;
        bins[idx].heap_idx = static_cast<long long>(idx);
      }

      build_heap();
    }

    void PPNThreshold::merge_to_size(std::size_t size) noexcept {
      while (bin_heap.size() > size) {
        merge();
      }
    }

    void PPNThreshold::merge() noexcept {
      auto& least_bin = bins[bin_heap[0]];
      auto& prev_least_bin = bins[least_bin.prev_idx];
      const auto& merge_bin = bins[least_bin.next_idx];

      // Update values for least_bin
      least_bin.red_channel_avg = (least_bin.red_channel_avg * least_bin.pixel_count
                                   + merge_bin.red_channel_avg * merge_bin.pixel_count)
                                  / (least_bin.pixel_count + merge_bin.pixel_count);

      least_bin.green_channel_avg = (least_bin.green_channel_avg * least_bin.pixel_count
                                     + merge_bin.green_channel_avg * merge_bin.pixel_count)
                                    / (least_bin.pixel_count + merge_bin.pixel_count);

      least_bin.blue_channel_avg = (least_bin.blue_channel_avg * least_bin.pixel_count
                                    + merge_bin.blue_channel_avg * merge_bin.pixel_count)
                                   / (least_bin.pixel_count + merge_bin.pixel_count);

      least_bin.alpha_channel_avg = (least_bin.alpha_channel_avg * least_bin.pixel_count
                                     + merge_bin.alpha_channel_avg * merge_bin.pixel_count)
                                    / (least_bin.pixel_count + merge_bin.pixel_count);

      least_bin.pixel_count += merge_bin.pixel_count;

      least_bin.distance_to_next = MSE_increase(least_bin, bins[merge_bin.next_idx]);

      // Update values for prev_least_bin
      prev_least_bin.distance_to_next = MSE_increase(least_bin, prev_least_bin);

      // Remove merged bin from heap
      const auto merge_bin_idx = merge_bin.heap_idx;
      swap_elem(merge_bin.heap_idx, bin_heap.size() - 1);
      bin_heap.pop_back();

      // Update heap
      heapify_down(merge_bin_idx);
      heapify_down(prev_least_bin.heap_idx);
      heapify_down(0);
    }

    void PPNThreshold::swap_elem(std::size_t first_idx, std::size_t second_idx) noexcept {
      auto& first_bin = bins[bin_heap[first_idx]];
      auto& second_bin = bins[bin_heap[second_idx]];

      first_bin.heap_idx = second_idx;
      second_bin.heap_idx = first_idx;

      std::swap(bin_heap[first_idx], bin_heap[second_idx]);
    }

    void PPNThreshold::build_heap() noexcept {
      for (long long idx = bins.size() / 2; idx >= 0; idx--) {
        heapify_down(idx);
      }
    }

    void PPNThreshold::heapify_down(std::size_t idx) noexcept {
      if (has_child(idx)) {
        const auto max_priority_idx = max_priority_child(idx);
        const auto& max_priority_bin = bins[bin_heap[max_priority_idx]];
        const auto& curr_bin = bins[bin_heap[idx]];
        if (max_priority_bin < curr_bin) {
          swap_elem(max_priority_idx, idx);
          heapify_down(max_priority_idx);
        }
      }
    }

    void PPNThreshold::heapify_up(std::size_t idx) noexcept {
      if (idx == 0) {
        return;
      }
      const auto parent_idx = parent(idx);
      const auto& parent_bin = bins[bin_heap[parent_idx]];
      const auto& curr_bin = bins[bin_heap[idx]];
      if (curr_bin < parent_bin) {
        swap_elem(parent_idx, idx);
        heapify_up(parent_idx);
      }
    }

    bool PPNThreshold::has_child(std::size_t idx) const noexcept {
      const auto left = left_child(idx);
      const auto right = right_child(idx);
      return (left < bins.size()) || (right < bins.size());
    }

    std::size_t PPNThreshold::max_priority_child(std::size_t idx) const noexcept {
      const auto left = left_child(idx);
      const auto right = right_child(idx);

      // There is a guarentee that the left child exists but there is not a guarentee that the right
      // child exists.
      if (right < bins.size()) {
        if (bins[right] < bins[left]) {
          return right;
        }
      }
      return left;
    }

    std::size_t PPNThreshold::left_child(std::size_t idx) const noexcept { return 2 * idx + 1; }

    std::size_t PPNThreshold::right_child(std::size_t idx) const noexcept { return 2 * (idx + 1); }

    std::size_t PPNThreshold::parent(std::size_t idx) const noexcept { return (idx - 1) / 2; }
  }  // namespace ppn
}  // namespace gif
