

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_RAK811_TRACKER.c
  generic_clock.c
  variant_RAK811_TRACKER.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 