/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F0xx
  #include "Legacy/stm32f0xx_hal_can.c"
  #include "stm32f0xx_hal_can.c"
#elif STM32F1xx
  #include "Legacy/stm32f1xx_hal_can.c"
  #include "stm32f1xx_hal_can.c"
#elif STM32F2xx
  #include "Legacy/stm32f2xx_hal_can.c"
  #include "stm32f2xx_hal_can.c"
#elif STM32F3xx
  #include "Legacy/stm32f3xx_hal_can.c"
  #include "stm32f3xx_hal_can.c"
#elif STM32F4xx
  #include "Legacy/stm32f4xx_hal_can.c"
  #include "stm32f4xx_hal_can.c"
#elif STM32F7xx
  #include "Legacy/stm32f7xx_hal_can.c"
  #include "stm32f7xx_hal_can.c"
#elif STM32L4xx
  #include "Legacy/stm32l4xx_hal_can.c"
  #include "stm32l4xx_hal_can.c"
#endif
#pragma GCC diagnostic pop
