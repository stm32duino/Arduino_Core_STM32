/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H7xx
  #include "stm32h7xx_hal_ramecc.c"
#endif
#pragma GCC diagnostic pop
