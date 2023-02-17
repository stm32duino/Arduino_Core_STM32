/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F7xx
  #include "stm32f7xx_hal_mdios.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_mdios.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_mdios.c"
#endif
#pragma GCC diagnostic pop
