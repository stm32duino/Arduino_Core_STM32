/**
  ******************************************************************************
  * @file    stm32u3xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL  module.
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
#ifndef __STM32U3xx_HAL_RCC_H
#define __STM32U3xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"
#include "stm32u3xx_ll_rcc.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, MSIS, MSIK, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;        /*!< The oscillators to be configured.
                                       This parameter can be a value of @ref RCC_Oscillator_Type                    */

  uint32_t HSEState;              /*!< The new state of the HSE.
                                       This parameter can be a value of @ref RCC_HSE_Config                         */

  uint32_t HSIState;              /*!< The new state of the HSI.
                                       This parameter can be a value of @ref RCC_HSI_Config                         */

  uint32_t HSICalibrationValue;   /*!< The calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F  */

  uint32_t HSI48State;            /*!< The new state of the HSI48.
                                       This parameter can be a value of @ref RCC_HSI48_Config                       */

  uint32_t LSEState;              /*!< The new state of the LSE.
                                       This parameter can be a value of @ref RCC_LSE_Config                         */

  uint32_t LSIState;              /*!< The new state of the LSI.
                                       This parameter can be a value of @ref RCC_LSI_Config                         */

  uint32_t LSIDiv;                /*!< The division factor of the LSI. Applicable only to LSI.
                                       This parameter can be a value of @ref RCC_LSI_Div                            */

  uint32_t MSISState;             /*!< The new state of the MSIS.
                                       This parameter can be a value of @ref RCC_MSI_Config                         */

  uint32_t MSISSource;            /*!< The MSIRCx source to feed the MSIS.
                                       This parameter can be a value of @ref RCC_MSI_Source                         */

  uint32_t MSISDiv;               /*!< The division factor of the MSIS.
                                       This parameter can be a value of @ref RCC_MSI_Div                            */

  uint32_t MSIKState;             /*!< The new state of the MSIK.
                                       This parameter can be a value of @ref RCC_MSI_Config                         */

  uint32_t MSIKSource;            /*!< The MSIRCx source to feed the MSIK.
                                       This parameter can be a value of @ref RCC_MSI_Source                         */

  uint32_t MSIKDiv;               /*!< The division factor of the MSIK.
                                       This parameter can be a value of @ref RCC_MSI_Div                            */

} RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;               /*!< The clock to be configured.
                                         This parameter can be a value of @ref RCC_System_Clock_Type      */

  uint32_t SYSCLKSource;            /*!< The clock source used as system clock (SYSCLK).
                                         This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t AHBCLKDivider;           /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                         This parameter can be a value of @ref RCC_AHB_Clock_Source       */

  uint32_t APB1CLKDivider;          /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                         This parameter can be a value of @ref RCC_APB1_APB2_APB3_Clock_Source */

  uint32_t APB2CLKDivider;          /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                         This parameter can be a value of @ref RCC_APB1_APB2_APB3_Clock_Source */

  uint32_t APB3CLKDivider;          /*!< The APB3 clock (PCLK3) divider. This clock is derived from the AHB clock (HCLK).
                                         This parameter can be a value of @ref RCC_APB1_APB2_APB3_Clock_Source */

} RCC_ClkInitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_LSE_TIMEOUT_VALUE           LSE_STARTUP_TIMEOUT
/**
  * @}
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE         0x00000000U   /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSE          0x00000001U   /*!< HSE to configure */
#define RCC_OSCILLATORTYPE_HSI          0x00000002U   /*!< HSI to configure */
#define RCC_OSCILLATORTYPE_LSE          0x00000004U   /*!< LSE to configure */
#define RCC_OSCILLATORTYPE_LSI          0x00000008U   /*!< LSI to configure */
#define RCC_OSCILLATORTYPE_HSI48        0x00000010U   /*!< HSI48 to configure */
#define RCC_OSCILLATORTYPE_MSIS         0x00000020U   /*!< MSIS to configure */
#define RCC_OSCILLATORTYPE_MSIK         0x00000040U   /*!< MSIK to configure */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                     0x00000000U                                   /*!< HSE clock deactivation */
#define RCC_HSE_ON                      RCC_CR_HSEON                                  /*!< HSE clock activation */
#define RCC_HSE_BYPASS                 (RCC_CR_HSEBYP | RCC_CR_HSEON)                 /*!< External clock source for HSE clock */
#define RCC_HSE_BYPASS_DIGITAL         (RCC_CR_HSEEXT | RCC_CR_HSEBYP | RCC_CR_HSEON) /*!< Digital external clock source for HSE clock */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                     0x00000000U         /*!< HSI clock deactivation */
#define RCC_HSI_ON                      RCC_CR_HSION        /*!< HSI clock activation */

#define RCC_HSICALIBRATION_DEFAULT      0x10U               /* Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_HSI48_Config HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                   0x00000000U         /*!< HSI48 clock deactivation */
#define RCC_HSI48_ON                    RCC_CR_HSI48ON      /*!< HSI48 clock activation */
/**
  * @}
  */


