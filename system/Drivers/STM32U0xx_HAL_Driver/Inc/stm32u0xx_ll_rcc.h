/**
  ******************************************************************************
  * @file    stm32u0xx_ll_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32U0xx_LL_RCC_H
#define __STM32U0xx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx.h"

/** @addtogroup STM32U0xx_LL_Driver
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
/* Offset used to access to RCC_CCIPR and RCC_CCIPR2 registers */
#define RCC_OFFSET_CCIPR        0U

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

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
#if !defined  (HSE_VALUE)
#define HSE_VALUE    8000000U   /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    16000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined  (HSI48_VALUE)
#define HSI48_VALUE  48000000U   /*!< Value of the HSI48 oscillator in Hz */
#endif /* HSI48_VALUE */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_WriteReg function
  * @{
  */
#define LL_RCC_CICR_LSIRDYC                RCC_CICR_LSIRDYC     /*!< LSI Ready Interrupt Clear */
#define LL_RCC_CICR_LSERDYC                RCC_CICR_LSERDYC     /*!< LSE Ready Interrupt Clear */
#define LL_RCC_CICR_MSIRDYC                RCC_CICR_MSIRDYC     /*!< MSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSIRDYC                RCC_CICR_HSIRDYC     /*!< HSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSERDYC                RCC_CICR_HSERDYC     /*!< HSE Ready Interrupt Clear */
#define LL_RCC_CICR_PLLRDYC                RCC_CICR_PLLRDYC     /*!< PLL Ready Interrupt Clear */
#define LL_RCC_CICR_CSSC                   RCC_CICR_CSSC        /*!< Clock Security System Interrupt Clear */
#define LL_RCC_CICR_LSECSSC                RCC_CICR_LSECSSC     /*!< LSE Clock Security System Interrupt Clear */
#if defined(RCC_CRRCR_HSI48ON)
#define LL_RCC_CICR_HSI48RDYC              RCC_CICR_HSI48RDYC   /*!< HSI48 Clock Security System Interrupt Clear */
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg function
  * @{
  */
#define LL_RCC_CIFR_LSIRDYF                RCC_CIFR_LSIRDYF     /*!< LSI Ready Interrupt flag */
#define LL_RCC_CIFR_LSERDYF                RCC_CIFR_LSERDYF     /*!< LSE Ready Interrupt flag */
#define LL_RCC_CIFR_MSIRDYF                RCC_CIFR_MSIRDYF     /*!< MSI Ready Interrupt flag */
#define LL_RCC_CIFR_HSIRDYF                RCC_CIFR_HSIRDYF     /*!< HSI Ready Interrupt flag */
#define LL_RCC_CIFR_HSERDYF                RCC_CIFR_HSERDYF     /*!< HSE Ready Interrupt flag */
#define LL_RCC_CIFR_PLLRDYF                RCC_CIFR_PLLRDYF     /*!< PLL Ready Interrupt flag */
#define LL_RCC_CIFR_CSSF                   RCC_CIFR_CSSF        /*!< HSE Clock Security System Interrupt flag */
#define LL_RCC_CIFR_LSECSSF                RCC_CIFR_LSECSSF     /*!< LSE Clock Security System Interrupt flag */
#if defined(RCC_CRRCR_HSI48ON)
#define LL_RCC_CIFR_HSI48RDYF              RCC_CIFR_HSI48RDYF   /*!< HSI48 Ready Interrupt flag */
#endif /* RCC_CRRCR_HSI48ON */
#define LL_RCC_CSR_RMVF                    RCC_CSR_RMVF         /*!< Low-Power reset flag */
#define LL_RCC_CSR_OBLRSTF                 RCC_CSR_OBLRSTF      /*!< OBL reset flag */
#define LL_RCC_CSR_PINRSTF                 RCC_CSR_PINRSTF      /*!< PIN reset flag */
#define LL_RCC_CSR_PWRRSTF                 RCC_CSR_PWRRSTF      /*!< PWR reset flag */
#define LL_RCC_CSR_SFTRSTF                 RCC_CSR_SFTRSTF      /*!< Software Reset flag */
#define LL_RCC_CSR_IWDGRSTF                RCC_CSR_IWDGRSTF     /*!< Independent Watchdog reset flag */
#define LL_RCC_CSR_WWDGRSTF                RCC_CSR_WWDGRSTF     /*!< Window watchdog reset flag */
#define LL_RCC_CSR_LPWRRSTF                RCC_CSR_LPWRRSTF     /*!< Low-Power reset flag */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIER_LSIRDYIE               RCC_CIER_LSIRDYIE      /*!< LSI Ready Interrupt Enable */
#define LL_RCC_CIER_LSERDYIE               RCC_CIER_LSERDYIE      /*!< LSE Ready Interrupt Enable */
#define LL_RCC_CIER_MSIRDYIE               RCC_CIER_MSIRDYIE      /*!< MSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSIRDYIE               RCC_CIER_HSIRDYIE      /*!< HSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSERDYIE               RCC_CIER_HSERDYIE      /*!< HSE Ready Interrupt Enable */
#define LL_RCC_CIER_PLLRDYIE               RCC_CIER_PLLRDYIE      /*!< PLL Ready Interrupt Enable */
#define LL_RCC_CIER_LSECSSIE               RCC_CIER_LSECSSIE      /*!< LSE CSS Interrupt Enable */
#if defined(RCC_CRRCR_HSI48ON)
#define LL_RCC_CIER_HSI48RDYIE             RCC_CIER_HSI48RDYIE    /*!< HSI48 Ready Interrupt Enable */
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSIPRE  LSI prescaler
  * @{
  */
#define LL_RCC_LSI_DIV_1                   0UL                     /*!< LSI divided by 1   */
#define LL_RCC_LSI_DIV_128                 RCC_CSR_LSIPREDIV       /*!< LSI divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0x00000000U             /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR_LSEDRV_0       /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR_LSEDRV_1       /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_BDCR_LSEDRV         /*!< Xtal mode higher driving capability */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIRANGE  MSI clock ranges
  * @{
  */
#define LL_RCC_MSIRANGE_0                  RCC_CR_MSIRANGE_0  /*!< MSI = 100 KHz  */
#define LL_RCC_MSIRANGE_1                  RCC_CR_MSIRANGE_1  /*!< MSI = 200 KHz  */
#define LL_RCC_MSIRANGE_2                  RCC_CR_MSIRANGE_2  /*!< MSI = 400 KHz  */
#define LL_RCC_MSIRANGE_3                  RCC_CR_MSIRANGE_3  /*!< MSI = 800 KHz  */
#define LL_RCC_MSIRANGE_4                  RCC_CR_MSIRANGE_4  /*!< MSI = 1 MHz    */
#define LL_RCC_MSIRANGE_5                  RCC_CR_MSIRANGE_5  /*!< MSI = 2 MHz    */
#define LL_RCC_MSIRANGE_6                  RCC_CR_MSIRANGE_6  /*!< MSI = 4 MHz    */
#define LL_RCC_MSIRANGE_7                  RCC_CR_MSIRANGE_7  /*!< MSI = 8 MHz    */
#define LL_RCC_MSIRANGE_8                  RCC_CR_MSIRANGE_8  /*!< MSI = 16 MHz   */
#define LL_RCC_MSIRANGE_9                  RCC_CR_MSIRANGE_9  /*!< MSI = 24 MHz   */
#define LL_RCC_MSIRANGE_10                 RCC_CR_MSIRANGE_10 /*!< MSI = 32 MHz   */
#define LL_RCC_MSIRANGE_11                 RCC_CR_MSIRANGE_11 /*!< MSI = 48 MHz   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSISRANGE  MSI range after Standby mode
  * @{
  */
#define LL_RCC_MSISRANGE_4                 RCC_CSR_MSISTBYRG_1  /*!< MSI = 1 MHz    */
#define LL_RCC_MSISRANGE_5                 RCC_CSR_MSISTBYRG_2  /*!< MSI = 2 MHz    */
#define LL_RCC_MSISRANGE_6                 RCC_CSR_MSISTBYRG_4  /*!< MSI = 4 MHz    */
#define LL_RCC_MSISRANGE_7                 RCC_CSR_MSISTBYRG_8  /*!< MSI = 8 MHz    */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI          0x00000000U          /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE          RCC_BDCR_LSCOSEL     /*!< LSE selection for low speed clock  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_MSI           (0x00000000U)                     /*!< MSI selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSI           RCC_CFGR_SW_0                     /*!< HSI selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSE           RCC_CFGR_SW_1                     /*!< HSE selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_PLL           (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)   /*!< PLL selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_LSI           RCC_CFGR_SW_2                     /*!< LSI selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_LSE           (RCC_CFGR_SW_2  |RCC_CFGR_SW_0)   /*!< LSE selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_MSI    (0x00000000U)                      /*!< MSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI    RCC_CFGR_SWS_0                     /*!< HSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_1                     /*!< HSE used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL    (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0)  /*!< PLL used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_LSI    RCC_CFGR_SWS_2                     /*!< LSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_LSE    (RCC_CFGR_SWS_2  |RCC_CFGR_SWS_0)  /*!< LSE used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_SYSCLK_DIV_1       (0x00000000U)                                                           /*!< SYSCLK not divided */
#define LL_RCC_SYSCLK_DIV_2       RCC_CFGR_HPRE_3                                                         /*!< SYSCLK divided by 2 */
#define LL_RCC_SYSCLK_DIV_4       (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0)                                     /*!< SYSCLK divided by 4 */
#define LL_RCC_SYSCLK_DIV_8       (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1)                                     /*!< SYSCLK divided by 8 */
#define LL_RCC_SYSCLK_DIV_16      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)                   /*!< SYSCLK divided by 16 */
#define LL_RCC_SYSCLK_DIV_64      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2)                                     /*!< SYSCLK divided by 64 */
#define LL_RCC_SYSCLK_DIV_128     (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0)                   /*!< SYSCLK divided by 128 */
#define LL_RCC_SYSCLK_DIV_256     (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1)                   /*!< SYSCLK divided by 256 */
#define LL_RCC_SYSCLK_DIV_512     (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_DIV_1         (0x00000000U)                                         /*!< APB not divided */
#define LL_RCC_APB1_DIV_2         RCC_CFGR_PPRE_2                                       /*!< APB divided by 2 */
#define LL_RCC_APB1_DIV_4         (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_0)                   /*!< APB divided by 4 */
#define LL_RCC_APB1_DIV_8         (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1)                   /*!< APB divided by 8 */
#define LL_RCC_APB1_DIV_16        (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_0) /*!< APB divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUPCLOCK  Wakeup from Stop and CSS backup clock selection
  * @{
  */
#define LL_RCC_STOP_WAKEUPCLOCK_MSI        0x00000000U             /*!< MSI selection after wake-up from STOP */
#define LL_RCC_STOP_WAKEUPCLOCK_HSI        RCC_CFGR_STOPWUCK       /*!< HSI selection after wake-up from STOP */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK    (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | 0x00000000U)            /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCO1SOURCE_SYSCLK     (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_0)     /*!< SYSCLK selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_MSI        (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_1)     /*!< MSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSI16      (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_1 |\
                                                RCC_CFGR_MCO1SEL_0)                               /*!< HSI16 selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSE        (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_2)     /*!< HSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PLLCLK     (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_2 |\
                                                RCC_CFGR_MCO1SEL_0)                               /*!< Main PLL selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSI        (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_2 |\
                                                RCC_CFGR_MCO1SEL_1)                               /*!< LSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSE        (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_2 |\
                                                RCC_CFGR_MCO1SEL_1     | RCC_CFGR_MCO1SEL_0)      /*!< LSE selection as MCO1 source */
#if defined(RCC_CRRCR_HSI48ON)
#define LL_RCC_MCO1SOURCE_HSI48      (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_3)     /*!< HSI48 selection as MCO1 source */
#endif /* RCC_CRRCR_HSI48ON */
#define LL_RCC_MCO1SOURCE_RTC        (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_3 |\
                                                RCC_CFGR_MCO1SEL_0)                               /*!< RTC alter clk selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_RTCWUPI    (uint32_t)((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_3 |\
                                                RCC_CFGR_MCO1SEL_1)                               /*!< RTC wakeup interrupt signal selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */

#define LL_RCC_MCO1_DIV_1        (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | 0x00000000U)             /*!< MCO not divided */

#define LL_RCC_MCO1_DIV_2        (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_0)      /*!< MCO divided by 2 */
#define LL_RCC_MCO1_DIV_4        (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_1)      /*!< MCO divided by 4 */
#define LL_RCC_MCO1_DIV_8        (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_1 |\
                                            RCC_CFGR_MCO1PRE_0)                                /*!< MCO divided by 8 */
#define LL_RCC_MCO1_DIV_16       (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2)      /*!< MCO divided by 16 */
#define LL_RCC_MCO1_DIV_32       (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2 |\
                                            RCC_CFGR_MCO1PRE_0)                                /*!< MCO divided by 32 */
#define LL_RCC_MCO1_DIV_64       (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2 |\
                                            RCC_CFGR_MCO1PRE_1)                                /*!< MCO divided by 64 */
#define LL_RCC_MCO1_DIV_128      (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2 |\
                                            RCC_CFGR_MCO1PRE_1     | RCC_CFGR_MCO1PRE_0)      /*!< MCO divided by 128 */
