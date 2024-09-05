/**
  ******************************************************************************
  * @file    stm32u0xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32U0xx_HAL_RCC_EX_H
#define __STM32U0xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal_def.h"

/** @addtogroup STM32U0xx_HAL_Driver
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
  * @brief  RCC PLL Clocks structure definition
  */
typedef struct
{
  uint32_t PLL_P_Frequency;
  uint32_t PLL_Q_Frequency;
  uint32_t PLL_R_Frequency;
} PLL_ClocksTypeDef;

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;                /*!< The Extended Clock to be configured.
                                                This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t Usart1ClockSelection;                /*!< Specifies USART1 clock source.
                                                This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection;                /*!< Specifies USART2 clock source.
                                                This parameter can be a value of @ref RCCEx_USART2_Clock_Source */
#if defined (LPUART3)
  uint32_t Lpuart3ClockSelection;               /*!< Specifies LPUART1 clock source.
                                                This parameter can be a value of @ref RCCEx_LPUART3_Clock_Source */
#endif /* LPUART3 */
  uint32_t Lpuart2ClockSelection;               /*!< Specifies LPUART2 clock source.
                                                This parameter can be a value of @ref RCCEx_LPUART2_Clock_Source */

  uint32_t Lpuart1ClockSelection;               /*!< Specifies LPUART3 clock source.
                                                This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */

  uint32_t I2c1ClockSelection;                  /*!< Specifies I2C1 clock source.
                                                This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

  uint32_t I2c3ClockSelection;                  /*!< Specifies I2C3 clock source.
                                                This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Lptim1ClockSelection;                /*!< Specifies LPTIM1 clock source.
                                                This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */

  uint32_t Lptim2ClockSelection;                /*!< Specifies LPTIM2 clock source.
                                                This parameter can be a value of @ref RCCEx_LPTIM2_Clock_Source */
#if defined (LPTIM3)
  uint32_t Lptim3ClockSelection;                /*!< Specifies LPTIM3 clock source.
                                                This parameter can be a value of @ref RCCEx_LPTIM3_Clock_Source */
#endif /* LPTIM3 */
  uint32_t Tim1ClockSelection;                  /*!< Specifies TIM1 clock source.
                                                This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim15ClockSelection;                 /*!< Specifies TIM15 clock source.
                                                This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */
#if defined(USB_DRD_FS)
  uint32_t UsbClockSelection;                   /*!< Specifies USB clock source.
                                                This parameter can be a value of @ref RCCEx_USB_Clock_Source */
#endif /* USB_DRD_FS */
  uint32_t RngClockSelection;                   /*!< Specifies RNG clock source.
                                                This parameter can be a value of @ref RCCEx_RNG_Clock_Source */

  uint32_t AdcClockSelection;                   /*!< Specifies ADC clock source.
                                                This parameter can be a value of @ref RCCEx_ADC_Clock_Source */

  uint32_t RTCClockSelection;                   /*!< Specifies RTC clock source.
                                                This parameter can be a value of @ref RCC_RTC_Clock_Source */
} RCC_PeriphCLKInitTypeDef;

#if defined (CRS)
/**
  * @brief RCC_CRS Init structure definition
  */
typedef struct
{
  uint32_t Prescaler;               /*!< Specifies the division factor of the SYNC signal.
                                      This parameter can be a value of @ref RCCEx_CRS_SynchroDivider */

  uint32_t Source;                  /*!< Specifies the SYNC signal source.
                                      This parameter can be a value of @ref RCCEx_CRS_SynchroSource */

  uint32_t Polarity;                /*!< Specifies the input polarity for the SYNC signal source.
                                      This parameter can be a value of @ref RCCEx_CRS_SynchroPolarity */

  uint32_t ReloadValue;             /*!< Specifies the value to be loaded in the frequency error counter with each SYNC
                                      event. It can be calculated in using macro
                                      @ref __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)
                                      This parameter must be a number between 0 and 0xFFFF or a value of
                                      @ref RCCEx_CRS_ReloadValueDefault .*/

  uint32_t ErrorLimitValue;         /*!< Specifies the value to be used to evaluate the captured frequency error value.
                                       This parameter must be a number between 0 and 0xFF or a value of
                                       @ref RCCEx_CRS_ErrorLimitDefault */

  uint32_t HSI48CalibrationValue;   /*!< Specifies a user-programmable trimming value to the HSI48 oscillator.
                                      This parameter must be a number between 0 and 0x3F or a value of
                                      @ref RCCEx_CRS_HSI48CalibrationDefault */

} RCC_CRSInitTypeDef;

/**
  * @brief RCC_CRS Synchronization structure definition
  */
