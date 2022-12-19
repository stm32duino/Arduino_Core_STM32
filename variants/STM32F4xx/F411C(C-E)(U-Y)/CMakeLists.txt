

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_BLACKPILL_F411CE.c
  PeripheralPins_THUNDERPACK_F411.c
  generic_clock.c
  variant_BLACKPILL_F411CE.cpp
  variant_THUNDERPACK_F411.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 