/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                     0U                                                     /*!< LSE clock deactivation */
#define RCC_LSE_ON_RTC_ONLY             RCC_BDCR_LSEON                                         /*!< LSE clock activation for RTC only */
#define RCC_LSE_ON                      (RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON)                   /*!< LSE clock activation for RCC and peripherals */
#define RCC_LSE_BYPASS_RTC_ONLY         (RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)                     /*!< External clock source for LSE clock */
#define RCC_LSE_BYPASS                  (RCC_BDCR_LSEBYP | RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON) /*!< External clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U          /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR_LSION        /*!< LSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_LSI_Div LSI Div
  * @{
  */
#define RCC_LSI_DIV1                    0U                  /*!< LSI clock is not divided */
#define RCC_LSI_DIV128                  RCC_CSR_LSIPREDIV   /*!< LSI clock is divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_MSI_Config MSI Config
  * @{
  */
#define RCC_MSI_OFF                     0x00000000U         /*!< MSI clock deactivation */
#define RCC_MSI_ON                      RCC_CR_MSISON       /*!< MSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_MSI_Source MSI Source
  * @{
  */
#define RCC_MSI_RC0                     0x00000000U         /*!< MSIRC0 (96 MHz) selected as MSI source */
#define RCC_MSI_RC1                     RCC_ICSCR1_MSISSEL  /*!< MSIRC1 (24 MHz) selected as MSI source */
/**
  * @}
  */

/** @defgroup RCC_MSI_Div MSI Divider
  * @note   If MSI source is MSIRC0
  *         range 0 (96 MHz) is selected using RCC_MSI_DIV1
  *         range 1 (48 MHz) is selected using RCC_MSI_DIV2
  *         range 2 (24 MHz) is selected using RCC_MSI_DIV4
  *         range 3 (12 MHz) is selected using RCC_MSI_DIV8
  * @note   If MSI source is MSIRC1
  *         range 4 (24 MHz) is selected using RCC_MSI_DIV1
  *         range 5 (12 MHz) is selected using RCC_MSI_DIV2
  *         range 6 ( 6 MHz) is selected using RCC_MSI_DIV4
  *         range 7 ( 3 MHz) is selected using RCC_MSI_DIV8
  * @{
  */
#define RCC_MSI_DIV1                    0x00000000U                                    /*!< MSIRCx divided by 1 */
#define RCC_MSI_DIV2                    RCC_ICSCR1_MSISDIV_0                           /*!< MSIRCx divided by 2 */
#define RCC_MSI_DIV4                    RCC_ICSCR1_MSISDIV_1                           /*!< MSIRCx divided by 4 */
#define RCC_MSI_DIV8                    (RCC_ICSCR1_MSISDIV_1 | RCC_ICSCR1_MSISDIV_0)  /*!< MSIRCx divided by 8 */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK            0x00000001U  /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK              0x00000002U  /*!< HCLK to configure   */
#define RCC_CLOCKTYPE_PCLK1             0x00000004U  /*!< PCLK1 to configure  */
#define RCC_CLOCKTYPE_PCLK2             0x00000008U  /*!< PCLK2 to configure  */
#define RCC_CLOCKTYPE_PCLK3             0x00000010U  /*!< PCLK3 to configure  */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_MSIS           0x00000000U                        /*!< MSIS selection as system clock */
#define RCC_SYSCLKSOURCE_HSI            RCC_CFGR1_SW_0                     /*!< HSI16 selection as system clock */
#define RCC_SYSCLKSOURCE_HSE            RCC_CFGR1_SW_1                     /*!< HSE selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_MSIS    0x00000000U                         /*!< HSI16 used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSI     RCC_CFGR1_SWS_0                     /*!< HSI16 used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE     RCC_CFGR1_SWS_1                     /*!< HSE used as system clock */
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                 0x00000000U                                                                 /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2                 RCC_CFGR2_HPRE_3                                                            /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4                 (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_0)                                       /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8                 (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1)                                       /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0)                    /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2)                                       /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128               (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0)                    /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256               (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1)                    /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512               (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APB1_APB2_APB3_Clock_Source APB1 APB2 APB3 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                   (0x00000000U)                                               /*!< HCLK not divided */
#define RCC_HCLK_DIV2                   RCC_CFGR2_PPRE1_2                                           /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4                   (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_0)                     /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8                   (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1)                     /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16                  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1 | RCC_CFGR2_PPRE1_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_DISABLE        0x00000000U        /*!< RTC clock is disabled */
#define RCC_RTCCLKSOURCE_LSE            RCC_BDCR_RTCSEL_0  /*!< LSE oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSI            RCC_BDCR_RTCSEL_1  /*!< LSI or LIS2 oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV32      RCC_BDCR_RTCSEL    /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/* @cond */
/*  32     28      20       16      0
    ---------------------------------
    | MCO   | GPIO  | GPIO  | GPIO  |
    | Index |  AF   | Port  |  Pin  |
    --------------------------------- */
#define RCC_MCO_GPIOPIN_POS             0U
#define RCC_MCO_GPIOPIN_MASK            (0xFFFFuL << RCC_MCO_GPIOPIN_POS)
#define RCC_MCO_GPIOPORT_POS            16U
#define RCC_MCO_GPIOPORT_MASK           (0xFuL << RCC_MCO_GPIOPORT_POS)
#define RCC_MCO_GPIOAF_POS              20U
#define RCC_MCO_GPIOAF_MASK             (0xFuL << RCC_MCO_GPIOAF_POS)
#define RCC_MCO_INDEX_POS               28U
#define RCC_MCO_INDEX_MASK              (0x1uL << RCC_MCO_INDEX_POS)
/* @endcond */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO1_PA8                    ((0x00U << RCC_MCO_INDEX_POS) |\
                                         (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | GPIO_PIN_8)
#define RCC_MCO1_PA9                    ((0x00U << RCC_MCO_INDEX_POS) |\
                                         (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | GPIO_PIN_9)
#define RCC_MCO1                        RCC_MCO1_PA8
#define RCC_MCO2_PA8                    ((0x01U << RCC_MCO_INDEX_POS) |\
                                         (GPIO_AF11_MCO2 << RCC_MCO_GPIOAF_POS) | GPIO_PIN_8)
#define RCC_MCO2_PA10                   ((0x01U << RCC_MCO_INDEX_POS) |\
                                         (GPIO_AF11_MCO2 << RCC_MCO_GPIOAF_POS) | GPIO_PIN_10)
#define RCC_MCO2                        RCC_MCO2_PA8
#define RCC_MCO                         RCC_MCO1
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK          0x00000000U                                                       /*!< MCO1 output disabled, no clock on MCO1 */
#define RCC_MCO1SOURCE_SYSCLK           RCC_CFGR1_MCOSEL_0                                                /*!< SYSCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_MSIS             RCC_CFGR1_MCOSEL_1                                                /*!< MSIS selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI              (RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_0)                         /*!< HSI16 selection as MCO1 source */
#define RCC_MCO1SOURCE_HSE              RCC_CFGR1_MCOSEL_2                                                /*!< HSE selection as MCO1 source */
#define RCC_MCO1SOURCE_LSI              (RCC_CFGR1_MCOSEL_2 | RCC_CFGR1_MCOSEL_0)                         /*!< LSI selection as MCO1 source */
#define RCC_MCO1SOURCE_LSE              (RCC_CFGR1_MCOSEL_2 | RCC_CFGR1_MCOSEL_1)                         /*!< LSE selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI48            (RCC_CFGR1_MCOSEL_2 | RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_0)    /*!< HSI48 selection as MCO1 source */
#define RCC_MCO1SOURCE_MSIK             RCC_CFGR1_MCOSEL_3                                                /*!< MSIK selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler MCO1 Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                    0x00000000U                                                       /*!< MCO is divided by 1 */
#define RCC_MCODIV_2                    RCC_CFGR1_MCOPRE_0                                                /*!< MCO is divided by 2 */
#define RCC_MCODIV_4                    RCC_CFGR1_MCOPRE_1                                                /*!< MCO is divided by 4 */
#define RCC_MCODIV_8                    (RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0)                         /*!< MCO is divided by 8 */
#define RCC_MCODIV_16                   RCC_CFGR1_MCOPRE_2                                                /*!< MCO is divided by 16 */
#define RCC_MCODIV_32                   (RCC_CFGR1_MCOPRE_2 | RCC_CFGR1_MCOPRE_0)                         /*!< MCO is divided by 32 */
#define RCC_MCODIV_64                   (RCC_CFGR1_MCOPRE_2 | RCC_CFGR1_MCOPRE_1)                         /*!< MCO is divided by 64 */
#define RCC_MCODIV_128                  (RCC_CFGR1_MCOPRE_2 | RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0)    /*!< MCO is divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Source MCO2 Clock Source
  * @{
  */
#define RCC_MCO2SOURCE_NOCLOCK          0x00000000U                                                       /*!< MCO2 output disabled, no clock on MCO2 */
#define RCC_MCO2SOURCE_SYSCLK           RCC_CFGR1_MCO2SEL_0                                               /*!< SYSCLK selection as MCO2 source */
#define RCC_MCO2SOURCE_MSIS             RCC_CFGR1_MCO2SEL_1                                               /*!< MSIS selection as MCO2 source */
#define RCC_MCO2SOURCE_HSI              (RCC_CFGR1_MCO2SEL_1 | RCC_CFGR1_MCO2SEL_0)                       /*!< HSI16 selection as MCO2 source */
#define RCC_MCO2SOURCE_HSE              RCC_CFGR1_MCO2SEL_2                                               /*!< HSE selection as MCO2 source */
#define RCC_MCO2SOURCE_LSI              (RCC_CFGR1_MCO2SEL_2 | RCC_CFGR1_MCO2SEL_0)                       /*!< LSI selection as MCO2 source */
#define RCC_MCO2SOURCE_LSE              (RCC_CFGR1_MCO2SEL_2 | RCC_CFGR1_MCO2SEL_1)                       /*!< LSE selection as MCO2 source */
#define RCC_MCO2SOURCE_HSI48            (RCC_CFGR1_MCO2SEL_2 | RCC_CFGR1_MCO2SEL_1 | RCC_CFGR1_MCO2SEL_0) /*!< HSI48 selection as MCO2 source */
#define RCC_MCO2SOURCE_MSIK             RCC_CFGR1_MCO2SEL_3                                               /*!< MSIK selection as MCO2 source */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Prescaler MCO2 Clock Prescaler
  * @{
  */
#define RCC_MCO2DIV_1                   0x00000000U                                                       /*!< MCO2 is divided by 1 */
#define RCC_MCO2DIV_2                   RCC_CFGR1_MCO2PRE_0                                               /*!< MCO2 is divided by 2 */
#define RCC_MCO2DIV_4                   RCC_CFGR1_MCO2PRE_1                                               /*!< MCO2 is divided by 4 */
#define RCC_MCO2DIV_8                   (RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)                       /*!< MCO2 is divided by 8 */
#define RCC_MCO2DIV_16                  RCC_CFGR1_MCO2PRE_2                                               /*!< MCO2 is divided by 16 */
#define RCC_MCO2DIV_32                  (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_0)                       /*!< MCO2 is divided by 32 */
#define RCC_MCO2DIV_64                  (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1)                       /*!< MCO2 is divided by 64 */
#define RCC_MCO2DIV_128                 (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0) /*!< MCO2 is divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_HSIRDY                   RCC_CIFR_HSIRDYF      /*!< HSI16 Ready Interrupt flag */
#define RCC_IT_HSI48RDY                 RCC_CIFR_HSI48RDYF    /*!< HSI48 Ready Interrupt flag */
#define RCC_IT_HSERDY                   RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt flag */
#define RCC_IT_LSIRDY                   RCC_CIFR_LSIRDYF      /*!< LSI Ready Interrupt flag */
#define RCC_IT_LSERDY                   RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt flag */
#define RCC_IT_MSISRDY                  RCC_CIFR_MSISRDYF     /*!< MSIS Ready Interrupt flag */
#define RCC_IT_MSIKRDY                  RCC_CIFR_MSIKRDYF     /*!< MSIK Ready Interrupt flag */
#define RCC_IT_MSI_PLL0RDY              RCC_CIFR_MSIPLL0RDYF  /*!< MSI RC0 PLL Ready Interrupt flag */
#define RCC_IT_MSI_PLL1RDY              RCC_CIFR_MSIPLL1RDYF  /*!< MSI RC1 PLL Ready Interrupt flag */
#define RCC_IT_MSI_PLLUNLCK_HSE         RCC_CIFR_MSIPLLHSUF   /*!< MSI PLL-mode with HSE unlock Interrupt Flag*/
#define RCC_IT_MSI_PLLUNLCK_LSE         RCC_CIFR_MSIPLLUF     /*!< MSI PLL-mode with LSE unlock Interrupt Flag*/
#define RCC_IT_CSS                      RCC_CIFR_CSSF         /*!< Clock Security System Interrupt flag */
#define RCC_IT_LSECSS                   RCC_CIFR_LSECSSF      /*!< LSE Clock Security System Interrupt flag */
/**
  * @}
  */

/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: BDCR register
  *                 - 011: CSR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                 ((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos)        /*!< HSI Ready flag */
#define RCC_FLAG_HSI48RDY               ((CR_REG_INDEX << 5U) | RCC_CR_HSI48RDY_Pos)      /*!< HSI48 Ready flag */
#define RCC_FLAG_HSERDY                 ((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos)        /*!< HSE Ready flag */
#define RCC_FLAG_MSISRDY                ((CR_REG_INDEX << 5U) | RCC_CR_MSISRDY_Pos)       /*!< MSIS Ready flag */
#define RCC_FLAG_MSIKRDY                ((CR_REG_INDEX << 5U) | RCC_CR_MSIKRDY_Pos)       /*!< MSIK Ready flag */
#define RCC_FLAG_MSI_PLL0RDY            ((CR_REG_INDEX << 5U) | RCC_CR_MSIPLL0RDY_Pos)    /*!< MSI RC0 PLL Ready Interrupt flag */
#define RCC_FLAG_MSI_PLL1RDY            ((CR_REG_INDEX << 5U) | RCC_CR_MSIPLL1RDY_Pos)    /*!< MSI RC1 PLL Ready Interrupt flag */

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                 ((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos)    /*!< LSE Ready flag */
#define RCC_FLAG_LSESYSRDY              ((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSESYSRDY_Pos) /*!< LSESYS Ready flag */
#define RCC_FLAG_LSECSSD                ((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSECSSD_Pos)   /*!< LSE Clock Security System Interrupt flag */

/* Flags in the CSR register */
#define RCC_FLAG_OBLRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_OBLRSTF_Pos)      /*!< Option Byte Loader reset flag */
#define RCC_FLAG_PINRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos)      /*!< PIN reset flag */
#define RCC_FLAG_BORRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_BORRSTF_Pos)      /*!< BOR reset flag */
#define RCC_FLAG_SFTRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos)      /*!< Software Reset flag */
#define RCC_FLAG_IWDGRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos)     /*!< Independent Watchdog reset flag */
#define RCC_FLAG_WWDGRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos)     /*!< Window watchdog reset flag */
#define RCC_FLAG_LPWRRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_LPWRRSTF_Pos)     /*!< Low-Power reset flag */
#define RCC_FLAG_LSIRDY                 ((CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos)       /*!< LSI Ready flag */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_LOW                0x00000000U            /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR_LSEDRV_0      /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR_LSEDRV_1      /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH               RCC_BDCR_LSEDRV        /*!< LSE high drive capability */
/**
  * @}
  */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define RCC_RESET_FLAG_OBL              RCC_CSR_OBLRSTF    /*!< Option Byte Loader reset flag */
#define RCC_RESET_FLAG_PIN              RCC_CSR_PINRSTF    /*!< PIN reset flag */
#define RCC_RESET_FLAG_PWR              RCC_CSR_BORRSTF    /*!< BOR or POR/PDR reset flag */
#define RCC_RESET_FLAG_SW               RCC_CSR_SFTRSTF    /*!< Software Reset flag */
#define RCC_RESET_FLAG_IWDG             RCC_CSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define RCC_RESET_FLAG_WWDG             RCC_CSR_WWDGRSTF   /*!< Window watchdog reset flag */
#define RCC_RESET_FLAG_LPWR             RCC_CSR_LPWRRSTF   /*!< Low power reset flag */
#define RCC_RESET_FLAG_ALL              (RCC_RESET_FLAG_OBL | RCC_RESET_FLAG_PIN  | RCC_RESET_FLAG_PWR  | \
                                         RCC_RESET_FLAG_SW  | RCC_RESET_FLAG_IWDG | RCC_RESET_FLAG_WWDG | \
                                         RCC_RESET_FLAG_LPWR)
/**
  * @}
  */

/** @defgroup RCC_items RCC items
  * @brief RCC items to configure attributes on
  * @{
  */
#define RCC_HSI                         RCC_SECCFGR_HSISEC
#define RCC_HSE                         RCC_SECCFGR_HSESEC
#define RCC_MSI                         RCC_SECCFGR_MSISEC
#define RCC_LSI                         RCC_SECCFGR_LSISEC
#define RCC_LSE                         RCC_SECCFGR_LSESEC
#define RCC_SYSCLK                      RCC_SECCFGR_SYSCLKSEC
#define RCC_PRESC                       RCC_SECCFGR_PRESCSEC
#define RCC_BOOST                       RCC_SECCFGR_BOOSTSEC
#define RCC_ICLK                        RCC_SECCFGR_ICLKSEC
#define RCC_HSI48                       RCC_SECCFGR_HSI48SEC
#define RCC_RMVF                        RCC_SECCFGR_RMVFSEC
#define RCC_ALL                         (RCC_HSI | RCC_HSE | RCC_MSI | RCC_LSI | RCC_LSE | RCC_SYSCLK | \
                                         RCC_PRESC | RCC_BOOST | RCC_ICLK | RCC_HSI48 | RCC_RMVF)
/**
  * @}
  */

/** @defgroup RCC_attributes RCC attributes
  * @brief RCC privilege/non-privilege and secure/non-secure attributes
  * @{
  */
#define RCC_NSEC_PRIV                   0x00000001U        /*!< Non-secure Privilege attribute item     */
#define RCC_NSEC_NPRIV                  0x00000002U        /*!< Non-secure Non-privilege attribute item */
#define RCC_SEC_PRIV                    0x00000010U        /*!< Secure Privilege attribute item         */
#define RCC_SEC_NPRIV                   0x00000020U        /*!< Secure Non-privilege attribute item     */
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_GPDMA1_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GPDMA1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GPDMA1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_ADF1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_ADF1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_ADF1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(HSP1)
#define __HAL_RCC_HSP1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_HSP1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_HSP1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* HSP1 */

#define __HAL_RCC_FLASH_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_FLASHEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_FLASHEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_CRC_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_CRCEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_CRCEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TSC_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_TSCEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_TSCEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_RAMCFG_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_RAMCFGEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_RAMCFGEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GTZC1_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GTZC1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GTZC1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(SRAM4)
#define __HAL_RCC_SRAM4_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM4EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM4EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* SRAM4 */

#define __HAL_RCC_SRAM1_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_PWR_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB1ENR2, RCC_AHB1ENR2_PWREN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB1ENR2, RCC_AHB1ENR2_PWREN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPDMA1_CLK_DISABLE()            CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GPDMA1EN)
#define __HAL_RCC_ADF1_CLK_DISABLE()              CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_ADF1EN)
#if defined(HSP1)
#define __HAL_RCC_HSP1_CLK_DISABLE()              CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_HSP1EN)
#endif /* HSP1 */
#define __HAL_RCC_FLASH_CLK_DISABLE()             CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_FLASHEN)
#define __HAL_RCC_CRC_CLK_DISABLE()               CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_CRCEN)
#define __HAL_RCC_TSC_CLK_DISABLE()               CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_TSCEN)
#define __HAL_RCC_RAMCFG_CLK_DISABLE()            CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_RAMCFGEN)
#define __HAL_RCC_GTZC1_CLK_DISABLE()             CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GTZC1EN)
#define __HAL_RCC_SRAM1_CLK_DISABLE()             CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM1EN)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_CLK_DISABLE()             CLEAR_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM4EN)
#endif /* SRAM4 */
#define __HAL_RCC_PWR_CLK_DISABLE()               CLEAR_BIT(RCC->AHB1ENR2, RCC_AHB1ENR2_PWREN)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable AHB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_GPIOA_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOAEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOAEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPIOB_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOBEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOBEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPIOC_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOCEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOCEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPIOD_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIODEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIODEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPIOE_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOEEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOEEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(GPIOF)
#define __HAL_RCC_GPIOF_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOFEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOFEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* GPIOF */

#define __HAL_RCC_GPIOG_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOGEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOGEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPIOH_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOHEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOHEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_ADC12_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_ADC12EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_ADC12EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_DAC1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_DAC1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_DAC1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_AES_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_AESEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_AESEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_HASH_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_HASHEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_HASHEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_RNG_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_RNGEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_RNGEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_PKA_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_PKAEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_PKAEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SAES_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SAESEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SAESEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_CCB_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_CCBEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_CCBEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SDMMC1_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SDMMC1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SDMMC1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SRAM2_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(SRAM3)
#define __HAL_RCC_SRAM3_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM3EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM3EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* SRAM3 */

#define __HAL_RCC_OCTOSPI1_CLK_ENABLE()           do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHB2ENR2, RCC_AHB2ENR2_OCTOSPI1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHB2ENR2, RCC_AHB2ENR2_OCTOSPI1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_GPIOA_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOAEN)
#define __HAL_RCC_GPIOB_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOBEN)
#define __HAL_RCC_GPIOC_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOCEN)
#define __HAL_RCC_GPIOD_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIODEN)
#define __HAL_RCC_GPIOE_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOEEN)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOFEN)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOGEN)
#define __HAL_RCC_GPIOH_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOHEN)
#define __HAL_RCC_ADC12_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_ADC12EN)
#define __HAL_RCC_DAC1_CLK_DISABLE()              CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_DAC1EN)
#define __HAL_RCC_AES_CLK_DISABLE()               CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_AESEN)
#define __HAL_RCC_HASH_CLK_DISABLE()              CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_HASHEN)
#define __HAL_RCC_RNG_CLK_DISABLE()               CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_RNGEN)
#define __HAL_RCC_PKA_CLK_DISABLE()               CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_PKAEN)
#define __HAL_RCC_SAES_CLK_DISABLE()              CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SAESEN)
#define __HAL_RCC_CCB_CLK_DISABLE()               CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_CCBEN)
#define __HAL_RCC_SDMMC1_CLK_DISABLE()            CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SDMMC1EN)
#define __HAL_RCC_SRAM2_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM2EN)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_CLK_DISABLE()             CLEAR_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM3EN)
#endif /* SRAM3 */
#define __HAL_RCC_OCTOSPI1_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR2, RCC_AHB2ENR2_OCTOSPI1EN)
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_TIM2_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM3_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM4_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM6_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM7_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SPI3_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI4EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI4EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* SPI4 */


#define __HAL_RCC_WWDG_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SPI2_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(USART2)
#define __HAL_RCC_USART2_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* USART2 */

#define __HAL_RCC_USART3_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_UART4_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_UART5_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_I2C1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_I2C2_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_I3C1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I3C1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I3C1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_CRS_CLK_ENABLE()                do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_OPAMP_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_OPAMPEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_OPAMPEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_VREF_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_VREFEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_VREFEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_RTCAPB_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* I2C4 */

#define __HAL_RCC_LPTIM2_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_FDCAN_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM2_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN)
#define __HAL_RCC_TIM3_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN)
#define __HAL_RCC_TIM4_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN)
#define __HAL_RCC_TIM6_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN)
#define __HAL_RCC_TIM7_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN)
#define __HAL_RCC_SPI3_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN)
#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI4EN)
#endif /* SPI4 */
#define __HAL_RCC_SPI2_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN)
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN)
#endif /* USART2 */
#define __HAL_RCC_USART3_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN)
#define __HAL_RCC_UART4_CLK_DISABLE()             CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN)
#define __HAL_RCC_UART5_CLK_DISABLE()             CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN)
#define __HAL_RCC_I2C1_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN)
#define __HAL_RCC_I2C2_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN)
#define __HAL_RCC_I3C1_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I3C1EN)
#define __HAL_RCC_CRS_CLK_DISABLE()               CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN)
#define __HAL_RCC_OPAMP_CLK_DISABLE()             CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_OPAMPEN)
#define __HAL_RCC_VREF_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_VREFEN)
#define __HAL_RCC_RTCAPB_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_DISABLE()              CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN)
#define __HAL_RCC_FDCAN_CLK_DISABLE()             CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN)
/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_TIM1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SPI1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(TIM8)
#define __HAL_RCC_TIM8_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* TIM8 */

#define __HAL_RCC_USART1_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#if defined(TIM12)
#define __HAL_RCC_TIM12_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM12EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM12EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)
#endif /* TIM12 */

#define __HAL_RCC_TIM15_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM16_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM17_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SAI1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_USB1_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USB1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USB1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_I3C2_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB2ENR, RCC_APB2ENR_I3C2EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_I3C2EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_TIM1_CLK_DISABLE()              CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN)
#define __HAL_RCC_SPI1_CLK_DISABLE()              CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)
#if defined(TIM8)
#define __HAL_RCC_TIM8_CLK_DISABLE()              CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN)
#endif /* TIM8 */
#define __HAL_RCC_USART1_CLK_DISABLE()            CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN)
#if defined(TIM12)
#define __HAL_RCC_TIM12_CLK_DISABLE()             CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM12EN)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_CLK_DISABLE()             CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN)
#define __HAL_RCC_TIM16_CLK_DISABLE()             CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN)
#define __HAL_RCC_TIM17_CLK_DISABLE()             CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN)
#define __HAL_RCC_SAI1_CLK_DISABLE()              CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN)
#define __HAL_RCC_USB1_CLK_DISABLE()              CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USB1EN)
#define __HAL_RCC_I3C2_CLK_DISABLE()              CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_I3C2EN)
/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Enable_Disable APB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_SYSCFG_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_SYSCFGEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_SYSCFGEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_LPUART1_CLK_ENABLE()            do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_LPUART1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPUART1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_I2C3_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_I2C3EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_I2C3EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_LPTIM1_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM1EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM1EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_LPTIM3_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM3EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM3EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_LPTIM4_CLK_ENABLE()             do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM4EN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM4EN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_COMP_CLK_ENABLE()               do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->APB3ENR, RCC_APB3ENR_COMPEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->APB3ENR, RCC_APB3ENR_COMPEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_SYSCFG_CLK_DISABLE()            CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_SYSCFGEN)
#define __HAL_RCC_LPUART1_CLK_DISABLE()           CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_LPUART1EN)
#define __HAL_RCC_I2C3_CLK_DISABLE()              CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_I2C3EN)
#define __HAL_RCC_LPTIM1_CLK_DISABLE()            CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM1EN)
#define __HAL_RCC_LPTIM3_CLK_DISABLE()            CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM3EN)
#define __HAL_RCC_LPTIM4_CLK_DISABLE()            CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM4EN)
#define __HAL_RCC_COMP_CLK_DISABLE()              CLEAR_BIT(RCC->APB3ENR, RCC_APB3ENR_COMPEN)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable_Status AHB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_GPDMA1_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GPDMA1EN) != 0U)
#define __HAL_RCC_ADF1_IS_CLK_ENABLED()           (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_ADF1EN) != 0U)
#if defined(HSP1)
#define __HAL_RCC_HSP1_IS_CLK_ENABLED()           (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_HSP1EN) != 0U)
#endif /* HSP1 */
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_FLASHEN) != 0U)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_CRCEN) != 0U)
#define __HAL_RCC_TSC_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_TSCEN) != 0U)
#define __HAL_RCC_RAMCFG_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_RAMCFGEN) != 0U)
#define __HAL_RCC_GTZC1_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_GTZC1EN) != 0U)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM4EN) != 0U)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB1ENR1, RCC_AHB1ENR1_SRAM1EN) != 0U)
#define __HAL_RCC_PWR_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB1ENR2, RCC_AHB1ENR2_PWREN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable_Status AHB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB2 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOAEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOBEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOCEN) != 0U)
#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIODEN) != 0U)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOEEN) != 0U)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOFEN) != 0U)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOGEN) != 0U)
#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_GPIOHEN) != 0U)
#define __HAL_RCC_ADC12_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_ADC12EN) != 0U)
#define __HAL_RCC_DAC1_IS_CLK_ENABLED()           (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_DAC1EN) != 0U)
#define __HAL_RCC_AES_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_AESEN) != 0U)
#define __HAL_RCC_HASH_IS_CLK_ENABLED()           (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_HASHEN) != 0U)
#define __HAL_RCC_RNG_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_RNGEN) != 0U)
#define __HAL_RCC_PKA_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_PKAEN) != 0U)
#define __HAL_RCC_SAES_IS_CLK_ENABLED()           (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SAESEN) != 0U)
#define __HAL_RCC_CCB_IS_CLK_ENABLED()            (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_CCBEN) != 0U)
#define __HAL_RCC_SDMMC1_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SDMMC1EN) != 0U)
#define __HAL_RCC_SRAM2_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM2EN) != 0U)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_IS_CLK_ENABLED()          (READ_BIT(RCC->AHB2ENR1, RCC_AHB2ENR1_SRAM3EN) != 0U)
#endif /* SRAM3 */
#define __HAL_RCC_OCTOSPI1_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR2, RCC_AHB2ENR2_OCTOSPI1EN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable_Status APB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN) != 0U)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN) != 0U)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN) != 0U)
#define __HAL_RCC_TIM6_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN) != 0U)
#define __HAL_RCC_TIM7_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN) != 0U)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN) != 0U)
#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI4EN) != 0U)
#endif /* SPI4 */
#define __HAL_RCC_WWDG_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN) != 0U)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN) != 0U)
#if defined(USART2)
#define __HAL_RCC_USART2_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN) != 0U)
#endif /* USART2 */
#define __HAL_RCC_USART3_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN) != 0U)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()          (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN) != 0U)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()          (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN) != 0U)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN) != 0U)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN) != 0U)
#define __HAL_RCC_I3C1_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I3C1EN) != 0U)
#define __HAL_RCC_CRS_IS_CLK_ENABLED()            (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN) != 0U)
#define __HAL_RCC_OPAMP_IS_CLK_ENABLED()          (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_OPAMPEN) != 0U)
#define __HAL_RCC_VREF_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_VREFEN) != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN) != 0U)
#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_ENABLED()           (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN) != 0U)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN) != 0U)
#define __HAL_RCC_FDCAN_IS_CLK_ENABLED()          (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Disable_Status APB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()           (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN) != 0U)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()           (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN) != 0U)
#if defined(TIM8)
#define __HAL_RCC_TIM8_IS_CLK_ENABLED()           (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN) != 0U)
#endif /* TIM8 */
#define __HAL_RCC_USART1_IS_CLK_ENABLED()         (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN) != 0U)
#if defined(TIM12)
#define __HAL_RCC_TIM12_IS_CLK_ENABLED()          (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM12EN) != 0U)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_IS_CLK_ENABLED()          (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN) != 0U)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()          (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN) != 0U)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()          (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN) != 0U)
#define __HAL_RCC_SAI1_IS_CLK_ENABLED()           (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN) != 0U)
#define __HAL_RCC_USB1_IS_CLK_ENABLED()           (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USB1EN) != 0U)
#define __HAL_RCC_I3C2_IS_CLK_ENABLED()           (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_I3C2EN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Enable_Disable_Status APB3 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB3 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()         (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_SYSCFGEN) != 0U)
#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPUART1EN) != 0U)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()           (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_I2C3EN) != 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()         (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM1EN) != 0U)
#define __HAL_RCC_LPTIM3_IS_CLK_ENABLED()         (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM3EN) != 0U)
#define __HAL_RCC_LPTIM4_IS_CLK_ENABLED()         (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_LPTIM4EN) != 0U)
#define __HAL_RCC_COMP_IS_CLK_ENABLED()           (READ_BIT(RCC->APB3ENR, RCC_APB3ENR_COMPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Force_Release_Reset AHB1 Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB1_FORCE_RESET()              WRITE_REG(RCC->AHB1RSTR1, 0xFFFFFFFFU)
#define __HAL_RCC_GPDMA1_FORCE_RESET()            SET_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_GPDMA1RST)
#define __HAL_RCC_ADF1_FORCE_RESET()              SET_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_ADF1RST)
#if defined(TIM12)
#define __HAL_RCC_HSP1_FORCE_RESET()              SET_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_HSP1RST)
#endif /* TIM12 */
#define __HAL_RCC_CRC_FORCE_RESET()               SET_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_CRCRST)
#define __HAL_RCC_TSC_FORCE_RESET()               SET_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_TSCRST)
#define __HAL_RCC_RAMCFG_FORCE_RESET()            SET_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_RAMCFGRST)

