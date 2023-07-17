/**
  ******************************************************************************
  * @file    stm32c0xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended module.
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
#ifndef STM32C0xx_HAL_RCC_EX_H
#define STM32C0xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal_def.h"

/** @addtogroup STM32C0xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
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
  uint32_t PeriphClockSelection;   /*!< The Extended Clock to be configured.
                                        This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t HSIKerClockDivider;     /*!< Specifies HSI Kernel divider.
                                        This parameter can be a value of @ref RCCEx_HSIKER_Div */

  uint32_t Usart1ClockSelection;   /*!< Specifies USART1 clock source.
                                        This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t I2c1ClockSelection;     /*!< Specifies I2C1 clock source
                                        This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

  uint32_t I2s1ClockSelection;     /*!< Specifies I2S1 clock source
                                        This parameter can be a value of @ref RCCEx_I2S1_Clock_Source */

  uint32_t AdcClockSelection;      /*!< Specifies ADC interface clock source
                                        This parameter can be a value of @ref RCCEx_ADC_Clock_Source */

  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source.
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source */
} RCC_PeriphCLKInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_LSCO_Clock_Source Low Speed Clock Source
  * @{
  */
#define RCC_LSCOSOURCE_LSI             0x00000000U           /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE             RCC_CSR1_LSCOSEL      /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1           0x00000001U
#define RCC_PERIPHCLK_I2C1             0x00000040U
#define RCC_PERIPHCLK_I2S1             0x00000800U
#define RCC_PERIPHCLK_ADC              0x00004000U
#define RCC_PERIPHCLK_RTC              0x00020000U
#define RCC_PERIPHCLK_HSIKER           0x80000000U

/**
  * @}
  */


/** @defgroup RCCEx_USART1_Clock_Source RCC USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK1      0x00000000U                                      /*!< APB clock selected as USART 1 clock */
#define RCC_USART1CLKSOURCE_SYSCLK     RCC_CCIPR_USART1SEL_0                            /*!< SYSCLK clock selected as USART 1 clock */
#define RCC_USART1CLKSOURCE_HSIKER     RCC_CCIPR_USART1SEL_1                            /*!< HSI Kernel clock selected as USART 1 clock */
#define RCC_USART1CLKSOURCE_LSE        (RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1)  /*!< LSE clock selected as USART 1 clock */
/**
  * @}
  */


/** @defgroup RCCEx_I2C1_Clock_Source RCC I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1        0x00000000U                                      /*!< APB clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0                              /*!< SYSCLK clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_HSIKER       RCC_CCIPR_I2C1SEL_1                              /*!< HSI Kernel clock selected as I2C1 clock */
/**
  * @}
  */

/** @defgroup RCCEx_I2S1_Clock_Source RCC I2S1 Clock Source
  * @{
  */
#define RCC_I2S1CLKSOURCE_SYSCLK       0x00000000U                                     /*!< SYSCLK clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_HSIKER       RCC_CCIPR_I2S1SEL_1                             /*!< HSI Kernel clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_EXT          RCC_CCIPR_I2S1SEL                               /*!< External I2S clock source selected as I2S1 clock */

/**
  * @}
  */


/** @defgroup RCCEx_ADC_Clock_Source RCC ADC Clock Source
  * @{
  */

#define RCC_ADCCLKSOURCE_SYSCLK       0x00000000U             /*!< SYSCLK used as ADC clock */
#define RCC_ADCCLKSOURCE_HSIKER       RCC_CCIPR_ADCSEL_1      /*!< HSI kernel used as ADC clock */
/**
  * @}
  */

/** @defgroup RCCEx_HSIKER_Div HSIKER Div
  * @{
  */
#define RCC_HSIKER_DIV1                 0x00000000U                                                 /*!< HSI Kernek clock is not divided */
#define RCC_HSIKER_DIV2                 RCC_CR_HSIKERDIV_0                                          /*!< HSI Kernel clock is divided by 2 */
#define RCC_HSIKER_DIV3                 RCC_CR_HSIKERDIV_1                                          /*!< HSI Kernel clock is divided by 3 */
#define RCC_HSIKER_DIV4                 (RCC_CR_HSIKERDIV_1|RCC_CR_HSIKERDIV_0)                     /*!< HSI Kernel clock is divided by 4 */
#define RCC_HSIKER_DIV5                 RCC_CR_HSIKERDIV_2                                          /*!< HSI Kernel clock is divided by 5 */
#define RCC_HSIKER_DIV6                 (RCC_CR_HSIKERDIV_2|RCC_CR_HSIKERDIV_0)                     /*!< HSI Kernel clock is divided by 6 */
#define RCC_HSIKER_DIV7                 (RCC_CR_HSIKERDIV_2|RCC_CR_HSIKERDIV_1)                     /*!< HSI Kernel clock is divided by 7 */
#define RCC_HSIKER_DIV8                 (RCC_CR_HSIKERDIV_2|RCC_CR_HSIKERDIV_1|RCC_CR_HSIKERDIV_0)  /*!< HSI Kernel clock is divided by 8 */
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


/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  *
  * @param  __I2C1_CLKSOURCE__  specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_HSIKER  HSI Kernel selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C1SEL, (uint32_t)(__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_HSIKER  HSI Kernel selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C1SEL)))

