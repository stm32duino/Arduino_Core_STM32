
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  variant_DISCO_F030R8.cpp
  variant_NUCLEO_F030R8.cpp
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)