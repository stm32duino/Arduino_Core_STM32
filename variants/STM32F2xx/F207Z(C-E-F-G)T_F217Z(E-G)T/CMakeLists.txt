

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_NUCLEO_F207ZG.c
  generic_clock.c
  variant_NUCLEO_F207ZG.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 