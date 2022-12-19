

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_SPARKY_F303CC.c
  generic_clock.c
  variant_BLACKPILL_F303CC.cpp
  variant_SPARKY_F303CC.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 