typedef struct
{
  uint32_t ReloadValue;                   /*!< Specifies the value loaded in the Counter reload value.
                                            This parameter must be a number between 0 and 0xFFFF */

  uint32_t HSI48CalibrationValue;         /*!< Specifies value loaded in RC48 oscillator smooth trimming.
                                            This parameter must be a number between 0 and 0x3F */

  uint32_t FreqErrorCapture;              /*!< Specifies the value loaded in the .FECAP, the frequency error counter
                                            value latched in the time of the last SYNC event.
                                            This parameter must be a number between 0 and 0xFFFF */

  uint32_t FreqErrorDirection;            /*!< Specifies the value loaded in the .FEDIR, the counting direction of the
                                            frequency error counter latched in the time of the last SYNC event.
                                            It shows whether the actual frequency is below or above the target.
                                            This parameter must be a value of @ref RCCEx_CRS_FreqErrorDirection */

} RCC_CRSSynchroInfoTypeDef;

#endif /* CRS */
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
#define RCC_LSCOSOURCE_LSI             (uint32_t)0x00000000U /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE             RCC_BDCR_LSCOSEL      /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001U)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002U)
#if defined (LPUART3)
#define RCC_PERIPHCLK_LPUART3          ((uint32_t)0x00000004U)
#endif /* LPUART3 */
#define RCC_PERIPHCLK_LPUART2          ((uint32_t)0x00000008U)
#define RCC_PERIPHCLK_LPUART1          ((uint32_t)0x00000010U)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020U)
#define RCC_PERIPHCLK_I2C3             ((uint32_t)0x00000040U)
#define RCC_PERIPHCLK_LPTIM1           ((uint32_t)0x00000080U)
#define RCC_PERIPHCLK_LPTIM2           ((uint32_t)0x00000100U)
#if defined (LPTIM3)
#define RCC_PERIPHCLK_LPTIM3           ((uint32_t)0x00000200U)
#endif /* LPTIM3 */
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00000400U)
#define RCC_PERIPHCLK_TIM15            ((uint32_t)0x00000800U)
#if defined(USB_DRD_FS)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00001000U)
#endif /* USB_DRD_FS */
#define RCC_PERIPHCLK_RNG              ((uint32_t)0x00002000U)
#define RCC_PERIPHCLK_ADC              ((uint32_t)0x00004000U)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00008000U)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00010000U)
#define RCC_PERIPHCLK_USART4           ((uint32_t)0x00020000U)

