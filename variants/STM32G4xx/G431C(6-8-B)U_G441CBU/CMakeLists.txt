
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  PeripheralPins_B_G431B_ESC1.c
  variant_B_G431B_ESC1.cpp
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)