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
  src/BasicMathFunctions/BasicMathFunctionsF16.c
  src/BayesFunctions/BayesFunctions.c
  src/BayesFunctions/BayesFunctionsF16.c
  src/CommonTables/CommonTables.c
  src/CommonTables/CommonTablesF16.c
  src/ComplexMathFunctions/ComplexMathFunctions.c
  src/ComplexMathFunctions/ComplexMathFunctionsF16.c
  src/ControllerFunctions/ControllerFunctions.c
  src/DistanceFunctions/DistanceFunctions.c
  src/DistanceFunctions/DistanceFunctionsF16.c
  src/FastMathFunctions/FastMathFunctions.c
  src/FastMathFunctions/FastMathFunctionsF16.c
  src/FilteringFunctions/FilteringFunctions.c
  src/FilteringFunctions/FilteringFunctionsF16.c
  src/InterpolationFunctions/InterpolationFunctions.c
  src/InterpolationFunctions/InterpolationFunctionsF16.c
  src/MatrixFunctions/MatrixFunctions.c
  src/MatrixFunctions/MatrixFunctionsF16.c
  src/QuaternionMathFunctions/QuaternionMathFunctions.c
  src/StatisticsFunctions/StatisticsFunctions.c
  src/StatisticsFunctions/StatisticsFunctionsF16.c
  src/SupportFunctions/SupportFunctions.c
  src/SupportFunctions/SupportFunctionsF16.c
  src/SVMFunctions/SVMFunctions.c
  src/SVMFunctions/SVMFunctionsF16.c
  src/TransformFunctions/TransformFunctions.c
  src/TransformFunctions/TransformFunctionsF16.c
)
target_link_libraries(CMSIS_DSP_bin PUBLIC CMSIS_DSP_usage)

target_link_libraries(CMSIS_DSP INTERFACE
  CMSIS_DSP_bin
  $<TARGET_OBJECTS:CMSIS_DSP_bin>
)

