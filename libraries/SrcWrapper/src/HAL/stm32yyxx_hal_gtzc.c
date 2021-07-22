/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32L5xx
  #include "stm32l5xx_hal_gtzc.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_gtzc.c"
#endif
#pragma GCC diagnostic pop
