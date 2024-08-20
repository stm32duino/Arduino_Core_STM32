/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBAxx_LL_RCC_H
#define STM32WBAxx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx.h"

/** @addtogroup STM32WBAxx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Constants RCC Private Constants
  * @{
  */
/* Defines used to perform offsets*/
/* Offset used to access to RCC_CCIPR1, RCC_CCIPR2 and RCC_CCIPR3 registers */
#define RCC_OFFSET_CCIPR1       0U
#define RCC_OFFSET_CCIPR2       0x04U
#define RCC_OFFSET_CCIPR3       0x08U

/* Defines used for security configuration extension */
#define RCC_SECURE_MASK         0x10FBU
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Exported_Types RCC Exported Types
  * @{
  */

/** @defgroup LL_ES_CLOCK_FREQ Clocks Frequency Structure
  * @{
  */

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct
{
  uint32_t SYSCLK_Frequency;        /*!< SYSCLK clock frequency */
  uint32_t HCLK_Frequency;          /*!< HCLK clock frequency */
  uint32_t PCLK1_Frequency;         /*!< PCLK1 clock frequency */
  uint32_t PCLK2_Frequency;         /*!< PCLK2 clock frequency */
  uint32_t PCLK7_Frequency;         /*!< PCLK7 clock frequency */
} LL_RCC_ClocksTypeDef;

/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_OSC_VALUES Oscillator Values adaptation
  * @brief    Defines used to adapt values of different oscillators
  * @note     These values could be modified in the user environment according to
  *           HW set-up.
  * @{
  */
#if !defined (HSE_VALUE)
#define HSE_VALUE    32000000U  /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined (HSI_VALUE)
#define HSI_VALUE    16000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

#if defined (RCC_LSI2_SUPPORT)
#if !defined (LSI2_VALUE)
#define LSI2_VALUE   32000U    /*!< Value of the LSI2 oscillator in Hz */
#endif /* LSI_VALUE */
#endif

#if !defined (EXTERNAL_SAI1_CLOCK_VALUE)
#define EXTERNAL_SAI1_CLOCK_VALUE    48000U /*!< Value of the SAI1_EXTCLK external oscillator in Hz */
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_WriteReg function
  * @{
  */
#define LL_RCC_CICR_LSI1RDYC               RCC_CICR_LSI1RDYC    /*!< LSI1 Ready Interrupt Clear */
#define LL_RCC_CICR_LSERDYC                RCC_CICR_LSERDYC     /*!< LSE Ready Interrupt Clear */
#define LL_RCC_CICR_HSIRDYC                RCC_CICR_HSIRDYC     /*!< HSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSERDYC                RCC_CICR_HSERDYC     /*!< HSE Ready Interrupt Clear */
#define LL_RCC_CICR_PLL1RDYC               RCC_CICR_PLL1RDYC    /*!< PLL1 Ready Interrupt Clear */
#define LL_RCC_CICR_HSECSSC                RCC_CICR_HSECSSC     /*!< HSE Clock Security System Interrupt Clear */
#define LL_RCC_CICR_LSI2RDYC               RCC_CICR_LSI2RDYC    /*!< LSI2 Ready Interrupt Clear */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg function
  * @{
  */
#define LL_RCC_CIFR_LSI1RDYF               RCC_CIFR_LSI1RDYF    /*!< LSI1 Ready Interrupt flag */
#define LL_RCC_CIFR_LSERDYF                RCC_CIFR_LSERDYF     /*!< LSE Ready Interrupt flag */
#define LL_RCC_CIFR_HSIRDYF                RCC_CIFR_HSIRDYF     /*!< HSI Ready Interrupt flag */
#define LL_RCC_CIFR_HSERDYF                RCC_CIFR_HSERDYF     /*!< HSE Ready Interrupt flag */
#define LL_RCC_CIFR_PLL1RDYF               RCC_CIFR_PLL1RDYF    /*!< PLL1 Ready Interrupt flag */
#define LL_RCC_CIFR_HSECSSF                RCC_CIFR_HSECSSF     /*!< HSE Clock Security System Interrupt flag */
#define LL_RCC_CIFR_LSI2RDYF               RCC_CIFR_LSI2RDYF    /*!< LSI2 Ready Interrupt flag */
#define LL_RCC_CSR_OBLRSTF                 RCC_CSR_OBLRSTF      /*!< Option byte loader reset flag */
#define LL_RCC_CSR_PINRSTF                 RCC_CSR_PINRSTF      /*!< NRST pin reset flag */
#define LL_RCC_CSR_BORRSTF                 RCC_CSR_BORRSTF      /*!< BOR reset flag */
#define LL_RCC_CSR_SFTRSTF                 RCC_CSR_SFTRSTF      /*!< Software reset flag */
#define LL_RCC_CSR_IWDGRSTF                RCC_CSR_IWDGRSTF     /*!< Independent watchdog reset flag */
#if defined(WWDG)
#define LL_RCC_CSR_WWDGRSTF                RCC_CSR_WWDGRSTF     /*!< Window watchdog reset flag */
#endif /* defined(WWDG) */
#define LL_RCC_CSR_LPWRRSTF                RCC_CSR_LPWRRSTF     /*!< Low-power reset flag */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIER_LSI1RDYIE              RCC_CIER_LSI1RDYIE     /*!< LSI1 Ready Interrupt Enable */
#define LL_RCC_CIER_LSERDYIE               RCC_CIER_LSERDYIE      /*!< LSE Ready Interrupt Enable */
#define LL_RCC_CIER_HSIRDYIE               RCC_CIER_HSIRDYIE      /*!< HSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSERDYIE               RCC_CIER_HSERDYIE      /*!< HSE Ready Interrupt Enable */
#define LL_RCC_CIER_PLL1RDYIE              RCC_CIER_PLL1RDYIE     /*!< PLL1 Ready Interrupt Enable */
#define LL_RCC_CIER_LSI2RDYIE              RCC_CIER_LSI2RDYIE     /*!< LSI2 Ready Interrupt Enable */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSIPRE  LSI prescaler
  * @{
  */
#define LL_RCC_LSI_DIV_1                   0U                     /*!< LSI1 divided by 1   */
#define LL_RCC_LSI_DIV_128                 RCC_BDCR1_LSI1PREDIV   /*!< LSI1 divided by 128 */
/**
  * @}
  */

#if defined(RCC_BDCR2_LSI2CFG)
/** @defgroup RCC_LL_EC_LSI2CFG  LSI2 oscillator temperature sensitivity configuration
  * @{
  */
#define LL_RCC_LSI2_TEMP_SENSITIVITY_80    0U                    /*!< LSI2 frequency temperature sensitivity is close to zero at +80 degrees C */
#define LL_RCC_LSI2_TEMP_SENSITIVITY_50    RCC_BDCR2_LSI2CFG_0   /*!< LSI2 frequency temperature sensitivity is close to zero at +50 degrees C */
#define LL_RCC_LSI2_TEMP_SENSITIVITY_20    RCC_BDCR2_LSI2CFG_1   /*!< LSI2 frequency temperature sensitivity is close to zero at +20 degrees C */
/**
  * @}
  */
#endif /* RCC_BDCR2_LSI2CFG */

#if defined(RCC_BDCR2_LSI2MODE)
/** @defgroup RCC_LL_EC_LSI2MODE  LSI2 oscillator operating mode configuration
  * @{
  */
#define LL_RCC_LSI2_NOMINAL_MODE           0U                     /*!< LSI2 nominal power, high accuracy  */
#define LL_RCC_LSI2_LOWPOWER_MODE          RCC_BDCR2_LSI2MODE_0   /*!< LSI2 low power, medium accuracy    */
#define LL_RCC_LSI2_ULTRALOWPOWER_MODE     RCC_BDCR2_LSI2MODE_1   /*!< LSI2 ultra low power, low accuracy */
/**
  * @}
  */
#endif /* RCC_BDCR2_LSI2MODE */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR1_LSEDRV_0     /*!< Xtal mode medium low driving capability  */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR1_LSEDRV_1     /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_BDCR1_LSEDRV       /*!< Xtal mode higher driving capability      */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI          0U                   /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE          RCC_BDCR1_LSCOSEL    /*!< LSE selection for low speed clock  */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_HSI           0U                                  /*!< HSI selection as system clock  */
#define LL_RCC_SYS_CLKSOURCE_HSE           RCC_CFGR1_SW_1                      /*!< HSE selection as system clock   */
#define LL_RCC_SYS_CLKSOURCE_PLL1R         (RCC_CFGR1_SW_1 | RCC_CFGR1_SW_0)   /*!< PLL1R selection as system clock */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI    0U                                   /*!< HSI used as system clock  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE    RCC_CFGR1_SWS_1                      /*!< HSE used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL1R  (RCC_CFGR1_SWS_1 | RCC_CFGR1_SWS_0)  /*!< PLL1R used as system clock */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_SYSCLK_DIV_1                0U                                                       /*!< SYSCLK not divided   */
#define LL_RCC_SYSCLK_DIV_2                RCC_CFGR2_HPRE_2                                         /*!< SYSCLK divided by 2  */
#define LL_RCC_SYSCLK_DIV_4                (RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0)                    /*!< SYSCLK divided by 4  */
#define LL_RCC_SYSCLK_DIV_8                (RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1)                    /*!< SYSCLK divided by 8  */
#define LL_RCC_SYSCLK_DIV_16               (RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0) /*!< SYSCLK divided by 16 */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYSTICK_CLKSOURCE  SYSTICK clock source selection
  * @{
  */
#define LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8  0U                      /*!< HCLKDIV8 clock used as SYSTICK clock source */
#define LL_RCC_SYSTICK_CLKSOURCE_LSI       RCC_CCIPR1_SYSTICKSEL_0 /*!< LSI clock used as SYSTICK clock source        */
#define LL_RCC_SYSTICK_CLKSOURCE_LSE       RCC_CCIPR1_SYSTICKSEL_1 /*!< LSE clock used as SYSTICK clock source        */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB1 prescaler
  * @{
  */
#define LL_RCC_APB1_DIV_1                  0U                                                          /*!< HCLK not divided   */
#define LL_RCC_APB1_DIV_2                  RCC_CFGR2_PPRE1_2                                           /*!< HCLK divided by 2  */
#define LL_RCC_APB1_DIV_4                  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_0)                     /*!< HCLK divided by 4  */
#define LL_RCC_APB1_DIV_8                  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1)                     /*!< HCLK divided by 8  */
#define LL_RCC_APB1_DIV_16                 (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1 | RCC_CFGR2_PPRE1_0) /*!< HCLK divided by 16 */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_APB2_DIV  APB2 prescaler
  * @{
  */
#define LL_RCC_APB2_DIV_1                  0U                                                          /*!< HCLK not divided   */
#define LL_RCC_APB2_DIV_2                  RCC_CFGR2_PPRE2_2                                           /*!< HCLK divided by 2  */
#define LL_RCC_APB2_DIV_4                  (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_0)                     /*!< HCLK divided by 4  */
#define LL_RCC_APB2_DIV_8                  (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1)                     /*!< HCLK divided by 8  */
#define LL_RCC_APB2_DIV_16                 (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1 | RCC_CFGR2_PPRE2_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB7_DIV  APB7 prescaler
  * @{
  */
#define LL_RCC_APB7_DIV_1                  0U                                                          /*!< HCLK not divided   */
#define LL_RCC_APB7_DIV_2                  RCC_CFGR3_PPRE7_2                                           /*!< HCLK divided by 2  */
#define LL_RCC_APB7_DIV_4                  (RCC_CFGR3_PPRE7_2 | RCC_CFGR3_PPRE7_0)                     /*!< HCLK divided by 4  */
#define LL_RCC_APB7_DIV_8                  (RCC_CFGR3_PPRE7_2 | RCC_CFGR3_PPRE7_1)                     /*!< HCLK divided by 8  */
#define LL_RCC_APB7_DIV_16                 (RCC_CFGR3_PPRE7_2 | RCC_CFGR3_PPRE7_1 | RCC_CFGR3_PPRE7_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_AHB5_DIV  AHB5 prescaler when SYSCLK is PLL1R
  * @{
  */
#define LL_RCC_AHB5_DIV_1                  0U                                                          /*!< SYSCLK not divided  */
#define LL_RCC_AHB5_DIV_2                  RCC_CFGR4_HPRE5_2                                           /*!< SYSCLK divided by 2 */
#define LL_RCC_AHB5_DIV_3                  (RCC_CFGR4_HPRE5_2 | RCC_CFGR4_HPRE5_0)                     /*!< SYSCLK divided by 3 */
#define LL_RCC_AHB5_DIV_4                  (RCC_CFGR4_HPRE5_2 | RCC_CFGR4_HPRE5_1)                     /*!< SYSCLK divided by 4 */
#define LL_RCC_AHB5_DIV_6                  (RCC_CFGR4_HPRE5_2 | RCC_CFGR4_HPRE5_1 | RCC_CFGR4_HPRE5_0) /*!< SYSCLK divided by 6 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_AHB5_DIVIDER  AHB5 divider when SYSCLK is HSI or HSE
  * @{
  */
#define LL_RCC_AHB5_DIVIDER_1              0U                                                          /*!< SYSCLK not divided  */
#define LL_RCC_AHB5_DIVIDER_2              RCC_CFGR4_HDIV5                                             /*!< SYSCLK divided by 2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK          0U                                                           /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCO1SOURCE_SYSCLK           RCC_CFGR1_MCOSEL_0                                           /*!< SYSCLK selection as MCO1 source      */
#define LL_RCC_MCO1SOURCE_HSI              (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_1)                    /*!< HSI selection as MCO1 source         */
#define LL_RCC_MCO1SOURCE_HSE              RCC_CFGR1_MCOSEL_2                                           /*!< HSE selection as MCO1 source         */
#define LL_RCC_MCO1SOURCE_PLL1R            (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_2)                    /*!< PLL1RCLK selection as MCO1 source    */
#define LL_RCC_MCO1SOURCE_LSI              (RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_2)                    /*!< LSI selection as MCO1 source         */
#define LL_RCC_MCO1SOURCE_LSE              (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_1| RCC_CFGR1_MCOSEL_2)/*!< LSE selection as MCO1 source         */
#define LL_RCC_MCO1SOURCE_PLL1P            RCC_CFGR1_MCOSEL_3                                           /*!< PLL1PCLK selection as MCO1 source    */
#define LL_RCC_MCO1SOURCE_PLL1Q            (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_3)                    /*!< PLL1QCLK selection as MCO1 source    */
#define LL_RCC_MCO1SOURCE_HCLK5            (RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_3)                    /*!< HCLK5 selection as MCO1 source       */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1_DIV_1                  0U                                              /*!< MCO not divided   */
#define LL_RCC_MCO1_DIV_2                  RCC_CFGR1_MCOPRE_0                              /*!< MCO divided by 2  */
#define LL_RCC_MCO1_DIV_4                  RCC_CFGR1_MCOPRE_1                              /*!< MCO divided by 4  */
#define LL_RCC_MCO1_DIV_8                  (RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0)       /*!< MCO divided by 8  */
#define LL_RCC_MCO1_DIV_16                 RCC_CFGR1_MCOPRE_2                              /*!< MCO divided by 16 */
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO         0U                 /*!< No clock enabled for the peripheral            */
#define LL_RCC_PERIPH_FREQUENCY_NA         0xFFFFFFFFU        /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE          0U                      /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE           RCC_BDCR1_RTCSEL_0      /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI           RCC_BDCR1_RTCSEL_1      /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV32     RCC_BDCR1_RTCSEL        /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RADIO_SLEEPTIMER_CLKSOURCE  RADIO Sleep Timer Clock source
  * @{
  */
#define LL_RCC_RADIOSLEEPSOURCE_NONE        0U                      /*!< No clock selected, 2.4 GHz RADIO sleep timer kernel clock disabled */
#define LL_RCC_RADIOSLEEPSOURCE_LSE         RCC_BDCR1_RADIOSTSEL_0  /*!< LSE oscillator clock selected */
#define LL_RCC_RADIOSLEEPSOURCE_LSI         RCC_BDCR1_RADIOSTSEL_1  /*!< LSI oscillator clock selected */
#define LL_RCC_RADIOSLEEPSOURCE_HSE_DIV1000 RCC_BDCR1_RADIOSTSEL    /*!< HSE oscillator clock divided by 1000 selected */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USART_CLKSOURCE  Peripheral USARTx clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2   (RCC_CCIPR1_USART1SEL << 16U)                            /*!< PCLK2 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_SYSCLK  ((RCC_CCIPR1_USART1SEL << 16U) | RCC_CCIPR1_USART1SEL_0) /*!< SYSCLK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSI     ((RCC_CCIPR1_USART1SEL << 16U) | RCC_CCIPR1_USART1SEL_1) /*!< HSI clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_LSE     ((RCC_CCIPR1_USART1SEL << 16U) | RCC_CCIPR1_USART1SEL)   /*!< LSE clock used as USART1 clock source */
#if defined(USART2)
#define LL_RCC_USART2_CLKSOURCE_PCLK1   (RCC_CCIPR1_USART2SEL << 16U)                            /*!< PCLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_SYSCLK  ((RCC_CCIPR1_USART2SEL << 16U) | RCC_CCIPR1_USART2SEL_0) /*!< SYSCLK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSI     ((RCC_CCIPR1_USART2SEL << 16U) | RCC_CCIPR1_USART2SEL_1) /*!< HSI clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_LSE     ((RCC_CCIPR1_USART2SEL << 16U) | RCC_CCIPR1_USART2SEL)   /*!< LSE clock used as USART2 clock source */
#endif /* USART2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART_CLKSOURCE  Peripheral LPUARTx clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK7  0U                                                  /*!< PCLK3 clock used as LPUART1 clock source  */
#define LL_RCC_LPUART1_CLKSOURCE_SYSCLK RCC_CCIPR3_LPUART1SEL_0                             /*!< SYSCLK clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSI    RCC_CCIPR3_LPUART1SEL_1                             /*!< HSI clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_LSE    (RCC_CCIPR3_LPUART1SEL_0 | RCC_CCIPR3_LPUART1SEL_1) /*!< LSE clock used as LPUART1 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C_CLKSOURCE  Peripheral I2Cx clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1     ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U))                                                    /*!< PCLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_SYSCLK    ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | (RCC_CCIPR1_I2C1SEL_0 >> RCC_CCIPR1_I2C1SEL_Pos)) /*!< SYSCLK clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_HSI       ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | (RCC_CCIPR1_I2C1SEL_1 >> RCC_CCIPR1_I2C1SEL_Pos)) /*!< HSI clock used as I2C1 clock source */
#define LL_RCC_I2C3_CLKSOURCE_PCLK7     ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U))                                                    /*!< PCLK7 clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_SYSCLK    ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | (RCC_CCIPR3_I2C3SEL_0 >> RCC_CCIPR3_I2C3SEL_Pos)) /*!< SYSCLK clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_HSI       ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | (RCC_CCIPR3_I2C3SEL_1 >> RCC_CCIPR3_I2C3SEL_Pos)) /*!< HSI clock used as I2C3 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPI_CLKSOURCE  Peripheral SPIx clock source selection
  * @{
  */
#if defined(SPI1)
#define LL_RCC_SPI1_CLKSOURCE_PCLK2     ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U))                                                    /*!< PCLK2 clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_SYSCLK    ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | (RCC_CCIPR1_SPI1SEL_0 >> RCC_CCIPR1_SPI1SEL_Pos)) /*!< SYSCLK clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_HSI       ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | (RCC_CCIPR1_SPI1SEL_1 >> RCC_CCIPR1_SPI1SEL_Pos)) /*!< HSI clock used as SPI1 clock source */
#endif /* SPI1 */
#define LL_RCC_SPI3_CLKSOURCE_PCLK7     ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U))                                                    /*!< PCLK7 clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_SYSCLK    ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | (RCC_CCIPR3_SPI3SEL_0 >> RCC_CCIPR3_SPI3SEL_Pos)) /*!< SYSCLK clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_HSI       ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | (RCC_CCIPR3_SPI3SEL_1 >> RCC_CCIPR3_SPI3SEL_Pos)) /*!< HSI clock used as SPI3 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM_CLKSOURCE  Peripheral LPTIMx clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK7   ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U))                                                           /*!< PCLK7 clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI     ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | (RCC_CCIPR3_LPTIM1SEL_0 >> RCC_CCIPR3_LPTIM1SEL_Pos))    /*!< LSI clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM1_CLKSOURCE_HSI     ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | (RCC_CCIPR3_LPTIM1SEL_1 >> RCC_CCIPR3_LPTIM1SEL_Pos))    /*!< HSI clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE     ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | (RCC_CCIPR3_LPTIM1SEL >> RCC_CCIPR3_LPTIM1SEL_Pos))      /*!< LSE clock used as LPTIM1 clock source  */
#if defined(LPTIM2)
#define LL_RCC_LPTIM2_CLKSOURCE_PCLK1   ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U))                                                           /*!< PCLK1 clock used as LPTIM2 clock source */
#define LL_RCC_LPTIM2_CLKSOURCE_LSI     ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | (RCC_CCIPR1_LPTIM2SEL_0 >> RCC_CCIPR1_LPTIM2SEL_Pos))    /*!< LSI clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_HSI     ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | (RCC_CCIPR1_LPTIM2SEL_1 >> RCC_CCIPR1_LPTIM2SEL_Pos))    /*!< HSI clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_LSE     ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | (RCC_CCIPR1_LPTIM2SEL >> RCC_CCIPR1_LPTIM2SEL_Pos))      /*!< LSE clock used as LPTIM2 clock source  */
#endif /* LPTIM2 */
/**
  * @}
  */

#if defined(SAI1)
/** @defgroup RCC_LL_EC_SAI_CLKSOURCE  Peripheral SAIx clock source selection
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE_PLL1P     (RCC_CCIPR2_SAI1SEL << 16U)                          /*!< PLL1P clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_PLL1Q     ((RCC_CCIPR2_SAI1SEL << 16U) | RCC_CCIPR2_SAI1SEL_0) /*!< PLL1Q clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_SYSCLK    ((RCC_CCIPR2_SAI1SEL << 16U) | RCC_CCIPR2_SAI1SEL_1) /*!< System clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_PIN       ((RCC_CCIPR2_SAI1SEL << 16U) | (RCC_CCIPR2_SAI1SEL_1 | RCC_CCIPR2_SAI1SEL_0))  /*!< External input clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_HSI       ((RCC_CCIPR2_SAI1SEL << 16U) | RCC_CCIPR2_SAI1SEL_2) /*!< HSI clock used as SAI1 clock source */
/**
  * @}
  */
#endif /* SAI1 */


/** @defgroup RCC_LL_EC_RNG_CLKSOURCE  Peripheral RNG clock source selection
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE_LSE        0U                     /*!< LSE clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_LSI        RCC_CCIPR2_RNGSEL_0    /*!< LSI clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_HSI        RCC_CCIPR2_RNGSEL_1    /*!< HSI clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_PLL1Q_DIV2 (RCC_CCIPR2_RNGSEL_1 | RCC_CCIPR2_RNGSEL_0)    /*!< PLL1Q/2 clock used as RNG clock source */
/**
  * @}
  */
/** Legacy definitions for compatibility purpose
@cond 0
  */
#define LL_RCC_RNG_CLKSOURCE_PLL1Q      LL_RCC_RNG_CLKSOURCE_PLL1Q_DIV2
/**
@endcond
  */

/** @defgroup RCC_LL_EC_ADC_CLKSOURCE  Peripheral ADC4 clock source selection
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_HCLK       0U                                             /*!< HCLK1 clock used as ADC4 clock source */
#define LL_RCC_ADC_CLKSOURCE_SYSCLK     RCC_CCIPR3_ADCSEL_0                            /*!< SYSCLK clock used as ADC4 clock source */
#define LL_RCC_ADC_CLKSOURCE_PLL1P      RCC_CCIPR3_ADCSEL_1                            /*!< PLL1P clock used as ADC4 clock source */
#define LL_RCC_ADC_CLKSOURCE_HSI        RCC_CCIPR3_ADCSEL_2                            /*!< HSI clock used as ADC4 clock source */
#define LL_RCC_ADC_CLKSOURCE_HSE        (RCC_CCIPR3_ADCSEL_1 | RCC_CCIPR3_ADCSEL_0)    /*!< HSE clock used as ADC4 clock source */
/**
  * @}
  */



/** @defgroup RCC_LL_EC_TIM_INPUT_CAPTURE_CLOCKSource TIM Input capture clock source selection
  * @{
  */
#define LL_RCC_TIMIC_CLKSOURCE_NONE       0U                       /*!< No clock available for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256 RCC_CCIPR1_TIMICSEL      /*!< HSI/256 selected for TIM16/TIM17 and LPTIM2 input capture */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USART Peripheral USARTx get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE         RCC_CCIPR1_USART1SEL /*!< USART1 Clock source selection */
#if defined(USART2)
#define LL_RCC_USART2_CLKSOURCE         RCC_CCIPR1_USART2SEL /*!< USART2 Clock source selection */
#endif /* USART2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPI Peripheral SPIx get clock source
  * @{
  */
#if defined(SPI1)
#define LL_RCC_SPI1_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | (RCC_CCIPR1_SPI1SEL >> RCC_CCIPR1_SPI1SEL_Pos)) /*!< SPI1 Clock source selection */
#endif /* SPI1 */
#define LL_RCC_SPI3_CLKSOURCE           ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | (RCC_CCIPR3_SPI3SEL >> RCC_CCIPR3_SPI3SEL_Pos)) /*!< SPI3 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART Peripheral LPUARTx get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE        RCC_CCIPR3_LPUART1SEL /*!< LPUART1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C Peripheral I2Cx get clock source
  * @{
  */
#if defined(I2C1)
#define LL_RCC_I2C1_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | (RCC_CCIPR1_I2C1SEL >> RCC_CCIPR1_I2C1SEL_Pos)) /*!< I2C1 Clock source selection */
#endif /* I2C1 */
#define LL_RCC_I2C3_CLKSOURCE           ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | (RCC_CCIPR3_I2C3SEL >> RCC_CCIPR3_I2C3SEL_Pos)) /*!< I2C3 Clock source selection */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM Peripheral LPTIMx get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | (RCC_CCIPR3_LPTIM1SEL >> RCC_CCIPR3_LPTIM1SEL_Pos)) /*!< LPTIM1 Clock source selection */
#if defined(LPTIM2)
#define LL_RCC_LPTIM2_CLKSOURCE         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | (RCC_CCIPR1_LPTIM2SEL >> RCC_CCIPR1_LPTIM2SEL_Pos)) /*!< LPTIM2 Clock source selection */
#endif /* LPTIM2 */
/**
  * @}
  */

#if defined(SAI1)
/** @defgroup RCC_LL_EC_SAI  Peripheral SAIx get clock source
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE           RCC_CCIPR2_SAI1SEL /*!< SAI1 Clock source selection */
/**
  * @}
  */
#endif /* SAI1 */

/** @defgroup RCC_LL_EC_RNG  Peripheral RNG get clock source
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE            RCC_CCIPR2_RNGSEL    /*!< RNG Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC  Peripheral ADC get clock source
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE            RCC_CCIPR3_ADCSEL /*!< ADCs Clock source selection */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_PLL1SOURCE  PLL1 entry clock source
  * @{
  */
#define LL_RCC_PLL1SOURCE_NONE          0U                                                /*!< No clock selected as PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_HSI           RCC_PLL1CFGR_PLL1SRC_1                            /*!< HSI clock selected as PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_HSE           (RCC_PLL1CFGR_PLL1SRC_0 | RCC_PLL1CFGR_PLL1SRC_1) /*!< HSE clock selected as PLL1 entry clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLINPUTRANGE   All PLLs input ranges
  * @{
  */
#define LL_RCC_PLLINPUTRANGE_4_8        2U                    /*!< VCO input range: 4 to 8 MHz  */
#define LL_RCC_PLLINPUTRANGE_8_16       3U                    /*!< VCO input range: 8 to 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1RCLKPRESTEP   PLL1RCLK prescaler steps division
  * @{
  */
#define LL_RCC_PLL1RCLK_2_STEP_DIV      0U                            /*!< PLL1RCLK 2-step division */
#define LL_RCC_PLL1RCLK_3_STEP_DIV      RCC_PLL1CFGR_PLL1RCLKPRESTEP  /*!< PLL1RCLK 3-step division */
/**
  * @}
  */

/** @defgroup RCC_LSE_Trimming LSE Trimming
  * @{
  */
#define LL_RCC_LSETRIMMING_R            0U                    /*!< Current source resistance R       */
#define LL_RCC_LSETRIMMING_3_4_R        RCC_BDCR1_LSETRIM_0   /*!< Current source resistance 3/4 * R */
#define LL_RCC_LSETRIMMING_2_3_R        RCC_BDCR1_LSETRIM_1   /*!< Current source resistance 2/3 * R */
#define LL_RCC_LSETRIMMING_1_2_R        RCC_BDCR1_LSETRIM     /*!< Current source resistance 1/2 * R */
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Security_Services Security Services
  * @note Only available when system implements security (TZEN=1)
  * @{
  */
#define LL_RCC_ALL_NSEC                 0U                      /*!< No security on RCC resources (default) */
#define LL_RCC_ALL_SEC                  RCC_SECURE_MASK         /*!< Security on all RCC resources          */

#define LL_RCC_HSI_SEC                  RCC_SECCFGR_HSISEC      /*!< HSI clock configuration secure-only access */
#define LL_RCC_HSI_NSEC                 0U                      /*!< HSI clock configuration secure/non-secure access */
#define LL_RCC_HSE_SEC                  RCC_SECCFGR_HSESEC      /*!< HSE clock configuration secure-only access */
#define LL_RCC_HSE_NSEC                 0U                      /*!< HSE clock configuration secure/non-secure access */
#define LL_RCC_LSE_SEC                  RCC_SECCFGR_LSESEC      /*!< LSE clock configuration secure-only access */
#define LL_RCC_LSE_NSEC                 0U                      /*!< LSE clock configuration secure/non-secure access */
#define LL_RCC_LSI_SEC                  RCC_SECCFGR_LSISEC      /*!< LSI clock configuration secure-only access */
#define LL_RCC_LSI_NSEC                 0U                      /*!< LSI clock configuration secure/non-secure access */
#define LL_RCC_SYSCLK_SEC               RCC_SECCFGR_SYSCLKSEC   /*!< SYSCLK clock; STOPWUCK and MCO output configuration secure-only access */
#define LL_RCC_SYSCLK_NSEC              0U                      /*!< SYSCLK clock; STOPWUCK and MCO output configuration secure/non-secure access */
#define LL_RCC_PRESCALERS_SEC           RCC_SECCFGR_PRESCSEC    /*!< AHBx/APBx prescaler configuration secure-only access */
#define LL_RCC_PRESCALERS_NSEC          0U                      /*!< AHBx/APBx prescaler configuration secure/non-secure access */
#define LL_RCC_PLL1_SEC                 RCC_SECCFGR_PLL1SEC     /*!< PLL1 clock configuration secure-only access */
#define LL_RCC_PLL1_NSEC                0U                      /*!< PLL1 clock configuration secure/non-secure access */
#define LL_RCC_RESET_FLAGS_SEC          RCC_SECCFGR_RMVFSEC     /*!< Remove reset flag secure-only access */
#define LL_RCC_RESET_FLAGS_NSEC         0U                      /*!< Remove reset flag secure/non-secure access */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RCC register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_RCC_WriteReg(__REG__, __VALUE__) WRITE_REG(RCC->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RCC register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RCC_ReadReg(__REG__) READ_REG(RCC->__REG__)
/**
  * @}
  */

/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */

/**
  * @brief  Helper macro to calculate the PLL1RCLK frequency on system domain
  * @note ex: @ref __LL_RCC_CALC_PLL1RCLK_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetR ());
  * @param __INPUTFREQ__ PLL1 Input frequency (based on HSE/HSI)
  * @param __PLL1M__ parameter can be a value between 1 and 16
  * @param __PLL1N__ parameter can be a value between 4 and 512
  * @param __PLL1R__ parameter can be a value between 1 and 128
  * @retval PLL1R clock frequency (in Hz)
  */

#define __LL_RCC_CALC_PLL1RCLK_FREQ(__INPUTFREQ__, __PLL1M__, __PLL1N__, __PLL1R__) ((((__INPUTFREQ__) /(__PLL1M__)) * (__PLL1N__)) / (__PLL1R__))

/**
  * @brief  Helper macro to calculate the PLL1PCLK frequency
  * @note ex: @ref __LL_RCC_CALC_PLL1PCLK_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetP ());
  * @param __INPUTFREQ__ PLL1 Input frequency (based on HSE/HSI)
  * @param __PLL1M__ parameter can be a value between 1 and 16
  * @param __PLL1N__ parameter can be a value between 4 and 512
  * @param __PLL1P__ parameter can be a value between 2 and 128
  * @retval PLL1P clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLL1PCLK_FREQ(__INPUTFREQ__, __PLL1M__, __PLL1N__, __PLL1P__) ((((__INPUTFREQ__) /(__PLL1M__)) * (__PLL1N__)) / (__PLL1P__))

/**
  * @brief  Helper macro to calculate the PLL1QCLK frequency
  * @note ex: @ref __LL_RCC_CALC_PLL1QCLK_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetQ ());
  * @param __INPUTFREQ__ PLL1 Input frequency (based on HSE/HSI)
  * @param __PLL1M__ parameter can be a value between 1 and 16
  * @param __PLL1N__ parameter can be a value between 4 and 512
  * @param __PLL1Q__ parameter can be a value between 1 and 128
  * @retval PLL1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLL1QCLK_FREQ(__INPUTFREQ__, __PLL1M__, __PLL1N__, __PLL1Q__) ((((__INPUTFREQ__) /(__PLL1M__)) * (__PLL1N__)) / (__PLL1Q__))

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on HSE/HSI/PLLCLK)
  * @param  __AHBPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  * @retval HCLK clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK_FREQ(__SYSCLKFREQ__, __AHBPRESCALER__) ((__SYSCLKFREQ__) >> AHBPrescTable[((__AHBPRESCALER__) & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos])

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (ABP1)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB1PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APB1PRESCALER__) ((__HCLKFREQ__) >> (APBPrescTable[((__APB1PRESCALER__) & RCC_CFGR2_PPRE1) >>  RCC_CFGR2_PPRE1_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK2 frequency (ABP2)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB2PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  * @retval PCLK2 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK2_FREQ(__HCLKFREQ__, __APB2PRESCALER__) ((__HCLKFREQ__) >> APBPrescTable[(__APB2PRESCALER__) >>  RCC_CFGR2_PPRE2_Pos])


/**
  * @brief  Helper macro to calculate the PCLK7 frequency (ABP7)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB7PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB7_DIV_1
  *         @arg @ref LL_RCC_APB7_DIV_2
  *         @arg @ref LL_RCC_APB7_DIV_4
  *         @arg @ref LL_RCC_APB7_DIV_8
  *         @arg @ref LL_RCC_APB7_DIV_16
  * @retval PCLK3 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK7_FREQ(__HCLKFREQ__, __APB7PRESCALER__) ((__HCLKFREQ__) >> APBPrescTable[(__APB7PRESCALER__) >>  RCC_CFGR3_PPRE7_Pos])

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_LL_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         LL_RCC_HSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Disable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         LL_RCC_HSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Check if HSE oscillator Ready
  * @rmtoll CR           HSERDY        LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == RCC_CR_HSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSE clock prescaler for sysclk
  * @rmtoll CR           HSEPRE        LL_RCC_HSE_EnablePrescaler
  * @note   Control the division factor of the HSE32 clock for sysclk
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnablePrescaler(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEPRE);
}

/**
  * @brief  Check if HSE clock prescaler for sysclk is enabled
  * @rmtoll CR           HSEPRE        LL_RCC_HSE_IsEnabledPrescaler
  * @note   Check if the HSE32 clock for sysclk is divided by 2 or not
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabledPrescaler(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEPRE) == RCC_CR_HSEPRE) ? 1UL : 0UL);
}

/**
  * @brief  Disable HSE clock prescaler for sysclk
  * @rmtoll CR           HSEPRE        LL_RCC_HSE_DisablePrescaler
  * @note   Control the division factor of the HSE32 clock for sysclk
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisablePrescaler(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEPRE);
}

/**
  * @brief  Enable the Clock Security System.
  * @rmtoll CR           HSECSSON         LL_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @brief  Set HSE clock trimming
  * @note user-programmable capacitor trimming value.
  * @rmtoll ECSCR1        HSETRIM       LL_RCC_HSE_SetClockTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 63
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_SetClockTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ECSCR1, RCC_ECSCR1_HSETRIM, Value << RCC_ECSCR1_HSETRIM_Pos);
}

/**
  * @brief  Get HSE clock trimming
  * @rmtoll ECSCR1        HSETRIM       LL_RCC_HSE_GetClockTrimming
  * @retval Between Min_Data = 0 and Max_Data = 63
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetClockTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ECSCR1, RCC_ECSCR1_HSETRIM) >> RCC_ECSCR1_HSETRIM_Pos);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI even in stop mode
  * @note HSI oscillator is forced ON even in Stop mode
  * @rmtoll CR           HSIKERON      LL_RCC_HSI_EnableInStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_EnableInStopMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Disable HSI in stop mode
  * @rmtoll CR           HSIKERON      LL_RCC_HSI_DisableInStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_DisableInStopMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Check if HSI is enabled in stop mode
  * @rmtoll CR           HSIKERON        LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIKERON) == RCC_CR_HSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI oscillator
  * @rmtoll CR           HSION         LL_RCC_HSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Disable HSI oscillator
  * @rmtoll CR           HSION         LL_RCC_HSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Check if HSI clock is ready
  * @rmtoll CR           HSIRDY        LL_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RCC_CR_HSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll ICSCR3       HSICAL        LL_RCC_HSI_GetCalibration
  * @retval Between Min_Data = 0 and Max_Data = 4095
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR3, RCC_ICSCR3_HSICAL) >> RCC_ICSCR3_HSICAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value that is added to the HSICAL
  * @note Default value is 16, which, when added to the HSICAL value,
  *       should trim the HSI to 16 MHz +/- 1 %
  * @rmtoll ICSCR3        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 31
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ICSCR3, RCC_ICSCR3_HSITRIM, Value << RCC_ICSCR3_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll ICSCR3        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 31
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR3, RCC_ICSCR3_HSITRIM) >> RCC_ICSCR3_HSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable Low Speed External (LSE) crystal.
  * @rmtoll BDCR1        LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEON);
}

/**
  * @brief  Disable Low Speed External (LSE) crystal.
  * @rmtoll BDCR1        LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSEON);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll BDCR1        LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll BDCR1        LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSEBYP);
}

/**
  * @brief  Enable LSE clock glitch filter.
  * @rmtoll BDCR1        LSEGFON        LL_RCC_LSE_EnableGlitchFilter
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableGlitchFilter(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEGFON);
}

/**
  * @brief  Disable LSE clock glitch filter.
  * @rmtoll BDCR1        LSEGFON        LL_RCC_LSE_DisableGlitchFilter
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableGlitchFilter(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSEGFON);
}

/**
  * @brief  Set LSE trimming
  * @rmtoll BDCR1        LSETRIM        LL_RCC_LSE_SetClockTrimming
  * @param  LSETrim This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSETRIMMING_R
  *         @arg @ref LL_RCC_LSETRIMMING_3_4_R
  *         @arg @ref LL_RCC_LSETRIMMING_2_3_R
  *         @arg @ref LL_RCC_LSETRIMMING_1_2_R
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetClockTrimming(uint32_t LSETrim)
{
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSETRIM, LSETrim);
}

/**
  * @brief  Get LSE trimming
  * @rmtoll BDCR1        LSETRIM        LL_RCC_LSE_GetClockTrimming
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSETRIMMING_R
  *         @arg @ref LL_RCC_LSETRIMMING_3_4_R
  *         @arg @ref LL_RCC_LSETRIMMING_2_3_R
  *         @arg @ref LL_RCC_LSETRIMMING_1_2_R
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetClockTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR1, RCC_BDCR1_LSETRIM));
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll BDCR1        LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t LSEDrive)
{
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll BDCR1        LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR1, RCC_BDCR1_LSEDRV));
}

/**
  * @brief  Enable Clock security system on LSE.
  * @rmtoll BDCR1        LSECSSON      LL_RCC_LSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSECSSON);
}

/**
  * @brief  Disable Clock security system on LSE.
  * @note Clock security system can be disabled only after a LSE
  *       failure detection. In that case it MUST be disabled by software.
  * @rmtoll BDCR1        LSECSSON      LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSECSSON);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR1        LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR1, RCC_BDCR1_LSERDY) == RCC_BDCR1_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE oscillator propagation for system clock
  * @rmtoll BDCR1        LSESYSEN      LL_RCC_LSE_EnablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnablePropagation(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSEN);
}

/**
  * @brief  Disable LSE oscillator propagation for system clock
  * @rmtoll BDCR1        LSESYSEN      LL_RCC_LSE_DisablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisablePropagation(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSEN);
}

/**
  * @brief  Check if LSE oscillator propagation for system clock Ready
  * @rmtoll BDCR1        LSESYSRDY     LL_RCC_LSE_IsPropagationReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsPropagationReady(void)
{
  return ((READ_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSRDY) == RCC_BDCR1_LSESYSRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll BDCR1        LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->BDCR1, RCC_BDCR1_LSECSSD) == RCC_BDCR1_LSECSSD) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI1 LSI1
  * @{
  */

/**
  * @brief  Enable LSI1 Oscillator
  * @rmtoll BDCR1         LSI1ON         LL_RCC_LSI1_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI1_Enable(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSI1ON);
}

/**
  * @brief  Disable LSI1 Oscillator
  * @rmtoll BDCR1         LSI1ON         LL_RCC_LSI1_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI1_Disable(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSI1ON);
}

/**
  * @brief  Check if LSI1 is Ready
  * @rmtoll BDCR1         LSI1RDY        LL_RCC_LSI1_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI1_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR1, RCC_BDCR1_LSI1RDY) == RCC_BDCR1_LSI1RDY) ? 1UL : 0UL);
}

/**
  * @brief  Set LSI1 prescaler
  * @rmtoll BDCR1         LSI1PREDIV        LL_RCC_LSI1_SetPrescaler
  * @param  LSI1Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI_DIV_1
  *         @arg @ref LL_RCC_LSI_DIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI1_SetPrescaler(uint32_t LSI1Prescaler)
{
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV, LSI1Prescaler);
}

/**
  * @brief  Get LSI1 prescaler
  * @rmtoll BDCR1         LSI1PREDIV        LL_RCC_LSI1_GetPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI_DIV_1
  *         @arg @ref LL_RCC_LSI_DIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_LSI1_GetPrescaler(void)
{
  return (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV));
}

/**
  * @}
  */

#if defined(RCC_LSI2_SUPPORT)
/** @defgroup RCC_LL_EF_LSI2 LSI2
  * @{
  */

/**
  * @brief  Enable LSI2 Oscillator
  * @rmtoll BDCR1         LSI2ON         LL_RCC_LSI2_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI2_Enable(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSI2ON);
}

/**
  * @brief  Disable LSI2 Oscillator
  * @rmtoll BDCR1         LSI2ON         LL_RCC_LSI2_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI2_Disable(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSI2ON);
}

/**
  * @brief  Check if LSI2 is Ready
  * @rmtoll BDCR1         LSI2RDY        LL_RCC_LSI2_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI2_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR1, RCC_BDCR1_LSI2RDY) == RCC_BDCR1_LSI2RDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure LSI2 oscillator temperature sensitivity
  * @rmtoll BDCR2         LSI2CFG       LL_RCC_LSI2_SetTempSensitivity
  * @param  Sensitivity This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI2_TEMP_SENSITIVITY_80
  *         @arg @ref LL_RCC_LSI2_TEMP_SENSITIVITY_50
  *         @arg @ref LL_RCC_LSI2_TEMP_SENSITIVITY_20
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI2_SetTempSensitivity(uint32_t Sensitivity)
{
  MODIFY_REG(RCC->BDCR2, RCC_BDCR2_LSI2CFG, Sensitivity);
}

/**
  * @brief  Get LSI2 oscillator temperature sensitivity
  * @rmtoll BDCR2        LSI2CFG       LL_RCC_LSI2_GetTempSensitivity
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI2_TEMP_SENSITIVITY_80
  *         @arg @ref LL_RCC_LSI2_TEMP_SENSITIVITY_50
  *         @arg @ref LL_RCC_LSI2_TEMP_SENSITIVITY_20
  */
__STATIC_INLINE uint32_t LL_RCC_LSI2_GetTempSensitivity(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR2, RCC_BDCR2_LSI2CFG));
}

/**
  * @brief  Configure LSI2 operating mode configuration
  * @rmtoll BDCR2         LSI2MODE       LL_RCC_LSI2_SetOperatingMode
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI2_NOMINAL_MODE
  *         @arg @ref LL_RCC_LSI2_LOWPOWER_MODE
  *         @arg @ref LL_RCC_LSI2_ULTRALOWPOWER_MODE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI2_SetOperatingMode(uint32_t Mode)
{
  MODIFY_REG(RCC->BDCR2, RCC_BDCR2_LSI2MODE, Mode);
}

/**
  * @brief  Get LSI2 oscillator operating mode
  * @rmtoll BDCR2        LSI2MODE       LL_RCC_LSI2_GetOperatingMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI2_NOMINAL_MODE
  *         @arg @ref LL_RCC_LSI2_LOWPOWER_MODE
  *         @arg @ref LL_RCC_LSI2_ULTRALOWPOWER_MODE
  */
__STATIC_INLINE uint32_t LL_RCC_LSI2_GetOperatingMode(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR2, RCC_BDCR2_LSI2MODE));
}

/**
  * @}
  */
#endif /* LSI2 */

/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll BDCR1        LSCOEN        LL_RCC_LSCO_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll BDCR1        LSCOEN        LL_RCC_LSCO_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSCOEN);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll BDCR1        LSCOSEL       LL_RCC_LSCO_SetSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSCOSEL, Source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll BDCR1        LSCOSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR1, RCC_BDCR1_LSCOSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll CFGR1         SW           LL_RCC_SetSysClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL1R
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, Source);
}

/**
  * @brief  Get the system clock source
  * @rmtoll CFGR1        SWS           LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL1R
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS));
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll CFGR2        HPRE          LL_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_HPRE, Prescaler);
}

/**
  * @brief  Set Systick clock source
  * @rmtoll CCIPR1      SYSTICKSEL    LL_RCC_SetSystickClockSource
  * @param  SystickSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSystickClockSource(uint32_t SystickSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, SystickSource);
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll CFGR2         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE1, Prescaler);
}

/**
  * @brief  Set APB2 prescaler
  * @rmtoll CFGR2         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE2, Prescaler);
}

/**
  * @brief  Set APB7 prescaler
  * @rmtoll CFGR3         PPRE7         LL_RCC_SetAPB7Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB7_DIV_1
  *         @arg @ref LL_RCC_APB7_DIV_2
  *         @arg @ref LL_RCC_APB7_DIV_4
  *         @arg @ref LL_RCC_APB7_DIV_8
  *         @arg @ref LL_RCC_APB7_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB7Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_PPRE7, Prescaler);
}

/**
  * @brief  Set AHB5 prescaler when SYSCLK is PLL1R
  * @rmtoll CFGR4         HPRE5         LL_RCC_SetAHB5Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_AHB5_DIV_1
  *         @arg @ref LL_RCC_AHB5_DIV_2
  *         @arg @ref LL_RCC_AHB5_DIV_3
  *         @arg @ref LL_RCC_AHB5_DIV_4
  *         @arg @ref LL_RCC_AHB5_DIV_6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHB5Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR4, RCC_CFGR4_HPRE5, Prescaler);
}

/**
  * @brief  Set AHB5 divider when SYSCLK is HSI or HSE
  * @rmtoll CFGR4         HDIV5         LL_RCC_SetAHB5Divider
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_AHB5_DIVIDER_1
  *         @arg @ref LL_RCC_AHB5_DIVIDER_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHB5Divider(uint32_t Divider)
{
  MODIFY_REG(RCC->CFGR4, RCC_CFGR4_HDIV5, Divider);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll CFGR2         HPRE          LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_HPRE));
}

/**
  * @brief  Get Sysctick clock source
  * @rmtoll CCIPR1       SYSTICKSEL    LL_RCC_SetSystickClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  */
__STATIC_INLINE uint32_t LL_RCC_GetSystickClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL));
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll CFGR2         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE1));
}

/**
  * @brief  Get APB2 prescaler
  * @rmtoll CFGR2         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE2));
}

/**
  * @brief  Get APB7 prescaler
  * @rmtoll CFGR3         PPRE7         LL_RCC_GetAPB7Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB7_DIV_1
  *         @arg @ref LL_RCC_APB7_DIV_2
  *         @arg @ref LL_RCC_APB7_DIV_4
  *         @arg @ref LL_RCC_APB7_DIV_8
  *         @arg @ref LL_RCC_APB7_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB7Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_PPRE7));
}

/**
  * @brief  Get AHB5 prescaler when SYSCLK is PLL1R
  * @rmtoll CFGR4         HPRE5         LL_RCC_GetAHB5Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_AHB5_DIV_1
  *         @arg @ref LL_RCC_AHB5_DIV_2
  *         @arg @ref LL_RCC_AHB5_DIV_3
  *         @arg @ref LL_RCC_AHB5_DIV_4
  *         @arg @ref LL_RCC_AHB5_DIV_6
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHB5Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR4, RCC_CFGR4_HPRE5));
}

/**
  * @brief  Get AHB5 divider when SYSCLK is HSI or HSE
  * @rmtoll CFGR4         HDIV5         LL_RCC_GetAHB5Divider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_AHB5_DIVIDER_1
  *         @arg @ref LL_RCC_AHB5_DIVIDER_2
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHB5Divider(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR4, RCC_CFGR4_HDIV5));
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_RADIO RADIO
  * @{
  */

/**
  * @brief  Enable the 2.4 GHz RADIO baseband clock
  * @rmtoll RADIOENR        BBCLKEN      LL_RCC_RADIO_EnableBasebandClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RADIO_EnableBasebandClock(void)
{
  SET_BIT(RCC->RADIOENR, RCC_RADIOENR_BBCLKEN);
}

/**
  * @brief  Disable the 2.4 GHz RADIO baseband clock
  * @rmtoll RADIOENR        BBCLKEN      LL_RCC_RADIO_DisableBasebandClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RADIO_DisableBasebandClock(void)
{
  CLEAR_BIT(RCC->RADIOENR, RCC_RADIOENR_BBCLKEN);
}

/**
  * @brief  Check if 2.4 GHz RADIO baseband clock is enabled
  * @rmtoll RADIOENR        BBCLKEN       LL_RCC_RADIO_IsEnabledBasebandClock
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_RADIO_IsEnabledBasebandClock(void)
{
  return ((READ_BIT(RCC->RADIOENR, RCC_RADIOENR_BBCLKEN) == RCC_RADIOENR_BBCLKEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable the 2.4 GHz RADIO bus clock and HSE32 oscillator by 2.4 GHz RADIO sleep timer wakeup event
  * @rmtoll RADIOENR        STRADIOCLKON      LL_RCC_RADIO_DisableSleepTimerClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RADIO_DisableSleepTimerClock(void)
{
  CLEAR_BIT(RCC->RADIOENR, RCC_RADIOENR_STRADIOCLKON);
}

/**
  * @brief  Check if 2.4 GHz RADIO bus clock and HSE32 oscillator are enabled by 2.4 GHz RADIO sleep timer wakeup event
  * @rmtoll RADIOENR        STRADIOCLKON       LL_RCC_RADIO_IsEnabledSleepTimerClock
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_RADIO_IsEnabledSleepTimerClock(void)
{
  return ((READ_BIT(RCC->RADIOENR, RCC_RADIOENR_STRADIOCLKON) == RCC_RADIOENR_STRADIOCLKON) ? 1UL : 0UL);
}

/**
  * @brief  Check if 2.4 GHz RADIO bus clock is ready
  * @rmtoll RADIOENR        RADIOCLKRDY       LL_RCC_RADIO_IsBusClockReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_RADIO_IsBusClockReady(void)
{
  return ((READ_BIT(RCC->RADIOENR, RCC_RADIOENR_RADIOCLKRDY) == RCC_RADIOENR_RADIOCLKRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set the 2.4 GHz RADIO sleep timer kernel clock
  * @rmtoll BDCR1        RADIOSTSEL        LL_RCC_RADIO_SetSleepTimerClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_NONE
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_LSE
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_LSI (*)
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_HSE_DIV1000
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RADIO_SetSleepTimerClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_RADIOSTSEL, Source);
}

/**
  * @brief  Get the 2.4 GHz RADIO sleep timer kernel clock
  * @rmtoll BDCR1        RADIOSTSEL        LL_RCC_RADIO_GetSleepTimerClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_NONE
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_LSE
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_LSI (*)
  *         @arg @ref LL_RCC_RADIOSLEEPSOURCE_HSE_DIV1000
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_RADIO_GetSleepTimerClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR1, RCC_BDCR1_RADIOSTSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll CFGR1         MCOSEL        LL_RCC_ConfigMCO\n
  *         CFGR1         MCOPRE        LL_RCC_ConfigMCO
  * @param  MCOxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO1SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLL1R
  *         @arg @ref LL_RCC_MCO1SOURCE_PLL1Q
  *         @arg @ref LL_RCC_MCO1SOURCE_PLL1P
  *         @arg @ref LL_RCC_MCO1SOURCE_LSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_HCLK5
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_DIV_1
  *         @arg @ref LL_RCC_MCO1_DIV_2
  *         @arg @ref LL_RCC_MCO1_DIV_4
  *         @arg @ref LL_RCC_MCO1_DIV_8
  *         @arg @ref LL_RCC_MCO1_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE, MCOxSource | MCOxPrescaler);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure USARTx clock source
  * @rmtoll CCIPR1       USART1SEL     LL_RCC_SetUSARTClockSource\n
  *         CCIPR1       USART2SEL     LL_RCC_SetUSARTClockSource\n
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t USARTxSource)
{
  MODIFY_REG(RCC->CCIPR1, USARTxSource >> 16U, (USARTxSource & 0x0000FFFFU));
}

/**
  * @brief  Configure LPUARTx clock source
  * @rmtoll CCIPR3       LPUART1SEL    LL_RCC_SetLPUARTClockSource
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t LPUARTxSource)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL, LPUARTxSource);
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CCIPR1       I2C1SEL       LL_RCC_SetI2CClockSource\n
  *         CCIPR3       I2C3SEL       LL_RCC_SetI2CClockSource\n
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t I2CxSource)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (I2CxSource >> 24U));
  MODIFY_REG(*reg, 3U << (((I2CxSource & 0x00FF0000U) >> 16U) & 0x1FU), ((I2CxSource & 0x000000FFU) << (((I2CxSource & 0x00FF0000U) >> 16U) & 0x1FU)));
}

/**
  * @brief  Configure SPIx clock source
  * @rmtoll CCIPR1       SPI1SEL       LL_RCC_SetSPIClockSource\n
  *         CCIPR3       SPI3SEL       LL_RCC_SetSPIClockSource\n
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t SPIxSource)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (SPIxSource >> 24U));
  MODIFY_REG(*reg, 3U << (((SPIxSource & 0x00FF0000U) >> 16U) & 0x1FU), ((SPIxSource & 0x000000FFU) << (((SPIxSource & 0x00FF0000U) >> 16U) & 0x1FU)));
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll CCIPR3       LPTIM1SEL     LL_RCC_SetLPTIMClockSource\n
  *         CCIPR1       LPTIM2SEL     LL_RCC_SetLPTIMClockSource\n
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t LPTIMxSource)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (LPTIMxSource >> 24U));
  MODIFY_REG(*reg, 3U << (((LPTIMxSource & 0x00FF0000U) >> 16U) & 0x1FU), ((LPTIMxSource & 0x000000FFU) << (((LPTIMxSource & 0x00FF0000U) >> 16U) & 0x1FU)));
}


/**
  * @brief  Configure SAIx clock source
  * @rmtoll CCIPR2       SAI1SEL       LL_RCC_SetSAIClockSource\n
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1P(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1Q(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_SYSCLK(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PIN(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_HSI(*)
  * (*) Feature not available on all devices of the family
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAIClockSource(uint32_t SAIxSource)
{
  MODIFY_REG(RCC->CCIPR2, (SAIxSource >> 16U), (SAIxSource & 0x0000FFFFU));
}

/**
  * @brief  Configure RNG clock source
  * @rmtoll CCIPR2       RNGSEL        LL_RCC_SetRNGClockSource
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_PLL1Q_DIV2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRNGClockSource(uint32_t RNGxSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_RNGSEL, RNGxSource);
}

/**
  * @brief  Configure ADC clock source
  * @rmtoll CCIPR3       ADCSEL        LL_RCC_SetADCClockSource
  * @param  ADC4Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL1P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t ADC4Source)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ADCSEL, ADC4Source);
}


/**
  * @brief  Get USARTx clock source
  * @rmtoll CCIPR1       USART1SEL     LL_RCC_GetUSARTClockSource\n
  *         CCIPR1       USART2SEL     LL_RCC_GetUSARTClockSource\n
  * @param  USARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t USARTx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, USARTx) | (USARTx << 16U));
}

/**
  * @brief  Get LPUARTx clock source
  * @rmtoll CCIPR3       LPUART1SEL    LL_RCC_GetLPUARTClockSource
  * @param  LPUARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t LPUARTx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, LPUARTx));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CCIPR1       I2C1SEL       LL_RCC_GetI2CClockSource\n
  *         CCIPR3       I2C3SEL       LL_RCC_GetI2CClockSource\n
  * @param  I2Cx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
 */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t I2Cx)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (I2Cx >> 24U));
  return (uint32_t)((READ_BIT(*reg, (3UL << (((I2Cx & 0x00FF0000UL) >> 16U) & 0x1FUL))) >> (((I2Cx & 0x00FF0000UL) >> 16U) & 0x1FUL)) | (I2Cx & 0xFFFF0000UL));
}

/**
  * @brief  Get SPIx clock source
  * @rmtoll CCIPR1       SPI1SEL       LL_RCC_GetSPIClockSource\n
  *         CCIPR3       SPI3SEL       LL_RCC_GetSPIClockSource
  * @param  SPIx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI
 */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t SPIx)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (SPIx >> 24U));
  return (uint32_t)((READ_BIT(*reg, (3UL << (((SPIx & 0x00FF0000UL) >> 16U) & 0x1FUL))) >> (((SPIx & 0x00FF0000UL) >> 16U) & 0x1FUL)) | (SPIx & 0xFFFF0000UL));
}

/**
  * @brief  Get LPTIMx clock source
  * @rmtoll CCIPR3       LPTIM1SEL     LL_RCC_GetLPTIMClockSource\n
  *         CCIPR1       LPTIM2SEL     LL_RCC_GetLPTIMClockSource\n
  * @param  LPTIMx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK7
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t LPTIMx)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (LPTIMx >> 24U));
  return (uint32_t)((READ_BIT(*reg, (3UL << (((LPTIMx & 0x00FF0000UL) >> 16U) & 0x1FUL))) >> (((LPTIMx & 0x00FF0000UL) >> 16U) & 0x1FUL)) | (LPTIMx & 0xFFFF0000UL));
}

/**
  * @brief  Set Tim Input capture clock source
  * @rmtoll CCIPR1       TIMICSEL      LL_RCC_SetTIMICClockSource
  * @param  TIMICSource This parameter can be one of the following combined values:
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_NONE
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256
  * @note    HSI clock without division is also available when TIMICSEL[2] is 1.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTIMICClockSource(uint32_t TIMICSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL, TIMICSource);
}

/**
  * @brief  Get Tim Input capture clock source
  * @rmtoll CCIPR1       TIMICSEL      LL_RCC_GetTIMICClockSource
  * @retval Returned value can be one of the following combined values:
  *          @arg @ref   LL_RCC_TIMIC_CLKSOURCE_NONE
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256
  */
__STATIC_INLINE uint32_t LL_RCC_GetTIMICClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL));
}

