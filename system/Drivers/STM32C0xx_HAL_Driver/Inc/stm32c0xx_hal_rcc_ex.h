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

#if defined(USB_DRD_FS)
  uint32_t UsbClockSelection;      /*!< Specifies USB clock source.
                                   This parameter can be a value of @ref RCCEx_USB_Clock_Source */
#endif /* USB_DRD_FS */

#if defined(FDCAN1)
  uint32_t Fdcan1ClockSelection;   /*!< Specifies FDCAN1 clock source.
                                   This parameter can be a value of @ref RCCEx_FDCAN1_Clock_Source */
#endif /* FDCAN1 */

  uint32_t AdcClockSelection;      /*!< Specifies ADC interface clock source
                                        This parameter can be a value of @ref RCCEx_ADC_Clock_Source */

  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source.
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
                        This parameter must be a value of @ref RCCEx_CRS_FreqErrorDirection*/

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
#define RCC_LSCOSOURCE_LSI             0x00000000U           /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE             RCC_CSR1_LSCOSEL      /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1           0x00000001U
#define RCC_PERIPHCLK_I2C1             0x00000002U
#define RCC_PERIPHCLK_I2S1             0x00000004U
#if defined(USB_DRD_FS)
#define RCC_PERIPHCLK_USB              0x00000008U
#endif /* USB_DRD_FS */
#if defined(FDCAN1)
#define RCC_PERIPHCLK_FDCAN1           0x00000010U
#endif /* FDCAN1 */
#define RCC_PERIPHCLK_ADC              0x00000020U
#define RCC_PERIPHCLK_RTC              0x00000040U
#define RCC_PERIPHCLK_HSIKER           0x00000080U

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
#define RCC_I2C1CLKSOURCE_PCLK1        0x00000000U                /*!< APB clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0        /*!< SYSCLK clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_HSIKER       RCC_CCIPR_I2C1SEL_1        /*!< HSI Kernel clock selected as I2C1 clock */
/**
  * @}
  */

/** @defgroup RCCEx_I2S1_Clock_Source RCC I2S1 Clock Source
  * @{
  */
#define RCC_I2S1CLKSOURCE_SYSCLK       0x00000000U              /*!< SYSCLK clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_HSIKER       RCC_CCIPR_I2S1SEL_1      /*!< HSI Kernel clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_EXT          RCC_CCIPR_I2S1SEL        /*!< External I2S clock source selected as I2S1 clock */

/**
  * @}
  */
#if defined(USB_DRD_FS)
/** @defgroup RCCEx_USB_Clock_Source USB Clock Source
  * @{
  */
#define RCC_USBCLKSOURCE_HSI48         0x00000000U
#define RCC_USBCLKSOURCE_HSE           RCC_CCIPR2_USBSEL
/**
  * @}
  */
#endif /* USB_DRD_FS */

#if defined(FDCAN1)
/** @defgroup RCCEx_FDCAN1_Clock_Source FDCAN1 Clock Source
  * @{
  */
#define RCC_FDCAN1CLKSOURCE_PCLK1         0x00000000U
#define RCC_FDCAN1CLKSOURCE_HSIKER        RCC_CCIPR_FDCAN1SEL_0
#define RCC_FDCAN1CLKSOURCE_HSE           RCC_CCIPR_FDCAN1SEL_1
/**
  * @}
  */