#define __HAL_RCC_AHB1_RELEASE_RESET()            WRITE_REG(RCC->AHB1RSTR1, 0x00000000U)
#define __HAL_RCC_GPDMA1_RELEASE_RESET()          CLEAR_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_GPDMA1RST)
#define __HAL_RCC_ADF1_RELEASE_RESET()            CLEAR_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_ADF1RST)
#if defined(TIM12)
#define __HAL_RCC_HSP1_RELEASE_RESET()            CLEAR_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_HSP1RST)
#endif /* TIM12 */
#define __HAL_RCC_CRC_RELEASE_RESET()             CLEAR_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_CRCRST)
#define __HAL_RCC_TSC_RELEASE_RESET()             CLEAR_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_TSCRST)
#define __HAL_RCC_RAMCFG_RELEASE_RESET()          CLEAR_BIT(RCC->AHB1RSTR1, RCC_AHB1RSTR1_RAMCFGRST)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Force_Release_Reset AHB2 Peripheral Force Release Reset
  * @brief  Force or release AHB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB2_FORCE_RESET()              do { \
                                                       WRITE_REG(RCC->AHB2RSTR1, 0xFFFFFFFFU); \
                                                       WRITE_REG(RCC->AHB2RSTR2, 0xFFFFFFFFU); \
                                                     } while(0)
