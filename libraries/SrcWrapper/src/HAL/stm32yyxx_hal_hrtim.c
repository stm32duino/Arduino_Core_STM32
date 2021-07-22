/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F3xx
  #include "stm32f3xx_hal_hrtim.c"
#elif STM32G4xx
  #include "stm32g4xx_hal_hrtim.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_hrtim.c"
#endif
#pragma GCC diagnostic pop
