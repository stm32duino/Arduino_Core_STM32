

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_FEATHER_F405.c
  generic_clock.c
  variant_FEATHER_F405.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 