#define __HAL_RCC_GPIOA_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOARST)
#define __HAL_RCC_GPIOB_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOBRST)
#define __HAL_RCC_GPIOC_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOCRST)
#define __HAL_RCC_GPIOD_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIODRST)
#define __HAL_RCC_GPIOE_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOERST)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOFRST)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOGRST)
#define __HAL_RCC_GPIOH_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOHRST)
#define __HAL_RCC_ADC12_FORCE_RESET()             SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_ADC12RST)
#define __HAL_RCC_DAC1_FORCE_RESET()              SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_DAC1RST)
#define __HAL_RCC_AES_FORCE_RESET()               SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_AESRST)
#define __HAL_RCC_HASH_FORCE_RESET()              SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_HASHRST)
#define __HAL_RCC_RNG_FORCE_RESET()               SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_RNGRST)
#define __HAL_RCC_PKA_FORCE_RESET()               SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_PKARST)
#define __HAL_RCC_SAES_FORCE_RESET()              SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_SAESRST)
#define __HAL_RCC_CCB_FORCE_RESET()               SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_CCBRST)
#define __HAL_RCC_SDMMC1_FORCE_RESET()            SET_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_SDMMC1RST)
#define __HAL_RCC_OCTOSPI1_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR2, RCC_AHB2RSTR2_OCTOSPI1RST)

#define __HAL_RCC_AHB2_RELEASE_RESET()            do { \
                                                       WRITE_REG(RCC->AHB2RSTR1, 0x00000000U); \
                                                       WRITE_REG(RCC->AHB2RSTR2, 0x00000000U); \
                                                     } while(0)
#define __HAL_RCC_GPIOA_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOARST)
#define __HAL_RCC_GPIOB_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOBRST)
#define __HAL_RCC_GPIOC_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOCRST)
#define __HAL_RCC_GPIOD_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIODRST)
#define __HAL_RCC_GPIOE_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOERST)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOFRST)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOGRST)
#define __HAL_RCC_GPIOH_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_GPIOHRST)
#define __HAL_RCC_ADC12_RELEASE_RESET()           CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_ADC12RST)
#define __HAL_RCC_DAC1_RELEASE_RESET()            CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_DAC1RST)
#define __HAL_RCC_AES_RELEASE_RESET()             CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_AESRST)
#define __HAL_RCC_HASH_RELEASE_RESET()            CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_HASHRST)
#define __HAL_RCC_RNG_RELEASE_RESET()             CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_RNGRST)
#define __HAL_RCC_PKA_RELEASE_RESET()             CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_PKARST)
#define __HAL_RCC_SAES_RELEASE_RESET()            CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_SAESRST)
#define __HAL_RCC_CCB_RELEASE_RESET()             CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_CCBRST)
#define __HAL_RCC_SDMMC1_RELEASE_RESET()          CLEAR_BIT(RCC->AHB2RSTR1, RCC_AHB2RSTR1_SDMMC1RST)
#define __HAL_RCC_OCTOSPI1_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR2, RCC_AHB2RSTR2_OCTOSPI1RST)
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_FORCE_RESET()              do { \
                                                       WRITE_REG(RCC->APB1RSTR1, 0xFFFFFFFFU); \
                                                       WRITE_REG(RCC->APB1RSTR2, 0xFFFFFFFFU); \
                                                     } while(0)
#define __HAL_RCC_TIM2_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)
#define __HAL_RCC_TIM3_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)
#define __HAL_RCC_TIM4_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM4RST)
#define __HAL_RCC_TIM6_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM6RST)
#define __HAL_RCC_TIM7_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM7RST)
#define __HAL_RCC_SPI3_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI3RST)
#if defined(SPI4)
#define __HAL_RCC_SPI4_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI4RST)
#endif /* SPI4 */
#define __HAL_RCC_SPI2_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI2RST)
#if defined(USART2)
#define __HAL_RCC_USART2_FORCE_RESET()            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)
#endif /* USART2 */
#define __HAL_RCC_USART3_FORCE_RESET()            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST)
#define __HAL_RCC_UART4_FORCE_RESET()             SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST)
#define __HAL_RCC_UART5_FORCE_RESET()             SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST)
#define __HAL_RCC_I2C1_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST)
#define __HAL_RCC_I2C2_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST)
#define __HAL_RCC_I3C1_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I3C1RST)
#define __HAL_RCC_CRS_FORCE_RESET()               SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_CRSRST)
#define __HAL_RCC_OPAMP_FORCE_RESET()             SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_OPAMPRST)
#define __HAL_RCC_VREF_FORCE_RESET()              SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_VREFRST)
#if defined(I2C4)
#define __HAL_RCC_I2C4_FORCE_RESET()              SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_I2C4RST)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_FORCE_RESET()            SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_LPTIM2RST)
#define __HAL_RCC_FDCAN_FORCE_RESET()             SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_FDCANRST)
#define __HAL_RCC_APB1_RELEASE_RESET()            do { \
                                                       WRITE_REG(RCC->APB1RSTR1, 0x00000000U); \
                                                       WRITE_REG(RCC->APB1RSTR2, 0x00000000U); \
                                                     } while(0)
#define __HAL_RCC_TIM2_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)
#define __HAL_RCC_TIM3_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)
#define __HAL_RCC_TIM4_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM4RST)
#define __HAL_RCC_TIM6_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM6RST)
#define __HAL_RCC_TIM7_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM7RST)
#define __HAL_RCC_SPI3_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI3RST)
#if defined(SPI4)
#define __HAL_RCC_SPI4_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI4RST)
#endif /* SPI4 */
#define __HAL_RCC_SPI2_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI2RST)
#if defined(USART2)
#define __HAL_RCC_USART2_RELEASE_RESET()          CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)
#endif /* USART2 */
#define __HAL_RCC_USART3_RELEASE_RESET()          CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST)
#define __HAL_RCC_UART4_RELEASE_RESET()           CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST)
#define __HAL_RCC_UART5_RELEASE_RESET()           CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST)
#define __HAL_RCC_I2C1_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST)
#define __HAL_RCC_I2C2_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST)
#define __HAL_RCC_I3C1_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I3C1RST)
#define __HAL_RCC_CRS_RELEASE_RESET()             CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_CRSRST)
#define __HAL_RCC_OPAMP_RELEASE_RESET()           CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_OPAMPRST)
#define __HAL_RCC_VREF_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_VREFRST)
#if defined(I2C4)
#define __HAL_RCC_I2C4_RELEASE_RESET()            CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_I2C4RST)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_RELEASE_RESET()          CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_LPTIM2RST)
#define __HAL_RCC_FDCAN_RELEASE_RESET()           CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_FDCANRST)
/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()              WRITE_REG(RCC->APB2RSTR, 0xFFFFFFFFU)
#define __HAL_RCC_TIM1_FORCE_RESET()              SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)
#define __HAL_RCC_SPI1_FORCE_RESET()              SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)
#if defined(TIM8)
#define __HAL_RCC_TIM8_FORCE_RESET()             SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM8RST)
#endif /* TIM8 */
#define __HAL_RCC_USART1_FORCE_RESET()            SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)
#if defined(TIM12)
#define __HAL_RCC_TIM12_FORCE_RESET()             SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM12RST)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_FORCE_RESET()             SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST)
#define __HAL_RCC_TIM16_FORCE_RESET()             SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)
#define __HAL_RCC_TIM17_FORCE_RESET()             SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)
#define __HAL_RCC_SAI1_FORCE_RESET()              SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)
#define __HAL_RCC_USB1_FORCE_RESET()              SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USB1RST)
#define __HAL_RCC_I3C2_FORCE_RESET()              SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_I3C2RST)

#define __HAL_RCC_APB2_RELEASE_RESET()            WRITE_REG(RCC->APB2RSTR, 0x00000000U)
#define __HAL_RCC_TIM1_RELEASE_RESET()            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)
#define __HAL_RCC_SPI1_RELEASE_RESET()            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)
#if defined(TIM8)
#define __HAL_RCC_TIM8_RELEASE_RESET()            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM8RST)
#endif /* TIM8 */
#define __HAL_RCC_USART1_RELEASE_RESET()          CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)
#if defined(TIM12)
#define __HAL_RCC_TIM12_RELEASE_RESET()           CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM12RST)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_RELEASE_RESET()           CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST)
#define __HAL_RCC_TIM16_RELEASE_RESET()           CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)
#define __HAL_RCC_TIM17_RELEASE_RESET()           CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)
#define __HAL_RCC_SAI1_RELEASE_RESET()            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)
#define __HAL_RCC_USB1_RELEASE_RESET()            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USB1RST)
#define __HAL_RCC_I3C2_RELEASE_RESET()            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_I3C2RST)
/**
  * @}
  */

/** @defgroup RCC_APB3_Force_Release_Reset APB3 Peripheral Force Release Reset
  * @brief  Force or release APB3 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB3_FORCE_RESET()              WRITE_REG(RCC->APB3RSTR, 0xFFFFFFFFU)
#define __HAL_RCC_SYSCFG_FORCE_RESET()            SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_SYSCFGRST)
#define __HAL_RCC_LPUART1_FORCE_RESET()           SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPUART1RST)
#define __HAL_RCC_I2C3_FORCE_RESET()              SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_I2C3RST)
#define __HAL_RCC_LPTIM1_FORCE_RESET()            SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPTIM1RST)
#define __HAL_RCC_LPTIM3_FORCE_RESET()            SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPTIM3RST)
#define __HAL_RCC_LPTIM4_FORCE_RESET()            SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPTIM4RST)
#define __HAL_RCC_COMP_FORCE_RESET()              SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_COMPRST)

#define __HAL_RCC_APB3_RELEASE_RESET()            WRITE_REG(RCC->APB3RSTR, 0x00000000U)
#define __HAL_RCC_SYSCFG_RELEASE_RESET()          CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_SYSCFGRST)
#define __HAL_RCC_LPUART1_RELEASE_RESET()         CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPUART1RST)
#define __HAL_RCC_I2C3_RELEASE_RESET()            CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_I2C3RST)
#define __HAL_RCC_LPTIM1_RELEASE_RESET()          CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPTIM1RST)
#define __HAL_RCC_LPTIM3_RELEASE_RESET()          CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPTIM3RST)
#define __HAL_RCC_LPTIM4_RELEASE_RESET()          CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_LPTIM4RST)
#define __HAL_RCC_COMP_RELEASE_RESET()            CLEAR_BIT(RCC->APB3RSTR, RCC_APB3RSTR_COMPRST)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enable_Disable AHB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Sleep mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_GPDMA1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_GPDMA1SLPEN)
#define __HAL_RCC_ADF1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_ADF1SLPEN)
#if defined(HSP1)
#define __HAL_RCC_HSP1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_HSP1SLPEN)
#endif /* HSP1 */
#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_FLASHSLPEN)
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_CRCSLPEN)
#define __HAL_RCC_TSC_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_TSCSLPEN)
#define __HAL_RCC_RAMCFG_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_RAMCFGSLPEN)
#define __HAL_RCC_GTZC1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_GTZC1SLPEN)
#define __HAL_RCC_ICACHE_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_ICACHESLPEN)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_SRAM4SLPEN)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_SRAM1SLPEN)
#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB1SLPENR2, RCC_AHB1SLPENR2_PWRSLPEN)

