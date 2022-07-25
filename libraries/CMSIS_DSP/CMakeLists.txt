# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(CMSIS_DSP INTERFACE)
add_library(CMSIS_DSP_usage INTERFACE)

target_include_directories(CMSIS_DSP_usage INTERFACE
  src
)


target_link_libraries(CMSIS_DSP_usage INTERFACE
  base_config
)

target_link_libraries(CMSIS_DSP INTERFACE CMSIS_DSP_usage)



add_library(CMSIS_DSP_bin OBJECT EXCLUDE_FROM_ALL
  src/BasicMathFunctions/BasicMathFunctions.c
  src/BayesFunctions/BayesFunctions.c
  src/CommonTables/CommonTables.c
  src/ComplexMathFunctions/ComplexMathFunctions.c
  src/ControllerFunctions/ControllerFunctions.c
  src/DistanceFunctions/DistanceFunctions.c
  src/FastMathFunctions/FastMathFunctions.c
  src/FilteringFunctions/FilteringFunctions.c
  src/MatrixFunctions/MatrixFunctions.c
  src/StatisticsFunctions/StatisticsFunctions.c
  src/SupportFunctions/SupportFunctions.c
  src/SVMFunctions/SVMFunctions.c
  src/TransformFunctions/TransformFunctions.c
)
target_link_libraries(CMSIS_DSP_bin PUBLIC CMSIS_DSP_usage)

target_link_libraries(CMSIS_DSP INTERFACE
  CMSIS_DSP_bin
  $<TARGET_OBJECTS:CMSIS_DSP_bin>
)