/**
  * @brief  Get SAIx clock source
  * @rmtoll CCIPR2       SAI1SEL       LL_RCC_GetSAIClockSource\n
  * @param  SAIx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE(*)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1P(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1Q(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_SYSCLK(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PIN(*)
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_HSI(*)
  * (*) Feature not available on all devices of the family
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAIClockSource(uint32_t SAIx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, SAIx) | (SAIx << 16U));
}

/**
  * @brief  Get RNGx clock source
  * @rmtoll CCIPR2       RNGSEL      LL_RCC_GetRNGClockSource
  * @param  RNGx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_PLL1Q_DIV2
  */
__STATIC_INLINE uint32_t LL_RCC_GetRNGClockSource(uint32_t RNGx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RNGx));
}

/**
  * @brief  Get ADCx clock source
  * @rmtoll CCIPR3       ADCSEL        LL_RCC_GetADCClockSource
  * @param  ADCx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL1P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t ADCx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, ADCx));
}


/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @note Once the RTC clock source has been selected, it cannot be changed anymore unless
  *       the Backup domain is reset, or unless a failure is detected on LSE (LSECSSD is
  *       set). The BDRST bit can be used to reset them.
  * @rmtoll BDCR1        RTCSEL        LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_RTCSEL, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll BDCR1        RTCSEL        LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR1, RCC_BDCR1_RTCSEL));
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll BDCR1        BDRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_BDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR1        BDRST         LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_BDRST);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL1 PLL1
  * @{
  */

