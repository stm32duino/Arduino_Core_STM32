/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32G0xx
  #include "stm32g0xx_ll_lpuart.c"
#elif STM32G4xx
  #include "stm32g4xx_ll_lpuart.c"
#elif STM32H7xx
  #include "stm32h7xx_ll_lpuart.c"
#elif STM32L0xx
  #include "stm32l0xx_ll_lpuart.c"
#elif STM32L4xx
  #include "stm32l4xx_ll_lpuart.c"
#elif STM32L5xx
  #include "stm32l5xx_ll_lpuart.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_lpuart.c"
#elif STM32WBxx
  #include "stm32wbxx_ll_lpuart.c"
#elif STM32WLxx
  #include "stm32wlxx_ll_lpuart.c"
#endif
#pragma GCC diagnostic pop