#define LL_RCC_MCO1_DIV_256      (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_3)     /*!< MCO divided by 256 */
#define LL_RCC_MCO1_DIV_512      (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_3 |\
                                            RCC_CFGR_MCO1PRE_0)                               /*!< MCO divided by 512 */
#define LL_RCC_MCO1_DIV_1024     (uint32_t)((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_3 |\
                                            RCC_CFGR_MCO1PRE_1)                              /*!< MCO divided by 1024 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2SOURCE  MCO2 SOURCE selection
  * @{
  */
#define LL_RCC_MCO2SOURCE_NOCLOCK    (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | 0x00000000U)           /*!< MCO output disabled, no clock on MCO2 */
#define LL_RCC_MCO2SOURCE_SYSCLK     (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_0)    /*!< SYSCLK selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_MSI        (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_1)    /*!< MSI selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSI16      (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_1 |\
                                                RCC_CFGR_MCO2SEL_0)                              /*!< HSI16 selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSE        (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2)    /*!< HSE selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_PLLCLK     (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2 |\
                                                RCC_CFGR_MCO2SEL_0)                              /*!< Main PLL selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_LSI        (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2 |\
                                                RCC_CFGR_MCO2SEL_1)                              /*!< LSI selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_LSE        (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2 |\
                                                RCC_CFGR_MCO2SEL_1     | RCC_CFGR_MCO2SEL_0)     /*!< LSE selection as MCO2 source */
#if defined(RCC_CRRCR_HSI48ON)
#define LL_RCC_MCO2SOURCE_HSI48      (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_3)    /*!< HSI48 selection as MCO2 source */
#endif /* RCC_CRRCR_HSI48ON */
#define LL_RCC_MCO2SOURCE_RTC        (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_3 |\
                                                RCC_CFGR_MCO2SEL_0)                              /*!< RTC alter clk selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_RTCWUPI    (uint32_t)((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_3 |\
                                                RCC_CFGR_MCO2SEL_1)                              /*!< RTC wakeup interrupt signal selection as MCO2 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2_DIV  MCO2 prescaler
  * @{
  */

#define LL_RCC_MCO2_DIV_1         (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | 0x00000000U)           /*!< MCO not divided */

#define LL_RCC_MCO2_DIV_2         (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_0)    /*!< MCO divided by 2 */
#define LL_RCC_MCO2_DIV_4         (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_1)    /*!< MCO divided by 4 */
#define LL_RCC_MCO2_DIV_8         (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_1 |\
                                             RCC_CFGR_MCO2PRE_0)                              /*!< MCO divided by 8 */
#define LL_RCC_MCO2_DIV_16        (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2)    /*!< MCO divided by 16 */
#define LL_RCC_MCO2_DIV_32        (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2 |\
                                             RCC_CFGR_MCO2PRE_0)                              /*!< MCO divided by 32 */
#define LL_RCC_MCO2_DIV_64        (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2 |\
                                             RCC_CFGR_MCO2PRE_1)                              /*!< MCO divided by 64 */
#define LL_RCC_MCO2_DIV_128       (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2 |\
                                             RCC_CFGR_MCO2PRE_1     | RCC_CFGR_MCO2PRE_0)     /*!< MCO divided by 128 */
#define LL_RCC_MCO2_DIV_256       (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_3)    /*!< MCO divided by 256 */
#define LL_RCC_MCO2_DIV_512       (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_3 |\
                                             RCC_CFGR_MCO2PRE_0)                              /*!< MCO divided by 512 */
#define LL_RCC_MCO2_DIV_1024      (uint32_t)((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_3 |\
                                             RCC_CFGR_MCO2PRE_1)                             /*!< MCO divided by 1024 */
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO         0x00000000U          /*!< No clock enabled for the peripheral */
#define LL_RCC_PERIPH_FREQUENCY_NA         0xFFFFFFFFU          /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup RCC_LL_EC_USART1_CLKSOURCE  Peripheral USART clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK1      (RCC_CCIPR_USART1SEL << 16U)                           /*!< PCLK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_SYSCLK     ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL_0) /*!< SYSCLK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSI        ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL_1) /*!< HSI clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_LSE        ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL)   /*!< LSE clock used as USART1 clock source */

#define LL_RCC_USART2_CLKSOURCE_PCLK1      (RCC_CCIPR_USART2SEL << 16U)                           /*!< PCLK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_SYSCLK     ((RCC_CCIPR_USART2SEL << 16U) | RCC_CCIPR_USART2SEL_0) /*!< SYSCLK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSI        ((RCC_CCIPR_USART2SEL << 16U) | RCC_CCIPR_USART2SEL_1) /*!< HSI clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_LSE        ((RCC_CCIPR_USART2SEL << 16U) | RCC_CCIPR_USART2SEL)   /*!< LSE clock used as USART2 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUARTx_CLKSOURCE Peripheral LPUART clock source selection
  * @{
  */
#if defined (LPUART3)
#define LL_RCC_LPUART3_CLKSOURCE_PCLK1     ((RCC_CCIPR_LPUART3SEL << 16U) | 0x00000000U)             /*!< PCLK clock used as LPUART3 clock source */
#define LL_RCC_LPUART3_CLKSOURCE_SYSCLK    ((RCC_CCIPR_LPUART3SEL << 16U) | RCC_CCIPR_LPUART3SEL_0)  /*!< SYSCLK clock used as LPUART3 clock source */
#define LL_RCC_LPUART3_CLKSOURCE_HSI       ((RCC_CCIPR_LPUART3SEL << 16U) | RCC_CCIPR_LPUART3SEL_1)  /*!< HSI clock used as LPUART3 clock source */
#define LL_RCC_LPUART3_CLKSOURCE_LSE       ((RCC_CCIPR_LPUART3SEL << 16U) | RCC_CCIPR_LPUART3SEL)    /*!< LSE clock used as LPUART3 clock source */
#endif /* LPUART3 */
#define LL_RCC_LPUART2_CLKSOURCE_PCLK1     ((RCC_CCIPR_LPUART2SEL << 16U) | 0x00000000U)             /*!< PCLK clock used as LPUART2 clock source */
#define LL_RCC_LPUART2_CLKSOURCE_SYSCLK    ((RCC_CCIPR_LPUART2SEL << 16U) | RCC_CCIPR_LPUART2SEL_0)  /*!< SYSCLK clock used as LPUART2 clock source */
#define LL_RCC_LPUART2_CLKSOURCE_HSI       ((RCC_CCIPR_LPUART2SEL << 16U) | RCC_CCIPR_LPUART2SEL_1)  /*!< HSI clock used as LPUART2 clock source */
#define LL_RCC_LPUART2_CLKSOURCE_LSE       ((RCC_CCIPR_LPUART2SEL << 16U) | RCC_CCIPR_LPUART2SEL)    /*!< LSE clock used as LPUART2 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK1     ((RCC_CCIPR_LPUART1SEL << 16U) | 0x00000000U)             /*!< PCLK clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_SYSCLK    ((RCC_CCIPR_LPUART1SEL << 16U) | RCC_CCIPR_LPUART1SEL_0)  /*!< SYSCLK clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSI       ((RCC_CCIPR_LPUART1SEL << 16U) | RCC_CCIPR_LPUART1SEL_1)  /*!< HSI clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_LSE       ((RCC_CCIPR_LPUART1SEL << 16U) | RCC_CCIPR_LPUART1SEL)    /*!< LSE clock used as LPUART1 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C1_CLKSOURCE  Peripheral I2C clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1        ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C1SEL_Pos << 16U))    /*!< PCLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_SYSCLK       ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C1SEL_Pos << 16U) | \
                                            (RCC_CCIPR_I2C1SEL_0 >> RCC_CCIPR_I2C1SEL_Pos))                /*!< SYSCLK clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_HSI          ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C1SEL_Pos << 16U) | \
                                            (RCC_CCIPR_I2C1SEL_1 >> RCC_CCIPR_I2C1SEL_Pos))                /*!< HSI clock used as I2C1 clock source */
