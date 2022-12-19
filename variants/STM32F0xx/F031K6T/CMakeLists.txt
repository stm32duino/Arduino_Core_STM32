

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  generic_clock.c
  variant_NUCLEO_F031K6.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 