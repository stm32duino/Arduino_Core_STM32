#ifndef _STM32_DEF_
#define _STM32_DEF_


/**
 * @brief STM32 core version number
 */
#define STM32_CORE_VERSION_MAJOR    (0x02U) /*!< [31:24] major version */
#define STM32_CORE_VERSION_MINOR    (0x04U) /*!< [23:16] minor version */
#define STM32_CORE_VERSION_PATCH    (0x00U) /*!< [15:8]  patch version */
/*
 * Extra label for development:
 * 0: official release
 * [1-9]: release candidate
 * F[0-9]: development
 */
#define STM32_CORE_VERSION_EXTRA    (0xF0U) /*!< [7:0]  extra version */
#define STM32_CORE_VERSION          ((STM32_CORE_VERSION_MAJOR << 24U)\
                                        |(STM32_CORE_VERSION_MINOR << 16U)\
                                        |(STM32_CORE_VERSION_PATCH << 8U )\
                                        |(STM32_CORE_VERSION_EXTRA))

#define USE_HAL_DRIVER

#if defined(STM32F0xx)
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
#elif defined(STM32G0xx)
  #include "stm32g0xx.h"
#elif defined(STM32G4xx)
  #include "stm32g4xx.h"
#elif defined(STM32H7xx)
  #include "stm32h7xx.h"
#elif defined(STM32L0xx)
  #include "stm32l0xx.h"
#elif defined(STM32L1xx)
  #include "stm32l1xx.h"
#elif defined(STM32L4xx)
  #include "stm32l4xx.h"
#elif defined(STM32L5xx)
  #include "stm32l5xx.h"
#elif defined(STM32MP1xx)
  #include "stm32mp1xx.h"
#elif defined(STM32U5xx)
  #include "stm32u5xx.h"
#elif defined(STM32WBxx)
  #include "stm32wbxx.h"
#elif defined(STM32WLxx)
  #include "stm32wlxx.h"
#else
  #error "STM32YYxx chip series is not defined in boards.txt."
#endif

#ifndef F_CPU
  #define F_CPU SystemCoreClock
#endif

// Here define some compatibility
#ifndef ADC1
  #define ADC1 ADC
#endif
#ifndef CAN1
  #define CAN1 CAN
#endif
#ifndef DAC1
  #define DAC1 DAC
#endif

#ifdef USB_OTG_FS
  #if !defined(__HAL_RCC_USB_OTG_FS_CLK_DISABLE) && defined(__HAL_RCC_USB_CLK_DISABLE)
    #define __HAL_RCC_USB_OTG_FS_CLK_DISABLE __HAL_RCC_USB_CLK_DISABLE
  #endif
  #if !defined(__HAL_RCC_USB_OTG_FS_CLK_ENABLE) && defined(__HAL_RCC_USB_CLK_ENABLE)
    #define __HAL_RCC_USB_OTG_FS_CLK_ENABLE __HAL_RCC_USB_CLK_ENABLE
  #endif
#endif

/* STM32G0xx defined USB_DRD_FS */
#if !defined(USB) && defined(USB_DRD_FS)
  #define USB USB_DRD_FS
  #define PinMap_USB PinMap_USB_DRD_FS
#endif

/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
  #define WEAK __attribute__ ((weak))
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// weaked functions declaration
void SystemClock_Config(void);

#if defined(NDEBUG)
#if !defined(_Error_Handler)
#define _Error_Handler(str, value) \
  while (1) {\
  }
#endif
#if !defined(Error_Handler)
#define Error_Handler() \
  while (1) {\
  }
#endif
#else
void _Error_Handler(const char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //_STM32_DEF_
