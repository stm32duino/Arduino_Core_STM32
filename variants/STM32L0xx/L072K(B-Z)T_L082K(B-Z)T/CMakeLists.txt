

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_THUNDERPACK_L072.c
  generic_clock.c
  variant_THUNDERPACK_L072.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 