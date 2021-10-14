/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H7xx
  #include "stm32h7xx_hal_dfsdm_ex.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_dfsdm_ex.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_dfsdm_ex.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_dfsdm_ex.c"
#endif
#pragma GCC diagnostic pop
