/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32L0xx
  #include "stm32l0xx_hal_firewall.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_firewall.c"
#endif
#pragma GCC diagnostic pop