/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK1      ((uint32_t)0x00000000U)
#define RCC_USART1CLKSOURCE_SYSCLK     RCC_CCIPR_USART1SEL_0
#define RCC_USART1CLKSOURCE_HSI        RCC_CCIPR_USART1SEL_1
#define RCC_USART1CLKSOURCE_LSE        (RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1      ((uint32_t)0x00000000U)
#define RCC_USART2CLKSOURCE_SYSCLK     RCC_CCIPR_USART2SEL_0
#define RCC_USART2CLKSOURCE_HSI        RCC_CCIPR_USART2SEL_1
#define RCC_USART2CLKSOURCE_LSE        (RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK1     ((uint32_t)0x00000000U)
#define RCC_LPUART1CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART1SEL_0
#define RCC_LPUART1CLKSOURCE_HSI       RCC_CCIPR_LPUART1SEL_1
#define RCC_LPUART1CLKSOURCE_LSE       (RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPUART2_Clock_Source LPUART2 Clock Source
  * @{
  */
#define RCC_LPUART2CLKSOURCE_PCLK1     ((uint32_t)0x00000000U)
#define RCC_LPUART2CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART2SEL_0
#define RCC_LPUART2CLKSOURCE_HSI       RCC_CCIPR_LPUART2SEL_1
#define RCC_LPUART2CLKSOURCE_LSE       (RCC_CCIPR_LPUART2SEL_0 | RCC_CCIPR_LPUART2SEL_1)
/**
  * @}
  */

#if defined (LPUART3)
/** @defgroup RCCEx_LPUART3_Clock_Source LPUART3 Clock Source
  * @{
  */
#define RCC_LPUART3CLKSOURCE_PCLK1    ((uint32_t)0x00000000U)
#define RCC_LPUART3CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART3SEL_0
#define RCC_LPUART3CLKSOURCE_HSI       RCC_CCIPR_LPUART3SEL_1
#define RCC_LPUART3CLKSOURCE_LSE      (RCC_CCIPR_LPUART3SEL_0 | RCC_CCIPR_LPUART3SEL_1)
/**
  * @}
  */
#endif /* LPUART3 */

/** @defgroup RCCEx_I2C1_Clock_Source I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1        ((uint32_t)0x00000000U)
#define RCC_I2C1CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0
#define RCC_I2C1CLKSOURCE_HSI          RCC_CCIPR_I2C1SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK1        ((uint32_t)0x00000000U)
#define RCC_I2C3CLKSOURCE_SYSCLK       RCC_CCIPR_I2C3SEL_0
#define RCC_I2C3CLKSOURCE_HSI          RCC_CCIPR_I2C3SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK1      ((uint32_t)0x00000000U)
#define RCC_LPTIM1CLKSOURCE_LSI        RCC_CCIPR_LPTIM1SEL_0
#define RCC_LPTIM1CLKSOURCE_HSI        RCC_CCIPR_LPTIM1SEL_1
#define RCC_LPTIM1CLKSOURCE_LSE        (RCC_CCIPR_LPTIM1SEL_0 | RCC_CCIPR_LPTIM1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM2_Clock_Source LPTIM2 Clock Source
  * @{
  */
#define RCC_LPTIM2CLKSOURCE_PCLK1       ((uint32_t)0x00000000U)
#define RCC_LPTIM2CLKSOURCE_LSI         RCC_CCIPR_LPTIM2SEL_0
#define RCC_LPTIM2CLKSOURCE_HSI         RCC_CCIPR_LPTIM2SEL_1
#define RCC_LPTIM2CLKSOURCE_LSE         (RCC_CCIPR_LPTIM2SEL_0 | RCC_CCIPR_LPTIM2SEL_1)
/**
  * @}
  */

#if defined (LPTIM3)
/** @defgroup RCCEx_LPTIM3_Clock_Source LPTIM3 Clock Source
  * @{
  */
#define RCC_LPTIM3CLKSOURCE_PCLK1      ((uint32_t)0x00000000U)
#define RCC_LPTIM3CLKSOURCE_LSI         RCC_CCIPR_LPTIM3SEL_0
#define RCC_LPTIM3CLKSOURCE_HSI         RCC_CCIPR_LPTIM3SEL_1
#define RCC_LPTIM3CLKSOURCE_LSE        (RCC_CCIPR_LPTIM3SEL_0 | RCC_CCIPR_LPTIM3SEL_1)
/**
  * @}
  */
#endif /* LPTIM3 */

/** @defgroup RCCEx_TIM1_Clock_Source TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLKSOURCE_PCLK1        ((uint32_t)0x00000000U)
#define RCC_TIM1CLKSOURCE_PLLQ          RCC_CCIPR_TIM1SEL
/**
  * @}
  */

/** @defgroup RCCEx_TIM15_Clock_Source TIM15 Clock Source
  * @{
  */
#define RCC_TIM15CLKSOURCE_PCLK1        ((uint32_t)0x00000000U)
#define RCC_TIM15CLKSOURCE_PLLQ          RCC_CCIPR_TIM15SEL
/**
  * @}
  */
#if defined(USB_DRD_FS)
/** @defgroup RCCEx_USB_Clock_Source USB Clock Source
  * @{
  */
#define RCC_USBCLKSOURCE_NONE         ((uint32_t)0x00000000U)
#define RCC_USBCLKSOURCE_MSI            RCC_CCIPR_CLK48SEL_0
#define RCC_USBCLKSOURCE_PLLQ           RCC_CCIPR_CLK48SEL_1
#define RCC_USBCLKSOURCE_HSI48          RCC_CCIPR_CLK48SEL
/**
  * @}
  */
#endif /* USB_DRD_FS */

/** @defgroup RCCEx_RNG_Clock_Source RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_NONE         ((uint32_t)0x00000000U)
#define RCC_RNGCLKSOURCE_MSI            RCC_CCIPR_CLK48SEL_0
#define RCC_RNGCLKSOURCE_PLLQ           RCC_CCIPR_CLK48SEL_1
#define RCC_RNGCLKSOURCE_HSI48          RCC_CCIPR_CLK48SEL
/**
  * @}
  */
/** @defgroup RCCEx_ADC_Clock_Source ADC1 Clock Source
  * @{
  */
#define RCC_ADCCLKSOURCE_SYSCLK         ((uint32_t)0x00000000U)
#define RCC_ADCCLKSOURCE_PLLP           RCC_CCIPR_ADCSEL_0
#define RCC_ADCCLKSOURCE_HSI            RCC_CCIPR_ADCSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_EXTI_LINE_LSECSS  RCC LSE CSS external interrupt line
  * @{
  */
#define RCC_EXTI_LINE_LSECSS           EXTI_IMR1_IM27    /*!< External interrupt line 27 connected to the LSE CSS EXTI Line */
/**
  * @}
  */

#if defined(CRS)

/** @defgroup RCCEx_CRS_Status RCCEx CRS Status
  * @{
  */
#define RCC_CRS_NONE                   0x00000000U
#define RCC_CRS_TIMEOUT                0x00000001U
#define RCC_CRS_SYNCOK                 0x00000002U
#define RCC_CRS_SYNCWARN               0x00000004U
#define RCC_CRS_SYNCERR                0x00000008U
#define RCC_CRS_SYNCMISS               0x00000010U
#define RCC_CRS_TRIMOVF                0x00000020U
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroSource RCCEx CRS SynchroSource
  * @{
  */
#define RCC_CRS_SYNC_SOURCE_GPIO       0U                   /*!< Synchro Signal source GPIO */
#define RCC_CRS_SYNC_SOURCE_LSE        CRS_CFGR_SYNCSRC_0   /*!< Synchro Signal source LSE */
#define RCC_CRS_SYNC_SOURCE_USB        CRS_CFGR_SYNCSRC_1   /*!< Synchro Signal source USB SOF (default)*/
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroDivider RCCEx CRS SynchroDivider
  * @{
  */
#define RCC_CRS_SYNC_DIV1              0U                                  /*!< Synchro Signal not divided (default) */
#define RCC_CRS_SYNC_DIV2              CRS_CFGR_SYNCDIV_0                         /*!< Synchro Signal divided by 2 */
#define RCC_CRS_SYNC_DIV4              CRS_CFGR_SYNCDIV_1                         /*!< Synchro Signal divided by 4 */
#define RCC_CRS_SYNC_DIV8              (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0)  /*!< Synchro Signal divided by 8 */
#define RCC_CRS_SYNC_DIV16             CRS_CFGR_SYNCDIV_2                         /*!< Synchro Signal divided by 16 */
#define RCC_CRS_SYNC_DIV32             (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0)  /*!< Synchro Signal divided by 32 */
#define RCC_CRS_SYNC_DIV64             (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1)  /*!< Synchro Signal divided by 64 */
#define RCC_CRS_SYNC_DIV128            CRS_CFGR_SYNCDIV                           /*!< Synchro Signal divided by 128 */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroPolarity RCCEx CRS SynchroPolarity
  * @{
  */
#define RCC_CRS_SYNC_POLARITY_RISING   0U                  /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING  CRS_CFGR_SYNCPOL    /*!< Synchro Active on falling edge */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ReloadValueDefault RCCEx CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT    0x0000BB7FU         /*!< The reset value of the RELOAD field corresponds
                                                             to a target frequency of 48 MHz and a synchronization
                                                             signal frequency of 1 kHz (SOF signal from USB). */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ErrorLimitDefault RCCEx CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT     0x00000022U         /*!< Default Frequency error limit */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault RCCEx CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT 0x00000040U       /*!< The default value is 64, which corresponds to the middle
                                                             of the trimming interval. The trimming step is specified in
                                                             the product datasheet. A higher TRIM value corresponds
                                                             to a higher output frequency */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_FreqErrorDirection RCCEx CRS FreqErrorDirection
  * @{
  */
#define RCC_CRS_FREQERRORDIR_UP        0U             /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN      CRS_ISR_FEDIR  /*!< Downcounting direction, the actual frequency is below the target */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Interrupt_Sources RCCEx CRS Interrupt Sources
  * @{
  */
#define RCC_CRS_IT_SYNCOK              CRS_CR_SYNCOKIE     /*!< SYNC event OK */
#define RCC_CRS_IT_SYNCWARN            CRS_CR_SYNCWARNIE   /*!< SYNC warning */
#define RCC_CRS_IT_ERR                 CRS_CR_ERRIE        /*!< Error */
#define RCC_CRS_IT_ESYNC               CRS_CR_ESYNCIE      /*!< Expected SYNC */
#define RCC_CRS_IT_SYNCERR             CRS_CR_ERRIE        /*!< SYNC error */
#define RCC_CRS_IT_SYNCMISS            CRS_CR_ERRIE        /*!< SYNC missed */
#define RCC_CRS_IT_TRIMOVF             CRS_CR_ERRIE        /*!< Trimming overflow or underflow */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Flags RCCEx CRS Flags
  * @{
  */
#define RCC_CRS_FLAG_SYNCOK            CRS_ISR_SYNCOKF     /*!< SYNC event OK flag     */
#define RCC_CRS_FLAG_SYNCWARN          CRS_ISR_SYNCWARNF   /*!< SYNC warning flag      */
#define RCC_CRS_FLAG_ERR               CRS_ISR_ERRF        /*!< Error flag        */
#define RCC_CRS_FLAG_ESYNC             CRS_ISR_ESYNCF      /*!< Expected SYNC flag     */
#define RCC_CRS_FLAG_SYNCERR           CRS_ISR_SYNCERR     /*!< SYNC error */
#define RCC_CRS_FLAG_SYNCMISS          CRS_ISR_SYNCMISS    /*!< SYNC missed*/
#define RCC_CRS_FLAG_TRIMOVF           CRS_ISR_TRIMOVF     /*!< Trimming overflow or underflow */
/**
  * @}
  */

#endif /* CRS */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/** @brief  Macro to configure the USART1 clock (USART1CLK).
  *
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK1  PCLK selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  SE selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART1SEL, (uint32_t)(__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK1  PCLK selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL)))

/** @brief  Macro to configure the USART2 clock (USART2CLK).
  *
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART2SEL, (uint32_t)(__USART2_CLKSOURCE__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_USART2SEL)))

/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  *
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1  PCLK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART1SEL, (uint32_t)(__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1  PCLK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART1SEL)))

/** @brief  Macro to configure the LPUART2 clock (LPUART2CLK).
  *
  * @param  __LPUART2_CLKSOURCE__ specifies the LPUART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART2CLKSOURCE_PCLK1  PCLK selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_HSI  HSI selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_SYSCLK  System Clock selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_LSE  LSE selected as LPUART2 clock
  * @retval None
  */
#define __HAL_RCC_LPUART2_CONFIG(__LPUART2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART2SEL, (uint32_t)(__LPUART2_CLKSOURCE__))

/** @brief  Macro to get the LPUART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART2CLKSOURCE_PCLK1  PCLK selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_HSI  HSI selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_SYSCLK  System Clock selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_LSE  LSE selected as LPUART2 clock
  */
#define __HAL_RCC_GET_LPUART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART2SEL)))

#if defined (LPUART3)
/** @brief  Macro to configure the LPUART3 clock (LPUART3CLK).
  *
  * @param  __LPUART3_CLKSOURCE__ specifies the LPUART3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART3CLKSOURCE_PCLK1  PCLK selected as LPUART3 clock
  *            @arg @ref RCC_LPUART3CLKSOURCE_HSI  HSI selected as LPUART3 clock
  *            @arg @ref RCC_LPUART3CLKSOURCE_SYSCLK  System Clock selected as LPUART3 clock
  *            @arg @ref RCC_LPUART3CLKSOURCE_LSE  LSE selected as LPUART3 clock
  * @retval None
  */
#define __HAL_RCC_LPUART3_CONFIG(__LPUART3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART3SEL, (uint32_t)(__LPUART3_CLKSOURCE__))

/** @brief  Macro to get the LPUART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART3CLKSOURCE_PCLK1  PCLK selected as LPUART3 clock
  *            @arg @ref RCC_LPUART3CLKSOURCE_HSI  HSI selected as LPUART3 clock
  *            @arg @ref RCC_LPUART3CLKSOURCE_SYSCLK  System Clock selected as LPUART3 clock
  *            @arg @ref RCC_LPUART3CLKSOURCE_LSE  LSE selected as LPUART3 clock
  */
#define __HAL_RCC_GET_LPUART3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART3SEL)))
#endif /* LPUART3 */

/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  *
  * @param  __I2C1_CLKSOURCE__ specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  * @retval None
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C1SEL, (uint32_t)(__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C1SEL)))

/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  *
  * @param  __I2C3_CLKSOURCE__ specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK1  PCLK selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI  HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK  System Clock selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C3SEL, (uint32_t)(__I2C3_CLKSOURCE__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK1  PCLK selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI   HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK  System Clock selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C3SEL)))

/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  *
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1 PCLK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL, (uint32_t)(__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL)))