/**
  * @brief  Enable PLL1
  * @rmtoll CR           PLL1ON         LL_RCC_PLL1_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Disable PLL1
  * @note Cannot be disabled if the PLL1 clock is used as the system clock
  * @rmtoll CR           PLL1ON         LL_RCC_PLL1_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Check if PLL1 Ready
  * @rmtoll CR           PLL1RDY        LL_RCC_PLL1_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL1RDY) == RCC_CR_PLL1RDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable prescaler division on PLL1RCLK for SYSCLK
  * @rmtoll PLL1CFGR     PLL1RCLKPRE    LL_RCC_PLL1_EnablePLL1RCLKDivision
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_EnablePLL1RCLKDivision(void)
{
  SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);
}

/**
  * @brief  Disable PLL1RCLK for SYSCLK prescaler division
  * @rmtoll PLL1CFGR     PLL1RCLKPRE    LL_RCC_PLL1_DisablePLL1RCLKDivision
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_DisablePLL1RCLKDivision(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);
}

/**
  * @brief  Set the division step of PLL1RCLK clock for SYSCLK
  * @rmtoll PLL1CFGR      PLL1RCLKPRESTEP  LL_RCC_PLL1_SetPLL1RCLKDivisionStep
  * @param  Step This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1RCLK_2_STEP_DIV
  *         @arg @ref LL_RCC_PLL1RCLK_3_STEP_DIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_SetPLL1RCLKDivisionStep(uint32_t Step)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRESTEP, Step);
}

/**
  * @brief  Get the division step of PLL1RCLK clock for SYSCLK
  * @rmtoll PLL1CFGR      PLL1RCLKPRESTEP  LL_RCC_PLL1_GetPLL1RCLKDivisionStep
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL1RCLK_2_STEP_DIV
  *         @arg @ref LL_RCC_PLL1RCLK_3_STEP_DIV
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetPLL1RCLKDivisionStep(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRESTEP));
}

/**
  * @brief  Check if prescaler division on PLL1RCLK for SYSCLK is ready
  * @rmtoll PLL1CFGR      PLL1RCLKPRERDY  LL_RCC_PLL1_IsPLL1RCLKDivisionReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsPLL1RCLKDivisionReady(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRERDY) == RCC_PLL1CFGR_PLL1RCLKPRERDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL1R used for SYSCLK Domain
  * @note PLL1 Source, PLLM, PLLN and PLLR can be written only when PLL1 is disabled.
  * @note PLLN/PLLR can be written only when PLL1 is disabled.
  * @rmtoll PLL1CFGR      PLL1SRC        LL_RCC_PLL1_ConfigDomain_PLL1R\n
  *         PLL1CFGR      PLL1M          LL_RCC_PLL1_ConfigDomain_PLL1R\n
  *         PLL1DIVR      PLL1N          LL_RCC_PLL1_ConfigDomain_PLL1R\n
  *         PLL1DIVR      PLL1R          LL_RCC_PLL1_ConfigDomain_PLL1R
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param PLLM parameter can be a value between 1 and 16
  * @param PLLR parameter can be a value between 1 and 128
  * @param PLLN parameter can be a value between 4 and 512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_PLL1R(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLR)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M, Source | ((PLLM - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1R, ((PLLN - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((PLLR - 1UL) << RCC_PLL1DIVR_PLL1R_Pos));
}

/**
  * @brief  Configure PLL1P
  * @note   PLL1 Source, PLLM, PLLN and PLLPDIV can be written only when PLL1 is disabled.
  * @note   This can be selected for ADC and SAI
  * @rmtoll PLL1CFGR      PLL1SRC        LL_RCC_PLL1_ConfigDomain_PLL1P\n
  *         PLL1CFGR      PLL1M          LL_RCC_PLL1_ConfigDomain_PLL1P\n
  *         PLL1DIVR      PLL1N          LL_RCC_PLL1_ConfigDomain_PLL1P\n
  *         PLL1DIVR      PLL1P          LL_RCC_PLL1_ConfigDomain_PLL1P
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param PLLM parameter can be a value between 1 and 16
  * @param PLLN parameter can be a value between 4 and 512
  * @param PLLP parameter can be a value between 2 and 128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_PLL1P(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M, Source | ((PLLM - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1P, ((PLLN - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((PLLP - 1UL) << RCC_PLL1DIVR_PLL1P_Pos));
}

/**
  * @brief  Configure PLL1Q
  * @note   PLL1 Source, PLLM, PLLN and PLLQ can be written only when PLL1 is disabled.
  * @note   This  can be selected for RNG and SAI
  * @rmtoll PLL1CFGR      PLL1SRC        LL_RCC_PLL1_ConfigDomain_PLL1Q\n
  *         PLL1CFGR      PLL1M          LL_RCC_PLL1_ConfigDomain_PLL1Q\n
  *         PLL1DIVR      PLL1N          LL_RCC_PLL1_ConfigDomain_PLL1Q\n
  *         PLL1DIVR      PLL1Q          LL_RCC_PLL1_ConfigDomain_PLL1Q
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param PLLM parameter can be a value between 1 and 16
  * @param PLLN parameter can be a value between 4 and 512
  * @param PLLQ parameter can be a value between 1 and 128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_PLL1Q(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLQ)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M, Source | ((PLLM - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1Q, ((PLLN - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((PLLQ - 1UL) << RCC_PLL1DIVR_PLL1Q_Pos));
}

/**
  * @brief  Configure PLL1 clock source
  * @rmtoll PLL1CFGR      PLL1SRC        LL_RCC_PLL1_SetMainSource
  * @param  PLL1Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_SetMainSource(uint32_t PLL1Source)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC, PLL1Source);
}

/**
  * @brief  Get the oscillator used as PLL1 clock source.
  * @rmtoll PLL1CFGR      PLL1SRC        LL_RCC_PLL1_GetMainSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetMainSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC));
}

/**
  * @brief  Set PLL1 multiplication factor for VCO
  * @rmtoll PLL1DIVR      PLL1N          LL_RCC_PLL1_SetN
  * @param  PLL1N parameter can be a value between 4 and 512
  */
