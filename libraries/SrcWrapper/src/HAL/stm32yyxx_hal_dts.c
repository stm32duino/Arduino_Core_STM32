/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H5xx
  #include "stm32h5xx_hal_dts.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_dts.c"
#endif
#pragma GCC diagnostic pop
