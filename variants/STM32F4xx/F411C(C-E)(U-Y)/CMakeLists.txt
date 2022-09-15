
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  PeripheralPins_BLACKPILL_F411CE.c
  generic_clock.c
  PeripheralPins_THUNDERPACK_F411.c
  variant_BLACKPILL_F411CE.cpp
  variant_THUNDERPACK_F411.cpp
  PeripheralPins.c
)