#define LL_RCC_I2C3_CLKSOURCE_PCLK1        ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C3SEL_Pos << 16U))    /*!< PCLK1 clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_SYSCLK       ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C3SEL_Pos << 16U) | \
                                            (RCC_CCIPR_I2C3SEL_0 >> RCC_CCIPR_I2C3SEL_Pos))                /*!< SYSCLK clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_HSI          ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C3SEL_Pos << 16U) | \
                                            (RCC_CCIPR_I2C3SEL_1 >> RCC_CCIPR_I2C3SEL_Pos))                /*!< HSI clock used as I2C3 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_TIMx_CLKSOURCE Peripheral TIM clock source selection
  * @{
  */
#define LL_RCC_TIM1_CLKSOURCE_PCLK1     (RCC_CCIPR_TIM1SEL   | (0x00000000U >> 16U))        /*!< PCLK clock used as TIM1 clock source */
#define LL_RCC_TIM1_CLKSOURCE_PLLQ      (RCC_CCIPR_TIM1SEL   | (RCC_CCIPR_TIM1SEL >> 16U))  /*!< PLL used as TIM1 clock source */
/**
  * @}
  */
/** @addtogroup RCC_LL_EC_TIMx_CLKSOURCE
  * @{
  */
#define LL_RCC_TIM15_CLKSOURCE_PCLK1    (RCC_CCIPR_TIM15SEL   | (0x00000000U >> 16U))          /*!< PCLK clock used as TIM15 clock source */
#define LL_RCC_TIM15_CLKSOURCE_PLLQ     (RCC_CCIPR_TIM15SEL   | (RCC_CCIPR_TIM15SEL >> 16U))   /*!< PLL used as TIM15 clock source */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_LPTIMx_CLKSOURCE Peripheral LPTIM clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK1   (RCC_CCIPR_LPTIM1SEL | (0x00000000U >> 16U))           /*!< PCLK selected as LPTIM1 clock */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI     (RCC_CCIPR_LPTIM1SEL | (RCC_CCIPR_LPTIM1SEL_0 >> 16U)) /*!< LSI selected as LPTIM1 clock */
#define LL_RCC_LPTIM1_CLKSOURCE_HSI     (RCC_CCIPR_LPTIM1SEL | (RCC_CCIPR_LPTIM1SEL_1 >> 16U)) /*!< HSI selected as LPTIM1 clock */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE     (RCC_CCIPR_LPTIM1SEL | (RCC_CCIPR_LPTIM1SEL >> 16U))   /*!< LSE selected as LPTIM1 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_PCLK1   (RCC_CCIPR_LPTIM2SEL | (0x00000000U >> 16U))           /*!< PCLK selected as LPTIM2 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_LSI     (RCC_CCIPR_LPTIM2SEL | (RCC_CCIPR_LPTIM2SEL_0 >> 16U)) /*!< LSI selected as LPTIM2 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_HSI     (RCC_CCIPR_LPTIM2SEL | (RCC_CCIPR_LPTIM2SEL_1 >> 16U)) /*!< HSI selected as LPTIM2 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_LSE     (RCC_CCIPR_LPTIM2SEL | (RCC_CCIPR_LPTIM2SEL >> 16U))   /*!< LSE selected as LPTIM2 clock */
#if defined (LPTIM3)
#define LL_RCC_LPTIM3_CLKSOURCE_PCLK1   (RCC_CCIPR_LPTIM3SEL | (0x00000000U >> 16U))           /*!< PCLK selected as LPTIM3 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_LSI     (RCC_CCIPR_LPTIM3SEL | (RCC_CCIPR_LPTIM3SEL_0 >> 16U)) /*!< LSI selected as LPTIM3 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_HSI     (RCC_CCIPR_LPTIM3SEL | (RCC_CCIPR_LPTIM3SEL_1 >> 16U)) /*!< HSI selected as LPTIM3 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_LSE     (RCC_CCIPR_LPTIM3SEL | (RCC_CCIPR_LPTIM3SEL >> 16U))   /*!< LSE selected as LPTIM3 clock */
#endif /* LPTIM3 */
/**
  * @}
  */
#if defined(USB_DRD_FS)
/** @defgroup RCC_LL_EC_USB_CLKSOURCE  Peripheral USB clock source selection
  * @{
  */
#define LL_RCC_USB_CLKSOURCE_NONE          0x00000000U          /*!< No clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_MSI           RCC_CCIPR_CLK48SEL_0 /*!< MSI clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_PLLQ          RCC_CCIPR_CLK48SEL_1 /*!< PLL clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_HSI48         RCC_CCIPR_CLK48SEL   /*!< HSI48 clock used as USB clock source */
#endif /* USB_DRD_FS */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RNG_CLKSOURCE  Peripheral RNG clock source selection
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE_NONE          0x00000000U          /*!< No clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_MSI           RCC_CCIPR_CLK48SEL_0 /*!< MSI clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_PLLQ          RCC_CCIPR_CLK48SEL_1 /*!< PLL clock used as RNG clock source */
#if defined(RCC_CRRCR_HSI48ON)
#define LL_RCC_RNG_CLKSOURCE_HSI48         RCC_CCIPR_CLK48SEL   /*!< HSI48 clock used as RNG clock source */
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_CLKSOURCE  Peripheral ADC clock source selection
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_SYSCLK        0x00000000U          /*!< SYSCLK clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_PLLP          RCC_CCIPR_ADCSEL_0   /*!< PLL P clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_HSI           RCC_CCIPR_ADCSEL_1   /*!< HSI clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_NONE          RCC_CCIPR_ADCSEL     /*!< No clock used as ADC clock source */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_USART1 Peripheral USART get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE            RCC_CCIPR_USART1SEL /*!< USART1 Clock source selection */
#define LL_RCC_USART2_CLKSOURCE            RCC_CCIPR_USART2SEL /*!< USART2 Clock source selection */
#define LL_RCC_USART3_CLKSOURCE            0x00000000U         /*!< To be used for USART3 Clock frequency retrieval */
#define LL_RCC_USART4_CLKSOURCE            0x00000001U         /*!< To be used for USART4 Clock frequency retrieval */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART1 Peripheral LPUART get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE           RCC_CCIPR_LPUART1SEL /*!< LPUART1 Clock source selection */
#define LL_RCC_LPUART2_CLKSOURCE           RCC_CCIPR_LPUART2SEL /*!< LPUART2 Clock source selection */
#if defined (LPUART3)
#define LL_RCC_LPUART3_CLKSOURCE           RCC_CCIPR_LPUART3SEL /*!< LPUART3 Clock source selection */
#endif /* LPUART3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C1 Peripheral I2C get clock source
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE              ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C1SEL_Pos << 16U) | \
                                            (RCC_CCIPR_I2C1SEL >> RCC_CCIPR_I2C1SEL_Pos))    /*!< I2C1 Clock source selection */
#define LL_RCC_I2C3_CLKSOURCE              ((RCC_OFFSET_CCIPR << 24U) | (RCC_CCIPR_I2C3SEL_Pos << 16U) | \
                                            (RCC_CCIPR_I2C3SEL >> RCC_CCIPR_I2C3SEL_Pos))    /*!< I2C3 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_TIMx Peripheral TIMx get clock source
  * @{
  */
#define LL_RCC_TIM1_CLKSOURCE              RCC_CCIPR_TIM1SEL   /*!< TIM1 Clock source selection */
#define LL_RCC_TIM15_CLKSOURCE             RCC_CCIPR_TIM15SEL  /*!< TIM15 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM1 Peripheral LPTIM get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE            RCC_CCIPR_LPTIM1SEL /*!< LPTIM2 Clock source selection */
#define LL_RCC_LPTIM2_CLKSOURCE            RCC_CCIPR_LPTIM2SEL /*!< LPTIM2 Clock source selection */
#if defined (LPTIM3)
#define LL_RCC_LPTIM3_CLKSOURCE            RCC_CCIPR_LPTIM3SEL /*!< LPTIM2 Clock source selection */
#endif /* LPTIM3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RNG  Peripheral RNG get clock source
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE               RCC_CCIPR_CLK48SEL /*!< RNG Clock source selection */
/**
  * @}
  */
#if defined (USB_DRD_FS)
/** @defgroup RCC_LL_EC_USB  Peripheral USB get clock source
  * @{
  */
#define LL_RCC_USB_CLKSOURCE               RCC_CCIPR_CLK48SEL /*!< USB Clock source selection */
#endif /* USB_DRD_FS */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC  Peripheral ADC get clock source
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE               RCC_CCIPR_ADCSEL /*!< ADC Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE          0x00000000U         /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE           RCC_BDCR_RTCSEL_0   /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI           RCC_BDCR_RTCSEL_1   /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV32     RCC_BDCR_RTCSEL     /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLSOURCE  PLL entry clock source
  * @{
  */
