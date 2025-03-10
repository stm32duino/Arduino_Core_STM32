/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32U3xx
  #include "stm32u3xx_hal_mdf.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_mdf.c"
#endif
#pragma GCC diagnostic pop
