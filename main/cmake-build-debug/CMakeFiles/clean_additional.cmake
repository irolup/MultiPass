# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MultiPass_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MultiPass_autogen.dir/ParseCache.txt"
  "MultiPass_autogen"
  )
endif()
