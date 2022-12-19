

add_library(variant EXCLUDE_FROM_ALL
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

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 