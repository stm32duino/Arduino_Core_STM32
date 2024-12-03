/**
  ******************************************************************************
  * @file    stm32u0xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
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

#ifndef STM32U0xx_HAL_RCC_H
#define STM32U0xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal_def.h"

/** @addtogroup STM32U0xx_HAL_Driver
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
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;   /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Config                      */

  uint32_t PLLSource;  /*!< RCC_PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source               */

  uint32_t PLLM;       /*!< PLLM: Division factor for PLL VCO input clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 16    */

  uint32_t PLLN;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 4 and Max_Data = 512   */

  uint32_t PLLP;       /*!< PLLP: Division factor for system clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128
                          odd division factors are not allowed                                        */

  uint32_t PLLQ;       /*!< PLLQ: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint32_t PLLR;       /*!< PLLR: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 2 and Max_Data = 128   */

  uint32_t PLLClockOut; /*!< PLLClockOut: specifies PLL output clock to be enabled.
                                  This parameter must be a value of @ref RCC_PLL_Clock_Output */

} RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, MSI, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F
                                      on the other devices */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t LSIDiv;               /*!< The division factor of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Div                           */

  uint32_t MSIState;             /*!< The new state of the MSI.
                                      This parameter can be a value of @ref RCC_MSI_Config */

  uint32_t MSICalibrationValue;  /*!< The calibration trimming value (default is RCC_MSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF */

  uint32_t MSIClockRange;        /*!< The MSI frequency range.
                                      This parameter can be a value of @ref RCC_MSI_Clock_Range  */
#if defined(RCC_CRRCR_HSI48ON)
  uint32_t HSI48State;           /*!< The new state of the HSI48.
                                        This parameter can be a value of @ref RCC_HSI48_Config */
#endif /* RCC_CRRCR_HSI48ON */
  RCC_PLLInitTypeDef PLL;        /*!< Main PLL structure parameters                          */

} RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a value of @ref RCC_System_Clock_Type      */

  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHB_Clock_Source       */

  uint32_t APB1CLKDivider;        /*!< The APB clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB_Clock_Source */

} RCC_ClkInitTypeDef;

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        (0x00000000U)   /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSE         (0x00000001U)   /*!< HSE to configure */
#define RCC_OSCILLATORTYPE_HSI         (0x00000002U)   /*!< HSI to configure */
#define RCC_OSCILLATORTYPE_LSE         (0x00000004U)   /*!< LSE to configure */
#define RCC_OSCILLATORTYPE_LSI         (0x00000008U)   /*!< LSI to configure */
#define RCC_OSCILLATORTYPE_MSI         (0x00000010U)   /*!< MSI to configure */
#if defined(RCC_CRRCR_HSI48ON)
#define RCC_OSCILLATORTYPE_HSI48       (0x00000020U)   /*!< HSI48 to configure */
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    (0x00000000U)                              /*!< HSE clock deactivation */
#define RCC_HSE_ON                     RCC_CR_HSEON                               /*!< HSE clock activation */
#define RCC_HSE_BYPASS                 ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON)) /*!< External clock source for HSE clock */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    (0x00000000U)                                          /*!< LSE clock deactivation */
#define RCC_LSE_ON_RTC_ONLY            RCC_BDCR_LSEON                                         /*!< LSE clock activation for RTC only */
#define RCC_LSE_ON                     (RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON)                   /*!< LSE clock activation for RCC and peripherals */
#define RCC_LSE_BYPASS_RTC_ONLY        (RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)                     /*!< External clock source for LSE clock */
#define RCC_LSE_BYPASS                 (RCC_BDCR_LSEBYP | RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON) /*!< External clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    (0x00000000U)          /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_CR_HSION           /*!< HSI clock activation */

