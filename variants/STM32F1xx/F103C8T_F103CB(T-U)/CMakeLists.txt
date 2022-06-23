
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
  PeripheralPins_MALYANM200_F103CB.c
  generic_clock.c
  startup_M200_f103xb.S
  variant_AFROFLIGHT_F103CB.cpp
  variant_MALYANM200_F103CB.cpp
  variant_MAPLEMINI_F103CB.cpp
  variant_PILL_F103Cx.cpp
  variant_generic.cpp
)
target_link_libraries(variant_bin PUBLIC variant_usage)

target_link_libraries(variant INTERFACE
  variant_bin
)

