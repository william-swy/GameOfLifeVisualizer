#pragma once

#include <cstddef>
#include <vector>

#include "colour_pallete.h"
#include "image_frame.h"
#include "ppn_bin.h"

namespace gif {

  namespace image {
    class PPNThreshold {
    public:
      PPNThreshold() = default;

      PPNThreshold(const ImageFrame& img, TargetFormat target_format) noexcept;

      ColourPallete merge_to_size(std::size_t size) noexcept;

    private:
      bool has_alpha;

      std::vector<Bin> bins;

      std::vector<std::size_t> bin_heap;  // Each entry represents an index in bins

      void merge() noexcept;

      void swap_elem(std::size_t first_idx, std::size_t second_idx) noexcept;

      void build_heap() noexcept;

      void heapify_down(std::size_t idx) noexcept;

      void heapify_up(std::size_t idx) noexcept;

      bool has_child(std::size_t idx) const noexcept;

      std::size_t max_priority_child(std::size_t idx) const noexcept;

      // Computes the index of the left child of the element at idx. There is no guarentee that the
      // index returned is an index inside of the heap.
      std::size_t left_child(std::size_t idx) const noexcept;

      // Computes the index of the right child of the element at idx. There is no guarentee that the
      // index returned is an index inside of the heap.
      std::size_t right_child(std::size_t idx) const noexcept;

      // Computes the index of the parent of the element at idx. This should not be used when idx is
      // zero i.e. on the root index.
      std::size_t parent(std::size_t idx) const noexcept;
    };

    std::vector<char> ppn_threshold(std::vector<unsigned char>& data, TargetFormat img_format,
                                    TargetFormat target_format) noexcept;
  }  // namespace image
}  // namespace gif
