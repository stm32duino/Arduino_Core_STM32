/**
  ******************************************************************************
  * @file    stm32u3xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended  module.
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
#ifndef __STM32U3xx_HAL_RCC_EX_H
#define __STM32U3xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
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
  uint32_t PeriphClockSelection;          /*!< The Extended Clock to be configured.
                                               This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t Usart1ClockSelection;          /*!< Specifies USART1 clock source.
                                               This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart3ClockSelection;          /*!< Specifies USART3 clock source.
                                               This parameter can be a value of @ref RCCEx_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;           /*!< Specifies UART4 clock source.
                                               This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;           /*!< Specifies UART5 clock source.
                                               This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I3c1ClockSelection;            /*!< Specifies I3C1 clock source.
                                               This parameter can be a value of @ref RCCEx_I3C1_Clock_Source */

  uint32_t I2c1ClockSelection;            /*!< Specifies I2C1 clock source.
                                               This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;            /*!< Specifies I2C2 clock source.
                                               This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I3c2ClockSelection;            /*!< Specifies I3C2 clock source.
                                               This parameter can be a value of @ref RCCEx_I3C2_Clock_Source */

  uint32_t Spi2ClockSelection;            /*!< Specifies SPI2 clock source
                                               This parameter can be a value of @ref RCCEx_SPI2_Clock_Source */

  uint32_t Lptim2ClockSelection;          /*!< Specifies LPTIM2 clock source.
                                               This parameter can be a value of @ref RCCEx_LPTIM2_Clock_Source */

  uint32_t Spi1ClockSelection;            /*!< Specifies SPI1 clock source
                                               This parameter can be a value of @ref RCCEx_SPI1_Clock_Source */

  uint32_t SystickClockSelection;         /*!< Specifies SYSTICK clock source.
                                               This parameter can be a value of @ref RCCEx_SYSTICK_Clock_Source */

  uint32_t FdcanClockSelection;           /*!< Specifies FDCAN clock source.
                                               This parameter can be a value of @ref RCCEx_FDCAN_Clock_Source */

  uint32_t IclkClockSelection;            /*!< Specifies ICLK Intermediate clock source.
                                               This parameter can be a value of @ref RCCEx_ICLK_Clock_Source */

  uint32_t Usb1ClockSelection;            /*!< Specifies USB1 clock source.
                                               This parameter can be a value of @ref RCCEx_USB1_Clock_Source */

  uint32_t TimIcClockSelection;           /*!< Specifies TIMIC clock source.
                                               This parameter can be a value of @ref RCCEx_TIMIC_Clock_Source */

  uint32_t Adf1ClockSelection;            /*!< Specifies ADF1 clock source
                                               This parameter can be a value of @ref RCCEx_ADF1_Clock_Source */

  uint32_t Spi3ClockSelection;            /*!< Specifies SPI3 clock source
                                               This parameter can be a value of @ref RCCEx_SPI3_Clock_Source */

  uint32_t Sai1ClockSelection;            /*!< Specifies SAI1 clock source.
                                               This parameter can be a value of @ref RCCEx_SAI1_Clock_Source */

  uint32_t RngClockSelection;             /*!< Specifies RNG clock source
                                               This parameter can be a value of @ref RCCEx_RNG_Clock_Source */

  uint32_t AdcDacClockSelection;          /*!< Specifies ADCDAC clock source.
                                               This parameter can be a value of @ref RCCEx_ADCDAC_Clock_Source */

  uint32_t AdcDacClockDivider;            /*!< Specifies ADCDAC clock divider.
                                               This parameter can be a value of @ref RCCEx_ADCDACDIV_Clock_Divider */

  uint32_t Dac1SampleHoldClockSelection;  /*!< Specifies DAC1 sample and hold clock source.
                                               This parameter can be a value of @ref RCCEx_DAC1_Sample_Hold_Clock_Source */

  uint32_t Octospi1ClockSelection;        /*!< Specifies OCTOSPI1 interface clock source.
                                               This parameter can be a value of @ref RCCEx_OCTOSPI1_Clock_Source */

  uint32_t Lpuart1ClockSelection;         /*!< Specifies LPUART1 clock source
                                               This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */

  uint32_t I2c3ClockSelection;            /*!< Specifies I2C3 clock source
                                               This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Lptim34ClockSelection;         /*!< Specifies LPTIM34 clock source.
                                               This parameter can be a value of @ref RCCEx_LPTIM34_Clock_Source */

  uint32_t Lptim1ClockSelection;          /*!< Specifies LPTIM1 clock source
                                               This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */

#if defined(USART2)
  uint32_t Usart2ClockSelection;          /*!< Specifies USART2 clock source.
                                               This parameter can be a value of @ref RCCEx_UART2_Clock_Source */
#endif /* USART2 */

#if defined(I2C4)
  uint32_t I2c4ClockSelection;            /*!< Specifies I2C4 clock source.
                                               This parameter can be a value of @ref RCCEx_I2C4_Clock_Source */
#endif /* I2C4 */

#if defined(SPI4)
  uint32_t Spi4ClockSelection;            /*!< Specifies SPI4 clock source
                                               This parameter can be a value of @ref RCCEx_SPI4_Clock_Source */
