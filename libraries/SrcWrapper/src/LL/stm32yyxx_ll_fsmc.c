/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F1xx
  #include "stm32f1xx_ll_fsmc.c"
#elif STM32F2xx
  #include "stm32f2xx_ll_fsmc.c"
#elif STM32F4xx
  #include "stm32f4xx_ll_fsmc.c"
#elif STM32L1xx
  #include "stm32l1xx_ll_fsmc.c"
#endif
#pragma GCC diagnostic pop
