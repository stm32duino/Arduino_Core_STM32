/**
  ******************************************************************************
  * @file    stm32c0xx_ll_rcc.h
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
#ifndef STM32C0xx_LL_RCC_H
#define STM32C0xx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx.h"

/** @addtogroup STM32C0xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Variables RCC Private Variables
  * @{
  */
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
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
#define HSE_VALUE    48000000U   /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    48000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */
#if !defined  (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE    48000000U /*!< Value of the I2S_CKIN external oscillator in Hz */
#endif /* EXTERNAL_CLOCK_VALUE */

#if defined(RCC_HSI48_SUPPORT)
#if !defined  (HSI48_VALUE)
#define HSI48_VALUE  48000000U  /*!< Value of the HSI48 oscillator in Hz */
#endif /* HSI48_VALUE */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_WriteReg function
  * @{
  */
#define LL_RCC_CICR_LSIRDYC                RCC_CICR_LSIRDYC     /*!< LSI Ready Interrupt Clear */
#define LL_RCC_CICR_LSERDYC                RCC_CICR_LSERDYC     /*!< LSE Ready Interrupt Clear */
#define LL_RCC_CICR_HSIRDYC                RCC_CICR_HSIRDYC     /*!< HSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSERDYC                RCC_CICR_HSERDYC     /*!< HSE Ready Interrupt Clear */
#define LL_RCC_CICR_LSECSSC                RCC_CICR_LSECSSC     /*!< LSE Clock Security System Interrupt Clear */
#define LL_RCC_CICR_CSSC                   RCC_CICR_CSSC        /*!< Clock Security System Interrupt Clear */
#if defined(RCC_HSI48_SUPPORT)
#define LL_RCC_CICR_HSI48CSSC              RCC_CICR_HSIUSB48RDYC  /*!< HSI48 Ready Interrupt Clear */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg function
  * @{
  */
#define LL_RCC_CIFR_LSIRDYF                RCC_CIFR_LSIRDYF     /*!< LSI Ready Interrupt flag */
#define LL_RCC_CIFR_LSERDYF                RCC_CIFR_LSERDYF     /*!< LSE Ready Interrupt flag */
#define LL_RCC_CIFR_HSIRDYF                RCC_CIFR_HSIRDYF     /*!< HSI Ready Interrupt flag */
#define LL_RCC_CIFR_HSERDYF                RCC_CIFR_HSERDYF     /*!< HSE Ready Interrupt flag */
#define LL_RCC_CIFR_LSECSSF                RCC_CIFR_LSECSSF     /*!< LSE Clock Security System Interrupt flag */
#define LL_RCC_CIFR_CSSF                   RCC_CIFR_CSSF        /*!< Clock Security System Interrupt flag */
#if defined(RCC_HSI48_SUPPORT)
#define LL_RCC_CIFR_HSI48RDYF              RCC_CIFR_HSIUSB48RDYF  /*!< HSI48 Ready Interrupt flag */
#endif /* RCC_HSI48_SUPPORT */
#define LL_RCC_CSR_LPWRRSTF                RCC_CSR2_LPWRRSTF    /*!< Low-Power reset flag */
#define LL_RCC_CSR_OBLRSTF                 RCC_CSR2_OBLRSTF     /*!< OBL reset flag */
#define LL_RCC_CSR_PINRSTF                 RCC_CSR2_PINRSTF     /*!< PIN reset flag */
#define LL_RCC_CSR_SFTRSTF                 RCC_CSR2_SFTRSTF     /*!< Software Reset flag */
#define LL_RCC_CSR_IWDGRSTF                RCC_CSR2_IWDGRSTF    /*!< Independent Watchdog reset flag */
#define LL_RCC_CSR_WWDGRSTF                RCC_CSR2_WWDGRSTF    /*!< Window watchdog reset flag */
#define LL_RCC_CSR_PWRRSTF                 RCC_CSR2_PWRRSTF     /*!< BOR or POR/PDR reset flag */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIER_LSIRDYIE               RCC_CIER_LSIRDYIE      /*!< LSI Ready Interrupt Enable */
#define LL_RCC_CIER_LSERDYIE               RCC_CIER_LSERDYIE      /*!< LSE Ready Interrupt Enable */
#define LL_RCC_CIER_HSIRDYIE               RCC_CIER_HSIRDYIE      /*!< HSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSERDYIE               RCC_CIER_HSERDYIE      /*!< HSE Ready Interrupt Enable */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0x00000000U             /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_CSR1_LSEDRV_0       /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_CSR1_LSEDRV_1       /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_CSR1_LSEDRV         /*!< Xtal mode higher driving capability */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI          0x00000000U                 /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE          RCC_CSR1_LSCOSEL            /*!< LSE selection for low speed clock  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_HSI           0x00000000U                        /*!< HSI selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSE           RCC_CFGR_SW_0                      /*!< HSE selection as system clock */
#if defined(RCC_HSI48_SUPPORT)
#define LL_RCC_SYS_CLKSOURCE_HSIUSB48      RCC_CFGR_SW_1                      /*!< HSIUSB48 selection used as system clock */
#endif /* RCC_HSI48_SUPPORT */
#define LL_RCC_SYS_CLKSOURCE_LSI           (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)    /*!< LSI selection used as system clock */
#define LL_RCC_SYS_CLKSOURCE_LSE           RCC_CFGR_SW_2                      /*!< LSE selection used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI           0x00000000U                         /*!< HSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE           RCC_CFGR_SWS_0                      /*!< HSE used as system clock */
#if defined(RCC_HSI48_SUPPORT)
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSIUSB48      RCC_CFGR_SWS_1                      /*!< HSIUSB48 used as system clock */
#endif /* RCC_HSI48_SUPPORT */
#define LL_RCC_SYS_CLKSOURCE_STATUS_LSI           (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0)   /*!< LSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_LSE           RCC_CFGR_SWS_2                      /*!< LSE used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#if defined(RCC_CR_SYSDIV)
#define LL_RCC_SYSCLK_DIV_1            0x00000000U                                 /*!< SYSCLK not divided */
#define LL_RCC_SYSCLK_DIV_2            RCC_CR_SYSDIV_0                             /*!< SYSCLK divided by 2 */
#define LL_RCC_SYSCLK_DIV_3            RCC_CR_SYSDIV_1                             /*!< SYSCLK divided by 3 */
#define LL_RCC_SYSCLK_DIV_4            (RCC_CR_SYSDIV_1 | RCC_CR_SYSDIV_0)         /*!< SYSCLK divided by 4 */
#define LL_RCC_SYSCLK_DIV_5            RCC_CR_SYSDIV_2                             /*!< SYSCLK divided by 5 */
#define LL_RCC_SYSCLK_DIV_6            (RCC_CR_SYSDIV_2 | RCC_CR_SYSDIV_0)         /*!< SYSCLK divided by 6 */
#define LL_RCC_SYSCLK_DIV_7            (RCC_CR_SYSDIV_2 | RCC_CR_SYSDIV_1)         /*!< SYSCLK divided by 7 */
#define LL_RCC_SYSCLK_DIV_8            (RCC_CR_SYSDIV_2 | RCC_CR_SYSDIV_1 | RCC_CR_SYSDIV_0) /*!< SYSCLK divided by 8 */
#else
#define LL_RCC_SYSCLK_DIV_1            0x00000000U                                           /*!< SYSCLK not divided */
#endif /* RCC_CR_SYSDIV */
/**
  * @}
  */

/** @defgroup RCC_HCLK_Clock_Source  RCC HCLK Clock Source
  * @{
  */
#define LL_RCC_HCLK_DIV_1                  0x00000000U                                                             /*!< HCLK not divided */
#define LL_RCC_HCLK_DIV_2                  RCC_CFGR_HPRE_3                                                         /*!< HCLK divided by 2 */
#define LL_RCC_HCLK_DIV_4                  (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0)                                     /*!< HCLK divided by 4 */
#define LL_RCC_HCLK_DIV_8                  (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1)                                     /*!< HCLK divided by 8 */
#define LL_RCC_HCLK_DIV_16                 (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)                   /*!< HCLK divided by 16 */
#define LL_RCC_HCLK_DIV_64                 (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2)                                     /*!< HCLK divided by 64 */
#define LL_RCC_HCLK_DIV_128                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0)                   /*!< HCLK divided by 128 */
#define LL_RCC_HCLK_DIV_256                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1)                   /*!< HCLK divided by 256 */
#define LL_RCC_HCLK_DIV_512                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0) /*!< HCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_DIV_1              0x00000000U                                           /*!< HCLK not divided */
#define LL_RCC_APB1_DIV_2              RCC_CFGR_PPRE_2                                       /*!< HCLK divided by 2 */
#define LL_RCC_APB1_DIV_4              (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_0)                   /*!< HCLK divided by 4 */
#define LL_RCC_APB1_DIV_8              (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1)                   /*!< HCLK divided by 8 */
#define LL_RCC_APB1_DIV_16             (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSI_DIV  HSI division factor
  * @{
  */
#define LL_RCC_HSI_DIV_1                  0x00000000U                                /*!< HSI not divided */
#define LL_RCC_HSI_DIV_2                  RCC_CR_HSIDIV_0                            /*!< HSI divided by 2 */
#define LL_RCC_HSI_DIV_4                  RCC_CR_HSIDIV_1                            /*!< HSI divided by 4 */
#define LL_RCC_HSI_DIV_8                  (RCC_CR_HSIDIV_1 | RCC_CR_HSIDIV_0)        /*!< HSI divided by 8 */
#define LL_RCC_HSI_DIV_16                 RCC_CR_HSIDIV_2                            /*!< HSI divided by 16 */
#define LL_RCC_HSI_DIV_32                 (RCC_CR_HSIDIV_2 | RCC_CR_HSIDIV_0)        /*!< HSI divided by 32 */
#define LL_RCC_HSI_DIV_64                 (RCC_CR_HSIDIV_2 | RCC_CR_HSIDIV_1)        /*!< HSI divided by 64 */
#define LL_RCC_HSI_DIV_128                RCC_CR_HSIDIV                              /*!< HSI divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSIKER_DIV  HSI Kernel division factor
  * @{
  */
#define LL_RCC_HSIKER_DIV_1                  0x00000000U                                /*!< HSI kernel not divided */
#define LL_RCC_HSIKER_DIV_2                  RCC_CR_HSIKERDIV_0                         /*!< HSI kernel divided by 2 */
#define LL_RCC_HSIKER_DIV_3                  RCC_CR_HSIKERDIV_1                         /*!< HSI kernel divided by 3 */
#define LL_RCC_HSIKER_DIV_4                  (RCC_CR_HSIKERDIV_1 | RCC_CR_HSIKERDIV_0)  /*!< HSI kernel divided by 4 */
#define LL_RCC_HSIKER_DIV_5                  RCC_CR_HSIKERDIV_2                         /*!< HSI kernel divided by 5 */
#define LL_RCC_HSIKER_DIV_6                  (RCC_CR_HSIKERDIV_2 | RCC_CR_HSIKERDIV_0)  /*!< HSI kernel divided by 6 */
#define LL_RCC_HSIKER_DIV_7                  (RCC_CR_HSIKERDIV_2 | RCC_CR_HSIKERDIV_1)  /*!< HSI kernel divided by 7 */
#define LL_RCC_HSIKER_DIV_8                  RCC_CR_HSIKERDIV                           /*!< HSI kernel divided by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK          0x00000000U                            /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCO1SOURCE_SYSCLK           RCC_CFGR_MCOSEL_0                      /*!< SYSCLK selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSI              (RCC_CFGR_MCOSEL_0| RCC_CFGR_MCOSEL_1) /*!< HSI16 selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSE              RCC_CFGR_MCOSEL_2                      /*!< HSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSI              (RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2)  /*!< LSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSE              (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2) /*!< LSE selection as MCO1 source */
#if defined(RCC_HSI48_SUPPORT)
#define LL_RCC_MCO1SOURCE_HSIUSB48         RCC_CFGR_MCOSEL_3                      /*!< HSIUSB48 selection as MCO1 source */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1_DIV_1        0x00000000U                                                 /*!< MCO1 not divided */
#define LL_RCC_MCO1_DIV_2        RCC_CFGR_MCOPRE_0                                           /*!< MCO1 divided by 2 */
#define LL_RCC_MCO1_DIV_4        RCC_CFGR_MCOPRE_1                                           /*!< MCO1 divided by 4 */
#define LL_RCC_MCO1_DIV_8        (RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0)                     /*!< MCO1 divided by 8 */
#define LL_RCC_MCO1_DIV_16       RCC_CFGR_MCOPRE_2                                           /*!< MCO1 divided by 16 */
#define LL_RCC_MCO1_DIV_32       (RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_0)                     /*!< MCO1 divided by 32 */
#define LL_RCC_MCO1_DIV_64       (RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_1)                     /*!< MCO1 divided by 64 */
#define LL_RCC_MCO1_DIV_128      (RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0) /*!< MCO1 divided by 128 */
#if defined(RCC_CFGR_MCOPRE_3)
#define LL_RCC_MCO1_DIV_256      RCC_CFGR_MCOPRE_3                                           /*!< MCO1 divided by 256 */
#define LL_RCC_MCO1_DIV_512      (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_0)                     /*!< MCO1 divided by 512 */
#define LL_RCC_MCO1_DIV_1024     (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_1)                    /*!< MCO1 divided by 1024 */
#endif /* RCC_CFGR_MCOPRE_3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2SOURCE  MCO2 SOURCE selection
  * @{
  */
#define LL_RCC_MCO2SOURCE_NOCLOCK          0x00000000U                               /*!< MCO2 output disabled, no clock on MCO2 */
#define LL_RCC_MCO2SOURCE_SYSCLK           RCC_CFGR_MCO2SEL_0                        /*!< SYSCLK selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSI              (RCC_CFGR_MCO2SEL_0| RCC_CFGR_MCO2SEL_1)  /*!< HSI16 selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSE              RCC_CFGR_MCO2SEL_2                        /*!< HSE selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_LSI              (RCC_CFGR_MCO2SEL_1|RCC_CFGR_MCO2SEL_2)   /*!< LSI selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_LSE              (RCC_CFGR_MCO2SEL_0|RCC_CFGR_MCO2SEL_1|RCC_CFGR_MCO2SEL_2) /*!< LSE selection as MCO2 source */
#if defined(RCC_HSI48_SUPPORT)
#define LL_RCC_MCO2SOURCE_HSIUSB48         RCC_CFGR_MCO2SEL_3                      /*!< HSIUSB48 selection as MCO2 source */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2_DIV  MCO2 prescaler
  * @{
  */
#define LL_RCC_MCO2_DIV_1      0x00000000U                                                    /*!< MCO2 not divided */
#define LL_RCC_MCO2_DIV_2      RCC_CFGR_MCO2PRE_0                                             /*!< MCO2 divided by 2 */
#define LL_RCC_MCO2_DIV_4      RCC_CFGR_MCO2PRE_1                                             /*!< MCO2 divided by 4 */
#define LL_RCC_MCO2_DIV_8      (RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO2 divided by 8 */
#define LL_RCC_MCO2_DIV_16     RCC_CFGR_MCO2PRE_2                                             /*!< MCO2 divided by 16 */
#define LL_RCC_MCO2_DIV_32     (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO2 divided by 32 */
#define LL_RCC_MCO2_DIV_64     (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1)                      /*!< MCO2 divided by 64 */
#define LL_RCC_MCO2_DIV_128    (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0) /*!< MCO2 divided by 128 */
#if defined(RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_256    RCC_CFGR_MCO2PRE_3                                            /*!< MCO1 divided by 256 */
#define LL_RCC_MCO2_DIV_512    (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_0)                     /*!< MCO1 divided by 512 */
#define LL_RCC_MCO2_DIV_1024   (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_1)                     /*!< MCO1 divided by 1024 */
#endif /* RCC_CFGR_MCO2PRE_3 */
/**
  * @}
  */
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO        0x00000000U           /*!< No clock enabled for the peripheral            */
#define LL_RCC_PERIPH_FREQUENCY_NA        0xFFFFFFFFU           /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup RCC_LL_EC_USARTx_CLKSOURCE  Peripheral USART clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK1      ((RCC_CCIPR_USART1SEL << 16U) | 0x00000000U)            /*!< PCLK1 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_SYSCLK     ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL_0)  /*!< SYSCLK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSIKER     ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL_1)  /*!< HSIKER clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_LSE        ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL)    /*!< LSE clock used as USART1 clock source */

/**
  * @}
  */


/** @defgroup RCC_LL_EC_I2Cx_CLKSOURCE Peripheral I2C clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1        0x00000000U                  /*!< PCLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0          /*!< SYSCLK clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_HSIKER       RCC_CCIPR_I2C1SEL_1          /*!< HSIKER clock used as I2C1 clock source */
#if defined(I2C2)
#define LL_RCC_I2C2_CLKSOURCE_PCLK1        0x00000000U                  /*!< PCLK1 clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0          /*!< SYSCLK clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_HSIKER       RCC_CCIPR_I2C1SEL_1          /*!< HSIKER clock used as I2C2 clock source */
#endif /* I2C2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2S1_CLKSOURCE Peripheral I2S clock source selection
  * @{
  */
#define LL_RCC_I2S1_CLKSOURCE_SYSCLK      0x00000000U                  /*!< SYSCLK clock used as I2S1 clock source */
#define LL_RCC_I2S1_CLKSOURCE_HSIKER      RCC_CCIPR_I2S1SEL_1          /*!< HSIKER clock used as I2S1 clock source */
#define LL_RCC_I2S1_CLKSOURCE_PIN         RCC_CCIPR_I2S1SEL            /*!< External clock used as I2S1 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_CLKSOURCE Peripheral ADC clock source selection
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_SYSCLK        0x00000000U                   /*!< SYSCLK used as ADC clock */
#define LL_RCC_ADC_CLKSOURCE_HSIKER        RCC_CCIPR_ADCSEL_1            /*!< HSIKER kernel used as ADC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USARTx Peripheral USARTx get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE            RCC_CCIPR_USART1SEL /*!< USART1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C1 Peripheral I2C get clock source
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE              RCC_CCIPR_I2C1SEL /*!< I2C1 Clock source selection */
#if defined(I2C2)
#define LL_RCC_I2C2_CLKSOURCE              RCC_CCIPR_I2C1SEL /*!< I2C2 Clock source selection */
#endif /* I2C2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2S1 Peripheral I2S get clock source
  * @{
  */
#define LL_RCC_I2S1_CLKSOURCE              RCC_CCIPR_I2S1SEL /*!< I2S1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC Peripheral ADC get clock source
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE               RCC_CCIPR_ADCSEL        /*!< ADC Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE          0x00000000U             /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE           RCC_CSR1_RTCSEL_0       /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI           RCC_CSR1_RTCSEL_1       /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV32     RCC_CSR1_RTCSEL         /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */
#if defined(USB_DRD_FS)
/** @defgroup RCC_LL_EC_USB_CLKSOURCE  Peripheral USB clock source selection
  * @{
  */
#define LL_RCC_USB_CLKSOURCE_HSI48         0x00000000U        /*!< HSI48 clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_HSE           RCC_CCIPR2_USBSEL  /*!< HSE clock used as USB clock source */
/** @defgroup RCC_LL_EC_USB  Peripheral USB get clock source
  * @{
  */
#define LL_RCC_USB_CLKSOURCE               RCC_CCIPR2_USBSEL /*!< USB Clock source selection */
/**
  * @}
  */

/**
  * @}
  */
#endif /* USB_DRD_FS */

#if defined(FDCAN1)
/** @defgroup RCC_LL_EC_FDCAN1_CLKSOURCE  Peripheral FDCAN1 clock source selection
  * @{
  */
#define LL_RCC_FDCAN1_CLKSOURCE_PCLK1         0x00000000U            /*!< PCLK1 clock used as FDCAN1 clock source */
#define LL_RCC_FDCAN1_CLKSOURCE_HSIKER        RCC_CCIPR_FDCAN1SEL_0  /*!< HSIKER clock used as FDCAN1 clock source */
#define LL_RCC_FDCAN1_CLKSOURCE_HSE           RCC_CCIPR_FDCAN1SEL_1  /*!< HSE clock used as FDCAN1 clock source */
/** @defgroup RCC_LL_EC_FDCAN1  Peripheral FDCAN1 get clock source
  * @{
  */
#define LL_RCC_FDCAN1_CLKSOURCE               RCC_CCIPR_FDCAN1SEL /*!< FDCAN1 Clock source selection */
/**
  * @}
  */

/**
  * @}
  */
#endif /* FDCAN1 */
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
#define LL_RCC_WriteReg(__REG__, __VALUE__) WRITE_REG((RCC->__REG__), (__VALUE__))

/**
  * @brief  Read a value in RCC register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RCC_ReadReg(__REG__) READ_REG(RCC->__REG__)
/**
  * @}
  */

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on HSE/HSI/LSE/LSI)
  * @param  __AHBPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_DIV_1
  *         @arg @ref LL_RCC_HCLK_DIV_2
  *         @arg @ref LL_RCC_HCLK_DIV_4
  *         @arg @ref LL_RCC_HCLK_DIV_8
  *         @arg @ref LL_RCC_HCLK_DIV_16
  *         @arg @ref LL_RCC_HCLK_DIV_64
  *         @arg @ref LL_RCC_HCLK_DIV_128
  *         @arg @ref LL_RCC_HCLK_DIV_256
  *         @arg @ref LL_RCC_HCLK_DIV_512
  * @retval HCLK clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK_FREQ(__SYSCLKFREQ__,__AHBPRESCALER__) \
  ((__SYSCLKFREQ__) >> (AHBPrescTable[((__AHBPRESCALER__)\
                                       & RCC_CFGR_HPRE) >>  RCC_CFGR_HPRE_Pos] & 0x1FU))

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (APB1)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB1PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APB1PRESCALER__) \
  ((__HCLKFREQ__) >> (APBPrescTable[(__APB1PRESCALER__) >>  RCC_CFGR_PPRE_Pos]\
                      & 0x1FU))

/**
  * @brief  Helper macro to calculate the HSISYS frequency
  * @param  __HSIDIV__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  *         @arg @ref LL_RCC_HSI_DIV_16
  *         @arg @ref LL_RCC_HSI_DIV_32
  *         @arg @ref LL_RCC_HSI_DIV_64
  *         @arg @ref LL_RCC_HSI_DIV_128
  * @retval HSISYS clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HSI_FREQ(__HSIDIV__) (HSI_VALUE / (1U << ((__HSIDIV__)>> RCC_CR_HSIDIV_Pos)))

/**
  * @brief  Helper macro to calculate the HSI Kernel frequency
  * @param  __HSIKERDIV__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSIKER_DIV_1
  *         @arg @ref LL_RCC_HSIKER_DIV_2
  *         @arg @ref LL_RCC_HSIKER_DIV_3
  *         @arg @ref LL_RCC_HSIKER_DIV_4
  *         @arg @ref LL_RCC_HSIKER_DIV_5
  *         @arg @ref LL_RCC_HSIKER_DIV_6
  *         @arg @ref LL_RCC_HSIKER_DIV_7
  *         @arg @ref LL_RCC_HSIKER_DIV_8
  * @retval HSIKER clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HSIKER_FREQ(__HSIKERDIV__) (HSI_VALUE / (((__HSIKERDIV__)>> RCC_CR_HSIKERDIV_Pos) +1U))
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
  * @rmtoll CR           CSSON         LL_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_CSSON);
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
  return ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY)) ? 1UL : 0UL);
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
  * @brief  Check if HSI in stop mode is enabled
  * @rmtoll CR           HSIKERON        LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIKERON) == (RCC_CR_HSIKERON)) ? 1UL : 0UL);
}

/**
  * @brief  Set HSIKER divider
  * @rmtoll CR           HSIKERDIV        LL_RCC_HSIKER_SetDivider
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSIKER_DIV_1
  *         @arg @ref LL_RCC_HSIKER_DIV_2
  *         @arg @ref LL_RCC_HSIKER_DIV_3
  *         @arg @ref LL_RCC_HSIKER_DIV_4
  *         @arg @ref LL_RCC_HSIKER_DIV_5
  *         @arg @ref LL_RCC_HSIKER_DIV_6
  *         @arg @ref LL_RCC_HSIKER_DIV_7
  *         @arg @ref LL_RCC_HSIKER_DIV_8
  * @retval None.
  */
__STATIC_INLINE void LL_RCC_HSIKER_SetDivider(uint32_t Divider)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSIKERDIV, Divider);
}

/**
  * @brief  Get HSIKER divider
  * @rmtoll CR           HSIKERDIV        LL_RCC_HSIKER_GetDivider
  * @retval can be one of the following values:
  *         @arg @ref LL_RCC_HSIKER_DIV_1
  *         @arg @ref LL_RCC_HSIKER_DIV_2
  *         @arg @ref LL_RCC_HSIKER_DIV_3
  *         @arg @ref LL_RCC_HSIKER_DIV_4
  *         @arg @ref LL_RCC_HSIKER_DIV_5
  *         @arg @ref LL_RCC_HSIKER_DIV_6
  *         @arg @ref LL_RCC_HSIKER_DIV_7
  *         @arg @ref LL_RCC_HSIKER_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_HSIKER_GetDivider(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSIKERDIV));
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
  * @brief  Set HSI divider
  * @rmtoll CR           HSIDIV        LL_RCC_HSI_SetDivider
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  *         @arg @ref LL_RCC_HSI_DIV_16
  *         @arg @ref LL_RCC_HSI_DIV_32
  *         @arg @ref LL_RCC_HSI_DIV_64
  *         @arg @ref LL_RCC_HSI_DIV_128
  * @retval None.
  */
__STATIC_INLINE void LL_RCC_HSI_SetDivider(uint32_t Divider)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSIDIV, Divider);
}

/**
  * @brief  Get HSI divider
  * @rmtoll CR           HSIDIV        LL_RCC_HSI_GetDivider
  * @retval can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  *         @arg @ref LL_RCC_HSI_DIV_16
  *         @arg @ref LL_RCC_HSI_DIV_32
  *         @arg @ref LL_RCC_HSI_DIV_64
  *         @arg @ref LL_RCC_HSI_DIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetDivider(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSIDIV));
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
  return ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)) ? 1UL : 0UL);
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
  * @note Default value is 64, which, when added to the HSICAL value,
  *       should trim the HSI to 16 MHz +/- 1 %
  * @rmtoll ICSCR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 127
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, Value << RCC_ICSCR_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll ICSCR        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_HSITRIM) >> RCC_ICSCR_HSITRIM_Pos);
}

/**
  * @}
  */

#if defined(RCC_HSI48_SUPPORT)
/** @defgroup RCC_LL_EF_HSI48 HSI48
  * @{
  */

/**
  * @brief  Enable HSI48
  * @rmtoll CR         HSI48ON       LL_RCC_HSI48_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIUSB48ON);
}

/**
  * @brief  Disable HSI48
  * @rmtoll CR          HSI48ON       LL_RCC_HSI48_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIUSB48ON);
}

/**
  * @brief  Check if HSI48 oscillator Ready
  * @rmtoll CR          HSI48RDY      LL_RCC_HSI48_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIUSB48RDY) == RCC_CR_HSIUSB48RDY) ? 1UL : 0UL);
}

/**
  * @}
  */
#endif /* RCC_HSI48_SUPPORT */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll CSR1         LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->CSR1, RCC_CSR1_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll CSR1         LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSEON);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll CSR1         LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->CSR1, RCC_CSR1_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll CSR1         LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSEBYP);
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll CSR1         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t LSEDrive)
{
  MODIFY_REG(RCC->CSR1, RCC_CSR1_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll CSR1         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR1, RCC_CSR1_LSEDRV));
}