#endif /* SPI4 */

  uint32_t RTCClockSelection;             /*!< Specifies RTC clock source.
                                               This parameter can be a value of @ref RCC_RTC_Clock_Source */
} RCC_PeriphCLKInitTypeDef;

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t State;                         /*!< The PLL Mode state.
                                               This parameter can be a value of @ref RCC_MSIRCx_PLL_State */

  uint32_t InputSrce;                     /*!< The PLL input clock source to be selected.
                                               This parameter can be a value of @ref RCC_MSIRCx_PLL_Input */

  uint32_t FastMode;                      /*!< Specifies if Fast mode is enabled or not.
                                               This parameter can be a value of @ref RCC_MSIRCx_PLL_Fast */

  uint32_t MSIRC1PLLN;                    /*!< Specifies LSE multiplication factor for MSIRC1 only.
                                               This parameter can be a value of @ref RCC_MSIRC1_PLLN*/
} RCC_MSIRCxPLLTypeDef;
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Exported_Types RCCEx CRS Exported Types
  * @{
  */
/**
  * @brief RCC_CRS Init structure definition
  */
typedef struct
{
  uint32_t Prescaler;             /*!< Specifies the division factor of the SYNC signal.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroDivider */

  uint32_t Source;                /*!< Specifies the SYNC signal source.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroSource */

  uint32_t Polarity;              /*!< Specifies the input polarity for the SYNC signal source.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroPolarity */

  uint32_t ReloadValue;           /*!< Specifies the value to be loaded in the frequency error counter with each SYNC event.
                                       It can be calculated in using macro __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)
                                       This parameter must be a number between 0 and 0xFFFF or a value of @ref RCCEx_CRS_ReloadValueDefault .*/

  uint32_t ErrorLimitValue;       /*!< Specifies the value to be used to evaluate the captured frequency error value.
                                       This parameter must be a number between 0 and 0xFF or a value of @ref RCCEx_CRS_ErrorLimitDefault */

  uint32_t HSI48CalibrationValue; /*!< Specifies a user-programmable trimming value to the HSI48 oscillator.
                                       This parameter must be a number between 0 and 0x7F or a value of @ref RCCEx_CRS_HSI48CalibrationDefault */

} RCC_CRSInitTypeDef;

/**
  * @brief RCC_CRS Synchronization structure definition
  */
typedef struct
{
  uint32_t ReloadValue;           /*!< Specifies the value loaded in the Counter reload value.
                                       This parameter must be a number between 0 and 0xFFFF */

  uint32_t HSI48CalibrationValue; /*!< Specifies value loaded in HSI48 oscillator smooth trimming.
                                       This parameter must be a number between 0 and 0x7F */

  uint32_t FreqErrorCapture;      /*!< Specifies the value loaded in the .FECAP, the frequency error counter
                                       value latched in the time of the last SYNC event.
                                       This parameter must be a number between 0 and 0xFFFF */

  uint32_t FreqErrorDirection;    /*!< Specifies the value loaded in the .FEDIR, the counting direction of the
                                       frequency error counter latched in the time of the last SYNC event.
                                       It shows whether the actual frequency is below or above the target.
                                       This parameter must be a value of @ref RCCEx_CRS_FreqErrorDirection*/

} RCC_CRSSynchroInfoTypeDef;
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
#define RCC_PERIPHCLK_USART3                0x00000002U
#define RCC_PERIPHCLK_UART4                 0x00000004U
#define RCC_PERIPHCLK_UART5                 0x00000008U
#define RCC_PERIPHCLK_I3C1                  0x00000010U
#define RCC_PERIPHCLK_I2C1                  0x00000020U
#define RCC_PERIPHCLK_I2C2                  0x00000040U
#define RCC_PERIPHCLK_I3C2                  0x00000080U
#define RCC_PERIPHCLK_SPI2                  0x00000100U
#define RCC_PERIPHCLK_LPTIM2                0x00000200U
#define RCC_PERIPHCLK_SPI1                  0x00000400U
#define RCC_PERIPHCLK_SYSTICK               0x00000800U
#define RCC_PERIPHCLK_FDCAN                 0x00001000U
#define RCC_PERIPHCLK_ICLK                  0x00002000U
#define RCC_PERIPHCLK_USB1                  0x00004000U
#define RCC_PERIPHCLK_TIMIC                 0x00008000U
#define RCC_PERIPHCLK_ADF1                  0x00010000U
#define RCC_PERIPHCLK_SPI3                  0x00020000U
#define RCC_PERIPHCLK_SAI1                  0x00040000U
#define RCC_PERIPHCLK_RNG                   0x00080000U
#define RCC_PERIPHCLK_ADCDAC                0x00100000U
#define RCC_PERIPHCLK_DAC1SH                0x00200000U
#define RCC_PERIPHCLK_OCTOSPI1              0x00400000U
#define RCC_PERIPHCLK_LPUART1               0x00800000U
#define RCC_PERIPHCLK_I2C3                  0x01000000U
#define RCC_PERIPHCLK_LPTIM34               0x02000000U
#define RCC_PERIPHCLK_LPTIM1                0x04000000U
#if defined(USART2)
#define RCC_PERIPHCLK_USART2                0x08000000U
#endif /* USART2 */
#if defined(I2C4)
#define RCC_PERIPHCLK_I2C4                  0x10000000U
#endif /* I2C4 */
#if defined(SPI4)
#define RCC_PERIPHCLK_SPI4                  0x20000000U
#endif /* SPI4 */
#define RCC_PERIPHCLK_RTC                   0x80000000U
/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2           0x00000000U
#define RCC_USART1CLKSOURCE_HSI             RCC_CCIPR1_USART1SEL
/**
  * @}
  */


/** @defgroup RCCEx_USART3_Clock_Source USART3 Clock Source
  * @{
  */
#define RCC_USART3CLKSOURCE_PCLK1           0x00000000U
#define RCC_USART3CLKSOURCE_HSI             RCC_CCIPR1_USART3SEL
/**
  * @}
  */

/** @defgroup RCCEx_UART4_Clock_Source UART4 Clock Source
  * @{
  */
#define RCC_UART4CLKSOURCE_PCLK1            0x00000000U
#define RCC_UART4CLKSOURCE_HSI              RCC_CCIPR1_UART4SEL
/**
  * @}
  */

/** @defgroup RCCEx_UART5_Clock_Source UART5 Clock Source
  * @{
  */
#define RCC_UART5CLKSOURCE_PCLK1            0x00000000U
#define RCC_UART5CLKSOURCE_HSI              RCC_CCIPR1_UART5SEL
/**
  * @}
  */

/** @defgroup RCCEx_I3C1_Clock_Source I3C1 Clock Source
  * @{
  */
#define RCC_I3C1CLKSOURCE_PCLK1             0x00000000U
#define RCC_I3C1CLKSOURCE_MSIK              RCC_CCIPR1_I3C1SEL
/**
  * @}
  */

/** @defgroup RCCEx_I2C1_Clock_Source I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1             0x00000000U
#define RCC_I2C1CLKSOURCE_MSIK              RCC_CCIPR1_I2C1SEL
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_PCLK1             0x00000000U
#define RCC_I2C2CLKSOURCE_MSIK              RCC_CCIPR1_I2C2SEL
/**
  * @}
  */

/** @defgroup RCCEx_I3C2_Clock_Source I3C2 Clock Source
  * @{
  */
#define RCC_I3C2CLKSOURCE_PCLK2             0x00000000U
#define RCC_I3C2CLKSOURCE_MSIK              RCC_CCIPR1_I3C2SEL
/**
  * @}
  */


/** @defgroup RCCEx_SPI2_Clock_Source SPI2 Clock Source
  * @{
  */
#define RCC_SPI2CLKSOURCE_PCLK1             0x00000000U
#define RCC_SPI2CLKSOURCE_MSIK              RCC_CCIPR1_SPI2SEL
/**
  * @}
  */

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

/** @defgroup RCCEx_SPI1_Clock_Source SPI1 Clock Source
  * @{
  */
#define RCC_SPI1CLKSOURCE_PCLK2             0x00000000U
#define RCC_SPI1CLKSOURCE_MSIK              RCC_CCIPR1_SPI1SEL
/**
  * @}
  */

/** @defgroup RCCEx_SYSTICK_Clock_Source SYSTICK Clock Source
  * @{
  */
#define RCC_SYSTICKCLKSOURCE_HCLK_DIV8      0x00000000U
#define RCC_SYSTICKCLKSOURCE_LSI            RCC_CCIPR1_SYSTICKSEL_0
#define RCC_SYSTICKCLKSOURCE_LSE            RCC_CCIPR1_SYSTICKSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_FDCAN_Clock_Source FDCAN Clock Source
  * @{
  */
#define RCC_FDCANCLKSOURCE_SYSCLK           0x00000000U
#define RCC_FDCANCLKSOURCE_MSIK             RCC_CCIPR1_FDCANSEL
/**
  * @}
  */


/** @defgroup RCCEx_ICLK_Clock_Source ICLK Clock Source
  * @{
  */
#define RCC_ICLKCLKSOURCE_HSI48             0x00000000U
#define RCC_ICLKCLKSOURCE_MSIK              RCC_CCIPR1_ICLKSEL_0
#define RCC_ICLKCLKSOURCE_HSE               RCC_CCIPR1_ICLKSEL_1
#define RCC_ICLKCLKSOURCE_SYSCLK            RCC_CCIPR1_ICLKSEL
/**
  * @}
  */

/** @defgroup RCCEx_USB1_Clock_Source USB1 Clock Source
  * @{
  */
#define RCC_USB1CLKSOURCE_ICLK              0x00000000U
#define RCC_USB1CLKSOURCE_ICLK_DIV2         RCC_CCIPR1_USB1SEL
/**
  * @}
  */


/** @defgroup RCCEx_TIMIC_Clock_Source TIMIC Clock Source
  * @{
  */
#define RCC_TIMICCLKSOURCE_DISABLE                0x00000000U             /*!< Input capture clock selection disable */
/*!< HSI/256, MSIS/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture */
#define RCC_TIMICCLKSOURCE_MSISDIV1024_MSISDIV4   RCC_CCIPR1_TIMICSEL_2
/*!< HSI/256, MSIS/1024 and MSIK/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture */
#define RCC_TIMICCLKSOURCE_MSISDIV1024_MSIKDIV4   (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_0)
/*!< HSI/256, MSIK/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture */
#define RCC_TIMICCLKSOURCE_MSIKDIV1024_MSISDIV4   (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1)
/*!< HSI/256, MSIK/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture */
#define RCC_TIMICCLKSOURCE_MSIKDIV1024_MSIKDIV4   (RCC_CCIPR1_TIMICSEL_2 | \
                                                   RCC_CCIPR1_TIMICSEL_1 | RCC_CCIPR1_TIMICSEL_0)
/**
  * @}
  */


/** @defgroup RCCEx_ADF1_Clock_Source ADF1 Clock Source
  * @{
  */
#define RCC_ADF1CLKSOURCE_HCLK              0x00000000U
#define RCC_ADF1CLKSOURCE_PIN               RCC_CCIPR2_ADF1SEL_0
#define RCC_ADF1CLKSOURCE_MSIK              RCC_CCIPR2_ADF1SEL_1
#define RCC_ADF1CLKSOURCE_SAI1K             (RCC_CCIPR2_ADF1SEL_1 | RCC_CCIPR2_ADF1SEL_0)
/**
  * @}
  */


/** @defgroup RCCEx_SPI3_Clock_Source SPI3 Clock Source
  * @{
  */
#define RCC_SPI3CLKSOURCE_PCLK1             0x00000000U
#define RCC_SPI3CLKSOURCE_MSIK              RCC_CCIPR2_SPI3SEL
/**
  * @}
  */

/** @defgroup RCCEx_SAI1_Clock_Source SAI1 Clock Source
  * @{
  */
#define RCC_SAI1CLKSOURCE_MSIK              0x00000000U
#define RCC_SAI1CLKSOURCE_PIN               RCC_CCIPR2_SAI1SEL_0
#define RCC_SAI1CLKSOURCE_HSE               RCC_CCIPR2_SAI1SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_RNG_Clock_Source  RCCEx RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_HSI48              0x00000000U
#define RCC_RNGCLKSOURCE_MSIK               RCC_CCIPR2_RNGSEL
/**
  * @}
  */

/** @defgroup RCCEx_ADCDACDIV_Clock_Divider ADC DAC DIV Clock Divider
  * @{
  */
#define RCC_ADCDACCLK_DIV1                  0x00000000U
#define RCC_ADCDACCLK_DIV2                  RCC_CCIPR2_ADCDACPRE_0
#define RCC_ADCDACCLK_DIV4                  RCC_CCIPR2_ADCDACPRE_3
#define RCC_ADCDACCLK_DIV8                  (RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_0)
#define RCC_ADCDACCLK_DIV16                 (RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_1)
#define RCC_ADCDACCLK_DIV32                 (RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_1 | RCC_CCIPR2_ADCDACPRE_0)
#define RCC_ADCDACCLK_DIV64                 (RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2)
#define RCC_ADCDACCLK_DIV128                (RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_0)
#define RCC_ADCDACCLK_DIV256                (RCC_CCIPR2_ADCDACPRE_3 | RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_1)
#define RCC_ADCDACCLK_DIV512                (RCC_CCIPR2_ADCDACPRE_3 | \
                                             RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_1 | RCC_CCIPR2_ADCDACPRE_0)
/**
  * @}
  */

/** @defgroup RCCEx_ADCDAC_Clock_Source ADCDAC Clock Source
  * @{
  */
