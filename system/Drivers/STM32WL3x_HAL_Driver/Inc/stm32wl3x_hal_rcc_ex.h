/**
  ******************************************************************************
  * @file    stm32wl3x_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WL3x_HAL_RCC_EX_H
#define STM32WL3x_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_NOCLOCK)        || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSI)            || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#define IS_RCC_LSCO(__LSCOX__) ( ((__LSCOX__) == RCC_LSCO1) ||\
                                 ((__LSCOX__) == RCC_LSCO2) ||\
                                 ((__LSCOX__) == RCC_LSCO3) )

#define RCC_PERIPHCLOCK_ALL     ( RCC_PERIPHCLK_SMPS                            | \
                                  RCC_PERIPHCLK_RF                              | \
                                  RCC_PERIPHCLK_LPUART1                         | \
                                  RCC_PERIPHCLK_SPI3_I2S                        | \
                                  RCC_PERIPHCLK_RTC_WDG_SUBG_LPAWUR_LCD_LCSC)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)         ((((__SELECTION__) & RCC_PERIPHCLOCK_ALL) != 0x00u) && \
                                                   (((__SELECTION__) & ~RCC_PERIPHCLOCK_ALL) == 0x00u))


#define IS_RCC_SMPS_CLOCK_PRESC(__PRESC__) \
  ((((__PRESC__) & RCC_SMPSCLK_DIV2) == RCC_SMPSCLK_DIV2) || \
   (((__PRESC__) & RCC_SMPSCLK_DIV4) == RCC_SMPSCLK_DIV4))

#define IS_RCC_SPI3I2S_CLOCK_SOURCE(__SOURCE__) \
  ((((__SOURCE__) & RCC_SPI3I2S_CLKSOURCE_CLK_ROOT_DIV) == RCC_SPI3I2S_CLKSOURCE_CLK_ROOT_DIV) || \
   (((__SOURCE__) & RCC_SPI3I2S_CLKSOURCE_CLK_ROOT) == RCC_SPI3I2S_CLKSOURCE_CLK_ROOT) || \
   (((__SOURCE__) & RCC_SPI3I2S_CLKSOURCE_CLK_RC64MPLL) == RCC_SPI3I2S_CLKSOURCE_CLK_RC64MPLL))


#if defined(RCC_CFGR_LPUCLKSEL)
#define IS_RCC_LPUART1_CLOCK_SOURCE(__SOURCE__) \
  ((((__SOURCE__) & RCC_LPUART1_CLKSOURCE_16M) == RCC_LPUART1_CLKSOURCE_16M) || \
   (((__SOURCE__) & RCC_LPUART1_CLKSOURCE_LSE) == RCC_LPUART1_CLKSOURCE_LSE))
#endif /* RCC_CFGR_LPUCLKSEL */

#define IS_RCC_RTC_WDG_SUBG_PAWUR_LCD_LCSC_CLOCK_SOURCE(__SOURCE__) \
  ((((__SOURCE__) & RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSE) == RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSE)  || \
   (((__SOURCE__) & RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSI) == RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSI) || \
   (((__SOURCE__) & RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_DIV512) == RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_DIV512))


#define IS_RCC_TRIMOSC(__OSC_TYPE__)  ((((__OSC_TYPE__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;    /*!< The Extended Clock to be configured.
                                         This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t SPI3I2SClockSelection;   /*!< Specifies SPI3_I2S clock source.
                                         This parameter can be a value of @ref RCCEx_SPI3_I2S_Clock_Source */

  uint32_t RTCWDGSUBGLPAWURLCDLCSCClockSelection; /*!< Specifies RTC, WDG and BLEWKUP clock source.
                                             This parameter can be a value of @ref RCCEx_RTC_WDG_BLEWKUP_Clock_Source */

#if defined(RCC_CFGR_LPUCLKSEL)
  uint32_t LPUART1ClockSelection;   /*!< Specifies LPUART1 clock source.
                                         This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */
