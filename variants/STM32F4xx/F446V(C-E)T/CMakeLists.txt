

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_FYSETC_S6.c
  PeripheralPins_RUMBA32.c
  PeripheralPins_VAKE_V1.c
  generic_clock.c
  variant_FYSETC_S6.cpp
  variant_RUMBA32.cpp
  variant_VAKE_V1.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 