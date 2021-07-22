/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H7xx
  #include "stm32h7xx_hal_otfdec.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_otfdec.c"
#endif
#pragma GCC diagnostic pop