__STATIC_INLINE void LL_RCC_PLL1_SetN(uint32_t PLL1N)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N, (PLL1N - 1UL) << RCC_PLL1DIVR_PLL1N_Pos);
}

/**
  * @brief  Get PLL1 multiplication factor for VCO
  * @rmtoll PLL1DIVR      PLL1N          LL_RCC_PLL1_GetN
  * @retval Between 4 and 512
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N) >>  RCC_PLL1DIVR_PLL1N_Pos) + 1UL);
}


/**
  * @brief  Set PLL1 division factor for PLL1P
  * @note   Used for PLL1PCLK selected ADC and SAI
  * @rmtoll PLL1DIVR      PLL1P       LL_RCC_PLL1_SetP
  * @param  PLL1P parameter can be a value between 2 and 128
  */
__STATIC_INLINE void LL_RCC_PLL1_SetP(uint32_t PLL1P)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1P, (PLL1P - 1UL) << RCC_PLL1DIVR_PLL1P_Pos);
}

/**
  * @brief  Get PLL1 division factor for PLL1P
  * @note   Used for PLL1PCLK selected ADC and SAI
  * @rmtoll PLL1DIVR      PLL1P      LL_RCC_PLL1_GetP
  * @retval Between 2 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1P) >>  RCC_PLL1DIVR_PLL1P_Pos) + 1UL);
}


/**
  * @brief  Set PLL1 division factor for PLL1Q
  * @note   Used for PLL1QCLK selected for RNG and SAI
  * @rmtoll PLL1DIVR      PLL1Q          LL_RCC_PLL1_SetQ
  * @param PLL1Q parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL1_SetQ(uint32_t PLL1Q)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1Q, (PLL1Q - 1UL) << RCC_PLL1DIVR_PLL1Q_Pos);
}

/**
  * @brief  Get PLL1 division factor for PLL1Q
  * @note   Used for PLL1QCLK selected for RNG and SAI
  * @rmtoll PLL1DIVR      PLL1Q          LL_RCC_PLL1_GetQ
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1Q) >>  RCC_PLL1DIVR_PLL1Q_Pos) + 1UL);
}

/**
  * @brief  Set PLL1 division factor for PLL1R
  * @note   Used for PLL1RCLK selected for system clock
  * @rmtoll PLL1DIVR      PLL1R          LL_RCC_PLL1_SetR
  * @param PLL1R parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL1_SetR(uint32_t PLL1R)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1R, (PLL1R - 1UL) << RCC_PLL1DIVR_PLL1R_Pos);
}

/**
  * @brief  Get PLL1 division factor for PLL1R
  * @note   Used for PLL1RCLK selected for system clock
  * @rmtoll PLL1DIVR      PLL1R          LL_RCC_PLL1_GetR
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1R) >>  RCC_PLL1DIVR_PLL1R_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL1
  * @rmtoll PLL1CFGR      PLL1M          LL_RCC_PLL1_SetDivider
  * @param PLL1M parameter can be a value between 1 and 8
  */
