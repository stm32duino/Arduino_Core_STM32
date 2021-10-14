/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32G0xx
  #include "stm32g0xx_hal_fdcan.c"
#elif STM32G4xx
  #include "stm32g4xx_hal_fdcan.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_fdcan.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_fdcan.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_fdcan.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_fdcan.c"
#endif
#pragma GCC diagnostic pop
