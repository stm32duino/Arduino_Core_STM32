/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended  module.
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
#ifndef __STM32WBAxx_HAL_RCC_EX_H
#define __STM32WBAxx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */
#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  RCC LSI2 configuration structure definition
  */
typedef struct
{
  uint32_t FreqTempSens;  /*!< The temperature at which the frequency temperature sensitivity is close to zero.
                               This parameter can be a value of @ref RCCEx_LSI2_Frequency_Temperature_Sensitivity  */

  uint32_t OpMode;        /*!< The operating mode of power consumption versus accuracy.
                               This parameter can be a value of @ref RCCEx_LSI2_Operating_Mode                     */
} RCC_LSIConfigTypeDef;
#endif

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;      /*!< The Extended Clock to be configured.
                                           This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t Usart1ClockSelection;      /*!< Specifies USART1 clock source.
                                           This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

#if defined (USART2)
  uint32_t Usart2ClockSelection;      /*!< Specifies USART2 clock source.
                                           This parameter can be a value of @ref RCCEx_USART2_Clock_Source */
#endif


#if defined (I2C1)
  uint32_t I2c1ClockSelection;        /*!< Specifies I2C1 clock source.
                                           This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */
#endif




#if defined (LPTIM2)
  uint32_t Lptim2ClockSelection;      /*!< Specifies LPTIM2 clock source.
                                           This parameter can be a value of @ref RCCEx_LPTIM2_Clock_Source */
#endif

#if defined (SPI1)
  uint32_t Spi1ClockSelection;        /*!< Specifies SPI1 clock source
                                           This parameter can be a value of @ref RCCEx_SPI1_Clock_Source */
#endif

  uint32_t SystickClockSelection;     /*!< Specifies SYSTICK clock source.
                                           This parameter can be a value of @ref RCCEx_SYSTICK_Clock_Source */

  uint32_t TimIcClockSelection;       /*!< Specifies TIMIC clock source.
                                           This parameter can be a value of @ref RCCEx_TIMIC_Clock_Source */

#if defined (SAI1)
  uint32_t Sai1ClockSelection;        /*!< Specifies SAI1 clock source.
                                           This parameter can be a value of @ref RCCEx_SAI1_Clock_Source */
#endif

  uint32_t RngClockSelection;         /*!< Specifies RNG clock source
                                           This parameter can be a value of @ref RCCEx_RNG_Clock_Source */


#if defined (RCC_CCIPR2_ASSEL)
  uint32_t AudioSyncClockSelection;   /*!< Specifies Audio Sync clock source.
                                           This parameter can be a value of @ref RCCEx_AudioSync_Clock_Source */
#endif

  uint32_t Lpuart1ClockSelection;     /*!< Specifies LPUART1 clock source.
                                           This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */

  uint32_t Spi3ClockSelection;        /*!< Specifies SPI3 clock source
                                           This parameter can be a value of @ref RCCEx_SPI3_Clock_Source */

  uint32_t I2c3ClockSelection;        /*!< Specifies I2C3 clock source.
                                           This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Lptim1ClockSelection;      /*!< Specifies LPTIM1 clock source.
                                           This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */

  uint32_t AdcClockSelection;         /*!< Specifies ADC4 interface clock source.
                                           This parameter can be a value of @ref RCCEx_ADC_Clock_Source */

  uint32_t RTCClockSelection;         /*!< Specifies RTC clock source.
                                           This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t RadioSlpTimClockSelection; /*!< Specifies Radio Sleep Timer clock source.
                                           This parameter can be a value of @ref RCC_RadioSleepTimer_Clock_Source */
} RCC_PeriphCLKInitTypeDef;

#if defined(RCC_CCIPR2_ASSEL)
/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
uint32_t CapturePrescaler;            /*!< Capture Prescaler.
                                           This parameter can ba a value between 0 and 0x7F */
uint32_t ClockPrescaler;              /*!< Clock Prescaler.
                                           This parameter can ba a value between 0 and 0x7F */
uint32_t AutoReloadValue;             /*!< Auto-reload value.
                                           This parameter can be a value between 0 and 0xFFFFF*/
