

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_PYBSTICK26_DUINO.c
  generic_clock.c
  variant_DISCO_F072RB.cpp
  variant_NUCLEO_F072RB.cpp
  variant_PYBSTICK26_DUINO.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 