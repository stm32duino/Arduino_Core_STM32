
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  PeripheralPins_THUNDERPACK_L072.c
  generic_clock.c
  PeripheralPins.c
  variant_THUNDERPACK_L072.cpp
)


target_link_libraries(variant PUBLIC
  core_config
)