uint32_t CompareValue;                /*!< Compare value.
                                           This parameter can be a value between 0 and 0xFFFFF*/
} RCC_AudioSyncConfigTypeDef;
#endif /* RCC_CCIPR2_ASSEL */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_Periph_Clock_Selection  RCCEx Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1                0x00000001U
#if defined (USART2)
#define RCC_PERIPHCLK_USART2                0x00000002U
#endif
#if defined (I2C1)
#define RCC_PERIPHCLK_I2C1                  0x00000004U
#endif
#if defined (LPTIM2)
#define RCC_PERIPHCLK_LPTIM2                0x00000008U
#endif
#if defined (SPI1)
#define RCC_PERIPHCLK_SPI1                  0x00000010U
#endif
#define RCC_PERIPHCLK_SYSTICK               0x00000020U
#define RCC_PERIPHCLK_TIMIC                 0x00000040U
#if defined (SAI1)
#define RCC_PERIPHCLK_SAI1                  0x00000080U
#endif
#define RCC_PERIPHCLK_RNG                   0x00000100U
#define RCC_PERIPHCLK_LPUART1               0x00000200U
#define RCC_PERIPHCLK_SPI3                  0x00000400U
#define RCC_PERIPHCLK_I2C3                  0x00000800U
#define RCC_PERIPHCLK_LPTIM1                0x00001000U
#define RCC_PERIPHCLK_ADC                   0x00002000U
#define RCC_PERIPHCLK_RTC                   0x00004000U
#define RCC_PERIPHCLK_RADIOST               0x00008000U
#if defined (RCC_CCIPR2_ASSEL)
#define RCC_PERIPHCLK_AUDIOSYNC             0x00200000U
#endif
/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2           0x00000000U
#define RCC_USART1CLKSOURCE_SYSCLK          RCC_CCIPR1_USART1SEL_0
#define RCC_USART1CLKSOURCE_HSI             RCC_CCIPR1_USART1SEL_1
#define RCC_USART1CLKSOURCE_LSE             (RCC_CCIPR1_USART1SEL_0 | RCC_CCIPR1_USART1SEL_1)
/**
  * @}
  */

#if defined (USART2)
/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1           0x00000000U
#define RCC_USART2CLKSOURCE_SYSCLK          RCC_CCIPR1_USART2SEL_0
#define RCC_USART2CLKSOURCE_HSI             RCC_CCIPR1_USART2SEL_1
#define RCC_USART2CLKSOURCE_LSE             (RCC_CCIPR1_USART2SEL_0 | RCC_CCIPR1_USART2SEL_1)
/**
  * @}
  */
#endif


#if defined (I2C1)
/** @defgroup RCCEx_I2C1_Clock_Source I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1             0x00000000U
#define RCC_I2C1CLKSOURCE_SYSCLK            RCC_CCIPR1_I2C1SEL_0
#define RCC_I2C1CLKSOURCE_HSI               RCC_CCIPR1_I2C1SEL_1
/**
  * @}
  */
#endif




#if defined (LPTIM2)
/** @defgroup RCCEx_LPTIM2_Clock_Source LPTIM2 Clock Source
  * @{
  */
#define RCC_LPTIM2CLKSOURCE_PCLK1           0x00000000U
#define RCC_LPTIM2CLKSOURCE_LSI             RCC_CCIPR1_LPTIM2SEL_0
#define RCC_LPTIM2CLKSOURCE_HSI             RCC_CCIPR1_LPTIM2SEL_1
#define RCC_LPTIM2CLKSOURCE_LSE             RCC_CCIPR1_LPTIM2SEL
/**
  * @}
  */
#endif

#if defined (SPI1)
/** @defgroup RCCEx_SPI1_Clock_Source SPI1 Clock Source
  * @{
  */
#define RCC_SPI1CLKSOURCE_PCLK2             0x00000000U
#define RCC_SPI1CLKSOURCE_SYSCLK            RCC_CCIPR1_SPI1SEL_0
#define RCC_SPI1CLKSOURCE_HSI               RCC_CCIPR1_SPI1SEL_1
/**
  * @}
  */
#endif

/** @defgroup RCCEx_SYSTICK_Clock_Source SYSTICK Clock Source
  * @{
  */