#define RCC_HSICALIBRATION_DEFAULT     (0x40U)                /*! Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    (0x00000000U)      /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR_LSION      /*!< LSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_LSI_Div LSI Div
  * @{
  */
#define RCC_LSI_DIV1                   (0x00000000U)       /*!< LSI clock is not divided */
#define RCC_LSI_DIV128                 RCC_CSR_LSIPREDIV   /*!< LSI clock is divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_MSI_Config MSI Config
  * @{
  */
#define RCC_MSI_OFF                    (0x00000000U)       /*!< MSI clock deactivation */
#define RCC_MSI_ON                     RCC_CR_MSION        /*!< MSI clock activation */

#define RCC_MSICALIBRATION_DEFAULT     (0x0U)              /*!< Default MSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_HSIK_Config HSIK Config
  * @{
  */
#define RCC_HSIK_OFF                   (0x00000000U)       /*!< HSIK clock deactivation */
#define RCC_HSIK_ON                    RCC_CR_HSIKERON     /*!< HSIK clock activation */
/**
  * @}
  */

/** @defgroup RCC_HSIASFS_Config HSIASFS Config
  * @{
  */
#define RCC_HSIASFS_OFF                (0x00000000U)         /*!< HSIASFS clock deactivation */
#define RCC_HSIASFS_ON                 RCC_CR_HSIASFSON      /*!< HSIASFS clock activation */
/**
  * @}
  */

/** @defgroup RCC_HSECSS_Config HSECSS Config
  * @{
  */
#define RCC_HSECSS_OFF                 (0x00000000U)         /*!< HSECSS clock deactivation */
#define RCC_HSECSS_ON                  RCC_CR_HSECSSON       /*!< HSECSS clock activation */

/**
  * @}
  */
#if defined(RCC_CRRCR_HSI48ON)
/** @defgroup RCC_HSI48_Config HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                 (0x00000000U)          /*!< HSI48 clock deactivation */
#define RCC_HSI48_ON                  RCC_CRRCR_HSI48ON      /*!< HSI48 clock activation */
#endif /* RCC_CRRCR_HSI48ON */
/**
  * @}
  */

/** @defgroup RCC_PLL_Config  RCC PLL Config
  * @{
  */
#define RCC_PLL_NONE                 (0x00000000U)
#define RCC_PLL_OFF                  (0x00000001U)
#define RCC_PLL_ON                   (0x00000002U)

/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Output  RCC PLL Clock Output
  * @{
  */
#define RCC_PLL_DIVP                RCC_PLLCFGR_PLLPEN
#define RCC_PLL_DIVQ                RCC_PLLCFGR_PLLQEN
#define RCC_PLL_DIVR                RCC_PLLCFGR_PLLREN

/**
  * @}
  */

/** @defgroup RCC_PLLM_Clock_Divider PLLM Clock Divider
  * @{
  */
#define RCC_PLLM_DIV1       0x00000000U                                                    /*!< PLLM division factor = 8  */
#define RCC_PLLM_DIV2       RCC_PLLCFGR_PLLM_0                                             /*!< PLLM division factor = 2  */
#define RCC_PLLM_DIV3       RCC_PLLCFGR_PLLM_1                                             /*!< PLLM division factor = 3  */
#define RCC_PLLM_DIV4       (RCC_PLLCFGR_PLLM_1 | RCC_PLLCFGR_PLLM_0)                      /*!< PLLM division factor = 4  */
#define RCC_PLLM_DIV5       RCC_PLLCFGR_PLLM_2                                             /*!< PLLM division factor = 5  */
#define RCC_PLLM_DIV6       (RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_0)                      /*!< PLLM division factor = 6  */
#define RCC_PLLM_DIV7       (RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_1)                      /*!< PLLM division factor = 7  */
#define RCC_PLLM_DIV8       (RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_1| RCC_PLLCFGR_PLLM_0)  /*!< PLLM division factor = 8  */
/**
  * @}
  */
/** @defgroup RCC_PLLP_Clock_Divider PLLP Clock Divider
  * @{
  */
#define RCC_PLLP_DIV2        RCC_PLLCFGR_PLLP_0                                                                   /*!< PLLP division factor = 2  */
#define RCC_PLLP_DIV3        RCC_PLLCFGR_PLLP_1                                                                   /*!< PLLP division factor = 3  */
#define RCC_PLLP_DIV4        (RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)                                            /*!< PLLP division factor = 4  */
#define RCC_PLLP_DIV5        RCC_PLLCFGR_PLLP_2                                                                   /*!< PLLP division factor = 5  */
#define RCC_PLLP_DIV6        (RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_0)                                            /*!< PLLP division factor = 6  */
#define RCC_PLLP_DIV7        (RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1)                                            /*!< PLLP division factor = 7  */
#define RCC_PLLP_DIV8        (RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)                       /*!< PLLP division factor = 8  */
#define RCC_PLLP_DIV9        RCC_PLLCFGR_PLLP_3                                                                   /*!< PLLP division factor = 9  */
#define RCC_PLLP_DIV10       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_0)                                            /*!< PLLP division factor = 10 */
#define RCC_PLLP_DIV11       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_1)                                            /*!< PLLP division factor = 11 */
#define RCC_PLLP_DIV12       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)                       /*!< PLLP division factor = 12 */
#define RCC_PLLP_DIV13       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2)                                            /*!< PLLP division factor = 13 */
#define RCC_PLLP_DIV14       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_0)                       /*!< PLLP division factor = 14 */
#define RCC_PLLP_DIV15       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1)                       /*!< PLLP division factor = 15 */
#define RCC_PLLP_DIV16       (RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)  /*!< PLLP division factor = 16 */
#define RCC_PLLP_DIV17       RCC_PLLCFGR_PLLP_4                                                                   /*!< PLLP division factor = 17 */
#define RCC_PLLP_DIV18       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_0)                                            /*!< PLLP division factor = 18 */
#define RCC_PLLP_DIV19       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_1)                                            /*!< PLLP division factor = 19 */
#define RCC_PLLP_DIV20       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)                       /*!< PLLP division factor = 20 */
#define RCC_PLLP_DIV21       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_2)                                            /*!< PLLP division factor = 21 */
#define RCC_PLLP_DIV22       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_0)                       /*!< PLLP division factor = 22 */
#define RCC_PLLP_DIV23       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1)                       /*!< PLLP division factor = 23 */
#define RCC_PLLP_DIV24       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)  /*!< PLLP division factor = 24 */
#define RCC_PLLP_DIV25       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3)                                            /*!< PLLP division factor = 25 */
#define RCC_PLLP_DIV26       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_0)                       /*!< PLLP division factor = 26 */
#define RCC_PLLP_DIV27       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_1)                       /*!< PLLP division factor = 27 */
#define RCC_PLLP_DIV28       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLP_0)  /*!< PLLP division factor = 28 */
#define RCC_PLLP_DIV29       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2)                       /*!< PLLP division factor = 29 */
#define RCC_PLLP_DIV30       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_0)  /*!< PLLP division factor = 30 */
#define RCC_PLLP_DIV31       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1)  /*!< PLLP division factor = 31 */
#define RCC_PLLP_DIV32       (RCC_PLLCFGR_PLLP_4 | RCC_PLLCFGR_PLLP_3 | RCC_PLLCFGR_PLLP_2 | RCC_PLLCFGR_PLLP_1 | \
                              RCC_PLLCFGR_PLLP_0)                                                                 /*!< PLLP division factor = 32 */
/**
  * @}
  */

/** @defgroup RCC_PLLQ_Clock_Divider PLLQ Clock Divider
  * @{
  */
#define RCC_PLLQ_DIV2       RCC_PLLCFGR_PLLQ_0                                             /*!< PLLQ division factor = 2 */
#define RCC_PLLQ_DIV3       RCC_PLLCFGR_PLLQ_1                                             /*!< PLLQ division factor = 3 */
#define RCC_PLLQ_DIV4       (RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_0)                      /*!< PLLQ division factor = 4 */
#define RCC_PLLQ_DIV5       RCC_PLLCFGR_PLLQ_2                                             /*!< PLLQ division factor = 5 */
#define RCC_PLLQ_DIV6       (RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_0)                      /*!< PLLQ division factor = 6 */
#define RCC_PLLQ_DIV7       (RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_1)                      /*!< PLLQ division factor = 7 */
#define RCC_PLLQ_DIV8       (RCC_PLLCFGR_PLLQ_2 |RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_0)  /*!< PLLQ division factor = 8 */
/**
  * @}
  */

/** @defgroup RCC_PLLR_Clock_Divider PLLR Clock Divider
  * @{
  */
#define RCC_PLLR_DIV2       RCC_PLLCFGR_PLLR_0                                             /*!< PLLR division factor = 2 */
#define RCC_PLLR_DIV3       RCC_PLLCFGR_PLLR_1                                             /*!< PLLR division factor = 3 */
#define RCC_PLLR_DIV4       (RCC_PLLCFGR_PLLR_1 | RCC_PLLCFGR_PLLR_0)                      /*!< PLLR division factor = 4 */
#define RCC_PLLR_DIV5       RCC_PLLCFGR_PLLR_2                                             /*!< PLLR division factor = 5 */
#define RCC_PLLR_DIV6       (RCC_PLLCFGR_PLLR_2 | RCC_PLLCFGR_PLLR_0)                      /*!< PLLR division factor = 6 */
#define RCC_PLLR_DIV7       (RCC_PLLCFGR_PLLR_2 | RCC_PLLCFGR_PLLR_1)                      /*!< PLLR division factor = 7 */
#define RCC_PLLR_DIV8       (RCC_PLLCFGR_PLLR_2 | RCC_PLLCFGR_PLLR_1 | RCC_PLLCFGR_PLLR_0) /*!< PLLR division factor = 8 */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source  RCC PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_NONE             (0x00000000U)
#define RCC_PLLSOURCE_MSI              RCC_PLLCFGR_PLLSRC_0
#define RCC_PLLSOURCE_HSI              RCC_PLLCFGR_PLLSRC_1
#define RCC_PLLSOURCE_HSE              (RCC_PLLCFGR_PLLSRC_0 | RCC_PLLCFGR_PLLSRC_1)

/**
  * @}
  */
/** @defgroup RCC_MSI_Clock_Range MSI Clock Range
  * @{
  */
#define RCC_MSIRANGE_0                 RCC_CR_MSIRANGE_0  /*!< MSI = 100 KHz  */
#define RCC_MSIRANGE_1                 RCC_CR_MSIRANGE_1  /*!< MSI = 200 KHz  */
#define RCC_MSIRANGE_2                 RCC_CR_MSIRANGE_2  /*!< MSI = 400 KHz  */
#define RCC_MSIRANGE_3                 RCC_CR_MSIRANGE_3  /*!< MSI = 800 KHz  */
#define RCC_MSIRANGE_4                 RCC_CR_MSIRANGE_4  /*!< MSI = 1 MHz    */
#define RCC_MSIRANGE_5                 RCC_CR_MSIRANGE_5  /*!< MSI = 2 MHz    */
#define RCC_MSIRANGE_6                 RCC_CR_MSIRANGE_6  /*!< MSI = 4 MHz    */
#define RCC_MSIRANGE_7                 RCC_CR_MSIRANGE_7  /*!< MSI = 8 MHz    */
#define RCC_MSIRANGE_8                 RCC_CR_MSIRANGE_8  /*!< MSI = 16 MHz   */
#define RCC_MSIRANGE_9                 RCC_CR_MSIRANGE_9  /*!< MSI = 24 MHz   */
#define RCC_MSIRANGE_10                RCC_CR_MSIRANGE_10 /*!< MSI = 32 MHz   */
#define RCC_MSIRANGE_11                RCC_CR_MSIRANGE_11 /*!< MSI = 48 MHz   */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           (0x00000001U)  /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK             (0x00000002U)  /*!< HCLK to configure */
#define RCC_CLOCKTYPE_PCLK1            (0x00000004U)  /*!< PCLK1 to configure */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_MSI            (0x00000000U)                     /*!< MSI selection as system clock */
#define RCC_SYSCLKSOURCE_HSI            RCC_CFGR_SW_0                     /*!< HSI selection as system clock */
#define RCC_SYSCLKSOURCE_HSE            RCC_CFGR_SW_1                     /*!< HSE selection as system clock */
#define RCC_SYSCLKSOURCE_PLLCLK         (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)   /*!< PLL selection as system clock */
#define RCC_SYSCLKSOURCE_LSI            RCC_CFGR_SW_2                     /*!< LSI selection as system clock */
#define RCC_SYSCLKSOURCE_LSE            (RCC_CFGR_SW_2  |RCC_CFGR_SW_0)   /*!< LSE selection as system clock */
/**
  * @}
  */


/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_MSI      (0x00000000U)                      /*!< MSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSI      RCC_CFGR_SWS_0                     /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE      RCC_CFGR_SWS_1                     /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK   (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0)  /*!< PLL used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_LSI      RCC_CFGR_SWS_2                     /*!< LSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_LSE      (RCC_CFGR_SWS_2  |RCC_CFGR_SWS_0)  /*!< LSE used as system clock */
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1       (0x00000000U)                                                           /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2       RCC_CFGR_HPRE_3                                                         /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4       (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0)                                     /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8       (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1)                                     /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)                   /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2)                                     /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128     (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0)                   /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256     (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1)                   /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512     (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Source APB Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                  (0x00000000U)                                         /*!< HCLK not divided */
#define RCC_HCLK_DIV2                  RCC_CFGR_PPRE_2                                       /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4                  (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_0)                   /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8                  (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1)                   /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16                 (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_0) /*!< HCLK divided by 16 */

/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NONE          0x00000000U          /*!< No clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSE           RCC_BDCR_RTCSEL_0    /*!< LSE oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSI           RCC_BDCR_RTCSEL_1    /*!< LSI oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE           RCC_BDCR_RTCSEL      /*!< HSE oscillator clock divided by 32 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV32     RCC_RTCCLKSOURCE_HSE
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
/* 32      28      20      16      0

   |-------|-------|-------|-------|
   | MCO   | GPIO  | GPIO  | GPIO  |
   | Index |  AF   | Port  |  Pin  |
   -------------------------------*/

#define RCC_MCO_GPIOPORT_POS   16U
#define RCC_MCO_GPIOPORT_MASK  (0xFUL << RCC_MCO_GPIOPORT_POS)
#define RCC_MCO_GPIOAF_POS     20U
#define RCC_MCO_GPIOAF_MASK    (0xFFUL << RCC_MCO_GPIOAF_POS)
#define RCC_MCO_INDEX_POS      28U
#define RCC_MCO_INDEX_MASK     (0x1UL << RCC_MCO_INDEX_POS)
#define RCC_MCO1_INDEX         (0x0UL << RCC_MCO_INDEX_POS)             /*!< MCO1 index */
#define RCC_MCO1_PA8           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_8)
#define RCC_MCO1_PA9           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_9)
#define RCC_MCO1_PF2           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOF) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_2)
#define RCC_MCO1               RCC_MCO1_PA8

#define RCC_MCO2_INDEX         (0x1UL << RCC_MCO_INDEX_POS)             /*!< MCO2 index */
#define RCC_MCO2_PC2           (RCC_MCO2_INDEX |\
                                (GPIO_AF0_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOC) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_2)
#define RCC_MCO2_PA10          (RCC_MCO2_INDEX |\
                                (GPIO_AF3_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_10)
#define RCC_MCO2_PA8           (RCC_MCO2_INDEX |\
                                (GPIO_AF3_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_8)
#define RCC_MCO2                RCC_MCO2_PC2

#define RCC_MCO                RCC_MCO1               /*!< MCO1 to be compliant with other families with 2 MCOs*/
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK         (0x00000000U)                                                   /*!< MCO1 output disabled, no clock on MCO1 */
#define RCC_MCO1SOURCE_SYSCLK          RCC_CFGR_MCO1SEL_0                                              /*!< SYSCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_MSI             RCC_CFGR_MCO1SEL_1                                              /*!< MSI selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI             (RCC_CFGR_MCO1SEL_0 | RCC_CFGR_MCO1SEL_1)                       /*!< HSI selection as MCO1 source */
#define RCC_MCO1SOURCE_HSE             RCC_CFGR_MCO1SEL_2                                              /*!< HSE selection as MCO1 source */
#define RCC_MCO1SOURCE_PLLR            (RCC_CFGR_MCO1SEL_0 | RCC_CFGR_MCO1SEL_2)                       /*!< PLLCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_LSI             (RCC_CFGR_MCO1SEL_1 | RCC_CFGR_MCO1SEL_2)                       /*!< LSI selection as MCO1 source */
#define RCC_MCO1SOURCE_LSE             (RCC_CFGR_MCO1SEL_0 | RCC_CFGR_MCO1SEL_1 | RCC_CFGR_MCO1SEL_2)  /*!< LSE selection as MCO1 source */
#if defined(RCC_CRRCR_HSI48ON)
#define RCC_MCO1SOURCE_HSI48           RCC_CFGR_MCO1SEL_3                                              /*!< HSI48 selection as MCO1 source */
#endif /* RCC_CRRCR_HSI48ON */
#define RCC_MCO1SOURCE_RTC_ALT         (RCC_CFGR_MCO1SEL_0 | RCC_CFGR_MCO1SEL_3)                       /*!< RTC alternative clock selection as MCO1 source */
#define RCC_MCO1SOURCE_RTC_WAKEUP      (RCC_CFGR_MCO1SEL_1 | RCC_CFGR_MCO1SEL_3)                       /*!< RTC wakeup interrupt signal selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Source MCO2 Clock Source
  * @{
  */
#define RCC_MCO2SOURCE_NOCLOCK         (0x00000000U)                                                   /*!< MCO2 output disabled, no clock on MCO2 */
#define RCC_MCO2SOURCE_SYSCLK          RCC_CFGR_MCO2SEL_0                                              /*!< SYSCLK selection as MCO2 source */
#define RCC_MCO2SOURCE_MSI             RCC_CFGR_MCO2SEL_1                                              /*!< MSI selection as MCO2 source */
#define RCC_MCO2SOURCE_HSI             (RCC_CFGR_MCO2SEL_0 | RCC_CFGR_MCO2SEL_1)                       /*!< HSI selection as MCO2 source */
#define RCC_MCO2SOURCE_HSE             RCC_CFGR_MCO2SEL_2                                              /*!< HSE selection as MCO2 source */
#define RCC_MCO2SOURCE_PLLR            (RCC_CFGR_MCO2SEL_0 | RCC_CFGR_MCO2SEL_2)                       /*!< PLLCLK selection as MCO2 source */
#define RCC_MCO2SOURCE_LSI             (RCC_CFGR_MCO2SEL_1 | RCC_CFGR_MCO2SEL_2)                       /*!< LSI selection as MCO2 source */
#define RCC_MCO2SOURCE_LSE             (RCC_CFGR_MCO2SEL_0 | RCC_CFGR_MCO2SEL_1 | RCC_CFGR_MCO2SEL_2)  /*!< LSE selection as MCO2 source */
#if defined(RCC_CRRCR_HSI48ON)
#define RCC_MCO2SOURCE_HSI48           RCC_CFGR_MCO2SEL_3                                              /*!< HSI48 selection as MCO2 source */
#endif /* RCC_CRRCR_HSI48ON */
#define RCC_MCO2SOURCE_RTC_ALT         (RCC_CFGR_MCO2SEL_0 | RCC_CFGR_MCO2SEL_3)                       /*!< RTC alternative clock selection as MCO2 source */
#define RCC_MCO2SOURCE_RTC_WAKEUP      (RCC_CFGR_MCO2SEL_1 | RCC_CFGR_MCO2SEL_3)                       /*!< RTC wakeup interrupt signal selection as MCO2 source */
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Prescaler MCO1 Clock Prescaler
  * @{
  */
#define RCC_MCO1DIV_1         (0x00000000U)                                                  /*!< MCO divided by 1 */
#define RCC_MCO1DIV_2         RCC_CFGR_MCO1PRE_0                                             /*!< MCO divided by 2 */
#define RCC_MCO1DIV_4         RCC_CFGR_MCO1PRE_1                                             /*!< MCO divided by 4 */
#define RCC_MCO1DIV_8         (RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0)                      /*!< MCO divided by 8 */
#define RCC_MCO1DIV_16        RCC_CFGR_MCO1PRE_2                                             /*!< MCO divided by 16 */
#define RCC_MCO1DIV_32        (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0)                      /*!< MCO divided by 32 */
#define RCC_MCO1DIV_64        (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1)                      /*!< MCO divided by 64 */
#define RCC_MCO1DIV_128       (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0) /*!< MCO divided by 128 */
#define RCC_MCO1DIV_256       RCC_CFGR_MCO1PRE_3                                             /*!< MCO divided by 256 */
#define RCC_MCO1DIV_512       (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_0)                      /*!< MCO divided by 512 */
#define RCC_MCO1DIV_1024      (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_1)                      /*!< MCO divided by 1024 */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Prescaler MCO2 Clock Prescaler
  * @{
  */
#define RCC_MCO2DIV_1         (0x00000000U)                                                  /*!< MCO divided by 1 */
#define RCC_MCO2DIV_2         RCC_CFGR_MCO2PRE_0                                             /*!< MCO divided by 2 */
#define RCC_MCO2DIV_4         RCC_CFGR_MCO2PRE_1                                             /*!< MCO divided by 4 */
#define RCC_MCO2DIV_8         (RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO divided by 8 */
#define RCC_MCO2DIV_16        RCC_CFGR_MCO2PRE_2                                             /*!< MCO divided by 16 */
#define RCC_MCO2DIV_32        (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO divided by 32 */
#define RCC_MCO2DIV_64        (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1)                      /*!< MCO divided by 64 */
#define RCC_MCO2DIV_128       (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO1PRE_0) /*!< MCO divided by 128 */
#define RCC_MCO2DIV_256       RCC_CFGR_MCO2PRE_3                                             /*!< MCO divided by 256 */
#define RCC_MCO2DIV_512       (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO divided by 512 */
#define RCC_MCO2DIV_1024      (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_1)                      /*!< MCO divided by 1024 */
/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                  RCC_CIFR_LSIRDYF      /*!< LSI Ready Interrupt flag */
#define RCC_IT_LSERDY                  RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt flag */
#define RCC_IT_MSIRDY                  RCC_CIFR_MSIRDYF      /*!< MSI Ready Interrupt flag */
#define RCC_IT_HSIRDY                  RCC_CIFR_HSIRDYF      /*!< HSI16 Ready Interrupt flag */
#define RCC_IT_HSERDY                  RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt flag */
#define RCC_IT_PLLRDY                  RCC_CIFR_PLLRDYF      /*!< PLL Ready Interrupt flag */
#define RCC_IT_CSS                     RCC_CIFR_CSSF         /*!< HSE Clock Security System Interrupt flag */
#define RCC_IT_LSECSS                  RCC_CIFR_LSECSSF      /*!< LSE Clock Security System Interrupt flag */
#if defined(RCC_CIFR_HSI48RDYF)
#define RCC_IT_HSI48RDY                RCC_CIFR_HSI48RDYF    /*!< HSI48 Ready Interrupt flag */
#endif /* RCC_CIFR_HSI48RDYF */

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
#define RCC_FLAG_MSIRDY           ((uint32_t)((CR_REG_INDEX << 5U) | RCC_CR_MSIRDY_Pos))        /*!< MSI Ready flag */
#define RCC_FLAG_HSIRDY           ((uint32_t)((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos))        /*!< HSI Ready flag */
#define RCC_FLAG_HSERDY           ((uint32_t)((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos))        /*!< HSE Ready flag */
#define RCC_FLAG_PLLRDY           ((uint32_t)((CR_REG_INDEX << 5U) | RCC_CR_PLLRDY_Pos))        /*!< PLL Ready flag */

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY           ((uint32_t)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos))    /*!< LSE Ready flag */
#define RCC_FLAG_LSECSSD          ((uint32_t)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSECSSD_Pos))   /*!< LSE Clock Security System Interrupt flag */
#define RCC_FLAG_LSESYSRDY        ((uint32_t)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSESYSRDY_Pos)) /*!< LSE clock ready to be used by the system */

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY           ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos))      /*!< LSI Ready flag */
#define RCC_FLAG_RMV              ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_RMVF_Pos))        /*!< Remove reset flag */
#define RCC_FLAG_OBLRST           ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_OBLRSTF_Pos))     /*!< Option byte loader reset flag */
#define RCC_FLAG_PINRST           ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos))     /*!< Pin reset flag */
#define RCC_FLAG_PWRRST           ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_PWRRSTF_Pos))     /*!< PWR reset flag */
#define RCC_FLAG_SFTRST           ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos))     /*!< Software reset flag */
#define RCC_FLAG_IWDGRST          ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos))    /*!< Independent window Watchdog reset flag */
#define RCC_FLAG_WWDGRST          ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos))    /*!< Window watchdog reset flag */
#define RCC_FLAG_LPWRRST          ((uint32_t)((CSR_REG_INDEX << 5U) | RCC_CSR_LPWRRSTF_Pos))    /*!< Low Power reset flag */
#if defined (RCC_CRRCR_HSI48ON)
#define RCC_FLAG_HSI48RDY         ((uint32_t)((CR_REG_INDEX << 5U)  | RCC_CR_HSI48RDY_Pos))     /*!< HSI48 Ready flag */
#endif /* RCC_CRRCR_HSI48ON */

/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_LOW                 (0x00000000U)           /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           RCC_BDCR_LSEDRV_0       /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          RCC_BDCR_LSEDRV_1       /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                RCC_BDCR_LSEDRV         /*!< LSE high drive capability */
/**
  * @}
  */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define RCC_RESET_FLAG_PIN             RCC_CSR_PINRSTF    /*!< PIN reset flag */
#define RCC_RESET_FLAG_PWR             RCC_CSR_PWRRSTF    /*!< BOR or POR/PDR reset flag */
#define RCC_RESET_FLAG_SW              RCC_CSR_SFTRSTF    /*!< Software Reset flag */
#define RCC_RESET_FLAG_IWDG            RCC_CSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define RCC_RESET_FLAG_WWDG            RCC_CSR_WWDGRSTF   /*!< Window watchdog reset flag */
#define RCC_RESET_FLAG_LPWR            RCC_CSR_LPWRRSTF   /*!< Low power reset flag */
#define RCC_RESET_FLAG_OBL             RCC_CSR_OBLRSTF    /*!< Option Byte Loader reset flag */
#define RCC_RESET_FLAG_ALL             (RCC_RESET_FLAG_PIN  | RCC_RESET_FLAG_PWR  | RCC_RESET_FLAG_SW   | \
                                        RCC_RESET_FLAG_IWDG | RCC_RESET_FLAG_WWDG | RCC_RESET_FLAG_LPWR | \
                                        RCC_RESET_FLAG_OBL)
