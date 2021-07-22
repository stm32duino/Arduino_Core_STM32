/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F1xx
  #include "stm32f1xx_hal_pccard.c"
#elif STM32F2xx
  #include "stm32f2xx_hal_pccard.c"
#elif STM32F3xx
  #include "stm32f3xx_hal_pccard.c"
#elif STM32F4xx
  #include "stm32f4xx_hal_pccard.c"
#endif
#pragma GCC diagnostic pop
