

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_DISCO_F413ZH.c
  generic_clock.c
  variant_DISCO_F413ZH.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 