/**
  * @}
  */

/** @defgroup RCC_Stop_WakeUpClock Wake-Up from STOP Clock
  * @{
  */
#define RCC_STOP_WAKEUPCLOCK_MSI       (0x00000000U)             /*!< MSI selection after wake-up from STOP */
#define RCC_STOP_WAKEUPCLOCK_HSI       RCC_CFGR_STOPWUCK         /*!< HSI selection after wake-up from STOP */
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enable_Disable AHB Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_DMA1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#if defined (DMA2)
#define __HAL_RCC_DMA2_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHBENR, RCC_AHBENR_DMA2EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA2EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* DMA2 */

#define __HAL_RCC_FLASH_CLK_ENABLE()              do { \
                                                       __IO uint32_t tmpreg; \
                                                       SET_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN); \
                                                       /* Delay after an RCC peripheral clock enabling */ \
                                                       tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN); \
                                                       UNUSED(tmpreg); \
                                                     } while(0)

#define __HAL_RCC_CRC_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_TSC_CLK_ENABLE()       do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHBENR, RCC_AHBENR_TSCEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_TSCEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_RNG_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->AHBENR, RCC_AHBENR_RNGEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_RNGEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#if defined (AES)
#define __HAL_RCC_AES_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->AHBENR, RCC_AHBENR_AESEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_AESEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* AES */

#define __HAL_RCC_DMA1_CLK_DISABLE()         CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN)
#if defined (DMA2)
#define __HAL_RCC_DMA2_CLK_DISABLE()         CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_DMA2EN)
#endif /* DMA2 */
#define __HAL_RCC_FLASH_CLK_DISABLE()        CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN)

#define __HAL_RCC_CRC_CLK_DISABLE()          CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)

#define __HAL_RCC_TSC_CLK_DISABLE()          CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_TSCEN)

#define __HAL_RCC_RNG_CLK_DISABLE()          CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_RNGEN)
#if defined (AES)
#define __HAL_RCC_AES_CLK_DISABLE()          CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_AESEN)
#endif /* AES */
/**
  * @}
  */

/** @defgroup RCC_IOPORT_Clock_Enable_Disable IOPORT Clock Enable Disable
  * @brief  Enable or disable the IO Ports clock.
  * @note   After reset, the IO ports clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_GPIOA_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_GPIOB_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_GPIOC_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_GPIOD_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#if defined (GPIOE)
#define __HAL_RCC_GPIOE_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOEEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOEEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)
#endif /* GPIOE */

#define __HAL_RCC_GPIOF_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_GPIOA_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN)
#define __HAL_RCC_GPIOB_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN)
#define __HAL_RCC_GPIOC_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN)
#define __HAL_RCC_GPIOD_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN)
#if defined (GPIOE)
#define __HAL_RCC_GPIOE_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOEEN)
#endif /* GPIOE */
#define __HAL_RCC_GPIOF_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN)

/**
  * @}
  */

/** @defgroup RCC_APB1_GRP1_Peripheral_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_TIM2_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_TIM3_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_TIM6_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM6EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM6EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_TIM7_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM7EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM7EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_LPUART2_CLK_ENABLE()          do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LPUART2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)
#if defined (LCD)
#define __HAL_RCC_LCD_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LCDEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LCDEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* LCD */
#define __HAL_RCC_RTCAPB_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)

#define __HAL_RCC_WWDG_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#if defined (LPUART3)
#define __HAL_RCC_LPUART3_CLK_ENABLE()          do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LPUART3EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART3EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)
#endif /* LPUART3 */
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_USBEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_USBEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)
#endif /* USB_DRD_FS */
#define __HAL_RCC_SPI2_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_SPI3_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#if defined(CRS)
#define __HAL_RCC_CRS_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* CRS */
#define __HAL_RCC_USART2_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_USART3_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_USART3EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_USART3EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_USART4_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_USART4EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_USART4EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_LPUART1_CLK_ENABLE()          do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_I2C1_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_I2C2_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_I2C3_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C3EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C3EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_OPAMP_CLK_ENABLE()            do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_OPAMPEN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_OPAMPEN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C4EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C4EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* I2C4 */
#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM3EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM3EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* LPTIM3 */
#define __HAL_RCC_PWR_CLK_ENABLE()              do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_PWREN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)

#define __HAL_RCC_DAC1_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)

#define __HAL_RCC_LPTIM2_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_LPTIM1_CLK_ENABLE()           do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)

#define __HAL_RCC_TIM2_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN)

#define __HAL_RCC_TIM3_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)

#define __HAL_RCC_TIM6_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM6EN)

#define __HAL_RCC_TIM7_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM7EN)

#define __HAL_RCC_LPUART2_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPUART2EN)