#define RCC_ADCDACCLKSOURCE_HCLK            0x00000000U
#define RCC_ADCDACCLKSOURCE_HSE             RCC_CCIPR2_ADCDACSEL_0
#define RCC_ADCDACCLKSOURCE_MSIK            RCC_CCIPR2_ADCDACSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_DAC1_Sample_Hold_Clock_Source DAC1 Sample and Hold Clock Source
  * @{
  */
#define RCC_DAC1SHCLKSOURCE_LSI             0x00000000U
#define RCC_DAC1SHCLKSOURCE_LSE             RCC_CCIPR2_DAC1SHSEL
/**
  * @}
  */

/** @defgroup RCCEx_OCTOSPI1_Clock_Source OCTOSPI1 Clock Source
  * @{
  */
#define RCC_OCTOSPICLKSOURCE_SYSCLK         0x00000000U
#define RCC_OCTOSPICLKSOURCE_MSIK           RCC_CCIPR2_OCTOSPISEL
/**
  * @}
  */

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK3          0x00000000U
#define RCC_LPUART1CLKSOURCE_HSI            RCC_CCIPR3_LPUART1SEL_0
#define RCC_LPUART1CLKSOURCE_LSE            RCC_CCIPR3_LPUART1SEL_1
#define RCC_LPUART1CLKSOURCE_MSIK           (RCC_CCIPR3_LPUART1SEL_1 | RCC_CCIPR3_LPUART1SEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK3             0x00000000U
#define RCC_I2C3CLKSOURCE_MSIK              RCC_CCIPR3_I2C3SEL
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM34_Clock_Source LPTIM34 Clock Source
  * @{
  */
#define RCC_LPTIM34CLKSOURCE_MSIK           0x00000000U
#define RCC_LPTIM34CLKSOURCE_LSI            RCC_CCIPR3_LPTIM34SEL_0
#define RCC_LPTIM34CLKSOURCE_HSI            RCC_CCIPR3_LPTIM34SEL_1
#define RCC_LPTIM34CLKSOURCE_LSE            (RCC_CCIPR3_LPTIM34SEL_1 | RCC_CCIPR3_LPTIM34SEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_MSIK            0x00000000U
#define RCC_LPTIM1CLKSOURCE_LSI             RCC_CCIPR3_LPTIM1SEL_0
#define RCC_LPTIM1CLKSOURCE_HSI             RCC_CCIPR3_LPTIM1SEL_1
#define RCC_LPTIM1CLKSOURCE_LSE             (RCC_CCIPR3_LPTIM1SEL_1 | RCC_CCIPR3_LPTIM1SEL_0)
/**
  * @}
  */

#if defined(USART2)
/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1           0x00000000U
#define RCC_USART2CLKSOURCE_HSI           RCC_CCIPR2_USART2SEL
/**
  * @}
  */
#endif /* USART2 */

#if defined(I2C4)
/** @defgroup RCCEx_I2C4_Clock_Source I2C4 Clock Source
  * @{
  */
#define RCC_I2C4CLKSOURCE_PCLK1             0x00000000U
#define RCC_I2C4CLKSOURCE_MSIK              RCC_CCIPR2_I2C4SEL
/**
  * @}
  */
#endif /* I2C4 */

#if defined(SPI4)
/** @defgroup RCCEx_SPI4_Clock_Source SPI4 Clock Source
  * @{
  */
#define RCC_SPI4CLKSOURCE_PCLK1             0x00000000U
#define RCC_SPI4CLKSOURCE_MSIK              RCC_CCIPR2_SPI4SEL
/**
  * @}
  */
#endif /* SPI4 */


/** @defgroup RCC_EPOD_Booster_Source EPOD Booster Source
  * @{
  */
#define RCC_EPODBOOSTER_SOURCE_NONE     0x00000000U                                   /*!< EPOD booster source is disabled (power saving) */
#define RCC_EPODBOOSTER_SOURCE_MSIS     RCC_CFGR4_BOOSTSEL_0                          /*!< EPOD booster source is MSIS */
#define RCC_EPODBOOSTER_SOURCE_HSI      RCC_CFGR4_BOOSTSEL_1                          /*!< EPOD booster source is HSI */
#define RCC_EPODBOOSTER_SOURCE_HSE      (RCC_CFGR4_BOOSTSEL_1 | RCC_CFGR4_BOOSTSEL_0) /*!< EPOD booster source is HSE */

/**
  * @}
  */

/** @defgroup RCC_EPOD_Booster_Div EPOD Booster Divider
  * @{
  */
#define RCC_EPODBOOSTER_DIV1            0x00000000U                                                           /*!< EPOD Booster clock source divided by 1 */
#define RCC_EPODBOOSTER_DIV2            RCC_CFGR4_BOOSTDIV_0                                                  /*!< EPOD Booster clock source divided by 2 */
#define RCC_EPODBOOSTER_DIV4            RCC_CFGR4_BOOSTDIV_1                                                  /*!< EPOD Booster clock source divided by 4 */
#define RCC_EPODBOOSTER_DIV6            (RCC_CFGR4_BOOSTDIV_1 | RCC_CFGR4_BOOSTDIV_0)                         /*!< EPOD Booster clock source divided by 6 */
#define RCC_EPODBOOSTER_DIV8            RCC_CFGR4_BOOSTDIV_2                                                  /*!< EPOD Booster clock source divided by 8 */
#define RCC_EPODBOOSTER_DIV10           (RCC_CFGR4_BOOSTDIV_2 | RCC_CFGR4_BOOSTDIV_0)                         /*!< EPOD Booster clock source divided by 10 */
#define RCC_EPODBOOSTER_DIV12           (RCC_CFGR4_BOOSTDIV_2 | RCC_CFGR4_BOOSTDIV_1)                         /*!< EPOD Booster clock source divided by 12 */
#define RCC_EPODBOOSTER_DIV14           (RCC_CFGR4_BOOSTDIV_2 | RCC_CFGR4_BOOSTDIV_1 | RCC_CFGR4_BOOSTDIV_0)  /*!< EPOD Booster clock source divided by 14 */
#define RCC_EPODBOOSTER_DIV16           RCC_CFGR4_BOOSTDIV_3                                                  /*!< EPOD Booster clock source divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_MSIRCx_PLL_State MSIRCx PLL State
  * @{
  */
#define RCC_MSIRCx_PLL_OFF                  0x00000000U           /*!< MSIRCx PLL mode enable */
#define RCC_MSIRCx_PLL_ON                   RCC_CR_MSIPLL1EN      /*!< MSIRCx PLL mode disable */
/**
  * @}
  */

/** @defgroup RCC_MSIRCx_PLL_Input MSIRCx PLL Input
  * @{
  */
#define RCC_MSIRCx_PLL_INPUT_LSE            0x00000000U           /*!< LSE selected as MSIRCx PLL input */
#define RCC_MSIRCx_PLL_INPUT_HSE            RCC_ICSCR1_MSIPLL1SEL /*!< HSE selected as MSIRCx PLL input */
/**
  * @}
  */

/** @defgroup RCC_MSIRCx_PLL_HSE_Input_Frequency MSIRCx PLL HSE Input Frequency
  * @{
  */
#define RCC_MSIRCx_PLL_INPUT_HSE32                  32000000U      /*!< HSE frequency is 32 MHz */
#define RCC_MSIRCx_PLL_INPUT_HSE16                  16000000U      /*!< HSE frequency is 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_MSIRCx_PLL_Fast MSIRCx PLL Fast
  * @{
  */
#define RCC_MSIRCx_PLL_FAST_DISABLE         0x00000000U           /*!< PLL fast mode disable */
#define RCC_MSIRCx_PLL_FAST_ENABLE          RCC_CR_MSIPLL1FAST    /*!< PLL fast mode enable */
/**
  * @}
  */

/** @defgroup RCC_MSIRC1_PLLN MSIRC1 PLLN factor
  * @{
  */
#define RCC_MSIRC1_PLLN_732                 0x00000000U                                     /*!< MSIRC1 frequency is  23.9862 MHz */
#define RCC_MSIRC1_PLLN_689                 RCC_ICSCR1_MSIPLL1N_1                           /*!< MSIRC1 frequency is  22.5772 MHz */
#define RCC_MSIRC1_PLLN_780                 (RCC_ICSCR1_MSIPLL1N_1 | RCC_ICSCR1_MSIPLL1N_0) /*!< MSIRC1 frequency is  24.576 MHz */
/**
  * @}
  */

/** @defgroup RCC_MSIRCx_PLL_Unlock MSIRCx PLL Unlock
  * @{
  */
#define RCC_MSIRCx_PLL_UNLCK_LSE            RCC_CIER_MSIPLLUIE    /*!< PLL unlock interrupt for LSE source */
#define RCC_MSIRCx_PLL_UNLCK_HSE            RCC_CIER_MSIPLLHSUIE  /*!< PLL unlock interrupt for HSE source */
/**
  * @}
  */

/** @defgroup RCC_Stop_SystemWakeUpClock Wakeup from Stop System Clock
  * @{
  */
#define RCC_STOP_WKUP_SYSCLK_MSIS           0x00000000U
#define RCC_STOP_WKUP_SYSCLK_HSI            RCC_CFGR1_STOPWUCK
/**
  * @}
  */

/** @defgroup RCC_Kernel_Clock Kernel clock
  * @{
  */
#define RCC_KERNELCLK_MSIK                  RCC_CR_MSIKERON
#define RCC_KERNELCLK_HSI                   RCC_CR_HSIKERON
/**
  * @}
  */

/** @defgroup RCCEx_LSCO_Clock_Source Low Speed Clock Source
  * @{
  */
#define RCC_LSCOSOURCE_LSI                  0x00000000U           /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE                  RCC_BDCR_LSCOSEL      /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup RCCEx_CRS_Exported_Constants RCCEx CRS Exported Constants
  * @{
  */
/** @defgroup RCCEx_CRS_Status RCCEx CRS Status
  * @{
  */
#define RCC_CRS_NONE                        0x00000000U
#define RCC_CRS_TIMEOUT                     0x00000001U
#define RCC_CRS_SYNCOK                      0x00000002U
#define RCC_CRS_SYNCWARN                    0x00000004U
#define RCC_CRS_SYNCERR                     0x00000008U
#define RCC_CRS_SYNCMISS                    0x00000010U
#define RCC_CRS_TRIMOVF                     0x00000020U
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroSource RCCEx CRS SynchroSource
  * @{
  */
#define RCC_CRS_SYNC_SOURCE_GPIO            0x00000000U             /*!< Synchro Signal source GPIO */
#define RCC_CRS_SYNC_SOURCE_LSE             CRS_CFGR_SYNCSRC_0      /*!< Synchro Signal source LSE */
#define RCC_CRS_SYNC_SOURCE_USB             CRS_CFGR_SYNCSRC_1      /*!< Synchro Signal source USB SOF */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroDivider RCCEx CRS SynchroDivider
  * @{
  */
#define RCC_CRS_SYNC_DIV1                   0x00000000U                               /*!< Synchro Signal not divided (default) */
#define RCC_CRS_SYNC_DIV2                   CRS_CFGR_SYNCDIV_0                        /*!< Synchro Signal divided by 2 */
#define RCC_CRS_SYNC_DIV4                   CRS_CFGR_SYNCDIV_1                        /*!< Synchro Signal divided by 4 */
#define RCC_CRS_SYNC_DIV8                   (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 8 */
#define RCC_CRS_SYNC_DIV16                  CRS_CFGR_SYNCDIV_2                        /*!< Synchro Signal divided by 16 */
#define RCC_CRS_SYNC_DIV32                  (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 32 */
#define RCC_CRS_SYNC_DIV64                  (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1) /*!< Synchro Signal divided by 64 */
#define RCC_CRS_SYNC_DIV128                 CRS_CFGR_SYNCDIV                          /*!< Synchro Signal divided by 128 */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroPolarity RCCEx CRS SynchroPolarity
  * @{
  */
#define RCC_CRS_SYNC_POLARITY_RISING        0x00000000U         /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING       CRS_CFGR_SYNCPOL    /*!< Synchro Active on falling edge */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ReloadValueDefault RCCEx CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT         0x0000BB7FU   /*!< The reset value of the RELOAD field corresponds
                                                               to a target frequency of 48 MHz and a synchronization signal frequency of 1 kHz (SOF signal from USB). */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ErrorLimitDefault RCCEx CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT          0x00000022U   /*!< Default Frequency error limit */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault RCCEx CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT    0x00000040U /*!< The default value is 64, which corresponds to the middle of the trimming interval.
                                                             The trimming step is specified in the product datasheet. A higher TRIM value
                                                             corresponds to a higher output frequency */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_FreqErrorDirection RCCEx CRS FreqErrorDirection
  * @{
  */
#define RCC_CRS_FREQERRORDIR_UP             0x00000000U   /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN           CRS_ISR_FEDIR /*!< Downcounting direction, the actual frequency is below the target */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Interrupt_Sources RCCEx CRS Interrupt Sources
  * @{
  */
#define RCC_CRS_IT_SYNCOK                   CRS_CR_SYNCOKIE       /*!< SYNC event OK */
#define RCC_CRS_IT_SYNCWARN                 CRS_CR_SYNCWARNIE     /*!< SYNC warning */
#define RCC_CRS_IT_ERR                      CRS_CR_ERRIE          /*!< Error */
#define RCC_CRS_IT_ESYNC                    CRS_CR_ESYNCIE        /*!< Expected SYNC */
#define RCC_CRS_IT_SYNCERR                  CRS_CR_ERRIE          /*!< SYNC error */
#define RCC_CRS_IT_SYNCMISS                 CRS_CR_ERRIE          /*!< SYNC missed */
#define RCC_CRS_IT_TRIMOVF                  CRS_CR_ERRIE           /*!< Trimming overflow or underflow */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Flags RCCEx CRS Flags
  * @{
  */
#define RCC_CRS_FLAG_SYNCOK                 CRS_ISR_SYNCOKF       /*!< SYNC event OK flag     */
#define RCC_CRS_FLAG_SYNCWARN               CRS_ISR_SYNCWARNF     /*!< SYNC warning flag      */
#define RCC_CRS_FLAG_ERR                    CRS_ISR_ERRF          /*!< Error flag        */
#define RCC_CRS_FLAG_ESYNC                  CRS_ISR_ESYNCF        /*!< Expected SYNC flag     */
#define RCC_CRS_FLAG_SYNCERR                CRS_ISR_SYNCERR       /*!< SYNC error */
#define RCC_CRS_FLAG_SYNCMISS               CRS_ISR_SYNCMISS      /*!< SYNC missed*/
#define RCC_CRS_FLAG_TRIMOVF                CRS_ISR_TRIMOVF       /*!< Trimming overflow or underflow */
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
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK2 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI    HSI selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART1SEL, (__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK2 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI    HSI selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART1SEL)

/** @brief  Macro to configure the USART3 clock (USART3CLK).
  * @param  __USART3_CLKSOURCE__ specifies the USART3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1  PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI    HSI selected as USART3 clock
  * @retval None
  */
#define __HAL_RCC_USART3_CONFIG(__USART3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART3SEL, (__USART3_CLKSOURCE__))

/** @brief  Macro to get the USART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1  PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI    HSI selected as USART3 clock
  */
#define __HAL_RCC_GET_USART3_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART3SEL)

/** @brief  Macro to configure the UART4 clock (UART4CLK).
  * @param  __UART4_CLKSOURCE__ specifies the UART4 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_UART4CLKSOURCE_PCLK1   PCLK1 selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_HSI     HSI selected as UART4 clock
  * @retval None
  */
#define __HAL_RCC_UART4_CONFIG(__UART4_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_UART4SEL, (__UART4_CLKSOURCE__))

/** @brief  Macro to get the UART4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_UART4CLKSOURCE_PCLK1  PCLK1 selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_HSI    HSI selected as UART4 clock
  */
#define __HAL_RCC_GET_UART4_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_UART4SEL)

/** @brief  Macro to configure the UART5 clock (UART5CLK).
  * @param  __UART5_CLKSOURCE__ specifies the UART5 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_UART5CLKSOURCE_PCLK1  PCLK1 selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_HSI    HSI selected as UART5 clock
  * @retval None
  */
#define __HAL_RCC_UART5_CONFIG(__UART5_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_UART5SEL, (__UART5_CLKSOURCE__))

/** @brief  Macro to get the UART5 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_UART5CLKSOURCE_PCLK1  PCLK1 selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_HSI    HSI selected as UART5 clock
  */
#define __HAL_RCC_GET_UART5_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_UART5SEL)

/** @brief  Macro to configure the I3C1 clock (I3C1CLK).
  * @param  __I3C1_CLKSOURCE__ specifies the I3C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I3C1CLKSOURCE_PCLK1  PCLK1 selected as I3C1 clock
  *            @arg @ref RCC_I3C1CLKSOURCE_MSIK   MSIK selected as I3C1 clock
  * @retval None
  */
#define __HAL_RCC_I3C1_CONFIG(__I3C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I3C1SEL, (__I3C1_CLKSOURCE__))

/** @brief  Macro to get the I3C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I3C1CLKSOURCE_PCLK1  PCLK1 selected as I3C1 clock
  *            @arg @ref RCC_I3C1CLKSOURCE_MSIK  MSIK selected as I3C1 clock
  */
#define __HAL_RCC_GET_I3C1_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I3C1SEL)

/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  * @param  __I2C1_CLKSOURCE__ specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_MSIK   MSIK selected as I2C1 clock
  * @retval None
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I2C1SEL, (__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_MSIK   MSIK selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I2C1SEL)

/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  * @param  __I2C2_CLKSOURCE__ specifies the I2C2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1  PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_MSIK   MSIK selected as I2C2 clock
  * @retval None
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I2C2SEL, (__I2C2_CLKSOURCE__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1  PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_MSIK   MSIK selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I2C2SEL)

/** @brief  Macro to configure the I3C2 clock (I3C2CLK).
  * @param  __I3C2_CLKSOURCE__ specifies the I3C2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I3C2CLKSOURCE_PCLK2  PCLK2 selected as I3C2 clock
  *            @arg @ref RCC_I3C2CLKSOURCE_MSIK   MSIK selected as I3C2 clock
  * @retval None
  */
#define __HAL_RCC_I3C2_CONFIG(__I3C2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I3C2SEL, (__I3C2_CLKSOURCE__))

/** @brief  Macro to get the I3C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I3C2CLKSOURCE_PCLK2  PCLK2 selected as I3C2 clock
  *            @arg @ref RCC_I3C2CLKSOURCE_MSIK   MSIK selected as I3C2 clock
  */
#define __HAL_RCC_GET_I3C2_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I3C2SEL)

/** @brief  macro to configure the SPI2 clock source.
  * @param  __SPI2_CLKSOURCE__ specifies the SPI2 clock source.es:
  *            @arg RCC_SPI2CLKSOURCE_PCLK1   PCLK1 selected as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_MSIK    MSIK Clock selected as SPI2 clock
  */
#define __HAL_RCC_SPI2_CONFIG(__SPI2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SPI2SEL, (__SPI2_CLKSOURCE__))

/** @brief  macro to get the SPI2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI2CLKSOURCE_PCLK1   PCLK1 selected as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_MSIK    MSIK Clock selected as SPI2 clock
  */
#define __HAL_RCC_GET_SPI2_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SPI2SEL)

/** @brief  Macro to configure the LPTIM2 clock (LPTIM2CLK).
  * @param  __LPTIM2_CLKSOURCE__ specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI    LSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI    HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE    LSE selected as LPTIM2 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_LPTIM2SEL, (__LPTIM2_CLKSOURCE__))

/** @brief  Macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI    LSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI    HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE    LSE selected as LPTIM2 clock
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_LPTIM2SEL)

/** @brief  macro to configure the SPI1 clock source.
  * @param  __SPI1_CLKSOURCE__ specifies the SPI1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SPI1CLKSOURCE_PCLK2   PCLK2 Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_MSIK    MSIK Clock selected as SPI1 clock
  */
#define __HAL_RCC_SPI1_CONFIG(__SPI1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SPI1SEL, (__SPI1_CLKSOURCE__))

/** @brief  macro to get the SPI1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI1CLKSOURCE_PCLK2   PCLK2 Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_MSIK    MSIK Clock selected as SPI1 clock
  */
#define __HAL_RCC_GET_SPI1_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SPI1SEL)

/** @brief  macro to configure the SYSTICK clock source.
  * @param  __SYSTICK_CLKSOURCE__ specifies the SYSTICK clock source.
  *            @arg RCC_SYSTICKCLKSOURCE_HCLK_DIV8  HCLK divided by 8 Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSI        LSI Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSE        LSE Clock selected as SYSTICK clock
  */
#define __HAL_RCC_SYSTICK_CONFIG(__SYSTICK_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, (__SYSTICK_CLKSOURCE__))

/** @brief  macro to get the SYSTICK clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SYSTICKCLKSOURCE_HCLK_DIV8  HCLK divided by 8 Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSI        LSI Clock selected as SYSTICK clock
  *            @arg RCC_SYSTICKCLKSOURCE_LSE        LSE Clock selected as SYSTICK clock
  */
#define __HAL_RCC_GET_SYSTICK_SOURCE()      READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL)

/** @brief  macro to configure the FDCAN clock source.
  * @param  __FDCAN_CLKSOURCE__ specifies the FDCAN clock source.
  *            @arg RCC_FDCANCLKSOURCE_SYSCLK  SYSCLK divided by 8 Clock selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_MSIK    MSIK Clock selected as FDCAN clock
  */
#define __HAL_RCC_FDCAN_CONFIG(__FDCAN_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL, (__FDCAN_CLKSOURCE__))

/** @brief  macro to get the FDCAN clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_FDCANCLKSOURCE_SYSCLK  SYSCLK divided by 8 Clock selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_MSIK    MSIK Clock selected as FDCAN clock
  */
#define __HAL_RCC_GET_FDCAN_SOURCE()       READ_BIT(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL)

/** @brief  Macro to configure the ICLK clock.
  * @param  __ICLK_CLKSOURCE__ specifies the ICLK clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_ICLKCLKSOURCE_HSI48  HSI48 selected as ICLK clock
  *            @arg @ref RCC_ICLKCLKSOURCE_MSIK   MSIK selected as ICLK clock
  *            @arg @ref RCC_ICLKCLKSOURCE_HSE    HSE selected as ICLK clock
  *            @arg @ref RCC_ICLKCLKSOURCE_SYSCLK System Clock selected as ICLK clock
  * @retval None
  */
#define __HAL_RCC_ICLK_CONFIG(__ICLK_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ICLKSEL, (__ICLK_CLKSOURCE__))

/** @brief  Macro to get the ICLK clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ICLKCLKSOURCE_HSI48  HSI48 selected as ICLK clock
  *            @arg @ref RCC_ICLKCLKSOURCE_MSIK   MSIK selected as ICLK clock
  *            @arg @ref RCC_ICLKCLKSOURCE_HSE    HSE selected as ICLK clock
  *            @arg @ref RCC_ICLKCLKSOURCE_SYSCLK System Clock selected as ICLK clock
  */
#define __HAL_RCC_GET_ICLK_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ICLKSEL)

/** @brief  macro to configure the USB1 clock source.
  * @param  __USB1_CLKSOURCE__ specifies the USB1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USB1CLKSOURCE_ICLK        Intermediate Clock selected as USB1 clock
  *            @arg RCC_USB1CLKSOURCE_ICLK_DIV2   Intermediate Clock divide by 2 selected as USB1 clock
  */
#define __HAL_RCC_USB1_CONFIG(__USB1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USB1SEL, (__USB1_CLKSOURCE__))

/** @brief  macro to get the USB1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USB1CLKSOURCE_ICLK        Intermediate Clock selected as USB1 clock
  *            @arg RCC_USB1CLKSOURCE_ICLK_DIV2   Intermediate Clock divide by 2 selected as USB1 clock
  */
#define __HAL_RCC_GET_USB1_SOURCE()         READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USB1SEL)

/** @brief  macro to configure the TIMIC clock source.
  * @param  __TIMIC_CLKSOURCE__ specifies the TIMIC clock source.
  *            @arg RCC_TIMICCLKSOURCE_DISABLE                Input capture clock selection disable
  *            @arg RCC_TIMICCLKSOURCE_MSISDIV1024_MSISDIV4   HSI/256, MSIS/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  *            @arg RCC_TIMICCLKSOURCE_MSISDIV1024_MSIKDIV4   HSI/256, MSIS/1024 and MSIK/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  *            @arg RCC_TIMICCLKSOURCE_MSIKDIV1024_MSISDIV4   HSI/256, MSIK/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  *            @arg RCC_TIMICCLKSOURCE_MSIKDIV1024_MSIKDIV4   HSI/256, MSIK/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  */
#define __HAL_RCC_TIMIC_CONFIG(__TIMIC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL, (__TIMIC_CLKSOURCE__))

/** @brief  macro to get the TIMIC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_TIMICCLKSOURCE_DISABLE                Input capture clock selection disable
  *            @arg RCC_TIMICCLKSOURCE_MSISDIV1024_MSISDIV4   HSI/256, MSIS/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  *            @arg RCC_TIMICCLKSOURCE_MSISDIV1024_MSIKDIV4   HSI/256, MSIS/1024 and MSIK/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  *            @arg RCC_TIMICCLKSOURCE_MSIKDIV1024_MSISDIV4   HSI/256, MSIK/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  *            @arg RCC_TIMICCLKSOURCE_MSIKDIV1024_MSIKDIV4   HSI/256, MSIK/1024 and MSIS/4 selected by TIM16, TIM17 and LPTIM2 as internal input capture
  */
#define __HAL_RCC_GET_TIMIC_SOURCE()        READ_BIT(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL)

/** @brief  Macro to configure the ADF1 clock.
  * @param  __ADF1_CLKSOURCE__ specifies the ADF1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_ADF1CLKSOURCE_HCLK   HCLK selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PIN    Input PIN Audioclk selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_MSIK   MSIK selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_SAI1K  SAI1 kernel clock selected as ADF1 clock
  * @retval None
  */
#define __HAL_RCC_ADF1_CONFIG(__ADF1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADF1SEL, (__ADF1_CLKSOURCE__))

/** @brief  Macro to get the ADF1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADF1CLKSOURCE_HCLK   HCLK selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PIN    Input PIN Audioclk selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_MSIK   MSIK selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_SAI1K  SAI1 kernel clock selected as ADF1 clock
  */
#define __HAL_RCC_GET_ADF1_SOURCE()         READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ADF1SEL)

/** @brief  macro to configure the SPI3 clock source.
  * @param  __SPI3_CLKSOURCE__ specifies the SPI3 clock source.es:
  *            @arg RCC_SPI3CLKSOURCE_PCLK1   PCLK1 selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_MSIK    MSIK Clock selected as SPI3 clock
  */
#define __HAL_RCC_SPI3_CONFIG(__SPI3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SPI3SEL, (__SPI3_CLKSOURCE__))

/** @brief  macro to get the SPI3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI3CLKSOURCE_PCLK1   PCLK1 selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_MSIK    MSIK Clock selected as SPI3 clock
  */
#define __HAL_RCC_GET_SPI3_SOURCE()         READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SPI3SEL)

/**
  * @brief  Macro to configure the SAI1 clock source.
  * @param  __SAI1_CLKSOURCE__ defines the SAI1 clock source. This clock is derived
  *         from the HSI, SYSCLK or external clock (through a dedicated pin).
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_MSIK  MSIK Clock selected as SPI3 clock
  *             @arg @ref RCC_SAI1CLKSOURCE_PIN   Input PIN Audioclk Clock selected as SPI3 clock
  *             @arg @ref RCC_SAI1CLKSOURCE_HSE   HSE Clock selected as SPI3 clock
  * @retval None
  */
#define __HAL_RCC_SAI1_CONFIG(__SAI1_CLKSOURCE__)\
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SAI1SEL, (__SAI1_CLKSOURCE__))

/** @brief  Macro to get the SAI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_MSIK  MSIK Clock selected as SPI3 clock
  *             @arg @ref RCC_SAI1CLKSOURCE_PIN   Input PIN Audioclk Clock selected as SPI3 clock
  *             @arg @ref RCC_SAI1CLKSOURCE_HSE   HSE Clock selected as SPI3 clock
  */
#define __HAL_RCC_GET_SAI1_SOURCE()         READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SAI1SEL)

/** @brief macro to configure the RNG clock source.
  * @param  __RNG_CLKSOURCE__: specifies the RNG clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI48  HSI48  selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_MSIK   MSIK selected as RNG clock
  * @retval None
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_RNGSEL, (__RNG_CLKSOURCE__))

/** @brief  macro to get the RNG clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI48  HSI48 selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_MSIK   MSIK selected as RNG clock
  */
#define __HAL_RCC_GET_RNG_SOURCE()          READ_BIT(RCC->CCIPR2, RCC_CCIPR2_RNGSEL)

/** @brief  Macro to configure the ADC12 and DAC1 kernel clock divider.
  * @param  __ADCDAC_CLKDIV__ specifies the ADC12 and DAC1 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCDACCLK_DIV1     ADC12 and DAC1 kernel clock divided by 1
  *            @arg @ref RCC_ADCDACCLK_DIV2     ADC12 and DAC1 kernel clock divided by 2
  *            @arg @ref RCC_ADCDACCLK_DIV4     ADC12 and DAC1 kernel clock divided by 4
  *            @arg @ref RCC_ADCDACCLK_DIV8     ADC12 and DAC1 kernel clock divided by 8
  *            @arg @ref RCC_ADCDACCLK_DIV16    ADC12 and DAC1 kernel clock divided by 16
  *            @arg @ref RCC_ADCDACCLK_DIV32    ADC12 and DAC1 kernel clock divided by 32
  *            @arg @ref RCC_ADCDACCLK_DIV64    ADC12 and DAC1 kernel clock divided by 64
  *            @arg @ref RCC_ADCDACCLK_DIV128   ADC12 and DAC1 kernel clock divided by 128
  *            @arg @ref RCC_ADCDACCLK_DIV256   ADC12 and DAC1 kernel clock divided by 256
  *            @arg @ref RCC_ADCDACCLK_DIV512   ADC12 and DAC1 kernel clock divided by 512
  * @retval None
  */
#define __HAL_RCC_ADCDAC_DIV_CONFIG(__ADCDAC_CLKDIV__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADCDACPRE, (__ADCDAC_CLKDIV__))

/** @brief  Macro to get the ADC12 and DAC1 kernel clock divider.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCDACCLK_DIV1     ADC12 and DAC1 kernel clock divided by 1
  *            @arg @ref RCC_ADCDACCLK_DIV2     ADC12 and DAC1 kernel clock divided by 2
  *            @arg @ref RCC_ADCDACCLK_DIV4     ADC12 and DAC1 kernel clock divided by 4
  *            @arg @ref RCC_ADCDACCLK_DIV8     ADC12 and DAC1 kernel clock divided by 8
  *            @arg @ref RCC_ADCDACCLK_DIV16    ADC12 and DAC1 kernel clock divided by 16
  *            @arg @ref RCC_ADCDACCLK_DIV32    ADC12 and DAC1 kernel clock divided by 32
  *            @arg @ref RCC_ADCDACCLK_DIV64    ADC12 and DAC1 kernel clock divided by 64
  *            @arg @ref RCC_ADCDACCLK_DIV128   ADC12 and DAC1 kernel clock divided by 128
  *            @arg @ref RCC_ADCDACCLK_DIV256   ADC12 and DAC1 kernel clock divided by 256
  *            @arg @ref RCC_ADCDACCLK_DIV512   ADC12 and DAC1 kernel clock divided by 512
  */
#define __HAL_RCC_GET_ADCDAC_DIV()          READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ADCDACPRE)

/** @brief  Macro to configure the ADC12 and DAC1 clock source.
  * @param  __ADCDAC_CLKSOURCE__ specifies the ADC12 and DAC1 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCDACCLKSOURCE_HCLK HCLK clock selected as ADC12 and DAC1 clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_HSE  HSE clock selected as ADC12 and DAC1 clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_MSIK MSIK clock selected as ADC12 and DAC1 clock
  * @retval None
  */
#define __HAL_RCC_ADCDAC_CONFIG(__ADCDAC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADCDACSEL, (__ADCDAC_CLKSOURCE__))

/** @brief  Macro to get the ADC12 and DAC1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCDACCLKSOURCE_HCLK HCLK clock selected as ADC12 and DAC1 clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_HSE  HSE clock selected as ADC12 and DAC1 clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_MSIK MSIK clock selected as ADC12 and DAC1 clock
  */
#define __HAL_RCC_GET_ADCDAC_SOURCE()       READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ADCDACSEL)

/** @brief  Macro to configure the DAC1 sample and hold clock source.
  * @param  __DAC1SH_CLKSOURCE__ specifies the DAC1 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_DAC1SHCLKSOURCE_LSE HCLK clock selected as DAC1 sample and hold clock
  *            @arg @ref RCC_DAC1SHCLKSOURCE_LSI  HSE clock selected as DAC1 sample and hold clock
  * @retval None
  */
#define __HAL_RCC_DAC1SH_CONFIG(__DAC1SH_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_DAC1SHSEL, (__DAC1SH_CLKSOURCE__))

/** @brief  Macro to get the DAC1 sample and hold clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_DAC1SHCLKSOURCE_LSE HCLK clock selected as DAC1 sample and hold clock
  *            @arg @ref RCC_DAC1SHCLKSOURCE_LSI  HSE clock selected as DAC1 sample and hold clock
  */
#define __HAL_RCC_GET_DAC1SH_SOURCE()       READ_BIT(RCC->CCIPR2, RCC_CCIPR2_DAC1SHSEL)


/** @brief macro to configure the OCTOSPI clock source.
  * @param  __OCTOSPI_CLKSOURCE__: specifies the OCTOSPI clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_OCTOSPICLKSOURCE_SYSCLK   SYSCLK  selected as OCTOSPI clock
  *            @arg RCC_OCTOSPICLKSOURCE_MSIK     MSIK selected as OCTOSPI clock
  * @retval None
  */
#define __HAL_RCC_OCTOSPI_CONFIG(__OCTOSPI_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_OCTOSPISEL, (__OCTOSPI_CLKSOURCE__))

/** @brief  macro to get the OCTOSPI clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_OCTOSPICLKSOURCE_SYSCLK   SYSCLK  selected as OCTOSPI clock
  *            @arg RCC_OCTOSPICLKSOURCE_MSIK     MSIK selected as OCTOSPI clock
  */
#define __HAL_RCC_GET_OCTOSPI_SOURCE()      READ_BIT(RCC->CCIPR2, RCC_CCIPR2_OCTOSPISEL)

/** @brief  Macro to configure the LPUART1 clock.
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK3 PCLK3 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI   HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE   LSE selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_MSIK  MSIK selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL, (__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK3 PCLK3 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI   HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE   LSE selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_MSIK  MSIK selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE()      READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL)

/** @brief  Macro to configure the I2C3 clock.
  * @param  __I2C3_CLKSOURCE__ specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK3  PCLK3 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_MSIK   MSIK selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_I2C3SEL, (__I2C3_CLKSOURCE__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK3  PCLK3 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_MSIK   MSIK selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE()         READ_BIT(RCC->CCIPR3, RCC_CCIPR3_I2C3SEL)

/** @brief  Macro to configure the LPTIM34 clock.
  * @param  __LPTIM34_CLKSOURCE__ specifies the LPTIM34 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM34CLKSOURCE_MSIK   MSIK selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSI    LSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_HSI    HSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSE    LSE selected as LPTIM34 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM34_CONFIG(__LPTIM34_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPTIM34SEL, (__LPTIM34_CLKSOURCE__))

/** @brief  Macro to get the LPTIM34 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM34CLKSOURCE_MSIK   MSIK selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSI    LSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_HSI    HSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSE    LSE selected as LPTIM34 clock
  */
#define __HAL_RCC_GET_LPTIM34_SOURCE()      READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPTIM34SEL)

/** @brief  Macro to configure the LPTIM1 clock.
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_MSIK   MSIK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI    LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI    HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE    LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL, (__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_MSIK   MSIK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI    LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI    HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE    LSE selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE()       READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL)

#if defined(USART2)
/** @brief  Macro to configure the USART2 clock (USART2CLK).
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI16  HSI16 selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_USART2SEL, (__USART2_CLKSOURCE__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI16  HSI16 selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE()       READ_BIT(RCC->CCIPR2, RCC_CCIPR2_USART2SEL)
#endif /* USART2 */

#if defined(I2C4)
/** @brief  Macro to configure the I2C4 clock (I2C4CLK).
  * @param  __I2C4_CLKSOURCE__ specifies the I2C4 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C4CLKSOURCE_PCLK1  PCLK1 selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_MSIK   MSIK selected as I2C4 clock
  * @retval None
  */
#define __HAL_RCC_I2C4_CONFIG(__I2C4_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C4SEL, (__I2C4_CLKSOURCE__))

/** @brief  Macro to get the I2C4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C4CLKSOURCE_PCLK1  PCLK1 selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_MSIK   MSIK selected as I2C4 clock
  */
#define __HAL_RCC_GET_I2C4_SOURCE()         READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C4SEL)
#endif /* I2C4 */

#if defined(SPI4)
/** @brief  macro to configure the SPI4 clock source.
  * @param  __SPI4_CLKSOURCE__ specifies the SPI4 clock source.es:
  *            @arg RCC_SPI4CLKSOURCE_PCLK1   PCLK1 selected as SPI4 clock
  *            @arg RCC_SPI4CLKSOURCE_MSIK    MSIK Clock selected as SPI4 clock
  */
#define __HAL_RCC_SPI4_CONFIG(__SPI4_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SPI4SEL, (__SPI4_CLKSOURCE__))

/** @brief  macro to get the SPI4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI4CLKSOURCE_PCLK1   PCLK1 selected as SPI4 clock
  *            @arg RCC_SPI4CLKSOURCE_MSIK    MSIK Clock selected as SPI4 clock
  */
#define __HAL_RCC_GET_SPI4_SOURCE()         READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SPI4SEL)
#endif /* SPI4 */

/**
  * @}
  */

/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/**
  * @brief  Enable the specified CRS interrupts.
  * @param  __INTERRUPT__ specifies the CRS interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  * @retval None
  */
#define __HAL_RCC_CRS_ENABLE_IT(__INTERRUPT__)    SET_BIT(CRS->CR, (__INTERRUPT__))

/**
  * @brief  Disable the specified CRS interrupts.
  * @param  __INTERRUPT__ specifies the CRS interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  * @retval None
  */
#define __HAL_RCC_CRS_DISABLE_IT(__INTERRUPT__)   CLEAR_BIT(CRS->CR, (__INTERRUPT__))

/** @brief  Check whether the CRS interrupt has occurred or not.
  * @param  __INTERRUPT__ specifies the CRS interrupt source to check.
  *         This parameter can be one of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_RCC_CRS_GET_IT_SOURCE(__INTERRUPT__)  ((READ_BIT(CRS->CR, (__INTERRUPT__)) != 0U) ? SET : RESET)

/** @brief  Clear the CRS interrupt pending bits
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  *              @arg @ref RCC_CRS_IT_TRIMOVF  Trimming overflow or underflow interrupt
  *              @arg @ref RCC_CRS_IT_SYNCERR  SYNC error interrupt
  *              @arg @ref RCC_CRS_IT_SYNCMISS  SYNC missed interrupt
  */
/* CRS IT Error Mask */
#define  RCC_CRS_IT_ERROR_MASK              (RCC_CRS_IT_TRIMOVF | RCC_CRS_IT_SYNCERR | RCC_CRS_IT_SYNCMISS)

#define __HAL_RCC_CRS_CLEAR_IT(__INTERRUPT__)  do { \
                                                    if(((__INTERRUPT__) & RCC_CRS_IT_ERROR_MASK) != 0U) \
                                                    { \
                                                      WRITE_REG(CRS->ICR, CRS_ICR_ERRC | ((__INTERRUPT__) & ~RCC_CRS_IT_ERROR_MASK)); \
                                                    } \
                                                    else \
                                                    { \
                                                      WRITE_REG(CRS->ICR, (__INTERRUPT__)); \
                                                    } \
                                                  } while(0)

/**
  * @brief  Check whether the specified CRS flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_CRS_FLAG_SYNCOK  SYNC event OK
  *              @arg @ref RCC_CRS_FLAG_SYNCWARN  SYNC warning
  *              @arg @ref RCC_CRS_FLAG_ERR  Error
  *              @arg @ref RCC_CRS_FLAG_ESYNC  Expected SYNC
  *              @arg @ref RCC_CRS_FLAG_TRIMOVF  Trimming overflow or underflow
  *              @arg @ref RCC_CRS_FLAG_SYNCERR  SYNC error
  *              @arg @ref RCC_CRS_FLAG_SYNCMISS  SYNC missed
  * @retval The new state of _FLAG_ (TRUE or FALSE).
  */
#define __HAL_RCC_CRS_GET_FLAG(__FLAG__)    (READ_BIT(CRS->ISR, (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the CRS specified FLAG.
  * @param __FLAG__ specifies the flag to clear.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_CRS_FLAG_SYNCOK  SYNC event OK
  *              @arg @ref RCC_CRS_FLAG_SYNCWARN  SYNC warning
  *              @arg @ref RCC_CRS_FLAG_ERR  Error
  *              @arg @ref RCC_CRS_FLAG_ESYNC  Expected SYNC
  *              @arg @ref RCC_CRS_FLAG_TRIMOVF  Trimming overflow or underflow
  *              @arg @ref RCC_CRS_FLAG_SYNCERR  SYNC error
  *              @arg @ref RCC_CRS_FLAG_SYNCMISS  SYNC missed
  * @note RCC_CRS_FLAG_ERR clears RCC_CRS_FLAG_TRIMOVF, RCC_CRS_FLAG_SYNCERR, RCC_CRS_FLAG_SYNCMISS and consequently RCC_CRS_FLAG_ERR
  * @retval None
  */
/* CRS Flag Error Mask */
#define RCC_CRS_FLAG_ERROR_MASK                (RCC_CRS_FLAG_TRIMOVF | RCC_CRS_FLAG_SYNCERR | RCC_CRS_FLAG_SYNCMISS)

#define __HAL_RCC_CRS_CLEAR_FLAG(__FLAG__)     do { \
                                                    if(((__FLAG__) & RCC_CRS_FLAG_ERROR_MASK) != 0U) \
                                                    { \
                                                      WRITE_REG(CRS->ICR, CRS_ICR_ERRC | ((__FLAG__) & ~RCC_CRS_FLAG_ERROR_MASK)); \
                                                    } \
                                                    else \
                                                    { \
                                                      WRITE_REG(CRS->ICR, (__FLAG__)); \
                                                    } \
                                                  } while(0)

/**
  * @}
  */

/** @defgroup RCCEx_CRS_Extended_Features RCCEx CRS Extended Features
  * @{
  */
/**
  * @brief  Enable the oscillator clock for frequency error counter.
  * @note   when the CEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_FREQ_ERROR_COUNTER_ENABLE()   SET_BIT(CRS->CR, CRS_CR_CEN)

/**
  * @brief  Disable the oscillator clock for frequency error counter.
  * @retval None
  */
#define __HAL_RCC_CRS_FREQ_ERROR_COUNTER_DISABLE()  CLEAR_BIT(CRS->CR, CRS_CR_CEN)

/**
  * @brief  Enable the automatic hardware adjustment of TRIM bits.
  * @note   When the AUTOTRIMEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_ENABLE()      SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

/**
  * @brief  Enable or disable the automatic hardware adjustment of TRIM bits.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_DISABLE()     CLEAR_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

/**
  * @brief  Macro to calculate reload value to be set in CRS register according to target and sync frequencies
  * @note   The RELOAD value should be selected according to the ratio between the target frequency and the frequency
  *             of the synchronization source after prescaling. It is then decreased by one in order to
  *             reach the expected synchronization on the zero value. The formula is the following:
  *             RELOAD = (fTARGET / fSYNC) -1
  * @param  __FTARGET__ Target frequency (value in Hz)
  * @param  __FSYNC__ Synchronization signal frequency (value in Hz)
  * @retval None
  */
#define __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__) (((__FTARGET__) / (__FSYNC__)) - 1U)

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
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_EpodBoosterClkConfig(uint32_t Source, uint32_t Divider);
void              HAL_RCCEx_GetEpodBoosterClkConfig(uint32_t *Source, uint32_t *Divider);
HAL_StatusTypeDef HAL_RCCEx_MSIRCxPLLModeConfig(uint32_t MSISrce, const RCC_MSIRCxPLLTypeDef *RCxPLLMode);
void              HAL_RCCEx_GetMSIRCxPLLModeConfig(uint32_t MSISrce, RCC_MSIRCxPLLTypeDef *RCxPLLMode);
void              HAL_RCCEx_StopWakeupSysclkConfig(uint32_t WakeupClk);
void              HAL_RCCEx_StopWakeupKernelClkConfig(uint32_t WakeupClk);
void              HAL_RCCEx_EnableKernelClkInStop(uint32_t KernelClk);
void              HAL_RCCEx_DisableKernelClkInStop(uint32_t KernelClk);
void              HAL_RCCEx_StandbyWakeupMSISConfig(uint32_t MSISDiv);
void              HAL_RCCEx_StandbyWakeupMSIKConfig(uint32_t MSIKDiv);
void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group3
  * @{
  */
void              HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *pInit);
void              HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void);
void              HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo);
uint32_t          HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout);
void              HAL_RCCEx_CRS_IRQHandler(void);
void              HAL_RCCEx_CRS_SyncOkCallback(void);
void              HAL_RCCEx_CRS_SyncWarnCallback(void);
void              HAL_RCCEx_CRS_ExpectedSyncCallback(void);
void              HAL_RCCEx_CRS_ErrorCallback(uint32_t Error);
/**
  * @}
  */

/**
  * @}
  */


/** @addtogroup RCCEx_Private_Constants
  * @{
  */
/* Define used for IS_RCC_* macros below */
#if defined(STM32U385xx) || defined(STM32U375xx)
#define RCC_PERIPHCLOCK_ALL                 (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART3   | RCC_PERIPHCLK_UART4   | \
                                             RCC_PERIPHCLK_UART5  | RCC_PERIPHCLK_I3C1     | RCC_PERIPHCLK_I2C1    | \
                                             RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I3C2     | RCC_PERIPHCLK_SPI2    | \
                                             RCC_PERIPHCLK_LPTIM2 | RCC_PERIPHCLK_SPI1     | RCC_PERIPHCLK_SYSTICK | \
                                             RCC_PERIPHCLK_FDCAN  | RCC_PERIPHCLK_ICLK     | RCC_PERIPHCLK_USB1    | \
                                             RCC_PERIPHCLK_TIMIC  | RCC_PERIPHCLK_ADF1     | RCC_PERIPHCLK_SPI3    | \
                                             RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_RNG      | RCC_PERIPHCLK_ADCDAC  | \
                                             RCC_PERIPHCLK_DAC1SH | RCC_PERIPHCLK_OCTOSPI1 | RCC_PERIPHCLK_LPUART1 | \
                                             RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_LPTIM34  | RCC_PERIPHCLK_LPTIM1  | \
                                             RCC_PERIPHCLK_RTC)
#endif /* STM32U385xx || STM32U375xx */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */
#define IS_RCC_PERIPHCLOCK(__SELECTION__)         ((((__SELECTION__) & RCC_PERIPHCLOCK_ALL) != 0x00u) && \
                                                   (((__SELECTION__) & ~RCC_PERIPHCLOCK_ALL) == 0x00u))

#define IS_RCC_USART1CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                                   ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI))

#define IS_RCC_USART3CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_USART3CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_USART3CLKSOURCE_HSI))

#define IS_RCC_UART4CLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_UART4CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_UART4CLKSOURCE_HSI))

#define IS_RCC_UART5CLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_UART5CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_UART5CLKSOURCE_HSI))

#define IS_RCC_I3C1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I3C1CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_I3C1CLKSOURCE_MSIK))

#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_I2C1CLKSOURCE_MSIK))

#define IS_RCC_I2C2CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I2C2CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_I2C2CLKSOURCE_MSIK))

#define IS_RCC_I3C2CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I3C2CLKSOURCE_PCLK2)  || \
                                                   ((__SOURCE__) == RCC_I3C2CLKSOURCE_MSIK))

#define IS_RCC_SPI2CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SPI2CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_SPI2CLKSOURCE_MSIK))

#define IS_RCC_LPTIM2CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_LPTIM2CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSI)    || \
                                                   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_HSI)    || \
                                                   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSE))

