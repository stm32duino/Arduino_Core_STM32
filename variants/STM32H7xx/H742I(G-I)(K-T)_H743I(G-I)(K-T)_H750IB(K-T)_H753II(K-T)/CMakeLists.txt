
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  PeripheralPins_DAISY_PATCH_SM.c
  variant_DAISY_SEED.cpp
  PeripheralPins_DAISY_PETAL_SM.c
  PeripheralPins_DAISY_SEED.c
  generic_clock.c
  variant_DAISY_PATCH_SM.cpp
  variant_DAISY_PETAL_SM.cpp
  PeripheralPins.c
)

