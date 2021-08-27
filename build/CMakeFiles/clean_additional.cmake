# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "src/visualization/CMakeFiles/game_of_life_autogen.dir/AutogenUsed.txt"
  "src/visualization/CMakeFiles/game_of_life_autogen.dir/ParseCache.txt"
  "src/visualization/game_of_life_autogen"
  )
endif()