__STATIC_INLINE void LL_RCC_PLL1_SetDivider(uint32_t PLL1M)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1M, (PLL1M - 1UL) << RCC_PLL1CFGR_PLL1M_Pos);
}

/**
  * @brief  Get Division factor for PLL1
  * @rmtoll PLL1CFGR      PLL1M          LL_RCC_PLL1_GetDivider
  * @retval Between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetDivider(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1M) >>  RCC_PLL1CFGR_PLL1M_Pos) + 1UL);
}

/**
  * @brief  Enable PLL1P output
  * @rmtoll PLL1CFGR      PLL1PEN        LL_RCC_PLL1_EnableDomain_PLL1P
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableDomain_PLL1P(void)
{
  SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN);
}

/**
  * @brief  Disable PLL1P output
  * @note   In order to save power, when the PLL1PCLK of the PLL1 is
  *         not used,  should be 0
  * @rmtoll PLL1CFGR      PLL1PEN        LL_RCC_PLL1_DisableDomain_PLL1P
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableDomain_PLL1P(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN);
}

/**
  * @brief  Check if PLL1P output is enabled
  * @rmtoll PLL1CFGR      PLL1PEN        LL_RCC_PLL1_IsEnabledDomain_PLL1P
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledDomain_PLL1P(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN) == RCC_PLL1CFGR_PLL1PEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1Q output
  * @rmtoll PLL1CFGR      PLL1QEN        LL_RCC_PLL1_EnableDomain_PLL1Q
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableDomain_PLL1Q(void)
{
  SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1QEN);
}

/**
  * @brief  Disable PLL1Q output
  * @note   In order to save power, when the PLL1QCLK of the PLL1 is
  *         not used,  should be 0
  * @rmtoll PLL1CFGR      PLL1QEN        LL_RCC_PLL1_DisableDomain_PLL1Q
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableDomain_PLL1Q(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1QEN);
}

/**
  * @brief  Check if PLL1Q output is enabled
  * @rmtoll PLL1CFGR      PLL1QEN        LL_RCC_PLL1_IsEnabledDomain_PLL1Q
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledDomain_PLL1Q(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1QEN) == RCC_PLL1CFGR_PLL1QEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1R output mapped on SYSCLK domain
  * @rmtoll PLL1CFGR      PLL1REN        LL_RCC_PLL1_EnableDomain_PLL1R
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableDomain_PLL1R(void)
{
  SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1REN);
}

/**
  * @brief  Disable PLL1 output mapped on SYSCLK domain
  * @note   Cannot be disabled if the PLL1 clock is used as the system
  *         clock
  * @note   In order to save power, when the PLL1RCLK of the PLL1 is
  *         not used, PLL1  should be 0
  * @rmtoll PLL1CFGR      PLL1REN        LL_RCC_PLL1_DisableDomain_PLL1R
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableDomain_PLL1R(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1REN);
}

/**
  * @brief  Check if PLL1R output mapped on SYSCLK domain clock is enabled
  * @rmtoll PLL1CFGR      PLL1REN        LL_RCC_PLL1_IsEnabledDomain_PLL1R
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledDomain_PLL1R(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1REN) == RCC_PLL1CFGR_PLL1REN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1 FRACN
  * @rmtoll PLL1CFGR           PLL1FRACEN         LL_RCC_PLL1FRACN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1FRACN_Enable(void)
{
  SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN);
}

/**
  * @brief  Check if PLL1 FRACN is enabled
  * @rmtoll PLL1CFGR           PLL1FRACEN         LL_RCC_PLL1FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN) == RCC_PLL1CFGR_PLL1FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL1 FRACN
  * @rmtoll PLL1CFGR           PLL1FRACEN         LL_RCC_PLL1FRACN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN);
}

/**
  * @brief  Set PLL1 FRACN Coefficient
  * @rmtoll PLL1FRACR        PLL1FRACN        LL_RCC_PLL1_SetFRACN
  * @param  FRACN parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetFRACN(uint32_t FRACN)
{
  MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_PLL1FRACN, FRACN << RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @brief  Get PLL1 FRACN Coefficient
  * @rmtoll PLL1FRACR      PLL1FRACN          LL_RCC_PLL1_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1FRACR, RCC_PLL1FRACR_PLL1FRACN) >>  RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @brief  Set PLL1 VCO Input Range
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLL1CFGR        PLL1RGE       LL_RCC_PLL1_SetVCOInputRange
  * @param  InputRange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_SetVCOInputRange(uint32_t InputRange)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RGE, InputRange << RCC_PLL1CFGR_PLL1RGE_Pos);
}

/**
  * @}
  */

