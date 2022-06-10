
add_library(variant EXCLUDE_FROM_ALL
  variant_BLACK_F407VX.cpp
  PeripheralPins_ARMED_V1.c
  PeripheralPins_FK407M1.c
  variant_generic.cpp
  variant_FK407M1.cpp
  variant_PRNTR_Vx.cpp
  variant_ARMED_V1.cpp
  variant_BLUE_F407VE_MINI.cpp
  variant_DISCO_F407VG.cpp
  PeripheralPins_BLUE_F407VE_MINI.c
  generic_clock.c
  variant_DIYMORE_F407VGT.cpp
  PeripheralPins_BLACK_F407VX.c
  PeripheralPins_PRNTR_V2.c
  PeripheralPins.c
  PeripheralPins_PRNTR_V1.c
)


target_link_libraries(variant PUBLIC
  core_config
)