#define LL_RCC_PLLSOURCE_NONE     0UL                                            /*!< No clock selected as main PLL entry clock source */
#define LL_RCC_PLLSOURCE_MSI      RCC_PLLCFGR_PLLSRC_0                           /*!< MSI clock selected as main PLL entry clock source */
#define LL_RCC_PLLSOURCE_HSI      RCC_PLLCFGR_PLLSRC_1                           /*!< HSI16 clock selected as main PLL entry clock source */
#define LL_RCC_PLLSOURCE_HSE      (RCC_PLLCFGR_PLLSRC_1 | RCC_PLLCFGR_PLLSRC_0)  /*!< HSE clock selected as main PLL entry clock source */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLM_DIV  PLL division factor
  * @{
  */
#define LL_RCC_PLLM_DIV_1       0x00000000U                                  /*!< Main PLL division factor for PLLM input by 1 */
#define LL_RCC_PLLM_DIV_2       (RCC_PLLCFGR_PLLM_0)                         /*!< Main PLL division factor for PLLM input by 2 */
#define LL_RCC_PLLM_DIV_3       (RCC_PLLCFGR_PLLM_1)                         /*!< Main PLL division factor for PLLM input by 3 */
#define LL_RCC_PLLM_DIV_4       (RCC_PLLCFGR_PLLM_1 | RCC_PLLCFGR_PLLM_0)    /*!< Main PLL division factor for PLLM input by 4 */
#define LL_RCC_PLLM_DIV_5       (RCC_PLLCFGR_PLLM_2)                         /*!< Main PLL division factor for PLLM input by 5 */
#define LL_RCC_PLLM_DIV_6       (RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_0)    /*!< Main PLL division factor for PLLM input by 6 */
#define LL_RCC_PLLM_DIV_7       (RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_1)    /*!< Main PLL division factor for PLLM input by 7 */
#define LL_RCC_PLLM_DIV_8       (RCC_PLLCFGR_PLLM)                           /*!< Main PLL division factor for PLLM input by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLR_DIV  PLL division factor (PLLR)
  * @{
  */
#define LL_RCC_PLLR_DIV_2       (RCC_PLLCFGR_PLLR_0)                        /*!< Main PLL division factor for PLLCLK (system clock) by 2 */
#define LL_RCC_PLLR_DIV_3       (RCC_PLLCFGR_PLLR_1)                        /*!< Main PLL division factor for PLLCLK (system clock) by 3 */
#define LL_RCC_PLLR_DIV_4       (RCC_PLLCFGR_PLLR_1 | RCC_PLLCFGR_PLLR_0)   /*!< Main PLL division factor for PLLCLK (system clock) by 4 */
#define LL_RCC_PLLR_DIV_5       (RCC_PLLCFGR_PLLR_2)                        /*!< Main PLL division factor for PLLCLK (system clock) by 5 */
#define LL_RCC_PLLR_DIV_6       (RCC_PLLCFGR_PLLR_2 | RCC_PLLCFGR_PLLR_0)   /*!< Main PLL division factor for PLLCLK (system clock) by 6 */
#define LL_RCC_PLLR_DIV_7       (RCC_PLLCFGR_PLLR_2 | RCC_PLLCFGR_PLLR_1)   /*!< Main PLL division factor for PLLCLK (system clock) by 7 */
#define LL_RCC_PLLR_DIV_8       (RCC_PLLCFGR_PLLR)                          /*!< Main PLL division factor for PLLCLK (system clock) by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLP_DIV  PLL division factor (PLLP)
  * @{
  */
#define LL_RCC_PLLP_DIV_2      (RCC_PLLCFGR_PLLP_0)                                              /*!< Main PLL division factor for PLLP output by 2 */
#define LL_RCC_PLLP_DIV_3      (RCC_PLLCFGR_PLLP_1)                                              /*!< Main PLL division factor for PLLP output by 3 */
#define LL_RCC_PLLP_DIV_4      (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0)                        /*!< Main PLL division factor for PLLP output by 4 */
#define LL_RCC_PLLP_DIV_5      (RCC_PLLCFGR_PLLP_2)                                              /*!< Main PLL division factor for PLLP output by 5 */
#define LL_RCC_PLLP_DIV_6      (RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_0)                        /*!< Main PLL division factor for PLLP output by 6 */
#define LL_RCC_PLLP_DIV_7      (RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1)                        /*!< Main PLL division factor for PLLP output by 7 */
#define LL_RCC_PLLP_DIV_8      (RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0)  /*!< Main PLL division factor for PLLP output by 8 */
#define LL_RCC_PLLP_DIV_9      (RCC_PLLCFGR_PLLP_3)                                              /*!< Main PLL division factor for PLLP output by 9 */
#define LL_RCC_PLLP_DIV_10     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_0)                        /*!< Main PLL division factor for PLLP output by 10 */
#define LL_RCC_PLLP_DIV_11     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_1)                        /*!< Main PLL division factor for PLLP output by 11 */
#define LL_RCC_PLLP_DIV_12     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0)  /*!< Main PLL division factor for PLLP output by 12 */
#define LL_RCC_PLLP_DIV_13     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2)                        /*!< Main PLL division factor for PLLP output by 13 */
#define LL_RCC_PLLP_DIV_14     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_0)  /*!< Main PLL division factor for PLLP output by 14 */
#define LL_RCC_PLLP_DIV_15     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1)  /*!< Main PLL division factor for PLLP output by 15 */
#define LL_RCC_PLLP_DIV_16     (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0) /*!< Main PLL division factor for PLLP output by 16 */
#define LL_RCC_PLLP_DIV_17     (RCC_PLLCFGR_PLLP_4)                                              /*!< Main PLL division factor for PLLP output by 17 */
#define LL_RCC_PLLP_DIV_18     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_0)                        /*!< Main PLL division factor for PLLP output by 18 */
#define LL_RCC_PLLP_DIV_19     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_1)                        /*!< Main PLL division factor for PLLP output by 19 */
#define LL_RCC_PLLP_DIV_20     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0)  /*!< Main PLL division factor for PLLP output by 20 */
#define LL_RCC_PLLP_DIV_21     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_2)                        /*!< Main PLL division factor for PLLP output by 21 */
#define LL_RCC_PLLP_DIV_22     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_0)  /*!< Main PLL division factor for PLLP output by 22 */
#define LL_RCC_PLLP_DIV_23     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1)  /*!< Main PLL division factor for PLLP output by 23 */
#define LL_RCC_PLLP_DIV_24     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0) /*!< Main PLL division factor for PLLP output by 24 */
#define LL_RCC_PLLP_DIV_25     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3)                        /*!< Main PLL division factor for PLLP output by 25 */
#define LL_RCC_PLLP_DIV_26     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_0)  /*!< Main PLL division factor for PLLP output by 26 */
#define LL_RCC_PLLP_DIV_27     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_1)  /*!< Main PLL division factor for PLLP output by 27 */
#define LL_RCC_PLLP_DIV_28     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_0) /*!< Main PLL division factor for PLLP output by 28 */
#define LL_RCC_PLLP_DIV_29     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2)  /*!< Main PLL division factor for PLLP output by 29 */
#define LL_RCC_PLLP_DIV_30     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_0) /*!< Main PLL division factor for PLLP output by 30 */
#define LL_RCC_PLLP_DIV_31     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1) /*!< Main PLL division factor for PLLP output by 31 */
#define LL_RCC_PLLP_DIV_32     (RCC_PLLCFGR_PLLP_4|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_1| \
                                RCC_PLLCFGR_PLLP_0)                                       /*!< Main PLL division factor for PLLP output by 32 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLQ_DIV  PLL division factor (PLLQ)
  * @{
  */
#define LL_RCC_PLLQ_DIV_2       (RCC_PLLCFGR_PLLQ_0)    /*!< Main PLL division factor for PLLQ output by 2 */
#define LL_RCC_PLLQ_DIV_3       (RCC_PLLCFGR_PLLQ_1)    /*!< Main PLL division factor for PLLQ output by 3 */
#define LL_RCC_PLLQ_DIV_4       (RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_0)    /*!< Main PLL division factor for PLLQ output by 4 */
#define LL_RCC_PLLQ_DIV_5       (RCC_PLLCFGR_PLLQ_2)    /*!< Main PLL division factor for PLLQ output by 5 */
#define LL_RCC_PLLQ_DIV_6       (RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_0)      /*!< Main PLL division factor for PLLQ output by 6 */
#define LL_RCC_PLLQ_DIV_7       (RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_1)      /*!< Main PLL division factor for PLLQ output by 7 */
#define LL_RCC_PLLQ_DIV_8       (RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_0)      /*!< Main PLL division factor for PLLQ output by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIRANGESEL  MSI clock range selection
  * @{
  */
#define LL_RCC_MSIRANGESEL_STANDBY         0U                  /*!< MSI Range is provided by MSISRANGE */
#define LL_RCC_MSIRANGESEL_RUN             1U                  /*!< MSI Range is provided by MSIRANGE */
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
  * @brief  Helper macro to calculate the PLLCLK frequency on system domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_R_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetM (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetR ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on MSI/HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  *
  * @param  __PLLN__ Between 4 and 127
  * @param  __PLLR__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLR_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_3
  *         @arg @ref LL_RCC_PLLR_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_5
  *         @arg @ref LL_RCC_PLLR_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_7
  *         @arg @ref LL_RCC_PLLR_DIV_8
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_R_FREQ(__INPUTFREQ__, __PLLM__, __PLLN__, __PLLR__) \
  ((__INPUTFREQ__) / ((((__PLLM__)>> RCC_PLLCFGR_PLLM_Pos) + 1U)) * (__PLLN__) / \
   (((__PLLR__)>> RCC_PLLCFGR_PLLR_Pos) + 1U))

/**
  * @brief  Helper macro to calculate the PLLCLK frequency used on 48M domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_Q_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetM (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetQ ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on MSI/HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  *
  * @param  __PLLN__ Between 4 and 127
  * @param  __PLLQ__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_3
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_5
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_7
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_Q_FREQ(__INPUTFREQ__, __PLLM__, __PLLN__, __PLLQ__) ((((__INPUTFREQ__) \
    /(((__PLLM__)>> RCC_PLLCFGR_PLLM_Pos) +1UL))) * (__PLLN__)) / (((__PLLQ__)>> RCC_PLLCFGR_PLLQ_Pos) + 1UL)

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on MSI/HSE/HSI/PLLCLK)
  * @param  __AHBPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval HCLK clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK_FREQ(__SYSCLKFREQ__, __AHBPRESCALER__) \
  ((__SYSCLKFREQ__) >> AHBPrescTable[((__AHBPRESCALER__) & \
                                      RCC_CFGR_HPRE) >>  RCC_CFGR_HPRE_Pos])

/**
  * @brief  Helper macro to calculate the PCLK frequency (APB)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APBPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APBPRESCALER__) \
  ((__HCLKFREQ__) >> APBPrescTable[(__APBPRESCALER__) >>  RCC_CFGR_PPRE_Pos])

/**
  * @brief  Helper macro to calculate the MSI frequency (in Hz)
  * @note __MSISEL__ can be retrieved thanks to function LL_RCC_MSI_IsEnabledRangeSelect()
  * @note if __MSISEL__ is equal to LL_RCC_MSIRANGESEL_STANDBY,
  *        __MSIRANGE__can be retrieved by LL_RCC_MSI_GetRangeAfterStandby()
  *        else by LL_RCC_MSI_GetRange()
  *        ex: __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
  *              (LL_RCC_MSI_IsEnabledRangeSelect()?
  *               LL_RCC_MSI_GetRange():
  *               LL_RCC_MSI_GetRangeAfterStandby()))
  * @param  __MSISEL__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGESEL_STANDBY
  *         @arg @ref LL_RCC_MSIRANGESEL_RUN
  * @param  __MSIRANGE__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGE_0
  *         @arg @ref LL_RCC_MSIRANGE_1
  *         @arg @ref LL_RCC_MSIRANGE_2
  *         @arg @ref LL_RCC_MSIRANGE_3
  *         @arg @ref LL_RCC_MSIRANGE_4
  *         @arg @ref LL_RCC_MSIRANGE_5
  *         @arg @ref LL_RCC_MSIRANGE_6
  *         @arg @ref LL_RCC_MSIRANGE_7
  *         @arg @ref LL_RCC_MSIRANGE_8
  *         @arg @ref LL_RCC_MSIRANGE_9
  *         @arg @ref LL_RCC_MSIRANGE_10
  *         @arg @ref LL_RCC_MSIRANGE_11
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  * @retval MSI clock frequency (in Hz)
  */
#define __LL_RCC_CALC_MSI_FREQ(__MSISEL__, __MSIRANGE__)   (((__MSISEL__) == LL_RCC_MSIRANGESEL_STANDBY) ? \
                                                            (MSIRangeTable[(__MSIRANGE__) >> 8U]) : \
                                                            (MSIRangeTable[(__MSIRANGE__) >> 4U]))

/**
  * @brief  Helper macro to calculate the PLLPCLK frequency used on P domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_P_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetM (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetP ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  __PLLN__ Between Min_Data = 4 and Max_Data = 127
  * @param  __PLLP__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLP_DIV_2
  *         @arg @ref LL_RCC_PLLP_DIV_3
  *         @arg @ref LL_RCC_PLLP_DIV_4
  *         @arg @ref LL_RCC_PLLP_DIV_5
  *         @arg @ref LL_RCC_PLLP_DIV_6
  *         @arg @ref LL_RCC_PLLP_DIV_7
  *         @arg @ref LL_RCC_PLLP_DIV_8
  *         @arg @ref LL_RCC_PLLP_DIV_9
  *         @arg @ref LL_RCC_PLLP_DIV_10
  *         @arg @ref LL_RCC_PLLP_DIV_11
  *         @arg @ref LL_RCC_PLLP_DIV_12
  *         @arg @ref LL_RCC_PLLP_DIV_13
  *         @arg @ref LL_RCC_PLLP_DIV_14
  *         @arg @ref LL_RCC_PLLP_DIV_15
  *         @arg @ref LL_RCC_PLLP_DIV_16
  *         @arg @ref LL_RCC_PLLP_DIV_17
  *         @arg @ref LL_RCC_PLLP_DIV_18
  *         @arg @ref LL_RCC_PLLP_DIV_19
  *         @arg @ref LL_RCC_PLLP_DIV_20
  *         @arg @ref LL_RCC_PLLP_DIV_21
  *         @arg @ref LL_RCC_PLLP_DIV_22
  *         @arg @ref LL_RCC_PLLP_DIV_23
  *         @arg @ref LL_RCC_PLLP_DIV_24
  *         @arg @ref LL_RCC_PLLP_DIV_25
  *         @arg @ref LL_RCC_PLLP_DIV_26
  *         @arg @ref LL_RCC_PLLP_DIV_27
  *         @arg @ref LL_RCC_PLLP_DIV_28
  *         @arg @ref LL_RCC_PLLP_DIV_29
  *         @arg @ref LL_RCC_PLLP_DIV_30
  *         @arg @ref LL_RCC_PLLP_DIV_31
  *         @arg @ref LL_RCC_PLLP_DIV_32
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_P_FREQ(__INPUTFREQ__, __PLLM__, __PLLN__, __PLLP__)  \
  ((__INPUTFREQ__) * (__PLLN__) / ((((__PLLM__)>> RCC_PLLCFGR_PLLM_Pos) + 1U)) /    \
   (((__PLLP__) >> RCC_PLLCFGR_PLLP_Pos) + 1U))
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
  * @brief  Enable the Clock Security System.
  * @rmtoll CR           CSSON         LL_RCC_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_CSSON);
}

/**
  * @brief  Disable the Clock Security System.
  * @rmtoll CR           CSSON         LL_RCC_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSS(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_CSSON);
}

/**
  * @brief  Enable HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        LL_RCC_HSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Disable HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        LL_RCC_HSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
}

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
  return (READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY));
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
  * @brief  IsEnabled HSI in stop mode
  * @rmtoll CR           HSIKERON      LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSIKERON) == (RCC_CR_HSIKERON));
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
  return (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY));
}

/**
  * @brief  Enable HSI oscillator in auto start from stop mode
  * @rmtoll CR           HSIASFS         LL_RCC_HSI_EnableAutoFromStop
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_EnableAutoFromStop(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIASFS);
}

/**
  * @brief  Disable HSI oscillator in auto start from stop mode
  * @rmtoll CR           HSIASFS         LL_RCC_HSI_DisableAutoFromStop
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_DisableAutoFromStop(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIASFS);
}

/**
  * @brief  Check if HSI is enabled in auto start from stop mode
  * @rmtoll CR           HSIASFS        LL_RCC_HSI_IsEnabledInAutoFromStop
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInAutoFromStop(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIASFS) == RCC_CR_HSIASFS) ? 1U : 0U);
}

/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll ICSCR        HSICAL        LL_RCC_HSI_GetCalibration
  * @retval Between Min_Data = 0x00 and Max_Data = 0xFF
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_HSICAL) >> RCC_ICSCR_HSICAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value that is added to the HSICAL
  * @note Default value is 16, which, when added to the HSICAL value,
  *       should trim the HSI to 16 MHz +/- 1 %
  * @rmtoll ICSCR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 31
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, Value << RCC_ICSCR_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll ICSCR        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 31
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_HSITRIM) >> RCC_ICSCR_HSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Enable LSE oscillator propagation for system clock
  * @rmtoll BDCR         LSESYSEN      LL_RCC_LSE_EnablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnablePropagation(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Disable LSE oscillator propagation for system clock
  * @rmtoll BDCR         LSESYSEN      LL_RCC_LSE_DisablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisablePropagation(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll BDCR         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t LSEDrive)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll BDCR         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSEDRV));
}

/**
  * @brief  Enable Clock security system on LSE.
  * @rmtoll BDCR         LSECSSON      LL_RCC_LSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable Clock security system on LSE.
  * @note Clock security system can be disabled only after a LSE
  *       failure detection. In that case it MUST be disabled by software.
  * @rmtoll BDCR         LSECSSON      LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == (RCC_BDCR_LSERDY));
}

/**
  * @brief  Check if LSE oscillator propagation for system clock Ready
  * @rmtoll BDCR         LSESYSRDY     LL_RCC_LSE_IsPropagationReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsPropagationReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) == RCC_BDCR_LSESYSRDY));
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll BDCR         LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return (READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == (RCC_BDCR_LSECSSD));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI Oscillator
  * @rmtoll CSR          LSION         LL_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll CSR          LSION         LL_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll CSR          LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == (RCC_CSR_LSIRDY));
}
/**
  * @brief  Set LSI prescaler
  * @rmtoll CSR          LSIPRE        LL_RCC_LSI_SetPrescaler
  * @param  LSIPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI_DIV_1
  *         @arg @ref LL_RCC_LSI_DIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_SetPrescaler(uint32_t LSIPrescaler)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_LSIPREDIV, LSIPrescaler);
}

/**
  * @brief  Get LSI prescaler
  * @rmtoll CSR          LSIPRE        LL_RCC_LSI_GetPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI_DIV_1
  *         @arg @ref LL_RCC_LSI_DIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_GetPrescaler(void)
{
  return (READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV));
}

/**
  * @}
  */
/**
  * @}
  */

/** @defgroup RCC_LL_EF_MSI MSI
  * @{
  */

/**
  * @brief  Enable MSI oscillator
  * @rmtoll CR           MSION         LL_RCC_MSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSION);
}

/**
  * @brief  Disable MSI oscillator
  * @rmtoll CR           MSION         LL_RCC_MSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSION);
}

/**
  * @brief  Check if MSI oscillator Ready
  * @rmtoll CR           MSIRDY        LL_RCC_MSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsReady(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_MSIRDY) == (RCC_CR_MSIRDY));
}

/**
  * @brief  Enable MSI PLL-mode (Hardware auto calibration with LSE)
  * @note MSIPLLEN must be enabled after LSE is enabled (LSEON enabled)
  *       and ready (LSERDY set by hardware)
  * @note hardware protection to avoid enabling MSIPLLEN if LSE is not
  *       ready
  * @rmtoll CR           MSIPLLEN      LL_RCC_MSI_EnablePLLMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_EnablePLLMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Disable MSI-PLL mode
  * @note cleared by hardware when LSE is disabled (LSEON = 0) or when
  *       the Clock Security System on LSE detects a LSE failure
  * @rmtoll CR           MSIPLLEN      LL_RCC_MSI_DisablePLLMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_DisablePLLMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Enable MSI clock range selection with MSIRANGE register
  * @note Write 0 has no effect. After a standby or a reset
  *       MSIRGSEL is at 0 and the MSI range value is provided by
  *       MSISRANGE
  * @rmtoll CR           MSIRGSEL      LL_RCC_MSI_EnableRangeSelection
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_EnableRangeSelection(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);
}

/**
  * @brief  Check if MSI clock range is selected with MSIRANGE register
  * @rmtoll CR           MSIRGSEL      LL_RCC_MSI_IsEnabledRangeSelect
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsEnabledRangeSelect(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_MSIRGSEL) == (RCC_CR_MSIRGSEL));
}

/**
  * @brief  Configure the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll CR           MSIRANGE      LL_RCC_MSI_SetRange
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGE_0
  *         @arg @ref LL_RCC_MSIRANGE_1
  *         @arg @ref LL_RCC_MSIRANGE_2
  *         @arg @ref LL_RCC_MSIRANGE_3
  *         @arg @ref LL_RCC_MSIRANGE_4
  *         @arg @ref LL_RCC_MSIRANGE_5
  *         @arg @ref LL_RCC_MSIRANGE_6
  *         @arg @ref LL_RCC_MSIRANGE_7
  *         @arg @ref LL_RCC_MSIRANGE_8
  *         @arg @ref LL_RCC_MSIRANGE_9
  *         @arg @ref LL_RCC_MSIRANGE_10
  *         @arg @ref LL_RCC_MSIRANGE_11
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetRange(uint32_t Range)
{
  MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, Range);
}

/**
  * @brief  Get the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll CR           MSIRANGE      LL_RCC_MSI_GetRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGE_0
  *         @arg @ref LL_RCC_MSIRANGE_1
  *         @arg @ref LL_RCC_MSIRANGE_2
  *         @arg @ref LL_RCC_MSIRANGE_3
  *         @arg @ref LL_RCC_MSIRANGE_4
  *         @arg @ref LL_RCC_MSIRANGE_5
  *         @arg @ref LL_RCC_MSIRANGE_6
  *         @arg @ref LL_RCC_MSIRANGE_7
  *         @arg @ref LL_RCC_MSIRANGE_8
  *         @arg @ref LL_RCC_MSIRANGE_9
  *         @arg @ref LL_RCC_MSIRANGE_10
  *         @arg @ref LL_RCC_MSIRANGE_11
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetRange(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_MSIRANGE));
}

/**
  * @brief  Configure MSI range used after standby
  * @rmtoll CSR          MSISTBYRG     LL_RCC_MSI_SetRangeAfterStandby
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetRangeAfterStandby(uint32_t Range)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_MSISTBYRG, Range);
}

/**
  * @brief  Get MSI range used after standby
  * @rmtoll CSR          MSISTBYRG     LL_RCC_MSI_GetRangeAfterStandby
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetRangeAfterStandby(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSISTBYRG));
}

/**
  * @brief  Get MSI Calibration value
  * @note When MSITRIM is written, MSICAL is updated with the sum of
  *       MSITRIM and the factory trim value
  * @rmtoll ICSCR        MSICAL        LL_RCC_MSI_GetCalibration
  * @retval Between Min_Data = 0 and Max_Data = 255
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_MSICAL) >> RCC_ICSCR_MSICAL_Pos);
}

/**
  * @brief  Set MSI Calibration trimming
  * @note user-programmable trimming value that is added to the MSICAL
  * @rmtoll ICSCR        MSITRIM       LL_RCC_MSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 255
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, Value << RCC_ICSCR_MSITRIM_Pos);
}

/**
  * @brief  Get MSI Calibration trimming
  * @rmtoll ICSCR        MSITRIM       LL_RCC_MSI_GetCalibTrimming
  * @retval Between 0 and 255
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_MSITRIM) >> RCC_ICSCR_MSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll BDCR         LSCOEN        LL_RCC_LSCO_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll BDCR         LSCOEN        LL_RCC_LSCO_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll BDCR         LSCOSEL       LL_RCC_LSCO_SetSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL, Source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll BDCR         LSCOSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSCOSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll CFGR         SW            LL_RCC_SetSysClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_MSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, Source);
}

/**
  * @brief  Get the system clock source
  * @rmtoll CFGR         SWS           LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_MSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_LSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll CFGR         HPRE          LL_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, Prescaler);
}

/**
  * @brief  Set APB prescaler
  * @rmtoll CFGR         PPRE         LL_RCC_SetAPBPrescaler
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
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, Prescaler);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll CFGR         HPRE          LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE));
}

/**
  * @brief  Get APB prescaler
  * @rmtoll CFGR         PPRE         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE));
}

/**
  * @brief  Set Clock After Wake-Up From Stop mode
  * @rmtoll CFGR         STOPWUCK      LL_RCC_SetClkAfterWakeFromStop
  * @param  Clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_MSI
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetClkAfterWakeFromStop(uint32_t Clock)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPWUCK, Clock);
}

/**
  * @brief  Get Clock After Wake-Up From Stop mode
  * @rmtoll CFGR         STOPWUCK      LL_RCC_GetClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_MSI
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetClkAfterWakeFromStop(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_STOPWUCK));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll CFGR         MCO1          LL_RCC_ConfigMCO\n
  *         CFGR         MCO1PRE       LL_RCC_ConfigMCO\n
  *         CFGR         MCO2          LL_RCC_ConfigMCO\n
  *         CFGR         MCO2PRE       LL_RCC_ConfigMCO
  * @param  MCOxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO1SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_MSI
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI16
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLLCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_LSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO2SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_MSI
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI16
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_PLLCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  *         @arg @ref LL_RCC_MCO2SOURCE_LSE
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI48
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_DIV_1
  *         @arg @ref LL_RCC_MCO1_DIV_2
  *         @arg @ref LL_RCC_MCO1_DIV_4
  *         @arg @ref LL_RCC_MCO1_DIV_8
  *         @arg @ref LL_RCC_MCO1_DIV_16
  *         @arg @ref LL_RCC_MCO1_DIV_32
  *         @arg @ref LL_RCC_MCO1_DIV_64
  *         @arg @ref LL_RCC_MCO1_DIV_128
  *         @arg @ref LL_RCC_MCO1_DIV_256
  *         @arg @ref LL_RCC_MCO1_DIV_512
  *         @arg @ref LL_RCC_MCO2_DIV_1
  *         @arg @ref LL_RCC_MCO2_DIV_2
  *         @arg @ref LL_RCC_MCO2_DIV_4
  *         @arg @ref LL_RCC_MCO2_DIV_8
  *         @arg @ref LL_RCC_MCO2_DIV_16
  *         @arg @ref LL_RCC_MCO2_DIV_32
  *         @arg @ref LL_RCC_MCO2_DIV_64
  *         @arg @ref LL_RCC_MCO2_DIV_128
  *         @arg @ref LL_RCC_MCO2_DIV_256
  *         @arg @ref LL_RCC_MCO2_DIV_512
  *         @arg @ref LL_RCC_MCO2_DIV_1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR, (MCOxSource << 16U) | (MCOxPrescaler << 16U), \
             (MCOxSource & 0xFFFF0000U) | (MCOxPrescaler & 0xFFFF0000U));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure USARTx clock source
  * @rmtoll CCIPR        USARTxSEL     LL_RCC_SetUSARTClockSource
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK1
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
  MODIFY_REG(RCC->CCIPR, (USARTxSource >> 16), (USARTxSource & 0x0000FFFF));
}

/**
  * @brief  Configure LPUART1x clock source
  * @rmtoll CCIPR        LPUART1SEL    LL_RCC_SetLPUARTClockSource
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_SYSCLK (*)
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_LSE (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t LPUARTxSource)
{
  MODIFY_REG(RCC->CCIPR, (LPUARTxSource >> 16), (LPUARTxSource & 0x0000FFFFU));
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CCIPR        I2CxSEL       LL_RCC_SetI2CClockSource
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t I2CxSource)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0x88U + (I2CxSource >> 24U));
  MODIFY_REG(*reg, 3U << ((I2CxSource & 0x00FF0000U) >> 16U), \
             ((I2CxSource & 0x000000FFU) << ((I2CxSource & 0x00FF0000U) >> 16U)));
}

/**
  * @brief  Configure TIMx clock source
  * @rmtoll CCIPR        TIMxSEL       LL_RCC_SetTIMClockSource
  * @param  TIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_TIM1_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_TIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_TIM15_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_TIM15_CLKSOURCE_PCLK1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTIMClockSource(uint32_t TIMxSource)
{
  MODIFY_REG(RCC->CCIPR, (TIMxSource & 0xFFFF0000U), (TIMxSource << 16));
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll CCIPR        LPTIMxSEL     LL_RCC_SetLPTIMClockSource
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSI   (*)
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_HSI   (*)
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSE   (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t LPTIMxSource)
{
  MODIFY_REG(RCC->CCIPR, (LPTIMxSource & 0xFFFF0000U), (LPTIMxSource << 16U));
}

/**
  * @brief  Configure RNG clock source
  * @rmtoll CCIPR        CLK48MSEL      LL_RCC_SetRNGClockSource
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_MSI
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRNGClockSource(uint32_t RNGxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CLK48SEL, RNGxSource);
}

#if defined(USB_DRD_FS)
/**
  * @brief  Configure USB clock source
  * @rmtoll CCIPR        USBSEL      LL_RCC_SetUSBClockSource
  * @param  USBxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_USB_CLKSOURCE_MSI
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSBClockSource(uint32_t USBxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CLK48SEL, USBxSource);
}
#endif /* USB_DRD_FS */

/**
  * @brief  Configure ADC clock source
  * @rmtoll CCIPR        ADCSEL        LL_RCC_SetADCClockSource
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLLP
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t ADCxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, ADCxSource);
}

/**
  * @brief  Get USARTx clock source
  * @rmtoll CCIPR        USARTxSEL     LL_RCC_GetUSARTClockSource
  * @param  USARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *
  *         (*) value not defined in all devices.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK1
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
  return (uint32_t)(READ_BIT(RCC->CCIPR, USARTx) | (USARTx << 16U));
}

/**
  * @brief  Get LPUARTx clock source
  * @rmtoll CCIPR        LPUART1SEL    LL_RCC_GetLPUARTClockSource
  * @param  LPUARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_SYSCLK (*)
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_LPUART3_CLKSOURCE_LSE (*)
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t LPUARTx)
{
  return (uint32_t)((READ_BIT(RCC->CCIPR, LPUARTx) | (LPUARTx << 16U)));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CCIPR        I2CxSEL       LL_RCC_GetI2CClockSource
  * @param  I2Cx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *
  *         (*) value not defined in all devices.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
 */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t I2Cx)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0x88U + (I2Cx >> 24U));
  return (uint32_t)((READ_BIT(*reg, 3U << ((I2Cx & 0x0000FF0000U) >> 16U)) >> ((I2Cx & 0x0000FF0000U) >> 16U)) | \
                    (I2Cx & 0xFFFF0000U));
}

