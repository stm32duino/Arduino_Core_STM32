/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F4xx
  #include "stm32f4xx_ll_dma2d.c"
#elif STM32F7xx
  #include "stm32f7xx_ll_dma2d.c"
#elif STM32H7xx
  #include "stm32h7xx_ll_dma2d.c"
#elif STM32L4xx
  #include "stm32l4xx_ll_dma2d.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_dma2d.c"
#endif
#pragma GCC diagnostic pop
