# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MemoFlip_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MemoFlip_autogen.dir\\ParseCache.txt"
  "MemoFlip_autogen"
  )
endif()