/**
  * @brief  Get TIMx clock source
  * @rmtoll CCIPR        TIMxSEL       LL_RCC_GetTIMClockSource
  * @param  TIMx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_TIM1_CLKSOURCE
  *         @arg @ref LL_RCC_TIM15_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_TIM1_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_TIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_TIM15_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_TIM15_CLKSOURCE_PCLK1
  */
__STATIC_INLINE uint32_t LL_RCC_GetTIMClockSource(uint32_t TIMx)
{
  return (uint32_t)((READ_BIT(RCC->CCIPR, TIMx) >> 16U) | TIMx);
}

/**
  * @brief  Get LPTIMx clock source
  * @rmtoll CCIPR        LPTIM1SEL     LL_RCC_GetLPTIMClockSource\n
  *         CCIPR        LPTIM2SEL     LL_RCC_GetLPTIMClockSource
  *         CCIPR        LPTIM3SEL     LL_RCC_GetLPTIMClockSource
  * @param  LPTIMx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSI   (*)
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_HSI   (*)
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSE   (*)
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t LPTIMx)
{
  return (uint32_t)((READ_BIT(RCC->CCIPR, LPTIMx) >> 16U) | LPTIMx);
}

/**
  * @brief  Get RNGx clock source
  * @rmtoll CCIPR        CLK48SEL      LL_RCC_GetRNGClockSource
  * @param  RNGx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_MSI
  *
  */
