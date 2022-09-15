
add_library(variant EXCLUDE_FROM_ALL
  variant_CoreBoard_F401RC.cpp
  variant_generic.cpp
  variant_NUCLEO_F401RE.cpp
  generic_clock.c
  PeripheralPins.c
  PeripheralPins_CoreBoard_F401RC.c
)

