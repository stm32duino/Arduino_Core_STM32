
add_library(variant INTERFACE)
add_library(variant_usage INTERFACE)

target_include_directories(variant_usage INTERFACE
  .
)


target_link_libraries(variant_usage INTERFACE
  core_config
)

target_link_libraries(variant INTERFACE variant_usage)



add_library(variant_bin STATIC EXCLUDE_FROM_ALL
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
target_link_libraries(variant_bin PUBLIC variant_usage)

target_link_libraries(variant INTERFACE
  variant_bin
)

