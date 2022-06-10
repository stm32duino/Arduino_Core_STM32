
add_library(variant EXCLUDE_FROM_ALL
  variant_NUCLEO_L552ZE_Q.cpp
  variant_generic.cpp
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)