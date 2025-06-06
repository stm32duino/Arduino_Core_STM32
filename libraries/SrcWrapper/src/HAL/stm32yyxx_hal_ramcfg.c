/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H5xx
  #include "stm32h5xx_hal_ramcfg.c"
#elif STM32U3xx
  #include "stm32u3xx_hal_ramcfg.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_ramcfg.c"
#elif STM32WBAxx
  #include "stm32wbaxx_hal_ramcfg.c"
#endif
#pragma GCC diagnostic pop
