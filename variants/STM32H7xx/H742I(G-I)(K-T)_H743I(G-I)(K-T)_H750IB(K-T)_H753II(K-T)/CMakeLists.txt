

add_library(variant EXCLUDE_FROM_ALL
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

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 