#define IS_RCC_SPI1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SPI1CLKSOURCE_PCLK2)  || \
                                                   ((__SOURCE__) == RCC_SPI1CLKSOURCE_MSIK))

#define IS_RCC_SYSTICKCLKSOURCE(__SOURCE__)       (((__SOURCE__) == RCC_SYSTICKCLKSOURCE_HCLK_DIV8)  || \
                                                   ((__SOURCE__) == RCC_SYSTICKCLKSOURCE_LSI)        || \
                                                   ((__SOURCE__) == RCC_SYSTICKCLKSOURCE_LSE))

#define IS_RCC_FDCANCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_FDCANCLKSOURCE_SYSCLK)  || \
                                                   ((__SOURCE__) == RCC_FDCANCLKSOURCE_MSIK))

#define IS_RCC_ICLKCLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_ICLKCLKSOURCE_HSI48)  || \
                                                   ((__SOURCE__) == RCC_ICLKCLKSOURCE_MSIK)   || \
                                                   ((__SOURCE__) == RCC_ICLKCLKSOURCE_HSE)    || \
                                                   ((__SOURCE__) == RCC_ICLKCLKSOURCE_SYSCLK))

#define IS_RCC_USB1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_USB1CLKSOURCE_ICLK)   || \
                                                   ((__SOURCE__) == RCC_USB1CLKSOURCE_ICLK_DIV2))