#if defined (LCD)
#define __HAL_RCC_LCD_CLK_DISABLE()             CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LCDEN)
#endif /* LCD */

#define __HAL_RCC_RTCAPB_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN)

#define __HAL_RCC_WWDG_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPUART3EN)
#endif /* LPUART3 */
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_DISABLE()             CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_USBEN)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN)

#define __HAL_RCC_SPI3_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN)
#if defined(CRS)
#define __HAL_RCC_CRS_CLK_DISABLE()             CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN)
#endif /* CRS */
#define __HAL_RCC_USART2_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN)

#define __HAL_RCC_USART3_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_USART3EN)

#define __HAL_RCC_USART4_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_USART4EN)

#define __HAL_RCC_LPUART1_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN)

#define __HAL_RCC_I2C1_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)

#define __HAL_RCC_I2C2_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN)

#define __HAL_RCC_I2C3_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C3EN)

#define __HAL_RCC_OPAMP_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_OPAMPEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C4EN)
#endif /* I2C4 */
#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM3EN)
#endif /* LPTIM3 */
#define __HAL_RCC_PWR_CLK_DISABLE()             CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)

#define __HAL_RCC_DAC1_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN)

#define __HAL_RCC_LPTIM2_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM2EN)

#define __HAL_RCC_LPTIM1_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN)

/**
  * @}
  */

/** @defgroup RCC_APB_Peripheral_Clock_Enable_Disable APB Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_SYSCFG_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_COMP_CLK_ENABLE()          __HAL_RCC_SYSCFG_CLK_ENABLE()

#define __HAL_RCC_VREFBUF_CLK_ENABLE()       __HAL_RCC_SYSCFG_CLK_ENABLE()

#define __HAL_RCC_TIM1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_SPI1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_USART1_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_TIM15_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM15EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM15EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_TIM16_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_ADC_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_SYSCFG_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN)

#define __HAL_RCC_COMP_CLK_DISABLE()           __HAL_RCC_SYSCFG_CLK_DISABLE()

#define __HAL_RCC_VREFBUF_CLK_DISABLE()        __HAL_RCC_SYSCFG_CLK_DISABLE()

#define __HAL_RCC_TIM1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)

#define __HAL_RCC_SPI1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)

#define __HAL_RCC_USART1_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN)

#define __HAL_RCC_TIM15_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM15EN)

#define __HAL_RCC_TIM16_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)

#define __HAL_RCC_ADC_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)

/**
  * @}
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enable_Disable_Status AHB Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_DMA1_IS_CLK_ENABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN) != 0U)

#if defined (DMA2)
#define __HAL_RCC_DMA2_IS_CLK_ENABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA2EN) != 0U)
#endif  /*DMA2 */

#define __HAL_RCC_FLASH_IS_CLK_ENABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN) != 0U)

#define __HAL_RCC_CRC_IS_CLK_ENABLED()          (READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN) != 0U)

#if defined (AES)
#define __HAL_RCC_AES_IS_CLK_ENABLED()          (READ_BIT(RCC->AHBENR, RCC_AHBENR_AESEN) != 0U)
#endif /* AES */

#define __HAL_RCC_RNG_IS_CLK_ENABLED()          (READ_BIT(RCC->AHBENR, RCC_AHBENR_RNGEN) != 0U)

#define __HAL_RCC_TSC_IS_CLK_ENABLED()          (READ_BIT(RCC->AHBENR, RCC_AHBENR_TSCEN) != 0U)

#define __HAL_RCC_DMA1_IS_CLK_DISABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN) == 0U)

#if defined (DMA2)
#define __HAL_RCC_DMA2_IS_CLK_DISABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA2EN) == 0U)
#endif /* DMA2 */

#define __HAL_RCC_FLASH_IS_CLK_DISABLED()       (READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN) == 0U)

#define __HAL_RCC_CRC_IS_CLK_DISABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN) == 0U)

#define __HAL_RCC_TSC_IS_CLK_DISABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_TSCEN) == 0U)

#define __HAL_RCC_RNG_IS_CLK_DISABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_RNGEN) == 0U)

#if defined (AES)
#define __HAL_RCC_AES_IS_CLK_DISABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_AESEN) == 0U)
#endif /* AES */

/**
  * @}
  */

/** @defgroup RCC__Peripheral_Clock_Enable_Disable_Status APB Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN) != 0U)

#define __HAL_RCC_TIM3_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN) != 0U)

#define __HAL_RCC_TIM6_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM6EN) != 0U)

#define __HAL_RCC_TIM7_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM7EN) != 0U)

#define __HAL_RCC_LPUART2_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART2EN) != 0U)

#if defined (LCD)
#define __HAL_RCC_LCD_IS_CLK_ENABLED()             (READ_BIT(RCC->APBENR1, RCC_APBENR1_LCDEN) != 0U)
#endif /* LCD */

#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN) != 0U)

#define __HAL_RCC_WWDG_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN) != 0U)

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART3EN) != 0U)
#endif /* LPUART3 */

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_IS_CLK_ENABLED()             (READ_BIT(RCC->APBENR1, RCC_APBENR1_USBEN) != 0U)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN) != 0U)

#define __HAL_RCC_SPI3_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN) != 0U)
#if defined(CRS)
#define __HAL_RCC_CRS_IS_CLK_ENABLED()             (READ_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN) != 0U)
#endif /* CRS */
#define __HAL_RCC_USART2_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN) != 0U)

#define __HAL_RCC_USART3_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART3EN) != 0U)

#define __HAL_RCC_USART4_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART4EN) != 0U)

#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN) != 0U)

#define __HAL_RCC_I2C1_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN) != 0U)

#define __HAL_RCC_I2C2_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN) != 0U)

#define __HAL_RCC_I2C3_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C3EN) != 0U)

#define __HAL_RCC_OPAMP_IS_CLK_ENABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_OPAMPEN) != 0U)
#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C4EN) != 0U)
#endif /* I2C4 */
#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM3EN) != 0U)
#endif /* LPTIM3 */

#define __HAL_RCC_PWR_IS_CLK_ENABLED()             (READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN) != 0U)

#define __HAL_RCC_DAC1_IS_CLK_ENABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN) != 0U)

#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM2EN) != 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1y_LPTIM1EN) != 0U)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN) == 0U)

#define __HAL_RCC_TIM3_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN) == 0U)

#define __HAL_RCC_TIM6_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM6EN) == 0U)

#define __HAL_RCC_TIM7_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM7EN) == 0U)

#define __HAL_RCC_LPUART2_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART2EN) == 0U)

#if defined (LCD)
#define __HAL_RCC_LCD_IS_CLK_DISABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_LCDEN) == 0U)
#endif /* LCD */

#define __HAL_RCC_RTCAPB_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN) == 0U)

#define __HAL_RCC_WWDG_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN) == 0U)

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART3EN) == 0U)
#endif /* LPUART3 */

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_IS_CLK_DISABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_USBEN) == 0U)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN) == 0U)

#define __HAL_RCC_SPI3_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI3EN) == 0U)

#define __HAL_RCC_CRS_IS_CLK_DISABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN) == 0U)

#define __HAL_RCC_USART2_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN) == 0U)

#define __HAL_RCC_USART3_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART3EN) == 0U)

#define __HAL_RCC_USART4_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART4EN) == 0U)

#define __HAL_RCC_LPUART1_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPUART1EN) == 0U)

#define __HAL_RCC_I2C1_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN) == 0U)

#define __HAL_RCC_I2C2_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN) == 0U)

#define __HAL_RCC_I2C3_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C3EN) == 0U)

#define __HAL_RCC_OPAMP_IS_CLK_DISABLED()          (READ_BIT(RCC->APBENR1, RCC_APBENR1_OPAMPEN) == 0U)

#define __HAL_RCC_I2C4_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C4EN) == 0U)

#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM3EN) == 0U)
#endif /* LPTIM3 */

#define __HAL_RCC_PWR_IS_CLK_DISABLED()            (READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN) == 0U)

#define __HAL_RCC_DAC1_IS_CLK_DISABLED()           (READ_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN) == 0U)

#define __HAL_RCC_LPTIM2_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM2EN) == 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_DISABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_LPTIM1EN) == 0U)
/**
  * @}
  */

/** @defgroup RCC_APB_2_Peripheral_Clock_Enable_Disable_Status APB_2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB_2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN) != 0U)

#define __HAL_RCC_COMP_IS_CLK_DISABLED()       __HAL_RCC_SYSCFG_IS_CLK_DISABLED()

#define __HAL_RCC_VREFBUF_IS_CLK_DISABLED()    __HAL_RCC_SYSCFG_IS_CLK_DISABLED()

#define __HAL_RCC_TIM1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)   != 0U)

#define __HAL_RCC_SPI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)   != 0U)

#define __HAL_RCC_USART1_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN) != 0U)

#define __HAL_RCC_TIM15_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM15EN)   != 0U)

#define __HAL_RCC_TIM16_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)  != 0U)

#define __HAL_RCC_ADC_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)    != 0U)

#define __HAL_RCC_COMP_IS_CLK_ENABLED()        __HAL_RCC_SYSCFG_IS_CLK_ENABLED()

#define __HAL_RCC_VREFBUF_IS_CLK_ENABLED()     __HAL_RCC_SYSCFG_IS_CLK_ENABLED()

#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN) == 0U)

#define __HAL_RCC_TIM1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)   == 0U)

#define __HAL_RCC_SPI1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)   == 0U)

#define __HAL_RCC_USART1_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN) == 0U)

#define __HAL_RCC_TIM15_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM15EN)   == 0U)

#define __HAL_RCC_TIM16_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)  == 0U)

#define __HAL_RCC_ADC_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)    == 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB_Force_Release_Reset AHB Peripheral Force Release Reset
  * @brief  Force or release AHB peripheral reset.
  * @{
  */

#define __HAL_RCC_AHB_FORCE_RESET()     do { \
                                                 WRITE_REG(RCC->AHBRSTR, 0xFFFFFFFFU); \
                                               } while(0)

#define __HAL_RCC_DMA1_FORCE_RESET()          SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMA1RST)

#if defined (DMA2)
#define __HAL_RCC_DMA2_FORCE_RESET()          SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMA2RST)
#endif /* DMA2 */

#define __HAL_RCC_FLASH_FORCE_RESET()         SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_FLASHRST)

#define __HAL_RCC_CRC_FORCE_RESET()           SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_CRCRST)

#if defined (AES)
#define __HAL_RCC_AES_FORCE_RESET()           SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_AESRST)
#endif /* AES */

#define __HAL_RCC_RNG_FORCE_RESET()           SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_RNGRST)

#define __HAL_RCC_TSC_FORCE_RESET()           SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_TSCRST)

#define __HAL_RCC_AHB_RELEASE_RESET()     do { \
                                                 WRITE_REG(RCC->AHBRSTR, 0x00000000U); \
                                               } while(0)

#define __HAL_RCC_DMA1_RELEASE_RESET()          CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMA1RST)

#if defined (DMA2)
#define __HAL_RCC_DMA2_RELEASE_RESET()          CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMA2RST)
#endif /* DMA2 */

#define __HAL_RCC_FLASH_RELEASE_RESET()         CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_FLASHRST)

#define __HAL_RCC_CRC_RELEASE_RESET()           CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_CRCRST)

#define __HAL_RCC_TSC_RELEASE_RESET()           CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_TSCRST)

#define __HAL_RCC_RNG_RELEASE_RESET()           CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_RNGRST)

#if defined (AES)
#define __HAL_RCC_AES_RELEASE_RESET()           CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_AESRST)
#endif /* AES */

/**
  * @}
  */

/** @defgroup RCC_IOPRSTR_Force_Release_Reset IO Peripheral Force Release Reset
  * @brief  Force or release IO peripheral reset.
  * @{
  */

