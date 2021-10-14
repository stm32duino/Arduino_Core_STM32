/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F0xx
  #include "stm32f0xx_hal_usart_ex.c"
#elif STM32F3xx
  #include "stm32f3xx_hal_usart_ex.c"
#elif STM32G0xx
  #include "stm32g0xx_hal_usart_ex.c"
#elif STM32G4xx
  #include "stm32g4xx_hal_usart_ex.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_usart_ex.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_usart_ex.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_usart_ex.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_usart_ex.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_usart_ex.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_usart_ex.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_usart_ex.c"
#endif
#pragma GCC diagnostic pop