#define __HAL_RCC_GPDMA1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_GPDMA1SLPEN)
#define __HAL_RCC_ADF1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_ADF1SLPEN)
#if defined(HSP1)
#define __HAL_RCC_HSP1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_HSP1SLPEN)
#endif /* HSP1 */
#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_FLASHSLPEN)
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_CRCSLPEN)
#define __HAL_RCC_TSC_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_TSCSLPEN)
#define __HAL_RCC_RAMCFG_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_RAMCFGSLPEN)
#define __HAL_RCC_GTZC1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_GTZC1SLPEN)
#define __HAL_RCC_ICACHE_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_ICACHESLPEN)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_SRAM4SLPEN)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_SRAM1SLPEN)
#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB1SLPENR2, RCC_AHB1SLPENR2_PWRSLPEN)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enable_Disable AHB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Sleep mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOASLPEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOBSLPEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOCSLPEN)
#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIODSLPEN)
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOESLPEN)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOFSLPEN)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOGSLPEN)
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOHSLPEN)
#define __HAL_RCC_ADC12_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_ADC12SLPEN)
#define __HAL_RCC_DAC1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_DAC1SLPEN)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_AESSLPEN)
#define __HAL_RCC_HASH_CLK_SLEEP_ENABLE()         SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_HASHSLPEN)
#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_RNGSLPEN)
#define __HAL_RCC_PKA_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_PKASLPEN)
#define __HAL_RCC_SAES_CLK_SLEEP_ENABLE()         SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SAESSLPEN)
#define __HAL_RCC_CCB_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_CCBSLPEN)
#define __HAL_RCC_SDMMC1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SDMMC1SLPEN)
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SRAM2SLPEN)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_CLK_SLEEP_ENABLE()        SET_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SRAM3SLPEN)
#endif /* SRAM3 */
#define __HAL_RCC_OCTOSPI1_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SLPENR2, RCC_AHB2SLPENR2_OCTOSPI1SLPEN)

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOASLPEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOBSLPEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOCSLPEN)
#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIODSLPEN)
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOESLPEN)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOFSLPEN)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOGSLPEN)
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOHSLPEN)
#define __HAL_RCC_ADC12_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_ADC12SLPEN)
#define __HAL_RCC_DAC1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_DAC1SLPEN)
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_AESSLPEN)
#define __HAL_RCC_HASH_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_HASHSLPEN)
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_RNGSLPEN)
#define __HAL_RCC_PKA_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_PKASLPEN)
#define __HAL_RCC_SAES_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SAESSLPEN)
#define __HAL_RCC_CCB_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_CCBSLPEN)
#define __HAL_RCC_SDMMC1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SDMMC1SLPEN)
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SRAM2SLPEN)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SRAM3SLPEN)
#endif /* SRAM3 */
#define __HAL_RCC_OCTOSPI1_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SLPENR2, RCC_AHB2SLPENR2_OCTOSPI1SLPEN)
/**
  * @}
  */
/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Sleep mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM2SLPEN)
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM3SLPEN)
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM4SLPEN)
#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM6SLPEN)
#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM7SLPEN)
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI3SLPEN)
#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI4SLPEN)
#endif /* SPI4 */
#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_WWDGSLPEN)
#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI2SLPEN)
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_USART2SLPEN)
#endif /* USART2 */
#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_USART3SLPEN)
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_UART4SLPEN)
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_UART5SLPEN)
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I2C1SLPEN)
#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I2C2SLPEN)
#define __HAL_RCC_I3C1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I3C1SLPEN)
#define __HAL_RCC_CRS_CLK_SLEEP_ENABLE()          SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_CRSSLPEN)
#define __HAL_RCC_OPAMP_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_OPAMPSLPEN)
#define __HAL_RCC_VREF_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_VREFSLPEN)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_RTCAPBSLPEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_I2C4SLPEN)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_LPTIM2SLPEN)
#define __HAL_RCC_FDCAN_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_FDCANSLPEN)

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM2SLPEN)
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM3SLPEN)
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM4SLPEN)
#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM6SLPEN)
#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM7SLPEN)
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI3SLPEN)
#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI4SLPEN)
#endif /* SPI4 */
#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_WWDGSLPEN)
#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI2SLPEN)
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_USART2SLPEN)
#endif /* USART2 */
#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_USART3SLPEN)
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_UART4SLPEN)
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_UART5SLPEN)
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I2C1SLPEN)
#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I2C2SLPEN)
#define __HAL_RCC_I3C1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I3C1SLPEN)
#define __HAL_RCC_CRS_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_CRSSLPEN)
#define __HAL_RCC_OPAMP_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_OPAMPSLPEN)
#define __HAL_RCC_VREF_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_VREFSLPEN)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_RTCAPBSLPEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_I2C4SLPEN)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_LPTIM2SLPEN)
#define __HAL_RCC_FDCAN_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_FDCANSLPEN)
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Sleep_Enable_Disable APB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Sleep mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM1SLPEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_SPI1SLPEN)
#if defined(TIM8)
#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM8SLPEN)
#endif /* TIM8 */
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_USART1SLPEN)
#if defined(TIM12)
#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM12SLPEN)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM15SLPEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM16SLPEN)
#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM17SLPEN)
#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_SAI1SLPEN)
#define __HAL_RCC_USB1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_USB1SLPEN)
#define __HAL_RCC_I3C2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_I3C2SLPEN)

#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM1SLPEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_SPI1SLPEN)
#if defined(TIM8)
#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM8SLPEN)
#endif /* TIM8 */
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_USART1SLPEN)
#if defined(TIM12)
#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM12SLPEN)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM15SLPEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM16SLPEN)
#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM17SLPEN)
#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_SAI1SLPEN)
#define __HAL_RCC_USB1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_USB1SLPEN)
#define __HAL_RCC_I3C2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_I3C2SLPEN)
/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Sleep_Enable_Disable APB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock during Sleep mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_SYSCFGSLPEN)
#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPUART1SLPEN)
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_I2C3SLPEN)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM1SLPEN)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM3SLPEN)
#define __HAL_RCC_LPTIM4_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM4SLPEN)
#define __HAL_RCC_COMP_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_COMPSLPEN)

#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_SYSCFGSLPEN)
#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPUART1SLPEN)
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_I2C3SLPEN)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM1SLPEN)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM3SLPEN)
#define __HAL_RCC_LPTIM4_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM4SLPEN)
#define __HAL_RCC_COMP_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_COMPSLPEN)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enabled_Status AHB1 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the AHB1 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_GPDMA1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_GPDMA1SLPEN) != 0U)
#define __HAL_RCC_ADF1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_ADF1SLPEN) != 0U)
#if defined(HSP1)
#define __HAL_RCC_HSP1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_HSP1SLPEN) != 0U)
#endif /* HSP1 */
#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_FLASHSLPEN) != 0U)
#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_CRCSLPEN) != 0U)
#define __HAL_RCC_TSC_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_TSCSLPEN) != 0U)
#define __HAL_RCC_RAMCFG_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_RAMCFGSLPEN) != 0U)
#define __HAL_RCC_GTZC1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_GTZC1SLPEN) != 0U)
#define __HAL_RCC_ICACHE_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_ICACHESLPEN) != 0U)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_SRAM4SLPEN) != 0U)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SLPENR1, RCC_AHB1SLPENR1_SRAM1SLPEN) != 0U)
#define __HAL_RCC_PWR_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB1SLPENR2, RCC_AHB1SLPENR2_PWRSLPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enabled_Status AHB2 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the AHB2 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOASLPEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOBSLPEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOCSLPEN) != 0U)
#define __HAL_RCC_GPIOD_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIODSLPEN) != 0U)
#define __HAL_RCC_GPIOE_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOESLPEN) != 0U)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOFSLPEN) != 0U)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOGSLPEN) != 0U)
#define __HAL_RCC_GPIOH_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_GPIOHSLPEN) != 0U)
#define __HAL_RCC_ADC12_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_ADC12SLPEN) != 0U)
#define __HAL_RCC_DAC1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_DAC1SLPEN) != 0U)
#define __HAL_RCC_AES_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_AESSLPEN) != 0U)
#define __HAL_RCC_HASH_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_HASHSLPEN) != 0U)
#define __HAL_RCC_RNG_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_RNGSLPEN) != 0U)
#define __HAL_RCC_PKA_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_PKASLPEN) != 0U)
#define __HAL_RCC_SAES_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SAESSLPEN) != 0U)
#define __HAL_RCC_CCB_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_CCBSLPEN) != 0U)
#define __HAL_RCC_SDMMC1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SDMMC1SLPEN) != 0U)
#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SRAM2SLPEN) != 0U)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SLPENR1, RCC_AHB2SLPENR1_SRAM3SLPEN) != 0U)
#endif /* SRAM3 */
#define __HAL_RCC_OCTOSPI1_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB2SLPENR2, RCC_AHB2SLPENR2_OCTOSPI1SLPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enabled_Status APB1 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the APB1 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM2SLPEN) != 0U)
#define __HAL_RCC_TIM3_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM3SLPEN) != 0U)
#define __HAL_RCC_TIM4_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM4SLPEN) != 0U)
#define __HAL_RCC_TIM6_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM6SLPEN) != 0U)
#define __HAL_RCC_TIM7_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_TIM7SLPEN) != 0U)
#define __HAL_RCC_SPI3_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI3SLPEN) != 0U)
#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI4SLPEN) != 0U)
#endif /* SPI4 */
#define __HAL_RCC_WWDG_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_WWDGSLPEN) != 0U)
#define __HAL_RCC_SPI2_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_SPI2SLPEN) != 0U)
#if defined(USART2)
#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_USART2SLPEN) != 0U)
#endif /* USART2 */
#define __HAL_RCC_USART3_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_USART3SLPEN) != 0U)
#define __HAL_RCC_UART4_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_UART4SLPEN) != 0U)
#define __HAL_RCC_UART5_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_UART5SLPEN) != 0U)
#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I2C1SLPEN) != 0U)
#define __HAL_RCC_I2C2_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I2C2SLPEN) != 0U)
#define __HAL_RCC_I3C1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_I3C1SLPEN) != 0U)
#define __HAL_RCC_CRS_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_CRSSLPEN) != 0U)
#define __HAL_RCC_OPAMP_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_OPAMPSLPEN) != 0U)
#define __HAL_RCC_VREF_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_VREFSLPEN) != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1SLPENR1, RCC_APB1SLPENR1_RTCAPBSLPEN) != 0U)
#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_I2C4SLPEN) != 0U)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_LPTIM2SLPEN) != 0U)
#define __HAL_RCC_FDCAN_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SLPENR2, RCC_APB1SLPENR2_FDCANSLPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Sleep_Enabled_Status APB2 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the APB2 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @{
  */
