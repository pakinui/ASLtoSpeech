# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "345Application_autogen"
  "CMakeFiles\\345Application_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\345Application_autogen.dir\\ParseCache.txt"
  )
endif()
