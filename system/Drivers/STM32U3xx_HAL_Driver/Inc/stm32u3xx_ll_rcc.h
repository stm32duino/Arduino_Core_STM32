/**
  ******************************************************************************
  * @file    stm32u3xx_ll_rcc.h
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
#ifndef STM32U3xx_LL_RCC_H
#define STM32U3xx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx.h"


#if !defined (UNUSED)
#define UNUSED(x) ((void)(x))
#endif /* !defined (UNUSED) */


/** @addtogroup STM32U3xx_LL_Driver
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
#define RCC_OFFSET_CCIPR2       1U
#define RCC_OFFSET_CCIPR3       2U

static __IO uint32_t *ccipr_addr_reg[3] =
{
  (__IO uint32_t *)(uint32_t) &RCC->CCIPR1,
  (__IO uint32_t *)(uint32_t) &RCC->CCIPR2,
  (__IO uint32_t *)(uint32_t) &RCC->CCIPR3
};

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
  uint32_t PCLK3_Frequency;         /*!< PCLK7 clock frequency */
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
#define HSE_VALUE      32000000U   /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined (HSI_VALUE)
#define HSI_VALUE      16000000U   /*!< Value of the HSI16 oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined (HSI48_VALUE)
#define HSI48_VALUE    48000000U  /*!< Value of the HSI48 oscillator in Hz */
#endif /* HSI48_VALUE */

#if !defined (LSE_VALUE)
#define LSE_VALUE      32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined (LSI_VALUE)
#define LSI_VALUE      32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined (MSIRC0_VALUE)
#define MSIRC0_VALUE   96000000U  /*!< Value of the MSI RC0 oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined (MSIRC1_VALUE)
#define MSIRC1_VALUE   24000000U  /*!< Value of the MSI RC1 oscillator in Hz */
#endif /* LSI_VALUE */


#if !defined (EXTERNAL_AUDIO_CLOCK_VALUE)
#define EXTERNAL_AUDIO_CLOCK_VALUE    48000U /*!< Value of the external AUDIO_CLK in Hz */
#endif /* EXTERNAL_AUDIO_CLOCK_VALUE */

/**
  * @}
  */


/** @defgroup RCC_LL_EC_MSIX_SET_FREQ_AFTER_STANDBY  MSIS/MSIK frequency after standby
  * @{
  */
#define LL_RCC_MSISDIVS_RANGE_5            (RCC_CSR_MSISDIVS_0)                         /*!< around 12 MHz (reset value) */
#define LL_RCC_MSISDIVS_RANGE_6            (RCC_CSR_MSISDIVS_1)                         /*!< around 6 MHz */
#define LL_RCC_MSISDIVS_RANGE_7            (RCC_CSR_MSISDIVS_1 | RCC_CSR_MSISDIVS_0)    /*!< around 3 MHz */

#define LL_RCC_MSIKDIVS_RANGE_5            (RCC_CSR_MSIKDIVS_0)                         /*!< around 12 MHz (reset value) */
#define LL_RCC_MSIKDIVS_RANGE_6            (RCC_CSR_MSIKDIVS_1)                         /*!< around 6 MHz */
#define LL_RCC_MSIKDIVS_RANGE_7            (RCC_CSR_MSIKDIVS_1 | RCC_CSR_MSIKDIVS_0)    /*!< around 3 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIER_LSIRDYE                RCC_CIER_LSIRDYE      /*!< LSI Ready Interrupt Enable */
#define LL_RCC_CIER_LSERDYE                RCC_CIER_LSERDYE      /*!< LSE Ready Interrupt Enable */
#define LL_RCC_CIER_MSIRDYE                RCC_CIER_MSIRDYE      /*!< MSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSIRDYE                RCC_CIER_HSIRDYE      /*!< HSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSERDYE                RCC_CIER_HSERDYE      /*!< HSE Ready Interrupt Enable */
#define LL_RCC_CIER_HSI48RDYE              RCC_CIER_HSI48RDYE    /*!< HSI48 Ready Interrupt Enable */
#define LL_RCC_CIER_MSIPLL1RDYE            RCC_CIER_MSIPLL1RDYE  /*!< MSIRC1 PLL-mode ready Interrupt Enable */
#define LL_RCC_CIER_MSIPLL0RDYE            RCC_CIER_MSIPLL0RDYE  /*!< MSIRC0 PLL-mode ready Interrupt Enable */
#define LL_RCC_CIER_MSIPLLUE               RCC_CIER_MSIPLLUE     /*!< MSI PLL-mode with LSE unlock Interrupt Enable */
#define LL_RCC_CIER_MSIPLLHSUE             RCC_CIER_MSIPLLHSUE   /*!< MSI PLL-mode with HSE unlock Interrupt Enable */
#define LL_RCC_CIER_MSIKRDYE               RCC_CIER_MSIKRDYE     /*!< MSIK oscillator Ready Interrupt Enable */
#define LL_RCC_CIER_LSECSSE                RCC_CIER_LSECSSE      /*!< LSE Clock security system Interrupt Enable */

#define LL_RCC_CICR_LSIRDYC                RCC_CICR_LSIRDYC      /*!< LSI Ready Interrupt Clear */
#define LL_RCC_CICR_LSERDYC                RCC_CICR_LSERDYC      /*!< LSE Ready Interrupt Clear */
#define LL_RCC_CICR_MSIRDYC                RCC_CICR_MSIRDYC      /*!< MSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSIRDYC                RCC_CICR_HSIRDYC      /*!< HSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSERDYC                RCC_CICR_HSERDYC      /*!< HSE Ready Interrupt Clear */
#define LL_RCC_CICR_HSI48RDYC              RCC_CICR_HSI48RDYC    /*!< HSI48 Ready Interrupt Clear */
#define LL_RCC_CICR_MSIPLL1RDYC            RCC_CICR_MSIPLL1RDYC  /*!< MSIRC1 PLL-mode ready Interrupt Clear */
#define LL_RCC_CICR_MSIPLL0RDYC            RCC_CICR_MSIPLL0RDYC  /*!< MSIRC0 PLL-mode ready Interrupt Clear */
#define LL_RCC_CICR_MSIPLLUC               RCC_CICR_MSIPLLUC     /*!< MSI PLL-mode with LSE unlock Interrupt Clear */
#define LL_RCC_CICR_MSIPLLHSUC             RCC_CICR_MSIPLLHSUC   /*!< MSI PLL-mode with HSE unlock Interrupt Clear */
#define LL_RCC_CICR_CSSC                   RCC_CICR_CSSC         /*!< Clock security system Interrupt Clear */
#define LL_RCC_CICR_MSIKRDYC               RCC_CICR_MSIKRDYC     /*!< MSIK oscillator Ready Interrupt Clear */
#define LL_RCC_CICR_LSECSSC                RCC_CICR_LSECSSC      /*!< LSE Clock security system Interrupt Clear */

