#pragma once

#include "image_frame.h"
#include "image_formats.h"

namespace gif {
  

  class ColourPallete {
  public:
    ColourPallete();


  };

  ColourPallete quantize(ImageFrame& img, TargetFormat format);
}  // namespace gif