/**
  * @brief  Enable Clock security system on LSE.
  * @rmtoll CSR1         LSECSSON      LL_RCC_LSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->CSR1, RCC_CSR1_LSECSSON);
}

/**
  * @brief  Disable Clock security system on LSE.
  * @note Clock security system can be disabled only after a LSE
  *       failure detection. In that case it MUST be disabled by software.
  * @rmtoll CSR1         LSECSSON      LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSECSSON);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll CSR1         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->CSR1, RCC_CSR1_LSERDY) == (RCC_CSR1_LSERDY)) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll CSR1         LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->CSR1, RCC_CSR1_LSECSSD) == (RCC_CSR1_LSECSSD)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI Oscillator
  * @rmtoll CSR2          LSION         LL_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->CSR2, RCC_CSR2_LSION);
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll CSR2          LSION         LL_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->CSR2, RCC_CSR2_LSION);
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll CSR2          LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_LSIRDY) == (RCC_CSR2_LSIRDY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll CSR1         LSCOEN        LL_RCC_LSCO_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->CSR1, RCC_CSR1_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll CSR1         LSCOEN        LL_RCC_LSCO_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSCOEN);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll CSR1         LSCOSEL       LL_RCC_LSCO_SetSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t Source)
{
  MODIFY_REG(RCC->CSR1, RCC_CSR1_LSCOSEL, Source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll CSR1         LSCOSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR1, RCC_CSR1_LSCOSEL));
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
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSIUSB48 (*)
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_LSE
  * @note (*) peripheral not available on all devices
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
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSIUSB48 (*)
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_LSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_LSE
  * @note (*) peripheral not available on all devices
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

#if defined(RCC_CR_SYSDIV)
/**
  * @brief  Set SYS DIV
  * @rmtoll CR         SYSDIV          LL_RCC_SetSYSDivider
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_7
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSYSDivider(uint32_t Divider)
{
  MODIFY_REG(RCC->CR, RCC_CR_SYSDIV, Divider);
}
#endif /* RCC_CR_SYSDIV */