#define LL_RCC_CIFR_LSIRDYF                RCC_CIFR_LSIRDYF      /*!< LSI Ready Interrupt Flag */
#define LL_RCC_CIFR_LSERDYF                RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt Flag */
#define LL_RCC_CIFR_MSIRDYF                RCC_CIFR_MSIRDYF      /*!< MSI Ready Interrupt Flag */
#define LL_RCC_CIFR_HSIRDYF                RCC_CIFR_HSIRDYF      /*!< HSI Ready Interrupt Flag */
#define LL_RCC_CIFR_HSERDYF                RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt Flag */
#define LL_RCC_CIFR_HSI48RDYF              RCC_CIFR_HSI48RDYF    /*!< HSI48 Ready Interrupt Flag */
#define LL_RCC_CIFR_MSIPLL1RDYF            RCC_CIFR_MSIPLL1RDYF  /*!< MSIRC1 PLL-mode ready Interrupt Flag */
#define LL_RCC_CIFR_MSIPLL0RDYF            RCC_CIFR_MSIPLL0RDYF  /*!< MSIRC0 PLL-mode ready Interrupt Flag */
#define LL_RCC_CIFR_MSIPLLUF               RCC_CIFR_MSIPLLUF     /*!< MSI PLL-mode with LSE unlock Interrupt Flag */
#define LL_RCC_CIFR_MSIPLLHSUF             RCC_CIFR_MSIPLLHSUF   /*!< MSI PLL-mode with HSE unlock Interrupt Flag */
#define LL_RCC_CIFR_CSSF                   RCC_CIFR_CSSF         /*!< Clock security system Interrupt Flag */
#define LL_RCC_CIFR_MSIKRDYF               RCC_CIFR_MSIKRDYF     /*!< MSIK oscillator Ready Interrupt Flag */
#define LL_RCC_CIFR_LSECSSF                RCC_CIFR_LSECSSF      /*!< LSE Clock security system Interrupt Flag */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0U                     /*!< Xtal mode lower driving capability       */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR_LSEDRV_0      /*!< Xtal mode medium low driving capability  */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR_LSEDRV_1      /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_BDCR_LSEDRV        /*!< Xtal mode higher driving capability      */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI          0U                     /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE          RCC_BDCR_LSCOSEL       /*!< LSE selection for low speed clock  */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_MSIS          0U                                  /*!< MSIS selection as system clock    */
#define LL_RCC_SYS_CLKSOURCE_HSI16         RCC_CFGR1_SW_0                      /*!< HSI16 selection as system clock   */
#define LL_RCC_SYS_CLKSOURCE_HSE           RCC_CFGR1_SW_1                      /*!< HSE selection as system clock     */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_MSIS          0U                           /*!< MSIS used as system clock    */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI16         RCC_CFGR1_SWS_0              /*!< HSI16 used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE           RCC_CFGR1_SWS_1              /*!< HSE used as system clock     */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_HCLK_SYSCLK_DIV_1                0U                                                                          /*!< SYSCLK not divided    */
#define LL_RCC_HCLK_SYSCLK_DIV_2                RCC_CFGR2_HPRE_3                                                            /*!< SYSCLK divided by 2   */
#define LL_RCC_HCLK_SYSCLK_DIV_4                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_0)                                       /*!< SYSCLK divided by 4   */
#define LL_RCC_HCLK_SYSCLK_DIV_8                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1)                                       /*!< SYSCLK divided by 8   */
#define LL_RCC_HCLK_SYSCLK_DIV_16               (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0)                    /*!< SYSCLK divided by 16  */
#define LL_RCC_HCLK_SYSCLK_DIV_64               (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2)                                       /*!< SYSCLK divided by 64  */
#define LL_RCC_HCLK_SYSCLK_DIV_128              (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0)                    /*!< SYSCLK divided by 128 */
#define LL_RCC_HCLK_SYSCLK_DIV_256              (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1)                    /*!< SYSCLK divided by 256 */
#define LL_RCC_HCLK_SYSCLK_DIV_512              (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB1 prescaler
  * @{
  */
#define LL_RCC_APB1_HCLK_DIV_1                  0U                                                          /*!< HCLK not divided   */
#define LL_RCC_APB1_HCLK_DIV_2                  RCC_CFGR2_PPRE1_2                                           /*!< HCLK divided by 2  */
#define LL_RCC_APB1_HCLK_DIV_4                  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_0)                     /*!< HCLK divided by 4  */
#define LL_RCC_APB1_HCLK_DIV_8                  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1)                     /*!< HCLK divided by 8  */
#define LL_RCC_APB1_HCLK_DIV_16                 (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1 | RCC_CFGR2_PPRE1_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV  APB2 prescaler
  * @{
  */
#define LL_RCC_APB2_HCLK_DIV_1                  0U                                                          /*!< HCLK not divided   */
#define LL_RCC_APB2_HCLK_DIV_2                  RCC_CFGR2_PPRE2_2                                           /*!< HCLK divided by 2  */
#define LL_RCC_APB2_HCLK_DIV_4                  (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_0)                     /*!< HCLK divided by 4  */
#define LL_RCC_APB2_HCLK_DIV_8                  (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1)                     /*!< HCLK divided by 8  */
#define LL_RCC_APB2_HCLK_DIV_16                 (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1 | RCC_CFGR2_PPRE2_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB3_DIV  APB3 prescaler
  * @{
  */
#define LL_RCC_APB3_HCLK_DIV_1                  0U                                                          /*!< HCLK not divided   */
#define LL_RCC_APB3_HCLK_DIV_2                  RCC_CFGR3_PPRE3_2                                           /*!< HCLK divided by 2  */
#define LL_RCC_APB3_HCLK_DIV_4                  (RCC_CFGR3_PPRE3_2 | RCC_CFGR3_PPRE3_0)                     /*!< HCLK divided by 4  */
#define LL_RCC_APB3_HCLK_DIV_8                  (RCC_CFGR3_PPRE3_2 | RCC_CFGR3_PPRE3_1)                     /*!< HCLK divided by 8  */
#define LL_RCC_APB3_HCLK_DIV_16                 (RCC_CFGR3_PPRE3_2 | RCC_CFGR3_PPRE3_1 | RCC_CFGR3_PPRE3_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCOSOURCE  MCO SOURCE selection
  * @{
  */
#define LL_RCC_MCOSOURCE_NOCLOCK          0U                                                                                 /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCOSOURCE_SYSCLK           RCC_CFGR1_MCOSEL_0                                                                 /*!< SYSCLK selection as MCO source      */
#define LL_RCC_MCOSOURCE_MSIS             RCC_CFGR1_MCOSEL_1                                                                 /*!< MSIS selection as MCO source        */
#define LL_RCC_MCOSOURCE_HSI16            (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_1)                                          /*!< HSI16 selection as MCO source       */
#define LL_RCC_MCOSOURCE_HSE              RCC_CFGR1_MCOSEL_2                                                                 /*!< HSE selection as MCO source         */
#define LL_RCC_MCOSOURCE_LSI              (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_2)                                          /*!< LSI selection as MCO source         */
#define LL_RCC_MCOSOURCE_LSE              (RCC_CFGR1_MCOSEL_1| RCC_CFGR1_MCOSEL_2)                                           /*!< LSE selection as MCO source         */
#define LL_RCC_MCOSOURCE_HSI48            (RCC_CFGR1_MCOSEL_0| RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_2)                      /*!< HSI48 selection as MCO source       */
#define LL_RCC_MCOSOURCE_MSIK             RCC_CFGR1_MCOSEL_3                                                                 /*!< MSIK selection as MCO source        */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO_DIV  MCO prescaler
  * @{
  */
#define LL_RCC_MCO_DIV_1                  0U                                                               /*!< MCO not divided    */
#define LL_RCC_MCO_DIV_2                  RCC_CFGR1_MCOPRE_0                                               /*!< MCO divided by 2   */
#define LL_RCC_MCO_DIV_4                  RCC_CFGR1_MCOPRE_1                                               /*!< MCO divided by 4   */
#define LL_RCC_MCO_DIV_8                  (RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0)                        /*!< MCO divided by 8   */
#define LL_RCC_MCO_DIV_16                 RCC_CFGR1_MCOPRE_2                                               /*!< MCO divided by 16  */
#define LL_RCC_MCO_DIV_32                 (RCC_CFGR1_MCOPRE_2 | RCC_CFGR1_MCOPRE_0)                        /*!< MCO divided by 32  */
#define LL_RCC_MCO_DIV_64                 (RCC_CFGR1_MCOPRE_2 | RCC_CFGR1_MCOPRE_1)                        /*!< MCO divided by 64  */
#define LL_RCC_MCO_DIV_128                (RCC_CFGR1_MCOPRE_2 | RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0)   /*!< MCO divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2SOURCE  MCO2 SOURCE selection
  * @{
  */
#define LL_RCC_MCO2SOURCE_NOCLOCK          0U                                                                                     /*!< MCO2 output disabled, no clock on MCO2 */
#define LL_RCC_MCO2SOURCE_SYSCLK           RCC_CFGR1_MCO2SEL_0                                                                    /*!< SYSCLK selection as MCO2 source        */
#define LL_RCC_MCO2SOURCE_MSIS             RCC_CFGR1_MCO2SEL_1                                                                    /*!< MSIS selection as MCO2 source          */
#define LL_RCC_MCO2SOURCE_HSI16            (RCC_CFGR1_MCO2SEL_0 | RCC_CFGR1_MCO2SEL_1)                                            /*!< HSI16 selection as MCO2 source         */
#define LL_RCC_MCO2SOURCE_HSE              RCC_CFGR1_MCO2SEL_2                                                                    /*!< HSE selection as MCO2 source           */
#define LL_RCC_MCO2SOURCE_LSI              (RCC_CFGR1_MCO2SEL_0 | RCC_CFGR1_MCO2SEL_2)                                            /*!< LSI selection as MCO2 source           */
#define LL_RCC_MCO2SOURCE_LSE              (RCC_CFGR1_MCO2SEL_1| RCC_CFGR1_MCO2SEL_2)                                             /*!< LSE selection as MCO2 source           */
#define LL_RCC_MCO2SOURCE_HSI48            (RCC_CFGR1_MCO2SEL_0| RCC_CFGR1_MCO2SEL_1 | RCC_CFGR1_MCO2SEL_2)                       /*!< HSI48 selection as MCO2 source         */
#define LL_RCC_MCO2SOURCE_MSIK             RCC_CFGR1_MCO2SEL_3                                                                    /*!< MSIK selection as MCO2 source          */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2_DIV  MCO2 prescaler
  * @{
  */
#define LL_RCC_MCO2_DIV_1                  0U                                                                  /*!< MCO2 not divided    */
#define LL_RCC_MCO2_DIV_2                  RCC_CFGR1_MCO2PRE_0                                                 /*!< MCO2 divided by 2   */
#define LL_RCC_MCO2_DIV_4                  RCC_CFGR1_MCO2PRE_1                                                 /*!< MCO2 divided by 4   */
#define LL_RCC_MCO2_DIV_8                  (RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)                         /*!< MCO2 divided by 8   */
#define LL_RCC_MCO2_DIV_16                 RCC_CFGR1_MCO2PRE_2                                                 /*!< MCO2 divided by 16  */
#define LL_RCC_MCO2_DIV_32                 (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_0)                         /*!< MCO2 divided by 32  */
#define LL_RCC_MCO2_DIV_64                 (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1)                         /*!< MCO2 divided by 64  */
#define LL_RCC_MCO2_DIV_128                (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)   /*!< MCO2 divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUP_CLK  Stop wakeup clock
  * @{
  */
#define LL_RCC_STOP_WAKEUP_CLK_MSIS        0U                                                                  /*!< MSIS oscillator selected as wakeup from stop clock and CSS backup clock    */
#define LL_RCC_STOP_WAKEUP_CLK_HSI16       RCC_CFGR1_STOPWUCK                                                  /*!< HSI16 oscillator selected as wakeup from stop clock and CSS backup clock   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUP_KERCLK  Stop wakeup kernel clock
  * @{
  */
#define LL_RCC_STOP_WAKEUP_KERCLK_MSIK        0U                                                               /*!< MSIK oscillator selected as wakeup from stop kernel clock    */
#define LL_RCC_STOP_WAKEUP_KERCLK_HSI16       RCC_CFGR1_STOPKERWUCK                                            /*!< HSI16 oscillator selected as wakeup from stop kernel clock   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RCx_PLL_INPUT_CLK  RCx PLL input clock
  * @{
  */
#define LL_RCC_MSIRCx_PLLMODE_INPUT_HSE         0U                                                              /*!< HSE (16 MHz) is used as MSI input clock when PLL-mode with high-speed clock is selected    */
#define LL_RCC_MSIRCx_PLLMODE_INPUT_HSE_DIV_2   RCC_ICSCR1_MSIHSINDIV                                           /*!< HSE (32 MHz) /2 is used as MSI input clock when PLL-mode with high-speed clock is selected */

#define LL_RCC_MSIPLL0SEL_LSE                   0U                                                              /*!< LSE is used as MSIRC0 input clock when PLL-mode is selected                */
#define LL_RCC_MSIPLL0SEL_HSE_OR_HSEDIV2        RCC_ICSCR1_MSIPLL0SEL                                           /*!< HSE or HSE/2 is used as MSIRC0 input clock when PLL-mode is selected       */

#define LL_RCC_MSIPLL1SEL_LSE                   0U                                                              /*!< LSE is used as MSIRC1 input clock when PLL-mode is selected                */
#define LL_RCC_MSIPLL1SEL_HSE_OR_HSEDIV2        RCC_ICSCR1_MSIPLL1SEL                                           /*!< HSE or HSE/2 is used as MSIRC1 input clock when PLL-mode is selected       */

#define LL_RCC_MSIPLL0_STARTUP_NORMAL           0U                                                              /*!< MSIRC0 PLL mode normal startup                */
#define LL_RCC_MSIPLL0_STARTUP_FAST             RCC_CR_MSIPLL0FAST                                              /*!< MSIRC0 PLL mode fast startup                  */

#define LL_RCC_MSIPLL1_STARTUP_NORMAL           0U                                                              /*!< MSIRC1 PLL mode normal startup                */
#define LL_RCC_MSIPLL1_STARTUP_FAST             RCC_CR_MSIPLL1FAST                                              /*!< MSIRC1 PLL mode fast startup                  */

/**
  * @}
  */

#define LL_RCC_MSI_CLOCK_RANGE_MSIXDIVS         0U                                                              /*!< MSIS/MSIK ranges provided by MSISSRANGE[3:0] and MSIKSRANGE[3:0] in RCC_CSR          */
#define LL_RCC_MSI_CLOCK_RANGE_MSIXDIV          RCC_ICSCR1_MSIRGSEL                                             /*!< MSIS/MSIK ranges provided by MSISRANGE[3:0] and MSIKRANGE[3:0] in RCC_ICSCR1         */

#define LL_RCC_MSI_BIAS_MODE_CONTINUOUS         0U                                                              /*!< MSI bias continuous mode (clock accuracy fast settling time)                         */
#define LL_RCC_MSI_BIAS_MODE_SAMPLING           RCC_ICSCR1_MSIBIAS                                              /*!< MSI bias sampling mode when the device is in Stop 1 or Stop 2 (ultra-low-power mode) */

#define LL_RCC_MSIS_CLOCK_SOURCE_RC0            0U                                                              /*!< MSIRC0 (96 MHz)  is selected as source to generate MSISSRANGE                        */
#define LL_RCC_MSIS_CLOCK_SOURCE_RC1            RCC_ICSCR1_MSISSEL                                              /*!< MSIRC1 (24 MHz)  is selected as source to generate MSISSRANGE                        */

#define LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_1       0U                                                              /*!< MSIRCx /1 is selected for MSIS (RC0 : range 0 around 96 MHz / RC1 : range 4 around 24 MHz) */
#define LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2       RCC_ICSCR1_MSISDIV_0                                            /*!< MSIRCx /2 is selected for MSIS (RC0 : range 0 around 48 MHz / RC1 : range 4 around 12 MHz) */
#define LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_4       RCC_ICSCR1_MSISDIV_1                                            /*!< MSIRCx /4 is selected for MSIS (RC0 : range 0 around 24 MHz / RC1 : range 4 around 6 MHz)  */
#define LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_8       (RCC_ICSCR1_MSISDIV_1 | RCC_ICSCR1_MSISDIV_0)                   /*!< MSIRCx /8 is selected for MSIS (RC0 : range 0 around 12 MHz / RC1 : range 4 around 3 MHz)  */

#define LL_RCC_MSIK_CLOCK_SOURCE_RC0            0U                                                              /*!< MSIRC0 (96 MHz)  is selected as source to generate MSIKSRANGE                        */
#define LL_RCC_MSIK_CLOCK_SOURCE_RC1            RCC_ICSCR1_MSIKSEL                                              /*!< MSIRC1 (24 MHz)  is selected as source to generate MSIKSRANGE                        */

#define LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_1       0U                                                              /*!< MSIRCx /1 is selected for MSIK (RC0 : range 0 around 96 MHz / RC1 : range 4 around 24 MHz) */
#define LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_2       RCC_ICSCR1_MSIKDIV_0                                            /*!< MSIRCx /2 is selected for MSIK (RC0 : range 0 around 48 MHz / RC1 : range 4 around 12 MHz) */
#define LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_4       RCC_ICSCR1_MSIKDIV_1                                            /*!< MSIRCx /4 is selected for MSIK (RC0 : range 0 around 24 MHz / RC1 : range 4 around 6 MHz)  */
#define LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_8       (RCC_ICSCR1_MSIKDIV_1 | RCC_ICSCR1_MSIKDIV_0)                   /*!< MSIRCx /8 is selected for MSIK (RC0 : range 0 around 12 MHz / RC1 : range 4 around 3 MHz)  */

#define LL_RCC_MSIRC1_PLLMODE_LSE_MULT_732 0U                                                         /*!< Freq MSIRC1 = 23.9862 MHz */
#define LL_RCC_MSIRC1_PLLMODE_LSE_MULT_689 RCC_ICSCR1_MSIPLL1N_1                                      /*!< Freq MSIRC1 = 22.5772 MHz */
#define LL_RCC_MSIRC1_PLLMODE_LSE_MULT_750 (RCC_ICSCR1_MSIPLL1N_1 | RCC_ICSCR1_MSIPLL1N_0)            /*!< Freq MSIRC1 = 24.576 MHz  */

#define LL_RCC_HSE_ANALOG_MODE             0U
#define LL_RCC_HSE_DIGITAL_MODE            RCC_CR_HSEEXT


/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE              ((RCC_BDCR_RTCSEL_Pos << 16U) | ((RCC_BDCR_RTCSEL_Msk >> RCC_BDCR_RTCSEL_Pos) << 8U))  /*!< Mask to get RTCSEL clock source      */

#define LL_RCC_RTC_CLKSOURCE_NONE          0U                                             /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE           RCC_BDCR_RTCSEL_0                              /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI           RCC_BDCR_RTCSEL_1                              /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV32     (RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCSEL_0)        /*!< HSE oscillator clock divided by 32 used as RTC clock */


#define IS_LL_RCC_RTC_CLKSOURCE(__VALUE__)  ((__VALUE__) == LL_RCC_RTC_CLKSOURCE)

/**
  * @}
  */


/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_LSI_PREDIV_NONE          0U                       /*!< LSI not divided */
#define LL_RCC_LSI_PREDIV_128           RCC_CSR_LSIPREDIV        /*!< LSI divided by 128 */
/**
  * @}
  */


/* Since CCIPR features are split into 3 registers, addressing is performed using following protocol:
   bits[25-24] : register_id (values RCC_OFFSET_CCIPR1/RCC_OFFSET_CCIPR2/RCC_OFFSET_CCIPR3)
   bits[20-16] : position of the field in the register
   bits[15-8]  : mask of the field in the register
   bits[7-0]   : value
   */


/** @defgroup RCC_LL_EC_UxART Peripheral UxARTx get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_USART1SEL_Pos << 16U) | ((RCC_CCIPR1_USART1SEL_Msk >> RCC_CCIPR1_USART1SEL_Pos) << 8U))  /*!< Mask to get USART1SEL clock source      */
#if defined(USART2)
#define LL_RCC_USART2_CLKSOURCE         ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_USART2SEL_Pos << 16U) | ((RCC_CCIPR2_USART2SEL_Msk >> RCC_CCIPR2_USART2SEL_Pos) << 8U))  /*!< Mask to get USART2SEL clock source      */
#endif /* USART2 */
#define LL_RCC_USART3_CLKSOURCE         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_USART3SEL_Pos << 16U) | ((RCC_CCIPR1_USART3SEL_Msk >> RCC_CCIPR1_USART3SEL_Pos) << 8U))  /*!< Mask to get USART3SEL clock source      */
#define LL_RCC_UART4_CLKSOURCE          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_UART4SEL_Pos << 16U) | ((RCC_CCIPR1_UART4SEL_Msk >> RCC_CCIPR1_UART4SEL_Pos) << 8U))     /*!< Mask to get UART4SEL clock source      */
#define LL_RCC_UART5_CLKSOURCE          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_UART5SEL_Pos << 16U) | ((RCC_CCIPR1_UART5SEL_Msk >> RCC_CCIPR1_UART5SEL_Pos) << 8U))     /*!< Mask to get UART5SEL clock source      */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_UxART_CLKSOURCE  Peripheral UxARTx clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2   (LL_RCC_USART1_CLKSOURCE | 0U)                                                                                                    /*!< PCLK2 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSI16   (LL_RCC_USART1_CLKSOURCE | (RCC_CCIPR1_USART1SEL >> RCC_CCIPR1_USART1SEL_Pos))                                                    /*!< HSI16 clock used as USART1 clock source */

#if defined(USART2)
#define LL_RCC_USART2_CLKSOURCE_PCLK1   (LL_RCC_USART2_CLKSOURCE | 0U)                                                                                                    /*!< PCLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSI16   (LL_RCC_USART2_CLKSOURCE | (RCC_CCIPR2_USART2SEL >> RCC_CCIPR2_USART2SEL_Pos))                                                    /*!< HSI16 clock used as USART2 clock source */
#endif /* USART2 */

#define LL_RCC_USART3_CLKSOURCE_PCLK1   (LL_RCC_USART3_CLKSOURCE | 0U)                                                                                                    /*!< PCLK1 clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_HSI16   (LL_RCC_USART3_CLKSOURCE | (RCC_CCIPR1_USART3SEL >> RCC_CCIPR1_USART3SEL_Pos))                                                    /*!< HSI16 clock used as USART3 clock source */

#define LL_RCC_UART4_CLKSOURCE_PCLK1   (LL_RCC_UART4_CLKSOURCE | 0U)                                                                                                      /*!< PCLK1 clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_HSI16   (LL_RCC_UART4_CLKSOURCE | (RCC_CCIPR1_UART4SEL >> RCC_CCIPR1_UART4SEL_Pos))                                                        /*!< HSI16 clock used as UART4 clock source */

#define LL_RCC_UART5_CLKSOURCE_PCLK1   (LL_RCC_UART5_CLKSOURCE | 0U)                                                                                                      /*!< PCLK1 clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_HSI16   (LL_RCC_UART5_CLKSOURCE | (RCC_CCIPR1_UART5SEL >> RCC_CCIPR1_UART5SEL_Pos))                                                        /*!< HSI16 clock used as UART5 clock source */
/**
  * @}
  */

#if defined(USART2)
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_USART2_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_USART3_CLKSOURCE))
#else
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_USART3_CLKSOURCE))
#endif /* USART2 */

#define IS_LL_RCC_UART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_UART4_CLKSOURCE) || \
                                              ((__VALUE__) == LL_RCC_UART5_CLKSOURCE))

/** @defgroup RCC_LL_EC_I3C Peripheral I3Cx get clock source
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I3C1SEL_Pos << 16U) | ((RCC_CCIPR1_I3C1SEL_Msk >> RCC_CCIPR1_I3C1SEL_Pos) << 8U))     /*!< Mask to get I3C1SEL clock source      */
#define LL_RCC_I3C2_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I3C2SEL_Pos << 16U) | ((RCC_CCIPR1_I3C2SEL_Msk >> RCC_CCIPR1_I3C2SEL_Pos) << 8U))     /*!< Mask to get I3C2SEL clock source      */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_I3Cx_CLKSOURCE  Peripheral I3Cx clock source selection
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE_PCLK1     (LL_RCC_I3C1_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_MSIK      (LL_RCC_I3C1_CLKSOURCE | (RCC_CCIPR1_I3C1SEL >> RCC_CCIPR1_I3C1SEL_Pos))                                                       /*!< MSIK clock used as I3C1 clock source  */

#define LL_RCC_I3C2_CLKSOURCE_PCLK2     (LL_RCC_I3C2_CLKSOURCE | 0U)                                                                                                   /*!< PCLK2 clock used as I3C2 clock source */
#define LL_RCC_I3C2_CLKSOURCE_MSIK      (LL_RCC_I3C2_CLKSOURCE | (RCC_CCIPR1_I3C2SEL >> RCC_CCIPR1_I3C2SEL_Pos))                                                       /*!< MSIK clock used as I3C2 clock source  */
/**
  * @}
  */

#define IS_LL_RCC_I3C_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_I3C1_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_I3C2_CLKSOURCE))

/** @defgroup RCC_LL_EC_I2C Peripheral I2Cx get clock source
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | ((RCC_CCIPR1_I2C1SEL_Msk >> RCC_CCIPR1_I2C1SEL_Pos) << 8U))     /*!< Mask to get I2C1SEL clock source       */
#define LL_RCC_I2C2_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C2SEL_Pos << 16U) | ((RCC_CCIPR1_I2C2SEL_Msk >> RCC_CCIPR1_I2C2SEL_Pos) << 8U))     /*!< Mask to get I2C2SEL clock source       */
#define LL_RCC_I2C3_CLKSOURCE           ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | ((RCC_CCIPR3_I2C3SEL_Msk >> RCC_CCIPR3_I2C3SEL_Pos) << 8U))     /*!< Mask to get I2C3SEL clock source       */
#if defined(I2C4)
#define LL_RCC_I2C4_CLKSOURCE           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C4SEL_Pos << 16U) | ((RCC_CCIPR2_I2C4SEL_Msk >> RCC_CCIPR2_I2C4SEL_Pos) << 8U))     /*!< Mask to get I2C4SEL clock source       */
#endif /* I2C4 */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_I2Cx_CLKSOURCE  Peripheral I2Cx clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1     (LL_RCC_I2C1_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as I2C1 clock source  */
#define LL_RCC_I2C1_CLKSOURCE_MSIK      (LL_RCC_I2C1_CLKSOURCE | (RCC_CCIPR1_I2C1SEL >> RCC_CCIPR1_I2C1SEL_Pos))                                                       /*!< MSIK clock used as I2C1 clock source   */

#define LL_RCC_I2C2_CLKSOURCE_PCLK1     (LL_RCC_I2C2_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as I2C2 clock source  */
#define LL_RCC_I2C2_CLKSOURCE_MSIK      (LL_RCC_I2C2_CLKSOURCE | (RCC_CCIPR1_I2C2SEL >> RCC_CCIPR1_I2C2SEL_Pos))                                                       /*!< MSIK clock used as I2C2 clock source   */

#define LL_RCC_I2C3_CLKSOURCE_PCLK3     (LL_RCC_I2C3_CLKSOURCE | 0U)                                                                                                   /*!< PCLK3 clock used as I2C3 clock source  */
#define LL_RCC_I2C3_CLKSOURCE_MSIK      (LL_RCC_I2C3_CLKSOURCE | (RCC_CCIPR3_I2C3SEL >> RCC_CCIPR3_I2C3SEL_Pos))                                                       /*!< MSIK clock used as I2C3 clock source   */

#if defined(I2C4)
#define LL_RCC_I2C4_CLKSOURCE_PCLK1     (LL_RCC_I2C4_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as I2C4 clock source  */
#define LL_RCC_I2C4_CLKSOURCE_MSIK      (LL_RCC_I2C4_CLKSOURCE | (RCC_CCIPR2_I2C4SEL >> RCC_CCIPR2_I2C4SEL_Pos))                                                       /*!< MSIK clock used as I2C4 clock source   */
#endif /* I2C4 */
/**
  * @}
  */

#if defined(I2C4)
#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_I2C2_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_I2C3_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_I2C4_CLKSOURCE))
#else
#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_I2C2_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_I2C3_CLKSOURCE))
#endif /* I2C4 */

/** @defgroup RCC_LL_EC_SPI Peripheral SPIx get clock source
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | ((RCC_CCIPR1_SPI1SEL_Msk >> RCC_CCIPR1_SPI1SEL_Pos) << 8U))     /*!< Mask to get SPI1SEL clock source       */
#define LL_RCC_SPI2_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI2SEL_Pos << 16U) | ((RCC_CCIPR1_SPI2SEL_Msk >> RCC_CCIPR1_SPI2SEL_Pos) << 8U))     /*!< Mask to get SPI2SEL clock source       */
#define LL_RCC_SPI3_CLKSOURCE           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_SPI3SEL_Pos << 16U) | ((RCC_CCIPR2_SPI3SEL_Msk >> RCC_CCIPR2_SPI3SEL_Pos) << 8U))     /*!< Mask to get SPI3SEL clock source       */
#if defined(SPI4)
#define LL_RCC_SPI4_CLKSOURCE           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_SPI4SEL_Pos << 16U) | ((RCC_CCIPR2_SPI4SEL_Msk >> RCC_CCIPR2_SPI4SEL_Pos) << 8U))     /*!< Mask to get SPI4SEL clock source       */
#endif /* SPI4 */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_SPIx_CLKSOURCE  Peripheral SPIx clock source selection
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE_PCLK2     (LL_RCC_SPI1_CLKSOURCE | 0U)                                                                                                   /*!< PCLK2 clock used as SPI1 clock source  */
#define LL_RCC_SPI1_CLKSOURCE_MSIK      (LL_RCC_SPI1_CLKSOURCE | (RCC_CCIPR1_SPI1SEL >> RCC_CCIPR1_SPI1SEL_Pos))                                                       /*!< MSIK clock used as SPI1 clock source   */

#define LL_RCC_SPI2_CLKSOURCE_PCLK1     (LL_RCC_SPI2_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as SPI2 clock source  */
#define LL_RCC_SPI2_CLKSOURCE_MSIK      (LL_RCC_SPI2_CLKSOURCE | (RCC_CCIPR1_SPI2SEL >> RCC_CCIPR1_SPI2SEL_Pos))                                                       /*!< MSIK clock used as SPI2 clock source   */

#define LL_RCC_SPI3_CLKSOURCE_PCLK1     (LL_RCC_SPI3_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as SPI3 clock source  */
#define LL_RCC_SPI3_CLKSOURCE_MSIK      (LL_RCC_SPI3_CLKSOURCE | (RCC_CCIPR2_SPI3SEL >> RCC_CCIPR2_SPI3SEL_Pos))                                                       /*!< MSIK clock used as SPI3 clock source   */

#if defined(SPI4)
#define LL_RCC_SPI4_CLKSOURCE_PCLK1     (LL_RCC_SPI4_CLKSOURCE | 0U)                                                                                                   /*!< PCLK1 clock used as SPI4 clock source  */
#define LL_RCC_SPI4_CLKSOURCE_MSIK      (LL_RCC_SPI4_CLKSOURCE | (RCC_CCIPR2_SPI4SEL >> RCC_CCIPR2_SPI4SEL_Pos))                                                       /*!< MSIK clock used as SPI4 clock source   */
#endif /* SPI4 */
/**
  * @}
  */

#if defined(SPI4)
#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SPI1_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_SPI2_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_SPI3_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_SPI4_CLKSOURCE))
#else
#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SPI1_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_SPI2_CLKSOURCE) || \
                                             ((__VALUE__) == LL_RCC_SPI3_CLKSOURCE))
#endif /* SPI4 */


/** @defgroup RCC_LL_EC_LPTIM Peripheral LPTIMx get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | ((RCC_CCIPR3_LPTIM1SEL_Msk >> RCC_CCIPR3_LPTIM1SEL_Pos) << 8U))     /*!< Mask to get LPTIM1SEL clock source       */
#define LL_RCC_LPTIM2_CLKSOURCE         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | ((RCC_CCIPR1_LPTIM2SEL_Msk >> RCC_CCIPR1_LPTIM2SEL_Pos) << 8U))     /*!< Mask to get LPTIM2SEL clock source       */
#define LL_RCC_LPTIM34_CLKSOURCE        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM34SEL_Pos << 16U) | ((RCC_CCIPR3_LPTIM34SEL_Msk >> RCC_CCIPR3_LPTIM34SEL_Pos) << 8U))  /*!< Mask to get LPTIM34SEL clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_LPTIM_CLKSOURCE  Peripheral LPTIMx clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_MSIK    (LL_RCC_LPTIM1_CLKSOURCE | 0U)                                                                                                       /*!< MSIK clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI     (LL_RCC_LPTIM1_CLKSOURCE | (RCC_CCIPR3_LPTIM1SEL_0 >> RCC_CCIPR3_LPTIM1SEL_Pos))                                                     /*!< LSI clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM1_CLKSOURCE_HSI16   (LL_RCC_LPTIM1_CLKSOURCE | (RCC_CCIPR3_LPTIM1SEL_1 >> RCC_CCIPR3_LPTIM1SEL_Pos))                                                     /*!< HSI16 clock used as LPTIM1 clock source    */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE     (LL_RCC_LPTIM1_CLKSOURCE | ((RCC_CCIPR3_LPTIM1SEL_1 | RCC_CCIPR3_LPTIM1SEL_0) >> RCC_CCIPR3_LPTIM1SEL_Pos))                          /*!< LSE clock used as LPTIM1 clock source    */

#define LL_RCC_LPTIM2_CLKSOURCE_PCLK1   (LL_RCC_LPTIM2_CLKSOURCE | 0U)                                                                                                       /*!< PCLK1 clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_LSI     (LL_RCC_LPTIM2_CLKSOURCE | (RCC_CCIPR1_LPTIM2SEL_0 >> RCC_CCIPR1_LPTIM2SEL_Pos))                                                     /*!< LSI clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_HSI16   (LL_RCC_LPTIM2_CLKSOURCE | (RCC_CCIPR1_LPTIM2SEL_1 >> RCC_CCIPR1_LPTIM2SEL_Pos))                                                     /*!< HSI16 clock used as LPTIM2 clock source    */
#define LL_RCC_LPTIM2_CLKSOURCE_LSE     (LL_RCC_LPTIM2_CLKSOURCE | ((RCC_CCIPR1_LPTIM2SEL_1 | RCC_CCIPR1_LPTIM2SEL_0) >> RCC_CCIPR1_LPTIM2SEL_Pos))                          /*!< LSE clock used as LPTIM2 clock source    */

#define LL_RCC_LPTIM34_CLKSOURCE_MSIK   (LL_RCC_LPTIM34_CLKSOURCE | 0U)                                                                                                      /*!< MSIK clock used as LPTIM34 clock source  */
#define LL_RCC_LPTIM34_CLKSOURCE_LSI    (LL_RCC_LPTIM34_CLKSOURCE | (RCC_CCIPR3_LPTIM34SEL_0 >> RCC_CCIPR3_LPTIM34SEL_Pos))                                                  /*!< LSI clock used as LPTIM34 clock source  */
#define LL_RCC_LPTIM34_CLKSOURCE_HSI16  (LL_RCC_LPTIM34_CLKSOURCE | (RCC_CCIPR3_LPTIM34SEL_1 >> RCC_CCIPR3_LPTIM34SEL_Pos))                                                  /*!< HSI16 clock used as LPTIM34 clock source    */
#define LL_RCC_LPTIM34_CLKSOURCE_LSE    (LL_RCC_LPTIM34_CLKSOURCE | ((RCC_CCIPR3_LPTIM34SEL_1 | RCC_CCIPR3_LPTIM34SEL_0) >> RCC_CCIPR3_LPTIM34SEL_Pos))                      /*!< LSE clock used as LPTIM34 clock source    */
/**
  * @}
  */

#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_LPTIM34_CLKSOURCE))

/** @defgroup RCC_LL_EC_LPUART Peripheral LPUARTx get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPUART1SEL_Pos << 16U) | ((RCC_CCIPR3_LPUART1SEL_Msk >> RCC_CCIPR3_LPUART1SEL_Pos) << 8U))     /*!< Mask to get LPUART clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_LPUART1_CLKSOURCE  Peripheral LPUART1 clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK3    (LL_RCC_LPUART1_CLKSOURCE | 0U)                                                                                                       /*!< PCLK3 clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSI16    (LL_RCC_LPUART1_CLKSOURCE | (RCC_CCIPR3_LPUART1SEL_0 >> RCC_CCIPR3_LPUART1SEL_Pos))                                                   /*!< HSI16 clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_LSE      (LL_RCC_LPUART1_CLKSOURCE | (RCC_CCIPR3_LPUART1SEL_1 >> RCC_CCIPR3_LPUART1SEL_Pos))                                                   /*!< LSE clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_MSIK     (LL_RCC_LPUART1_CLKSOURCE | ((RCC_CCIPR3_LPUART1SEL_1 | RCC_CCIPR3_LPUART1SEL_0) >> RCC_CCIPR3_LPUART1SEL_Pos))                       /*!< MSIK clock used as LPUART1 clock source */
/**
  * @}
  */

#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE))

/** @defgroup RCC_LL_EC_SYSTICK Peripheral SYSTICK get clock source
  * @{
  */
#define LL_RCC_SYSTICK_CLKSOURCE        ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SYSTICKSEL_Pos << 16U) | ((RCC_CCIPR1_SYSTICKSEL_Msk >> RCC_CCIPR1_SYSTICKSEL_Pos) << 8U))     /*!< Mask to get SYSTICK clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_SYSTICK_CLKSOURCE Peripheral SYSTICK clock source selection
  * @{
  */
#define LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8  (LL_RCC_SYSTICK_CLKSOURCE | 0U )                                                                                                       /*!< HCLKDIV8 clock used as SYSTICK clock source */
#define LL_RCC_SYSTICK_CLKSOURCE_LSI       (LL_RCC_SYSTICK_CLKSOURCE | (RCC_CCIPR1_SYSTICKSEL_0 >> RCC_CCIPR1_SYSTICKSEL_Pos))                                                  /*!< LSI clock used as SYSTICK clock source      */
#define LL_RCC_SYSTICK_CLKSOURCE_LSE       (LL_RCC_SYSTICK_CLKSOURCE | (RCC_CCIPR1_SYSTICKSEL_1 >> RCC_CCIPR1_SYSTICKSEL_Pos))                                                  /*!< LSE clock used as SYSTICK clock source      */
/**
  * @}
  */

#define IS_LL_RCC_SYSTICK_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SYSTICK_CLKSOURCE))

/** @defgroup RCC_LL_EC_FDCAN Peripheral FDCAN get clock source
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_FDCANSEL_Pos << 16U) | ((RCC_CCIPR1_FDCANSEL_Msk >> RCC_CCIPR1_FDCANSEL_Pos) << 8U))       /*!< Mask to get FDCAN clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_FDCAN_CLKSOURCE Peripheral FDCAN clock source selection
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE_SYSCLK   (LL_RCC_FDCAN_CLKSOURCE | 0U)                                                                                                        /*!< SYSCLK clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_MSIK     (LL_RCC_FDCAN_CLKSOURCE | (RCC_CCIPR1_FDCANSEL >> RCC_CCIPR1_FDCANSEL_Pos))                                                        /*!< MSIK clock used as FDCAN clock source    */
/**
  * @}
  */

#define IS_LL_RCC_FDCAN_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_FDCAN_CLKSOURCE))

/** @defgroup RCC_LL_EC_ICLK Peripheral ICLK get clock source
  * @{
  */
#define LL_RCC_ICLK_CLKSOURCE            ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_ICLKSEL_Pos << 16U) | ((RCC_CCIPR1_ICLKSEL_Msk >> RCC_CCIPR1_ICLKSEL_Pos) << 8U))            /*!< Mask to get ICLK clock source       */
#define LL_RCC_SDMMC1_CLKSOURCE          LL_RCC_ICLK_CLKSOURCE
/**
  * @}
  */
/** @defgroup RCC_LL_EC_ICLK_CLKSOURCE Peripheral ICLK clock source selection
  * @{
  */
#define LL_RCC_ICLK_CLKSOURCE_HSI48      (LL_RCC_ICLK_CLKSOURCE | 0U)                                                                                                          /*!< HSI48 clock used as ICLK clock source   */
#define LL_RCC_ICLK_CLKSOURCE_MSIK       (LL_RCC_ICLK_CLKSOURCE | (RCC_CCIPR1_ICLKSEL_0 >> RCC_CCIPR1_ICLKSEL_Pos))                                                            /*!< MSIK clock used as ICLK clock source    */
#define LL_RCC_ICLK_CLKSOURCE_HSE        (LL_RCC_ICLK_CLKSOURCE | (RCC_CCIPR1_ICLKSEL_1 >> RCC_CCIPR1_ICLKSEL_Pos))                                                            /*!< HSE clock used as ICLK clock source     */
#define LL_RCC_ICLK_CLKSOURCE_SYSCLK     (LL_RCC_ICLK_CLKSOURCE | ((RCC_CCIPR1_ICLKSEL_1 | RCC_CCIPR1_ICLKSEL_0) >> RCC_CCIPR1_ICLKSEL_Pos))                                   /*!< SYSCLK clock used as ICLK clock source  */
/**
  * @}
  */

#define IS_LL_RCC_ICLK_CLKSOURCE(__VALUE__)   (((__VALUE__) == LL_RCC_ICLK_CLKSOURCE))
#define IS_LL_RCC_SDMMC_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SDMMC1_CLKSOURCE))

/** @defgroup RCC_LL_EC_USB1 Peripheral USB1 get clock source
  * @{
  */
#define LL_RCC_USB1_CLKSOURCE            ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_USB1SEL_Pos << 16U) | ((RCC_CCIPR1_USB1SEL_Msk >> RCC_CCIPR1_USB1SEL_Pos) << 8U))            /*!< Mask to get USB1 clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_USB1_USB1SOURCE Peripheral USB1 clock source selection
  * @{
  */
#define LL_RCC_USB1_CLKSOURCE_ICLK           (LL_RCC_USB1_CLKSOURCE | 0U)                                                                                                      /*!< ICLK clock used as USB1 clock source */
#define LL_RCC_USB1_CLKSOURCE_ICLKDIV2       (LL_RCC_USB1_CLKSOURCE | (RCC_CCIPR1_USB1SEL >> RCC_CCIPR1_USB1SEL_Pos))                                                          /*!< ICLK/2 clock used as USB1 clock source    */
/**
  * @}
  */

#define IS_LL_RCC_USB_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USB1_CLKSOURCE))

/** @defgroup RCC_LL_EC_TIMIC Peripheral TIMIC get clock source
  * @{
  */
#define LL_RCC_TIMIC_CLKSOURCE            ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_TIMICSEL_Pos << 16U) | ((RCC_CCIPR1_TIMICSEL_Msk >> RCC_CCIPR1_TIMICSEL_Pos) << 8U))        /*!< Mask to get TIMIC clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_TIM_INPUT_CAPTURE_CLOCKSource Peripheral TIMIC clock source selection
  * @{
  */
#define LL_RCC_TIMIC_CLKSOURCE_NONE                           (LL_RCC_TIMIC_CLKSOURCE | 0U)                                                                                                       /*!< No clock available for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSISDIV1024_MSISDIV4 (LL_RCC_TIMIC_CLKSOURCE | (RCC_CCIPR1_TIMICSEL_2 >> RCC_CCIPR1_TIMICSEL_Pos))                                                       /*!< HSI/256, MSIS/1024 and MSIS/4 generated and can be selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSISDIV1024_MSIKDIV4 (LL_RCC_TIMIC_CLKSOURCE | ((RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_0) >> RCC_CCIPR1_TIMICSEL_Pos))                             /*!< HSI/256, MSIS/1024 and MSIK/4 generated and can be selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSIKDIV1024_MSISDIV4 (LL_RCC_TIMIC_CLKSOURCE | ((RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1) >> RCC_CCIPR1_TIMICSEL_Pos))                             /*!< HSI/256, MSIK/1024 and MSIS/4 generated and can be selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSIKDIV1024_MSIKDIV4 (LL_RCC_TIMIC_CLKSOURCE | ((RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1 | RCC_CCIPR1_TIMICSEL_0) >> RCC_CCIPR1_TIMICSEL_Pos))     /*!< HSI/256, MSIK/1024 and MSIK/4 generated and can be selected for TIM16/TIM17 and LPTIM2 input capture */
/**
  * @}
  */

#define IS_LL_RCC_TIMIC_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_TIMIC_CLKSOURCE))

/** @defgroup RCC_LL_EC_ADF1 Peripheral ADF1 get clock source
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE             ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_ADF1SEL_Pos << 16U) | ((RCC_CCIPR2_ADF1SEL_Msk >> RCC_CCIPR2_ADF1SEL_Pos) << 8U))           /*!< Mask to get ADF1 clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_ADF1_CLKSOURCE  Peripheral ADF1 clock source selection
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE_SAI1       (LL_RCC_ADF1_CLKSOURCE | 0U)                                                                                                           /*!< SAI1 clock used as ADF1 clock source */
#define LL_RCC_ADF1_CLKSOURCE_AUDCLKIN   (LL_RCC_ADF1_CLKSOURCE | (RCC_CCIPR2_ADF1SEL_0 >> RCC_CCIPR2_ADF1SEL_Pos))                                                             /*!< input pin AUDIOCLK clock used as ADF1 clock source */
#define LL_RCC_ADF1_CLKSOURCE_MSIK       (LL_RCC_ADF1_CLKSOURCE | (RCC_CCIPR2_ADF1SEL_1 >> RCC_CCIPR2_ADF1SEL_Pos))                                                             /*!< MSIK clock used as ADF1 clock source */
/**
  * @}
  */

#define IS_LL_RCC_ADF_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_ADF1_CLKSOURCE))

/** @defgroup RCC_LL_EC_SAI1 Peripheral SAI1 get clock source
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE             ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_SAI1SEL_Pos << 16U) | ((RCC_CCIPR2_SAI1SEL_Msk >> RCC_CCIPR2_SAI1SEL_Pos) << 8U))           /*!< Mask to get SAI1 clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_SAI1_CLKSOURCE  Peripheral SAI1 clock source selection
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE_MSIK        (LL_RCC_SAI1_CLKSOURCE | 0U)                                                                                                         /*!< MSIK clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_AUDCLKIN    (LL_RCC_SAI1_CLKSOURCE | (RCC_CCIPR2_SAI1SEL_0 >> RCC_CCIPR2_SAI1SEL_Pos))                                                           /*!< External input clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_HSE         (LL_RCC_SAI1_CLKSOURCE | (RCC_CCIPR2_SAI1SEL_1>> RCC_CCIPR2_SAI1SEL_Pos))                                                            /*!< HSE clock used as SAI1 clock source */
/**
  * @}
  */

#define IS_LL_RCC_SAI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SAI1_CLKSOURCE))

/** @defgroup RCC_LL_EC_RNG Peripheral RNG get clock source
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE              ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_RNGSEL_Pos << 16U) | ((RCC_CCIPR2_RNGSEL_Msk >> RCC_CCIPR2_RNGSEL_Pos) << 8U))              /*!< Mask to get RNG clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_RNG_CLKSOURCE  Peripheral RNG clock source selection
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE_HSI48        (LL_RCC_RNG_CLKSOURCE | 0U)                                                                                                          /*!< HSI48 clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_MSIK         (LL_RCC_RNG_CLKSOURCE | (RCC_CCIPR2_RNGSEL >> RCC_CCIPR2_RNGSEL_Pos))                                                                /*!< MSIK clock used as RNG clock source */
/**
  * @}
  */

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_RNG_CLKSOURCE))

/** @defgroup RCC_LL_EC_ADCDAC_CLKPRESCALER Peripheral ADCDAC get kernel clock prescaler
  * @{
  */
#define LL_RCC_ADCDAC_CLKPRESCALER        ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_ADCDACPRE_Pos << 16U) | ((RCC_CCIPR2_ADCDACPRE_Msk >> RCC_CCIPR2_ADCDACPRE_Pos) << 8U))    /*!< Mask to get ADCDAC kernel clock prescaler  */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_ADCDAC_CLKPRESCALER_SELECTION  Peripheral ADCDAC clock prescaler selection
  * @{
  */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK             (LL_RCC_ADCDAC_CLKPRESCALER | 0U)                                                                                                                                /*!< ICLK clock used as ADCDAC clock prescaler     */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_2       (LL_RCC_ADCDAC_CLKPRESCALER | (RCC_CCIPR2_ADCDACPRE_0 >> RCC_CCIPR2_ADCDACPRE_Pos))                                                                              /*!< ICLK/2 clock used as ADCDAC clock prescaler   */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_4       (LL_RCC_ADCDAC_CLKPRESCALER | (RCC_CCIPR2_ADCDACPRE_3 >> RCC_CCIPR2_ADCDACPRE_Pos))                                                                              /*!< ICLK/4 clock used as ADCDAC clock prescaler   */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_8       (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_0) >> RCC_CCIPR2_ADCDACPRE_Pos))                                                   /*!< ICLK/8 clock used as ADCDAC clock prescaler   */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_16      (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_1) >> RCC_CCIPR2_ADCDACPRE_Pos))                                                   /*!< ICLK/16 clock used as ADCDAC clock prescaler  */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_32      (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_1 | RCC_CCIPR2_ADCDACPRE_0) >> RCC_CCIPR2_ADCDACPRE_Pos))                          /*!< ICLK/32 clock used as ADCDAC clock prescaler  */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_64      (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2) >> RCC_CCIPR2_ADCDACPRE_Pos))                                                   /*!< ICLK/64 clock used as ADCDAC clock prescaler  */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_128     (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_0) >> RCC_CCIPR2_ADCDACPRE_Pos))                          /*!< ICLK/128 clock used as ADCDAC clock prescaler */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_256     (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_1) >> RCC_CCIPR2_ADCDACPRE_Pos))                          /*!< ICLK/256 clock used as ADCDAC clock prescaler */