#endif /* RCC_CFGR_LPUCLKSEL */

  uint32_t SmpsDivSelection;        /*!< Specifies SMPS clock prescaling factor.
                                         This parameter can be a value of @ref RCCEx_SMPS_Clock_Divider */

  uint32_t KRMRateMultiplier;       /*!< Specifies KRM rate multiplier.
                                         This parameter can be a value of @ref RCCEx_KRM_Clock_Divider */
} RCC_PeriphCLKInitTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCC_LSCO_Index LSCO Index
  * @{
  */
#define RCC_LSCO1                       0x00000000U          /*!< LSCO1 index */
#define RCC_LSCO2                       0x00000001U          /*!< LSCO2 index */
#define RCC_LSCO3                       0x00000002U          /*!< LSCO3 index */

/**
  * @}
  */

/** @defgroup RCC_LSCO_Clock_Source LSCO Clock Source
  * @{
  */
#define RCC_LSCOSOURCE_NOCLOCK         LL_RCC_LSCOSOURCE_NOCLOCK          /*!< LSCO output disabled, no clock on LSCO */
#define RCC_LSCOSOURCE_LSI             LL_RCC_LSCOSOURCE_LSI              /*!< LSI selection as LSCO source */
#define RCC_LSCOSOURCE_LSE             LL_RCC_LSCOSOURCE_LSE              /*!< LSE selection as LSCO source */
/**
  * @}
  */


/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_RF                0x00000001U                    /*!< RADIO IP  Peripheral Clock Selection */
#define RCC_PERIPHCLK_SMPS              0x00000002U                    /*!< SMPS Peripheral Clock Selection      */

#define RCC_PERIPHCLK_SPI3_I2S          0x00000008U                    /*!< SPI3 I2S Peripheral Clock Selection  */

#if defined(RCC_CFGR_LPUCLKSEL)
#define RCC_PERIPHCLK_LPUART1           0x00000010U                    /*!< LPUART1 Peripheral Clock Selection   */
#endif /* RCC_CFGR_LPUCLKSEL */
#define RCC_PERIPHCLK_RTC_WDG_SUBG_LPAWUR_LCD_LCSC           0x00000020U /*!< RTC WDG SUBG LPAWUR LCD LCSC Peripheral Clock Selection */
/**
  * @}
  */


/** @defgroup RCCEx_SPI3_I2S_Clock_Source SPI3_I2S Clock Source
  * @{
  */
#define RCC_SPI3I2S_CLKSOURCE_CLK_ROOT_DIV    LL_RCC_SPI3_I2S_CLKSOURCE_CLK_ROOT_DIV  /*!< SPI3 I2S 16 MHz clock source selection */
#define RCC_SPI3I2S_CLKSOURCE_CLK_ROOT        LL_RCC_SPI3_I2S_CLKSOURCE_CLK_ROOT  /*!< SPI3 I2S 24/32 MHz clock source selection */
#define RCC_SPI3I2S_CLKSOURCE_CLK_RC64MPLL    LL_RCC_SPI3_I2S_CLKSOURCE_CLK_RC64MPLL  /*!< SPI3 I2S 64 MHz clock source selection */
/**
  * @}
  */

#if defined(RCC_CFGR_LPUCLKSEL)
/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1_CLKSOURCE_16M    LL_RCC_LPUCLKSEL_CLK16M  /*!< LPUART1 16 MHz clock source selection  */
#define RCC_LPUART1_CLKSOURCE_LSE    LL_RCC_LPUCLKSEL_CLKLSE  /*!< LPUART1 LSE clock source selection     */
/**
  * @}
  */
#endif  /* RCC_CFGR_LPUCLKSEL */

/** @defgroup RCCEx_SMPS_Clock_Divider SMPS clock prescaling factor
  * @{
  */
#define RCC_SMPSCLK_DIV2   LL_RCC_SMPS_DIV_2   /*!< SMPS clock division 2 (SMPS clock is 8 MHz if ANADIV = 1)*/
#define RCC_SMPSCLK_DIV4   LL_RCC_SMPS_DIV_4   /*!< SMPS clock division 4 (SMPS clock is 4 MHz if ANADIV = 1)*/
/**
  * @}
  */
/** @defgroup RCCEx_RTC_WDG_BLEWKUP_Clock_Source RTC, WDG, BLEWKUP Clock Source
  * @{
  */
#define RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSE             LL_RCC_LSCO_CLKSOURCE_LSE            /*!< RTC, WDG and BLEWKUP LSE clock source selection     */
#define RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSI             LL_RCC_LSCO_CLKSOURCE_LSI            /*!< RTC, WDG and BLEWKUP LSI clock source selection     */
#define RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_DIV512          LL_RCC_LSCO_CLKSOURCE_HSI64M_DIV2048 /*!< RTC, WDG and BLEWKUP 32K clock source selection     */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/**
  * @brief  Macro to configure the LSCO clock.
  * @param  __LSCOCLKSOURCE__ specifies the LSCO clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSCOSOURCE_NOCLOCK          LSCO output disabled
  *            @arg RCC_LSCOSOURCE_LSI              LSI clock selected as LSCO source
  *            @arg RCC_LSCOSOURCE_LSE              LSE clock selected as LSCO source
  */
#define __HAL_RCC_LSCO_CONFIG(__LSCOCLKSOURCE__)  LL_RCC_ConfigLSCO((__LSCOCLKSOURCE__))

/** @brief  Macro to configure the SMPS clock prescaling factor.
  *
  * @param  __SMPSCLKDIV__ specifies the division factor for SMPS clock.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SMPSCLK_DIV2           SMPS clock division 2 (SMPS clock is 8 MHz)
  *            @arg @ref RCC_SMPSCLK_DIV4           SMPS clock division 4 (SMPS clock is 4 MHz)
  *
  * @retval None
  */
#define __HAL_RCC_SMPS_DIV_CONFIG(__SMPSCLKDIV__) LL_RCC_SetSMPSPrescaler(__SMPSCLKDIV__)

/** @brief  Macro to get the SMPS clock prescaling factor.
  *
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SMPSCLK_DIV2           SMPS clock division 2 (SMPS clock is 8 MHz)
  *            @arg @ref RCC_SMPSCLK_DIV4           SMPS clock division 4 (SMPS clock is 4 MHz)
  *
  */
#define __HAL_RCC_GET_SMPS_DIV() LL_RCC_GetSMPSPrescaler()


/** @brief  Macro to configure the KRM rate multiplier.
  * @param  __KRM_VALUE__ specifies the rate miltiplier
  *         This parameter can be between Min_Data = 0 and Max_Data = 16
  *
  * @retval None
  */
#define __HAL_RCC_KRM_RATE_MULTIPLIER_CONFIG(__KRM_VALUE__)    LL_RCC_KRM_SetRateMultiplier(__KRM_VALUE__)

/** @brief  Macro to set the KRM rate multiplier.
  *
  * @retval Between Min_Data = 0 and Max_Data = 16
  */
#define __HAL_RCC_GET_KRM_RATE_MULTIPLIER()    LL_RCC_KRM_GetRateMultiplier()

/** @brief  Macro to get the KRM rate multiplier.
  *
  * @retval State of KRM bit (1 or 0)
  */
#define __HAL_RCC_IS_KRM_ENABLED()               LL_RCC_KRM_IsEnabled()

/** @brief  Macro to disable KRM.
  *
  * @retval None
  */
#define __HAL_RCC_KRM_DISABLE()               LL_RCC_KRM_Disable()

/** @brief  Macro to enable KRM.
  *
  * @retval None
  */
#define __HAL_RCC_KRM_ENABLE()               LL_RCC_KRM_Enable()

/** @brief  Macro to configure the SPI3_I2S clock.
  *
  * @param  __SPI3I2S_CLK__ specifies the SPI3I2S clock.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_SPI3I2S_CLK_16M
  *            @arg @ref RCC_SPI3I2S_CLK_32M
  *            @arg @ref RCC_SPI3I2S_CLK_64M
  * @retval None
  */
#define __HAL_RCC_SPI3I2S_CLK_CONFIG(__SPI3I2S_CLK__) LL_RCC_SetSPI3I2SClockSource(__SPI3I2S_CLK__)

/** @brief  Macro to get the SPI3_I2S clock.
  * @retval The clock can be one of the following values:
  *            @arg @ref RCC_SPI3I2S_CLK_16M
  *            @arg @ref RCC_SPI3I2S_CLK_32M
  *            @arg @ref RCC_SPI3I2S_CLK_64M
  */
#define __HAL_RCC_GET_SPI3I2S_CLK_CONFIG() LL_RCC_GetSPI3I2SClockSource()

/**
  * @}
  */

#if defined(RCC_CFGR_LPUCLKSEL)
/** @brief  Macro to configure the LPUART1 clock.
  *
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1_CLKSOURCE_16M
  *            @arg @ref RCC_LPUART1_CLKSOURCE_LSE
  * @retval None
  */
#define __HAL_RCC_LPUART1_CLK_CONFIG(__LPUART1_CLKSOURCE__) LL_RCC_SetLPUARTClockSource(__LPUART1_CLKSOURCE__)

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1_CLKSOURCE_16M
  *            @arg @ref RCC_LPUART1_CLKSOURCE_LSE
  */
#define __HAL_RCC_GET_LPUART1_CLK_CONFIG() LL_RCC_GetLPUARTClockSource()
#endif /* RCC_CFGR_LPUCLKSEL */

/** @brief  Macro to configure the RTC, WDG, SUBG, LPAWUR, LCD and LCSC clock source.
  *
  * @param  __CLKSOURCE__ specifies the RTC, WDG, SUBG, LPAWUR, LCD and LCSC clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSE
  *            @arg @ref RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSI
  *            @arg @ref RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_DIV512
  * @retval None
  */
#define __HAL_RCC_RTC_SUBG_LPAWUR_LCD_LCSC_CLK_CONFIG( __CLKSOURCE__ ) LL_RCC_LSCO_SetSource( __CLKSOURCE__ )

/** @brief  Macro to get the RTC, WDG, SUBG, LPAWUR, LCD and LCSC clock source.
  *
  * @retval  The RTC, WDG, SUBG, LPAWUR, LCD and LCSC clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSE
  *            @arg @ref RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_LSI
  *            @arg @ref RCC_RTC_WDG_SUBG_LPAWUR_LCD_LCSC_CLKSOURCE_DIV512
  */
#define __HAL_RCC_GET_RTC_SUBG_LPAWUR_LCD_LCSC_CLK_CONFIG() LL_RCC_LSCO_GetSource()

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

void              HAL_RCCEx_LSCOConfig(uint32_t RCC_LSCOx, uint32_t RCC_LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);
void              HAL_RCCEx_EnableLSCOinDEEPSTOP(uint32_t LSCOSource);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WL3x_HAL_RCC_EX_H */