/**
  * @brief  Set AHB prescaler
  * @rmtoll CFGR         HPRE          LL_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_DIV_1
  *         @arg @ref LL_RCC_HCLK_DIV_2
  *         @arg @ref LL_RCC_HCLK_DIV_4
  *         @arg @ref LL_RCC_HCLK_DIV_8
  *         @arg @ref LL_RCC_HCLK_DIV_16
  *         @arg @ref LL_RCC_HCLK_DIV_64
  *         @arg @ref LL_RCC_HCLK_DIV_128
  *         @arg @ref LL_RCC_HCLK_DIV_256
  *         @arg @ref LL_RCC_HCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, Prescaler);
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll CFGR         PPRE         LL_RCC_SetAPB1Prescaler
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
  * @brief  Set HSI48 division factor
  * @rmtoll CR         HSIDIV          LL_RCC_SetHSIDiv
  * @note  HSIDIV parameter is only applied to SYSCLK_Frequency when HSI is used as
  * system clock source.
  * @param  HSIDiv  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  *         @arg @ref LL_RCC_HSI_DIV_16
  *         @arg @ref LL_RCC_HSI_DIV_32
  *         @arg @ref LL_RCC_HSI_DIV_64
  *         @arg @ref LL_RCC_HSI_DIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetHSIDiv(uint32_t HSIDiv)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSIDIV, HSIDiv);
}

/**
  * @brief  Set HSIKER division factor
  * @rmtoll CR         HSIKERDIV          LL_RCC_SetHSIKERDiv
  * @param  HSIKERDiv  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSIKER_DIV_1
  *         @arg @ref LL_RCC_HSIKER_DIV_2
  *         @arg @ref LL_RCC_HSIKER_DIV_3
  *         @arg @ref LL_RCC_HSIKER_DIV_4
  *         @arg @ref LL_RCC_HSIKER_DIV_5
  *         @arg @ref LL_RCC_HSIKER_DIV_6
  *         @arg @ref LL_RCC_HSIKER_DIV_7
  *         @arg @ref LL_RCC_HSIKER_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetHSIKERDiv(uint32_t HSIKERDiv)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSIKERDIV, HSIKERDiv);
}

#if defined(RCC_CR_SYSDIV)
/**
  * @brief  Get SYS divider
  * @rmtoll CR         SYSDIV          LL_RCC_GetSYSDivider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_7
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_GetSYSDivider(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_SYSDIV));
}
#endif /* RCC_CR_SYSDIV */

