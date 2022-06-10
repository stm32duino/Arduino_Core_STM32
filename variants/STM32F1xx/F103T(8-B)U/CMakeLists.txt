
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  variant_HY_TINYSTM103TB.cpp
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)