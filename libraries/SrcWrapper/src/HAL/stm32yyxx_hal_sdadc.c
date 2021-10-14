/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F3xx
  #include "stm32f3xx_hal_sdadc.c"
#endif
#pragma GCC diagnostic pop
