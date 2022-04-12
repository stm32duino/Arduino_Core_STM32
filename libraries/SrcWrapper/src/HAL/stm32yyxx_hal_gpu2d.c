/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32U5xx
  #include "stm32u5xx_hal_gpu2d.c"
#endif
#pragma GCC diagnostic pop