__STATIC_INLINE uint32_t LL_RCC_GetRNGClockSource(uint32_t RNGx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, RNGx));
}

#if defined (USB_DRD_FS)
/**
  * @brief  Get USBx clock source
  * @rmtoll CCIPR        CLK48SEL      LL_RCC_GetUSBClockSource
  * @param  USBx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLLQ
  *         @arg @ref LL_RCC_USB_CLKSOURCE_MSI
  *
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBClockSource(uint32_t USBx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, USBx));
}
#endif /* USB_DRD_FS */

/**
  * @brief  Get ADCx clock source
  * @rmtoll CCIPR        ADCSEL        LL_RCC_GetADCClockSource
  * @param  ADCx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLLP
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t ADCx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, ADCx));
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
  * @rmtoll BDCR         RTCSEL        LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll BDCR         RTCSEL        LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL));
}

/**
  * @brief  Enable RTC
  * @rmtoll BDCR         RTCEN         LL_RCC_EnableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll BDCR         RTCEN         LL_RCC_DisableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll BDCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return (READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == (RCC_BDCR_RTCEN));
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll BDCR         BDRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR         BDRST         LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL PLL
  * @{
  */

/**
  * @brief  Enable PLL
  * @rmtoll CR           PLLON         LL_RCC_PLL_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @brief  Disable PLL
  * @note Cannot be disabled if the PLL clock is used as the system clock
  * @rmtoll CR           PLLON         LL_RCC_PLL_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @brief  Check if PLL Ready
  * @rmtoll CR           PLLRDY        LL_RCC_PLL_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_IsReady(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY));
}

/** @defgroup RCC_LL_EF_HSI48 HSI48
  * @{
  */
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Enable HSI48
  * @rmtoll CRRCR           HSI48ON         LL_RCC_HSI48_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Enable(void)
{
  SET_BIT(RCC->CRRCR, RCC_CRRCR_HSI48ON);
}