/** @brief  Macro to configure the LPTIM2 clock (LPTIM2CLK).
  *
  * @param  __LPTIM2_CLKSOURCE__ specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1 PCLK selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  LSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM2SEL, (uint32_t)(__LPTIM2_CLKSOURCE__))

/** @brief  Macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1 PCLK selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM2SEL)))

#if defined (LPTIM3)
/** @brief  Macro to configure the LPTIM3 clock (LPTIM3CLK).
  *
  * @param  __LPTIM3_CLKSOURCE__ specifies the LPTIM3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM3CLKSOURCE_PCLK1 PCLK selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSI  LSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_HSI  HSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSE  LSE selected as LPTIM3 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM3_CONFIG(__LPTIM3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM3SEL, (uint32_t)(__LPTIM3_CLKSOURCE__))

/** @brief  Macro to get the LPTIM3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM3CLKSOURCE_PCLK1 PCLK selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSI  LSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_HSI  HSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSE  LSE selected as LPTIM3 clock
  */
#define __HAL_RCC_GET_LPTIM3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM3SEL)))
#endif /* LPTIM3 */

#if defined(USB_DRD_FS)
/** @brief  Macro to configure the CLK48 source (CLK48CLK).
  *
  * @param  __USB_SOURCE__: specifies the CLK48 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USBCLKSOURCE_HSI48: HSI48 selected as USB source
  *            @arg RCC_USBCLKSOURCE_PLLQ : PLL selected as USB source
  *            @arg RCC_USBCLKSOURCE_MSIS : MSIS selected as USB source
  */