#define RCC_SYSTICKCLKSOURCE_HCLK_DIV8      0x00000000U
#define RCC_SYSTICKCLKSOURCE_LSI            RCC_CCIPR1_SYSTICKSEL_0
#define RCC_SYSTICKCLKSOURCE_LSE            RCC_CCIPR1_SYSTICKSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_TIMIC_Clock_Source RCC Timicsel Items
  * @{
  */
#define RCC_TIMICCLKSOURCE_HSI              0x00000000U             /*!< HSI selected for Timer16/17 and LPTimer2 */
#define RCC_TIMICCLKSOURCE_HSI_DIV256       RCC_CCIPR1_TIMICSEL     /*!< HSI/256 selected for Timer16/17 and LPTimer2 */
/**
  * @}
  */

#if defined (SAI1)
/** @defgroup RCCEx_SAI1_Clock_Source SAI1 Clock Source
  * @{
  */
#define RCC_SAI1CLKSOURCE_PLL1P             0x00000000U
#define RCC_SAI1CLKSOURCE_PLL1Q             RCC_CCIPR2_SAI1SEL_0
#define RCC_SAI1CLKSOURCE_SYSCLK            RCC_CCIPR2_SAI1SEL_1
#define RCC_SAI1CLKSOURCE_PIN               (RCC_CCIPR2_SAI1SEL_1 | RCC_CCIPR2_SAI1SEL_0)
#define RCC_SAI1CLKSOURCE_HSI               RCC_CCIPR2_SAI1SEL_2
/**
  * @}
  */
#endif

/** @defgroup RCCEx_RNG_Clock_Source  RCCEx RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_LSE                0x00000000U
#define RCC_RNGCLKSOURCE_LSI                RCC_CCIPR2_RNGSEL_0
#define RCC_RNGCLKSOURCE_HSI                RCC_CCIPR2_RNGSEL_1
#define RCC_RNGCLKSOURCE_PLL1Q              (RCC_CCIPR2_RNGSEL_0 | RCC_CCIPR2_RNGSEL_1)
/**
  * @}
  */


#if defined (RCC_CCIPR2_ASSEL)
/** @defgroup RCCEx_AudioSync_Clock_Source Audio Sync Clock Source
  * @{
  */
#define RCC_ASCLKSOURCE_PLL1P               0x00000000U
#define RCC_ASCLKSOURCE_PLL1Q               RCC_CCIPR2_ASSEL
/**
  * @}
  */
#endif

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK7          0x00000000U
#define RCC_LPUART1CLKSOURCE_SYSCLK         RCC_CCIPR3_LPUART1SEL_0
#define RCC_LPUART1CLKSOURCE_HSI            RCC_CCIPR3_LPUART1SEL_1
#define RCC_LPUART1CLKSOURCE_LSE            (RCC_CCIPR3_LPUART1SEL_0 | RCC_CCIPR3_LPUART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_SPI3_Clock_Source SPI3 Clock Source
  * @{
  */
#define RCC_SPI3CLKSOURCE_PCLK7             0x00000000U
#define RCC_SPI3CLKSOURCE_SYSCLK            RCC_CCIPR3_SPI3SEL_0
#define RCC_SPI3CLKSOURCE_HSI               RCC_CCIPR3_SPI3SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK7             0x00000000U
#define RCC_I2C3CLKSOURCE_SYSCLK            RCC_CCIPR3_I2C3SEL_0
#define RCC_I2C3CLKSOURCE_HSI               RCC_CCIPR3_I2C3SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK7           0x00000000U
#define RCC_LPTIM1CLKSOURCE_LSI             RCC_CCIPR3_LPTIM1SEL_0
#define RCC_LPTIM1CLKSOURCE_HSI             RCC_CCIPR3_LPTIM1SEL_1
#define RCC_LPTIM1CLKSOURCE_LSE             RCC_CCIPR3_LPTIM1SEL
/**
  * @}
  */

/** @defgroup RCCEx_ADC_Clock_Source ADC4 Clock Source
  * @{
  */
#define RCC_ADCCLKSOURCE_HCLK               0x00000000U
#define RCC_ADCCLKSOURCE_SYSCLK             RCC_CCIPR3_ADCSEL_0
#define RCC_ADCCLKSOURCE_PLL1P              RCC_CCIPR3_ADCSEL_1
#define RCC_ADCCLKSOURCE_HSE                (RCC_CCIPR3_ADCSEL_0 | RCC_CCIPR3_ADCSEL_1)
#define RCC_ADCCLKSOURCE_HSI                RCC_CCIPR3_ADCSEL_2
/**
  * @}
  */

/** @defgroup RCC_RadioSleepTimer_Clock_Source Radio Sleep Timer Source
  * @{
  */
#define RCC_RADIOSTCLKSOURCE_DISABLE        0x00000000U             /*!< No clock selected, 2.4 GHz RADIO sleep timer kernel clock disabled */
#define RCC_RADIOSTCLKSOURCE_LSE            RCC_BDCR1_RADIOSTSEL_0  /*!< LSE oscillator clock selected */
#define RCC_RADIOSTCLKSOURCE_LSI            RCC_BDCR1_RADIOSTSEL_1  /*!< LSI oscillator clock selected */
#define RCC_RADIOSTCLKSOURCE_HSE_DIV1000    RCC_BDCR1_RADIOSTSEL    /*!< HSE32 oscillator clock divided by 1000 selected */
/**
  * @}
  */

/** @defgroup RCCEx_LSCO_Clock_Source Low Speed Clock Source
  * @{
  */
#define RCC_LSCOSOURCE_LSI                  0x00000000U           /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE                  RCC_BDCR1_LSCOSEL     /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/** @defgroup RCCEx_LSE_Trimming LSE Trimming
  * @{
  */
#define RCC_LSETRIMMING_R                   0x00000000U           /*!< Current source resistance R       */
#define RCC_LSETRIMMING_3_4_R               RCC_BDCR1_LSETRIM_0   /*!< Current source resistance 3/4 * R */
#define RCC_LSETRIMMING_2_3_R               RCC_BDCR1_LSETRIM_1   /*!< Current source resistance 2/3 * R */
#define RCC_LSETRIMMING_1_2_R               RCC_BDCR1_LSETRIM     /*!< Current source resistance 1/2 * R */
/**
  * @}
  */

#if defined(RCC_LSI2_SUPPORT)
/** @defgroup RCCEx_LSI2_Frequency_Temperature_Sensitivity LSI2 Frequency Temperature Sensitivity
  * @{
  */
#define RCC_LSI2_FREQTEMPSENS_80            0x00000000U           /*!< LSI2 frequency temperature sensitivity is close to zero at +80 degrees C */
#define RCC_LSI2_FREQTEMPSENS_50            RCC_BDCR2_LSI2CFG_0   /*!< LSI2 frequency temperature sensitivity is close to zero at +50 degrees C */
#define RCC_LSI2_FREQTEMPSENS_20            RCC_BDCR2_LSI2CFG_1   /*!< LSI2 frequency temperature sensitivity is close to zero at +20 degrees C */
/**
  * @}
  */

/** @defgroup RCCEx_LSI2_Operating_Mode LSI2 Operating Mode
  * @{
  */
#define RCC_LSI2_MODE_NOMINAL               0x00000000U           /*!< Nominal-power, high accuracy  */
#define RCC_LSI2_MODE_LP                    RCC_BDCR2_LSI2MODE_0  /*!< Low-power, medium accuracy    */
#define RCC_LSI2_MODE_ULP                   RCC_BDCR2_LSI2MODE_1  /*!< Ultra-low-power, low accuracy */
/**
  * @}
  */
#endif /* RCC_BDCR1_LSI2ON */


/** @defgroup RCCEx_RADIO_Bus_Clock_Readiness 2.4 GHz RADIO bus clock readiness
  * @{
  */
#define RCC_RADIO_BUS_CLOCK_NOT_READY       0x00000000U                /*!< 2.4 GHz RADIO bus clock not ready */
#define RCC_RADIO_BUS_CLOCK_READY           RCC_RADIOENR_RADIOCLKRDY   /*!< 2.4 GHz RADIO bus clock ready     */
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

/** @brief  Macro to configure the USART1 clock (USART1CLK).
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART1SEL, (__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART1SEL)

#if defined (USART2)
/** @brief  Macro to configure the USART2 clock (USART2CLK).
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART2SEL, (__USART2_CLKSOURCE__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART2SEL)
#endif


#if defined (I2C1)
/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  * @param  __I2C1_CLKSOURCE__ specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  * @retval None
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I2C1SEL, (__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I2C1SEL)
#endif




#if defined (LPTIM2)
/** @brief  Macro to configure the LPTIM2 clock (LPTIM2CLK).
  * @param  __LPTIM2_CLKSOURCE__ specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  LSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_LPTIM2SEL, (__LPTIM2_CLKSOURCE__))

/** @brief  Macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_LPTIM2SEL)
#endif

#if defined (SPI1)
/** @brief  macro to configure the SPI1 clock source.
  * @param  __SPI1_CLKSOURCE__ specifies the SPI1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SPI1CLKSOURCE_PCLK2 : PCLK2 Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_SYSCLK : SYSCLK Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_HSI : HSI Clock selected as SPI1 clock
  */
#define __HAL_RCC_SPI1_CONFIG(__SPI1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SPI1SEL, (__SPI1_CLKSOURCE__))

/** @brief  macro to get the SPI1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI1CLKSOURCE_PCLK2 : PCLK2 Clock used as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_SYSCLK : SYSCLK Clock used as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_HSI : HSI Clock used as SPI1 clock
  */
#define __HAL_RCC_GET_SPI1_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SPI1SEL)
#endif

/** @brief  macro to configure the SYSTICK clock source.
  * @param  __SYSTICK_CLKSOURCE__ specifies the SYSTICK clock source.
  *            @arg RCC_SYSTICKCLKSOURCE_HCLK_DIV8 : HCLK divided by 8 Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSI : LSI Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSE : LSE Clock selected as SYSTICK clock
  */
#define __HAL_RCC_SYSTICK_CONFIG(__SYSTICK_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, (__SYSTICK_CLKSOURCE__))

/** @brief  macro to get the SYSTICK clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SYSTICKCLKSOURCE_HCLK_DIV8 : HCLK divided by 8 Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSI : LSI Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSE : LSE Clock selected as SYSTICK clock
  */
#define __HAL_RCC_GET_SYSTICK_SOURCE()      READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL)

/** @brief  macro to configure the TIMIC clock source.
  * @param  __TIMIC_CLKSOURCE__ specifies the TIMIC clock source.
  *            @arg RCC_TIMICCLKSOURCE_HSI : HSI Clock selected as TIMIC clock
  *            @arg RCC_TIMICCLKSOURCE_HSI_DIV256 : HSI divided by 256 Clock selected as TIMIC clock
  */
#define __HAL_RCC_TIMIC_CONFIG(__TIMIC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL, (__TIMIC_CLKSOURCE__))

/** @brief  macro to get the TIMIC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_TIMICCLKSOURCE_HSI : HSI Clock selected as TIMIC clock
  *            @arg RCC_TIMICCLKSOURCE_HSI_DIV256 : HSI divided by 256 Clock selected as TIMIC clock
  */
#define __HAL_RCC_GET_TIMIC_SOURCE()        READ_BIT(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL)

#if defined (SAI1)
/**
  * @brief  Macro to configure the SAI1 clock source.
  * @param  __SAI1_CLKSOURCE__ defines the SAI1 clock source. This clock is derived
  *         from the PLL2, system PLL1 or external clock (through a dedicated pin).
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL1P SAI1 clock = PLL1 "P" clock (PLL1PCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL1Q  SAI1 clock = PLL1 "Q" clock (PLL1QCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_SYSCLK SAI1 clock = System Clock
  *             @arg @ref RCC_SAI1CLKSOURCE_PIN  SAI1 clock = External Clock (SAI1_EXTCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_HSI  SAI1 clock = HSI16
  * @retval None
  */
#define __HAL_RCC_SAI1_CONFIG(__SAI1_CLKSOURCE__)\
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SAI1SEL, (__SAI1_CLKSOURCE__))

/** @brief  Macro to get the SAI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL1P SAI1 clock = PLL1 "P" clock (PLL1PCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL1Q  SAI1 clock = PLL1 "Q" clock (PLL1QCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_SYSCLK SAI1 clock = System Clock
  *             @arg @ref RCC_SAI1CLKSOURCE_PIN  SAI1 clock = External Clock (SAI1_EXTCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_HSI  SAI1 clock = HSI16
  */
#define __HAL_RCC_GET_SAI1_SOURCE()         READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SAI1SEL)
#endif


#if defined (RCC_CCIPR2_ASSEL)
/** @brief  macro to configure the Audio Sync clock source.
  * @param  __AS_CLKSOURCE__ specifies the Audio Sync clock source.
  *            @arg RCC_ASCLKSOURCE_PLL1P : PLL1P Clock selected as Audio Sync clock
  *            @arg RCC_ASCLKSOURCE_PLL1Q : PLL1Q Clock selected as Audio Sync clock
  */
#define __HAL_RCC_AUDIOSYNC_CONFIG(__AS_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ASSEL, (__AS_CLKSOURCE__))

/** @brief  macro to get the Audio Sync clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ASCLKSOURCE_PLL1P : PLL1P Clock selected as Audio Sync clock
  *            @arg RCC_ASCLKSOURCE_PLL1Q : PLL1Q Clock selected as Audio Sync clock
  */
#define __HAL_RCC_GET_AUDIOSYNC_SOURCE()        READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ASSEL)
#endif

/** @brief macro to configure the RNG clock (RNGCLK).
  * @param  __RNG_CLKSOURCE__: specifies the RNG clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI: HSI selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_LSI: LSI selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_LSE: LSE selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_PLL1Q: PLL1Q selected as RNG clock
  * @retval None
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_RNGSEL, (__RNG_CLKSOURCE__))

/** @brief  macro to get the RNG clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI: HSI selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_LSI: LSI selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_LSE: LSE selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_PLL1Q: PLL1Q selected as RNG clock
  */
#define __HAL_RCC_GET_RNG_SOURCE()          READ_BIT(RCC->CCIPR2, RCC_CCIPR2_RNGSEL)

/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK7  PCLK7 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL, (__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK7  PCLK7 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE()      READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL)

/** @brief  macro to configure the SPI3 clock source.
  * @param  __SPI3_CLKSOURCE__ specifies the SPI3 clock source.es:
  *            @arg RCC_SPI3CLKSOURCE_PCLK7 : PCLK7 selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_SYSCLK : SYSCLK Clock selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_HSI : HSI Clock selected as SPI3 clock
  */
#define __HAL_RCC_SPI3_CONFIG(__SPI3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SPI3SEL, (__SPI3_CLKSOURCE__))

/** @brief  macro to get the SPI3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI3CLKSOURCE_PCLK7 : PCLK7 selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_SYSCLK : SYSCLK Clock selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_HSI : HSI Clock selected as SPI3 clock
  */
#define __HAL_RCC_GET_SPI3_SOURCE()         READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SPI3SEL)

/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  * @param  __I2C3_CLKSOURCE__ specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK7 : PCLK7 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK : HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI : MSIK selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_I2C3SEL, (__I2C3_CLKSOURCE__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK7 : PCLK7 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK : HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI : MSIK selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE()         READ_BIT(RCC->CCIPR3, RCC_CCIPR3_I2C3SEL)


/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK7  PCLK7 selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL, (__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK7  PCLK7 selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE()       READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL)

/** @brief  Macro to configure the ADC4 interface clock.
  * @param  __ADC_CLKSOURCE__ specifies the ADC4 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_HCLK    HCLK clock selected as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK  SYSCLK clock selected as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_PLL1P   PLL1P clock selected as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSE     HSE clock selected as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI     HSI clock selected as ADC4 clock
  * @retval None
  */
#define __HAL_RCC_ADC_CONFIG(__ADC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ADCSEL, (__ADC_CLKSOURCE__))

/** @brief  Macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_HCLK    HCLK clock used as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK  SYSCLK clock used as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_PLL1P   PLL1P clock used as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSE     HSE clock used as ADC4 clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI     HSI clock used as ADC4 clock
  */
#define __HAL_RCC_GET_ADC_SOURCE()          READ_BIT(RCC->CCIPR3, RCC_CCIPR3_ADCSEL)

/** @brief  Macro to configure the RADIO Sleep timer clock source.
  * @param  __RADIOST_CLKSOURCE__ specifies the Radio sleep timer clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RADIOSTCLKSOURCE_DISABLE     2.4 GHz RADIO sleep timer kernel clock disabled
  *            @arg @ref RCC_RADIOSTCLKSOURCE_LSE         LSE oscillator clock selected
  *            @arg @ref RCC_RADIOSTCLKSOURCE_LSI         LSI oscillator clock selected
  *            @arg @ref RCC_RADIOSTCLKSOURCE_HSE_DIV1000 HSE32 oscillator clock divided by 1000 selected
  * @retval None
  */
#define __HAL_RCC_RADIOSLPTIM_CONFIG(__RADIOST_CLKSOURCE__) \
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_RADIOSTSEL, (__RADIOST_CLKSOURCE__))

/** @brief  Macro to get the RADIO Sleep timer clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_RADIOSTCLKSOURCE_DISABLE     2.4 GHz RADIO sleep timer kernel clock disabled
  *            @arg @ref RCC_RADIOSTCLKSOURCE_LSE         LSE oscillator clock selected
  *            @arg @ref RCC_RADIOSTCLKSOURCE_LSI         LSI oscillator clock selected
  *            @arg @ref RCC_RADIOSTCLKSOURCE_HSE_DIV1000 HSE32 oscillator clock divided by 1000 selected
  */
#define __HAL_RCC_GET_RADIOSLPTIM_SOURCE()  READ_BIT(RCC->BDCR1, RCC_BDCR1_RADIOSTSEL)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);
/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group2 Extended Clock management functions
  * @{
  */
void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);
void              HAL_RCCEx_HSESetTrimming(uint32_t Trimming);
uint32_t          HAL_RCCEx_HSEGetTrimming(void);
void              HAL_RCCEx_LSESetTrimming(uint32_t Trimming);
uint32_t          HAL_RCCEx_LSEGetTrimming(void);
#if defined(RCC_LSI2_SUPPORT)
void              HAL_RCCEx_LSI2SetConfig(const RCC_LSIConfigTypeDef *pConfig);
void              HAL_RCCEx_LSI2GetConfig(RCC_LSIConfigTypeDef *pConfig);
#endif /* RCC_BDCR1_LSI2ON */
/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group3 Radio Clock management functions
  * @{
  */
void              HAL_RCCEx_EnableRadioBBClock(void);
void              HAL_RCCEx_DisableRadioBBClock(void);
void              HAL_RCCEx_EnableRequestUponRadioWakeUpEvent(void);
void              HAL_RCCEx_DisableRequestUponRadioWakeUpEvent(void);
uint32_t          HAL_RCCEx_GetRadioBusClockReadiness(void);
/**
  * @}
  */

#if defined(RCC_CCIPR2_ASSEL)
/** @defgroup RCCEx_Exported_Functions_Group4 Audio Synchronization management functions
  * @{
  */
void              HAL_RCCEx_EnableAudioSyncClock(void);
void              HAL_RCCEx_DisableAudioSyncClock(void);
HAL_StatusTypeDef HAL_RCCEx_SetConfigAudioSync(const RCC_AudioSyncConfigTypeDef *pConf);
void              HAL_RCCEx_GetConfigAudioSync(RCC_AudioSyncConfigTypeDef *pConf);
uint32_t          HAL_RCCEx_GetAudioSyncCounterValue(void);
uint32_t          HAL_RCCEx_GetAudioSyncCaptureValue(void);
/**
  * @}
  */
#endif /* RCC_CCIPR2_ASSEL */

/**
  * @}
  */

/** @defgroup RCCEx_Private_Constants Private Constants
  * @{
  */
/* Define used for IS_RCC_* macros below */
#if   defined (STM32WBA54xx) || defined (STM32WBA55xx)
#if !defined (STM32WBAXX_SI_CUT1_0)
#define RCC_PERIPHCLOCK_ALL             (RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2C1    | \
                                         RCC_PERIPHCLK_LPTIM2  | RCC_PERIPHCLK_SPI1   | RCC_PERIPHCLK_SYSTICK | \
                                         RCC_PERIPHCLK_TIMIC   | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_RNG     | \
                                         RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_SPI3   | RCC_PERIPHCLK_I2C3    | \
                                         RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_ADC    | RCC_PERIPHCLK_RTC     | \
                                         RCC_PERIPHCLK_RADIOST | RCC_PERIPHCLK_AUDIOSYNC)
#else
#define RCC_PERIPHCLOCK_ALL             (RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2C1    | \
                                         RCC_PERIPHCLK_LPTIM2  | RCC_PERIPHCLK_SPI1   | RCC_PERIPHCLK_SYSTICK | \
                                         RCC_PERIPHCLK_TIMIC   | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_RNG     | \
                                         RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_SPI3   | RCC_PERIPHCLK_I2C3    | \
                                         RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_ADC    | RCC_PERIPHCLK_RTC     | \
                                         RCC_PERIPHCLK_RADIOST)
#endif
#elif defined (STM32WBA52xx)
#define RCC_PERIPHCLOCK_ALL             (RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2C1    | \
                                         RCC_PERIPHCLK_LPTIM2  | RCC_PERIPHCLK_SPI1   | RCC_PERIPHCLK_SYSTICK | \
                                         RCC_PERIPHCLK_TIMIC                          | RCC_PERIPHCLK_RNG     | \
                                         RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_SPI3   | RCC_PERIPHCLK_I2C3    | \
                                         RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_ADC    | RCC_PERIPHCLK_RTC     | \
                                         RCC_PERIPHCLK_RADIOST)
