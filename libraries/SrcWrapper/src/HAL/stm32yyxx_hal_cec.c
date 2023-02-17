/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F0xx
  #include "stm32f0xx_hal_cec.c"
#elif STM32F1xx
  #include "stm32f1xx_hal_cec.c"
#elif STM32F3xx
  #include "stm32f3xx_hal_cec.c"
#elif STM32F4xx
  #include "stm32f4xx_hal_cec.c"
#elif STM32F7xx
  #include "stm32f7xx_hal_cec.c"
#elif STM32G0xx
  #include "stm32g0xx_hal_cec.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_cec.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_cec.c"
#endif
#pragma GCC diagnostic pop