#define __HAL_RCC_USB_CONFIG(__USB_SOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CLK48SEL, (uint32_t)(__USB_SOURCE__))

/** @brief  macro to get the USB source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBCLKSOURCE_HSI48: HSI48 used as USB source
  *            @arg RCC_USBCLKSOURCE_PLLQ : PLL used as USB source
  *            @arg RCC_USBCLKSOURCE_MSIS  : MSIS used as USB source
  */
#define __HAL_RCC_GET_USB_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_CLK48SEL)))
#endif /* USB_DRD_FS */

/** @brief  Macro to configure the RNG source (CLK48CLK).
  *
  * @param  __RNG_SOURCE__: specifies the CLK48 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI48: HSI48 selected as USB source
  *            @arg RCC_RNGCLKSOURCE_PLLQ : PLL selected as USB source
  *            @arg RCC_RNGCLKSOURCE_MSIS  : MSIS selected as USB source
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_SOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CLK48SEL, (uint32_t)(__RNG_SOURCE__))

/** @brief  macro to get the RNG source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI48: HSI48 used as USB source
  *            @arg RCC_RNGCLKSOURCE_PLLQ : PLL used as USB source
  *            @arg RCC_RNGCLKSOURCE_MSIS : MSIS used as USB source
  */
#define __HAL_RCC_GET_RNG_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_CLK48SEL)))

