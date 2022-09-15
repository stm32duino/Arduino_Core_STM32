
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  PeripheralPins_PYBSTICK26_DUINO.c
  variant_DISCO_F072RB.cpp
  variant_PYBSTICK26_DUINO.cpp
  variant_NUCLEO_F072RB.cpp
  generic_clock.c
  PeripheralPins.c
)

