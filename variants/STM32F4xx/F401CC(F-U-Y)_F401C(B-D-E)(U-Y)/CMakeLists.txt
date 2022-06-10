
add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins_PYBSTICK26_LITE.c
  variant_generic.cpp
  variant_PYBSTICK26_LITE.cpp
  PeripheralPins_BLACKPILL_F401CC.c
  generic_clock.c
  PeripheralPins.c
  variant_BLACKPILL_F401CC.cpp
)


target_link_libraries(variant PUBLIC
  core_config
)