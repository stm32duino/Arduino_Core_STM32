/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32C0xx
  #include "stm32c0xx_ll_crc.c"
#elif STM32F0xx
  #include "stm32f0xx_ll_crc.c"
#elif STM32F1xx
  #include "stm32f1xx_ll_crc.c"
#elif STM32F2xx
  #include "stm32f2xx_ll_crc.c"
#elif STM32F3xx
  #include "stm32f3xx_ll_crc.c"
#elif STM32F4xx
  #include "stm32f4xx_ll_crc.c"
#elif STM32F7xx
  #include "stm32f7xx_ll_crc.c"
#elif STM32G0xx
  #include "stm32g0xx_ll_crc.c"
#elif STM32G4xx
  #include "stm32g4xx_ll_crc.c"
#elif STM32H5xx
  #include "stm32h5xx_ll_crc.c"
#elif STM32H7xx
  #include "stm32h7xx_ll_crc.c"
#elif STM32L0xx
  #include "stm32l0xx_ll_crc.c"
#elif STM32L1xx
  #include "stm32l1xx_ll_crc.c"
#elif STM32L4xx
  #include "stm32l4xx_ll_crc.c"
#elif STM32L5xx
  #include "stm32l5xx_ll_crc.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_crc.c"
#elif STM32WBxx
  #include "stm32wbxx_ll_crc.c"
#elif STM32WLxx
  #include "stm32wlxx_ll_crc.c"
#endif
#pragma GCC diagnostic pop