#elif defined (STM32WBA50xx)
#define RCC_PERIPHCLOCK_ALL             (RCC_PERIPHCLK_USART1                                                 | \
                                                                                        RCC_PERIPHCLK_SYSTICK | \
                                         RCC_PERIPHCLK_TIMIC                          | RCC_PERIPHCLK_RNG     | \
                                         RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_SPI3   | RCC_PERIPHCLK_I2C3    | \
                                         RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_ADC    | RCC_PERIPHCLK_RTC     | \
                                         RCC_PERIPHCLK_RADIOST)
#endif
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Macros Private Macros
  * @{
  */
#define IS_RCC_PERIPHCLOCK(__SELECTION__)         ((((__SELECTION__) & RCC_PERIPHCLOCK_ALL) != 0x00u) && \
                                                   (((__SELECTION__) & ~RCC_PERIPHCLOCK_ALL) == 0x00u))

#define IS_RCC_USART1CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                                   ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI)    || \
                                                   ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE))

#if defined(USART2)
#define IS_RCC_USART2CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_USART2CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI)    || \
                                                   ((__SOURCE__) == RCC_USART2CLKSOURCE_LSE))
#endif


#if defined(I2C1)
#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSI))
#endif




#if defined (LPTIM2)
#define IS_RCC_LPTIM2CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_LPTIM2CLKSOURCE_PCLK1) || \
                                                   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSI)   || \
                                                   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_HSI)   || \
                                                   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSE))