#define IS_RCC_TIMICCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_TIMICCLKSOURCE_DISABLE)               || \
                                                   ((__SOURCE__) == RCC_TIMICCLKSOURCE_MSISDIV1024_MSISDIV4)  || \
                                                   ((__SOURCE__) == RCC_TIMICCLKSOURCE_MSISDIV1024_MSIKDIV4)  || \
                                                   ((__SOURCE__) == RCC_TIMICCLKSOURCE_MSIKDIV1024_MSISDIV4)  || \
                                                   ((__SOURCE__) == RCC_TIMICCLKSOURCE_MSIKDIV1024_MSIKDIV4))

#define IS_RCC_ADF1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_ADF1CLKSOURCE_HCLK)   || \
                                                   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PIN)    || \
                                                   ((__SOURCE__) == RCC_ADF1CLKSOURCE_MSIK)   || \
                                                   ((__SOURCE__) == RCC_ADF1CLKSOURCE_SAI1K))

#define IS_RCC_SPI3CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SPI3CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_SPI3CLKSOURCE_MSIK))

#define IS_RCC_SAI1CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SAI1CLKSOURCE_MSIK) || \
                                                   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PIN)  || \
                                                   ((__SOURCE__) == RCC_SAI1CLKSOURCE_HSE))

#define IS_RCC_RNGCLKSOURCE(__SOURCE__)           (((__SOURCE__) == RCC_RNGCLKSOURCE_HSI48) || \
                                                   ((__SOURCE__) == RCC_RNGCLKSOURCE_MSIK))

