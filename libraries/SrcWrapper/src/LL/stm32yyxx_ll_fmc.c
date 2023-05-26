/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F3xx
  #include "stm32f3xx_ll_fmc.c"
#elif STM32F4xx
  #include "stm32f4xx_ll_fmc.c"
#elif STM32F7xx
  #include "stm32f7xx_ll_fmc.c"
#elif STM32G4xx
  #include "stm32g4xx_ll_fmc.c"
#elif STM32H5xx
  #include "stm32h5xx_ll_fmc.c"
#elif STM32H7xx
  #include "stm32h7xx_ll_fmc.c"
#elif STM32L4xx
  #include "stm32l4xx_ll_fmc.c"
#elif STM32L5xx
  #include "stm32l5xx_ll_fmc.c"
#elif STM32MP1xx
  #include "stm32mp1xx_ll_fmc.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_fmc.c"
#endif
#pragma GCC diagnostic pop
