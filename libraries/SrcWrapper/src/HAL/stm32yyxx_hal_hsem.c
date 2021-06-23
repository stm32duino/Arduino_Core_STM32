#ifdef STM32H7xx
  #include "stm32h7xx_hal_hsem.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_hsem.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_hsem.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_hsem.c"
#endif
