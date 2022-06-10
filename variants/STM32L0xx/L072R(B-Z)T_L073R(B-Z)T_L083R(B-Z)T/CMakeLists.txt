
add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins_PX_HER0.c
  variant_generic.cpp
  variant_NUCLEO_L073RZ.cpp
  generic_clock.c
  variant_PX_HER0.cpp
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)