
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  variant_EEXTR_F030_V1.cpp
  generic_clock.c
  PeripheralPins_EEXTR_F030_V1.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)