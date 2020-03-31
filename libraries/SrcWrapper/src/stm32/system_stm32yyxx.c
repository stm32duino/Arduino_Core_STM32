#define USE_HAL_DRIVER

#ifdef STM32F0xx
  #include "system_stm32f0xx.c"
#endif
#ifdef STM32F1xx
  #include "system_stm32f1xx.c"
#endif
#ifdef STM32F2xx
  #include "system_stm32f2xx.c"
#endif
#ifdef STM32F3xx
  #include "system_stm32f3xx.c"
#endif
#ifdef STM32F4xx
  #include "system_stm32f4xx.c"
#endif
#ifdef STM32F7xx
  #include "system_stm32f7xx.c"
#endif
#ifdef STM32G0xx
  #include "system_stm32g0xx.c"
#endif
#ifdef STM32G4xx
  #include "system_stm32g4xx.c"
#endif
#ifdef STM32H7xx
  #include "system_stm32h7xx.c"
#endif
#ifdef STM32L0xx
  #include "system_stm32l0xx.c"
#endif
#ifdef STM32L1xx
  #include "system_stm32l1xx.c"
#endif
#ifdef STM32L4xx
  #include "system_stm32l4xx.c"
#endif
#ifdef STM32MP1xx
  #include "system_stm32mp1xx.c"
#endif
#ifdef STM32WBxx
  #include "system_stm32wbxx.c"
#endif
