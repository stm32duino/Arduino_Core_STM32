
add_library(variant INTERFACE)
add_library(variant_usage INTERFACE)

target_include_directories(variant_usage INTERFACE
  .
)


target_link_libraries(variant_usage INTERFACE
  base_config
)

target_link_libraries(variant INTERFACE variant_usage)



add_library(variant_bin STATIC EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_BLACKPILL_F401CC.c
  PeripheralPins_PYBSTICK26_LITE.c
  generic_clock.c
  variant_BLACKPILL_F401CC.cpp
  variant_PYBSTICK26_LITE.cpp
  variant_generic.cpp
)
target_link_libraries(variant_bin PUBLIC variant_usage)

target_link_libraries(variant INTERFACE
  variant_bin
)

