/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32WL3x
  #include "stm32wl3x_ll_lcsc.c"
#endif
#pragma GCC diagnostic pop