#define __HAL_RCC_IOP_FORCE_RESET()     do { \
                                                 WRITE_REG(RCC->IOPRSTR, 0xFFFFFFFFU); \
                                               } while(0)

#define __HAL_RCC_GPIOA_FORCE_RESET()         SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOARST)

#define __HAL_RCC_GPIOB_FORCE_RESET()         SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOBRST)

#define __HAL_RCC_GPIOC_FORCE_RESET()         SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOCRST)

#define __HAL_RCC_GPIOD_FORCE_RESET()         SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIODRST)

#if defined(GPIOE)
#define __HAL_RCC_GPIOE_FORCE_RESET()         SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOERST)
#endif /* GPIOE */

#define __HAL_RCC_GPIOF_FORCE_RESET()         SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOFRST)

#define __HAL_RCC_IOP_RELEASE_RESET()     do { \
                                                 WRITE_REG(RCC->IOPRSTR, 0x00000000U); \
                                               } while(0)

#define __HAL_RCC_GPIOA_RELEASE_RESET()       CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOARST)

#define __HAL_RCC_GPIOB_RELEASE_RESET()       CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOBRST)

#define __HAL_RCC_GPIOC_RELEASE_RESET()       CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOCRST)

#define __HAL_RCC_GPIOD_RELEASE_RESET()       CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIODRST)

#if defined(GPIOE)
#define __HAL_RCC_GPIOE_RELEASE_RESET()       CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOERST)
#endif /* GPIOE */

#define __HAL_RCC_GPIOF_RELEASE_RESET()       CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOFRST)

/**
  * @}
  */

/** @defgroup RCC_APB_GRP1_Force_Release_Reset APB1_GRP1 Peripheral Force Release Reset
  * @brief  Force or release APB peripheral reset.
  * @{
  */

#define __HAL_RCC_APB1_GRP1_FORCE_RESET()     do { \
                                                   WRITE_REG(RCC->APBRSTR1, 0xFFFFFFFFU); \
                                                 } while(0)

#define __HAL_RCC_TIM2_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM2RST)

#define __HAL_RCC_TIM3_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM3RST)

#define __HAL_RCC_TIM6_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM6RST)

#define __HAL_RCC_TIM7_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM7RST)

#define __HAL_RCC_LPUART2_FORCE_RESET()       SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART2RST)

#if defined (LCD)
#define __HAL_RCC_LCD_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LCDRST)
#endif /* LCD */

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_FORCE_RESET()       SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART3RST)
#endif /* LPUART3 */

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USBRST)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI2RST)

#define __HAL_RCC_SPI3_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI3RST)
#if defined(CRS)
#define __HAL_RCC_CRS_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_CRSRST)
#endif /* CRS */
#define __HAL_RCC_USART2_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART2RST)

#define __HAL_RCC_USART3_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART3RST)

#define __HAL_RCC_USART4_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART4RST)

#define __HAL_RCC_LPUART1_FORCE_RESET()       SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART1RST)

#define __HAL_RCC_I2C1_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C1RST)

#define __HAL_RCC_I2C2_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C2RST)

#define __HAL_RCC_I2C3_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C3RST)

#define __HAL_RCC_OPAMP_FORCE_RESET()         SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_OPAMPRST)
#if defined(I2C4)
#define __HAL_RCC_I2C4_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C4RST)
#endif /* I2C4 */
#define __HAL_RCC_PWR_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_PWRRST)

#define __HAL_RCC_DAC1_FORCE_RESET()          SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_DAC1RST)

#define __HAL_RCC_LPTIM2_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM2RST)

#define __HAL_RCC_LPTIM1_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM1RST)
#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_FORCE_RESET()        SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM3RST)
#endif /* LPTIM3 */
#define __HAL_RCC_APB1_GRP1_RELEASE_RESET()     do { \
                                                     WRITE_REG(RCC->APBRSTR1, 0x00000000U); \
                                                   } while(0)

#define __HAL_RCC_TIM2_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM2RST)

#define __HAL_RCC_TIM3_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM3RST)

#define __HAL_RCC_TIM6_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM6RST)

#define __HAL_RCC_TIM7_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM7RST)

#define __HAL_RCC_LPUART2_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART2RST)

#if defined (LCD)
#define __HAL_RCC_LCD_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LCDRST)
#endif /* LCD */

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART3RST)
#endif /* LPUART3 */

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USBRST)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI2RST)

#define __HAL_RCC_SPI3_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI3RST)

#if defined(CRS)
#define __HAL_RCC_CRS_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_CRSRST)
#endif /* CRS */

#define __HAL_RCC_USART2_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART2RST)

#define __HAL_RCC_USART3_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART3RST)

#define __HAL_RCC_USART4_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART4RST)

#define __HAL_RCC_LPUART1_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPUART1RST)

#define __HAL_RCC_I2C1_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C1RST)

#define __HAL_RCC_I2C2_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C2RST)

#define __HAL_RCC_I2C3_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C3RST)

#define __HAL_RCC_OPAMP_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_OPAMPRST)

#define __HAL_RCC_I2C4_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C4RST)

#define __HAL_RCC_PWR_RELEASE_RESET()           CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_PWRRST)

#define __HAL_RCC_DAC1_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_DAC1RST)

#define __HAL_RCC_LPTIM2_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM2RST)

#define __HAL_RCC_LPTIM1_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM1RST)

#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_LPTIM3RST)
#endif /* LPTIM3 */
/**
  * @}
  */

/** @defgroup RCC_APB_GRP2_Force_Release_Reset APB1_GRP2 Peripheral Force Release Reset
  * @brief  Force or release APB_2 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB1_GRP2_FORCE_RESET()          WRITE_REG(RCC->APBRSTR2, 0xFFFFFFFFU)

#define __HAL_RCC_SYSCFG_FORCE_RESET()         SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SYSCFGRST)

#define __HAL_RCC_COMP_FORCE_RESET()           __HAL_RCC_SYSCFG_FORCE_RESET()

#define __HAL_RCC_VREFBUF_FORCE_RESET()        __HAL_RCC_SYSCFG_FORCE_RESET()

#define __HAL_RCC_TIM1_FORCE_RESET()           SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM1RST)

#define __HAL_RCC_SPI1_FORCE_RESET()           SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SPI1RST)

#define __HAL_RCC_USART1_FORCE_RESET()         SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_USART1RST)

#define __HAL_RCC_TIM15_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM15RST)

#define __HAL_RCC_TIM16_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM16RST)

#define __HAL_RCC_ADC_FORCE_RESET()            SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST)

#define __HAL_RCC_APB1_GRP2_RELEASE_RESET()        WRITE_REG(RCC->APBRSTR2, 0x00000000U)

#define __HAL_RCC_SYSCFG_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SYSCFGRST)

#define __HAL_RCC_COMP_RELEASE_RESET()         __HAL_RCC_SYSCFG_RELEASE_RESET()

#define __HAL_RCC_VREFBUF_RELEASE_RESET()      __HAL_RCC_SYSCFG_RELEASE_RESET()

#define __HAL_RCC_TIM1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM1RST)

#define __HAL_RCC_SPI1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SPI1RST)

#define __HAL_RCC_USART1_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_USART1RST)

#define __HAL_RCC_TIM15_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM15RST)

#define __HAL_RCC_TIM16_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM16RST)

#define __HAL_RCC_ADC_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST)

/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Sleep_Enable_Disable AHB1_GRP1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()           SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA1SMEN)

#if defined (DMA2)
#define __HAL_RCC_DMA2_CLK_SLEEP_ENABLE()           SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA2SMEN)
#endif /* DMA2 */

#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_FLASHSMEN)

#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()          SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_SRAM1SMEN)

#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()            SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_CRCSMEN)

#if defined (AES)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()            SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_AESSMEN)
#endif /* AES */

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()            SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_RNGSMEN)

#define __HAL_RCC_TSC_CLK_SLEEP_ENABLE()            SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_TSCSMEN)

#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()          CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA1SMEN)

#if defined (DMA2)
#define __HAL_RCC_DMA2_CLK_SLEEP_DISABLE()          CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA2SMEN)
#endif /* DMA2 */

#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_FLASHSMEN)

#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_SRAM1SMEN)

#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_CRCSMEN)

#if defined (AES)
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_AESSMEN)
#endif /* AES */

#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_RNGSMEN)

#define __HAL_RCC_TSC_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_TSCSMEN)

/**
  * @}
  */

/** @defgroup RCC_IOPORT_Clock_Sleep_Enable_Disable IOPORT Clock Sleep Enable Disable
  * @brief  Enable or disable the IOPORT clock during Low Power (Sleep) mode.
  * @note   IOPORT clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()          SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOASMEN)

#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()          SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOBSMEN)

#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()          SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOCSMEN)

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()          SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIODSMEN)

#if defined (GPIOE)
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()          SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOESMEN)
#endif /* GPIOE */

#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()          SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOFSMEN)

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOASMEN)

#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOBSMEN)

#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOCSMEN)

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIODSMEN)

#if defined (GPIOE)
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOESMEN)
#endif /* GPIOE */

#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOFSMEN)

/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Sleep_Enable_Disable APB Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM2SMEN)

#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM3SMEN)

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM6SMEN)

#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM7SMEN)

#define __HAL_RCC_LPUART2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPUART2SMEN)

#if defined (LCD)
#define __HAL_RCC_LCD_CLK_SLEEP_ENABLE()            SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LCDSMEN)
#endif /* LCD */

#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_RTCAPBSMEN)

#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_WWDGSMEN)

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPUART3SMEN)
#endif /* LPUART3 */

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_SLEEP_ENABLE()            SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USBSMEN)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI2SMEN)

#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI3SMEN)
#if defined(CRS)
#define __HAL_RCC_CRS_CLK_SLEEP_ENABLE()            SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_CRSSMEN)
#endif /* CRS */
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN)

#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART3SMEN)

#define __HAL_RCC_USART4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART4SMEN)

#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPUART1SMEN)

#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN)

#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN)

#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C3SMEN)

#define __HAL_RCC_OPAMP_CLK_SLEEP_ENABLE()          SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_OPAMPSMEN)
#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C4SMEN)
#endif /* I2C4 */
#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPTIM3SMEN)
#endif /* LPTIM3 */

#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()            SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_PWRSMEN)

#define __HAL_RCC_DAC1_CLK_SLEEP_ENABLE()           SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_DAC1SMEN)

#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPTIM2SMEN)

#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPTIM1SMEN)

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM2SMEN)

#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM3SMEN)

#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM6SMEN)

#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM7SMEN)

#define __HAL_RCC_LPUART2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPUART2SMEN)

#if defined (LCD)
#define __HAL_RCC_LCD_CLK_SLEEP_DISABLE()            CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LCDSMEN)
#endif /* LCD */

#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_RTCAPBSMEN)

#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_WWDGSMEN)

#if defined (LPUART3)
#define __HAL_RCC_LPUART3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPUART3SMEN)
#endif /* LPUART3 */

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_SLEEP_DISABLE()            CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USBSMEN)
#endif /* USB_DRD_FS */

#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI2SMEN)

#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI3SMEN)

#if defined(CRS)
#define __HAL_RCC_CRS_CLK_SLEEP_DISABLE()            CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_CRSSMEN)
#endif /* CRS */

#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN)

#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART3SMEN)

#define __HAL_RCC_USART4_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART4SMEN)

#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPUART1SMEN)

#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN)

#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN)

#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C3SMEN)

#define __HAL_RCC_OPAMP_CLK_SLEEP_DISABLE()          CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_OPAMPSMEN)

#define __HAL_RCC_I2C4_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C4SMEN)

#if defined (LPTIM3)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPTIM3SMEN)
#endif /* LPTIM3 */
#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()            CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_PWRSMEN)

