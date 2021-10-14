/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32L0xx
  #include "stm32l0xx_hal_lcd.c"
#elif STM32L1xx
  #include "stm32l1xx_hal_lcd.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_lcd.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_lcd.c"
#endif
#pragma GCC diagnostic pop
