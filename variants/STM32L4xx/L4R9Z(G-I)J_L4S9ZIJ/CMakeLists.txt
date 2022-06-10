
add_library(variant EXCLUDE_FROM_ALL
  variant_STEVAL_MKSBOX1V1.cpp
  variant_generic.cpp
  generic_clock.c
  PeripheralPins.c
  PeripheralPins_STEVAL_MKSBOX1V1.c
)


target_link_libraries(variant PUBLIC
  core_config
)