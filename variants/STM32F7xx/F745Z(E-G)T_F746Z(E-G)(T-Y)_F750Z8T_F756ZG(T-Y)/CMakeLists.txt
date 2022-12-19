

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_ETHERCAT_DUINO.c
  generic_clock.c
  variant_ETHERCAT_DUINO.cpp
  variant_NUCLEO_F7x6ZG.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 