#endif

#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PCLK7) || \
                                                   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)   || \
                                                   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI)   || \
                                                   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))

#if defined (SPI1)
#define IS_RCC_SPI1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SPI1CLKSOURCE_PCLK2)  || \
                                                   ((__SOURCE__) == RCC_SPI1CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_SPI1CLKSOURCE_HSI))
#endif

#define IS_RCC_SYSTICKCLKSOURCE(__SOURCE__)       (((__SOURCE__) == RCC_SYSTICKCLKSOURCE_HCLK_DIV8)  || \
                                                   ((__SOURCE__) == RCC_SYSTICKCLKSOURCE_LSI)        || \
                                                   ((__SOURCE__) == RCC_SYSTICKCLKSOURCE_LSE))

#define IS_RCC_TIMICCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_TIMICCLKSOURCE_HSI)  || \
                                                   ((__SOURCE__) == RCC_TIMICCLKSOURCE_HSI_DIV256))

#if defined(SAI1)
#define IS_RCC_SAI1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL1P)  || \
                                                   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL1Q)  || \
                                                   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PIN)    || \
                                                   ((__SOURCE__) == RCC_SAI1CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_SAI1CLKSOURCE_HSI))
#endif

#define IS_RCC_RNGCLKSOURCE(__SOURCE__)           (((__SOURCE__) == RCC_RNGCLKSOURCE_LSE)   || \
                                                   ((__SOURCE__) == RCC_RNGCLKSOURCE_LSI)   || \
                                                   ((__SOURCE__) == RCC_RNGCLKSOURCE_HSI)   || \
                                                   ((__SOURCE__) == RCC_RNGCLKSOURCE_PLL1Q))


