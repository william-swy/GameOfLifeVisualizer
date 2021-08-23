#include "ppn.h"

#include <algorithm>
#include <functional>
#include <limits>

namespace gif {
  namespace image {
    namespace {
      inline void create_bins(std::vector<Bin>& bins, const ImageFrame& img,
                              TargetFormat format) noexcept {
        // Attempt reduce the amount of conditionals in a high iteration loop
        if (format == TargetFormat::RGB12) {
          for (const auto& pixel : img.pixel_data) {
            const auto& [index, new_pixel] = pixel.RGB12();
            bins[index].red_channel_avg += new_pixel.red;
            bins[index].green_channel_avg += new_pixel.green;
            bins[index].blue_channel_avg += new_pixel.blue;
            bins[index].pixel_count++;
          }
        } else if (format == TargetFormat::RGB16) {
          for (const auto& pixel : img.pixel_data) {
            const auto& [index, new_pixel] = pixel.RGB16();
            bins[index].red_channel_avg += new_pixel.red;
            bins[index].green_channel_avg += new_pixel.green;
            bins[index].blue_channel_avg += new_pixel.blue;
            bins[index].pixel_count++;
          }
        } else {
          for (const auto& pixel : img.pixel_data) {
            const auto& [index, new_pixel] = pixel.RGB24();
            bins[index].red_channel_avg += new_pixel.red;
            bins[index].green_channel_avg += new_pixel.green;
            bins[index].blue_channel_avg += new_pixel.blue;
            bins[index].pixel_count++;
          }
        }
      }

      // Compute the average pixel value of each bin
      inline void bin_average(std::vector<Bin>& bins) noexcept {
        std::for_each(bins.begin(), bins.end(), [](Bin& bin) -> void {
          if (bin.pixel_count > 0) {
            const auto scaling_fac = 1.0 / static_cast<double>(bin.pixel_count);
            bin.red_channel_avg *= scaling_fac;
            bin.green_channel_avg *= scaling_fac;
            bin.blue_channel_avg *= scaling_fac;
          }
        });
      }

      // Remove bins where bin matches the condition specified by the function `is_valid_bin`
      inline void remove_bins(std::vector<Bin>& bins,
                              const std::function<bool(const Bin&)>& is_valid_bin) noexcept {
        // Move all empty bins to the end of the vector and remove
        std::size_t max_bins = 0;
        for (std::size_t idx = 0; idx < bins.size(); ++idx) {
          const auto bin = bins[idx];
          if (is_valid_bin(bin)) {
            bins[max_bins++] = bin;
          }
        }
        bins.resize(max_bins);
      }
    }  // namespace

    PPNThreshold::PPNThreshold(const ImageFrame& img, TargetFormat target_format) noexcept {
      constexpr std::size_t bin_count = 4096;
      bins = std::vector<Bin>(bin_count);

      create_bins(bins, img, target_format);

      // Compute average
      bin_average(bins);

      // Remove empty bins
      const auto is_not_empty = [](const Bin& bin) { return bin.pixel_count != 0; };
      remove_bins(bins, is_not_empty);

      // Connect next and previous indicies and set MSE. Size should be always greater than 0.
      for (std::size_t idx = 0; idx < bins.size() - 1; idx++) {
        bins[idx].idx = idx;
        bins[idx].next_idx = static_cast<long long>(idx + 1);
        bins[idx + 1].prev_idx = static_cast<long long>(idx);
        bins[idx].distance_to_next = MSE_increase(bins[idx], bins[idx + 1]);
      }
      // Give last index its appropriate index
      bins[bins.size() - 1].idx = bins.size() - 1;

      bin_heap = std::vector<std::size_t>(bins.size());
      for (std::size_t idx = 0; idx < bins.size(); idx++) {
        bin_heap[idx] = idx;
        bins[idx].heap_idx = static_cast<long long>(idx);
      }

      build_heap();
    }

    ColourPallete PPNThreshold::merge_to_size(std::size_t size) noexcept {
      while (bin_heap.size() > size) {
        merge();
      }

      // Remove all merged bins
      const auto is_not_merged = [](const Bin& bin) { return bin.heap_idx != -1; };
      remove_bins(bins, is_not_merged);

      return ColourPallete(bins);
    }

    void PPNThreshold::merge() noexcept {
      auto& least_bin = bins[bin_heap[0]];
      // Next_idx should never be -1. Always 0 or greater, hence safe indexing.
      auto& merge_bin = bins[static_cast<std::size_t>(least_bin.next_idx)];

      // Merge the least_bin into the target merge_bin
      merge_bin.add_bin(least_bin);

      // Connect previous bin and recalculate merge cost
      if (least_bin.prev_idx != -1) {
        auto& least_bin_prev = bins[static_cast<std::size_t>(least_bin.prev_idx)];
        least_bin_prev.distance_to_next = MSE_increase(least_bin_prev, merge_bin);
        least_bin_prev.next_idx = static_cast<long long>(merge_bin.idx);
        merge_bin.prev_idx = static_cast<long long>(least_bin_prev.idx);

        // Merge cost will always increase so heapify down
        heapify_down(static_cast<std::size_t>(least_bin_prev.heap_idx));
      }

      // Recalculate cost for merging
      if (merge_bin.next_idx != -1) {
        auto& merge_bin_next = bins[static_cast<std::size_t>(merge_bin.next_idx)];
        merge_bin.distance_to_next = MSE_increase(merge_bin, merge_bin_next);
      } else {
        merge_bin.distance_to_next = std::numeric_limits<double>::max();
      }

      // Cost of merging will always increase so heapify down
      heapify_down(static_cast<std::size_t>(merge_bin.heap_idx));

      // Remove least bin. heap_idx should never be -1. Should always be 0 or greater
      swap_elem(static_cast<std::size_t>(least_bin.heap_idx), bin_heap.size() - 1);
      bin_heap.pop_back();
      least_bin.heap_idx = -1;
      heapify_down(0);
    }

    void PPNThreshold::swap_elem(std::size_t first_idx, std::size_t second_idx) noexcept {
      auto& first_bin = bins[bin_heap[first_idx]];
      auto& second_bin = bins[bin_heap[second_idx]];

      first_bin.heap_idx = static_cast<long long>(second_idx);
      second_bin.heap_idx = static_cast<long long>(first_idx);

      std::swap(bin_heap[first_idx], bin_heap[second_idx]);
    }

    void PPNThreshold::build_heap() noexcept {
      const auto upper_bound = bins.size() / 2;
      for (std::size_t idx = 0; idx <= upper_bound; idx++) {
        const auto effective_idx = upper_bound - idx;
        heapify_down(effective_idx);
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

    bool PPNThreshold::has_child(std::size_t idx) const noexcept {
      const auto left = left_child(idx);
      const auto right = right_child(idx);
      return (left < bin_heap.size()) || (right < bin_heap.size());
    }

    std::size_t PPNThreshold::max_priority_child(std::size_t idx) const noexcept {
      const auto left = left_child(idx);
      const auto right = right_child(idx);

      // There is a guarentee that the left child exists but there is not a guarentee that the right
      // child exists.
      if (right < bin_heap.size()) {
        if (bins[bin_heap[right]] < bins[bin_heap[left]]) {
          return right;
        }
      }
      return left;
    }

    std::size_t PPNThreshold::left_child(std::size_t idx) const noexcept { return 2 * idx + 1; }

    std::size_t PPNThreshold::right_child(std::size_t idx) const noexcept { return 2 * (idx + 1); }
  }  // namespace image
}  // namespace gif