/**
  * @brief  Disable HSI48
  * @note Cannot be disabled if the HSI48 clock is used as the system clock
  * @rmtoll CRRCR           HSI48ON         LL_RCC_HSI48_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Disable(void)
{
  CLEAR_BIT(RCC->CRRCR, RCC_CRRCR_HSI48ON);
}
#endif /* RCC_CRRCR_HSI48ON */
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Check if HSI48 Ready
  * @rmtoll CRRCR           HSI48RDY        LL_RCC_HSI48_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsReady(void)
{
  return (READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48RDY) == (RCC_CRRCR_HSI48RDY));
}
#endif /* RCC_CRRCR_HSI48ON */
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll CRRCR        HSICAL        LL_RCC_HSI_GetCalibration
  * @retval Between Min_Data = 0x00 and Max_Data = 0xFF
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48CAL) >> RCC_CRRCR_HSI48CAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value that is added to the HSICAL
  * @note Default value is 16, which, when added to the HSICAL value,
  *       should trim the HSI to 16 MHz +/- 1 %
  * @rmtoll CRRCR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 31
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_SetCalibration(uint32_t Value)
{
  MODIFY_REG(RCC->CRRCR, RCC_CRRCR_HSI48CAL, Value << RCC_CRRCR_HSI48CAL_Pos);
}
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @brief  Configure PLLR used for SYSCLK Domain
  * @note PLL Source and PLLM Divider can be written only when PLL
  *        is disabled.
  * @note PLLN/PLLR can be written only when PLL is disabled.
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_SYS\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_SYS\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_SYS\n
  *         PLLCFGR      PLLR          LL_RCC_PLL_ConfigDomain_SYS
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  *
  * @param  PLLN Between 4 and 127
  * @param  PLLR This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLR_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_SYS(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLR)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLR,
             Source | PLLM | PLLN << RCC_PLLCFGR_PLLN_Pos | PLLR);
}

