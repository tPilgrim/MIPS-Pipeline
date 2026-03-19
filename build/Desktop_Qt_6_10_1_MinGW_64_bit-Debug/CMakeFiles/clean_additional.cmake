# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PipelineSimulator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PipelineSimulator_autogen.dir\\ParseCache.txt"
  "PipelineSimulator_autogen"
  )
endif()
