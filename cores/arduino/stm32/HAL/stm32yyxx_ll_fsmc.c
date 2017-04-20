#include "stm32_def_build.h"

#ifdef STM32F0xx
// none
#endif
#ifdef STM32F1xx
#include "stm32f1xx_ll_fsmc.c"
#endif
#ifdef STM32F2xx
#include "stm32f2xx_ll_fsmc.c"
#endif
#ifdef STM32F3xx
// none
#endif
#ifdef STM32F4xx
#include "stm32f4xx_ll_fsmc.c"
#endif
#ifdef STM32F7xx
// none
#endif
#ifdef STM32L0xx
// none
#endif
#ifdef STM32L1xx
#include "stm32l1xx_ll_fsmc.c"
#endif
#ifdef STM32L4xx
// none
#endif
