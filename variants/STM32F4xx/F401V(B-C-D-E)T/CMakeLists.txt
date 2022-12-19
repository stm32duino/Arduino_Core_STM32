

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_ST3DP001_EVAL.c
  generic_clock.c
  variant_ST3DP001_EVAL.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 