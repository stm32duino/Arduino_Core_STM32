

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_BLACK_F407ZX.c
  PeripheralPins_VCCGND_F407ZG_MINI.c
  generic_clock.c
  variant_BLACK_F407ZX.cpp
  variant_VCCGND_F407ZG_MINI.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 