#define __HAL_RCC_DAC1_CLK_SLEEP_DISABLE()           CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_DAC1SMEN)

#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPTIM2SMEN)

#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_LPTIM1SMEN)

/**
  * @}
  */

/** @defgroup RCC_APB1_GRP2_Clock_Sleep_Enable_Disable APB1_GRP2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SYSCFGSMEN)
#define __HAL_RCC_COMP_CLK_SLEEP_ENABLE()      __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()
#define __HAL_RCC_VREFBUF_CLK_SLEEP_ENABLE()   __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM1SMEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SPI1SMEN)
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_USART1SMEN)
#define __HAL_RCC_TIM15_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM15SMEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM16SMEN)
#define __HAL_RCC_ADC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_ADCSMEN)

#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SYSCFGSMEN)
#define __HAL_RCC_COMP_CLK_SLEEP_DISABLE()     __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()
#define __HAL_RCC_VREFBUF_CLK_SLEEP_DISABLE()  __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()
#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM1SMEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SPI1SMEN)
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_USART1SMEN)
#define __HAL_RCC_TIM15_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM15SMEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM16SMEN)
#define __HAL_RCC_ADC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_ADCSMEN)

/**
  * @}
  */

/** @defgroup RCC_DBGMCU Enable , Disable , Force_Reset and Release_Reset
  * @brief  Enable or Disable, Force or Release DBGMCU.
  * @{
  */
#define __HAL_RCC_DBGMCU_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_DBGMCU_IS_CLK_ENABLED()      (READ_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN) != 0U)

#define __HAL_RCC_DBGMCU_CLK_DISABLE()         CLEAR_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN)

#define __HAL_RCC_DBGMCU_IS_CLK_DISABLED()     (READ_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN) == 0U)

#define __HAL_RCC_DBGMCU_FORCE_RESET()         SET_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGRST)

#define __HAL_RCC_DBGMCU_RELEASE_RESET()       CLEAR_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGRST)

/**
  * @}
  */

/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief  Macros to force or release the Vswitch Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @note   The BKPSRAM is not affected by this reset.
  * @retval None
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   SET_BIT(RCC->BDCR, RCC_BDCR_BDRST)

#define __HAL_RCC_BACKUPRESET_RELEASE() CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST)

/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Configuration RCC RTC Clock Configuration
  * @{
  */

/** @brief  Macros to enable or disable the RTC clock.
  * @note   As the RTC is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the RTC
  *         (to be done once after reset).
  * @note   These macros must be used after the RTC clock source was selected.
  * @retval None
  */
#define __HAL_RCC_RTC_ENABLE()         SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

#define __HAL_RCC_RTC_DISABLE()        CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

/**
  * @}
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
#define __HAL_RCC_HSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSION)

#define __HAL_RCC_HSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macro to adjust the Internal High Speed 16MHz oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 127.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__) \
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, (__HSICALIBRATIONVALUE__) << RCC_ICSCR_HSITRIM_Pos)

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI startup time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI_STOP_ENABLE()     SET_BIT(RCC->CR, RCC_CR_HSIKERON)

#define __HAL_RCC_HSI_STOP_DISABLE()    CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON)

/**
  * @brief    Macros to enable or disable the wakeup the Internal High Speed oscillator (HSI)
  *           in parallel to the Internal Multi Speed oscillator (MSI) used at system wakeup.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI_AUTOMATIC_START_ENABLE()   SET_BIT(RCC->CR, RCC_CR_HSIASFS)

#define __HAL_RCC_HSI_AUTOMATIC_START_DISABLE()  CLEAR_BIT(RCC->CR, RCC_CR_HSIASFS)

/**
  * @brief  Macros to enable or disable the Internal Multi Speed oscillator (MSI).
  * @note     The MSI is stopped by hardware when entering STOP and STANDBY modes.
  *           It is used (enabled by hardware) as system clock source after
  *           startup from Reset, wakeup from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly or indirectly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     MSI can not be stopped if it is used as system clock source.
  *           In this case, you have to select another source of the system
  *           clock then stop the MSI.
  * @note     After enabling the MSI, the application software should wait on
  *           MSIRDY flag to be set indicating that MSI clock is stable and can
  *           be used as system clock source.
  * @note   When the MSI is stopped, MSIRDY flag goes low after 6 MSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_MSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_MSION)

#define __HAL_RCC_MSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_MSION)

/** @brief  Macro Adjusts the Internal Multi Speed oscillator (MSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal MSI RC.
  *         Refer to the Application Note AN3300 for more details on how to
  *         calibrate the MSI.
  * @param  __MSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_MSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 255.
  * @retval None
  */
#define __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(__MSICALIBRATIONVALUE__) \
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, (__MSICALIBRATIONVALUE__) << RCC_ICSCR_MSITRIM_Pos)

/**
  * @brief  Macro configures the Internal Multi Speed oscillator (MSI) clock range in run mode
  * @note     After restart from Reset , the MSI clock is around 4 MHz.
  *           After stop the startup clock can be MSI (at any of its possible
  *           frequencies, the one that was used before entering stop mode) or HSI.
  *          After Standby its frequency can be selected between 4 possible values
  *          (1, 2, 4 or 8 MHz).
  * @note     MSISRANGE can be modified when MSI is OFF (MSION=0) or when MSI is ready
  *          (MSIRDY=1).
  * @note    The MSI clock range after reset can be modified on the fly.
  * @param  __MSIRANGEVALUE__: specifies the MSI clock range.
  *         This parameter must be one of the following values:
  *            @arg @ref RCC_MSIRANGE_0  MSI clock is around 48 MHz
  *            @arg @ref RCC_MSIRANGE_1  MSI clock is around 24 MHz
  *            @arg @ref RCC_MSIRANGE_2  MSI clock is around 16 MHz
  *            @arg @ref RCC_MSIRANGE_3  MSI clock is around 12 MHz
  *            @arg @ref RCC_MSIRANGE_4  MSI clock is around 4 MHz (default after Reset)
  *            @arg @ref RCC_MSIRANGE_5  MSI clock is around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  MSI clock is around 1.5 MHz
  *            @arg @ref RCC_MSIRANGE_7  MSI clock is around 1 MHz
  *            @arg @ref RCC_MSIRANGE_8  MSI clock is around 400 KHz
  *            @arg @ref RCC_MSIRANGE_9  MSI clock is around 200 KHz
  *            @arg @ref RCC_MSIRANGE_10  MSI clock is around 150 KHz
  *            @arg @ref RCC_MSIRANGE_11  MSI clock is around 100 KHz
  * @retval None
  */
#define __HAL_RCC_MSI_RANGE_CONFIG(__MSIRANGEVALUE__) \
  do {                                                         \
    SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);                         \
    MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, (__MSIRANGEVALUE__)); \
  } while(0)

/**
  * @brief  Macro configures the Internal Multi Speed oscillator (MSI) clock range after Standby mode
  *         After Standby its frequency can be selected between 4 possible values (1, 2, 4 or 8 MHz).
  * @param  __MSISRANGEVALUE__ specifies the MSI clock range.
  *         This parameter must be one of the following values:
  *            @arg @ref RCC_MSIRANGE_4  MSI clock is around 1 MHz
  *            @arg @ref RCC_MSIRANGE_5  MSI clock is around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  MSI clock is around 4 MHz (default after Reset)
  *            @arg @ref RCC_MSIRANGE_7  MSI clock is around 8 MHz
  * @retval None
  */
#define __HAL_RCC_MSI_STANDBY_RANGE_CONFIG(__MSISRANGEVALUE__) \
  MODIFY_REG(RCC->CSR, RCC_CSR_MSISTBYRG, (__MSISRANGEVALUE__) << 4U)

/** @brief  Macro to get the Internal Multi Speed oscillator (MSI) clock range in run mode
  * @retval MSI clock range.
  *         This parameter must be one of the following values:
  *            @arg @ref RCC_MSIRANGE_0  MSI clock is around 100 KHz
  *            @arg @ref RCC_MSIRANGE_1  MSI clock is around 200 KHz
  *            @arg @ref RCC_MSIRANGE_2  MSI clock is around 400 KHz
  *            @arg @ref RCC_MSIRANGE_3  MSI clock is around 800 KHz
  *            @arg @ref RCC_MSIRANGE_4  MSI clock is around 1 MHz
  *            @arg @ref RCC_MSIRANGE_5  MSI clock is around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  MSI clock is around 4 MHz (default after Reset)
  *            @arg @ref RCC_MSIRANGE_7  MSI clock is around 8 MHz
  *            @arg @ref RCC_MSIRANGE_8  MSI clock is around 16 MHz
  *            @arg @ref RCC_MSIRANGE_9  MSI clock is around 24 MHz
  *            @arg @ref RCC_MSIRANGE_10  MSI clock is around 32 MHz
  *            @arg @ref RCC_MSIRANGE_11  MSI clock is around 48 MHz
  */
#define __HAL_RCC_GET_MSI_RANGE()                              \
  ((READ_BIT(RCC->CR, RCC_CR_MSIRGSEL) != 0U) ?                \
   READ_BIT(RCC->CR, RCC_CR_MSIRANGE) :                        \
   (READ_BIT(RCC->CSR, RCC_CSR_MSISTBYRG) >> 4U))

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         SET_BIT(RCC->CSR, RCC_CSR_LSION)

#define __HAL_RCC_LSI_DISABLE()        CLEAR_BIT(RCC->CSR, RCC_CSR_LSION)

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this macro. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function reset the CSSON bit, so if the clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  __STATE__: specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS  HSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                      \
  do {                                                       \
    if((__STATE__) == RCC_HSE_ON)                            \
    {                                                        \
      SET_BIT(RCC->CR, RCC_CR_HSEON);                        \
    }                                                        \
    else if((__STATE__) == RCC_HSE_BYPASS)                   \
    {                                                        \
      SET_BIT(RCC->CR, (RCC_CR_HSEBYP | RCC_CR_HSEON));      \
    }                                                        \
    else                                                     \
    {                                                        \
      CLEAR_BIT(RCC->CR, (RCC_CR_HSEON | RCC_CR_HSEBYP));    \
    }                                                        \
  } while(0)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__ specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON_RTC_ONLY      Turn ON the LSE oscillator to be used only for RTC.
  *            @arg @ref RCC_LSE_ON               Turn ON the LSE oscillator to be used by any peripheral.
  *            @arg @ref RCC_LSE_BYPASS_RTC_ONLY  LSE oscillator bypassed with external clock to be used only for RTC.
  *            @arg @ref RCC_LSE_BYPASS           LSE oscillator bypassed with external clock
                                                  to be used by any peripheral.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)                                \
  do {                                                                 \
    if((__STATE__) == RCC_LSE_ON_RTC_ONLY)                             \
    {                                                                  \
      SET_BIT(RCC->BDCR,RCC_BDCR_LSEON);                               \
    }                                                                  \
    else if((__STATE__) == RCC_LSE_ON)                                 \
    {                                                                  \
      SET_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN));        \
    }                                                                  \
    else if((__STATE__) == RCC_LSE_BYPASS_RTC_ONLY)                    \
    {                                                                  \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                             \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);                              \
    }                                                                  \
    else if((__STATE__) == RCC_LSE_BYPASS)                             \
    {                                                                  \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                             \
      SET_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN));        \
    }                                                                  \
    else                                                               \
    {                                                                  \
      CLEAR_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN));      \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                           \
    }                                                                  \
  } while(0)

/** @brief  Macro to set Low-speed clock (LSI) divider.
  * @note   This bit can be written only when the LSI is disabled (LSION = 0 and LSIRDY = 0).
  *         The LSIPREDIV cannot be changed if the LSI is used by the IWDG or by the RTC.
  *
  * @param  __DIVIDER__ : specifies the divider value
  *          This parameter can be one of the following values
  *          @arg @ref RCC_LSI_DIV1
  *          @arg @ref RCC_LSI_DIV128
  * @retval None
  */
