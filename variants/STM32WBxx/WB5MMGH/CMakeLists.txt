
add_library(variant EXCLUDE_FROM_ALL
  variant_STM32WB5MM_DK.cpp
  variant_generic.cpp
  generic_clock.c
  PeripheralPins_STM32WB5MM_DK.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)