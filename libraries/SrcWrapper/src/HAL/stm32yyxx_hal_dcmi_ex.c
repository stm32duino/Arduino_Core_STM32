/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F2xx
  #include "stm32f2xx_hal_dcmi_ex.c"
#elif STM32F4xx
  #include "stm32f4xx_hal_dcmi_ex.c"
#elif STM32F7xx
  #include "stm32f7xx_hal_dcmi_ex.c"
#endif
#pragma GCC diagnostic pop
