
add_library(variant EXCLUDE_FROM_ALL
  variant_generic.cpp
  variant_B_L4S5I_IOT01A.cpp
  generic_clock.c
  PeripheralPins_B_L4S5I_IOT01A.c
  PeripheralPins.c
)


target_link_libraries(variant PUBLIC
  core_config
)