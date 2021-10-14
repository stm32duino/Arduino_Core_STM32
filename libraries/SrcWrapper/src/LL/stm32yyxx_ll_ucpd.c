/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32G0xx
  #include "stm32g0xx_ll_ucpd.c"
#elif STM32G4xx
  #include "stm32g4xx_ll_ucpd.c"
#elif STM32L5xx
  #include "stm32l5xx_ll_ucpd.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_ucpd.c"
#endif
#pragma GCC diagnostic pop
