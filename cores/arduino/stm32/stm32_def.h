#ifndef _STM32_DEF_
#define _STM32_DEF_

#define F_CPU SystemCoreClock
#define USE_HAL_DRIVER

#ifdef STM32F0xx
#include "stm32f0xx.h"
#elif defined(STM32F1xx)
#include "stm32f1xx.h"
#elif defined(STM32F2xx)
#include "stm32f2xx.h"
#elif defined(STM32F3xx)
#include "stm32f3xx.h"
#elif defined(STM32F4xx)
#include "stm32f4xx.h"
#elif defined(STM32F7xx)
#include "stm32f7xx.h"
#elif defined(STM32H7xx)
#include "stm32h7xx.h"
#elif defined(STM32L0xx)
#include "stm32l0xx.h"
#elif defined(STM32L1xx)
#include "stm32l1xx.h"
#elif defined(STM32L4xx)
#include "stm32l4xx.h"
#else
#error "STM32YYxx chip series is not defined in boards.txt."
#endif

// Here define some compatibility
#ifndef CAN1
#define CAN1 CAN
#endif

/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#define WEAK __attribute__ ((weak))
#endif

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

// weaked functions declaration
void SystemClock_Config(void);

void _Error_Handler(const char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //_STM32_DEF_
