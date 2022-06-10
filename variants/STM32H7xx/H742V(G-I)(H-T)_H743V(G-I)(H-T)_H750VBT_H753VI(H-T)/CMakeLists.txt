
add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins_DevEBoxH7xx.c
  variant_WeActMiniH7xx.cpp
  variant_generic.cpp
  variant_DevEBoxH7xx.cpp
  PeripheralPins_WeActMiniH7xx.c
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)