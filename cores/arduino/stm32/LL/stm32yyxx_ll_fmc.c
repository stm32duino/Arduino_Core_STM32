#ifdef STM32F3xx
#include "stm32f3xx_ll_fmc.c"
#endif
#ifdef STM32F4xx
#include "stm32f4xx_ll_fmc.c"
#endif
#ifdef STM32F7xx
#include "stm32f7xx_ll_fmc.c"
#endif
#ifdef STM32H7xx
/*
 * Build issue as not properly guard in current
 * version if stm32h7xx_ll_fmc.h is not include
 */
/*#include "stm32h7xx_ll_fmc.c"*/
#endif
#ifdef STM32L4xx
#include "stm32l4xx_ll_fmc.c"
#endif