/**
  * @brief  Get AHB prescaler
  * @rmtoll CFGR         HPRE          LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_DIV_1
  *         @arg @ref LL_RCC_HCLK_DIV_2
  *         @arg @ref LL_RCC_HCLK_DIV_4
  *         @arg @ref LL_RCC_HCLK_DIV_8
  *         @arg @ref LL_RCC_HCLK_DIV_16
  *         @arg @ref LL_RCC_HCLK_DIV_64
  *         @arg @ref LL_RCC_HCLK_DIV_128
  *         @arg @ref LL_RCC_HCLK_DIV_256
  *         @arg @ref LL_RCC_HCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE));
}

/**
  * @brief  Get APB1 prescaler
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
  * @brief  Get HSI48 Division factor
  * @rmtoll CR         HSIDIV         LL_RCC_GetHSIDiv
  * @note  HSIDIV parameter is only applied to SYSCLK_Frequency when HSI is used as
  * system clock source.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  *         @arg @ref LL_RCC_HSI_DIV_16
  *         @arg @ref LL_RCC_HSI_DIV_32
  *         @arg @ref LL_RCC_HSI_DIV_64
  *         @arg @ref LL_RCC_HSI_DIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_GetHSIDiv(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSIDIV));
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
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_HSIUSB48 (*)
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_LSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_DIV_1
  *         @arg @ref LL_RCC_MCO1_DIV_2
  *         @arg @ref LL_RCC_MCO1_DIV_4
  *         @arg @ref LL_RCC_MCO1_DIV_8
  *         @arg @ref LL_RCC_MCO1_DIV_16
  *         @arg @ref LL_RCC_MCO1_DIV_32
  *         @arg @ref LL_RCC_MCO1_DIV_64
  *         @arg @ref LL_RCC_MCO1_DIV_128
  *         @arg @ref LL_RCC_MCO1_DIV_256 (*)
  *         @arg @ref LL_RCC_MCO1_DIV_512 (*)
  *         @arg @ref LL_RCC_MCO1_DIV_1024 (*)
  * @note (*) not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE, MCOxSource | MCOxPrescaler);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MCO2 MCO2
  * @{
  */

