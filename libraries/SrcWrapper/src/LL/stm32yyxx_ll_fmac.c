/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32G4xx
  #include "stm32g4xx_ll_fmac.c"
#elif STM32H7xx
  #include "stm32h7xx_ll_fmac.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_fmac.c"
#endif
#pragma GCC diagnostic pop
