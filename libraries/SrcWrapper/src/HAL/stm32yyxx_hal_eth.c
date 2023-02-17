/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F1xx
  #include "stm32f1xx_hal_eth.c"
#elif STM32F2xx
  #include "stm32f2xx_hal_eth.c"
#elif STM32F4xx
  #include "Legacy/stm32f4xx_hal_eth.c"
  #include "stm32f4xx_hal_eth.c"
#elif STM32F7xx
  #include "Legacy/stm32f7xx_hal_eth.c"
  #include "stm32f7xx_hal_eth.c"
#elif STM32H7xx
  #include "Legacy/stm32h7xx_hal_eth.c"
  #include "stm32h7xx_hal_eth.c"
#endif
#pragma GCC diagnostic pop