#define IS_RCC_ADCDAC_DIV(__DIVIDER__)            (((__DIVIDER__) == RCC_ADCDACCLK_DIV1)    || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV2)    || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV4)    || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV8)    || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV16)   || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV32)   || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV64)   || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV128)  || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV256)  || \
                                                   ((__DIVIDER__) == RCC_ADCDACCLK_DIV512))

#define IS_RCC_ADCDACCLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_ADCDACCLKSOURCE_HCLK) || \
                                                   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_HSE)  || \
                                                   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_MSIK))

#define IS_RCC_DAC1SHCLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_DAC1SHCLKSOURCE_LSI) || \
                                                   ((__SOURCE__) == RCC_DAC1SHCLKSOURCE_LSE))


#define IS_RCC_OCTOSPICLKSOURCE(__SOURCE__)       (((__SOURCE__) == RCC_OCTOSPICLKSOURCE_SYSCLK) || \
                                                   ((__SOURCE__) == RCC_OCTOSPICLKSOURCE_MSIK))

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)       (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK3) || \
                                                   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI)   || \
                                                   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE)   || \
                                                   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_MSIK))

#define IS_RCC_I2C3CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I2C3CLKSOURCE_PCLK3)   || \
                                                   ((__SOURCE__) == RCC_I2C3CLKSOURCE_MSIK))

