#include "colour_pallete.h"

namespace gif {

  ColourPallete::ColourPallete(std::vector<unsigned char>& data, bool has_alpha)
      : data(std::vector<unsigned char>(data.begin(), data.end())), step_size(has_alpha ? 4 : 3) {}
}  // namespace gif