#define __HAL_RCC_LSI_DIV_CONFIG(__DIVIDER__)  \
  do {                                         \
    if((__DIVIDER__) == RCC_LSI_DIV128)        \
    {                                          \
      SET_BIT(RCC->CSR, RCC_CSR_LSIPREDIV);  \
    }                                          \
    else                                       \
    {                                          \
      CLEAR_BIT(RCC->CSR, RCC_CSR_LSIPREDIV);\
    }                                          \
  } while(0)
#if defined(RCC_CRRCR_HSI48ON)
/** @brief  Macros to enable or disable the RC 48MHz oscillator (RC48).
  * @note   The RC48 is stopped by hardware when entering STOP and STANDBY modes.
  * @note   After enabling the RC48, the application software should wait on HSI48RDY
  *         flag to be set indicating that RC48 clock is stable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI48_ENABLE()  SET_BIT(RCC->CRRCR, RCC_CRRCR_HSI48ON)

#define __HAL_RCC_HSI48_DISABLE() CLEAR_BIT(RCC->CRRCR, RCC_CRRCR_HSI48ON)
#endif /* RCC_CRRCR_HSI48ON */
/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  *
  * @param  __RTC_CLKSOURCE__ specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE  No clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  *
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__)  \
  MODIFY_REG( RCC->BDCR, RCC_BDCR_RTCSEL, (__RTC_CLKSOURCE__))

/** @brief  Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE  No clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  */
#define  __HAL_RCC_GET_RTC_SOURCE() (READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL))

/** @brief  Macros to enable or disable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @retval None
  */
#define __HAL_RCC_PLL_ENABLE()         SET_BIT(RCC->CR, RCC_CR_PLLON)

#define __HAL_RCC_PLL_DISABLE()        CLEAR_BIT(RCC->CR, RCC_CR_PLLON)

/** @brief  Macro to configure the PLL clock source.
  * @note   This function must be used only when the main PLL is disabled.
  * @param  __PLLSOURCE__ specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_MSI  MSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL clock entry
  * @note   This clock source is common for the main PLL and audio PLL (PLLSAI1 and PLLSAI2).
  * @retval None
  *
  */
#define __HAL_RCC_PLL_PLLSOURCE_CONFIG(__PLLSOURCE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, (__PLLSOURCE__))

/** @brief  Macro to configure the PLL source division factor M.
  * @note   This function must be used only when the main PLL is disabled.
  * @param  __PLLM__ specifies the division factor for PLL VCO input clock
  *         This parameter must be a number between Min_Data = 1 and Max_Data = 8.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 4 to 16 MHz. It is recommended to select a frequency
  *         of 16 MHz to limit PLL jitter.
  * @retval None
  *
  */
#define __HAL_RCC_PLL_PLLM_CONFIG(__PLLM__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, (__PLLM__))

/**
  * @brief  Macro to configures the main PLL clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL is disabled.
  *
  * @param  __PLLSOURCE__: specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_MSI: MSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  *
  * @param  __PLLM__: specifies the division factor for PLL VCO input clock
  *          This parameter must be a number between 1 and 63.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 1 to 16 MHz.
  *
  * @param  __PLLN__: specifies the multiplication factor for PLL VCO output clock
  *          This parameter must be a number between 4 and 127.
  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
  *         output frequency is between 150 and 420 MHz (when in medium VCO range) or
  *         between 192 and 836 MHZ (when in wide VCO range)
  *
  * @param  __PLLP__: specifies the division factor for system  clock.
  *          This parameter must be a number between 2 and 32
  *
  * @param  __PLLQ__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 2 and 8
  *
  * @param  __PLLR__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 2 and 8
  *
  * @retval None
  */
#define __HAL_RCC_PLL_CONFIG(__PLLSOURCE__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__,__PLLR__ ) \
  MODIFY_REG(RCC->PLLCFGR, \
             (RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | \
              RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLR | RCC_PLLCFGR_PLLP), \
             ((__PLLSOURCE__) | \
              (__PLLM__) | \
              ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos) | \
              (__PLLQ__) | \
              (__PLLR__) | \
              (__PLLP__)))

/** @brief  Macro to configure the PLL input clock division factor M.
  *
  * @note   This function must be used only when the PLL is disabled.
  * @note   PLL clock source is common with the main PLL (configured through
  *         __HAL_RCC_PLL_CONFIG() macro)
  *
  * @param  __PLLM__ specifies the division factor for PLL clock.
  *         This parameter must be a number between Min_Data = 1 and Max_Data = 16.
  *
  * @retval None
  */
#define __HAL_RCC_PLL_DIVM_CONFIG(__PLLM__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, ((__PLLM__) - 1U) << RCC_PLLCFGR_PLLM_Pos)

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_NONE: No oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_MSI: MSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC))

/**
  * @brief  Enable each clock output (RCC_PLLRCLK, RCC_PLLQCLK, RCC_PLLPCLK)
  * @note   Enabling clock outputs RCC_PLLPCLK and RCC_PLLQCLK can be done at anytime
  *         without the need to stop the PLL in order to save power. But RCC_PLLRCLK cannot
  *         be stopped if used as System Clock.
  * @note   (*) RCC_PLLQCLK availability depends on devices
  * @param  __PLLCLOCKOUT__ specifies the PLL clock to be output.
  *          This parameter can be one or a combination of the following values:
  *            @arg @ref RCC_PLL_DIVP  This clock is used to generate the clock for the ADC.
  *            @arg @ref RCC_PLL_DIVQ  This Clock is used to generate the clock for the High Speed Timers,
  *                                  and the random analog generator (<=48 MHz).
  *            @arg @ref RCC_PLL_DIVR  This Clock is used to generate the high speed system clock (up to 48MHz)
  * @retval None
  */
#define __HAL_RCC_PLLCLKOUT_ENABLE(__PLLCLOCKOUT__)   SET_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Disable each clock output (RCC_PLLRCLK, RCC_PLLQCLK, RCC_PLLPCLK)
  * @note   Disabling clock outputs RCC_PLLPCLK and RCC_PLLQCLK can be done at anytime
  *         without the need to stop the PLL in order to save power. But RCC_PLLRCLK cannot
  *         be stopped if used as System Clock.
  * @note   (*) RCC_PLLQCLK availability depends on devices
  * @param  __PLLCLOCKOUT__  specifies the PLL clock to be output.
  *          This parameter can be one or a combination of the following values:
  *            @arg @ref RCC_PLL_DIVP  This clock may be used to generate the clock for the ADC, I2S1.
  *            @arg @ref RCC_PLL_DIVQ This Clock may be used to generate the clock for the High Speed Timers,
  *             and RNG (<=48 MHz).
  *            @arg @ref RCC_PLL_DIVR  This Clock is used to generate the high speed system clock (up to 48MHz)
  * @retval None
  */
#define __HAL_RCC_PLLCLKOUT_DISABLE(__PLLCLOCKOUT__)  CLEAR_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Get clock output enable status (RCC_PLLRCLK, RCC_PLLQCLK, RCC_PLLPCLK)
  * @param  __PLLCLOCKOUT__ specifies the output PLL clock to be checked.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_DIVP  This clock may be used to generate the clock for the ADC, I2S1.
  *            @arg @ref RCC_PLL_DIVQ This Clock may be used to generate the clock for the High Speed Timers,
  *             and RNG (<=48 MHz).
  *            @arg @ref RCC_PLL_DIVR  This Clock is used to generate the high speed system clock (up to 48MHz)
  * @retval SET / RESET
  * @note   (*) RCC_PLLQCLK availability depends on devices
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLLCLKOUT_CONFIG(__PLLCLOCKOUT__)  READ_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__: specifies the system clock source.
  *          This parameter can be one of the following values:
  *              - RCC_SYSCLKSOURCE_MSI: MSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSI: HSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSE: HSE oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_PLLCLK: PLL output is used as system clock source.
  *              - RCC_SYSCLKSOURCE_LSI: LSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_LSE: LSE oscillator is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__SYSCLKSOURCE__))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              - RCC_SYSCLKSOURCE_MSI: MSI used as system clock.
  *              - RCC_SYSCLKSOURCE_HSI: HSI used as system clock.
  *              - RCC_SYSCLKSOURCE_HSE: HSE used as system clock.
  *              - RCC_SYSCLKSOURCE_PLLCLK: PLL used as system clock.
  *              - RCC_SYSCLKSOURCE_LSI: LSI used as system clock.
  *              - RCC_SYSCLKSOURCE_LSE: LSE used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() ((uint32_t)(RCC->CFGR & RCC_CFGR_SWS))

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @param  __LSEDRIVE__: specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW  LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, (uint32_t)(__LSEDRIVE__))

/**
  * @brief  Macro to configure the wake up from stop clock.
  * @param  __STOPWUCLK__: specifies the clock source used after wake up from stop.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_MSI  MSI selected as system clock source
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_HSI  HSI selected as system clock source
  * @retval None
  */
#define __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(__STOPWUCLK__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPWUCK, (__STOPWUCLK__))

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK  System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_MSI  MSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI  HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE  HSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLLR  Main PLL clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI  LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE  LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI48  HSI48 clock selected as MCO source for devices with HSI48 (*)
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1DIV_1    MCO clock source is divided by 1
  *            @arg @ref RCC_MCO1DIV_2    MCO clock source is divided by 2
  *            @arg @ref RCC_MCO1DIV_4    MCO clock source is divided by 4
  *            @arg @ref RCC_MCO1DIV_8    MCO clock source is divided by 8
  *            @arg @ref RCC_MCO1DIV_16   MCO clock source is divided by 16
  *            @arg @ref RCC_MCO1DIV_32   MCO clock source is divided by 32
  *            @arg @ref RCC_MCO1DIV_64   MCO clock source is divided by 64
  *            @arg @ref RCC_MCO1DIV_128  MCO clock source is divided by 128
  *            @arg @ref RCC_MCO1DIV_256  MCO clock source is divided by 256
  *            @arg @ref RCC_MCO1DIV_512  MCO clock source is divided by 512
  *            @arg @ref RCC_MCO1DIV_1024 MCO clock source is divided by 1024
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO1SEL | RCC_CFGR_MCO1PRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO2SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO2SOURCE_SYSCLK  System  clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_MSI  MSI clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_HSI  HSI clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_HSE  HSE clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_PLLR  Main PLL clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_LSI  LSI clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_LSE  LSE clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_HSI48  HSI48 clock selected as MCO source for devices with HSI48 (*)
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO2DIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCO2DIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCO2DIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCO2DIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCO2DIV_16  MCO clock source is divided by 16
  *            @arg @ref RCC_MCO2DIV_32  MCO clock source is divided by 32
  *            @arg @ref RCC_MCO2DIV_64  MCO clock source is divided by 64
  *            @arg @ref RCC_MCO2DIV_128  MCO clock source is divided by 128
  *            @arg @ref RCC_MCO2DIV_256  MCO clock source is divided by 256
  *            @arg @ref RCC_MCO2DIV_512  MCO clock source is divided by 512
  *            @arg @ref RCC_MCO2DIV_1024  MCO clock source is divided by 1024
  */
