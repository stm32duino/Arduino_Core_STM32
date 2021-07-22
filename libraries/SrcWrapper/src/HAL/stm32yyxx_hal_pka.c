/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32L4xx
  #include "stm32l4xx_hal_pka.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_pka.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_pka.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_pka.c"
#endif
#pragma GCC diagnostic pop
