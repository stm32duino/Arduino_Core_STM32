/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32MP1xx
  #include "stm32mp1xx_hal_ipcc.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_ipcc.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_ipcc.c"
#endif
#pragma GCC diagnostic pop
