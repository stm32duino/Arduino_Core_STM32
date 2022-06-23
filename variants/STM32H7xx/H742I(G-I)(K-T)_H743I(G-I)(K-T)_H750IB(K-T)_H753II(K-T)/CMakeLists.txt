
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
  PeripheralPins_DAISY_PATCH_SM.c
  PeripheralPins_DAISY_PETAL_SM.c
  PeripheralPins_DAISY_SEED.c
  generic_clock.c
  variant_DAISY_PATCH_SM.cpp
  variant_DAISY_PETAL_SM.cpp
  variant_DAISY_SEED.cpp
  variant_generic.cpp
)
target_link_libraries(variant_bin PUBLIC variant_usage)

target_link_libraries(variant INTERFACE
  variant_bin
)

