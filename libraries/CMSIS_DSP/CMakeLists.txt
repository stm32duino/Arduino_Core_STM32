

add_library(CMSIS_DSP OBJECT EXCLUDE_FROM_ALL
  src/BasicMathFunctions/BasicMathFunctions.c
  src/BayesFunctions/BayesFunctions.c
  src/CommonTables/CommonTables.c
  src/ComplexMathFunctions/ComplexMathFunctions.c
  src/ControllerFunctions/ControllerFunctions.c
  src/DistanceFunctions/DistanceFunctions.c
  src/FastMathFunctions/FastMathFunctions.c
  src/FilteringFunctions/FilteringFunctions.c
  src/MatrixFunctions/MatrixFunctions.c
  src/SVMFunctions/SVMFunctions.c
  src/StatisticsFunctions/StatisticsFunctions.c
  src/SupportFunctions/SupportFunctions.c
  src/TransformFunctions/TransformFunctions.c
)

target_include_directories(CMSIS_DSP PUBLIC
  src
)

target_link_libraries(CMSIS_DSP PUBLIC
  core_config
)



 