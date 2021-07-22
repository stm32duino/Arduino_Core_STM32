/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F0xx
  #include "stm32f0xx_hal_tsc.c"
#elif STM32F3xx
  #include "stm32f3xx_hal_tsc.c"
#elif STM32L0xx
  #include "stm32l0xx_hal_tsc.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_tsc.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_tsc.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_tsc.c"
#endif
#pragma GCC diagnostic pop
