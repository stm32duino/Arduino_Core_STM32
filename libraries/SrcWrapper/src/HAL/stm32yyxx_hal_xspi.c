/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H5xx
  #include "stm32h5xx_hal_xspi.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_xspi.c"
#endif
#pragma GCC diagnostic pop