/**
  * @brief  Configure MCO2
  * @rmtoll CFGR         MCO2SEL        LL_RCC_ConfigMCO2\n
  *         CFGR         MCO2PRE        LL_RCC_ConfigMCO2
  * @note  feature not available in all devices.
  * @param  MCOxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO2SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI
  *         @arg @ref LL_RCC_MCO2SOURCE_HSIUSB48 (*)
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  *         @arg @ref LL_RCC_MCO2SOURCE_LSE
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO2_DIV_1
  *         @arg @ref LL_RCC_MCO2_DIV_2
  *         @arg @ref LL_RCC_MCO2_DIV_4
  *         @arg @ref LL_RCC_MCO2_DIV_8
  *         @arg @ref LL_RCC_MCO2_DIV_16
  *         @arg @ref LL_RCC_MCO2_DIV_32
  *         @arg @ref LL_RCC_MCO2_DIV_64
  *         @arg @ref LL_RCC_MCO2_DIV_128
  *         @arg @ref LL_RCC_MCO2_DIV_256 (*)
  *         @arg @ref LL_RCC_MCO2_DIV_512 (*)
  *         @arg @ref LL_RCC_MCO2_DIV_1024 (*)
  * @note (*) not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO2(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO2SEL | RCC_CFGR_MCO2PRE, MCOxSource | MCOxPrescaler);
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
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSIKER
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t USARTxSource)
{
  MODIFY_REG(RCC->CCIPR, (USARTxSource >> 16U), (USARTxSource & 0x0000FFFFU));
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CCIPR        I2C1SEL       LL_RCC_SetI2CClockSource
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSIKER
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t I2CxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C1SEL, I2CxSource);
}

/**
  * @brief  Configure ADC clock source
  * @rmtoll CCIPR        ADCSEL        LL_RCC_SetADCClockSource
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSIKER
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t ADCxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, ADCxSource);
}

/**
  * @brief  Configure I2Sx clock source
  * @rmtoll CCIPR        I2S1SEL       LL_RCC_SetI2SClockSource
  * @param  I2SxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE_PIN
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE_HSIKER
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2SClockSource(uint32_t I2SxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2S1SEL, I2SxSource);
}

#if defined (USB_DRD_FS)
/**
  * @brief  Configure USB clock source
  * @rmtoll CCIPR2        CK48MSEL      LL_RCC_SetUSBClockSource
  * @param  USBxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSE
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSBClockSource(uint32_t USBxSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_USBSEL, USBxSource);
}
#endif /* USB_DRD_FS */

