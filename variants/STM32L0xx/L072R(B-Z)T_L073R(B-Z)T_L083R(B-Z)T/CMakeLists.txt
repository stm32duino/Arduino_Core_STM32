

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_PX_HER0.c
  generic_clock.c
  variant_NUCLEO_L073RZ.cpp
  variant_PX_HER0.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 