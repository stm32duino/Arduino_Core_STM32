/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32WB0x
  #include "stm32wb0x_ll_system.c"
#endif
#pragma GCC diagnostic pop