#define LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_512     (LL_RCC_ADCDAC_CLKPRESCALER | ((RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_1 | RCC_CCIPR2_ADCDACPRE_0) >> RCC_CCIPR2_ADCDACPRE_Pos)) /*!< ICLK/512 clock used as ADCDAC clock prescaler */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADCDAC Peripheral ADCDAC get clock source
  * @{
  */
#define LL_RCC_ADCDAC_CLKSOURCE            ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_ADCDACSEL_Pos << 16U) | ((RCC_CCIPR2_ADCDACSEL_Msk >> RCC_CCIPR2_ADCDACSEL_Pos) << 8U))    /*!< Mask to get ADCDAC clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_ADCDAC_CLKSOURCE  Peripheral ADCDAC clock source selection
  * @{
  */
#define LL_RCC_ADCDAC_CLKSOURCE_HCLK       (LL_RCC_ADCDAC_CLKSOURCE | 0U)                                                                                                      /*!< HCLK clock used as ADCDAC clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_HSE        (LL_RCC_ADCDAC_CLKSOURCE | (RCC_CCIPR2_ADCDACSEL_0 >> RCC_CCIPR2_ADCDACSEL_Pos))                                                    /*!< HSE clock used as ADCDAC clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_MSIK       (LL_RCC_ADCDAC_CLKSOURCE | (RCC_CCIPR2_ADCDACSEL_1 >> RCC_CCIPR2_ADCDACSEL_Pos))                                                    /*!< MSI clock used as ADCDAC clock source */
/**
  * @}
  */

#define IS_LL_RCC_ADCDAC_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_ADCDAC_CLKSOURCE))

/** @defgroup RCC_LL_EC_DAC1 Peripheral DAC1 get clock source
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_DAC1SHSEL_Pos << 16U) | ((RCC_CCIPR2_DAC1SHSEL_Msk >> RCC_CCIPR2_DAC1SHSEL_Pos) << 8U))   /*!< Mask to get DAC1 sample & hold clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_DAC1SH_CLKSOURCE  Peripheral DAC1 sample & hold clock source selection
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE_LSE       (LL_RCC_DAC1SH_CLKSOURCE | 0U)                                                                                                         /*!< LSE clock used as DAC1 clock source */
#define LL_RCC_DAC1SH_CLKSOURCE_LSI       (LL_RCC_DAC1SH_CLKSOURCE | (RCC_CCIPR2_DAC1SHSEL >> RCC_CCIPR2_DAC1SHSEL_Pos))                                                         /*!< LSI clock used as DAC1 clock source */
/**
  * @}
  */

#define IS_LL_RCC_DAC1SH_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_DAC1SH_CLKSOURCE))

/** @defgroup RCC_LL_EC_OCTOSPI Peripheral OCTOSPI get clock source
  * @{
  */
#define LL_RCC_OCTOSPI_CLKSOURCE          ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_OCTOSPISEL_Pos << 16U) | ((RCC_CCIPR2_OCTOSPISEL_Msk >> RCC_CCIPR2_OCTOSPISEL_Pos) << 8U))  /*!< Mask to get OCTOSPI clock source       */
/**
  * @}
  */
/** @defgroup RCC_LL_EC_OCTOSPI_CLKSOURCE  Peripheral OCTOSPI clock source selection
  * @{
  */
#define LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK   (LL_RCC_OCTOSPI_CLKSOURCE | 0U)                                                                                                      /*!< SYSCLK clock used as OCTOSPI clock source */
#define LL_RCC_OCTOSPI_CLKSOURCE_MSIK     (LL_RCC_OCTOSPI_CLKSOURCE | (RCC_CCIPR2_OCTOSPISEL>> RCC_CCIPR2_OCTOSPISEL_Pos))                                                     /*!< MSIK clock used as OCTOSPI clock source */
/**
  * @}
  */

#define IS_LL_RCC_OCTOSPI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_OCTOSPI_CLKSOURCE))


/** @defgroup RCC_LL_EC_EPODBOOST_CLKSOURCE  EPOD clock source selection
  * @{
  */
#define LL_RCC_EPODBOOSTCLKSRCE_BYPASS          0U
#define LL_RCC_EPODBOOSTCLKSRCE_MSIS            RCC_CFGR4_BOOSTSEL_0
#define LL_RCC_EPODBOOSTCLKSRCE_HSI16           RCC_CFGR4_BOOSTSEL_1
#define LL_RCC_EPODBOOSTCLKSRCE_HSE             ( RCC_CFGR4_BOOSTSEL_1 | RCC_CFGR4_BOOSTSEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_EPODBOOST_CLKPRESCAL  EPOD clock prescaler
  * @{
  */
#define LL_RCC_EPODBOOSTCLKPRESCAL_1            0U
#define LL_RCC_EPODBOOSTCLKPRESCAL_2            RCC_CFGR4_BOOSTDIV_0
#define LL_RCC_EPODBOOSTCLKPRESCAL_4            RCC_CFGR4_BOOSTDIV_1
#define LL_RCC_EPODBOOSTCLKPRESCAL_6            (RCC_CFGR4_BOOSTDIV_1 | RCC_CFGR4_BOOSTDIV_0)
#define LL_RCC_EPODBOOSTCLKPRESCAL_8            RCC_CFGR4_BOOSTDIV_2
#define LL_RCC_EPODBOOSTCLKPRESCAL_10           (RCC_CFGR4_BOOSTDIV_2 | RCC_CFGR4_BOOSTDIV_0)
#define LL_RCC_EPODBOOSTCLKPRESCAL_12           (RCC_CFGR4_BOOSTDIV_2 | RCC_CFGR4_BOOSTDIV_1)
#define LL_RCC_EPODBOOSTCLKPRESCAL_14           (RCC_CFGR4_BOOSTDIV_2 | RCC_CFGR4_BOOSTDIV_1 | RCC_CFGR4_BOOSTDIV_0)
#define LL_RCC_EPODBOOSTCLKPRESCAL_16           (RCC_CFGR4_BOOSTDIV_3)
/**
  * @}
  */


/** @defgroup RCC_LL_EF_Security_Services Security Services
  * @note Only available when system implements security (TZEN=1)
  * @{
  */
#define LL_RCC_ALL_NSEC                 0U                        /*!< No security on RCC resources (default) */
#define LL_RCC_ALL_SEC                  (RCC_SECCFGR_HSISEC    |\
                                         RCC_SECCFGR_HSESEC    |\
                                         RCC_SECCFGR_MSISEC    |\
                                         RCC_SECCFGR_LSISEC    |\
                                         RCC_SECCFGR_LSESEC    |\
                                         RCC_SECCFGR_SYSCLKSEC |\
                                         RCC_SECCFGR_PRESCSEC  |\
                                         RCC_SECCFGR_BOOSTSEC  |\
                                         RCC_SECCFGR_ICLKSEC   |\
                                         RCC_SECCFGR_HSI48SEC  |\
                                         RCC_SECCFGR_RMVFSEC)     /*!< Security on all RCC resources          */


#define LL_RCC_HSI_SEC                  RCC_SECCFGR_HSISEC      /*!< HSI clock configuration secure-only access */
#define LL_RCC_HSI_NSEC                 0U                      /*!< HSI clock configuration secure/non-secure access */
#define LL_RCC_HSE_SEC                  RCC_SECCFGR_HSESEC      /*!< HSE clock configuration secure-only access */
#define LL_RCC_HSE_NSEC                 0U                      /*!< HSE clock configuration secure/non-secure access */
#define LL_RCC_MSI_SEC                  RCC_SECCFGR_MSISEC      /*!< MSI clock configuration secure-only access */
#define LL_RCC_MSI_NSEC                 0U                      /*!< MSI clock configuration secure/non-secure access */
#define LL_RCC_LSI_SEC                  RCC_SECCFGR_LSISEC      /*!< LSI clock configuration secure-only access */
#define LL_RCC_LSI_NSEC                 0U                      /*!< LSI clock configuration secure/non-secure access */
#define LL_RCC_LSE_SEC                  RCC_SECCFGR_LSESEC      /*!< LSE clock configuration secure-only access */
#define LL_RCC_LSE_NSEC                 0U                      /*!< LSE clock configuration secure/non-secure access */
#define LL_RCC_SYSCLK_SEC               RCC_SECCFGR_SYSCLKSEC   /*!< SYSCLK clock; STOPWUCK and MCO output configuration secure-only access */
#define LL_RCC_SYSCLK_NSEC              0U                      /*!< SYSCLK clock; STOPWUCK and MCO output configuration secure/non-secure access */
#define LL_RCC_PRESCALERS_SEC           RCC_SECCFGR_PRESCSEC    /*!< AHBx/APBx prescaler configuration secure-only access */
#define LL_RCC_PRESCALERS_NSEC          0U                      /*!< AHBx/APBx prescaler configuration secure/non-secure access */
#define LL_RCC_BOOST_SEC                RCC_SECCFGR_BOOSTSEC    /*!< BOOST clock configuration secure-only access */
#define LL_RCC_BOOST_NSEC               0U                      /*!< BOOST clock configuration secure/non-secure access */
#define LL_RCC_ICLK_SEC                 RCC_SECCFGR_ICLKSEC     /*!< ICLK clock configuration secure-only access */
#define LL_RCC_ICLK_NSEC                0U                      /*!< ICLK clock configuration secure/non-secure access */
#define LL_RCC_HSI48_SEC                RCC_SECCFGR_HSI48SEC    /*!< HSI48 clock configuration secure-only access */
#define LL_RCC_HSI48_NSEC               0U                      /*!< HSI48 clock configuration secure/non-secure access */
#define LL_RCC_RESET_FLAGS_SEC          RCC_SECCFGR_RMVFSEC     /*!< Remove reset flag secure-only access */
#define LL_RCC_RESET_FLAGS_NSEC         0U                      /*!< Remove reset flag secure/non-secure access */
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


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
  * @{
  */


/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */


/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on HSE/MSIS/HSI16)
  * @param  __AHBPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_512
  * @retval HCLK clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK_FREQ(__SYSCLKFREQ__, __AHBPRESCALER__) \
  ((__SYSCLKFREQ__) >> (AHBPrescTable[((__AHBPRESCALER__) & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (ABP1)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB1PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APB1PRESCALER__) \
  ((__HCLKFREQ__) >> (APBPrescTable[((__APB1PRESCALER__) & RCC_CFGR2_PPRE1) >> RCC_CFGR2_PPRE1_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK2 frequency (ABP2)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB2PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_16
  * @retval PCLK2 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK2_FREQ(__HCLKFREQ__, __APB2PRESCALER__) \
  ((__HCLKFREQ__) >> (APBPrescTable[((__APB2PRESCALER__) & RCC_CFGR2_PPRE2) >> RCC_CFGR2_PPRE2_Pos]))


/**
  * @brief  Helper macro to calculate the PCLK3 frequency (ABP3)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB3PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_16
  * @retval PCLK3 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK3_FREQ(__HCLKFREQ__, __APB3PRESCALER__) \
  ((__HCLKFREQ__) >> (APBPrescTable[((__APB3PRESCALER__) & RCC_CFGR3_PPRE3) >> RCC_CFGR3_PPRE3_Pos]))

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
  * @brief  Check if HSE is enabled
  * @rmtoll CR           HSEON        LL_RCC_HSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEON) == RCC_CR_HSEON) ? 1UL : 0UL);
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
  * @brief  Enable the Clock Security System.
  * @rmtoll CR           HSECSSON         LL_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @brief  Check if HSE CSS is enabled
  * @rmtoll CR           HSECSSON        LL_RCC_HSE_IsEnabledCSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabledCSS(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSECSSON) == RCC_CR_HSECSSON) ? 1UL : 0UL);
}

/**
  * @brief  Enable bypass of the oscillator with an external clock.
  * @rmtoll CR           HSEBYP         LL_RCC_HSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Disable bypass the oscillator with an external clock.
  * @rmtoll CR           HSEBYP         LL_RCC_HSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Check if HSE bypass is enabled
  * @rmtoll CR           HSEBYP        LL_RCC_HSE_IsEnabledBypass
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabledBypass(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEBYP) == RCC_CR_HSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Set external clock mode in bypass mode.
  * @rmtoll CR           HSEEXT         LL_RCC_HSE_SetClockMode
  * @param  ClockMode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_SetClockMode(uint32_t ClockMode)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSEEXT, ClockMode);
}

/**
  * @brief  Get external clock mode in bypass mode.
  * @rmtoll CR           HSEEXT         LL_RCC_HSE_GetClockMode
  * @retval  Return can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetClockMode(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSEEXT));
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
  * @brief  Check if HSI is enabled
  * @rmtoll CR           HSION        LL_RCC_HSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSION) == RCC_CR_HSION) ? 1UL : 0UL);
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
  MODIFY_REG(RCC->ICSCR3, RCC_ICSCR3_HSITRIM, (Value << RCC_ICSCR3_HSITRIM_Pos));
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
  * @brief  Enable HSI48 oscillator
  * @rmtoll CR           HSI48ON         LL_RCC_HSI48_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Disable HSI48 oscillator
  * @rmtoll CR           HSI48ON         LL_RCC_HSI48_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Check if HSI48 is enabled
  * @rmtoll CR           HSI48ON        LL_RCC_HSI48_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSI48ON) == RCC_CR_HSI48ON) ? 1UL : 0UL);
}


/**
  * @brief  Check if HSI48 clock is ready
  * @rmtoll CR           HSI48RDY        LL_RCC_HSI48_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSI48RDY) == RCC_CR_HSI48RDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI48 Calibration value
  * @note  Read value initialized at startup with the factory-programmed HSI48 calibration trim value
  * @rmtoll CRRCR       HSI48CAL        LL_RCC_HSI48_GetCalibration
  * @retval Between Min_Data = 0 and Max_Data = 512
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48CAL) >> RCC_CRRCR_HSI48CAL_Pos);
}


/**
  * @}
  */


/** @defgroup RCC_LL_EF_MSI MSI
  * @{
  */

/**
  * @brief  Set MSI clock range with (MSISDIV[1:0] and MSIKDIV[1:0])
  * @note Set the MSIS and MSIK clocks range with (MSISDIV[1:0] and MSIKDIV[1:0])
  *       instead of (MSISDIVS[1:0] and MSIKDIVS[1:0])
  * @rmtoll ICSCR1        MSIRGSEL        LL_RCC_MSI_SetMSIxClockRange
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetMSIxClockRange(void)
{
  SET_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL);
}

/**
  * @brief  Get MSI clock range
  * @rmtoll ICSCR1        MSIRGSEL        LL_RCC_MSI_GetMSIxClockRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSI_CLOCK_RANGE_MSIXDIVS
  *         @arg @ref LL_RCC_MSI_CLOCK_RANGE_MSIXDIV
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetMSIxClockRange(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL));
}

/**
  * @brief  Set MSI bias mode
  * @note Set MSI bias mode - continuous mode maintains the output clocks accuracy but lead to higher consumption
  * @rmtoll ICSCR1        MSIBIAS        LL_RCC_MSI_SetBiasMode
  * @param  MSIBiasMode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSI_BIAS_MODE_CONTINUOUS
  *         @arg @ref LL_RCC_MSI_BIAS_MODE_SAMPLING
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetBiasMode(uint32_t MSIBiasMode)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIBIAS, MSIBiasMode);
}

/**
  * @brief  Get MSI bias mode
  * @rmtoll ICSCR1        MSIBIAS        LL_RCC_MSI_GetBiasMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSI_BIAS_MODE_CONTINUOUS
  *         @arg @ref LL_RCC_MSI_BIAS_MODE_SAMPLING
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetBiasMode(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIBIAS));
}

/**
  * @brief  Enable MSIS oscillator
  * @rmtoll CR           MSISON         LL_RCC_MSIS_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIS_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSISON);
}

/**
  * @brief  Disable MSIS oscillator
  * @rmtoll CR           MSISON         LL_RCC_MSIS_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIS_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSISON);
}

/**
  * @brief  Check if MSIS is enabled or not
  * @rmtoll CR    MSISON        LL_RCC_MSIS_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSISON) == RCC_CR_MSISON) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSIS clock is ready
  * @rmtoll CR           MSISRDY        LL_RCC_MSIS_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSISRDY) == RCC_CR_MSISRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set MSIS clock source
  * @note  Select the RC oscillator used to generate MSIS clock
  * @rmtoll ICSCR1        MSISSEL        LL_RCC_MSIS_SetClockSource
  * @param  MSISClockSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC0 (96MHz)
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC1 (24MHz)
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIS_SetClockSource(uint32_t MSISClockSource)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSISSEL, MSISClockSource);
}

/**
  * @brief  Get MSIS clock source
  * @rmtoll ICSCR1        MSISSEL        LL_RCC_MSIS_GetClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC0 (96MHz)
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC1 (24MHz)
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_GetClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSISSEL));
}

/**
  * @brief  Set MSIS clock division
  * @note  Select the MSIS division factor
  *        if MSIS clock source is LL_RCC_MSIS_CLOCK_SOURCE_RC0
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_1: MSIRC0 /1 is selected for MSIS (range 0 around 96 MHz)
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2: MSIRC0 /2 is selected for MSIS (range 1 around 48 MHz)
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_4: MSIRC0 /4 is selected for MSIS (range 2 around 24 MHz)
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_8: MSIRC0 /8 is selected for MSIS (range 3 around 12 MHz)
  *        if MSIS clock source is LL_RCC_MSIS_CLOCK_SOURCE_RC1
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_1: MSIRC1 /1 is selected for MSIS (range 4 around 24 MHz)
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2: MSIRC1 /2 is selected for MSIS (range 5 around 12 MHz)
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_4: MSIRC1 /4 is selected for MSIS (range 6 around 6 MHz)
  *          LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_8: MSIRC1 /8 is selected for MSIS (range 7 around 3 MHz)
  * @rmtoll ICSCR1        MSISDIV        LL_RCC_MSIS_SetClockDivision
  * @param  MSISClockDivision This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_1
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_4
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIS_SetClockDivision(uint32_t MSISClockDivision)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSISDIV, MSISClockDivision);
}

/**
  * @brief  Get MSIS clock division
  * @rmtoll ICSCR1        MSISDIV        LL_RCC_MSIS_GetClockDivision
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_1
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_4
  *         @arg @ref LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_GetClockDivision(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSISDIV));
}

/**
  * @brief  Set MSIS oscillator division after Standby mode
  * @note Set MSIS frequency at Standby mode exit and until MSIRGSEL is set
  * @rmtoll CSR        MSISDIVS        LL_RCC_MSIS_SetFreqAfterStandby
  * @param  MSISdivs This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISDIVS_RANGE_5
  *         @arg @ref LL_RCC_MSISDIVS_RANGE_6
  *         @arg @ref LL_RCC_MSISDIVS_RANGE_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIS_SetFreqAfterStandby(uint32_t MSISdivs)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_MSISDIVS, MSISdivs);
}

/**
  * @brief  Get MSIS oscillator division after Standby mode
  * @rmtoll CSR        MSISDIVS        LL_RCC_MSIS_GetFreqAfterStandby
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSISDIVS_RANGE_5
  *         @arg @ref LL_RCC_MSISDIVS_RANGE_6
  *         @arg @ref LL_RCC_MSISDIVS_RANGE_7
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_GetFreqAfterStandby(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSISDIVS));
}

/**
  * @brief  Enable MSI for some peripheral kernels
  * @rmtoll CR           MSIKERON         LL_RCC_MSIKER_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIKER_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIKERON);
}

/**
  * @brief  Disable MSI for some peripheral kernels
  * @rmtoll CR           MSIKERON         LL_RCC_MSIKER_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIKER_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIKERON);
}

/**
  * @brief  Check if MSIKER is enabled or not
  * @rmtoll CR    MSIKERON        LL_RCC_MSIKER_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_MSIKER_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIKERON) == RCC_CR_MSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSIK oscillator
  * @rmtoll CR           MSIKON         LL_RCC_MSIK_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIK_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIKON);
}

/**
  * @brief  Disable MSIK oscillator
  * @rmtoll CR           MSIKON         LL_RCC_MSIK_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIK_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIKON);
}

/**
  * @brief  Check if MSIK is enabled or not
  * @rmtoll CR    MSIKON        LL_RCC_MSIK_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIKON) == RCC_CR_MSIKON) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSIK clock is ready
  * @rmtoll CR           MSIKRDY        LL_RCC_MSIK_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIKRDY) == RCC_CR_MSIKRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set MSIK clock source
  * @note  Select the RC oscillator used to generate MSIK clock
  * @rmtoll ICSCR1        MSIKSEL        LL_RCC_MSIK_SetClockSource
  * @param  MSIKClockSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC0 (96MHz)
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC1 (24MHz)
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIK_SetClockSource(uint32_t MSIKClockSource)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIKSEL, MSIKClockSource);
}

/**
  * @brief  Get MSIK clock source
  * @rmtoll ICSCR1        MSIKSEL        LL_RCC_MSIK_GetClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC0 (96MHz)
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC1 (24MHz)
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_GetClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIKSEL));
}

/**
  * @brief  Set MSIK clock division
  * @note  Select the MSIK division factor
  *        if MSIK clock source is LL_RCC_MSIK_CLOCK_SOURCE_RC0
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_1: MSIRC0 /1 is selected for MSIK (range 0 around 96 MHz)
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_2: MSIRC0 /2 is selected for MSIK (range 1 around 48 MHz)
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_4: MSIRC0 /4 is selected for MSIK (range 2 around 24 MHz)
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_8: MSIRC0 /8 is selected for MSIK (range 3 around 12 MHz)
  *        if MSIK clock source is LL_RCC_MSIK_CLOCK_SOURCE_RC1
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_1: MSIRC1 /1 is selected for MSIK (range 4 around 24 MHz)
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_2: MSIRC1 /2 is selected for MSIK (range 5 around 12 MHz)
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_4: MSIRC1 /4 is selected for MSIK (range 6 around 6 MHz)
  *          LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_8: MSIRC1 /8 is selected for MSIK (range 7 around 3 MHz)
  * @rmtoll ICSCR1        MSIKDIV        LL_RCC_MSIK_SetClockDivision
  * @param  MSIKClockDivision This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_1
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_2
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_4
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIK_SetClockDivision(uint32_t MSIKClockDivision)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIKDIV, MSIKClockDivision);
}

/**
  * @brief  Get MSIK clock division
  * @rmtoll ICSCR1        MSIKDIV        LL_RCC_MSIK_GetClockDivision
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_1
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_2
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_4
  *         @arg @ref LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_GetClockDivision(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIKDIV));
}

/**
  * @brief  Set MSIK oscillator division after Standby mode
  * @note Set MSIK frequency at Standby mode exit and until MSIRGSEL is set
  * @rmtoll CSR        MSIKDIVS        LL_RCC_MSIK_SetFreqAfterStandby
  * @param  MSIKdivs This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIKDIVS_RANGE_5
  *         @arg @ref LL_RCC_MSIKDIVS_RANGE_6
  *         @arg @ref LL_RCC_MSIKDIVS_RANGE_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSIK_SetFreqAfterStandby(uint32_t MSIKdivs)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_MSIKDIVS, MSIKdivs);
}

/**
  * @brief  Get MSIK oscillator division after Standby mode
  * @rmtoll CSR        MSIKDIVS        LL_RCC_MSIK_GetFreqAfterStandby
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIKDIVS_RANGE_5
  *         @arg @ref LL_RCC_MSIKDIVS_RANGE_6
  *         @arg @ref LL_RCC_MSIKDIVS_RANGE_7
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_GetFreqAfterStandby(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSIKDIVS));
}

/**
  * @brief  Set MSIRCx PLL-mode HSE input division
  * @note Divide HSE input clock when used by MSI in PLL-mode. MSI high speed input clock must be  16 Mhz.
  * @rmtoll ICSCR1        MSIHSINDIV        LL_RCC_MSI_RCx_SetPLLmodeHSEInputDiv
  * @param  HSEInputDiv This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRCx_PLLMODE_INPUT_HSE
  *         @arg @ref LL_RCC_MSIRCx_PLLMODE_INPUT_HSE_DIV_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RCx_SetPLLmodeHSEInputDiv(uint32_t HSEInputDiv)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIHSINDIV, HSEInputDiv);
}

/**
  * @brief  Get MSIRCx PLL-mode HSE input division
  * @rmtoll ICSCR1        MSIHSINDIV        LL_RCC_MSI_RCx_GetPLLmodeHSEInputDiv
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIRCx_PLLMODE_INPUT_HSE
  *         @arg @ref LL_RCC_MSIRCx_PLLMODE_INPUT_HSE_DIV_2
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RCx_GetPLLmodeHSEInputDiv(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIHSINDIV));
}


/**
  * @brief  Enable MSI RC0  PLL-mode
  * @rmtoll CR           MSIPLL0EN         LL_RCC_MSI_RC0_PLLmode_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC0_PLLmode_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLL0EN);
}

/**
  * @brief  Disable MSI RC0  PLL-mode
  * @rmtoll CR           MSIPLL0EN         LL_RCC_MSI_RC0_PLLmode_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC0_PLLmode_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLL0EN);
}

/**
  * @brief  Check if MSI RC0  PLL-mode is enabled or not
  * @rmtoll CR    MSIPLL1EN        LL_RCC_MSI_RC0_PLLmode_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC0_PLLmode_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIPLL0EN) == RCC_CR_MSIPLL0EN) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI RC0 PLL mode is ready
  * @rmtoll CR           MSIPLL0RDY        LL_RCC_MSI_RC0_PLLmode_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC0_PLLmode_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIPLL0RDY) == RCC_CR_MSIPLL0RDY) ? 1UL : 0UL);
}

/**
  * @brief  Set MSIRC0 PLL-mode input clock
  * @note LSE or HSE must be enabled and ready before selecting this oscillator as MSIRC0 input clock
  * @rmtoll ICSCR1        MSIPLL0SEL        LL_RCC_MSI_RC0_SetPLLInputClk
  * @param  MSIPLL0sel This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIPLL0SEL_LSE
  *         @arg @ref LL_RCC_MSIPLL0SEL_HSE_OR_HSEDIV2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC0_SetPLLInputClk(uint32_t MSIPLL0sel)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIPLL0SEL, MSIPLL0sel);
}

/**
  * @brief  Get MSIRC0 PLL-mode input clock
  * @rmtoll ICSCR1        MSIPLL0SEL        LL_RCC_MSI_RC0_GetPLLInputClk
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIPLL0SEL_LSE
  *         @arg @ref LL_RCC_MSIPLL0SEL_HSE_OR_HSEDIV2
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC0_GetPLLInputClk(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIPLL0SEL));
}

/**
  * @brief  MSI RC0 PLL mode fast startup
  * @rmtoll CR           MSIPLL0FAST         LL_RCC_MSI_RC0_PLLmode_FastStartup
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC0_PLLmode_FastStartup(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLL0FAST);
}

/**
  * @brief  MSI RC0 PLL mode normal startup
  * @rmtoll CR           MSIPLL0FAST         LL_RCC_MSI_RC0_PLLmode_NormalStartup
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC0_PLLmode_NormalStartup(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLL0FAST);
}

/**
  * @brief  Get MSIRC0 PLL-mode startup status
  * @rmtoll CR        MSIPLL0FAST        LL_RCC_MSI_RC0_PLLmode_GetStartupStatus
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIPLL0_STARTUP_NORMAL
  *         @arg @ref LL_RCC_MSIPLL0_STARTUP_FAST
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC0_PLLmode_GetStartupStatus(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_MSIPLL0FAST));
}


/**
  * @brief  Set MSI clock trimming for ranges 0 to 3
  * @note Additional user-programmable trimming value that is added to the factory-programmed
  *       calibration trim value MSIRC0[5:0] bits.
  * @rmtoll ICSCR2        MSITRIM0        LL_RCC_MSI_RC0_SetTrimming
  * @param  TrimValue
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC0_SetTrimming(uint32_t TrimValue)
{
  MODIFY_REG(RCC->ICSCR2, RCC_ICSCR2_MSITRIM0, (TrimValue << RCC_ICSCR2_MSITRIM0_Pos));
}

/**
  * @brief  Get MSI clock trimming for ranges 0 to 3
  * @note Additional user-programmable trimming value that is added to the factory-programmed
  *       calibration trim value MSIRC0[5:0] bits.
  * @rmtoll ICSCR2        MSITRIM0        LL_RCC_MSI_RC0_GetTrimming
  * @retval TrimValue
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC0_GetTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR2, RCC_ICSCR2_MSITRIM0) >> RCC_ICSCR2_MSITRIM0_Pos);
}

/**
  * @brief  Get MSIRC0 clock calibration for MSI ranges 0 to 3
  * @note Field initialized at startup with the factory-programmed MSIRC0 calibration trim value for ranges 0 to 3.
  *       When MSITRIM0 is written, MSICAL0 is updated with the sum of MSITRIM0[5:0] and the
  *       factory-programmed calibration trim value MSIRC0[5:0].
  * @rmtoll ICSCR1        MSICAL0        LL_RCC_MSI_RC0_GetCalibration
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC0_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSICAL0) >> RCC_ICSCR1_MSICAL0_Pos);
}

/**
  * @brief  Enable MSI RC1  PLL-mode
  * @rmtoll CR           MSIPLL1EN         LL_RCC_MSI_RC1_PLLmode_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_PLLmode_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLL1EN);
}

/**
  * @brief  Disable MSI RC1  PLL-mode
  * @rmtoll CR           MSIPLL1EN         LL_RCC_MSI_RC1_PLLmode_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_PLLmode_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLL1EN);
}

/**
  * @brief  Check if MSI RC1  PLL-mode is enabled or not
  * @rmtoll CR    MSIPLL1EN        LL_RCC_MSI_RC1_PLLmode_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_PLLmode_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIPLL1EN) == RCC_CR_MSIPLL1EN) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI RC1 PLL mode is ready
  * @rmtoll CR           MSIPLL1RDY        LL_RCC_MSI_RC1_PLLmode_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_PLLmode_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIPLL1RDY) == RCC_CR_MSIPLL1RDY) ? 1UL : 0UL);
}

/**
  * @brief  Set MSIRC1 PLL-mode input clock
  * @note LSE or HSE must be enabled and ready before selecting this oscillator as MSIRC1 input clock
  * @rmtoll ICSCR1        MSIPLL1SEL        LL_RCC_MSI_RC1_SetPLLInputClk
  * @param  MSIPLL1sel This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIPLL1SEL_LSE
  *         @arg @ref LL_RCC_MSIPLL1SEL_HSE_OR_HSEDIV2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_SetPLLInputClk(uint32_t MSIPLL1sel)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIPLL1SEL, MSIPLL1sel);
}

/**
  * @brief  Get MSIRC1 PLL-mode input clock
  * @rmtoll ICSCR1        MSIPLL1SEL        LL_RCC_MSI_RC1_GetPLLInputClk
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIPLL1SEL_LSE
  *         @arg @ref LL_RCC_MSIPLL1SEL_HSE_OR_HSEDIV2
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_GetPLLInputClk(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIPLL1SEL));
}

/**
  * @brief  Set MSIRC1 PLL-mode LSE multiplication factor
  *         MSIRC1 frequency is MSIPLL1N * fLSE.
  * @note LSE or HSE must be enabled and ready before selecting this oscillator as MSIRC1 input clock
  *       MSIS and MSIK ranges 4, 5 6 and 7 frequencies are therefore impacted accordingly
  * @rmtoll ICSCR1        MSIPLL1N[1:0]        LL_RCC_MSI_RC1_SetLSEMultiplicationFactor
  * @param  LSEMultiplicationFactor This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRC1_PLLMODE_LSE_MULT_732 (Freq MSIRC1 = 23.9862 MHz)
  *         @arg @ref LL_RCC_MSIRC1_PLLMODE_LSE_MULT_689 (Freq MSIRC1 = 22.5772 MHz)
  *         @arg @ref LL_RCC_MSIRC1_PLLMODE_LSE_MULT_750 (Freq MSIRC1 = 24.576 MHz)
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_SetLSEMultiplicationFactor(uint32_t LSEMultiplicationFactor)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIPLL1N, LSEMultiplicationFactor);
}

/**
  * @brief  Get MSIRC1 PLL-mode LSE multiplication factor
  * @rmtoll ICSCR1        MSIPLL1N[1:0]        LL_RCC_MSI_RC1_GetLSEMultiplicationFactor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIRC1_PLLMODE_LSE_MULT_732
  *         @arg @ref LL_RCC_MSIRC1_PLLMODE_LSE_MULT_689
  *         @arg @ref LL_RCC_MSIRC1_PLLMODE_LSE_MULT_750
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_GetLSEMultiplicationFactor(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIPLL1N));
}

/**
  * @brief  MSI RC1 PLL mode fast startup
  * @rmtoll CR           MSIPLL1FAST         LL_RCC_MSI_RC1_PLLmode_FastStartup
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_PLLmode_FastStartup(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLL1FAST);
}

/**
  * @brief  MSI RC1 PLL mode normal startup
  * @rmtoll CR           MSIPLL1FAST         LL_RCC_MSI_RC1_PLLmode_NormalStartup
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_PLLmode_NormalStartup(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLL1FAST);
}

/**
  * @brief  Get MSIRC1 PLL-mode startup status
  * @rmtoll CR        MSIPLL1FAST        LL_RCC_MSI_RC1_PLLmode_GetStartupStatus
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIPLL1_STARTUP_NORMAL
  *         @arg @ref LL_RCC_MSIPLL1_STARTUP_FAST
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_PLLmode_GetStartupStatus(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_MSIPLL1FAST));
}


/**
  * @brief  Set MSI clock trimming for ranges 4 to 7
  * @note Additional user-programmable trimming value that is added to the factory-programmed
  *       calibration trim value MSIRC1[5:0] bits.
  * @rmtoll ICSCR2        MSITRIM1        LL_RCC_MSI_RC1_SetTrimming
  * @param  TrimValue
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_RC1_SetTrimming(uint32_t TrimValue)
{
  MODIFY_REG(RCC->ICSCR2, RCC_ICSCR2_MSITRIM1, (TrimValue << RCC_ICSCR2_MSITRIM1_Pos));
}

/**
  * @brief  Get MSI clock trimming for ranges 4 to 7
  * @note Additional user-programmable trimming value that is added to the factory-programmed
  *       calibration trim value MSIRC1[5:0] bits.
  * @rmtoll ICSCR2        MSITRIM1        LL_RCC_MSI_RC1_GetTrimming
  * @retval TrimValue
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_GetTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR2, RCC_ICSCR2_MSITRIM1) >> RCC_ICSCR2_MSITRIM1_Pos);
}

/**
  * @brief  Get MSIRC1 clock calibration for MSI ranges 0 to 3
  * @note Field initialized at startup with the factory-programmed MSIRC1 calibration trim value for ranges 4 to 7.
  *       When MSITRIM1 is written, MSICAL1 is updated with the sum of MSITRIM1[5:0] and the
  *       factory-programmed calibration trim value MSIRC1[5:0].
  * @rmtoll ICSCR1        MSICAL1        LL_RCC_MSI_RC1_GetCalibration
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_RC1_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSICAL1) >> RCC_ICSCR1_MSICAL1_Pos);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable Low Speed External (LSE) crystal.
  * @rmtoll BDCR        LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable Low Speed External (LSE) crystal.
  * @rmtoll BDCR        LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Check if LSE is enabled or not
  * @rmtoll BDCR    LSEON        LL_RCC_LSE_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEON) == RCC_BDCR_LSEON) ? 1UL : 0UL);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll BDCR        LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll BDCR        LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Check if LSE bypass is enabled or not
  * @rmtoll BDCR    LSEBYP        LL_RCC_LSE_IsEnabledBypass
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabledBypass(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE clock glitch filter.
  * @rmtoll BDCR        LSEGFON        LL_RCC_LSE_EnableGLITCH_FILTER
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableGLITCH_FILTER(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEGFON);
}

/**
  * @brief  Disable LSE clock glitch filter.
  * @rmtoll BDCR        LSEGFON        LL_RCC_LSE_DisableGLITCH_FILTER
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableGLITCH_FILTER(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEGFON);
}

/**
  * @brief  Check if LSE clock glitch filter is enabled or not
  * @rmtoll BDCR    LSEGFON        LL_RCC_LSE_IsEnabledGLITCH_FILTER
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabledGLITCH_FILTER(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEGFON) == RCC_BDCR_LSEGFON) ? 1UL : 0UL);
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll BDCR        LSEDRV        LL_RCC_LSE_SetDriveCapability
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
  * @rmtoll BDCR        LSEDRV        LL_RCC_LSE_GetDriveCapability
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
  * @rmtoll BDCR        LSECSSON      LL_RCC_LSE_EnableCSS
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
  * @rmtoll BDCR        LSECSSON      LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Check if LSE CSS is enabled or not
  * @rmtoll BDCR    LSECSSON        LL_RCC_LSE_IsEnabledCSS
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabledCSS(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) == RCC_BDCR_LSECSSON) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR        LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == RCC_BDCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE oscillator propagation for system clock
  * @rmtoll BDCR        LSESYSEN      LL_RCC_LSE_EnablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnablePropagation(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Disable LSE oscillator propagation for system clock
  * @rmtoll BDCR        LSESYSEN      LL_RCC_LSE_DisablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisablePropagation(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Check if LSE oscillator propagation is enabled or not
  * @rmtoll BDCR    LSESYSEN        LL_RCC_LSE_IsEnabledPropagation
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabledPropagation(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN) == RCC_BDCR_LSESYSEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator propagation for system clock Ready
  * @rmtoll BDCR        LSESYSRDY     LL_RCC_LSE_IsPropagationReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsPropagationReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) == RCC_BDCR_LSESYSRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll BDCR        LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == RCC_BDCR_LSECSSD) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable Low Speed Internal (LSI) oscillator.
  * @rmtoll CSR        LSION         LL_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Disable Low Speed Internal (LSI) oscillator.
  * @rmtoll CSR        LSION         LL_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Check if LSI is enabled or not
  * @rmtoll CSR    LSION        LL_RCC_LSI_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LSION) == RCC_CSR_LSION) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI oscillator Ready
  * @rmtoll CSR        LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == RCC_CSR_LSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set LSI divider configuration
  * @note Set low-speed clock divider configuration
  * @rmtoll CSR        LSIPREDIV        LL_RCC_LSI_SetClockPrediv
  * @param  LSIprediv This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI_PREDIV_NONE
  *         @arg @ref LL_RCC_LSI_PREDIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_SetClockPrediv(uint32_t LSIprediv)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_LSIPREDIV, LSIprediv);
}

/**
  * @brief  Get LSI divider configuration
  * @note Get low-speed clock divider configuration
  * @rmtoll CSR        LSIPREDIV        LL_RCC_LSI_GetClockPrediv
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI_PREDIV_NONE
  *         @arg @ref LL_RCC_LSI_PREDIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_GetClockPrediv(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV));
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
  * @rmtoll BDCR        RTCSEL        LL_RCC_SetRTCClockSource
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
  * @rmtoll BDCR        RTCSEL        LL_RCC_GetRTCClockSource
  * @param  RTCx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(uint32_t RTCx_clksource)
{
  UNUSED(RTCx_clksource);
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL));
}

/**
  * @brief  Enable RTC and TAMP clock
  * @rmtoll BDCR           RTCEN         LL_RCC_RTC_ClockEnable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RTC_ClockEnable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Disable RTC and TAMP clock
  * @rmtoll BDCR           RTCEN         LL_RCC_RTC_ClockDisable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RTC_ClockDisable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC and TAMP clock is enabled or not
  * @rmtoll BDCR    RTCEN        LL_RCC_RTC_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_RTC_IsEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == RCC_BDCR_RTCEN) ? 1UL : 0UL);
}


/**
  * @brief  Force the Backup domain reset
  * @rmtoll BDCR        BDRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR        BDRST         LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll BDCR        LSCOEN        LL_RCC_LSCO_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll BDCR        LSCOEN        LL_RCC_LSCO_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Check if LSCO is enabled or not
  * @rmtoll BDCR    LSCOEN        LL_RCC_LSCO_IsEnabled
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_IsEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSCOEN) == RCC_BDCR_LSCOEN) ? 1UL : 0UL);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll BDCR        LSCOSEL       LL_RCC_LSCO_SetSource
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
  * @rmtoll BDCR        LSCOSEL       LL_RCC_LSCO_GetSource
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
  * @rmtoll CFGR1         SW           LL_RCC_SetSysClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_MSIS
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
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
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_MSIS
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS));
}

/**
  * @brief  Select Wakeup from Stop and CSS backup clock
  * @note  Select the system clock used when exiting Stop mode
  * @rmtoll CFGR1        STOPWUCK        LL_RCC_SetStopWakeupClock
  * @param  Clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUP_CLK_MSIS
  *         @arg @ref LL_RCC_STOP_WAKEUP_CLK_HSI16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetStopWakeupClock(uint32_t Clock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_STOPWUCK, Clock);
}

/**
  * @brief  Get Wakeup from Stop and CSS backup clock
  * @rmtoll CFGR1        STOPWUCK        LL_RCC_GetStopWakeupClock
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUP_CLK_MSIS
  *         @arg @ref LL_RCC_STOP_WAKEUP_CLK_HSI16
  */
__STATIC_INLINE uint32_t LL_RCC_GetStopWakeupClock(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_STOPWUCK));
}

/**
  * @brief  Select Wakeup from Stop kernel clock
  * @note  Select the kernel clock used when exiting Stop mode
  * @rmtoll CFGR1        STOPKERWUCK        LL_RCC_SetStopWakeupKernelClock
  * @param  Clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUP_KERCLK_MSIK
  *         @arg @ref LL_RCC_STOP_WAKEUP_KERCLK_HSI16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetStopWakeupKernelClock(uint32_t Clock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_STOPKERWUCK, Clock);
}

/**
  * @brief  Get Wakeup from Stop kernel clock
  * @rmtoll CFGR1        STOPKERWUCK        LL_RCC_GetStopWakeupKernelClock
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUP_KERCLK_MSIK
  *         @arg @ref LL_RCC_STOP_WAKEUP_KERCLK_HSI16
  */
__STATIC_INLINE uint32_t LL_RCC_GetStopWakeupKernelClock(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_STOPKERWUCK));
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll CFGR2        HPRE          LL_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_HPRE, Prescaler);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll CFGR2         HPRE          LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_HCLK_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_HPRE));
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll CFGR2         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE1, Prescaler);
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll CFGR2         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB1_HCLK_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE1));
}