#if defined (RCC_CCIPR2_ASSEL)
#define IS_RCC_ASCLKSOURCE(__SOURCE__)            (((__SOURCE__) == RCC_ASCLKSOURCE_PLL1P)  || \
                                                   ((__SOURCE__) == RCC_ASCLKSOURCE_PLL1Q))
#endif

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)       (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK7)  || \
                                                   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI)    || \
                                                   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE))

#define IS_RCC_SPI3CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SPI3CLKSOURCE_PCLK7)  || \
                                                   ((__SOURCE__) == RCC_SPI3CLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_SPI3CLKSOURCE_HSI))

#define IS_RCC_I2C3CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I2C3CLKSOURCE_PCLK7)   || \
                                                   ((__SOURCE__) == RCC_I2C3CLKSOURCE_SYSCLK ) || \
                                                   ((__SOURCE__) == RCC_I2C3CLKSOURCE_HSI))

#define IS_RCC_ADCCLKSOURCE(__SOURCE__)           (((__SOURCE__) == RCC_ADCCLKSOURCE_HCLK)   || \
                                                   ((__SOURCE__) == RCC_ADCCLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_ADCCLKSOURCE_PLL1P)  || \
                                                   ((__SOURCE__) == RCC_ADCCLKSOURCE_HSE)    || \
                                                   ((__SOURCE__) == RCC_ADCCLKSOURCE_HSI))

