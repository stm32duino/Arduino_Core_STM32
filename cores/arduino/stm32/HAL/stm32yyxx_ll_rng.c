#include "stm32_def_build.h"

#ifdef STM32F0xx
// none
#endif
#ifdef STM32F1xx
// none
#endif
#ifdef STM32F2xx
#include "stm32f2xx_ll_rng.c"
#endif
#ifdef STM32F3xx
// none
#endif
#ifdef STM32F4xx
// none
#endif
#ifdef STM32F7xx
#include "stm32f7xx_ll_rng.c"
#endif
#ifdef STM32L0xx
#include "stm32l0xx_ll_rng.c"
#endif
#ifdef STM32L1xx
// none
#endif
#ifdef STM32L4xx
#include "stm32l4xx_ll_rng.c"
#endif