#endif /* FDCAN1 */

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
#define RCC_CRS_SYNC_SOURCE_LSE        CRS_CFGR_SYNCSRC_0  /*!< Synchro Signal source LSE */
#define RCC_CRS_SYNC_SOURCE_USB        CRS_CFGR_SYNCSRC_1  /*!< Synchro Signal source USB SOF (default)*/
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroDivider RCCEx CRS SynchroDivider
  * @{
  */
#define RCC_CRS_SYNC_DIV1         0U                                        /*!< Synchro Signal not divided (default) */
#define RCC_CRS_SYNC_DIV2         CRS_CFGR_SYNCDIV_0                        /*!< Synchro Signal divided by 2 */
#define RCC_CRS_SYNC_DIV4         CRS_CFGR_SYNCDIV_1                        /*!< Synchro Signal divided by 4 */
#define RCC_CRS_SYNC_DIV8         (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 8 */
#define RCC_CRS_SYNC_DIV16        CRS_CFGR_SYNCDIV_2                        /*!< Synchro Signal divided by 16 */
#define RCC_CRS_SYNC_DIV32        (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 32 */
#define RCC_CRS_SYNC_DIV64        (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1) /*!< Synchro Signal divided by 64 */
#define RCC_CRS_SYNC_DIV128       CRS_CFGR_SYNCDIV                          /*!< Synchro Signal divided by 128 */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroPolarity RCCEx CRS SynchroPolarity
  * @{
  */
#define RCC_CRS_SYNC_POLARITY_RISING   0U                   /*!< Synchro Active on rising edge (default) */
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
#define RCC_CRS_FREQERRORDIR_UP        0U                  /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN      CRS_ISR_FEDIR       /*!< Downcounting direction, the actual frequency is below the target */
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

#if defined(USB_DRD_FS)
/** @brief  Macro to configure the CLK48 source (CLK48CLK).
  *
  * @param  __USB_SOURCE__: specifies the CLK48 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USBCLKSOURCE_HSI48: HSI48 selected as USB source
  *            @arg RCC_USBCLKSOURCE_HSE  : HSE selected as USB source
  */
#define __HAL_RCC_USB_CONFIG(__USB_SOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_USBSEL, (uint32_t)(__USB_SOURCE__))

/** @brief  macro to get the USB source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBCLKSOURCE_HSI48: HSI48 used as USB source
  *            @arg RCC_USBCLKSOURCE_HSE  : HSE used as USB source
  */
#define __HAL_RCC_GET_USB_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_USBSEL)))
#endif /* USB_DRD_FS */

#if defined(FDCAN1)
/** @brief  Macro to configure the FDCAN1 clock (FDCAN1CLK).
  *
  * @param  __FDCAN1_CLKSOURCE__  specifies the FDCAN1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_FDCAN1CLKSOURCE_PCLK1  APB Clock selected as FDCAN1 clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_HSIKER  HSI Kernel Clock selected as FDCAN1 clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_HSE     HSE clock selected as FDCAN1 clock
  */
#define __HAL_RCC_FDCAN1_CONFIG(__FDCAN1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_FDCAN1SEL, (uint32_t)(__FDCAN1_CLKSOURCE__))

/** @brief  Macro to get the FDCAN1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_FDCAN1CLKSOURCE_PCLK1  APB Clock selected as FDCAN1 clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_HSIKER  HSI Kernel Clock selected as FDCAN1 clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_HSE     HSE clock selected as FDCAN1 clock
  */
#define __HAL_RCC_GET_FDCAN1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_FDCAN1SEL)))
#endif /* FDCAN1 */

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
  *       consequently RCC_CRS_FLAG_ERR
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

#if defined(CRS)

/** @addtogroup RCCEx_Exported_Functions_Group3
  * @{
  */

void              HAL_RCCEx_CRSConfig(RCC_CRSInitTypeDef *pInit);
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
/** @defgroup RCCEx_Private_Macros RCCEx Private Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#if defined (USB_DRD_FS)
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
  ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_USB)     == RCC_PERIPHCLK_USB)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_HSIKER)  == RCC_PERIPHCLK_HSIKER))
#elif defined (FDCAN1)
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
  ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_FDCAN1)  == RCC_PERIPHCLK_FDCAN1)  || \
   (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_HSIKER)  == RCC_PERIPHCLK_HSIKER))
#else
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
  ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_HSIKER)  == RCC_PERIPHCLK_HSIKER))
#endif /* USB_DRD_FS */

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

#if defined (FDCAN1)
#define IS_RCC_FDCAN1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_FDCAN1CLKSOURCE_HSE)   || \
   ((__SOURCE__) == RCC_FDCAN1CLKSOURCE_HSIKER)|| \
   ((__SOURCE__) == RCC_FDCAN1CLKSOURCE_PCLK1))
#endif /* FDCAN1 */

#if defined (USB_DRD_FS)
#define IS_RCC_USBCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USBCLKSOURCE_HSE)   || \
   ((__SOURCE__) == RCC_USBCLKSOURCE_HSI48))
#endif /* USB_DRD_FS */

#define IS_RCC_ADCCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_ADCCLKSOURCE_SYSCLK)  || \
   ((__SOURCE__) == RCC_ADCCLKSOURCE_HSIKER))

#define IS_RCC_HSIKERDIV(__DIV__) (((__DIV__) == RCC_HSIKER_DIV1)  || ((__DIV__) == RCC_HSIKER_DIV2) || \
                                   ((__DIV__) == RCC_HSIKER_DIV3)  || ((__DIV__) == RCC_HSIKER_DIV4) || \
                                   ((__DIV__) == RCC_HSIKER_DIV5)  || ((__DIV__) == RCC_HSIKER_DIV6) || \
                                   ((__DIV__) == RCC_HSIKER_DIV7)  || ((__DIV__) == RCC_HSIKER_DIV8))

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

#endif /* STM32C0xx_HAL_RCC_EX_H */
