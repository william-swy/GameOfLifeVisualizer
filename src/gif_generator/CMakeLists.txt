# Model for specifically converting image frames to GIF

add_library(
  gif_generator
  "gif.h"
  "gif_generator.cpp"
  "gif_generator.h"
  "gif_writer.cpp"
  "gif_writer.h"
  "image/colour_pallete.cpp"
  "image/colour_pallete.h"
  "image/image_frame.cpp"
  "image/image_frame.h"
  "image/ppn.cpp"
  "image/ppn.h"
  "image/ppn_bin.cpp"
  "image/ppn_bin.h"
  "image/RGB_pixel.cpp"
  "image/RGB_pixel.h"
)

target_include_directories(gif_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gif_generator PRIVATE project_warnings
  project_options)
