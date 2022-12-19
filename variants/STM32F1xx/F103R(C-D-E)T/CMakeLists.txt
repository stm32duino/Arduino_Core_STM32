

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_STORM32_V1_31_RC.c
  generic_clock.c
  variant_BLUEBUTTON_F103RxT.cpp
  variant_STORM32_V1_31_RC.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 