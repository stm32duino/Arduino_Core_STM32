
add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins_STM32MP157_DK.c
  variant_generic.cpp
  variant_STM32MP157_DK.cpp
  generic_clock.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)