#if defined(FDCAN1)
/**
  * @brief  Configure FDCANx clock source
  * @rmtoll CCIPR        FDCAN1SEL       LL_RCC_SetFDCANClockSource
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE_HSIKER
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t FDCANxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_FDCAN1SEL, FDCANxSource);
}
#endif /* FDCAN1 */

/**
  * @brief  Get USARTx clock source
  * @rmtoll CCIPR        USART1SEL     LL_RCC_GetUSARTClockSource
  * @param  USARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSIKER
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t USARTx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, USARTx) | (USARTx << 16U));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CCIPR        I2C1SEL       LL_RCC_GetI2CClockSource
  * @param  I2Cx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSIKER
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t I2Cx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, I2Cx));
}

/**
  * @brief  Get ADCx clock source
  * @rmtoll CCIPR        ADCSEL        LL_RCC_GetADCClockSource
  * @param  ADCx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSIKER
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t ADCx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, ADCx));
}

/**
  * @brief  Get I2Sx clock source
  * @rmtoll CCIPR        I2S        LL_RCC_GetI2SClockSource
  * @param  I2Sx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE_PIN
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE_HSIKER
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2SClockSource(uint32_t I2Sx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, I2Sx));
}

#if defined (USB_DRD_FS)
/**
  * @brief  Get USBx clock source
  * @rmtoll CCIPR2        CK48MSEL        LL_RCC_GetUSBClockSource
  * @param  USBx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBClockSource(uint32_t USBx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, USBx));
}
#endif /* USB_DRD_FS */

