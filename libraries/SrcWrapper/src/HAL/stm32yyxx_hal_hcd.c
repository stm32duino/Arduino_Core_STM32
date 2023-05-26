/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F1xx
  #include "stm32f1xx_hal_hcd.c"
#elif STM32F2xx
  #include "stm32f2xx_hal_hcd.c"
#elif STM32F4xx
  #include "stm32f4xx_hal_hcd.c"
#elif STM32F7xx
  #include "stm32f7xx_hal_hcd.c"
#elif STM32G0xx
  #include "stm32g0xx_hal_hcd.c"
#elif STM32H5xx
  #include "stm32h5xx_hal_hcd.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_hcd.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_hcd.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_hcd.c"
#endif
#pragma GCC diagnostic pop