#define IS_RCC_LPTIM34CLKSOURCE(__SOURCE__)       (((__SOURCE__) == RCC_LPTIM34CLKSOURCE_MSIK)  || \
                                                   ((__SOURCE__) == RCC_LPTIM34CLKSOURCE_LSI)   || \
                                                   ((__SOURCE__) == RCC_LPTIM34CLKSOURCE_HSI)   || \
                                                   ((__SOURCE__) == RCC_LPTIM34CLKSOURCE_LSE))

#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_MSIK)   || \
                                                   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)    || \
                                                   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI)    || \
                                                   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))

#if defined(USART2)
#define IS_RCC_USART2CLKSOURCE(__SOURCE__)        (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI))
#endif /* USART2 */

#if defined(I2C4)
#define IS_RCC_I2C4CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_I2C4CLKSOURCE_PCLK1)   || \
                                                   ((__SOURCE__) == RCC_I2C4CLKSOURCE_MSIK))
#endif /* I2C4 */

#if defined(SPI4)
#define IS_RCC_SPI4CLKSOURCE(__SOURCE__)          (((__SOURCE__) == RCC_SPI4CLKSOURCE_PCLK1)  || \
                                                   ((__SOURCE__) == RCC_SPI4CLKSOURCE_MSIK))
#endif /* SPI4 */

