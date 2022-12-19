

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_CoreBoard_F401RC.c
  generic_clock.c
  variant_CoreBoard_F401RC.cpp
  variant_NUCLEO_F401RE.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 