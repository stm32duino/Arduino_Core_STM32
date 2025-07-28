#ifndef _STM32_DEF_
#define _STM32_DEF_


/**
 * @brief STM32 core version number
 */
#define STM32_CORE_VERSION_MAJOR    (0x02U) /*!< [31:24] major version */
#define STM32_CORE_VERSION_MINOR    (0x0CU) /*!< [23:16] minor version */
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

#if defined(STM32C0xx)
  #include "stm32c0xx.h"
#elif defined(STM32F0xx)
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
#elif defined(STM32H5xx)
  #include "stm32h5xx.h"
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
#elif defined(STM32U0xx)
  #include "stm32u0xx.h"
#elif defined(STM32U3xx)
  #include "stm32u3xx.h"
#elif defined(STM32U5xx)
  #include "stm32u5xx.h"
#elif defined(STM32WB0x)
  #include "stm32wb0x.h"
#elif defined(STM32WBxx)
  #include "stm32wbxx.h"
#elif defined(STM32WBAxx)
  #include "stm32wbaxx.h"
#elif defined(STM32WLxx)
  #include "stm32wlxx.h"
#else
  #error "STM32YYxx chip series is not defined in boards.txt."
#endif

#ifndef F_CPU
  #define F_CPU SystemCoreClock
#endif

// Here define some compatibility
#if !defined (ADC1) && defined (ADC)
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

#if defined(STM32U0xx)
#define RCC_CR_HSIDY_Pos RCC_CR_HSIRDY_Pos
#include "stm32yyxx_ll_rtc.h"
#if !defined(LL_RTC_BINARY_NONE)
  #define LL_RTC_BINARY_NONE RTC_BINARY_NONE
#endif
#if !defined(LL_RTC_BINARY_ONLY)
  #define LL_RTC_BINARY_ONLY RTC_BINARY_ONLY
#endif
#if !defined(LL_RTC_BINARY_MIX)
  #define LL_RTC_BINARY_MIX RTC_BINARY_MIX
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_0)
  #define LL_RTC_BINARY_MIX_BCDU_0 RTC_BINARY_MIX_BCDU_0
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_1)
  #define LL_RTC_BINARY_MIX_BCDU_1 RTC_BINARY_MIX_BCDU_1
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_2)
  #define LL_RTC_BINARY_MIX_BCDU_2 RTC_BINARY_MIX_BCDU_2
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_3)
  #define LL_RTC_BINARY_MIX_BCDU_3 RTC_BINARY_MIX_BCDU_3
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_4)
  #define LL_RTC_BINARY_MIX_BCDU_4 RTC_BINARY_MIX_BCDU_4
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_5)
  #define LL_RTC_BINARY_MIX_BCDU_5 RTC_BINARY_MIX_BCDU_5
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_6)
  #define LL_RTC_BINARY_MIX_BCDU_6 RTC_BINARY_MIX_BCDU_6
#endif
#if !defined(LL_RTC_BINARY_MIX_BCDU_7)
  #define LL_RTC_BINARY_MIX_BCDU_7 RTC_BINARY_MIX_BCDU_7
#endif

/**
  * @brief  Get Binary mode (Sub Second Register)
  * @rmtoll RTC_ICSR           BIN           LL_RTC_GetBinaryMode
  * @param  RTCx RTC Instance
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RTC_GetBinaryMode(const RTC_TypeDef *RTCx)
{
  return (uint32_t)(READ_BIT(RTCx->ICSR, RTC_ICSR_BIN));
}

/**
  * @brief  Set Binary mode (Sub Second Register)
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function).
  * @rmtoll RTC_ICSR           BIN           LL_RTC_SetBinaryMode
  * @param  RTCx RTC Instance
  * @param  BinaryMode can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_NONE
  *         @arg @ref LL_RTC_BINARY_ONLY
  *         @arg @ref LL_RTC_BINARY_MIX
  * @retval None
  */
__STATIC_INLINE void LL_RTC_SetBinaryMode(RTC_TypeDef *RTCx, uint32_t BinaryMode)
{
  MODIFY_REG(RTCx->ICSR, RTC_ICSR_BIN, BinaryMode);
}

/**
  * @brief  Set Binary Mix mode BCDU
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref LL_RTC_EnableInitMode function).
  * @rmtoll RTC_ICSR           BCDU          LL_RTC_SetBinMixBCDU
  * @param  RTCx RTC Instance
  * @param  BinMixBcdU can be one of the following values:
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_0
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_1
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_2
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_3
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_4
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_5
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_6
  *         @arg @ref LL_RTC_BINARY_MIX_BCDU_7
  * @retval None
  */
__STATIC_INLINE void LL_RTC_SetBinMixBCDU(RTC_TypeDef *RTCx, uint32_t BinMixBcdU)
{
  MODIFY_REG(RTCx->ICSR, RTC_ICSR_BCDU, BinMixBcdU);
}
#endif // STM32U0xx

/* STM32G0xx, STM32U0xx and some STM32U5xx defined USB_DRD_FS */
#if !defined(USB) && defined(USB_DRD_FS)
  #define USB USB_DRD_FS
  #define PinMap_USB PinMap_USB_DRD_FS
  #if defined(STM32H5xx) || defined(STM32U0xx) ||\
    defined(STM32U3xx) || defined(STM32U5xx)
    #define USB_BASE USB_DRD_BASE
    #if !defined(__HAL_RCC_USB_CLK_ENABLE)
      #if defined(__HAL_RCC_USB_FS_CLK_ENABLE)
        #define __HAL_RCC_USB_CLK_ENABLE __HAL_RCC_USB_FS_CLK_ENABLE
        #define __HAL_RCC_USB_CLK_DISABLE __HAL_RCC_USB_FS_CLK_DISABLE
      #endif
      #if defined(__HAL_RCC_USB1_CLK_ENABLE)
        #define __HAL_RCC_USB_CLK_ENABLE __HAL_RCC_USB1_CLK_ENABLE
        #define __HAL_RCC_USB_CLK_DISABLE __HAL_RCC_USB1_CLK_DISABLE
      #endif
    #endif
  #endif
#endif

/**
 * Some mcu have single AF and thus only AF mode should be configured.
 * No AFRL/AFRG registers exists so they should not be configured.
 * In that case the AF does not exists so defining the linked AF
 * to 0x7F (max value of the AFNUM i.e. STM_PIN_AFNUM_MASK)
 * See GitHub issue #1798.
 */
#if defined(STM32F0xx) && !defined(GPIO_AF0_TIM3)
  #define GPIO_AF0_TIM3 STM_PIN_AFNUM_MASK
#endif
#if defined(STM32L0xx) && !defined(GPIO_AF1_SPI1)
  #define GPIO_AF1_SPI1 STM_PIN_AFNUM_MASK
#endif

#if defined(STM32C0xx) && defined(USART3) && !defined(GPIO_AF7_USART3)
  #define GPIO_AF7_USART3 ((uint8_t)0x07)
#endif // STM32C0xx && !defined(USART3)

#if defined(STM32WBAxx) && defined(USB_OTG_HS) && !defined(GPIO_AF4_USB_OTG_HS)
  #define GPIO_AF4_USB_OTG_HS GPIO_AF4_OTG_HS
#endif // STM32WBAxx && defined(USB_OTG_HS) && !defined(GPIO_AF4_USB_OTG_HS)

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
    (void)str;\
    (void)value;\
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
