

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_DevEBoxH7xx.c
  PeripheralPins_WeActMiniH7xx.c
  generic_clock.c
  variant_DevEBoxH7xx.cpp
  variant_WeActMiniH7xx.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 