#if defined(FDCAN1)
/**
  * @brief  Get FDCANx clock source
  * @rmtoll CCIPR        FDCAN        LL_RCC_GetFDCANClockSource
  * @param  FDCANx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN1_CLKSOURCE_HSIKER
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t FDCANx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, FDCANx));
}
#endif /* FDCAN1 */
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
  * @rmtoll CSR1         RTCSEL        LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->CSR1, RCC_CSR1_RTCSEL, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll CSR1         RTCSEL        LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR1, RCC_CSR1_RTCSEL));
}

/**
  * @brief  Enable RTC
  * @rmtoll CSR1         RTCEN         LL_RCC_EnableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->CSR1, RCC_CSR1_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll CSR1         RTCEN         LL_RCC_DisableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->CSR1, RCC_CSR1_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll CSR1         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((READ_BIT(RCC->CSR1, RCC_CSR1_RTCEN) == (RCC_CSR1_RTCEN)) ? 1UL : 0UL);
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll CSR1         RTCRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->CSR1, RCC_CSR1_RTCRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll CSR1         RTCRST         LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->CSR1, RCC_CSR1_RTCRST);
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

#if defined(RCC_HSI48_SUPPORT)
/**
  * @brief  Clear HSI48 ready interrupt flag
  * @rmtoll CICR          HSI48RDYC     LL_RCC_ClearFlag_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIUSB48RDYC);
}
#endif /* RCC_HSI48_SUPPORT */

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
  * @brief  Clear Clock security system interrupt flag
  * @rmtoll CICR         CSSC          LL_RCC_ClearFlag_HSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
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

