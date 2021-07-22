/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32G4xx
  #include "stm32g4xx_hal_smbus_ex.c"
#elif STM32L0xx
  #include "stm32l0xx_hal_smbus_ex.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_smbus_ex.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_smbus_ex.c"
#endif
#pragma GCC diagnostic pop