/** @brief  Macro to configure the I2S1 clock (I2S1CLK).
  *
  * @param  __I2S1_CLKSOURCE__  specifies the I2S1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2S1CLKSOURCE_SYSCLK  System Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_HSIKER  HSI Kernel Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_EXT     External clock selected as I2S1 clock
  */
#define __HAL_RCC_I2S1_CONFIG(__I2S1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2S1SEL, (uint32_t)(__I2S1_CLKSOURCE__))

/** @brief  Macro to get the I2S1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2S1CLKSOURCE_SYSCLK  System Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_HSIKER  HSI Kernel Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_EXT     External clock selected as I2S1 clock
  */
#define __HAL_RCC_GET_I2S1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2S1SEL)))


/** @brief  Macro to configure the USART1 clock (USART1CLK).
  *
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK1   PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSIKER  HSI Kernel selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART1SEL, (uint32_t)(__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK1   PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSIKER  HSI Kernel selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL)))

/** @brief  Macro to configure the ADC interface clock
  * @param  __ADC_CLKSOURCE__ specifies the ADC digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK System Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSIKER  HSI Kernel Clock selected as ADC clock
  */
#define __HAL_RCC_ADC_CONFIG(__ADC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, (uint32_t)(__ADC_CLKSOURCE__))

/** @brief  Macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK System Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSIKER  HSI Kernel Clock selected as ADC clock
  */
#define __HAL_RCC_GET_ADC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_ADCSEL)))

/** @brief  Macro to configure the HSIKER clock.
  * @param  __HSIKERDIV__ specifies the HSI Kernel division factor.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_HSIKER_DIV1   HSI clock source is divided by 1
  *            @arg @ref RCC_HSIKER_DIV2   HSI clock source is divided by 2
  *            @arg @ref RCC_HSIKER_DIV3   HSI clock source is divided by 3
  *            @arg @ref RCC_HSIKER_DIV4   HSI clock source is divided by 4
  *            @arg @ref RCC_HSIKER_DIV5   HSI clock source is divided by 5
  *            @arg @ref RCC_HSIKER_DIV6   HSI clock source is divided by 6
  *            @arg @ref RCC_HSIKER_DIV7   HSI clock source is divided by 7
  *            @arg @ref RCC_HSIKER_DIV8   HSI clock source is divided by 8
  */
#define __HAL_RCC_HSIKER_CONFIG(__HSIKERDIV__) \
  MODIFY_REG(RCC->CR, RCC_CR_HSIKERDIV, (__HSIKERDIV__))

/** @brief  Macro to get the HSIKER divider.
  * @retval The HSI Kernel divider. The returned value can be one
  *         of the following:
  *            - RCC_HSIKER_DIV1  HSI oscillator divided by 1
  *            - RCC_HSIKER_DIV2  HSI oscillator divided by 2
  *            - RCC_HSIKER_DIV3  HSI oscillator divided by 3  (default after reset)
  *            - RCC_HSIKER_DIV4  HSI oscillator divided by 4
  *            - RCC_HSIKER_DIV5  HSI oscillator divided by 5
  *            - RCC_HSIKER_DIV6  HSI oscillator divided by 6
  *            - RCC_HSIKER_DIV7  HSI oscillator divided by 7
  *            - RCC_HSIKER_DIV8  HSI oscillator divided by 8
  */
#define __HAL_RCC_GET_HSIKER_DIVIDER() ((uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSIKERDIV)))

/** @defgroup RCCEx_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */



/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);

/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Macros RCCEx Private Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))


#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
  ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_HSIKER)  == RCC_PERIPHCLK_HSIKER))


#define IS_RCC_USART1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE)    || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_HSIKER))

#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)   \
  (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1)   || \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK)  || \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSIKER))

#define IS_RCC_I2S1CLKSOURCE(__SOURCE__)   \
  (((__SOURCE__) == RCC_I2S1CLKSOURCE_SYSCLK)|| \
   ((__SOURCE__) == RCC_I2S1CLKSOURCE_HSIKER)   || \
   ((__SOURCE__) == RCC_I2S1CLKSOURCE_EXT))


#define IS_RCC_ADCCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_ADCCLKSOURCE_SYSCLK)  || \
   ((__SOURCE__) == RCC_ADCCLKSOURCE_HSIKER))

#define IS_RCC_HSIKERDIV(__DIV__) (((__DIV__) == RCC_HSIKER_DIV1)  || ((__DIV__) == RCC_HSIKER_DIV2) || \
                                   ((__DIV__) == RCC_HSIKER_DIV3)  || ((__DIV__) == RCC_HSIKER_DIV4) || \
                                   ((__DIV__) == RCC_HSIKER_DIV5)  || ((__DIV__) == RCC_HSIKER_DIV6) || \
                                   ((__DIV__) == RCC_HSIKER_DIV7)  || ((__DIV__) == RCC_HSIKER_DIV8))
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

#endif /* STM32C0xx_HAL_RCC_EX_H */
