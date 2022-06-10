
add_library(CMSIS_DSP OBJECT EXCLUDE_FROM_ALL
  src/CommonTables/CommonTables.c
  src/BasicMathFunctions/BasicMathFunctions.c
  src/TransformFunctions/TransformFunctions.c
  src/FastMathFunctions/FastMathFunctions.c
  src/BayesFunctions/BayesFunctions.c
  src/StatisticsFunctions/StatisticsFunctions.c
  src/DistanceFunctions/DistanceFunctions.c
  src/SupportFunctions/SupportFunctions.c
  src/ControllerFunctions/ControllerFunctions.c
  src/FilteringFunctions/FilteringFunctions.c
  src/MatrixFunctions/MatrixFunctions.c
  src/ComplexMathFunctions/ComplexMathFunctions.c
  src/SVMFunctions/SVMFunctions.c
)

target_include_directories(CMSIS_DSP PUBLIC
  src
)

target_link_libraries(CMSIS_DSP PUBLIC
  core_config
)