/**
  * @brief  Set APB2 prescaler
  * @rmtoll CFGR2         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE2, Prescaler);
}

/**
  * @brief  Get APB2 prescaler
  * @rmtoll CFGR2         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB2_HCLK_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE2));
}

/**
  * @brief  Set APB3 prescaler
  * @rmtoll CFGR3         PPRE3         LL_RCC_SetAPB3Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB3Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_PPRE3, Prescaler);
}

/**
  * @brief  Get APB3 prescaler
  * @rmtoll CFGR3         PPRE3         LL_RCC_GetAPB3Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_1
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_2
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_4
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_8
  *         @arg @ref LL_RCC_APB3_HCLK_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB3Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_PPRE3));
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
  __IO uint32_t *addr = ccipr_addr_reg[SystickSource >> 24];
  uint8_t  pos   = (uint8_t)(SystickSource >> 16) & 0x1FU;
  uint32_t mask  = (SystickSource >> 8) & 0x000000FFU;
  uint32_t value = (SystickSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get Sysctick clock source
  * @rmtoll CCIPR1       SYSTICKSEL    LL_RCC_GetSystickClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  */
__STATIC_INLINE uint32_t LL_RCC_GetSystickClockSource(void)
{
  const uint32_t Systick_clksource = LL_RCC_SYSTICK_CLKSOURCE;
  const __IO uint32_t *addr = ccipr_addr_reg[Systick_clksource >> 24];
  uint8_t  pos   = (uint8_t)(Systick_clksource >> 16) & 0x1FU;
  uint32_t mask  = (Systick_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*(const __IO uint32_t *)addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((Systick_clksource & 0xFFFFFF00U) | value);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Set MCO clock source
  * @rmtoll CFGR1         MCOSEL        LL_RCC_SetSourceClockMCO\n
  * @param  MCOSourceClock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCOSOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCOSOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCOSOURCE_MSIS
  *         @arg @ref LL_RCC_MCOSOURCE_HSI16
  *         @arg @ref LL_RCC_MCOSOURCE_HSE
  *         @arg @ref LL_RCC_MCOSOURCE_LSI
  *         @arg @ref LL_RCC_MCOSOURCE_LSE
  *         @arg @ref LL_RCC_MCOSOURCE_HSI48
  *         @arg @ref LL_RCC_MCOSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSourceClockMCO(uint32_t MCOSourceClock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_MCOSEL, MCOSourceClock);
}

/**
  * @brief  Get MCO clock source
  * @rmtoll CFGR1         MCOSEL        LL_RCC_GetSourceClockMCO\n
  * @retval @arg @ref LL_RCC_MCOSOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCOSOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCOSOURCE_MSIS
  *         @arg @ref LL_RCC_MCOSOURCE_HSI16
  *         @arg @ref LL_RCC_MCOSOURCE_HSE
  *         @arg @ref LL_RCC_MCOSOURCE_LSI
  *         @arg @ref LL_RCC_MCOSOURCE_LSE
  *         @arg @ref LL_RCC_MCOSOURCE_HSI48
  *         @arg @ref LL_RCC_MCOSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetSourceClockMCO(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_MCOSEL));
}

/**
  * @brief  Set MCO clock prescaler
  * @rmtoll CFGR1         MCOPRE        LL_RCC_SetClockPrescalerMCO\n
  * @param  MCOClockPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO_DIV_1
  *         @arg @ref LL_RCC_MCO_DIV_2
  *         @arg @ref LL_RCC_MCO_DIV_4
  *         @arg @ref LL_RCC_MCO_DIV_8
  *         @arg @ref LL_RCC_MCO_DIV_16
  *         @arg @ref LL_RCC_MCO_DIV_32
  *         @arg @ref LL_RCC_MCO_DIV_64
  *         @arg @ref LL_RCC_MCO_DIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetClockPrescalerMCO(uint32_t MCOClockPrescaler)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_MCOPRE, MCOClockPrescaler);
}

/**
  * @brief  Get MCO clock prescaler
  * @rmtoll CFGR1         MCOPRE        LL_RCC_GetSourceClockMCO\n
  * @retval @arg @ref LL_RCC_MCO_DIV_1
  *         @arg @ref LL_RCC_MCO_DIV_2
  *         @arg @ref LL_RCC_MCO_DIV_4
  *         @arg @ref LL_RCC_MCO_DIV_8
  *         @arg @ref LL_RCC_MCO_DIV_16
  *         @arg @ref LL_RCC_MCO_DIV_32
  *         @arg @ref LL_RCC_MCO_DIV_64
  *         @arg @ref LL_RCC_MCO_DIV_128

  */
__STATIC_INLINE uint32_t LL_RCC_GetClockPrescalerMCO(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_MCOPRE));
}

