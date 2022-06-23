
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
  PeripheralPins_B_L475E_IOT01A.c
  generic_clock.c
  variant_B_L475E_IOT01A.cpp
  variant_generic.cpp
)
target_link_libraries(variant_bin PUBLIC variant_usage)

target_link_libraries(variant INTERFACE
  variant_bin
)

