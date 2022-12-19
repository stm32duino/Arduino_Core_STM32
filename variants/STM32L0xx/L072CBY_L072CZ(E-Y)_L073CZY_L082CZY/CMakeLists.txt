

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_B_L072Z_LRWAN1.c
  generic_clock.c
  variant_B_L072Z_LRWAN1.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 