#if defined(RCC_HSI48_SUPPORT)
/**
  * @brief  Check if HSI48 ready interrupt occurred or not
  * @rmtoll CIR          HSI48RDYF     LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIUSB48RDYF) == (RCC_CIFR_HSIUSB48RDYF)) ? 1UL : 0UL);
}
#endif /* RCC_HSI48_SUPPORT */

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
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll CIFR         CSSF          LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_CSSF) == (RCC_CIFR_CSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE Clock security system interrupt occurred or not
  * @rmtoll CIFR         LSECSSF       LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == (RCC_CIFR_LSECSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Independent Watchdog reset is set or not.
  * @rmtoll CSR2          IWDGRSTF      LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_IWDGRSTF) == (RCC_CSR2_IWDGRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll CSR2          LPWRRSTF      LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_LPWRRSTF) == (RCC_CSR2_LPWRRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Option byte reset is set or not.
  * @rmtoll CSR2          OBLRSTF       LL_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_OBLRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_OBLRSTF) == (RCC_CSR2_OBLRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll CSR2          PINRSTF       LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_PINRSTF) == (RCC_CSR2_PINRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll CSR2          SFTRSTF       LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_SFTRSTF) == (RCC_CSR2_SFTRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll CSR2          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_WWDGRSTF) == (RCC_CSR2_WWDGRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag BOR or POR/PDR reset is set or not.
  * @rmtoll CSR2          PWRRSTF       LL_RCC_IsActiveFlag_PWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PWRRST(void)
{
  return ((READ_BIT(RCC->CSR2, RCC_CSR2_PWRRSTF) == (RCC_CSR2_PWRRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll CSR2          RMVF          LL_RCC_ClearResetFlags
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  SET_BIT(RCC->CSR2, RCC_CSR2_RMVF);
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

#if defined(RCC_HSI48_SUPPORT)
/**
  * @brief  Enable HSI48 ready interrupt
  * @rmtoll CIER          HSI48RDYIE    LL_RCC_EnableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIUSB48RDYIE);
}
#endif /* RCC_HSI48_SUPPORT */

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

#if defined(RCC_HSI48_SUPPORT)
/**
  * @brief  Disable HSI48 ready interrupt
  * @rmtoll CIER          HSI48RDYIE    LL_RCC_DisableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIUSB48RDYIE);
}
#endif /* RCC_HSI48_SUPPORT */

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

#if defined(RCC_HSI48_SUPPORT)
/**
  * @brief  Checks if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_IsEnabledIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIUSB48RDYIE) == (RCC_CIER_HSIUSB48RDYIE)) ? 1UL : 0UL);
}
#endif /* RCC_HSI48_SUPPORT */

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
uint32_t    LL_RCC_GetADCClockFreq(uint32_t ADCxSource);
uint32_t    LL_RCC_GetI2SClockFreq(uint32_t I2SxSource);
uint32_t    LL_RCC_GetRTCClockFreq(void);
#if defined(USB_DRD_FS)
uint32_t    LL_RCC_GetUSBClockFreq(uint32_t USBxSource);
#endif /* USB_DRD_FS */
#if defined(FDCAN1)
uint32_t    LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource);
#endif /* FDCAN1 */
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

#endif /* STM32C0xx_LL_RCC_H */
