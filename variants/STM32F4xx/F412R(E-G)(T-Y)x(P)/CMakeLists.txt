
add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins_PYBSTICK26_PRO.c
  variant_generic.cpp
  generic_clock.c
  variant_PYBSTICK26_PRO.cpp
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)