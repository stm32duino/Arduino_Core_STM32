/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F7xx
  #include "stm32f7xx_hal_jpeg.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_jpeg.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_jpeg.c"
#endif
#pragma GCC diagnostic pop
