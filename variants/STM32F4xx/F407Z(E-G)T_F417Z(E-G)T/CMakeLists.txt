
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  generic_clock.c
  variant_BLACK_F407ZX.cpp
  PeripheralPins_VCCGND_F407ZG_MINI.c
  variant_VCCGND_F407ZG_MINI.cpp
  PeripheralPins.c
  PeripheralPins_BLACK_F407ZX.c
)


target_link_libraries(variant PUBLIC
  core_config
)