#define IS_RCC_RADIOSLEEPTIMERSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_RADIOSTCLKSOURCE_DISABLE)   || \
                                                   ((__SOURCE__) == RCC_RADIOSTCLKSOURCE_LSE)    || \
                                                   ((__SOURCE__) == RCC_RADIOSTCLKSOURCE_LSI)    || \
                                                   ((__SOURCE__) == RCC_RADIOSTCLKSOURCE_HSE_DIV1000))

#define IS_RCC_LSCOSOURCE(__SOURCE__)             (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                                   ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#define IS_RCC_HSETRIM(__TRIM__)                  ((__TRIM__) <= (RCC_ECSCR1_HSETRIM >> RCC_ECSCR1_HSETRIM_Pos))

#define IS_RCC_LSETRIM(__SOURCE__)                (((__SOURCE__) == RCC_LSETRIMMING_R)     || \
                                                   ((__SOURCE__) == RCC_LSETRIMMING_3_4_R) || \
                                                   ((__SOURCE__) == RCC_LSETRIMMING_2_3_R) || \
                                                   ((__SOURCE__) == RCC_LSETRIMMING_1_2_R))

#if defined(RCC_LSI2_SUPPORT)
#define IS_RCC_LSI2_FREQTEMPSENS(__SENS__)        (((__SENS__) == RCC_LSI2_FREQTEMPSENS_80)   || \
                                                   ((__SENS__) == RCC_LSI2_FREQTEMPSENS_50)   || \
                                                   ((__SENS__) == RCC_LSI2_FREQTEMPSENS_20))

