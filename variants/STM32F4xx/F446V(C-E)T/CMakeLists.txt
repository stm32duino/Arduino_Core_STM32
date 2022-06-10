
add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins_RUMBA32.c
  variant_RUMBA32.cpp
  variant_generic.cpp
  PeripheralPins_VAKE_V1.c
  generic_clock.c
  PeripheralPins_FYSETC_S6.c
  PeripheralPins.c
  variant_FYSETC_S6.cpp
  variant_VAKE_V1.cpp
)


target_link_libraries(variant PUBLIC
  core_config
)