#if defined(RCC_PRIVCFGR_NSPRIV)
/** @defgroup RCC_LL_EF_PRIV Privileged mode
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable Secure Privileged mode
  * @rmtoll PRIVCFGR       SPRIV         LL_RCC_EnableSecPrivilegedMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSecPrivilegedMode(void)
{
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
}

/**
  * @brief  Disable Secure Privileged mode
  * @rmtoll PRIVCFGR           SPRIV          LL_RCC_DisableSecPrivilegedMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSecPrivilegedMode(void)
{
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
}

/**
  * @brief  Check if Secure Privileged mode has been enabled or not
  * @rmtoll PRIVCFGR           SPRIV          LL_RCC_IsEnabledSecPrivilegedMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledSecPrivilegedMode(void)
{
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV) == RCC_PRIVCFGR_SPRIV) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Enable Non Secure Privileged mode
  * @rmtoll PRIVCFGR       NSPRIV        LL_RCC_EnableNSecPrivilegedMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableNSecPrivilegedMode(void)
{
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Disable Non Secure Privileged mode
  * @rmtoll PRIVCFGR           NSPRIV          LL_RCC_DisableNSecPrivilegedMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableNSecPrivilegedMode(void)
{
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Check if Non Secure Privileged mode has been enabled or not
  * @rmtoll PRIVCFGR           NSPRIV          LL_RCC_IsEnabledNSecPrivilegedMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledNSecPrivilegedMode(void)
{
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV) == RCC_PRIVCFGR_NSPRIV) ? 1UL : 0UL);
}

/**
  * @}
  */