/** @brief  macro to configure the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADCCLKSOURCE_SYSCLK : SYSCLK Clock selected as ADC1 clock
  *            @arg RCC_ADCCLKSOURCE_PLLP : PLLP Clock selected as ADC1 clock
  *            @arg RCC_ADCCLKSOURCE_HSI : HSI Clock selected as ADC1 clock
  */
#define __HAL_RCC_ADC_CONFIG(__ADCCLKSource__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, (uint32_t)(__ADCCLKSource__))

/** @brief  macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADCCLKSOURCE_SYSCLK : SYSCLK Clock selected as ADC clock
  *            @arg RCC_ADCCLKSOURCE_PLLP : PLLP Clock selected as ADC clock
  *            @arg RCC_ADCCLKSOURCE_HSI : HSI Clock selected as ADC clock
  */
#define __HAL_RCC_GET_ADC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_ADCSEL)))

/** @brief  macro to configure the TIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_PCLK : PCLK Clock used as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLLQ : PLLQ clock used as TIM1 clock
  */
#define __HAL_RCC_TIM1_CONFIG(__TIM1CLKSource__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIM1SEL, (uint32_t)(__TIM1CLKSource__))

/** @brief  macro to get the TIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_PCLK1 : PCLK Clock used as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLLQ : PLLQ clock used as TIM1 clock
  */
#define __HAL_RCC_GET_TIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_TIM1SEL)))

/** @brief  macro to configure the TIM15 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_TIM15CLKSOURCE_PCLK1 : PCLK Clock used as TIM15 clock
  *            @arg RCC_TIM15CLKSOURCE_PLLQ : PLLQ clock used as TIM15 clock
  */
#define __HAL_RCC_TIM15_CONFIG(__TIM15CLKSource__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIM1SEL, (uint32_t)(__TIM15CLKSource__))

/** @brief  macro to get the TIM15 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_TIM15CLKSOURCE_PCLK1 : PCLK Clock used as TIM15 clock
  *            @arg RCC_TIM15CLKSOURCE_PLLQ : PLLQ clock used as TIM15 clock
  */
#define __HAL_RCC_GET_TIM15_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_TIM15SEL)))

/** @defgroup RCCEx_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/**
  * @brief Enable the RCC LSE CSS Extended Interrupt Line.
  * @retval None
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_IT()      SET_BIT(EXTI->IMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Line.
  * @retval None
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_IT()     CLEAR_BIT(EXTI->IMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Enable the RCC LSE CSS Event Line.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Event Line.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief  Enable the RCC LSE CSS Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR1, RCC_EXTI_LINE_LSECSS)


/**
  * @brief  Enable the RCC LSE CSS Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Enable the RCC LSE CSS Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                      \
    __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_RCC_LSECSS_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                       \
    __HAL_RCC_LSECSS_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_RCC_LSECSS_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Check whether the specified RCC LSE CSS EXTI interrupt flag is set or not.
  * @retval EXTI RCC LSE CSS Line Status.
  */
#define __HAL_RCC_LSECSS_EXTI_GET_FLAG()       (READ_BIT(EXTI->PR1, RCC_EXTI_LINE_LSECSS) == RCC_EXTI_LINE_LSECSS)

/**
  * @brief Clear the RCC LSE CSS EXTI flag.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_CLEAR_FLAG()     WRITE_REG(EXTI->PR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Generate a Software interrupt on the RCC LSE CSS EXTI line.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_GENERATE_SWIT()  SET_BIT(EXTI->SWIER1, RCC_EXTI_LINE_LSECSS)

#if defined(CRS)

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
#define __HAL_RCC_CRS_ENABLE_IT(__INTERRUPT__)   SET_BIT(CRS->CR, (__INTERRUPT__))

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
#define __HAL_RCC_CRS_DISABLE_IT(__INTERRUPT__)  CLEAR_BIT(CRS->CR, (__INTERRUPT__))

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
#define  RCC_CRS_IT_ERROR_MASK                 (RCC_CRS_IT_TRIMOVF | RCC_CRS_IT_SYNCERR | RCC_CRS_IT_SYNCMISS)

#define __HAL_RCC_CRS_CLEAR_IT(__INTERRUPT__)  do { \
                                                    if(((__INTERRUPT__) & RCC_CRS_IT_ERROR_MASK) != 0U) \
                                                    { \
                                                      WRITE_REG(CRS->ICR, CRS_ICR_ERRC | \
                                                                ((__INTERRUPT__) & ~RCC_CRS_IT_ERROR_MASK)); \
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
#define __HAL_RCC_CRS_GET_FLAG(__FLAG__)  (READ_BIT(CRS->ISR, (__FLAG__)) == (__FLAG__))

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
  * @note RCC_CRS_FLAG_ERR clears RCC_CRS_FLAG_TRIMOVF, RCC_CRS_FLAG_SYNCERR, RCC_CRS_FLAG_SYNCMISS and
          consequently RCC_CRS_FLAG_ERR
  * @retval None
  */

