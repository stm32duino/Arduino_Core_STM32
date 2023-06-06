/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F3xx
  #include "stm32f3xx_hal_opamp.c"
#elif STM32G4xx
  #include "stm32g4xx_hal_opamp.c"
#elif STM32H5xx
  #include "stm32h5xx_hal_opamp.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_opamp.c"
#elif STM32L1xx
  #include "stm32l1xx_hal_opamp.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_opamp.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_opamp.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_opamp.c"
#endif
#pragma GCC diagnostic pop