#endif /* RCC_PRIVCFGR_NSPRIV */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear LSI1 ready interrupt flag
  * @rmtoll CICR         LSI1RDYC       LL_RCC_ClearFlag_LSI1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSI1RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSI1RDYC);
}

#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  Clear LSI2 ready interrupt flag
  * @rmtoll CICR         LSI2RDYC       LL_RCC_ClearFlag_LSI2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSI2RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSI2RDYC);
}
#endif /* RCC_BDCR1_LSI2ON */

/**
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll CICR         LSERDYC       LL_RCC_ClearFlag_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSERDYC);
}

/**
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll CICR         HSIRDYC       LL_RCC_ClearFlag_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIRDYC);
}

/**
  * @brief  Clear HSE ready interrupt flag
  * @rmtoll CICR         HSERDYC       LL_RCC_ClearFlag_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSERDYC);
}

/**
  * @brief  Clear PLL1 ready interrupt flag
  * @rmtoll CICR         PLL1RDYC       LL_RCC_ClearFlag_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL1RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL1RDYC);
}

/**
  * @brief  Clear Clock security system interrupt flag
  * @rmtoll CICR         CSSC          LL_RCC_ClearFlag_HSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSECSSC);
}


/**
  * @brief  Check if LSI1 ready interrupt occurred or not
  * @rmtoll CIFR         LSI1RDYF       LL_RCC_IsActiveFlag_LSI1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSI1RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSI1RDYF) == RCC_CIFR_LSI1RDYF) ? 1UL : 0UL);
}

#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  Check if LSI2 ready interrupt occurred or not
  * @rmtoll CIFR         LSI2RDYF       LL_RCC_IsActiveFlag_LSI2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSI2RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSI2RDYF) == RCC_CIFR_LSI2RDYF) ? 1UL : 0UL);
}
#endif /* RCC_BDCR1_LSI2ON */

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll CIFR         LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == RCC_CIFR_LSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll CIFR         HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == RCC_CIFR_HSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == RCC_CIFR_HSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 ready interrupt occurred or not
  * @rmtoll CIFR         PLL1RDYF       LL_RCC_IsActiveFlag_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL1RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL1RDYF) == RCC_CIFR_PLL1RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll CIFR         CSSF          LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSECSSF) == RCC_CIFR_HSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Independent Watchdog reset is set or not.
  * @rmtoll CSR          IWDGRSTF      LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF) == RCC_CSR_IWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll CSR          LPWRRSTF      LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LPWRRSTF) == RCC_CSR_LPWRRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag is set or not.
  * @rmtoll CSR          OBLRSTF       LL_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_OBLRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_OBLRSTF) == RCC_CSR_OBLRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll CSR          PINRSTF       LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_PINRSTF) == RCC_CSR_PINRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll CSR          SFTRSTF       LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_SFTRSTF) == RCC_CSR_SFTRSTF) ? 1UL : 0UL);
}

