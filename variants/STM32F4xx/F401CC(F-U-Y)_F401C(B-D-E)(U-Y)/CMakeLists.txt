

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_BLACKPILL_F401CC.c
  PeripheralPins_PYBSTICK26_LITE.c
  generic_clock.c
  variant_BLACKPILL_F401CC.cpp
  variant_PYBSTICK26_LITE.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 