/**
  * @brief  Configure PLL used for Q domain clock
  * @note PLL Source and PLLM Divider can be written only when PLL.
  * @note PLLN/PLLQ can be written only when PLL is disabled.
  * @note This  can be selected for USB, RNG
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_PLLQ\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_PLLQ\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_PLLQ\n
  *         PLLCFGR      PLLQ          LL_RCC_PLL_ConfigDomain_PLLQ
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  *
  * @param  PLLN Between 4 and 127
  * @param  PLLQ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_PLLQ(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLQ)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLQ,
             Source | PLLM | (PLLN << RCC_PLLCFGR_PLLN_Pos) | PLLQ);
}

/**
  * @brief  Configure PLL used for P domain clock
  * @note PLL Source and PLLM Divider can be written only when PLL.
  * @note PLLN/PLLQ can be written only when PLL is disabled.
  * @note This  can be selected for ADC, TIM1 , TIM15
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_PLLP\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_PLLP\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_PLLP\n
  *         PLLCFGR      PLLP          LL_RCC_PLL_ConfigDomain_PLLP
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  *
  * @param  PLLN Between 4 and 127
  * @param  PLLP This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLP_DIV_2
  *         @arg @ref LL_RCC_PLLP_DIV_3
  *         @arg @ref LL_RCC_PLLP_DIV_4
  *         @arg @ref LL_RCC_PLLP_DIV_5
  *         @arg @ref LL_RCC_PLLP_DIV_6
  *         @arg @ref LL_RCC_PLLP_DIV_7
  *         @arg @ref LL_RCC_PLLP_DIV_8
  *         @arg @ref LL_RCC_PLLP_DIV_9
  *         @arg @ref LL_RCC_PLLP_DIV_10
  *         @arg @ref LL_RCC_PLLP_DIV_11
  *         @arg @ref LL_RCC_PLLP_DIV_12
  *         @arg @ref LL_RCC_PLLP_DIV_13
  *         @arg @ref LL_RCC_PLLP_DIV_14
  *         @arg @ref LL_RCC_PLLP_DIV_15
  *         @arg @ref LL_RCC_PLLP_DIV_16
  *         @arg @ref LL_RCC_PLLP_DIV_17
  *         @arg @ref LL_RCC_PLLP_DIV_18
  *         @arg @ref LL_RCC_PLLP_DIV_19
  *         @arg @ref LL_RCC_PLLP_DIV_20
  *         @arg @ref LL_RCC_PLLP_DIV_21
  *         @arg @ref LL_RCC_PLLP_DIV_22
  *         @arg @ref LL_RCC_PLLP_DIV_23
  *         @arg @ref LL_RCC_PLLP_DIV_24
  *         @arg @ref LL_RCC_PLLP_DIV_25
  *         @arg @ref LL_RCC_PLLP_DIV_26
  *         @arg @ref LL_RCC_PLLP_DIV_27
  *         @arg @ref LL_RCC_PLLP_DIV_28
  *         @arg @ref LL_RCC_PLLP_DIV_29
  *         @arg @ref LL_RCC_PLLP_DIV_30
  *         @arg @ref LL_RCC_PLLP_DIV_31
  *         @arg @ref LL_RCC_PLLP_DIV_32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_PLLP(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP,
             Source | PLLM | (PLLN << RCC_PLLCFGR_PLLN_Pos) | PLLP);
}

/**
  * @brief  Get Main PLL multiplication factor for VCO
  * @rmtoll PLLCFGR      PLLN          LL_RCC_PLL_GetN
  * @retval Between 4 and 127
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >>  RCC_PLLCFGR_PLLN_Pos);
}

/**
  * @brief  Get Main PLL division factor for PLLP
  * @rmtoll PLLCFGR      PLLPDIV       LL_RCC_PLL_GetP
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLP_DIV_2
  *         @arg @ref LL_RCC_PLLP_DIV_3
  *         @arg @ref LL_RCC_PLLP_DIV_4
  *         @arg @ref LL_RCC_PLLP_DIV_5
  *         @arg @ref LL_RCC_PLLP_DIV_6
  *         @arg @ref LL_RCC_PLLP_DIV_7
  *         @arg @ref LL_RCC_PLLP_DIV_8
  *         @arg @ref LL_RCC_PLLP_DIV_9
  *         @arg @ref LL_RCC_PLLP_DIV_10
  *         @arg @ref LL_RCC_PLLP_DIV_11
  *         @arg @ref LL_RCC_PLLP_DIV_12
  *         @arg @ref LL_RCC_PLLP_DIV_13
  *         @arg @ref LL_RCC_PLLP_DIV_14
  *         @arg @ref LL_RCC_PLLP_DIV_15
  *         @arg @ref LL_RCC_PLLP_DIV_16
  *         @arg @ref LL_RCC_PLLP_DIV_17
  *         @arg @ref LL_RCC_PLLP_DIV_18
  *         @arg @ref LL_RCC_PLLP_DIV_19
  *         @arg @ref LL_RCC_PLLP_DIV_20
  *         @arg @ref LL_RCC_PLLP_DIV_21
  *         @arg @ref LL_RCC_PLLP_DIV_22
  *         @arg @ref LL_RCC_PLLP_DIV_23
  *         @arg @ref LL_RCC_PLLP_DIV_24
  *         @arg @ref LL_RCC_PLLP_DIV_25
  *         @arg @ref LL_RCC_PLLP_DIV_26
  *         @arg @ref LL_RCC_PLLP_DIV_27
  *         @arg @ref LL_RCC_PLLP_DIV_28
  *         @arg @ref LL_RCC_PLLP_DIV_29
  *         @arg @ref LL_RCC_PLLP_DIV_30
  *         @arg @ref LL_RCC_PLLP_DIV_31
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetP(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP));
}

/**
  * @brief  Get Main PLL division factor for PLLQ
  * @note Used for PLL48M1CLK selected for USB, RNG, SDMMC (48 MHz clock)
  * @rmtoll PLLCFGR      PLLQ          LL_RCC_PLL_GetQ
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetQ(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ));
}

/**
  * @brief  Get Main PLL division factor for PLLR
  * @note Used for PLLCLK (system clock)
  * @rmtoll PLLCFGR      PLLR          LL_RCC_PLL_GetR
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLR_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetR(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLR));
}

/**
  * @brief  Get the oscillator used as PLL clock source.
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_GetMainSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetMainSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC));
}

/**
  * @brief  Get Division factor for the main PLL and other PLL
  * @rmtoll PLLCFGR      PLLM          LL_RCC_PLL_GetM
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  *
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetM(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM));
}

/**
  * @brief  Enable PLL output mapped on P domain clock
  * @rmtoll PLLCFGR      PLLPEN        LL_RCC_PLL_EnableDomain_PLLP
  * @note   User shall check that PLL enable is not done through
  *         other functions (ex: I2S1)
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_PLLP(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN);
}

/**
  * @brief  Disable PLL output mapped on P domain clock
  * @note Cannot be disabled if the PLL clock is used as the system clock
  * @note   User shall check that PLL is not used by any other peripheral
  *         (ex: I2S1)
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used,  should be 0
  * @rmtoll PLLCFGR      PLLPEN        LL_RCC_PLL_DisableDomain_PLLP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_PLLP(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN);
}

/**
  * @brief  Check if PLL output mapped on P domain clock is enabled
  * @rmtoll PLLCFGR      PLLPEN        LL_RCC_PLL_IsEnabledDomain_PLLP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_IsEnabledDomain_PLLP(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN) == (RCC_PLLCFGR_PLLPEN)) ? 1UL : 0UL);
}
/**
  * @brief  Enable PLL output mapped on 48MHz domain clock
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_EnableDomain_PLLQ
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_PLLQ(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
}

/**
  * @brief  Disable PLL output mapped on 48MHz domain clock
  * @note Cannot be disabled if the PLL clock is used as the system
  *       clock
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used,  should be 0
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_DisableDomain_PLLQ
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_PLLQ(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
}

/**
  * @brief  Check if PLL output mapped on Q domain clock is enabled
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_IsEnabledDomain_PLLQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_IsEnabledDomain_PLLQ(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN) == (RCC_PLLCFGR_PLLQEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL output mapped on SYSCLK domain
  * @rmtoll PLLCFGR      PLLREN        LL_RCC_PLL_EnableDomain_SYS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_SYS(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN);
}

/**
  * @brief  Disable PLL output mapped on SYSCLK domain
  * @note Cannot be disabled if the PLL clock is used as the system
  *       clock
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used, Main PLL  should be 0
  * @rmtoll PLLCFGR      PLLREN        LL_RCC_PLL_DisableDomain_SYS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_SYS(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN);
}

/**
  * @brief  Check if PLL output mapped on tR(SYS) domain clock is enabled
  * @rmtoll PLLCFGR      PLLREN        LL_RCC_PLL_IsEnabledDomain_SYS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_IsEnabledDomain_SYS(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN) == (RCC_PLLCFGR_PLLREN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear LSI ready interrupt flag
  * @rmtoll CICR         LSIRDYC       LL_RCC_ClearFlag_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC);
}

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
  * @brief  Clear MSI ready interrupt flag
  * @rmtoll CICR         MSIRDYC       LL_RCC_ClearFlag_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIRDYC);
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
  * @brief  Clear PLL ready interrupt flag
  * @rmtoll CICR         PLLRDYC       LL_RCC_ClearFlag_PLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLLRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLLRDYC);
}

/**
  * @brief  Clear Clock security system interrupt flag
  * @rmtoll CICR         CSSC          LL_RCC_ClearFlag_HSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_CSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_CSSC);
}

/**
  * @brief  Clear LSE Clock security system interrupt flag
  * @rmtoll CICR         LSECSSC       LL_RCC_ClearFlag_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSECSSC);
}
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Clear LSE Clock security system interrupt flag
  * @rmtoll CICR         HSI48RDYC       LL_RCC_ClearFlag_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSI48RDYC);
}
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll CIFR         LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == (RCC_CIFR_LSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll CIFR         LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == (RCC_CIFR_LSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI ready interrupt occurred or not
  * @rmtoll CIFR         MSIRDYF       LL_RCC_IsActiveFlag_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIRDYF) == (RCC_CIFR_MSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll CIFR         HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == (RCC_CIFR_HSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == (RCC_CIFR_HSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL ready interrupt occurred or not
  * @rmtoll CIFR         PLLRDYF       LL_RCC_IsActiveFlag_PLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLLRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLLRDYF) == (RCC_CIFR_PLLRDYF)) ? 1UL : 0UL);
}
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Check if HSI48 ready interrupt occurred or not
  * @rmtoll CIR          HSI48RDYF     LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSI48RDYF) == (RCC_CIFR_HSI48RDYF)) ? 1UL : 0UL);
}
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll CIFR         CSSF          LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == (RCC_CIFR_LSECSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE Clock security system interrupt occurred or not
  * @rmtoll CIFR         LSECSSF       LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_CSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_CSSF) == (RCC_CIFR_CSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Watchdog reset is set or not.
  * @rmtoll CSR          IWDGRSTF      LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF) == (RCC_CSR_IWDGRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll CSR          LPWRRSTF      LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LPWRRSTF) == (RCC_CSR_LPWRRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag is set or not.
  * @rmtoll CSR          OBLRSTF       LL_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_OBLRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_OBLRSTF) == (RCC_CSR_OBLRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll CSR          PINRSTF       LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_PINRSTF) == (RCC_CSR_PINRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll CSR          SFTRSTF       LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_SFTRSTF) == (RCC_CSR_SFTRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll CSR          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_WWDGRSTF) == (RCC_CSR_WWDGRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag PWR reset is set or not.
  * @rmtoll CSR          PWRRSTF       LL_RCC_IsActiveFlag_PWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PWRRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_PWRRSTF) == (RCC_CSR_PWRRSTF)) ? 1UL : 0UL);
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

/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_EnableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

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
  * @brief  Enable MSI ready interrupt
  * @rmtoll CIER         MSIRDYIE      LL_RCC_EnableIT_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIRDYIE);
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
  * @brief  Enable PLL ready interrupt
  * @rmtoll CIER         PLLRDYIE      LL_RCC_EnableIT_PLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLLRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLLRDYIE);
}
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Enable HSI48 ready interrupt
  * @rmtoll CIER          HSI48RDYIE    LL_RCC_EnableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @brief  Enable LSE clock security system interrupt
  * @rmtoll CIER         LSECSSIE      LL_RCC_EnableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSECSS(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_DisableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

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
  * @brief  Disable MSI ready interrupt
  * @rmtoll CIER         MSIRDYIE      LL_RCC_DisableIT_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIRDYIE);
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
  * @brief  Disable PLL ready interrupt
  * @rmtoll CIER         PLLRDYIE      LL_RCC_DisableIT_PLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLLRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLLRDYIE);
}
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Disable HSI48 ready interrupt
  * @rmtoll CIER          HSI48RDYIE    LL_RCC_DisableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @brief  Disable LSE clock security system interrupt
  * @rmtoll CIER         LSECSSIE      LL_RCC_DisableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSIRDYIE      LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == (RCC_CIER_LSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSERDYIE      LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == (RCC_CIER_LSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if MSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIRDYIE      LL_RCC_IsEnabledIT_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIRDYIE) == (RCC_CIER_MSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSIRDYIE      LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == (RCC_CIER_HSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == (RCC_CIER_HSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL ready interrupt source is enabled or disabled.
  * @rmtoll CIER         PLLRDYIE      LL_RCC_IsEnabledIT_PLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLLRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLLRDYIE) == (RCC_CIER_PLLRDYIE)) ? 1UL : 0UL);
}
#if defined(RCC_CRRCR_HSI48ON)
/**
  * @brief  Checks if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll CIER          HSI48RDYIE    LL_RCC_IsEnabledIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE) == (RCC_CIER_HSI48RDYIE)) ? 1UL : 0UL);
}
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @brief  Checks if LSECSS interrupt source is enabled or disabled.
  * @rmtoll CIER         LSECSSIE      LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSECSS(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSECSSIE) == (RCC_CIER_LSECSSIE)) ? 1UL : 0UL);
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
uint32_t    LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource);
uint32_t    LL_RCC_GetI2CClockFreq(uint32_t I2CxSource);
uint32_t    LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource);
uint32_t    LL_RCC_GetTIMClockFreq(uint32_t TIMxSource);
uint32_t    LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource);
uint32_t    LL_RCC_GetRNGClockFreq(uint32_t RNGxSource);
#if defined (USB_DRD_FS)
uint32_t    LL_RCC_GetUSBClockFreq(uint32_t USBxSource);
#endif /* USB_DRD_FS */
uint32_t    LL_RCC_GetRTCClockFreq(void);
uint32_t    LL_RCC_GetADCClockFreq(uint32_t ADCxSource);
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

#endif /* RCC */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32U0xx_LL_RCC_H */