#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM1SLPEN) != 0U)
#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_SPI1SLPEN) != 0U)
#if defined(TIM8)
#define __HAL_RCC_TIM8_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM8SLPEN) != 0U)
#endif /* TIM8 */
#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_USART1SLPEN) != 0U)
#if defined(TIM12)
#define __HAL_RCC_TIM12_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM12SLPEN) != 0U)
#endif /* TIM12 */
#define __HAL_RCC_TIM15_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM15SLPEN) != 0U)
#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM16SLPEN) != 0U)
#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_TIM17SLPEN) != 0U)
#define __HAL_RCC_SAI1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_SAI1SLPEN) != 0U)
#define __HAL_RCC_USB1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_USB1SLPEN) != 0U)
#define __HAL_RCC_I3C2_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SLPENR, RCC_APB2SLPENR_I3C2SLPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Sleep_Enabled_Status APB3 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the APB3 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_SYSCFGSLPEN) != 0U)
#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPUART1SLPEN) != 0U)
#define __HAL_RCC_I2C3_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_I2C3SLPEN) != 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM1SLPEN) != 0U)
#define __HAL_RCC_LPTIM3_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM3SLPEN) != 0U)
#define __HAL_RCC_LPTIM4_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_LPTIM4SLPEN) != 0U)
#define __HAL_RCC_COMP_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB3SLPENR, RCC_APB3SLPENR_COMPSLPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Stop_Enable_Disable AHB1 Peripheral Clock Stop Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Stop mode.
  * @note   Peripheral clock gating in STOP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during STOP mode.
  * @{
  */
#define __HAL_RCC_GPDMA1_CLK_STOP_ENABLE()        SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_GPDMA1STPEN)
#define __HAL_RCC_ADF1_CLK_STOP_ENABLE()          SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_ADF1STPEN)
#define __HAL_RCC_FLASH_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_FLASHSTPEN)
#define __HAL_RCC_RAMCFG_CLK_STOP_ENABLE()        SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_RAMCFGSTPEN)
#define __HAL_RCC_GTZC1_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_GTZC1STPEN)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_SRAM4STPEN)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_SRAM1STPEN)

#define __HAL_RCC_GPDMA1_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_GPDMA1STPEN)
#define __HAL_RCC_ADF1_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_ADF1STPEN)
#define __HAL_RCC_FLASH_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_FLASHSTPEN)
#define __HAL_RCC_RAMCFG_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_RAMCFGSTPEN)
#define __HAL_RCC_GTZC1_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_GTZC1STPEN)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_SRAM4STPEN)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_SRAM1STPEN)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Stop_Enable_Disable AHB2 Peripheral Clock Stop Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Stop mode.
  * @note   Peripheral clock gating in STOP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during STOP mode.
  * @{
  */
#define __HAL_RCC_GPIOA_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOASTPEN)
#define __HAL_RCC_GPIOB_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOBSTPEN)
#define __HAL_RCC_GPIOC_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOCSTPEN)
#define __HAL_RCC_GPIOD_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIODSTPEN)
#define __HAL_RCC_GPIOE_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOESTPEN)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOFSTPEN)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOGSTPEN)
#define __HAL_RCC_GPIOH_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOHSTPEN)
#define __HAL_RCC_DAC1_CLK_STOP_ENABLE()          SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_DAC1STPEN)
#define __HAL_RCC_SRAM2_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_SRAM2STPEN)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_CLK_STOP_ENABLE()         SET_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_SRAM3STPEN)
#endif /* SRAM3 */

#define __HAL_RCC_GPIOA_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOASTPEN)
#define __HAL_RCC_GPIOB_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOBSTPEN)
#define __HAL_RCC_GPIOC_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOCSTPEN)
#define __HAL_RCC_GPIOD_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIODSTPEN)
#define __HAL_RCC_GPIOE_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOESTPEN)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOFSTPEN)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOGSTPEN)
#define __HAL_RCC_GPIOH_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOHSTPEN)
#define __HAL_RCC_DAC1_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_DAC1STPEN)
#define __HAL_RCC_SRAM2_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_SRAM2STPEN)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_SRAM3STPEN)
#endif /* SRAM3 */
/**
  * @}
  */
/** @defgroup RCC_APB1_Peripheral_Clock_Stop_Enable_Disable APB1 Peripheral Clock Stop Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Stop mode.
  * @note   Peripheral clock gating in STOP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during STOP mode.
  * @{
  */
#define __HAL_RCC_SPI3_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI3STPEN)
#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI4STPEN)
#endif /* SPI4 */
#define __HAL_RCC_SPI2_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI2STPEN)
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_STOP_ENABLE()        SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_USART2STPEN)
#endif /* USART2 */
#define __HAL_RCC_USART3_CLK_STOP_ENABLE()        SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_USART3STPEN)
#define __HAL_RCC_UART4_CLK_STOP_ENABLE()         SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_UART4STPEN)
#define __HAL_RCC_UART5_CLK_STOP_ENABLE()         SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_UART5STPEN)
#define __HAL_RCC_I2C1_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I2C1STPEN)
#define __HAL_RCC_I2C2_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I2C2STPEN)
#define __HAL_RCC_I3C1_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I3C1STPEN)
#define __HAL_RCC_OPAMP_CLK_STOP_ENABLE()         SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_OPAMPSTPEN)
#define __HAL_RCC_VREF_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_VREFSTPEN)
#define __HAL_RCC_RTCAPB_CLK_STOP_ENABLE()        SET_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_RTCAPBSTPEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_STOP_ENABLE()          SET_BIT(RCC->APB1STPENR2, RCC_APB1STPENR2_I2C4STPEN)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_CLK_STOP_ENABLE()        SET_BIT(RCC->APB1STPENR2, RCC_APB1STPENR2_LPTIM2STPEN)

#define __HAL_RCC_SPI3_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI3STPEN)
#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI4STPEN)
#endif /* SPI4 */
#define __HAL_RCC_SPI2_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI2STPEN)
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_USART2STPEN)
#endif /* USART2 */
#define __HAL_RCC_USART3_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_USART3STPEN)
#define __HAL_RCC_UART4_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_UART4STPEN)
#define __HAL_RCC_UART5_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_UART5STPEN)
#define __HAL_RCC_I2C1_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I2C1STPEN)
#define __HAL_RCC_I2C2_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I2C2STPEN)
#define __HAL_RCC_I3C1_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I3C1STPEN)
#define __HAL_RCC_OPAMP_CLK_STOP_DISABLE()        CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_OPAMPSTPEN)
#define __HAL_RCC_VREF_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_VREFSTPEN)
#define __HAL_RCC_RTCAPB_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_RTCAPBSTPEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB1STPENR2, RCC_APB1STPENR2_I2C4STPEN)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB1STPENR2, RCC_APB1STPENR2_LPTIM2STPEN)
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Stop_Enable_Disable APB2 Peripheral Clock Stop Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Stop mode.
  * @note   Peripheral clock gating in STOP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during STOP mode.
  * @{
  */
#define __HAL_RCC_SPI1_CLK_STOP_ENABLE()          SET_BIT(RCC->APB2STPENR, RCC_APB2STPENR_SPI1STPEN)
#define __HAL_RCC_USART1_CLK_STOP_ENABLE()        SET_BIT(RCC->APB2STPENR, RCC_APB2STPENR_USART1STPEN)
#define __HAL_RCC_USB1_CLK_STOP_ENABLE()          SET_BIT(RCC->APB2STPENR, RCC_APB2STPENR_USB1STPEN)
#define __HAL_RCC_I3C2_CLK_STOP_ENABLE()          SET_BIT(RCC->APB2STPENR, RCC_APB2STPENR_I3C2STPEN)

#define __HAL_RCC_SPI1_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB2STPENR, RCC_APB2STPENR_SPI1STPEN)
#define __HAL_RCC_USART1_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB2STPENR, RCC_APB2STPENR_USART1STPEN)
#define __HAL_RCC_USB1_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB2STPENR, RCC_APB2STPENR_USB1STPEN)
#define __HAL_RCC_I3C2_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB2STPENR, RCC_APB2STPENR_I3C2STPEN)
/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Stop_Enable_Disable APB3 Peripheral Clock Stop Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock during Stop mode.
  * @note   Peripheral clock gating in STOP mode can be used to further reduce
  *         power consumption.
  * @note   By default, all peripheral clocks are enabled during STOP mode.
  * @{
  */
#define __HAL_RCC_LPUART1_CLK_STOP_ENABLE()       SET_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPUART1STPEN)
#define __HAL_RCC_I2C3_CLK_STOP_ENABLE()          SET_BIT(RCC->APB3STPENR, RCC_APB3STPENR_I2C3STPEN)
#define __HAL_RCC_LPTIM1_CLK_STOP_ENABLE()        SET_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM1STPEN)
#define __HAL_RCC_LPTIM3_CLK_STOP_ENABLE()        SET_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM3STPEN)
#define __HAL_RCC_LPTIM4_CLK_STOP_ENABLE()        SET_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM4STPEN)
#define __HAL_RCC_COMP_CLK_STOP_ENABLE()          SET_BIT(RCC->APB3STPENR, RCC_APB3STPENR_COMPSTPEN)

#define __HAL_RCC_LPUART1_CLK_STOP_DISABLE()      CLEAR_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPUART1STPEN)
#define __HAL_RCC_I2C3_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB3STPENR, RCC_APB3STPENR_I2C3STPEN)
#define __HAL_RCC_LPTIM1_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM1STPEN)
#define __HAL_RCC_LPTIM3_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM3STPEN)
#define __HAL_RCC_LPTIM4_CLK_STOP_DISABLE()       CLEAR_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM4STPEN)
#define __HAL_RCC_COMP_CLK_STOP_DISABLE()         CLEAR_BIT(RCC->APB3STPENR, RCC_APB3STPENR_COMPSTPEN)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Stop_Enabled_Status AHB1 Peripheral Clock Stop Enabled Status
  * @brief  Check whether the AHB1 peripheral clock during Low Power (Stop) is enabled or not.
  * @{
  */
#define __HAL_RCC_GPDMA1_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_GPDMA1STPEN) != 0U)
#define __HAL_RCC_ADF1_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_ADF1STPEN) != 0U)
#define __HAL_RCC_FLASH_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_FLASHSTPEN) != 0U)
#define __HAL_RCC_RAMCFG_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_RAMCFGSTPEN) != 0U)
#define __HAL_RCC_GTZC1_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_GTZC1STPEN) != 0U)
#if defined(SRAM4)
#define __HAL_RCC_SRAM4_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_SRAM4STPEN) != 0U)
#endif /* SRAM4 */
#define __HAL_RCC_SRAM1_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB1STPENR1, RCC_AHB1STPENR1_SRAM1STPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Stop_Enabled_Status AHB2 Peripheral Clock Stop Enabled Status
  * @brief  Check whether the AHB2 peripheral clock during Low Power (Stop) is enabled or not.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOASTPEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOBSTPEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOCSTPEN) != 0U)
#define __HAL_RCC_GPIOD_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIODSTPEN) != 0U)
#define __HAL_RCC_GPIOE_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOESTPEN) != 0U)
#if defined(GPIOF)
#define __HAL_RCC_GPIOF_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOFSTPEN) != 0U)
#endif /* GPIOF */
#define __HAL_RCC_GPIOG_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOGSTPEN) != 0U)
#define __HAL_RCC_GPIOH_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_GPIOHSTPEN) != 0U)
#define __HAL_RCC_DAC1_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_DAC1STPEN) != 0U)
#define __HAL_RCC_SRAM2_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_SRAM2STPEN) != 0U)
#if defined(SRAM3)
#define __HAL_RCC_SRAM3_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->AHB2STPENR1, RCC_AHB2STPENR1_SRAM3STPEN) != 0U)
#endif /* SRAM3 */
/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Stop_Enabled_Status APB1 Peripheral Clock Stop Enabled Status
  * @brief  Check whether the APB1 peripheral clock during Low Power (Stop) is enabled or not.
  * @{
  */
#define __HAL_RCC_SPI3_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI3STPEN) != 0U)
#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI4STPEN) != 0U)
#endif /* SPI4 */
#define __HAL_RCC_SPI2_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_SPI2STPEN) != 0U)
#if defined(USART2)
#define __HAL_RCC_USART2_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_USART2STPEN) != 0U)
#endif /* USART2 */
#define __HAL_RCC_USART3_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_USART3STPEN) != 0U)
#define __HAL_RCC_UART4_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_UART4STPEN) != 0U)
#define __HAL_RCC_UART5_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_UART5STPEN) != 0U)
#define __HAL_RCC_I2C1_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I2C1STPEN) != 0U)
#define __HAL_RCC_I2C2_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I2C2STPEN) != 0U)
#define __HAL_RCC_I3C1_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_I3C1STPEN) != 0U)
#define __HAL_RCC_OPAMP_IS_CLK_STOP_ENABLED()     (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_OPAMPSTPEN) != 0U)
#define __HAL_RCC_VREF_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_VREFSTPEN) != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB1STPENR1, RCC_APB1STPENR1_RTCAPBSTPEN) != 0U)
#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB1STPENR2, RCC_APB1STPENR2_I2C4STPEN) != 0U)
#endif /* I2C4 */
#define __HAL_RCC_LPTIM2_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB1STPENR2, RCC_APB1STPENR2_LPTIM2STPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Stop_Enabled_Status APB2 Peripheral Clock Stop Enabled Status
  * @brief  Check whether the APB2 peripheral clock during Low Power (Stop) mode is enabled or not.
  * @{
  */
#define __HAL_RCC_SPI1_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB2STPENR, RCC_APB2STPENR_SPI1STPEN) != 0U)
#define __HAL_RCC_USART1_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB2STPENR, RCC_APB2STPENR_USART1STPEN) != 0U)
#define __HAL_RCC_USB1_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB2STPENR, RCC_APB2STPENR_USB1STPEN) != 0U)
#define __HAL_RCC_I3C2_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB2STPENR, RCC_APB2STPENR_I3C2STPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Stop_Enabled_Status APB3 Peripheral Clock Stop Enabled Status
  * @brief  Check whether the APB3 peripheral clock during Low Power (Stop) mode is enabled or not.
  * @{
  */
#define __HAL_RCC_LPUART1_IS_CLK_STOP_ENABLED()   (READ_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPUART1STPEN) != 0U)
#define __HAL_RCC_I2C3_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB3STPENR, RCC_APB3STPENR_I2C3STPEN) != 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM1STPEN) != 0U)
#define __HAL_RCC_LPTIM3_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM3STPEN) != 0U)
#define __HAL_RCC_LPTIM4_IS_CLK_STOP_ENABLED()    (READ_BIT(RCC->APB3STPENR, RCC_APB3STPENR_LPTIM4STPEN) != 0U)
#define __HAL_RCC_COMP_IS_CLK_STOP_ENABLED()      (READ_BIT(RCC->APB3STPENR, RCC_APB3STPENR_COMPSTPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */
/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @retval None
  */
#define __HAL_RCC_BACKUPRESET_FORCE()             SET_BIT(RCC->BDCR, RCC_BDCR_BDRST)
#define __HAL_RCC_BACKUPRESET_RELEASE()           CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST)
/**
  * @}
  */

/** @defgroup RCC_Oscillators_Clocks_Configuration Oscillators and Clocks Configuration
  * @{
  */
/** @brief  Macros to enable or disable the Internal High Speed 16MHz oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_HSI_ENABLE()                    SET_BIT(RCC->CR, RCC_CR_HSION)
#define __HAL_RCC_HSI_DISABLE()                   CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macro to adjust the Internal High Speed 16MHz oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__: specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__) \
  MODIFY_REG(RCC->ICSCR3, RCC_ICSCR3_HSITRIM, (__HSICALIBRATIONVALUE__) << RCC_ICSCR3_HSITRIM_Pos)

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs, LPUART and I2Cs.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI startup time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()                SET_BIT(RCC->CR, RCC_CR_HSIKERON)
#define __HAL_RCC_HSISTOP_DISABLE()               CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON)

/** @brief  Macros to enable or disable the Internal Low Speed oscillator LSI.
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   When the IWDG is started the LSI clock is forced on and cannot be disabled.
  *         When LSI is disabled LSI will be forced on.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 3 LSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()                    SET_BIT(RCC->CSR, RCC_CSR_LSION)
#define __HAL_RCC_LSI_DISABLE()                   CLEAR_BIT(RCC->CSR, RCC_CSR_LSION)

/** @brief  Macro to set Low-speed clock LSI divider.
  * @note   Only LSI clock can be divided
  * @note   This bit can be written only when the LSI is disabled (LSION = 0 and LSIRDY = 0).
  *         The LSIPREDIV cannot be changed if the LSI is used by the IWDG or by the RTC.
  * @param  __DIVIDER__ : specifies the divider value
  *          This parameter can be one of the following values
  *          @arg @ref RCC_LSI_DIV1
  *          @arg @ref RCC_LSI_DIV128
  * @retval None
  */
#define __HAL_RCC_LSI_DIV_CONFIG(__DIVIDER__)     MODIFY_REG(RCC->CSR, RCC_CSR_LSIPREDIV, __DIVIDER__)

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the system clock.
  * @note   HSE state can not be changed if it is used directly as system clock.
  *         In this case, you have to select another source, of the system clock
  *          then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY or shutdown modes.
  * @note   HSERDY flag may remain high when HSEON bit is cleared.
  * @param  __STATE__: specifies the new state of the HSE.
  *         This parameter can be a combination of the following values:
  *            @arg @ref RCC_HSE_OFF            Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                                             6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON             Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS         Turn ON HSE in analog bypass mode
  *            @arg @ref RCC_HSE_BYPASS_DIGITAL Turn ON HSE in digital bypass mode
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)           do {                                                      \
                                                    if((__STATE__) == RCC_HSE_ON)                           \
                                                    {                                                       \
                                                      SET_BIT(RCC->CR, RCC_CR_HSEON);                       \
                                                    }                                                       \
                                                    else if((__STATE__) == RCC_HSE_BYPASS)                  \
                                                    {                                                       \
                                                      SET_BIT(RCC->CR, RCC_CR_HSEBYP);                      \
                                                      SET_BIT(RCC->CR, RCC_CR_HSEON);                       \
                                                    }                                                       \
                                                    else if((__STATE__) == RCC_HSE_BYPASS_DIGITAL)          \
                                                    {                                                       \
                                                      SET_BIT(RCC->CR, (RCC_CR_HSEBYP | RCC_CR_HSEEXT));    \
                                                      SET_BIT(RCC->CR, RCC_CR_HSEON);                       \
                                                    }                                                       \
                                                    else                                                    \
                                                    {                                                       \
                                                      CLEAR_BIT(RCC->CR, RCC_CR_HSEON);                     \
                                                      CLEAR_BIT(RCC->CR, (RCC_CR_HSEBYP | RCC_CR_HSEEXT));  \
                                                    }                                                       \
                                                  } while(0U)

/** @brief  Macros to enable or disable the Internal High Speed 48MHz oscillator (HSI48).
  * @note   The HSI48 is stopped by hardware when entering STOP mode.
  * @note   After enabling the HSI48, the application software should wait on HSI48RDY
  *         flag to be set indicating that HSI48 clock is stable.
  * @retval None
  */
#define __HAL_RCC_HSI48_ENABLE()                  SET_BIT(RCC->CR, RCC_CR_HSI48ON)
#define __HAL_RCC_HSI48_DISABLE()                 CLEAR_BIT(RCC->CR, RCC_CR_HSI48ON)

/** @brief   Macro to enable or disable the LSE system clock.
  * @note    This clock can be used by any peripheral when its source clock is the LSE or at system
  *          in case of one of the LSCOSEL, MCO or CSS on LSE is needed.
  * @note    The LSESYS clock can be generated even if LSESYSEN= 0 if the LSE clock is requested by
  *          the CSS on LSE, by a peripheral or any other source clock using LSE.
  * @retval None
  */
#define __HAL_RCC_LSESYS_ENABLE()                 SET_BIT(RCC->BDCR,RCC_BDCR_LSESYSEN)
#define __HAL_RCC_LSESYS_DISABLE()                CLEAR_BIT(RCC->BDCR,RCC_BDCR_LSESYSEN)

/** @brief  Macros to enable or disable LSE clock glitch filter .
  * @note   The glitches on LSE can be filtred by setting the LSEGFON.
  * @note   LSEGFON must be written when the LSE is disabled (LSEON = 0 and LSERDY = 0).
  * @retval None
  */
#define __HAL_RCC_LSE_GLITCH_FILTER_ENABLE()       SET_BIT(RCC->BDCR, RCC_BDCR_LSEGFON )
#define __HAL_RCC_LSE_GLITCH_FILTER_DISABLE()      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEGFON )

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE, the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__: specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF          Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                                               6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON_RTC_ONLY      Turn ON the LSE oscillator to be used only for RTC.
  *            @arg @ref RCC_LSE_ON               Turn ON the LSE oscillator to be used by any peripheral.
  *            @arg @ref RCC_LSE_BYPASS_RTC_ONLY  LSE oscillator bypassed with external clock to be used only for RTC.
  *            @arg @ref RCC_LSE_BYPASS           LSE oscillator bypassed with external clock to be used by any peripheral.
  * @retval None
  */

#define __HAL_RCC_LSE_CONFIG(__STATE__)                                                                           \
                                                  do {                                                            \
                                                    if((__STATE__) == RCC_LSE_ON_RTC_ONLY)                        \
                                                    {                                                             \
                                                      SET_BIT(RCC->BDCR,RCC_BDCR_LSEON);                          \
                                                    }                                                             \
                                                    else if((__STATE__) == RCC_LSE_ON)                            \
                                                    {                                                             \
                                                      SET_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN));   \
                                                    }                                                             \
                                                    else if((__STATE__) == RCC_LSE_BYPASS_RTC_ONLY)               \
                                                    {                                                             \
                                                      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                        \
                                                      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);                         \
                                                    }                                                             \
                                                    else if((__STATE__) == RCC_LSE_BYPASS)                        \
                                                    {                                                             \
                                                      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                        \
                                                      SET_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN));   \
                                                    }                                                             \
                                                    else                                                          \
                                                    {                                                             \
                                                      CLEAR_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN)); \
                                                      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                      \
                                                    }                                                             \
                                                  } while(0)

