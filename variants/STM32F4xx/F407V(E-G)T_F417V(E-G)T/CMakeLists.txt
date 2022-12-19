

add_library(variant EXCLUDE_FROM_ALL
  PeripheralPins.c
  PeripheralPins_ARMED_V1.c
  PeripheralPins_BLACK_F407VX.c
  PeripheralPins_BLUE_F407VE_MINI.c
  PeripheralPins_FK407M1.c
  PeripheralPins_PRNTR_V1.c
  PeripheralPins_PRNTR_V2.c
  generic_clock.c
  variant_ARMED_V1.cpp
  variant_BLACK_F407VX.cpp
  variant_BLUE_F407VE_MINI.cpp
  variant_DISCO_F407VG.cpp
  variant_DIYMORE_F407VGT.cpp
  variant_FK407M1.cpp
  variant_PRNTR_Vx.cpp
  variant_generic.cpp
)

target_include_directories(variant PUBLIC
  .
)

target_link_libraries(variant PUBLIC
  core_config
)



 