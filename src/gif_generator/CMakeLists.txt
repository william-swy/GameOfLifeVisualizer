# Model for specifically converting image frames to GIF

add_library(
  gif_generator colour_kd_tree.cpp colour_kd_tree.h gif_generator.cpp gif_generator.h
                image_frame.cpp image_frame.h
 "gif.h")

target_include_directories(gif_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(
    gif_generator
    PRIVATE -Wall -Wpedantic -Wextra -Werror
  )
elseif(MSVC)
  target_compile_options(
    gif_generator
    PRIVATE /Wall /W3
  )
endif()

target_compile_features(gif_generator PRIVATE cxx_std_20)