/**
  * @brief  Macros to enable or disable the Internal Multi Speed oscillator (MSIS)
  * @note     The MSI is stopped by hardware when entering STOP and STANDBY modes.
  *           It is used (enabled by hardware) as system clock source after
  *           startup from Reset, wakeup from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     MSIS can not be stopped if it is used as system clock source.
  *           In this case, you have to select another source of the system
  *           clock then stop the MSIS.
  * @note     After enabling the MSIS, the application software should wait on
  *           MSISRDY flag to be set indicating that MSIS clock is stable and can
  *           be used.
  * @retval None
  */
#define __HAL_RCC_MSIS_ENABLE()                   SET_BIT(RCC->CR, RCC_CR_MSISON)
#define __HAL_RCC_MSIS_DISABLE()                  CLEAR_BIT(RCC->CR, RCC_CR_MSISON)

/** @brief  Macros to enable or disable the Internal multi-speed RC Kernel oscillator clock (MSIK).
  * @note   if the peripheral requests its kernel clock in Stop 0 or Stop 1 mode,MSIK is woken up
  * @note   After enabling the MSIK, the application software should wait on MSIKRDY
  *         flag to be set indicating that MSIK clock is stable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_MSIK_ENABLE()                   SET_BIT(RCC->CR, RCC_CR_MSIKON)
#define __HAL_RCC_MSIK_DISABLE()                  CLEAR_BIT(RCC->CR, RCC_CR_MSIKON)

/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after power On).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  * @param  __RTC_CLKSOURCE__: specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_DISABLE  RTC clock is disabled.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__)   MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, (__RTC_CLKSOURCE__))

/** @brief  Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_DISABLE  RTC clock is disabled.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  */
#define  __HAL_RCC_GET_RTC_SOURCE()               READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL)

/** @brief  Macros to enable or disable the RTC clock.
  * @note   As the RTC is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the RTC
  *         (to be done once after reset).
  * @note   These macros must be used after the RTC clock source was selected.
  * @retval None
  */
#define __HAL_RCC_RTC_ENABLE()                    SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN)
#define __HAL_RCC_RTC_DISABLE()                   CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__: specifies the system clock source.
  *          This parameter can be one of the following values:
  *              - RCC_SYSCLKSOURCE_MSIS: MSIS oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSI: HSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSE: HSE oscillator is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
                  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, (__SYSCLKSOURCE__))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              - RCC_SYSCLKSOURCE_STATUS_MSIS: MSIS used as system clock.
  *              - RCC_SYSCLKSOURCE_STATUS_HSI: HSI used as system clock.
  *              - RCC_SYSCLKSOURCE_STATUS_HSE: HSE used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() (RCC->CFGR1 & RCC_CFGR1_SWS)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   The LSE drive can be decreased to the lower drive capability (LSEDRV = 0)
  *         when the LSE is ON. However, once LSEDRV is selected, the drive
  *         capability can not be increased if LSEON = 1.
  * @param  __LSEDRIVE__: specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW  LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
                  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, (__LSEDRIVE__))

/** @brief  Macro to configure the MCO1 clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK   System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_MSIS     MSIS clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI      HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE      HSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI      LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE      LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI48    HSI48 selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_MSIK     MSIK selected as MCO source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1    MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2    MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4    MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8    MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16   MCO clock source is divided by 16
  *            @arg @ref RCC_MCODIV_32   MCO clock source is divided by 32
  *            @arg @ref RCC_MCODIV_64   MCO clock source is divided by 64
  *            @arg @ref RCC_MCODIV_128  MCO clock source is divided by 128
  * @retval None
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
                 MODIFY_REG(RCC->CFGR1, (RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @brief  Macro to configure the MCO2 clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO2SOURCE_NOCLOCK  MCO2 output disabled
  *            @arg @ref RCC_MCO2SOURCE_SYSCLK   System  clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_MSIS     MSIS clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSI      HSI clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSE      HSE clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_LSI      LSI clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_LSE      LSE clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSI48    HSI48 selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_MSIK     MSIK selected as MCO2 source
  * @param  __MCODIV__ specifies the MCO2 clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO2DIV_1    MCO2 clock source is divided by 1
  *            @arg @ref RCC_MCO2DIV_2    MCO2 clock source is divided by 2
  *            @arg @ref RCC_MCO2DIV_4    MCO2 clock source is divided by 4
  *            @arg @ref RCC_MCO2DIV_8    MCO2 clock source is divided by 8
  *            @arg @ref RCC_MCO2DIV_16   MCO2 clock source is divided by 16
  *            @arg @ref RCC_MCO2DIV_32   MCO2 clock source is divided by 32
  *            @arg @ref RCC_MCO2DIV_64   MCO2 clock source is divided by 64
  *            @arg @ref RCC_MCO2DIV_128  MCO2 clock source is divided by 128
  * @retval None
  */