/**
  * @brief  Set MCO2 clock source
  * @rmtoll CFGR1         MCO2SEL        LL_RCC_SetSourceClockMCO2\n
  * @param  MCO2SourceClock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO2SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_MSIS
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI16
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  *         @arg @ref LL_RCC_MCO2SOURCE_LSE
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO2SOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSourceClockMCO2(uint32_t MCO2SourceClock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_MCO2SEL, MCO2SourceClock);
}

/**
  * @brief  Get MCO2 clock source
  * @rmtoll CFGR1         MCO2SEL        LL_RCC_GetSourceClockMCO2\n
  * @retval @arg @ref LL_RCC_MCO2SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_MSIS
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI16
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  *         @arg @ref LL_RCC_MCO2SOURCE_LSE
  *         @arg @ref LL_RCC_MCO2SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO2SOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetSourceClockMCO2(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_MCO2SEL));
}

/**
  * @brief  Set MCO2 clock prescaler
  * @rmtoll CFGR1         MCO2PRE        LL_RCC_SetClockPrescalerMCO2\n
  * @param  MCO2ClockPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO2_DIV_1
  *         @arg @ref LL_RCC_MCO2_DIV_2
  *         @arg @ref LL_RCC_MCO2_DIV_4
  *         @arg @ref LL_RCC_MCO2_DIV_8
  *         @arg @ref LL_RCC_MCO2_DIV_16
  *         @arg @ref LL_RCC_MCO2_DIV_32
  *         @arg @ref LL_RCC_MCO2_DIV_64
  *         @arg @ref LL_RCC_MCO2_DIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetClockPrescalerMCO2(uint32_t MCO2ClockPrescaler)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_MCO2PRE, MCO2ClockPrescaler);
}

/**
  * @brief  Get MCO2 clock prescaler
  * @rmtoll CFGR1         MCO2PRE        LL_RCC_GetSourceClockMCO2\n
  * @retval @arg @ref LL_RCC_MCO2_DIV_1
  *         @arg @ref LL_RCC_MCO2_DIV_2
  *         @arg @ref LL_RCC_MCO2_DIV_4
  *         @arg @ref LL_RCC_MCO2_DIV_8
  *         @arg @ref LL_RCC_MCO2_DIV_16
  *         @arg @ref LL_RCC_MCO2_DIV_32
  *         @arg @ref LL_RCC_MCO2_DIV_64
  *         @arg @ref LL_RCC_MCO2_DIV_128

  */
