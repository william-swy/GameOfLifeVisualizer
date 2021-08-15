# Model for specifically converting image frames to GIF

add_library(
  gif_generator
  colour_kd_tree.cpp
  colour_kd_tree.h
  colour_pallete.cpp
  colour_pallete.h
  gif.h
  gif_generator.cpp
  gif_generator.h
  gif_writer.cpp
  gif_writer.h
  image_formats.cpp
  image_formats.h
  image_frame.cpp
  image_frame.h
  ppn.cpp
  ppn.h
  ppn_bin.cpp
  ppn_bin.h
)

target_include_directories(gif_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(gif_generator PRIVATE -Wall -Wpedantic -Wextra -Werror)
elseif(MSVC)
  target_compile_options(gif_generator PRIVATE /Wall /W3)
endif()

target_compile_features(gif_generator PRIVATE cxx_std_20)