#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO2SEL | RCC_CFGR_MCO2PRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt (Perform access to RCC_CIER bits to enable
  *         the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_MSIRDY   MSI ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY   PLL ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt (*)
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt (Perform access to RCC_CIER bits to disable
  *        the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_MSIRDY   MSI ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY   PLL ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt (*)
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits (Perform access to RCC_CICR
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_MSIRDY   MSI ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY   PLL ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt (*)
  * @retval None
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) WRITE_REG(RCC->CICR, (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_MSIRDY   MSI ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY   PLL ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt (*)
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__)  ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PADRST, RCC_FLAG_BORRST,
  *        RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST and RCC_FLAG_LPWRRST.
  * @retval None
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_MSIRDY    MSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSIRDY    HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY    HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLLRDY    PLL clock ready
  *            @arg @ref RCC_FLAG_HSI48RDY  HSI48 clock ready (*)
  *            @arg @ref RCC_FLAG_LSERDY    LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD   Clock security system failure on LSE oscillator detection
  *            @arg @ref RCC_FLAG_LSIRDY    LSI oscillator clock ready
  *            @arg @ref RCC_FLAG_PWRRST    BOR reset
  *            @arg @ref RCC_FLAG_OBLRST    OBLRST reset
  *            @arg @ref RCC_FLAG_PINRST    Pin reset
  *            @arg @ref RCC_FLAG_RMV       Remove reset Flag
  *            @arg @ref RCC_FLAG_SFTRST    Software reset
  *            @arg @ref RCC_FLAG_IWDGRST   Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST   Window Watchdog reset
  *            @arg @ref RCC_FLAG_LPWRRST   Low Power reset
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#if defined(RCC_CRRCR_HSI48ON)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5U) == 1U) ? RCC->CR :                    \
                                         ((((__FLAG__) >> 5U) == 4U) ? RCC->CRRCR :                 \
                                          ((((__FLAG__) >> 5U) == 2U) ? RCC->BDCR :                  \
                                           ((((__FLAG__) >> 5U) == 3U) ? RCC->CSR : RCC->CIFR)))) &   \
                                        (1U << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) ? 1U : 0U)
#else
#define __HAL_RCC_GET_FLAG(__FLAG__) ((((((((__FLAG__) >> 5U) == 1U) ? RCC->CR :                   \
                                          ((((__FLAG__) >> 5U) == 2U) ? RCC->BDCR :                  \
                                           ((((__FLAG__) >> 5U) == 3U) ? RCC->CSR : RCC->CIFR)))) &   \
                                        (1U << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) ? 1U : 0U)
#endif /* HSI48 */
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
#define RCC_HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define RCC_HSI_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1) */
#define RCC_MSI_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1) */
#define RCC_DBP_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1) */
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT
/* Defines used for Flags */
#define CR_REG_INDEX              (1U)
#define BDCR_REG_INDEX            (2U)
#define CSR_REG_INDEX             (3U)
#if defined(RCC_CRRCR_HSI48ON)
#define CRRCR_REG_INDEX           (4U)
#endif /* RCC_CRRCR_HSI48ON */
#define CIFR_REG_INDEX            (5U)
#define RCC_FLAG_MASK             (0x1FU)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */
#if defined(RCC_CRRCR_HSI48ON)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) \
  (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                                || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE)   == RCC_OSCILLATORTYPE_HSE)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI)   == RCC_OSCILLATORTYPE_HSI)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48)  || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_MSI)   == RCC_OSCILLATORTYPE_MSI)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI)   == RCC_OSCILLATORTYPE_LSI)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE)   == RCC_OSCILLATORTYPE_LSE))
#else
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) \
  (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                                || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE)   == RCC_OSCILLATORTYPE_HSE)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI)   == RCC_OSCILLATORTYPE_HSI)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_MSI)   == RCC_OSCILLATORTYPE_MSI)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI)   == RCC_OSCILLATORTYPE_LSI)    || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE)   == RCC_OSCILLATORTYPE_LSE))
#endif /* RCC_CRRCR_HSI48ON */

#define IS_RCC_HSE(__HSE__)  (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                              ((__HSE__) == RCC_HSE_BYPASS))

#define IS_RCC_LSE(__LSE__)  (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                              ((__LSE__) == RCC_LSE_ON_RTC_ONLY) || ((__LSE__) == RCC_LSE_BYPASS_RTC_ONLY) || \
                              ((__LSE__) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(__HSI__)  (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (RCC_ICSCR_HSITRIM >> RCC_ICSCR_HSITRIM_Pos))

#define IS_RCC_LSI(__LSI__)  (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_LSIDIV(__DIV__) (((__DIV__) == RCC_LSI_DIV1)  || ((__DIV__) == RCC_LSI_DIV128))

#define IS_RCC_MSI(__MSI__)  (((__MSI__) == RCC_MSI_OFF) || ((__MSI__) == RCC_MSI_ON))

#define IS_RCC_MSICALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 255U)

#if defined(RCC_CRRCR_HSI48ON)
#define IS_RCC_HSI48(__HSI48__)  (((__HSI48__) == RCC_HSI48_OFF) || ((__HSI48__) == RCC_HSI48_ON))
#endif /* RCC_CRRCR_HSI48ON */

#define IS_RCC_PLL(PLL) (((PLL) == RCC_PLL_NONE) ||((PLL) == RCC_PLL_OFF) || \
                         ((PLL) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_MSI)  || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSI)  || \
                                  ((SOURCE) == RCC_PLLSOURCE_NONE) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))

#define IS_RCC_PLL_DIVM_VALUE(__VALUE__) (((__VALUE__) == RCC_PLLM_DIV1) || ((__VALUE__) == RCC_PLLM_DIV2) || \
                                          ((__VALUE__) == RCC_PLLM_DIV3) || ((__VALUE__) == RCC_PLLM_DIV4) || \
                                          ((__VALUE__) == RCC_PLLM_DIV5) || ((__VALUE__) == RCC_PLLM_DIV6) || \
                                          ((__VALUE__) == RCC_PLLM_DIV7) || ((__VALUE__) == RCC_PLLM_DIV8))
#define IS_RCC_PLL_MULN_VALUE(VALUE) ((4U <= (VALUE)) && ((VALUE) <= 127U))
#define IS_RCC_PLL_DIVP_VALUE(__VALUE__) ((RCC_PLLP_DIV2 <= (__VALUE__)) && ((__VALUE__) <= RCC_PLLP_DIV32))
#define IS_RCC_PLL_DIVQ_VALUE(__VALUE__) ((RCC_PLLQ_DIV2 <= (__VALUE__)) && ((__VALUE__) <= RCC_PLLQ_DIV8))
#define IS_RCC_PLL_DIVR_VALUE(__VALUE__) ((RCC_PLLR_DIV2 <= (__VALUE__)) && ((__VALUE__) <= RCC_PLLR_DIV8))

#define IS_RCC_PLLCLOCKOUT_VALUE(VALUE) ((((VALUE) & RCC_PLL_DIVP) == RCC_PLL_DIVP) || \
                                         (((VALUE) & RCC_PLL_DIVQ) == RCC_PLL_DIVQ) || \
                                         (((VALUE) & RCC_PLL_DIVR) == RCC_PLL_DIVR))

#define IS_RCC_MSI_CLOCK_RANGE(__RANGE__) (((__RANGE__) == RCC_MSIRANGE_0)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_1)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_2)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_3)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_4)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_5)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_6)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_7)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_8)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_9)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_10) || \
                                           ((__RANGE__) == RCC_MSIRANGE_11))


#define IS_RCC_MSI_STANDBY_CLOCK_RANGE(__RANGE__) (((__RANGE__) == RCC_MSIRANGE_4)  || \
                                                   ((__RANGE__) == RCC_MSIRANGE_5)  || \
                                                   ((__RANGE__) == RCC_MSIRANGE_6)  || \
                                                   ((__RANGE__) == RCC_MSIRANGE_7))

#define IS_RCC_CLOCKTYPE(CLK) ((1U <= (CLK)) && ((CLK) <= 0x1FU))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_MSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK)|| \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE))

#define IS_RCC_HCLK(__HCLK__) (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                               ((__HCLK__) == RCC_SYSCLK_DIV4)   || ((__HCLK__) == RCC_SYSCLK_DIV8)   || \
                               ((__HCLK__) == RCC_SYSCLK_DIV16)  || ((__HCLK__) == RCC_SYSCLK_DIV64)  || \
                               ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV512))

#define IS_RCC_PCLK(__PCLK__) (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                               ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                               ((__PCLK__) == RCC_HCLK_DIV16))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE)   || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)    || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)    || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE))

#define IS_RCC_MCO(__MCOX__) ( ((__MCOX__) == RCC_MCO1_PA8)  || \
                               ((__MCOX__) == RCC_MCO1_PA9)  || \
                               ((__MCOX__) == RCC_MCO1_PF2)  || \
                               ((__MCOX__) == RCC_MCO2_PA10) || \
                               ((__MCOX__) == RCC_MCO2_PC2)  || \
                               ((__MCOX__) == RCC_MCO2_PA8))
#if defined(RCC_MCO1SOURCE_HSI48)
#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_MSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_PLLR) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSE) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI48) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_RTC_ALT) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_RTC_WAKEUP))
#else
#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_MSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_PLLR) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSE) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_RTC_ALT) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_RTC_WAKEUP))
#endif /* RCC_MCO1SOURCE_HSI48 */
#if defined(RCC_MCO2SOURCE_HSI48)
#define IS_RCC_MCO2SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO2SOURCE_NOCLOCK) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_SYSCLK) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_MSI) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_HSI) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_HSE) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_PLLR) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_LSE) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_HSI48) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_RTC_ALT) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_RTC_WAKEUP))
#else
#define IS_RCC_MCO2SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO2SOURCE_NOCLOCK) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_SYSCLK) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_MSI) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_HSI) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_HSE) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_PLLR) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_LSE) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_RTC_ALT) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_RTC_WAKEUP))
#endif /* RCC_MCO2SOURCE_HSI48 */
#define IS_RCC_MCO1DIV(__DIV__) (((__DIV__) == RCC_MCO1DIV_1) || ((__DIV__) == RCC_MCO1DIV_2)  || \
                                 ((__DIV__) == RCC_MCO1DIV_4) || ((__DIV__) == RCC_MCO1DIV_8)  || \
                                 ((__DIV__) == RCC_MCO1DIV_16)|| ((__DIV__) == RCC_MCO1DIV_32) || \
                                 ((__DIV__) == RCC_MCO1DIV_64)|| ((__DIV__) == RCC_MCO1DIV_128)|| \
                                 ((__DIV__) == RCC_MCO1DIV_256)|| ((__DIV__) == RCC_MCO1DIV_512)|| \
                                 ((__DIV__) == RCC_MCO1DIV_1024))

#define IS_RCC_MCO2DIV(__DIV__) (((__DIV__) == RCC_MCO2DIV_1) || ((__DIV__) == RCC_MCO2DIV_2) || \
                                 ((__DIV__) == RCC_MCO2DIV_4) || ((__DIV__) == RCC_MCO2DIV_8) || \
                                 ((__DIV__) == RCC_MCO2DIV_16)|| ((__DIV__) == RCC_MCO2DIV_32) || \
                                 ((__DIV__) == RCC_MCO2DIV_64)|| ((__DIV__) == RCC_MCO2DIV_128)|| \
                                 ((__DIV__) == RCC_MCO2DIV_256)|| ((__DIV__) == RCC_MCO2DIV_512)|| \
                                 ((__DIV__) == RCC_MCO2DIV_1024))

#define IS_RCC_LSE_DRIVE(__DRIVE__) (((__DRIVE__) == RCC_LSEDRIVE_LOW)        || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

#define IS_RCC_STOP_WAKEUPCLOCK(__SOURCE__) (((__SOURCE__) == RCC_STOP_WAKEUPCLOCK_MSI) || \
                                             ((__SOURCE__) == RCC_STOP_WAKEUPCLOCK_HSI))

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "stm32u0xx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef  *const RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency);
uint32_t          HAL_RCC_GetResetSource(void);
/* CSS NMI IRQ handler */
void              HAL_RCC_NMI_IRQHandler(void);
/* User Callbacks in non blocking mode (IT mode) */
void              HAL_RCC_CSSCallback(void);

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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32U0xx_HAL_RCC_H */