#define IS_RCC_EPODBOOSTER_SOURCE(__SRCE__)       (((__SRCE__) == RCC_EPODBOOSTER_SOURCE_NONE) || \
                                                   ((__SRCE__) == RCC_EPODBOOSTER_SOURCE_MSIS) || \
                                                   ((__SRCE__) == RCC_EPODBOOSTER_SOURCE_HSI) || \
                                                   ((__SRCE__) == RCC_EPODBOOSTER_SOURCE_HSE))

#define IS_RCC_EPODBOOSTER_DIV(__DIV__)           (((__DIV__) == RCC_EPODBOOSTER_DIV1) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV2) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV4) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV6) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV8) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV10) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV12) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV14) || \
                                                   ((__DIV__) == RCC_EPODBOOSTER_DIV16))

#define IS_RCC_MSI_PLL(__STATE__)                 (((__STATE__) == RCC_MSIRCx_PLL_ON)   ||  \
                                                   ((__STATE__) == RCC_MSIRCx_PLL_OFF))

#define IS_RCC_MSI_PLL_INPUT(__SOURCE__)          (((__SOURCE__) == RCC_MSIRCx_PLL_INPUT_LSE) || \
                                                   ((__SOURCE__) == RCC_MSIRCx_PLL_INPUT_HSE))

#define IS_RCC_MSI_PLL_INPUT_HSE_FREQ(__VALUE__)  (((__VALUE__) == RCC_MSIRCx_PLL_INPUT_HSE16) || \
                                                   ((__VALUE__) == RCC_MSIRCx_PLL_INPUT_HSE32))

#define IS_RCC_MSI_PLL_FASTMODE(__MODE__)         (((__MODE__) == RCC_MSIRCx_PLL_FAST_DISABLE)  || \
                                                   ((__MODE__) == RCC_MSIRCx_PLL_FAST_ENABLE))

#define IS_RCC_MSI_PLL_NVALUE(__VALUE__)          (((__VALUE__) == RCC_MSIRC1_PLLN_732)   || \
                                                   ((__VALUE__) == RCC_MSIRC1_PLLN_689)  || \
                                                   ((__VALUE__) == RCC_MSIRC1_PLLN_780))

#define IS_RCC_STOP_WKUP_SYSCLK(__SOURCE__)       (((__SOURCE__) == RCC_STOP_WKUP_SYSCLK_MSIS) || \
                                                   ((__SOURCE__) == RCC_STOP_WKUP_SYSCLK_HSI))

#define IS_RCC_KERNEL_CLK(__SOURCE__)             (((__SOURCE__) == RCC_KERNELCLK_MSIK) || \
                                                   ((__SOURCE__) == RCC_KERNELCLK_HSI))

#define IS_RCC_MULTI_KERNEL_CLK(__SOURCE__)       ((((__SOURCE__) & (RCC_KERNELCLK_MSIK | RCC_KERNELCLK_HSI)) != 0x00UL) && \
                                                   (((__SOURCE__) & ~(RCC_KERNELCLK_MSIK | RCC_KERNELCLK_HSI)) == 0x00UL))

#define IS_RCC_MSI_STANDBY_DIV(__DIV__)           (((__DIV__) == RCC_MSI_DIV2) || ((__DIV__) == RCC_MSI_DIV4) || \
                                                   ((__DIV__) == RCC_MSI_DIV8))

#define IS_RCC_LSCOSOURCE(__SOURCE__)             (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                                   ((__SOURCE__) == RCC_LSCOSOURCE_LSE))
/**
  * @}
  */

/** @addtogroup RCCEx_CRS_Private_Macros
  * @{
  */
#define IS_RCC_CRS_SYNC_SOURCE(__SOURCE__)        (((__SOURCE__) == RCC_CRS_SYNC_SOURCE_GPIO) || \
                                                   ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_LSE) || \
                                                   ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_USB))

#define IS_RCC_CRS_SYNC_DIV(__DIV__)              (((__DIV__) == RCC_CRS_SYNC_DIV1)  || ((__DIV__) == RCC_CRS_SYNC_DIV2)  || \
                                                   ((__DIV__) == RCC_CRS_SYNC_DIV4)  || ((__DIV__) == RCC_CRS_SYNC_DIV8)  || \
                                                   ((__DIV__) == RCC_CRS_SYNC_DIV16) || ((__DIV__) == RCC_CRS_SYNC_DIV32) || \
                                                   ((__DIV__) == RCC_CRS_SYNC_DIV64) || ((__DIV__) == RCC_CRS_SYNC_DIV128))

#define IS_RCC_CRS_SYNC_POLARITY(__POLARITY__)    (((__POLARITY__) == RCC_CRS_SYNC_POLARITY_RISING) || \
                                                   ((__POLARITY__) == RCC_CRS_SYNC_POLARITY_FALLING))

#define IS_RCC_CRS_RELOADVALUE(__VALUE__)         (((__VALUE__) <= 0xFFFFU))

#define IS_RCC_CRS_ERRORLIMIT(__VALUE__)          (((__VALUE__) <= 0xFFU))

#define IS_RCC_CRS_HSI48CALIBRATION(__VALUE__)    (((__VALUE__) <= 0x7FU))

#define IS_RCC_CRS_FREQERRORDIR(__DIR__)          (((__DIR__) == RCC_CRS_FREQERRORDIR_UP) || \
                                                   ((__DIR__) == RCC_CRS_FREQERRORDIR_DOWN))
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

#endif /* __STM32U3xx_HAL_RCC_EX_H */
