/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32U3xx
  #include "stm32u3xx_hal_ccb.c"
#endif
#pragma GCC diagnostic pop
