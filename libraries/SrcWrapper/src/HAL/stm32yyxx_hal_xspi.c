/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32C5xx
  #include "stm32c5xx_hal_xspi.c"
#elif STM32H5xx
  #include "stm32h5xx_hal_xspi.c"
#elif STM32H7RSxx
  #include "stm32h7rsxx_hal_xspi.c"
#elif STM32U3xx
  #include "stm32u3xx_hal_xspi.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_xspi.c"
#elif STM32WBAxx
  #include "stm32wbaxx_hal_xspi.c"
#endif
#pragma GCC diagnostic pop