#if defined(WWDG)
/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll CSR          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_WWDGRSTF) == RCC_CSR_WWDGRSTF) ? 1UL : 0UL);
}
#endif /* WWDG */

/**
  * @brief  Check if RCC flag BOR reset is set or not.
  * @rmtoll CSR          BORRSTF       LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_BORRSTF) == RCC_CSR_BORRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll CSR          RMVF          LL_RCC_ClearResetFlags
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

/* Alias for portability */
#define LL_RCC_PLL1_ConfigDomain_SYS     LL_RCC_PLL1_ConfigDomain_PLL1R

/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable LSI1 ready interrupt
  * @rmtoll CIER         LSI1RDYIE      LL_RCC_EnableIT_LSI1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSI1RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSI1RDYIE);
}

#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  Enable LSI2 ready interrupt
  * @rmtoll CIER         LSI2RDYIE      LL_RCC_EnableIT_LSI2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSI2RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSI2RDYIE);
}
#endif /* RCC_BDCR1_LSI2ON */

/**
  * @brief  Enable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_EnableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Enable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_EnableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_EnableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Enable PLL1 ready interrupt
  * @rmtoll CIER         PLL1RDYIE      LL_RCC_EnableIT_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL1RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Disable LSI1 ready interrupt
  * @rmtoll CIER         LSI1RDYIE      LL_RCC_DisableIT_LSI1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSI1RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSI1RDYIE);
}

#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  Disable LSI2 ready interrupt
  * @rmtoll CIER         LSI2RDYIE      LL_RCC_DisableIT_LSI2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSI2RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSI2RDYIE);
}
#endif /* RCC_BDCR1_LSI2ON */

/**
  * @brief  Disable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_DisableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Disable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_DisableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_DisableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Disable PLL1 ready interrupt
  * @rmtoll CIER         PLL1RDYIE      LL_RCC_DisableIT_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL1RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Checks if LSI1 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSI1RDYIE      LL_RCC_IsEnabledIT_LSI1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSI1RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSI1RDYIE) == RCC_CIER_LSI1RDYIE) ? 1UL : 0UL);
}

#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  Checks if LSI2 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSI2RDYIE      LL_RCC_IsEnabledIT_LSI2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSI2RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSI2RDYIE) == RCC_CIER_LSI2RDYIE) ? 1UL : 0UL);
}
#endif /* RCC_BDCR1_LSI2ON */

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSERDYIE      LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == RCC_CIER_LSERDYIE) ? 1UL : 0UL);
}


/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSIRDYIE      LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == RCC_CIER_HSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == RCC_CIER_HSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL1 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         PLL1RDYIE      LL_RCC_IsEnabledIT_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL1RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE) == RCC_CIER_PLL1RDYIE) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Security_Services Security Services
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure RCC resources security
  * @note Only available from secure state when system implements security (TZEN=1)
  * @rmtoll SECCFGR     HSISEC        LL_RCC_ConfigSecure\n
  *         SECCFGR     HSESEC        LL_RCC_ConfigSecure\n
  *         SECCFGR     LSISEC        LL_RCC_ConfigSecure\n
  *         SECCFGR     LSESEC        LL_RCC_ConfigSecure\n
  *         SECCFGR     SYSCLKSEC     LL_RCC_ConfigSecure\n
  *         SECCFGR     PRESCSEC      LL_RCC_ConfigSecure\n
  *         SECCFGR     PLL1SEC       LL_RCC_ConfigSecure\n
  *         SECCFGR     RMVFSEC       LL_RCC_ConfigSecure
  * @param  SecureConfig This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_ALL_NSEC & LL_RCC_ALL_SEC
  *         @arg @ref LL_RCC_HSI_SEC & LL_RCC_HSI_NSEC
  *         @arg @ref LL_RCC_HSE_SEC & LL_RCC_HSE_NSEC
  *         @arg @ref LL_RCC_LSE_SEC & LL_RCC_LSE_NSEC
  *         @arg @ref LL_RCC_LSI_SEC & LL_RCC_LSI_NSEC
  *         @arg @ref LL_RCC_SYSCLK_SEC & LL_RCC_SYSCLK_NSEC
  *         @arg @ref LL_RCC_PRESCALERS_SEC & LL_RCC_PRESCALERS_NSEC
  *         @arg @ref LL_RCC_PLL1_SEC & LL_RCC_PLL1_NSEC
  *         @arg @ref LL_RCC_RESET_FLAGS_SEC & LL_RCC_RESET_FLAGS_NSEC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigSecure(uint32_t SecureConfig)
{
  WRITE_REG(RCC->SECCFGR, SecureConfig);
}
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get RCC resources security status
  * @note Only available from secure state when system implements security (TZEN=1)
  * @rmtoll SECCFGR     HSISEC        LL_RCC_GetConfigSecure\n
  *         SECCFGR     HSESEC        LL_RCC_GetConfigSecure\n
  *         SECCFGR     LSISEC        LL_RCC_GetConfigSecure\n
  *         SECCFGR     LSESEC        LL_RCC_GetConfigSecure\n
  *         SECCFGR     SYSCLKSEC     LL_RCC_GetConfigSecure\n
  *         SECCFGR     PRESCSEC      LL_RCC_GetConfigSecure\n
  *         SECCFGR     PLL1SEC       LL_RCC_GetConfigSecure\n
  *         SECCFGR     RMVFSEC       LL_RCC_GetConfigSecure
  * @retval Returned value can be one or a combination of the following values:
  *         @arg @ref LL_RCC_ALL_NSEC & LL_RCC_ALL_SEC
  *         @arg @ref LL_RCC_HSI_SEC & LL_RCC_HSI_NSEC
  *         @arg @ref LL_RCC_HSE_SEC & LL_RCC_HSE_NSEC
  *         @arg @ref LL_RCC_LSE_SEC & LL_RCC_LSE_NSEC
  *         @arg @ref LL_RCC_LSI_SEC & LL_RCC_LSI_NSEC
  *         @arg @ref LL_RCC_SYSCLK_SEC & LL_RCC_SYSCLK_NSEC
  *         @arg @ref LL_RCC_PRESCALERS_SEC & LL_RCC_PRESCALERS_NSEC
  *         @arg @ref LL_RCC_PLL1_SEC & LL_RCC_PLL1_NSEC
  *         @arg @ref LL_RCC_RESET_FLAGS_SEC & LL_RCC_RESET_FLAGS_NSEC
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_GetConfigSecure(void)
{
  return (uint32_t)(READ_BIT(RCC->SECCFGR, RCC_SECURE_MASK));
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_RCC_DeInit(void);
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Get_Freq Get system and peripherals clocks frequency functions
  * @{
  */
void        LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks);
uint32_t    LL_RCC_GetADCClockFreq(uint32_t ADCxSource);
uint32_t    LL_RCC_GetI2CClockFreq(uint32_t I2CxSource);
uint32_t    LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource);
uint32_t    LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource);
uint32_t    LL_RCC_GetRNGClockFreq(uint32_t RNGxSource);
uint32_t    LL_RCC_GetSAIClockFreq(uint32_t SAIxSource);
uint32_t    LL_RCC_GetSPIClockFreq(uint32_t SPIxSource);
uint32_t    LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource);
/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBAxx_LL_RCC_H */
