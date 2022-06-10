
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  variant_RAK811_TRACKER.cpp
  PeripheralPins_RAK811_TRACKER.c
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)