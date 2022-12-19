

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_ELEKTOR_F072Cx.c
  generic_clock.c
  variant_ELEKTOR_F072Cx.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 