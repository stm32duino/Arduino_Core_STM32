
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  generic_clock.c
  variant_NUCLEO_F303RE.cpp
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)