__STATIC_INLINE uint32_t LL_RCC_GetClockPrescalerMCO2(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_MCO2PRE));
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
  *         CCIPR1       USART3SEL     LL_RCC_SetUSARTClockSource\n
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI16 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI16
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t USARTxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[USARTxSource >> 24];
  uint8_t  pos   = (uint8_t)(USARTxSource >> 16) & 0x1FU;
  uint32_t mask  = (USARTxSource >> 8) & 0x000000FFU;
  uint32_t value = (USARTxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get USARTx clock source
  * @rmtoll CCIPR1       USART1SEL     LL_RCC_GetUSARTClockSource\n
  *         CCIPR1       USART2SEL     LL_RCC_GetUSARTClockSource\n
  *         CCIPR1       USART3SEL     LL_RCC_GetUSARTClockSource\n
  * @param  USARTx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI16 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI16
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t USARTx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[USARTx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(USARTx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (USARTx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((USARTx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Configure UARTx clock source
  * @rmtoll CCIPR1       UART4SEL     LL_RCC_SetUARTClockSource\n
  *         CCIPR1       UART5SEL     LL_RCC_SetUARTClockSource\n
  * @param  UARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUARTClockSource(uint32_t UARTxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[UARTxSource >> 24];
  uint8_t  pos   = (uint8_t)(UARTxSource >> 16) & 0x1FU;
  uint32_t mask  = (UARTxSource >> 8) & 0x000000FFU;
  uint32_t value = (UARTxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get UARTx clock source
  * @rmtoll CCIPR1       UART4SEL     LL_RCC_GetUARTClockSource\n
  *         CCIPR1       UART5SEL     LL_RCC_GetUARTClockSource\n
  * @param  UARTx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI16
  */
__STATIC_INLINE uint32_t LL_RCC_GetUARTClockSource(uint32_t UARTx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[UARTx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(UARTx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (UARTx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((UARTx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Configure I3Cx clock source
  * @rmtoll CCIPR1       I3C1SEL       LL_RCC_SetI3CClockSource\n
  *         CCIPR1       I3C2SEL       LL_RCC_SetI3CClockSource\n
  * @param  I3CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3CClockSource(uint32_t I3CxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[I3CxSource >> 24];
  uint8_t  pos   = (uint8_t)(I3CxSource >> 16) & 0x1FU;
  uint32_t mask  = (I3CxSource >> 8) & 0x000000FFU;
  uint32_t value = (I3CxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get I3Cx clock source
  * @rmtoll CCIPR1       I3C1SEL     LL_RCC_GetI3CClockSource\n
  *         CCIPR1       I3C2SEL     LL_RCC_GetI3CClockSource\n
  * @param  I3Cx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3CClockSource(uint32_t I3Cx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[I3Cx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(I3Cx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (I3Cx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((I3Cx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CCIPR1       I2C1SEL       LL_RCC_SetI2CClockSource\n
  *         CCIPR1       I2C2SEL       LL_RCC_SetI2CClockSource\n
  *         CCIPR3       I2C3SEL       LL_RCC_SetI2CClockSource\n
  *         CCIPR2       I2C4SEL       LL_RCC_SetI2CClockSource\n
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_MSIK (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t I2CxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[I2CxSource >> 24];
  uint8_t  pos   = (uint8_t)(I2CxSource >> 16) & 0x1FU;
  uint32_t mask  = (I2CxSource >> 8) & 0x000000FFU;
  uint32_t value = (I2CxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CCIPR1       I2C1SEL     LL_RCC_GetI2CClockSource\n
  *         CCIPR1       I2C2SEL     LL_RCC_GetI2CClockSource\n
  *         CCIPR3       I2C3SEL     LL_RCC_GetI2CClockSource\n
  *         CCIPR2       I2C4SEL     LL_RCC_GetI2CClockSource\n
  * @param  I2Cx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_MSIK (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t I2Cx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[I2Cx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(I2Cx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (I2Cx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((I2Cx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Configure SPIx clock source
  * @rmtoll CCIPR1       SPI1SEL       LL_RCC_SetSPIClockSource\n
  *         CCIPR1       SPI2SEL       LL_RCC_SetSPIClockSource\n
  *         CCIPR2       SPI3SEL       LL_RCC_SetSPIClockSource\n
  *         CCIPR2       SPI4SEL       LL_RCC_SetSPIClockSource\n
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE_MSIK (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t SPIxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[SPIxSource >> 24];
  uint8_t  pos   = (uint8_t)(SPIxSource >> 16) & 0x1FU;
  uint32_t mask  = (SPIxSource >> 8) & 0x000000FFU;
  uint32_t value = (SPIxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get SPIx clock source
  * @rmtoll CCIPR1       SPI1SEL     LL_RCC_GetSPIClockSource\n
  *         CCIPR1       SPI2SEL     LL_RCC_GetSPIClockSource\n
  *         CCIPR1       SPI3SEL     LL_RCC_GetSPIClockSource\n
  *         CCIPR1       SPI4SEL     LL_RCC_GetSPIClockSource\n
  * @param  SPIx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE_MSIK (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t SPIx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[SPIx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(SPIx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (SPIx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((SPIx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll CCIPR3       LPTIM1SEL     LL_RCC_SetLPTIMClockSource\n
  *         CCIPR1       LPTIM2SEL     LL_RCC_SetLPTIMClockSource\n
  *         CCIPR3       LPTIM34SEL    LL_RCC_SetLPTIMClockSource\n
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t LPTIMxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[LPTIMxSource >> 24];
  uint8_t  pos   = (uint8_t)(LPTIMxSource >> 16) & 0x1FU;
  uint32_t mask  = (LPTIMxSource >> 8) & 0x000000FFU;
  uint32_t value = (LPTIMxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get LPTIMx clock source
  * @rmtoll CCIPR3       LPTIM1SEL     LL_RCC_GetLPTIMClockSource\n
  *         CCIPR1       LPTIM2SEL     LL_RCC_GetLPTIMClockSource\n
  *         CCIPR3       LPTIM34SEL    LL_RCC_GetLPTIMClockSource\n
  * @param  LPTIMx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t LPTIMx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[LPTIMx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(LPTIMx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (LPTIMx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((LPTIMx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set FDCANx clock source
  * @rmtoll CCIPR1      FDCANSEL    LL_RCC_SetFDCANClockSource
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t FDCANxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[FDCANxSource >> 24];
  uint8_t  pos   = (uint8_t)(FDCANxSource >> 16) & 0x1FU;
  uint32_t mask  = (FDCANxSource >> 8) & 0x000000FFU;
  uint32_t value = (FDCANxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get FDCANx clock source
  * @rmtoll CCIPR1       FDCANSEL    LL_RCC_GetFDCANClockSource
  * @param  FDCANx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t FDCANx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[FDCANx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(FDCANx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (FDCANx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((FDCANx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set ICLK clock source
  * @rmtoll CCIPR1      ICLKSEL    LL_RCC_SetICLKClockSource
  * @param  ICLKSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_SYSCLK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetICLKClockSource(uint32_t ICLKSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[ICLKSource >> 24];
  uint8_t  pos   = (uint8_t)(ICLKSource >> 16) & 0x1FU;
  uint32_t mask  = (ICLKSource >> 8) & 0x000000FFU;
  uint32_t value = (ICLKSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get ICLK clock source
  * @rmtoll CCIPR1       ICLKSEL    LL_RCC_GetICLKClockSource
  * @param  ICLK_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ICLK_CLKSOURCE_SYSCLK
  */
__STATIC_INLINE uint32_t LL_RCC_GetICLKClockSource(uint32_t ICLK_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[ICLK_clksource >> 24];
  uint8_t  pos   = (uint8_t)(ICLK_clksource >> 16) & 0x1FU;
  uint32_t mask  = (ICLK_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((ICLK_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set USBx clock source
  * @rmtoll CCIPR1      USB1SEL    LL_RCC_SetUSBClockSource
  * @param  USBxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB1_CLKSOURCE_ICLK
  *         @arg @ref LL_RCC_USB1_CLKSOURCE_ICLKDIV2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSBClockSource(uint32_t USBxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[USBxSource >> 24];
  uint8_t  pos   = (uint8_t)(USBxSource >> 16) & 0x1FU;
  uint32_t mask  = (USBxSource >> 8) & 0x000000FFU;
  uint32_t value = (USBxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get USB clock source
  * @rmtoll CCIPR1       USB1SEL    LL_RCC_GetUSBClockSource
  * @param  USBx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USB1_CLKSOURCE_ICLK
  *         @arg @ref LL_RCC_USB1_CLKSOURCE_ICLKDIV2
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBClockSource(uint32_t USBx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[USBx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(USBx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (USBx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((USBx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set TIMIC clock source
  * @rmtoll CCIPR1      TIMICSEL    LL_RCC_SetTIMICClockSource
  * @param  TIMICxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSISDIV1024_MSISDIV4
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSISDIV1024_MSIKDIV4
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSIKDIV1024_MSISDIV4
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSIKDIV1024_MSIKDIV4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTIMICClockSource(uint32_t TIMICxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[TIMICxSource >> 24];
  uint8_t  pos   = (uint8_t)(TIMICxSource >> 16) & 0x1FU;
  uint32_t mask  = (TIMICxSource >> 8) & 0x000000FFU;
  uint32_t value = (TIMICxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get TIMICx clock source
  * @rmtoll CCIPR1       TIMICSEL    LL_RCC_GetTIMICClockSource
  * @param  TIMICx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSISDIV1024_MSISDIV4
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSISDIV1024_MSIKDIV4
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSIKDIV1024_MSISDIV4
  *         @arg @ref LL_RCC_TIMIC_CLKSOURCE_HSIDIV256_MSIKDIV1024_MSIKDIV4
  */
__STATIC_INLINE uint32_t LL_RCC_GetTIMICClockSource(uint32_t TIMICx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[TIMICx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(TIMICx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (TIMICx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((TIMICx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set ADFx clock source
  * @rmtoll CCIPR2      ADF1SEL    LL_RCC_SetADFClockSource
  * @param  ADFxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_SAI1
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_AUDCLKIN
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADFClockSource(uint32_t ADFxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[ADFxSource >> 24];
  uint8_t  pos   = (uint8_t)(ADFxSource >> 16) & 0x1FU;
  uint32_t mask  = (ADFxSource >> 8) & 0x000000FFU;
  uint32_t value = (ADFxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get ADFx clock source
  * @rmtoll CCIPR2       ADF1SEL    LL_RCC_GetADFClockSource
  * @param  ADFx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_SAI1
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_AUDCLKIN
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetADFClockSource(uint32_t ADFx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[ADFx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(ADFx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (ADFx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((ADFx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set SAIx clock source
  * @rmtoll CCIPR2      SAI1SEL    LL_RCC_SetSAIClockSource
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_AUDCLKIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAIClockSource(uint32_t SAIxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[SAIxSource >> 24];
  uint8_t  pos   = (uint8_t)(SAIxSource >> 16) & 0x1FU;
  uint32_t mask  = (SAIxSource >> 8) & 0x000000FFU;
  uint32_t value = (SAIxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get SAIx clock source
  * @rmtoll CCIPR2       SAI1SEL    LL_RCC_GetSAIClockSource
  * @param  SAIx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_AUDCLKIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAIClockSource(uint32_t SAIx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[SAIx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(SAIx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (SAIx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((SAIx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set RNGx clock source
  * @rmtoll CCIPR2      RNGSEL    LL_RCC_SetRNGClockSource
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRNGClockSource(uint32_t RNGxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[RNGxSource >> 24];
  uint8_t  pos   = (uint8_t)(RNGxSource >> 16) & 0x1FU;
  uint32_t mask  = (RNGxSource >> 8) & 0x000000FFU;
  uint32_t value = (RNGxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get RNGx clock source
  * @rmtoll CCIPR2       RNGSEL    LL_RCC_GetRNGClockSource
  * @param  RNGx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetRNGClockSource(uint32_t RNGx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[RNGx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(RNGx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (RNGx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((RNGx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set ADCDACx kernel clock prescaler
  * @rmtoll CCIPR2      ADCDACPRE    LL_RCC_SetADCDACClockPrescaler
  * @param  ADCDACxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_2
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_4
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_8
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_16
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_32
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_64
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_128
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_256
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCDACClockPrescaler(uint32_t ADCDACxPrescaler)
{
  __IO uint32_t *addr = ccipr_addr_reg[ADCDACxPrescaler >> 24];
  uint8_t  pos   = (uint8_t)(ADCDACxPrescaler >> 16) & 0x1FU;
  uint32_t mask  = (ADCDACxPrescaler >> 8) & 0x000000FFU;
  uint32_t value = (ADCDACxPrescaler >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get ADCDAC kernel clock prescaler
  * @rmtoll CCIPR2      ADCDACPRE    LL_RCC_GetADCDACClockPrescaler
  * @param  ADCDACx_clkprescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_2
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_4
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_8
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_16
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_32
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_64
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_128
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_256
  *         @arg @ref LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCDACClockPrescaler(uint32_t ADCDACx_clkprescaler)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[ADCDACx_clkprescaler >> 24];
  uint8_t  pos   = (uint8_t)(ADCDACx_clkprescaler >> 16) & 0x1FU;
  uint32_t mask  = (ADCDACx_clkprescaler >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((ADCDACx_clkprescaler & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set ADCDACx clock source
  * @rmtoll CCIPR2      ADCDACSEL    LL_RCC_SetADCDACClockSource
  * @param  ADCDACxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCDACClockSource(uint32_t ADCDACxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[ADCDACxSource >> 24];
  uint8_t  pos   = (uint8_t)(ADCDACxSource >> 16) & 0x1FU;
  uint32_t mask  = (ADCDACxSource >> 8) & 0x000000FFU;
  uint32_t value = (ADCDACxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get ADCDACx clock source
  * @rmtoll CCIPR2       ADCDACSEL    LL_RCC_GetADCDACClockSource
  * @param  ADCDACx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCDACClockSource(uint32_t ADCDACx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[ADCDACx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(ADCDACx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (ADCDACx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((ADCDACx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set DACx sample & hold clock source
  * @rmtoll CCIPR2      DAC1SHSEL    LL_RCC_SetDACSHClockSource
  * @param  DACxSHSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDACSHClockSource(uint32_t DACxSHSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[DACxSHSource >> 24];
  uint8_t  pos   = (uint8_t)(DACxSHSource >> 16) & 0x1FU;
  uint32_t mask  = (DACxSHSource >> 8) & 0x000000FFU;
  uint32_t value = (DACxSHSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get DACx sample & hold clock source
  * @rmtoll CCIPR2       DAC1SHSEL    LL_RCC_GetDACSHClockSource
  * @param  DACxSH_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetDACSHClockSource(uint32_t DACxSH_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[DACxSH_clksource >> 24];
  uint8_t  pos   = (uint8_t)(DACxSH_clksource >> 16) & 0x1FU;
  uint32_t mask  = (DACxSH_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((DACxSH_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set OCTOSPIx clock source
  * @rmtoll CCIPR2      OCTOSPISEL    LL_RCC_SetOCTOSPIClockSource
  * @param  OCTOSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOCTOSPIClockSource(uint32_t OCTOSPIxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[OCTOSPIxSource >> 24];
  uint8_t  pos   = (uint8_t)(OCTOSPIxSource >> 16) & 0x1FU;
  uint32_t mask  = (OCTOSPIxSource >> 8) & 0x000000FFU;
  uint32_t value = (OCTOSPIxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get OCTOSPIx clock source
  * @rmtoll CCIPR2       OCTOSPISEL    LL_RCC_GetOCTOSPIClockSource
  * @param  OCTOSPIx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetOCTOSPIClockSource(uint32_t OCTOSPIx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[OCTOSPIx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(OCTOSPIx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (OCTOSPIx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((OCTOSPIx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @brief  Set LPUARTx clock source
  * @rmtoll CCIPR3      LPUART1SEL    LL_RCC_SetLPUARTClockSource
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_MSIK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t LPUARTxSource)
{
  __IO uint32_t *addr = ccipr_addr_reg[LPUARTxSource >> 24];
  uint8_t  pos   = (uint8_t)(LPUARTxSource >> 16) & 0x1FU;
  uint32_t mask  = (LPUARTxSource >> 8) & 0x000000FFU;
  uint32_t value = (LPUARTxSource >> 0) & 0x000000FFU;
  MODIFY_REG(*(__IO uint32_t *)addr, (mask << pos), (value << pos));
}

/**
  * @brief  Get LPUARTx clock source
  * @rmtoll CCIPR3       LPUART1SEL    LL_RCC_GetLPUARTClockSource
  * @param  LPUARTx_clksource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI16
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t LPUARTx_clksource)
{
  const __IO uint32_t *const addr = ccipr_addr_reg[LPUARTx_clksource >> 24];
  uint8_t  pos   = (uint8_t)(LPUARTx_clksource >> 16) & 0x1FU;
  uint32_t mask  = (LPUARTx_clksource >> 8) & 0x000000FFU;
  uint32_t value = ((uint32_t)(READ_BIT(*addr, mask << pos)) >> pos) & 0x000000FFU;
  return (uint32_t)((LPUARTx_clksource & 0xFFFFFF00U) | value);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_EPOD_Management EPOD
  * @{
  */

/**
  * @brief  Set EPOD booster input clock source
  * @note Set EPOD booster input clock source
  * @rmtoll CFGR4      BOOSTSEL        LL_RCC_SetEPODBoosterClkSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_BYPASS
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_MSIS
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_HSI16
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetEPODBoosterClkSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CFGR4, RCC_CFGR4_BOOSTSEL, ClkSource);
}

/**
  * @brief  Get EPOD booster input clock source
  * @note Get EPOD booster input clock source
  * @rmtoll CFGR4      BOOSTSEL        LL_RCC_GetEPODBoosterClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_BYPASS
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_MSIS
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_HSI16
  *         @arg @ref LL_RCC_EPODBOOSTCLKSRCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetEPODBoosterClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR4, RCC_CFGR4_BOOSTSEL));
}

/**
  * @brief  Set EPOD booster input clock prescaler
  * @note Set EPOD booster input clock prescaler
  * @rmtoll CFGR4      BOOSTDIV        LL_RCC_SetEPODBoosterClkPrescaler
  * @param  ClkPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_1
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_2
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_4
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_6
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_8
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_10
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_12
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_14
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetEPODBoosterClkPrescaler(uint32_t ClkPrescaler)
{
  MODIFY_REG(RCC->CFGR4, RCC_CFGR4_BOOSTDIV, ClkPrescaler);
}

/**
  * @brief  Get EPOD booster input clock prescaler
  * @note Get EPOD booster input clock prescaler
  * @rmtoll CFGR4      BOOSTDIV        LL_RCC_GetEPODBoosterClkPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_1
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_2
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_4
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_6
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_8
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_10
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_12
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_14
  *         @arg @ref LL_RCC_EPODBOOSTCLKPRESCAL_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetEPODBoosterClkPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR4, RCC_CFGR4_BOOSTDIV));
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

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
  * @brief  Check if RCC flag BOR reset is set or not.
  * @rmtoll CSR          BORRSTF       LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_BORRSTF) == RCC_CSR_BORRSTF) ? 1UL : 0UL);
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
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll CSR          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_WWDGRSTF) == RCC_CSR_WWDGRSTF) ? 1UL : 0UL);
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
  * @brief  Disable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_DisableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSIRDYIE      LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == RCC_CIER_LSIRDYIE) ? 1UL : 0UL);
}

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
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll CIFR         LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == RCC_CIFR_LSIRDYF) ? 1UL : 0UL);
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
  * @brief  Disable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_DisableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

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
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll CICR         LSERDYC       LL_RCC_ClearFlag_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSERDYC);
}

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
  * @brief  Enable MSIS ready interrupt
  * @rmtoll CIER         MSISRDYIE      LL_RCC_EnableIT_MSISRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSISRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSISRDYIE);
}

/**
  * @brief  Disable MSIS ready interrupt
  * @rmtoll CIER         MSISRDYIE      LL_RCC_DisableIT_MSISRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSISRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSISRDYIE);
}

/**
  * @brief  Checks if MSIS ready interrupt source is enabled or disabled.
  * @rmtoll CIER         MSISRDYIE      LL_RCC_IsEnabledIT_MSISRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSISRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSISRDYIE) == RCC_CIER_MSISRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear MSIS ready interrupt flag
  * @rmtoll CICR         MSISRDYC       LL_RCC_ClearFlag_MSISRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSISRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSISRDYC);
}

/**
  * @brief  Check if MSIS ready interrupt occurred or not
  * @rmtoll CIFR         MSISRDYF       LL_RCC_IsActiveFlag_MSISRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSISRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSISRDYF) == RCC_CIFR_MSISRDYF) ? 1UL : 0UL);
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
  * @brief  Disable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_DisableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
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
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll CICR         HSIRDYC       LL_RCC_ClearFlag_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIRDYC);
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
  * @brief  Enable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_EnableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
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
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == RCC_CIER_HSERDYIE) ? 1UL : 0UL);
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
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == RCC_CIFR_HSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI48 ready interrupt
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_EnableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Disable HSI48 ready interrupt
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_DisableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Checks if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_IsEnabledIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE) == RCC_CIER_HSI48RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear HSI48 ready interrupt flag
  * @rmtoll CICR         HSI48RDYC       LL_RCC_ClearFlag_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSI48RDYC);
}

/**
  * @brief  Check if HSI48 ready interrupt occurred or not
  * @rmtoll CIFR         HSI48RDYF       LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSI48RDYF) == RCC_CIFR_HSI48RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSIRC1 PLL-mode ready interrupt
  * @rmtoll CIER         MSIPLL1RDYIE      LL_RCC_EnableIT_MSIPLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIPLL1RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIPLL1RDYIE);
}

/**
  * @brief  Disable MSIRC1 PLL-mode ready interrupt
  * @rmtoll CIER         MSIPLL1RDYIE      LL_RCC_DisableIT_MSIPLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIPLL1RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIPLL1RDYIE);
}

/**
  * @brief  Checks if MSIRC1 PLL-mode ready interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIPLL1RDYIE      LL_RCC_IsEnabledIT_MSIPLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIPLL1RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIPLL1RDYIE) == RCC_CIER_MSIPLL1RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear MSIRC1 PLL-mode ready interrupt flag
  * @rmtoll CICR         MSIPLL1RDYC       LL_RCC_ClearFlag_MSIPLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIPLL1RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIPLL1RDYC);
}

/**
  * @brief  Check if MSIRC1 PLL-mode ready interrupt occurred or not
  * @rmtoll CIFR         MSIPLL1RDYF       LL_RCC_IsActiveFlag_MSIPLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIPLL1RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIPLL1RDYF) == RCC_CIFR_MSIPLL1RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSIRC0 PLL-mode ready interrupt
  * @rmtoll CIER         MSIPLL0RDYIE      LL_RCC_EnableIT_MSIPLL0RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIPLL0RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIPLL0RDYIE);
}

/**
  * @brief  Disable MSIRC0 PLL-mode ready interrupt
  * @rmtoll CIER         MSIPLL0RDYIE      LL_RCC_DisableIT_MSIPLL0RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIPLL0RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIPLL0RDYIE);
}

/**
  * @brief  Checks if MSIRC0 PLL-mode ready interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIPLL0RDYIE      LL_RCC_IsEnabledIT_MSIPLL0RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIPLL0RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIPLL0RDYIE) == RCC_CIER_MSIPLL0RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear MSIRC0 PLL-mode ready interrupt flag
  * @rmtoll CICR         MSIPLL0RDYC       LL_RCC_ClearFlag_MSIPLL0RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIPLL0RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIPLL0RDYC);
}

/**
  * @brief  Check if MSIRC0 PLL-mode ready interrupt occurred or not
  * @rmtoll CIFR         MSIPLL0RDYF       LL_RCC_IsActiveFlag_MSIPLL0RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIPLL0RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIPLL0RDYF) == RCC_CIFR_MSIPLL0RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSI PLL-mode with LSE unlock interrupt
  * @rmtoll CIER         MSIPLLUIE      LL_RCC_EnableIT_MSIPLLU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIPLLU(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIPLLUIE);
}

/**
  * @brief  Disable MSI PLL-mode with LSE unlock interrupt
  * @rmtoll CIER         MSIPLLUIE      LL_RCC_DisableIT_MSIPLLU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIPLLU(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIPLLUIE);
}

/**
  * @brief  Checks if MSI PLL-mode with LSE unlock interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIPLLUIE      LL_RCC_IsEnabledIT_MSIPLLU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIPLLU(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIPLLUIE) == RCC_CIER_MSIPLLUIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear MSI PLL-mode with LSE unlock interrupt flag
  * @rmtoll CICR         MSIPLLUC       LL_RCC_ClearFlag_MSIPLLU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIPLLU(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIPLLUC);
}

/**
  * @brief  Check if MSI PLL-mode with LSE unlock interrupt occurred or not
  * @rmtoll CIFR         MSIPLLUF       LL_RCC_IsActiveFlag_MSIPLLU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIPLLU(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIPLLUF) == RCC_CIFR_MSIPLLUF) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSI PLL-mode with HSE unlock interrupt
  * @rmtoll CIER         MSIPLLHSUIE      LL_RCC_EnableIT_MSIPLLHSU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIPLLHSU(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIPLLHSUIE);
}

/**
  * @brief  Disable MSI PLL-mode with HSE unlock unlock interrupt
  * @rmtoll CIER         MSIPLLHSUIE      LL_RCC_DisableIT_MSIPLLHSU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIPLLHSU(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIPLLHSUIE);
}

/**
  * @brief  Checks if MSI PLL-mode with HSE unlock interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIPLLHSUIE      LL_RCC_IsEnabledIT_MSIPLLHSU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIPLLHSU(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIPLLHSUIE) == RCC_CIER_MSIPLLHSUIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear MSI PLL-mode with HSE unlock interrupt flag
  * @rmtoll CICR         MSIPLLHSUC       LL_RCC_ClearFlag_MSIPLLHSU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIPLLHSU(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIPLLHSUC);
}

/**
  * @brief  Check if MSI PLL-mode with HSE unlock interrupt occurred or not
  * @rmtoll CIFR         MSIPLLHSUF       LL_RCC_IsActiveFlag_MSIPLLHSU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIPLLHSU(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIPLLHSUF) == RCC_CIFR_MSIPLLHSUF) ? 1UL : 0UL);
}

/**
  * @brief  Clear HSE clock security system interrupt flag
  * @rmtoll CICR         CSSC       LL_RCC_ClearFlag_CSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_CSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_CSSC);
}

/**
  * @brief  Check if HSE clock security system interrupt occurred or not
  * @rmtoll CIFR         CSSF       LL_RCC_IsActiveFlag_CSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_CSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_CSSF) == RCC_CIFR_CSSF) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSIK ready interrupt
  * @rmtoll CIER         MSIKRDYIE      LL_RCC_EnableIT_MSIKRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIKRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIKRDYIE);
}

/**
  * @brief  Disable MSIK ready interrupt
  * @rmtoll CIER         MSIKRDYIE      LL_RCC_DisableIT_MSIKRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIKRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIKRDYIE);
}

/**
  * @brief  Checks if MSIK ready interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIKRDYIE      LL_RCC_IsEnabledIT_MSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIKRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIKRDYIE) == RCC_CIER_MSIKRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear MSIK ready interrupt flag
  * @rmtoll CICR         MSIKRDYC       LL_RCC_ClearFlag_MSIKRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIKRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIKRDYC);
}

/**
  * @brief  Check if MSIK ready interrupt occurred or not
  * @rmtoll CIFR         MSIKRDYF       LL_RCC_IsActiveFlag_MSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIKRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIKRDYF) == RCC_CIFR_MSIKRDYF) ? 1UL : 0UL);
}

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
  * @brief  Disable LSE clock security system interrupt
  * @rmtoll CIER         LSECSSIE      LL_RCC_DisableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Checks if LSE clock security system interrupt source is enabled or disabled.
  * @rmtoll CIER         LSECSSIE      LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSECSS(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSECSSIE) == RCC_CIER_LSECSSIE) ? 1UL : 0UL);
}

/**
  * @brief  Clear LSE clock security system interrupt flag
  * @rmtoll CICR         LSECSSC       LL_RCC_ClearFlag_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSECSSC);
}

/**
  * @brief  Check if LSE clock security system interrupt occurred or not
  * @rmtoll CIFR         LSECSSF       LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == RCC_CIFR_LSECSSF) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_Security_Services Security Services
  * @{
  */

#if defined(CPU_IN_SECURE_STATE)
/**
  * @brief  Configure RCC resources security
  * @note Only available from secure state when system implements security (TZEN=1)
  * @rmtoll SECCFGR     HSISEC    LL_RCC_ConfigSecure\n
  *         SECCFGR     HSESEC    LL_RCC_ConfigSecure\n
  *         SECCFGR     MSISEC    LL_RCC_ConfigSecure\n
  *         SECCFGR     LSISEC    LL_RCC_ConfigSecure\n
  *         SECCFGR     LSESEC    LL_RCC_ConfigSecure\n
  *         SECCFGR     SYSCLKSEC LL_RCC_ConfigSecure\n
  *         SECCFGR     PRESCSEC  LL_RCC_ConfigSecure\n
  *         SECCFGR     BOOSTSEC  LL_RCC_ConfigSecure\n
  *         SECCFGR     ICLKSEC   LL_RCC_ConfigSecure\n
  *         SECCFGR     HSI48SEC  LL_RCC_ConfigSecure\n
  *         SECCFGR     RMVFSEC   LL_RCC_ConfigSecure
  * @param  SecureConfig This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_ALL_NSEC & LL_RCC_ALL_SEC
  *         @arg @ref LL_RCC_HSI_SEC & LL_RCC_HSI_NSEC
  *         @arg @ref LL_RCC_HSE_SEC & LL_RCC_HSE_NSEC
  *         @arg @ref LL_RCC_MSI_SEC & LL_RCC_MSI_NSEC
  *         @arg @ref LL_RCC_LSI_SEC & LL_RCC_LSI_NSEC
  *         @arg @ref LL_RCC_LSE_SEC & LL_RCC_LSE_NSEC
  *         @arg @ref LL_RCC_SYSCLK_SEC & LL_RCC_SYSCLK_NSEC
  *         @arg @ref LL_RCC_PRESCALERS_SEC & LL_RCC_PRESCALERS_NSEC
  *         @arg @ref LL_RCC_BOOST_SEC & LL_RCC_BOOST_NSEC
  *         @arg @ref LL_RCC_ICLK_SEC & LL_RCC_ICLK_NSEC
  *         @arg @ref LL_RCC_HSI48_SEC & LL_RCC_HSI48_NSEC
  *         @arg @ref LL_RCC_RESET_FLAGS_SEC & LL_RCC_RESET_FLAGS_NSEC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigSecure(uint32_t SecureConfig)
{
  WRITE_REG(RCC->SECCFGR, SecureConfig);
}
#endif /* CPU_IN_SECURE_STATE */

/**
  * @brief  Get RCC resources security status
  * @note Only available from secure state when system implements security (TZEN=1)
  * @rmtoll SECCFGR     HSISEC    LL_RCC_GetConfigSecure\n
  *         SECCFGR     HSESEC    LL_RCC_GetConfigSecure\n
  *         SECCFGR     MSISEC    LL_RCC_GetConfigSecure\n
  *         SECCFGR     LSISEC    LL_RCC_GetConfigSecure\n
  *         SECCFGR     LSESEC    LL_RCC_GetConfigSecure\n
  *         SECCFGR     SYSCLKSEC LL_RCC_GetConfigSecure\n
  *         SECCFGR     PRESCSEC  LL_RCC_GetConfigSecure\n
  *         SECCFGR     BOOSTSEC  LL_RCC_GetConfigSecure\n
  *         SECCFGR     ICLKSEC   LL_RCC_GetConfigSecure\n
  *         SECCFGR     HSI48SEC  LL_RCC_GetConfigSecure\n
  *         SECCFGR     RMVFSEC   LL_RCC_GetConfigSecure
  * @retval Returned value can be one or a combination of the following values:
  *         @arg @ref LL_RCC_ALL_NSEC & LL_RCC_ALL_SEC
  *         @arg @ref LL_RCC_HSI_SEC & LL_RCC_HSI_NSEC
  *         @arg @ref LL_RCC_HSE_SEC & LL_RCC_HSE_NSEC
  *         @arg @ref LL_RCC_MSI_SEC & LL_RCC_MSI_NSEC
  *         @arg @ref LL_RCC_LSI_SEC & LL_RCC_LSI_NSEC
  *         @arg @ref LL_RCC_LSE_SEC & LL_RCC_LSE_NSEC
  *         @arg @ref LL_RCC_SYSCLK_SEC & LL_RCC_SYSCLK_NSEC
  *         @arg @ref LL_RCC_PRESCALERS_SEC & LL_RCC_PRESCALERS_NSEC
  *         @arg @ref LL_RCC_BOOST_SEC & LL_RCC_BOOST_NSEC
  *         @arg @ref LL_RCC_ICLK_SEC & LL_RCC_ICLK_NSEC
  *         @arg @ref LL_RCC_HSI48_SEC & LL_RCC_HSI48_NSEC
  *         @arg @ref LL_RCC_RESET_FLAGS_SEC & LL_RCC_RESET_FLAGS_NSEC
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_GetConfigSecure(void)
{
  return (uint32_t)(READ_BIT(RCC->SECCFGR, LL_RCC_ALL_SEC));
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_PRIV Privileged mode
  * @{
  */

#if defined(CPU_IN_SECURE_STATE)
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
#endif /* CPU_IN_SECURE_STATE */

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
uint32_t    LL_RCC_GetUARTClockFreq(uint32_t UARTxSource);
uint32_t    LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource);
uint32_t    LL_RCC_GetSPIClockFreq(uint32_t SPIxSource);
uint32_t    LL_RCC_GetOCTOSPIClockFreq(uint32_t OCTOSPIxSource);
uint32_t    LL_RCC_GetI2CClockFreq(uint32_t I2CxSource);
uint32_t    LL_RCC_GetI3CClockFreq(uint32_t I3CxSource);
uint32_t    LL_RCC_GetADCDACClockFreq(uint32_t ADCDACxSource);
uint32_t    LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource);
uint32_t    LL_RCC_GetRNGClockFreq(uint32_t RNGxSource);
uint32_t    LL_RCC_GetSAIClockFreq(uint32_t SAIxSource);
uint32_t    LL_RCC_GetRTCClockFreq(uint32_t RTCxSource);
uint32_t    LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource);
uint32_t    LL_RCC_GetUSBClockFreq(uint32_t USBxSource);
uint32_t    LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource);
uint32_t    LL_RCC_GetADFClockFreq(uint32_t ADFxSource);
uint32_t    LL_RCC_GetDACSHClockFreq(uint32_t DACSHxSource);
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

#endif /* STM32U3xx_LL_RCC_H */