/* CRS Flag Error Mask */
#define RCC_CRS_FLAG_ERROR_MASK                (RCC_CRS_FLAG_TRIMOVF | RCC_CRS_FLAG_SYNCERR | RCC_CRS_FLAG_SYNCMISS)

#define __HAL_RCC_CRS_CLEAR_FLAG(__FLAG__)     do { \
                                                    if(((__FLAG__) & RCC_CRS_FLAG_ERROR_MASK) != 0U) \
                                                    { \
                                                      WRITE_REG(CRS->ICR, CRS_ICR_ERRC | \
                                                                ((__FLAG__) & ~RCC_CRS_FLAG_ERROR_MASK)); \
                                                    } \
                                                    else \
                                                    { \
                                                      WRITE_REG(CRS->ICR, (__FLAG__)); \
                                                    } \
                                                  } while(0)

#endif /* CRS */

/**
  * @}
  */

#if defined(CRS)

/** @defgroup RCCEx_CRS_Extended_Features RCCEx CRS Extended Features
  * @{
  */
/**
  * @brief  Enable the oscillator clock for frequency error counter.
  * @note   when the CEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_FREQ_ERROR_COUNTER_ENABLE()  SET_BIT(CRS->CR, CRS_CR_CEN)

/**
  * @brief  Disable the oscillator clock for frequency error counter.
  * @retval None
  */
#define __HAL_RCC_CRS_FREQ_ERROR_COUNTER_DISABLE() CLEAR_BIT(CRS->CR, CRS_CR_CEN)

/**
  * @brief  Enable the automatic hardware adjustment of TRIM bits.
  * @note   When the AUTOTRIMEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_ENABLE()     SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

/**
  * @brief  Enable or disable the automatic hardware adjustment of TRIM bits.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_DISABLE()    CLEAR_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

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
#define __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)  (((__FTARGET__) / (__FSYNC__)) - 1U)

/**
  * @}
  */

#endif /* CRS */

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
void              HAL_RCCEx_GetPLLClockFreq(PLL_ClocksTypeDef *PLL_Clocks);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_EnablePLL(RCC_PLLInitTypeDef  *PLLInit);
HAL_StatusTypeDef HAL_RCCEx_DisablePLL(void);
void              HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk);
void              HAL_RCCEx_StandbyMSIRangeConfig(uint32_t MSIRange);
void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableLSECSS_IT(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);
void              HAL_RCCEx_EnableMSIPLLMode(void);
void              HAL_RCCEx_DisableMSIPLLMode(void);

/**
  * @}
  */

#if defined(CRS)

/** @addtogroup RCCEx_Exported_Functions_Group3
  * @{
  */

void              HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *const pInit);
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

#endif /* CRS */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))
#if (defined (LPUART3) || defined (LPTIM3) || defined (USB_DRD_FS))
#define RCC_PERIPHCLOCK_ALL (RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2  | \
                             RCC_PERIPHCLK_USART3  | RCC_PERIPHCLK_USART4  | \
                             RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_LPUART2 | \
                             RCC_PERIPHCLK_LPUART3 | RCC_PERIPHCLK_I2C1    | \
                             RCC_PERIPHCLK_I2C3    | RCC_PERIPHCLK_LPTIM1  | \
                             RCC_PERIPHCLK_LPTIM2  | RCC_PERIPHCLK_LPTIM3  | \
                             RCC_PERIPHCLK_TIM1    | RCC_PERIPHCLK_TIM15   | \
                             RCC_PERIPHCLK_USB     | RCC_PERIPHCLK_RNG     | \
                             RCC_PERIPHCLK_RTC     | RCC_PERIPHCLK_ADC)
#else
#define RCC_PERIPHCLOCK_ALL (RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2  | \
                             RCC_PERIPHCLK_USART3  | RCC_PERIPHCLK_USART4  | \
                             RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_LPUART2 | \
                             RCC_PERIPHCLK_I2C1    |  RCC_PERIPHCLK_I2C3   | \
                             RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_LPTIM2  | \
                             RCC_PERIPHCLK_TIM1    | RCC_PERIPHCLK_TIM15   | \
                             RCC_PERIPHCLK_RNG     | RCC_PERIPHCLK_RTC     | \
                             RCC_PERIPHCLK_ADC)
