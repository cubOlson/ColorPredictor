# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ColorPredictionApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ColorPredictionApp_autogen.dir\\ParseCache.txt"
  "ColorPredictionApp_autogen"
  )
endif()
