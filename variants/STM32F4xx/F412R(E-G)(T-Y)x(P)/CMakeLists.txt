

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_PYBSTICK26_PRO.c
  generic_clock.c
  variant_PYBSTICK26_PRO.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 