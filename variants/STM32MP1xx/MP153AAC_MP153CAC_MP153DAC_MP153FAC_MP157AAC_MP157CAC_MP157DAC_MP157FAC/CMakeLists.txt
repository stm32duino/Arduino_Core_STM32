

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_STM32MP157_DK.c
  generic_clock.c
  variant_STM32MP157_DK.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 