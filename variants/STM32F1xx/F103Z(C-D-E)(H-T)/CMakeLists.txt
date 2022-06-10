
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  variant_VCCGND_F103ZET6_XXX.cpp
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)