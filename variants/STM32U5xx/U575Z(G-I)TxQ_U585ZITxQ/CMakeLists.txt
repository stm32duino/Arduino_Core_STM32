

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_NUCLEO_U575ZI_Q.c
  generic_clock.c
  variant_NUCLEO_U575ZI_Q.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 