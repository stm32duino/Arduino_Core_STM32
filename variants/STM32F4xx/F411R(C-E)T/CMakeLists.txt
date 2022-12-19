

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_PYBSTICK26_STD.c
  generic_clock.c
  variant_NUCLEO_F411RE.cpp
  variant_PYBSTICK26_STD.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 