#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
                 MODIFY_REG(RCC->CFGR1, (RCC_CFGR1_MCO2SEL | RCC_CFGR1_MCO2PRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))
/**
  * @}
  */

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */
/** @brief  Enable RCC interrupt
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_HSIRDY           HSI ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY         HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY           HSE Ready interrupt
  *            @arg @ref RCC_IT_LSIRDY           LSI Ready interrupt
  *            @arg @ref RCC_IT_LSERDY           LSE Ready interrupt
  *            @arg @ref RCC_IT_MSISRDY          MSIS Ready interrupt
  *            @arg @ref RCC_IT_MSIKRDY          MSIK Ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL1RDY      MSI RC1 PLL ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL0RDY      MSI RC0 PLL ready iInterrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_LSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_HSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_CSS              HSE clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS           LSE clock security system interrupt
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_HSIRDY           HSI ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY         HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY           HSE Ready interrupt
  *            @arg @ref RCC_IT_LSIRDY           LSI Ready interrupt
  *            @arg @ref RCC_IT_LSERDY           LSE Ready interrupt
  *            @arg @ref RCC_IT_MSISRDY          MSIS Ready interrupt
  *            @arg @ref RCC_IT_MSIKRDY          MSIK Ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL1RDY      MSI RC1 PLL ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL0RDY      MSI RC0 PLL ready iInterrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_LSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_HSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_CSS              HSE clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS           LSE clock security system interrupt
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_HSIRDY           HSI ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY         HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY           HSE Ready interrupt
  *            @arg @ref RCC_IT_LSIRDY           LSI Ready interrupt
  *            @arg @ref RCC_IT_LSERDY           LSE Ready interrupt
  *            @arg @ref RCC_IT_MSISRDY          MSIS Ready interrupt
  *            @arg @ref RCC_IT_MSIKRDY          MSIK Ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL1RDY      MSI RC1 PLL ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL0RDY      MSI RC0 PLL ready iInterrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_LSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_HSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_LSECSS           LSE clock security system interrupt
  * @retval None
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) WRITE_REG(RCC->CICR, (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_HSIRDY           HSI ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY         HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY           HSE Ready interrupt
  *            @arg @ref RCC_IT_LSIRDY           LSI Ready interrupt
  *            @arg @ref RCC_IT_LSERDY           LSE Ready interrupt
  *            @arg @ref RCC_IT_MSISRDY          MSIS Ready interrupt
  *            @arg @ref RCC_IT_MSIKRDY          MSIK Ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL1RDY      MSI RC1 PLL ready interrupt
  *            @arg @ref RCC_IT_MSI_PLL0RDY      MSI RC0 PLL ready iInterrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_LSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_MSI_PLLUNLCK_HSE MSI PLL-mode with HSE unlock interrupt
  *            @arg @ref RCC_IT_CSS              HSE clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS           LSE clock security system interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__)  ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_PWRRST, RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_BORRST,
  *        RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST and RCC_FLAG_LPWRRST.
  * @retval None
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref  RCC_FLAG_HSIRDY                  HSI Ready flag
  *            @arg @ref  RCC_FLAG_HSI48RDY                HSI48 Ready flag
  *            @arg @ref  RCC_FLAG_HSERDY                  HSE Ready flag
  *            @arg @ref  RCC_FLAG_MSISRDY                 MSIS Ready flag
  *            @arg @ref  RCC_FLAG_MSIKRDY                 MSIK Ready flag
  *            @arg @ref  RCC_FLAG_MSI_PLL0RDY             MSI RC0 PLL Ready Interrupt flag
  *            @arg @ref  RCC_FLAG_MSI_PLL1RDY             MSI RC1 PLL Ready Interrupt flag
  *            @arg @ref  RCC_FLAG_LSERDY                  LSE Ready flag
  *            @arg @ref  RCC_FLAG_LSESYSRDY               LSESYS Ready flag
  *            @arg @ref  RCC_FLAG_LSECSSD                 LSE Clock Security System Interrupt flag
  *            @arg @ref  RCC_FLAG_OBLRST                  Option Byte Loader reset flag
  *            @arg @ref  RCC_FLAG_PINRST                  PIN reset flag
  *            @arg @ref  RCC_FLAG_BORRST                  BOR reset flag
  *            @arg @ref  RCC_FLAG_SFTRST                  Software Reset flag
  *            @arg @ref  RCC_FLAG_IWDGRST                 Independent Watchdog reset flag
  *            @arg @ref  RCC_FLAG_WWDGRST                 Window watchdog reset flag
  *            @arg @ref  RCC_FLAG_LPWRRST                 Low-Power reset flag
  *            @arg @ref  RCC_FLAG_LSIRDY                  LSI Ready flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) ((((((((__FLAG__) >> 5U) == 1U) ? RCC->CR :                     \
                                        ((((__FLAG__) >> 5U) == 2U) ? RCC->BDCR :                     \
                                        ((((__FLAG__) >> 5U) == 3U) ? RCC->CSR : RCC->CIFR)))) &  \
                                          (1U << ((__FLAG__) & RCC_FLAG_MASK))) != 0U)               \
                                            ? 1U : 0U)
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */
/* Defines used for Flags */
#define CR_REG_INDEX                    (1U)
#define BDCR_REG_INDEX                  (2U)
#define CSR_REG_INDEX                   (3U)

#define RCC_FLAG_MASK                   (0x1FU)

/* Define used for IS_RCC_* below */
#define RCC_CLOCKTYPE_ALL               (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | \
                                         RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3)         /*!< All clocks to configure */
#define RCC_OSCILLATORTYPE_ALL          (RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48 | \
                                         RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_MSIS |  \
                                         RCC_OSCILLATORTYPE_MSIK) /*!< All Oscillators to configure */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */
#define IS_RCC_OSCILLATORTYPE(__TYPE__)         (((__TYPE__) == RCC_OSCILLATORTYPE_NONE) || \
                                                 (((__TYPE__) & ~RCC_OSCILLATORTYPE_ALL) == 0x00U))

#define IS_RCC_HSE(__STATE__)                   (((__STATE__) == RCC_HSE_OFF)    || ((__STATE__) == RCC_HSE_ON) || \
                                                 ((__STATE__) == RCC_HSE_BYPASS) || ((__STATE__) == RCC_HSE_BYPASS_DIGITAL))

#define IS_RCC_LSE(__STATE__)                   (((__STATE__) == RCC_LSE_OFF) || ((__STATE__) == RCC_LSE_ON_RTC_ONLY)     || \
                                                 ((__STATE__) == RCC_LSE_ON)  || ((__STATE__) == RCC_LSE_BYPASS_RTC_ONLY) || \
                                                 ((__STATE__) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(__STATE__)                   (((__STATE__) == RCC_HSI_OFF) || ((__STATE__) == RCC_HSI_ON))

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (uint32_t)( RCC_ICSCR3_HSITRIM  >>  RCC_ICSCR3_HSITRIM_Pos))

#define IS_RCC_HSI48(__STATE__)                 (((__STATE__) == RCC_HSI48_OFF) || ((__STATE__) == RCC_HSI48_ON))

#define IS_RCC_LSI(__STATE__)                   (((__STATE__) == RCC_LSI_OFF) || ((__STATE__) == RCC_LSI_ON))

#define IS_RCC_LSI_DIV(__DIV__)                 (((__DIV__) == RCC_LSI_DIV1) || ((__DIV__) == RCC_LSI_DIV128))

#define IS_RCC_MSI(__STATE__)                   (((__STATE__) == RCC_MSI_OFF) || ((__STATE__) == RCC_MSI_ON))

#define IS_RCC_MSI_SOURCE(__RC__)               (((__RC__) == RCC_MSI_RC0) || ((__RC__) == RCC_MSI_RC1))

#define IS_RCC_MSI_DIV(__DIV__)                 (((__DIV__) == RCC_MSI_DIV1) || ((__DIV__) == RCC_MSI_DIV2) || \
                                                 ((__DIV__) == RCC_MSI_DIV4) || ((__DIV__) == RCC_MSI_DIV8))

#define IS_RCC_CLOCKTYPE(__CLK__)               ((((__CLK__) & RCC_CLOCKTYPE_ALL) != 0x00UL) && (((__CLK__) & ~RCC_CLOCKTYPE_ALL) == 0x00UL))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_SYSCLKSOURCE_MSIS) || ((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                                 ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE))

#define IS_RCC_HCLK(__HCLK__)                   (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                                                 ((__HCLK__) == RCC_SYSCLK_DIV4)   || ((__HCLK__) == RCC_SYSCLK_DIV8)   || \
                                                 ((__HCLK__) == RCC_SYSCLK_DIV16)  || ((__HCLK__) == RCC_SYSCLK_DIV64)  || \
                                                 ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
                                                 ((__HCLK__) == RCC_SYSCLK_DIV512))

#define IS_RCC_PCLK(__PCLK__)                   (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                                                 ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                                                 ((__PCLK__) == RCC_HCLK_DIV16))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_RTCCLKSOURCE_DISABLE) || \
                                                 ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)     || \
                                                 ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)     || \
                                                 ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32))

#define IS_RCC_MCO(__MCOX__)                    (((__MCOX__) == RCC_MCO1_PA8) || ((__MCOX__) == RCC_MCO1_PA9) || \
                                                 ((__MCOX__) == RCC_MCO2_PA8) || ((__MCOX__) == RCC_MCO2_PA10))

#define IS_RCC_MCO1SOURCE(__SOURCE__)           (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK)  || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK)   || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_MSIS)     || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_HSI)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_HSE)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_LSI)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_LSE)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_HSI48)    || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_MSIK))

#define IS_RCC_MCODIV(__DIV__)                  (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                                 ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                                 ((__DIV__) == RCC_MCODIV_16) || ((__DIV__) == RCC_MCODIV_32) || \
                                                 ((__DIV__) == RCC_MCODIV_64) || ((__DIV__) == RCC_MCODIV_128))

#define IS_RCC_MCO2SOURCE(__SOURCE__)           (((__SOURCE__) == RCC_MCO2SOURCE_NOCLOCK)  || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_SYSCLK)   || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_MSIS)     || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_HSI)      || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_HSE)      || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_LSI)      || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_LSE)      || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_HSI48)    || \
                                                 ((__SOURCE__) == RCC_MCO2SOURCE_MSIK))

#define IS_RCC_MCO2DIV(__DIV__)                 (((__DIV__) == RCC_MCO2DIV_1) || ((__DIV__) == RCC_MCO2DIV_2) || \
                                                 ((__DIV__) == RCC_MCO2DIV_4) || ((__DIV__) == RCC_MCO2DIV_8) || \
                                                 ((__DIV__) == RCC_MCO2DIV_16) || ((__DIV__) == RCC_MCO2DIV_32) || \
                                                 ((__DIV__) == RCC_MCO2DIV_64) || ((__DIV__) == RCC_MCO2DIV_128))

#define IS_RCC_LSE_DRIVE(__DRIVE__)             (((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

#define IS_RCC_ITEM_ATTRIBUTES(__ITEM__)        (((__ITEM__) != 0x00U) && \
                                                 (((__ITEM__) & ~RCC_ALL) == 0x00U))

#if defined(CPU_IN_SECURE_STATE)
#define IS_RCC_ATTRIBUTES(__ATTRIBUTES__)       (((__ATTRIBUTES__) == RCC_SEC_PRIV)  || ((__ATTRIBUTES__)  == RCC_SEC_NPRIV) || \
                                                 ((__ATTRIBUTES__)  == RCC_NSEC_PRIV) || ((__ATTRIBUTES__)  == RCC_NSEC_NPRIV))
#else
#define IS_RCC_ATTRIBUTES(__ATTRIBUTES__)       (((__ATTRIBUTES__) == RCC_NSEC_NPRIV) || ((__ATTRIBUTES__) == RCC_NSEC_PRIV))
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/**
  * @}
  */
/* Include RCC HAL Extended module */
#include "stm32u3xx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  **********************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);
uint32_t          HAL_RCC_GetPCLK3Freq(void);
uint32_t          HAL_RCC_GetMSISFreq(void);
uint32_t          HAL_RCC_GetMSIKFreq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* CSS NMI IRQ handler */
void              HAL_RCC_NMI_IRQHandler(void);
/* User Callbacks in non blocking mode (IT mode) */
void              HAL_RCC_CSSCallback(void);
uint32_t          HAL_RCC_GetResetSource(void);
/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group3
  * @{
  */
/* Attributes management functions ********************************************/
void              HAL_RCC_ConfigAttributes(uint32_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_RCC_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);
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

#endif /* __STM32U3xx_HAL_RCC_H */
