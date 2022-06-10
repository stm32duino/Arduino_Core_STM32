
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  generic_clock.c
  PeripheralPins.c
  variant_NUCLEO_G474RE.cpp
)


target_link_libraries(variant PUBLIC
  core_config
)