#define IS_RCC_LSI2_OPERATINGMODE(__MODE__)       (((__MODE__) == RCC_LSI2_MODE_NOMINAL)  || \
                                                   ((__MODE__) == RCC_LSI2_MODE_LP)       || \
                                                   ((__MODE__) == RCC_LSI2_MODE_ULP))
#endif /* RCC_BDCR1_LSI2ON */

#if defined(RCC_CCIPR2_ASSEL)
#define IS_RCC_AUDIOSYNC_CAPTUREPRESCALER(__PRESCALER__)  ((__PRESCALER__) <= (RCC_ASCR_CPS >> RCC_ASCR_CPS_Pos))

#define IS_RCC_AUDIOSYNC_CLOCKPRESCALER(__PRESCALER__)    ((__PRESCALER__) <= (RCC_ASCR_PSC >> RCC_ASCR_PSC_Pos))

#define IS_RCC_AUDIOSYNC_AUTORELOAD(__VALUE__)  ((__VALUE__) <= (RCC_ASARR_AR >> RCC_ASARR_AR_Pos))

#define IS_RCC_AUDIOSYNC_COMPARE(__VALUE__)     ((__VALUE__) <= (RCC_ASCOR_CO >> RCC_ASCOR_CO_Pos))
#endif /* RCC_CCIPR2_ASSEL */

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

#endif /* __STM32WBAxx_HAL_RCC_EX_H */