#endif /* LPUART3 | LPTIM3 | USB_DRD_FS */
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  ((((__SELECTION__) & RCC_PERIPHCLOCK_ALL) != (0x00U)) && \
                                            (((__SELECTION__) & ~RCC_PERIPHCLOCK_ALL) == (0x00U)))
#define IS_RCC_USART1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI)    || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE))

#define IS_RCC_USART2CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_USART2CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI)    || \
   ((__SOURCE__) == RCC_USART2CLKSOURCE_LSE))

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI)    || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE))

#define IS_RCC_LPUART2CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPUART2CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_LPUART2CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_LPUART2CLKSOURCE_HSI)    || \
   ((__SOURCE__) == RCC_LPUART2CLKSOURCE_LSE))
#if defined (LPUART3)
#define IS_RCC_LPUART3CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPUART3CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_LPUART3CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_LPUART3CLKSOURCE_HSI)    || \
   ((__SOURCE__) == RCC_LPUART3CLKSOURCE_LSE))
#endif /* LPUART3 */
#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSI))

#define IS_RCC_I2C2CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_I2C2CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_I2C2CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_I2C2CLKSOURCE_HSI))

#define IS_RCC_I2C3CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_I2C3CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_I2C3CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_I2C3CLKSOURCE_HSI))

#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI)    || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)    || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))

#define IS_RCC_LPTIM2CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPTIM2CLKSOURCE_PCLK1)|| \
   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_HSI)  || \
   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSI)  || \
   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSE))
#if defined (LPTIM3)
#define IS_RCC_LPTIM3CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPTIM3CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_LPTIM3CLKSOURCE_LSI)   || \
   ((__SOURCE__) == RCC_LPTIM3CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_LPTIM3CLKSOURCE_LSE))
#endif /* LPTIM3 */
#define IS_RCC_TIM1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_TIM1CLKSOURCE_PCLK1)   || \
   ((__SOURCE__) == RCC_TIM1CLKSOURCE_PLLQ))
#if defined (USB_DRD_FS)
#define IS_RCC_USBCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USBCLKSOURCE_NONE)  || \
   ((__SOURCE__) == RCC_USBCLKSOURCE_MSI)   || \
   ((__SOURCE__) == RCC_USBCLKSOURCE_PLLQ)  || \
   ((__SOURCE__) == RCC_USBCLKSOURCE_HSI48))
#endif /* USB_DRD_FS */
#if defined(RCC_RNGCLKSOURCE_HSI48)
#define IS_RCC_RNGCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_RNGCLKSOURCE_NONE)  || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_MSI)   || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_PLLQ)  || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_HSI48))
#else
#define IS_RCC_RNGCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_RNGCLKSOURCE_NONE)  || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_MSI)   || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_PLLQ))
#endif /* RCC_CRRCR_HSI48ON */
#define IS_RCC_TIM15CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_TIM15CLKSOURCE_PCLK1)  || \
   ((__SOURCE__) == RCC_TIM15CLKSOURCE_PLLQ))

#define IS_RCC_ADCCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_ADCCLKSOURCE_SYSCLK)|| \
   ((__SOURCE__) == RCC_ADCCLKSOURCE_PLLP)  || \
   ((__SOURCE__) == RCC_ADCCLKSOURCE_HSI))

#if defined(CRS)

#define IS_RCC_CRS_SYNC_SOURCE(__SOURCE__) (((__SOURCE__) == RCC_CRS_SYNC_SOURCE_GPIO) || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_LSE)  || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_USB))

#define IS_RCC_CRS_SYNC_DIV(__DIV__)       (((__DIV__) == RCC_CRS_SYNC_DIV1)  || ((__DIV__) == RCC_CRS_SYNC_DIV2)  || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV4)  || ((__DIV__) == RCC_CRS_SYNC_DIV8)  || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV16) || ((__DIV__) == RCC_CRS_SYNC_DIV32) || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV64) || ((__DIV__) == RCC_CRS_SYNC_DIV128))

#define IS_RCC_CRS_SYNC_POLARITY(__POLARITY__) (((__POLARITY__) == RCC_CRS_SYNC_POLARITY_RISING) || \
                                                ((__POLARITY__) == RCC_CRS_SYNC_POLARITY_FALLING))

#define IS_RCC_CRS_RELOADVALUE(__VALUE__)  (((__VALUE__) <= 0xFFFFU))

#define IS_RCC_CRS_ERRORLIMIT(__VALUE__)   (((__VALUE__) <= 0xFFU))

#define IS_RCC_CRS_HSI48CALIBRATION(__VALUE__) (((__VALUE__) <= 0x7FU))

#define IS_RCC_CRS_FREQERRORDIR(__DIR__)   (((__DIR__) == RCC_CRS_FREQERRORDIR_UP) || \
                                            ((__DIR__) == RCC_CRS_FREQERRORDIR_DOWN))

#endif /* CRS */

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

#endif /* __STM32U0xx_HAL_RCC_EX_H */
