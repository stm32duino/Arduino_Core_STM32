/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H7xx
  #include "Legacy/stm32h7xx_hal_eth_ex.c"
  #include "stm32h7xx_hal_eth_ex.c"
#endif
#pragma GCC diagnostic pop
