/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL  module.
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
#ifndef __STM32WBAxx_HAL_RCC_H
#define __STM32WBAxx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"
#include "stm32wbaxx_ll_rcc.h"

/** @addtogroup STM32WBAxx_HAL_Driver
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
  * @brief  RCC PLL1 configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;        /*!< The new state of the PLL1.
                                 This parameter can be a value of @ref RCC_PLL_Config                     */

  uint32_t PLLSource;       /*!< RCC_PLLSource: PLL1 entry clock source.
                                 This parameter must be a value of @ref RCC_PLL_Clock_Source              */

  uint32_t PLLM;            /*!< PLLM: Division factor for PLL1 VCO input clock.
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 8    */

  uint32_t PLLN;            /*!< PLLN: Multiplication factor for PLL1 VCO output clock.
                                 This parameter must be a number between Min_Data = 4 and Max_Data = 512   */

  uint32_t PLLP;            /*!< PLLP: Division factor for system clock.
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 128  */

  uint32_t PLLQ;            /*!< PLLQ: Division factor for peripheral clocks.
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 128  */

  uint32_t PLLR;            /*!< PLLR: Division factor for peripheral clocks.
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 128  */

  uint32_t PLLFractional;   /*!< PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
                                 PLL1 VCO It should be a value between 0 and 0x1FFF                       */

} RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, MSI, LSE and LSI1) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t HSEDiv;               /*!< The division factor of the HSE. Applicable only to SYSCLK when HSE is source.
                                      This parameter can be a value of @ref RCC_HSE_Div                           */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F
                                      on the other devices */

  uint32_t LSIState;             /*!< The new state of the LSI (LSI1 or LSI2 when applicable).
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t LSIDiv;               /*!< The division factor of the LSI. Applicable only to LSI1.
                                      This parameter can be a value of @ref RCC_LSI_Div                           */

  RCC_PLLInitTypeDef PLL1;       /*!< Main PLL1 structure parameters                                              */

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
                                         This parameter can be a value of @ref RCC_AHB_Clock_Source */

  uint32_t APB1CLKDivider;          /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                         This parameter can be a value of @ref RCC_APB1_APB2_APB7_Clock_Source */

  uint32_t APB2CLKDivider;          /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                         This parameter can be a value of @ref RCC_APB1_APB2_APB7_Clock_Source */

  uint32_t APB7CLKDivider;          /*!< The APB7 clock (PCLK7) divider. This clock is derived from the AHB clock (HCLK).
                                         This parameter can be a value of @ref RCC_APB1_APB2_APB7_Clock_Source */

  uint32_t AHB5_PLL1_CLKDivider;    /*!< The AHB5 clock (HCLK5) divider when PLL1 is source of SYSCLK. This clock is derived from the system clock (SYSCLK).
                                         This parameter can be a value of @ref RCC_AHB5_PLL1_Clock_Source       */

  uint32_t AHB5_HSEHSI_CLKDivider;  /*!< The AHB5 clock (HCLK5) divider when HSI or HSE are sources of SYSCLK. This clock is derived from the system clock (SYSCLK).
                                         This parameter can be a value of @ref RCC_AHB5_HSEHSI_Clock_Source       */

} RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Peripheral_Memory_Mapping Peripheral Memory Mapping
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_DBP_TIMEOUT_VALUE           (2U)    /* 2 ms (minimum Tick + 1) */
#define RCC_LSE_TIMEOUT_VALUE           LSE_STARTUP_TIMEOUT
/**
  * @}
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE         0x00000000U   /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSE          0x00000001U   /*!< HSE32 to configure */
#define RCC_OSCILLATORTYPE_HSI          0x00000002U   /*!< HSI16 to configure */
#define RCC_OSCILLATORTYPE_LSE          0x00000004U   /*!< LSE to configure */
#define RCC_OSCILLATORTYPE_LSI          0x00000008U   /*!< LSI to configure */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                     0x00000000U        /*!< HSE clock deactivation */
#define RCC_HSE_ON                      RCC_CR_HSEON       /*!< HSE clock activation */
/**
  * @}
  */

/** @defgroup RCC_HSE_Div HSE Div
  * @{
  */
#define RCC_HSE_DIV1                    0x00000000U        /*!< HSE clock divided by 1 for SYSCLK */
#define RCC_HSE_DIV2                    RCC_CR_HSEPRE      /*!< HSE clock divided by 2 for SYSCLK */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                     0U                                                        /*!< LSE clock deactivation */
#define RCC_LSE_ON_RTC_ONLY             RCC_BDCR1_LSEON                                           /*!< LSE clock activation for RTC only */
#define RCC_LSE_ON                      (RCC_BDCR1_LSESYSEN | RCC_BDCR1_LSEON)                    /*!< LSE clock activation for RCC and peripherals */
#define RCC_LSE_BYPASS_RTC_ONLY         (RCC_BDCR1_LSEBYP | RCC_BDCR1_LSEON)                      /*!< External clock source for LSE clock */
#define RCC_LSE_BYPASS                  (RCC_BDCR1_LSEBYP | RCC_BDCR1_LSESYSEN | RCC_BDCR1_LSEON) /*!< External clock source for LSE clock */
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

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U          /*!< LSI clock deactivation */
#define RCC_LSI1_ON                     RCC_BDCR1_LSI1ON    /*!< LSI1 clock activation */
#if defined(RCC_LSI2_SUPPORT)
#define RCC_LSI2_ON                     RCC_BDCR1_LSI2ON    /*!< LSI2 clock activation */
#endif
/**
  * @}
  */

/** @defgroup RCC_LSI_Div LSI Div
  * @{
  */
#define RCC_LSI_DIV1                    0U                    /*!< LSI1 clock is not divided */
#define RCC_LSI_DIV128                  RCC_BDCR1_LSI1PREDIV  /*!< LSI1 clock is divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_PLL_Config  RCC PLL1 Config
  * @{
  */
#define RCC_PLL_NONE                    0x00000000U
#define RCC_PLL_OFF                     0x00000001U
#define RCC_PLL_ON                      0x00000002U
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source  RCC PLL1 Clock Source
  * @{
  */
#define RCC_PLLSOURCE_NONE              0x00000000U
#define RCC_PLLSOURCE_HSI               RCC_PLL1CFGR_PLL1SRC_1
#define RCC_PLLSOURCE_HSE               (RCC_PLL1CFGR_PLL1SRC_1 | RCC_PLL1CFGR_PLL1SRC_0)
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Output  RCC PLL1 Clock Output
  * @{
  */
#define RCC_PLL1_PCLK                   RCC_PLL1CFGR_PLL1PEN
#define RCC_PLL1_QCLK                   RCC_PLL1CFGR_PLL1QEN
#define RCC_PLL1_RCLK                   RCC_PLL1CFGR_PLL1REN
/**
  * @}
  */

/** @defgroup RCC_PLL_VCO_Input_Range  RCC PLL1 VCO Input Range
  * @{
  */
#define RCC_PLL_VCOINPUT_RANGE0         0x00000000U
#define RCC_PLL_VCOINPUT_RANGE1         (RCC_PLL1CFGR_PLL1RGE_1 | RCC_PLL1CFGR_PLL1RGE_0)
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
#define RCC_CLOCKTYPE_PCLK7             0x00000010U  /*!< PCLK7 to configure  */
#define RCC_CLOCKTYPE_HCLK5             0x00000020U  /*!< HCLK5 to configure  */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI            0x00000000U                        /*!< HSI16 selection as system clock */
#define RCC_SYSCLKSOURCE_HSE            RCC_CFGR1_SW_1                     /*!< HSE32 or HSE32/32 (depending on HSEPRE) selection as system clock */
#define RCC_SYSCLKSOURCE_PLLCLK         (RCC_CFGR1_SW_1 | RCC_CFGR1_SW_0)  /*!< PLL1R selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSI     0x00000000U                         /*!< HSI16 used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE     RCC_CFGR1_SWS_1                     /*!< HSE32 or HSE32/32 (depending on HSEPRE) used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK  (RCC_CFGR1_SWS_1 | RCC_CFGR1_SWS_0) /*!< PLL1R used as system clock */
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                 0x00000000U                                                 /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2                 RCC_CFGR2_HPRE_2                                            /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4                 (RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0)                       /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8                 (RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1)                       /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16                (RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0)    /*!< SYSCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB1_APB2_APB7_Clock_Source APB1 APB2 APB7 Clock Source
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

/** @defgroup RCC_AHB5_PLL1_Clock_Source AHB5 PLL1 Clock Source
  * @{
  */
#define RCC_SYSCLK_PLL1_DIV1            0x00000000U                                                 /*!< SYSCLK when PLL1 is source not divided */
#define RCC_SYSCLK_PLL1_DIV2            RCC_CFGR4_HPRE5_2                                           /*!< SYSCLK when PLL1 is source divided by 2 */
#define RCC_SYSCLK_PLL1_DIV3            (RCC_CFGR4_HPRE5_2 | RCC_CFGR4_HPRE5_0)                     /*!< SYSCLK when PLL1 is source divided by 3 */
#define RCC_SYSCLK_PLL1_DIV4            (RCC_CFGR4_HPRE5_2 | RCC_CFGR4_HPRE5_1)                     /*!< SYSCLK when PLL1 is source divided by 4 */
#define RCC_SYSCLK_PLL1_DIV6            (RCC_CFGR4_HPRE5_2 | RCC_CFGR4_HPRE5_1 | RCC_CFGR4_HPRE5_0) /*!< SYSCLK when PLL1 is source divided by 6 */
/**
  * @}
  */

/** @defgroup RCC_AHB5_HSEHSI_Clock_Source AHB5 HSEHSI Clock Source
  * @{
  */
#define RCC_SYSCLK_HSEHSI_DIV1          0x00000000U         /*!< SYSCLK when HSE or HSI is source not divided */
#define RCC_SYSCLK_HSEHSI_DIV2          RCC_CFGR4_HDIV5     /*!< SYSCLK when HSE or HSI is source divided by 2 */
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_DISABLE        0x00000000U         /*!< RTC clock is disabled */
#define RCC_RTCCLKSOURCE_LSE            RCC_BDCR1_RTCSEL_0  /*!< LSE oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSI            RCC_BDCR1_RTCSEL_1  /*!< LSI1 or LIS2 oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV32      RCC_BDCR1_RTCSEL    /*!< HSE32 oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO1                        0x00000000U
#define RCC_MCO                         RCC_MCO1            /*!< MCO1 to be compliant with other families with 2 MCOs*/
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK          0x00000000U                                                     /*!< MCO1 output disabled, no clock on MCO1 */
#define RCC_MCO1SOURCE_SYSCLK           RCC_CFGR1_MCOSEL_0                                              /*!< SYSCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI              (RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_0)                       /*!< HSI16 selection as MCO1 source */
#define RCC_MCO1SOURCE_HSE              RCC_CFGR1_MCOSEL_2                                              /*!< HSE32 selection as MCO1 source */
#define RCC_MCO1SOURCE_PLL1RCLK         (RCC_CFGR1_MCOSEL_2 | RCC_CFGR1_MCOSEL_0)                       /*!< PLL1RCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_LSI              (RCC_CFGR1_MCOSEL_2 | RCC_CFGR1_MCOSEL_1)                       /*!< LSI selection as MCO1 source */
#define RCC_MCO1SOURCE_LSE              (RCC_CFGR1_MCOSEL_2 | RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_0)  /*!< LSE selection as MCO1 source */
#define RCC_MCO1SOURCE_PLL1PCLK         RCC_CFGR1_MCOSEL_3                                              /*!< PLL1PCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_PLL1QCLK         (RCC_CFGR1_MCOSEL_3 | RCC_CFGR1_MCOSEL_0)                       /*!< PLL1QCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_HCLK5            (RCC_CFGR1_MCOSEL_3 | RCC_CFGR1_MCOSEL_1)                       /*!< HCLK5 selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler MCO1 Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                    0x00000000U                               /*!< MCO is divided by 1 */
#define RCC_MCODIV_2                    RCC_CFGR1_MCOPRE_0                        /*!< MCO is divided by 2 */
#define RCC_MCODIV_4                    RCC_CFGR1_MCOPRE_1                        /*!< MCO is divided by 4 */
#define RCC_MCODIV_8                    (RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0) /*!< MCO is divided by 8 */
#define RCC_MCODIV_16                   RCC_CFGR1_MCOPRE_2                        /*!< MCO is divided by 16 */
/**
  * @}
  */

#if defined(RCC_CCIPR2_ASSEL)
/** @defgroup RCC_Interrupt Interrupts
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 000: CIFR register
  *                 - 001: ASSR register
  * @{
  */
/* Flags in the CIFR register */
#define RCC_IT_LSI1RDY                  ((CIFR_REG_INDEX << 5U) | RCC_CIFR_LSI1RDYF_Pos)    /*!< LSI1 Ready Interrupt flag */
#define RCC_IT_LSERDY                   ((CIFR_REG_INDEX << 5U) | RCC_CIFR_LSERDYF_Pos)     /*!< LSE Ready Interrupt flag */
#define RCC_IT_HSIRDY                   ((CIFR_REG_INDEX << 5U) | RCC_CIFR_HSIRDYF_Pos)     /*!< HSI16 Ready Interrupt flag */
#define RCC_IT_HSERDY                   ((CIFR_REG_INDEX << 5U) | RCC_CIFR_HSERDYF_Pos)     /*!< HSE Ready Interrupt flag */
#define RCC_IT_PLL1RDY                  ((CIFR_REG_INDEX << 5U) | RCC_CIFR_PLL1RDYF_Pos)    /*!< PLL1 Ready Interrupt flag */
#define RCC_IT_CSS                      ((CIFR_REG_INDEX << 5U) | RCC_CIFR_HSECSSF_Pos)     /*!< HSE32 Clock Security System Interrupt flag */
#if defined(RCC_LSI2_SUPPORT)
#define RCC_IT_LSI2RDY                  ((CIFR_REG_INDEX << 5U) | RCC_CIFR_LSI2RDYF_Pos)    /*!< LSI2 Ready Interrupt flag */
#endif /* RCC_BDCR1_LSI2ON */

/* Flags in the ASSR register */
#define RCC_IT_CAPTURE_ERROR            ((ASSR_REG_INDEX << 5U) | RCC_ASSR_CAEF_Pos)        /*!< Capture Error Interrupt flag */
#define RCC_IT_COMPARER                 ((ASSR_REG_INDEX << 5U) | RCC_ASSR_COF_Pos)         /*!< Comparer Interrupt flag */
#define RCC_IT_CAPTURE_TRIGGER          ((ASSR_REG_INDEX << 5U) | RCC_ASSR_CAF_Pos)         /*!< Capture Trigger Interrupt flag */
/**
  * @}
  */
#else
/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSI1RDY                  RCC_CIFR_LSI1RDYF     /*!< LSI1 Ready Interrupt flag */
#define RCC_IT_LSERDY                   RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt flag */
#define RCC_IT_HSIRDY                   RCC_CIFR_HSIRDYF      /*!< HSI16 Ready Interrupt flag */
#define RCC_IT_HSERDY                   RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt flag */
#define RCC_IT_PLL1RDY                  RCC_CIFR_PLL1RDYF     /*!< PLL1 Ready Interrupt flag */
#define RCC_IT_CSS                      RCC_CIFR_HSECSSF      /*!< HSE32 Clock Security System Interrupt flag */
#if defined(RCC_LSI2_SUPPORT)
#define RCC_IT_LSI2RDY                  RCC_CIFR_LSI2RDYF     /*!< LSI2 Ready Interrupt flag */
#endif /* RCC_BDCR1_LSI2ON */
/**
  * @}
  */
 #endif /* RCC_CCIPR2_ASSEL */

/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: BDCR1 register
  *                 - 011: CSR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                 ((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos)   /*!< HSI Ready flag */
#define RCC_FLAG_HSERDY                 ((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos)   /*!< HSE Ready flag */
#define RCC_FLAG_PLL1RDY                ((CR_REG_INDEX << 5U) | RCC_CR_PLL1RDY_Pos)  /*!< PLL1 Ready flag */

/* Flags in the BDCR1 register */
#define RCC_FLAG_LSERDY                 ((BDCR1_REG_INDEX << 5U) | RCC_BDCR1_LSERDY_Pos)    /*!< LSE Ready flag */
#define RCC_FLAG_LSESYSRDY              ((BDCR1_REG_INDEX << 5U) | RCC_BDCR1_LSESYSRDY_Pos) /*!< LSESYS Ready flag */
#define RCC_FLAG_LSECSSD                ((BDCR1_REG_INDEX << 5U) | RCC_BDCR1_LSECSSD_Pos)   /*!< LSE Clock Security System Interrupt flag */
#define RCC_FLAG_LSI1RDY                ((BDCR1_REG_INDEX << 5U) | RCC_BDCR1_LSI1RDY_Pos)   /*!< LSI1 Ready flag */
#if defined(RCC_LSI2_SUPPORT)
#define RCC_FLAG_LSI2RDY                ((BDCR1_REG_INDEX << 5U) | RCC_BDCR1_LSI2RDY_Pos)   /*!< LSI2 Ready flag */
#endif /* RCC_BDCR1_LSI2ON */

/* Flags in the CSR register */
#define RCC_FLAG_OBLRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_OBLRSTF_Pos)  /*!< Option Byte Loader reset flag */
#define RCC_FLAG_PINRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos)  /*!< PIN reset flag */
#define RCC_FLAG_BORRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_BORRSTF_Pos)  /*!< BOR reset flag */
#define RCC_FLAG_SFTRST                 ((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos)  /*!< Software Reset flag */
#define RCC_FLAG_IWDGRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos) /*!< Independent Watchdog reset flag */
#if defined(WWDG)
#define RCC_FLAG_WWDGRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos) /*!< Window watchdog reset flag */
#endif /* WWDG */
#define RCC_FLAG_LPWRRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_LPWRRSTF_Pos) /*!< Low-Power reset flag */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR1_LSEDRV_0     /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR1_LSEDRV_1     /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH               RCC_BDCR1_LSEDRV       /*!< LSE high drive capability */
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
#if defined(WWDG)
#define RCC_RESET_FLAG_WWDG             RCC_CSR_WWDGRSTF   /*!< Window watchdog reset flag */
#endif /* WWDG */
#define RCC_RESET_FLAG_LPWR             RCC_CSR_LPWRRSTF   /*!< Low power reset flag */
#if defined(WWDG)
#define RCC_RESET_FLAG_ALL              (RCC_RESET_FLAG_OBL | RCC_RESET_FLAG_PIN | RCC_RESET_FLAG_PWR |  \
                                         RCC_RESET_FLAG_SW | RCC_RESET_FLAG_IWDG | RCC_RESET_FLAG_WWDG | \
                                         RCC_RESET_FLAG_LPWR)
#else
#define RCC_RESET_FLAG_ALL              (RCC_RESET_FLAG_OBL | RCC_RESET_FLAG_PIN | RCC_RESET_FLAG_PWR |  \
                                         RCC_RESET_FLAG_SW | RCC_RESET_FLAG_IWDG | RCC_RESET_FLAG_LPWR)
#endif /* WWDG */
/**
  * @}
  */

/** @defgroup RCC_items RCC items
  * @brief RCC items to configure attributes on
  * @{
  */
#define RCC_HSI                         RCC_SECCFGR_HSISEC
#define RCC_HSE                         RCC_SECCFGR_HSESEC
#define RCC_LSI                         RCC_SECCFGR_LSISEC
#define RCC_LSE                         RCC_SECCFGR_LSESEC
#define RCC_SYSCLK                      RCC_SECCFGR_SYSCLKSEC
#define RCC_PRESC                       RCC_SECCFGR_PRESCSEC
#define RCC_PLL1                        RCC_SECCFGR_PLL1SEC
#define RCC_RMVF                        RCC_SECCFGR_RMVFSEC
#define RCC_ALL                         (RCC_HSI|RCC_HSE|RCC_LSI|RCC_LSE|RCC_SYSCLK| \
                                         RCC_PRESC|RCC_PLL1|RCC_RMVF)
/**
  * @}
  */

/** @defgroup RCC_attributes RCC attributes
  * @brief RCC privilege/non-privilege and secure/non-secure attributes
  * @{
  */
#define RCC_NSEC_PRIV                   0x00000001U        /*!< Non-secure Privilege attribute item     */
#define RCC_NSEC_NPRIV                  0x00000002U        /*!< Non-secure Non-privilege attribute item */
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define RCC_SEC_PRIV                    0x00000010U        /*!< Secure Privilege attribute item         */
#define RCC_SEC_NPRIV                   0x00000020U        /*!< Secure Non-privilege attribute item     */
#endif
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

#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* GPDMA1 */

#define __HAL_RCC_FLASH_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_CRC_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(TSC)
#define __HAL_RCC_TSC_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_TSCEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_TSCEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* TSC */

#define __HAL_RCC_RAMCFG_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RAMCFGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RAMCFGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(GTZC_TZSC)
#define __HAL_RCC_GTZC1_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GTZC1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GTZC1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* GTZC_TZSC */

#define __HAL_RCC_SRAM1_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_SRAM1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_SRAM1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_CLK_DISABLE()         CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN)
#endif /* GPDMA1 */
#define __HAL_RCC_FLASH_CLK_DISABLE()          CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN)
#define __HAL_RCC_CRC_CLK_DISABLE()            CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN)
#define __HAL_RCC_TSC_CLK_DISABLE()            CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_TSCEN)
#define __HAL_RCC_RAMCFG_CLK_DISABLE()         CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RAMCFGEN)
#if defined(GTZC_TZSC)
#define __HAL_RCC_GTZC1_CLK_DISABLE()          CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GTZC1EN)
#endif /* GTZC_TZSC */
#define __HAL_RCC_SRAM1_CLK_DISABLE()          CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_SRAM1EN)

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

#define __HAL_RCC_GPIOA_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_GPIOB_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_GPIOC_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)


#define __HAL_RCC_GPIOH_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOHEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOHEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)


#define __HAL_RCC_AES_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_HASH_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_RNG_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(SAES)
#define __HAL_RCC_SAES_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SAESEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SAESEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* SAES */

#if defined(HSEM)
#define __HAL_RCC_HSEM_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HSEMEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HSEMEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* HSEM */

#define __HAL_RCC_PKA_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PKAEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PKAEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)



#define __HAL_RCC_SRAM2_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_GPIOA_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN)
#define __HAL_RCC_GPIOB_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN)
#define __HAL_RCC_GPIOC_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN)
#define __HAL_RCC_GPIOH_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOHEN)
#define __HAL_RCC_AES_CLK_DISABLE()            CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN)
#define __HAL_RCC_HASH_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN)
#define __HAL_RCC_RNG_CLK_DISABLE()            CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN)
#if defined(SAES)
#define __HAL_RCC_SAES_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SAESEN)
#endif /* SAES */
#if defined(HSEM)
#define __HAL_RCC_HSEM_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HSEMEN)
#endif /* HSEM */
#define __HAL_RCC_PKA_CLK_DISABLE()            CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PKAEN)
#define __HAL_RCC_SRAM2_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN)
/**
  * @}
  */

/** @defgroup RCC_AHB4_Clock_Enable_Disable AHB4ENR Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB4ENR peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_PWR_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_PWREN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_PWREN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_ADC4_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_ADC4EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_ADC4EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_PWR_CLK_DISABLE()            CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_PWREN)
#define __HAL_RCC_ADC4_CLK_DISABLE()           CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_ADC4EN)
/**
  * @}
  */

/** @defgroup RCC_AHB5_Clock_Enable_Disable AHB5ENR Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB5ENR peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_RADIO_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_RADIOEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_RADIOEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(PTACONV)
#define __HAL_RCC_PTACONV_CLK_ENABLE()         do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_PTACONVEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_PTACONVEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* PTACONV */

#define __HAL_RCC_RADIO_CLK_DISABLE()          CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_RADIOEN)

#if defined(PTACONV)
#define __HAL_RCC_PTACONV_CLK_DISABLE()        CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_PTACONVEN)
#endif /* PTACONV */
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

#define __HAL_RCC_TIM2_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(TIM3)
#define __HAL_RCC_TIM3_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* TIM3 */


#if defined(WWDG)
#define __HAL_RCC_WWDG_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* WWDG */


#if defined(USART2)
#define __HAL_RCC_USART2_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* USART2 */


#if defined(I2C1)
#define  __HAL_RCC_I2C1_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* I2C1 */



#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* LPTIM2 */

#define __HAL_RCC_TIM2_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN)
#if defined(TIM3)
#define __HAL_RCC_TIM3_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN)
#endif /* TIM3 */
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_DISABLE()         CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_CLK_DISABLE()         CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN)
#endif /* LPTIM2 */
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
#if defined(TIM1)
#define __HAL_RCC_TIM1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* TIM1 */

#if defined(SPI1)
#define __HAL_RCC_SPI1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* SPI1 */

#define __HAL_RCC_USART1_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_TIM16_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#if defined(TIM17)
#define __HAL_RCC_TIM17_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* TIM17 */

#if defined(SAI1)
#define __HAL_RCC_SAI1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* SAI1 */


#if defined(TIM1)
#define __HAL_RCC_TIM1_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN)
#endif /* TIM1 */
#if defined(SPI1)
#define __HAL_RCC_SPI1_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)
#endif /* SPI1 */
#define __HAL_RCC_USART1_CLK_DISABLE()         CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN)
#define __HAL_RCC_TIM16_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN)
#if defined(TIM17)
#define __HAL_RCC_TIM17_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN)
#endif /* SAI1 */
/**
  * @}
  */

/** @defgroup RCC_APB7_Clock_Enable_Disable APB7 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB7 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_SYSCFG_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_SYSCFGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_SYSCFGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_SPI3_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_SPI3EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_SPI3EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_LPUART1_CLK_ENABLE()         do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_LPUART1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_LPUART1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_I2C3_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_I2C3EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_I2C3EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_COMP_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_COMPEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_COMPEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_LPTIM1_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_LPTIM1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_LPTIM1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)


#define __HAL_RCC_RTCAPB_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APB7ENR, RCC_APB7ENR_RTCAPBEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APB7ENR, RCC_APB7ENR_RTCAPBEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)

#define __HAL_RCC_SYSCFG_CLK_DISABLE()         CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_SYSCFGEN)
#define __HAL_RCC_SPI3_CLK_DISABLE()           CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_SPI3EN)
#define __HAL_RCC_LPUART1_CLK_DISABLE()        CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_LPUART1EN)
#define __HAL_RCC_I2C3_CLK_DISABLE()           CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_I2C3EN)
#define __HAL_RCC_COMP_CLK_DISABLE()           CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_COMPEN)
#define __HAL_RCC_LPTIM1_CLK_DISABLE()         CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_LPTIM1EN)
#define __HAL_RCC_RTCAPB_CLK_DISABLE()         CLEAR_BIT(RCC->APB7ENR, RCC_APB7ENR_RTCAPBEN)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable_Status AHB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @{
  */
#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_IS_CLK_ENABLED()      (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN) != 0U)
#endif /* GPDMA1 */
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN) != 0U)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN) != 0U)
#define __HAL_RCC_TSC_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_TSCEN) != 0U)
#define __HAL_RCC_RAMCFG_IS_CLK_ENABLED()      (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RAMCFGEN) != 0U)
#if defined(GTZC_TZSC)
#define __HAL_RCC_GTZC1_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GTZC1EN) != 0U)
#endif /* GTZC_TZSC */
#define __HAL_RCC_SRAM1_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_SRAM1EN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable_Status AHB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB2 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN) != 0U)
#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOHEN) != 0U)
#define __HAL_RCC_AES_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN) != 0U)
#define __HAL_RCC_HASH_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN) != 0U)
#define __HAL_RCC_RNG_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN) != 0U)
#if defined(SAES)
#define __HAL_RCC_SAES_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SAESEN) != 0U)
#endif /* SAES */
#if defined(HSEM)
#define __HAL_RCC_HSEM_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HSEMEN) != 0U)
#endif /* HSEM */
#define __HAL_RCC_PKA_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PKAEN) != 0U)
#define __HAL_RCC_SRAM2_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB4_Peripheral_Clock_Enable_Disable_Status AHB4 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB4 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_PWR_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_PWREN) != 0U)
#define __HAL_RCC_ADC4_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_ADC4EN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB5_Peripheral_Clock_Enable_Disable_Status AHB5 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB5 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_RADIO_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_RADIOEN) != 0U)
#if defined(PTACONV)
#define __HAL_RCC_PTACONV_IS_CLK_ENABLED()     (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_PTACONVEN) != 0U)
#endif
/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable_Status APB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN) != 0U)
#if defined(TIM3)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN) != 0U)
#endif /* TIM3 */
#if defined(WWDG)
#define __HAL_RCC_WWDG_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN) != 0U)
#endif /* WWDG */
#if defined(USART2)
#define __HAL_RCC_USART2_IS_CLK_ENABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN) != 0U)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN) != 0U)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()      (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPTIM2EN) != 0U)
#endif /* LPTIM2 */
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Disable_Status APB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @{
  */
 #if defined(TIM1)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN) != 0U)
#endif /* TIM1 */
#if defined(SPI1)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN) != 0U)
#endif /* SPI1 */
#define __HAL_RCC_USART1_IS_CLK_ENABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN) != 0U)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN) != 0U)
#if defined(TIM17)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN) != 0U)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN) != 0U)
#endif /* SAI1 */
/**
  * @}
  */

/** @defgroup RCC_APB7_Peripheral_Clock_Enable_Disable_Status APB7 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB7 peripheral clock is enabled or not.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()      (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_SYSCFGEN) != 0U)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()        (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_SPI3EN) != 0U)
#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()     (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_LPUART1EN) != 0U)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()        (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_I2C3EN) != 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()      (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_LPTIM1EN) != 0U)
#define __HAL_RCC_COMP_IS_CLK_ENABLED()        (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_COMPEN) != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()      (READ_BIT(RCC->APB7ENR, RCC_APB7ENR_RTCAPBEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Force_Release_Reset AHB1 Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB1_FORCE_RESET()           WRITE_REG(RCC->AHB1RSTR, 0xFFFFFFFFU)
#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_FORCE_RESET()         SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_GPDMA1RST)
#endif /* GPDMA1 */
#define __HAL_RCC_CRC_FORCE_RESET()            SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_CRCRST)
#define __HAL_RCC_TSC_FORCE_RESET()            SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_TSCRST)

#define __HAL_RCC_AHB1_RELEASE_RESET()         WRITE_REG(RCC->AHB1RSTR, 0x00000000U)
#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_RELEASE_RESET()       CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_GPDMA1RST)
#endif /* GPDMA1 */
#define __HAL_RCC_CRC_RELEASE_RESET()          CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_CRCRST)
#define __HAL_RCC_TSC_RELEASE_RESET()          CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_TSCRST)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Force_Release_Reset AHB2 Peripheral Force Release Reset
  * @brief  Force or release AHB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB2_FORCE_RESET()           WRITE_REG(RCC->AHB2RSTR, 0xFFFFFFFFU)
#define __HAL_RCC_GPIOA_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOARST)
#define __HAL_RCC_GPIOB_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOBRST)
#define __HAL_RCC_GPIOC_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOCRST)
#define __HAL_RCC_GPIOH_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOHRST)
#define __HAL_RCC_AES_FORCE_RESET()            SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_AESRST)
#define __HAL_RCC_HASH_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_HASHRST)
#define __HAL_RCC_RNG_FORCE_RESET()            SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_RNGRST)
#if defined(SAES)
#define __HAL_RCC_SAES_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_SAESRST)
#endif /* SAES */
#if defined(HSEM)
#define __HAL_RCC_HSEM_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_HSEMRST)
#endif /* HSEM */
#define __HAL_RCC_PKA_FORCE_RESET()            SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_PKARST)
#define __HAL_RCC_AHB2_RELEASE_RESET()         WRITE_REG(RCC->AHB2RSTR, 0x00000000U)
#define __HAL_RCC_GPIOA_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOARST)
#define __HAL_RCC_GPIOB_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOBRST)
#define __HAL_RCC_GPIOC_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOCRST)
#define __HAL_RCC_GPIOH_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOHRST)
#define __HAL_RCC_AES_RELEASE_RESET()          CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_AESRST)
#define __HAL_RCC_HASH_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_HASHRST)
#define __HAL_RCC_RNG_RELEASE_RESET()          CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_RNGRST)
#if defined(SAES)
#define __HAL_RCC_SAES_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_SAESRST)
#endif /* SAES */
#if defined(HSEM)
#define __HAL_RCC_HSEM_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_HSEMRST)
#endif /* HSEM */
#define __HAL_RCC_PKA_RELEASE_RESET()          CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_PKARST)
/**
  * @}
  */

/** @defgroup RCC_AHB4_Force_Release_Reset AHB4 Peripheral Force Release Reset
  * @brief  Force or release AHB4 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB4_FORCE_RESET()           WRITE_REG(RCC->AHB4RSTR, 0xFFFFFFFFU)
#define __HAL_RCC_ADC4_FORCE_RESET()           SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_ADC4RST)

#define __HAL_RCC_AHB4_RELEASE_RESET()         WRITE_REG(RCC->AHB4RSTR, 0x00000000U)
#define __HAL_RCC_ADC4_RELEASE_RESET()         CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_ADC4RST)
/**
  * @}
  */

/** @defgroup RCC_AHB5_Force_Release_Reset AHB5 Peripheral Force Release Reset
  * @brief  Force or release AHB5 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB5_FORCE_RESET()           WRITE_REG(RCC->AHB5RSTR, 0xFFFFFFFFU)
#define __HAL_RCC_RADIO_FORCE_RESET()          SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_RADIORST)
#if defined(PTACONV)
#define __HAL_RCC_PTACONV_FORCE_RESET()        SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_PTACONVRST)
#endif /* PTACONV */

#define __HAL_RCC_AHB5_RELEASE_RESET()         WRITE_REG(RCC->AHB5RSTR, 0x00000000U)
#define __HAL_RCC_RADIO_RELEASE_RESET()        CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_RADIORST)
#if defined(PTACONV)
#define __HAL_RCC_PTACONV_RELEASE_RESET()      CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_PTACONVRST)
#endif /* PTACONV */
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_FORCE_RESET()           do { \
                                                    WRITE_REG(RCC->APB1RSTR1, 0xFFFFFFFFU); \
                                                    WRITE_REG(RCC->APB1RSTR2, 0xFFFFFFFFU); \
                                                  } while(0)
#define __HAL_RCC_TIM2_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)
#if defined(TIM3)
#define __HAL_RCC_TIM3_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)
#endif /* TIM3 */
#if defined(USART2)
#define __HAL_RCC_USART2_FORCE_RESET()         SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_FORCE_RESET()         SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_LPTIM2RST)
#endif /* LPTIM2 */

#define __HAL_RCC_APB1_RELEASE_RESET()         do { \
                                                    WRITE_REG(RCC->APB1RSTR1, 0x00000000U); \
                                                    WRITE_REG(RCC->APB1RSTR2, 0x00000000U); \
                                                  } while(0)
#define __HAL_RCC_TIM2_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)
#if defined(TIM3)
#define __HAL_RCC_TIM3_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)
#endif /* TIM3 */
#if defined(USART2)
#define __HAL_RCC_USART2_RELEASE_RESET()       CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_RELEASE_RESET()       CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_LPTIM2RST)
#endif /* LPTIM2 */
/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()           WRITE_REG(RCC->APB2RSTR, 0xFFFFFFFFU)
#if defined(TIM1)
#define __HAL_RCC_TIM1_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)
#endif /* TIM1 */
#if defined(SPI1)
#define __HAL_RCC_SPI1_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)
#endif /* SPI1 */
#define __HAL_RCC_USART1_FORCE_RESET()         SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)
#define __HAL_RCC_TIM16_FORCE_RESET()          SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)
#if defined(TIM17)
#define __HAL_RCC_TIM17_FORCE_RESET()          SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)
#endif /* SAI1 */

#define __HAL_RCC_APB2_RELEASE_RESET()         WRITE_REG(RCC->APB2RSTR, 0x00000000U)
#define __HAL_RCC_TIM1_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)
#if defined(SPI1)
#define __HAL_RCC_SPI1_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)
#endif /* SPI1 */
#define __HAL_RCC_USART1_RELEASE_RESET()       CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)
#define __HAL_RCC_TIM16_RELEASE_RESET()        CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)
#if defined(TIM17)
#define __HAL_RCC_TIM17_RELEASE_RESET()        CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)
#endif /* SAI1 */
/**
  * @}
  */

/** @defgroup RCC_APB7_Force_Release_Reset APB7 Peripheral Force Release Reset
  * @brief  Force or release APB7 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB7_FORCE_RESET()           WRITE_REG(RCC->APB7RSTR, 0xFFFFFFFFU)
#define __HAL_RCC_SYSCFG_FORCE_RESET()         SET_BIT(RCC->APB7RSTR, RCC_APB7RSTR_SYSCFGRST)
#define __HAL_RCC_SPI3_FORCE_RESET()           SET_BIT(RCC->APB7RSTR, RCC_APB7RSTR_SPI3RST)
#define __HAL_RCC_LPUART1_FORCE_RESET()        SET_BIT(RCC->APB7RSTR, RCC_APB7RSTR_LPUART1RST)
#define __HAL_RCC_I2C3_FORCE_RESET()           SET_BIT(RCC->APB7RSTR, RCC_APB7RSTR_I2C3RST)
#define __HAL_RCC_LPTIM1_FORCE_RESET()         SET_BIT(RCC->APB7RSTR, RCC_APB7RSTR_LPTIM1RST)
#define __HAL_RCC_COMP_FORCE_RESET()           SET_BIT(RCC->APB7RSTR, RCC_APB7RSTR_COMPRST)

#define __HAL_RCC_APB7_RELEASE_RESET()         WRITE_REG(RCC->APB7RSTR, 0x00000000U)
#define __HAL_RCC_SYSCFG_RELEASE_RESET()       CLEAR_BIT(RCC->APB7RSTR, RCC_APB7RSTR_SYSCFGRST)
#define __HAL_RCC_SPI3_RELEASE_RESET()         CLEAR_BIT(RCC->APB7RSTR, RCC_APB7RSTR_SPI3RST)
#define __HAL_RCC_LPUART1_RELEASE_RESET()      CLEAR_BIT(RCC->APB7RSTR, RCC_APB7RSTR_LPUART1RST)
#define __HAL_RCC_I2C3_RELEASE_RESET()         CLEAR_BIT(RCC->APB7RSTR, RCC_APB7RSTR_I2C3RST)
#define __HAL_RCC_LPTIM1_RELEASE_RESET()       CLEAR_BIT(RCC->APB7RSTR, RCC_APB7RSTR_LPTIM1RST)
#define __HAL_RCC_COMP_RELEASE_RESET()         CLEAR_BIT(RCC->APB7RSTR, RCC_APB7RSTR_COMPRST)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enable_Disable AHB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_GPDMA1SMEN)
#endif /* GPDMA1 */
#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN)
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN)
#define __HAL_RCC_TSC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_TSCSMEN)
#define __HAL_RCC_RAMCFG_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_RAMCFGSMEN)
#if defined(GTZC_TZSC)
#define __HAL_RCC_GTZC1_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_GTZC1SMEN)
#endif /* GTZC_TZSC */
#define __HAL_RCC_ICACHE_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_ICACHESMEN)
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN)

#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_GPDMA1SMEN)
#endif /* GPDMA1 */
#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN)
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN)
#define __HAL_RCC_TSC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_TSCSMEN)
#define __HAL_RCC_RAMCFG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_RAMCFGSMEN)
#if defined(GTZC_TZSC)
#define __HAL_RCC_GTZC1_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_GTZC1SMEN)
#endif /* GTZC_TZSC */
#define __HAL_RCC_ICACHE_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_ICACHESMEN)
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enable_Disable AHB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN)
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOHSMEN)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN)
#define __HAL_RCC_HASH_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_HASHSMEN)
#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN)
#if defined(SAES)
#define __HAL_RCC_SAES_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SAESSMEN)
#endif /* SAES */
#define __HAL_RCC_PKA_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_PKASMEN)
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN)

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN)
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOHSMEN)
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN)
#define __HAL_RCC_HASH_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_HASHSMEN)
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN)
#if defined(SAES)
#define __HAL_RCC_SAES_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SAESSMEN)
#endif /* SAES */
#define __HAL_RCC_PKA_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_PKASMEN)
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN)
/**
  * @}
  */

/** @defgroup RCC_AHB4_Clock_Sleep_Enable_Disable AHB4SMENR Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB4SMENR peripheral clock during Low Power (Sleep and STOP ) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB4SMENR, RCC_AHB4SMENR_PWRSMEN)
#define __HAL_RCC_ADC4_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB4SMENR, RCC_AHB4SMENR_ADC4SMEN)

#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB4SMENR, RCC_AHB4SMENR_PWRSMEN)
#define __HAL_RCC_ADC4_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB4SMENR, RCC_AHB4SMENR_ADC4SMEN)
/**
  * @}
  */

/** @defgroup RCC_AHB5_Clock_Sleep_Enable_Disable AHB5SMENR Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB5SMENR peripheral clock during Low Power (Sleep and STOP ) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
#define __HAL_RCC_RADIO_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB5SMENR, RCC_AHB5SMENR_RADIOSMEN)
#define __HAL_RCC_RADIO_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB5SMENR, RCC_AHB5SMENR_RADIOSMEN)

#if defined(PTACONV)
#define __HAL_RCC_PTACONV_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5SMENR, RCC_AHB5SMENR_PTACONVSMEN)
#define __HAL_RCC_PTACONV_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5SMENR, RCC_AHB5SMENR_PTACONVSMEN)
#endif /* PTACONV */
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests APB clock.
  * @{
  */
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN)
#if defined(TIM3)
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN)
#endif /* TIM3 */
#if defined(WWDG)
#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN)
#endif /* WWDG */
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPTIM2SMEN)
#endif /* LPTIM2 */

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN)
#if defined(TIM3)
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN)
#endif /* TIM3 */
#if defined(WWDG)
#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN)
#endif /* WWDG */
#if defined(USART2)
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPTIM2SMEN)
#endif /* LPTIM2 */
/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Sleep_Enable_Disable APB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP mode, the pseripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests APB clock.
  * @{
  */
#if defined(TIM1)
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN)
#endif /* TIM1 */
#if defined(SPI1)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN)
#endif /* SPI1 */
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN)
#if defined(TIM17)
#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN)
#endif /* SAI1 */

#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN)
#if defined(SPI1)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN)
#endif /* SPI1 */
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN)
#if defined(TIM17)
#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN)
#endif /* SAI1 */
/**
  * @}
  */

/** @defgroup RCC_APB7_Clock_Sleep_Enable_Disable APB7 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB7 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests APB clock.
  * @{
  */
#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_SYSCFGSMEN)
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_SPI3SMEN)
#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_LPUART1SMEN)
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_I2C3SMEN)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_LPTIM1SMEN)
#define __HAL_RCC_COMP_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_COMPSMEN)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB7SMENR, RCC_APB7SMENR_RTCAPBSMEN)

#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_SYSCFGSMEN)
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_SPI3SMEN)
#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_LPUART1SMEN)
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_I2C3SMEN)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_LPTIM1SMEN)
#define __HAL_RCC_COMP_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_COMPSMEN)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB7SMENR, RCC_APB7SMENR_RTCAPBSMEN)
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enabled_Status AHB1 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the AHB1 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#if defined(GPDMA1)
#define __HAL_RCC_GPDMA1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_GPDMA1SMEN) != 0U)
#endif /* GPDMA1 */
#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN) != 0U)
#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()         (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN) != 0U)
#define __HAL_RCC_TSC_IS_CLK_SLEEP_ENABLED()         (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_TSCSMEN) != 0U)
#define __HAL_RCC_RAMCFG_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_RAMCFGSMEN) != 0U)
#if defined(GTZC_TZSC)
#define __HAL_RCC_GTZC1_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_GTZC1SMEN) != 0U)
#endif /* GTZC_TZSC */
#define __HAL_RCC_ICACHE_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_ICACHESMEN) != 0U)
#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enabled_Status AHB2 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the AHB2 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN) != 0U)
#define __HAL_RCC_GPIOH_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOHSMEN) != 0U)
#define __HAL_RCC_AES_IS_CLK_SLEEP_ENABLED()         (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN) != 0U)
#define __HAL_RCC_HASH_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_HASHSMEN) != 0U)
#define __HAL_RCC_RNG_IS_CLK_SLEEP_ENABLED()         (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN) != 0U)
#if defined(SAES)
#define __HAL_RCC_SAES_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SAESSMEN) != 0U)
#endif /* SAES */
#define __HAL_RCC_PKA_IS_CLK_SLEEP_ENABLED()         (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_PKASMEN) != 0U)
#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB4_Peripheral_Clock_Sleep_Enabled_Status AHB4 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the AHB4 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_PWR_IS_CLK_SLEEP_ENABLED()         (READ_BIT(RCC->AHB4SMENR, RCC_AHB4SMENR_PWRSMEN) != 0U)
#define __HAL_RCC_ADC4_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->AHB4SMENR, RCC_AHB4SMENR_ADC4SMEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB5_Peripheral_Clock_Sleep_Enabled_Status AHB5 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the AHB5 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_RADIO_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->AHB5SMENR, RCC_AHB5SMENR_RADIOSMEN) != 0U)
#if defined(PTACONV)
#define __HAL_RCC_PTACONV_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB5SMENR, RCC_AHB5SMENR_PTACONVSMEN) != 0U)
#endif /* PTACONV */
/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enabled_Status APB1 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the APB1 peripheral clock during Low Power (Sleep) is enabled or not.
  * @{
  */
#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN) != 0U)
#if defined(TIM3)
#define __HAL_RCC_TIM3_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN) != 0U)
#endif /* TIM3 */
#if defined(WWDG)
#define __HAL_RCC_WWDG_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN) != 0U)
#endif /* WWDG */
#if defined(USART2)
#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN) != 0U)
#endif /* USART2 */
#if defined(I2C1)
#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN) != 0U)
#endif /* I2C1 */
#if defined(LPTIM2)
#define __HAL_RCC_LPTIM2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPTIM2SMEN) != 0U)
#endif /* LPTIM2 */
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Sleep_Enabled_Status APB2 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the APB2 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @{
  */
#if defined(TIM1)
#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN) != 0U)
#endif /* TIM1 */
#if defined(SPI1)
#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN) != 0U)
#endif /* SPI1 */
#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN) != 0U)
#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN) != 0U)
#if defined(TIM17)
#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN) != 0U)
#endif /* TIM17 */
#if defined(SAI1)
#define __HAL_RCC_SAI1_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN) != 0U)
#endif /* SAI1 */
/**
  * @}
  */

/** @defgroup RCC_APB7_Peripheral_Clock_Sleep_Enabled_Status APB7 Peripheral Clock Sleep Enabled Status
  * @brief  Check whether the APB7 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_SYSCFGSMEN) != 0U)
#define __HAL_RCC_SPI3_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_SPI3SMEN) != 0U)
#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_LPUART1SMEN) != 0U)
#define __HAL_RCC_I2C3_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_I2C3SMEN) != 0U)
#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_LPTIM1SMEN) != 0U)
#define __HAL_RCC_COMP_IS_CLK_SLEEP_ENABLED()        (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_COMPSMEN) != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB7SMENR, RCC_APB7SMENR_RTCAPBSMEN) != 0U)
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
#define __HAL_RCC_BACKUPRESET_FORCE()             SET_BIT(RCC->BDCR1, RCC_BDCR1_BDRST)
#define __HAL_RCC_BACKUPRESET_RELEASE()           CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_BDRST)
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



/** @brief  Macros to enable or disable the Internal Low Speed oscillator LSI1.
  * @note   After enabling the LSI1, the application software should wait on
  *         LSI1RDY flag to be set indicating that LSI1 clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   When the IWDG is started the LSI clock is forced on and cannot be disabled.
  *         When both LSI1 and LSI2 are disabled LSI1 will be forced on. When LSI selects
  *         LSI2 RC source, the LSI1 RC source can be disabled.
  * @note   When the LSI1 is stopped, LSI1RDY flag goes low after 3 LSI1 oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI1_ENABLE()                   SET_BIT(RCC->BDCR1, RCC_BDCR1_LSI1ON)
#define __HAL_RCC_LSI1_DISABLE()                  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSI1ON)

/** @brief  Macro to set Low-speed clock LSI1 divider.
  * @note   Only LSI1 clock can be divided
  * @note   This bit can be written only when the LSI1 is disabled (LSI1ON = 0 and LSI1RDY = 0).
  *         The LSI1PREDIV cannot be changed if the LSI1 is used by the IWDG or by the RTC.
  * @param  __DIVIDER__ : specifies the divider value
  *          This parameter can be one of the following values
  *          @arg @ref RCC_LSI_DIV1
  *          @arg @ref RCC_LSI_DIV128
  * @retval None
  */
#define __HAL_RCC_LSI_DIV_CONFIG(__DIVIDER__)     MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV, __DIVIDER__)

#if defined(RCC_LSI2_SUPPORT)
/** @brief  Macros to enable or disable the Internal Low Speed oscillator LSI2.
  * @note   After enabling the LSI2, the application software should wait on
  *         LSI2RDY flag to be set indicating that LSI2 clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   When the IWDG is started the LSI clock is forced on and cannot be disabled.
  *         When both LSI1 and LSI2 are disabled LSI1 will be forced on. When LSI selects
  *         LSI2 RC source, the LSI1 RC source can be disabled.
  * @note   When the LSI2 is stopped, LSI2RDY flag goes low after 3 LSI1 oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI2_ENABLE()                   SET_BIT(RCC->BDCR1, RCC_BDCR1_LSI2ON)
#define __HAL_RCC_LSI2_DISABLE()                  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSI2ON)
#endif /* RCC_BDCR1_LSI2ON */

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL1 and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL1 as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY or shutdown modes.
  * @note   HSERDY flag may remain high when HSEON bit is cleared. This is when the 2.4 GHz
  *         RADIO uses the HSE32 as its kernel clock.
  * @param  __STATE__: specifies the new state of the HSE.
  *         This parameter can be a combination of the following values:
  *            @arg @ref RCC_HSE_OFF    Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                                     6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON     Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_DIV1   Divide HSE by 1 for SYSCLK
  *            @arg @ref RCC_HSE_DIV2   Divide HSE by 2 for SYSCLK
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)           MODIFY_REG(RCC->CR, (RCC_CR_HSEON | RCC_CR_HSEPRE), __STATE__)


/** @brief   Macro to enable or disable the LSE system clock.
  * @note    This clock can be used by any peripheral when its source clock is the LSE or at system
  *          in case of one of the LSCOSEL, MCO or CSS on LSE is needed.
  * @note    The LSESYS clock can be generated even if LSESYSEN= 0 if the LSE clock is requested by
  *          the CSS on LSE, by a peripheral or any other source clock using LSE.
  * @retval None
  */
#define __HAL_RCC_LSESYS_ENABLE()                 SET_BIT(RCC->BDCR1,RCC_BDCR1_LSESYSEN)
#define __HAL_RCC_LSESYS_DISABLE()                CLEAR_BIT(RCC->BDCR1,RCC_BDCR1_LSESYSEN)


/** @brief  Macros to enable or disable LSE clock glitch filter .
  * @note   The glitches on LSE can be filtred by setting the LSEGFON.
  * @note   LSEGFON must be written when the LSE is disabled (LSEON = 0 and LSERDY = 0).
  * @retval None
  */
#define __HAL_RCC_LSE_GlitchFilter_ENABLE()       SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEGFON )
#define __HAL_RCC_LSE_GlitchFilter_DISABLE()      CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSEGFON )

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
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON_RTC_ONLY      Turn ON the LSE oscillator to be used only for RTC.
  *            @arg @ref RCC_LSE_ON               Turn ON the LSE oscillator to be used by any peripheral.
  *            @arg @ref RCC_LSE_BYPASS_RTC_ONLY  LSE oscillator bypassed with external clock to be used only for RTC.
  *            @arg @ref RCC_LSE_BYPASS           LSE oscillator bypassed with external clock to be used by any peripheral.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)           do {                                                                \
                                                    if((__STATE__) == RCC_LSE_ON_RTC_ONLY)                            \
                                                    {                                                                 \
                                                      SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEON);                           \
                                                    }                                                                 \
                                                    else if((__STATE__) == RCC_LSE_ON)                                \
                                                    {                                                                 \
                                                      SET_BIT(RCC->BDCR1, (RCC_BDCR1_LSEON | RCC_BDCR1_LSESYSEN));    \
                                                    }                                                                 \
                                                    else if((__STATE__) == RCC_LSE_BYPASS)                            \
                                                    {                                                                 \
                                                      SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEBYP);                          \
                                                      SET_BIT(RCC->BDCR1, (RCC_BDCR1_LSEON | RCC_BDCR1_LSESYSEN));    \
                                                    }                                                                 \
                                                    else if((__STATE__) == RCC_LSE_BYPASS)                            \
                                                    {                                                                 \
                                                      SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEBYP);                          \
                                                      SET_BIT(RCC->BDCR1, RCC_BDCR1_LSEON);                           \
                                                    }                                                                 \
                                                    else                                                              \
                                                    {                                                                 \
                                                      CLEAR_BIT(RCC->BDCR1, (RCC_BDCR1_LSEON | RCC_BDCR1_LSESYSEN));  \
                                                      CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSEBYP);                        \
                                                    }                                                                 \
                                                  } while(0)


/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  *
  * @param  __RTC_CLKSOURCE__: specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_DISABLE  RTC clock is disabled.
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
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_RTCSEL, (__RTC_CLKSOURCE__))


/** @brief  Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_DISABLE  RTC clock is disabled.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  */
#define  __HAL_RCC_GET_RTC_SOURCE() READ_BIT(RCC->BDCR1, RCC_BDCR1_RTCSEL)

/** @brief  Macros to enable or disable the main PLL1.
  * @note   After enabling the main PLL1, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL1 clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL1 can not be disabled if it is used as system clock source
  * @note   The main PLL1 is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL1_ENABLE()                              SET_BIT(RCC->CR, RCC_CR_PLL1ON)
#define __HAL_RCC_PLL1_DISABLE()                             CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON)

/**
  * @brief  Enables or disables each clock output (PLL_PCLK, PLL_QCLK, PLL_RCLK)
  * @note   Enabling/disabling  Those Clocks can be any time without the need to stop the PLL1,
  *         This is mainly used to save Power.
  * @param  __PLL1_CLOCKOUT__: specifies the PLL1 clock to be output
  *          This parameter can be a combination of the following values:
  *            @arg RCC_PLL1_PCLK: This clock can be used to generate an accurate clock for SAI1
  *                                interface and/or ADC4
  *            @arg RCC_PLL1_QCLK: This Clock is used to generate an accurate clock for RNG (<= 48 MHz).
  *            @arg RCC_PLL1_RCLK: This Clock is used to generate and high speed system clock (up to 100MHz)
  * @retval None
  *
  */
#define __HAL_RCC_PLL1CLKOUT_ENABLE(__PLL1_CLOCKOUT__)       SET_BIT(RCC->PLL1CFGR, (__PLL1_CLOCKOUT__))
#define __HAL_RCC_PLL1CLKOUT_DISABLE(__PLL1_CLOCKOUT__)      CLEAR_BIT(RCC->PLL1CFGR, (__PLL1_CLOCKOUT__))

/**
  * @brief  Macro to get the PLL1 clock output enable status.
  * @param  __PLL1_CLOCKOUT__ specifies the PLL1 clock to be output.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL1_PCLK
  *            @arg RCC_PLL1_QCLK
  *            @arg RCC_PLL1_RCLK
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLL1CLKOUT_CONFIG(__PLL1_CLOCKOUT__)   READ_BIT(RCC->PLL1CFGR, (__PLL1_CLOCKOUT__))

/**
  * @brief  Macro to configures the main PLL1 clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL1 is disabled.
  * @param  __PLL1SOURCE__: specifies the PLL1 entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL1 clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL1 clock entry
  * @param  __PLL1M__: specifies the division factor for PLL1 VCO input clock
  *         This parameter must be a number between 1 and 8.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 4 to 16 MHz.
  * @param  __PLL1N__: specifies the multiplication factor for PLL1 VCO output clock
  *         This parameter must be a number between 4 and 512.
  * @note   You have to set the PLLN parameter correctly to ensure that the VCO output
  *         frequency is between 128 and 544 MHz.
  * @param  __PLL1P__: specifies the division factor for system  clock.
  *          This parameter must be an even number between 2 and 128.
  * @param  __PLL1Q__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @param  __PLL1R__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @retval None
  */
#define __HAL_RCC_PLL1_CONFIG(__PLL1SOURCE__, __PLL1M__, __PLL1N__, __PLL1P__, __PLL1Q__, __PLL1R__) \
  do{ \
    MODIFY_REG(RCC->PLL1CFGR, (RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M), ((__PLL1SOURCE__) | (((__PLL1M__) - 1U) << RCC_PLL1CFGR_PLL1M_Pos)));     \
    WRITE_REG(RCC->PLL1DIVR, (((__PLL1N__) - 1U) | (((__PLL1P__) - 1U) << RCC_PLL1DIVR_PLL1P_Pos) | (((__PLL1Q__) - 1U) << RCC_PLL1DIVR_PLL1Q_Pos) | \
                              (((__PLL1R__) - 1U) << RCC_PLL1DIVR_PLL1R_Pos)));                                                                     \
  } while(0)

/**
  * @brief  Macro to configure the PLL1 clock source.
  * @note   This function must be used only when PLL1 is disabled.
  * @param  __PLL1SOURCE__: specifies the PLLs entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_NONE: No clock selected as PLL1 clock entry (used to save Power)
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL1 clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL1 clock entry
  *
  */
#define __HAL_RCC_PLL1_PLLSOURCE_CONFIG(__PLL1SOURCE__)  \
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC, (__PLL1SOURCE__))

/**
  *@brief  Macro to select the PLL1 VCO input frequency range.
  * @param  __VCOINPUTRANGE__: specifies VCO input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL_VCOINPUT_RANGE0: Range frequency is between 4 and 8 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE1: Range frequency is between 8 and 16 MHz
  * @retval None
  */
#define __HAL_RCC_PLL1_VCOINPUTRANGE_CONFIG(__VCOINPUTRANGE__)   \
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RGE, (__VCOINPUTRANGE__))

/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL1 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL1
  * @retval None
  */
#define __HAL_RCC_PLL1_FRACN_ENABLE()                SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN)
#define __HAL_RCC_PLL1_FRACN_DISABLE()               CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN)

/**
  * @brief  Macro to configures the main PLL1 clock fractional part of The multiplication factor
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL1 VCO
  * @param  __PLL1FRACN__: specifies Fractional part of the multiplication factor for PLL1 VCO
  *                       It should be a value between 0 and 8191
  * @retval None
  */
#define __HAL_RCC_PLL1_FRACN_CONFIG(__PLL1FRACN__)   WRITE_REG(RCC->PLL1FRACR, (__PLL1FRACN__) << RCC_PLL1FRACR_PLL1FRACN_Pos)


/**
  * @brief  Macro to get the oscillator used as PLL1 clock source.
  * @retval The oscillator used as PLL1 clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_NONE: No oscillator is used as PLL1 clock source.
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL1 clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL1 clock source.
  */
#define __HAL_RCC_GET_PLL1_OSCSOURCE() (RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1SRC)

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__: specifies the system clock source.
  *          This parameter can be one of the following values:
  *              - RCC_SYSCLKSOURCE_HSI: HSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSE: HSE oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_PLLCLK: PLL1 output is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, (__SYSCLKSOURCE__))

/**
  * @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              - RCC_SYSCLKSOURCE_STATUS_HSI: HSI used as system clock.
  *              - RCC_SYSCLKSOURCE_STATUS_HSE: HSE used as system clock.
  *              - RCC_SYSCLKSOURCE_STATUS_PLL1CLK: PLL1 used as system clock.
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
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSEDRV, (__LSEDRIVE__))

/**
  * @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK  System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI  HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE  HSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLL1RCLK  Main PLL1 clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI  LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE  LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLL1PCLK  pll1pclk selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLL1QCLK  pll1qclk selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HCLK5  phclk5 selected as MCO source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR1, (RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/**
  * @brief  Enable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to enable
  *         the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSI1RDY         LSI1 ready interrupt
  *            @arg @ref RCC_IT_LSERDY          LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY          HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY          HSE ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY         PLL1 ready interrupt
  *            @arg @ref RCC_IT_LSI2RDY         LSI2 ready interrupt(*)
#if defined(RCC_CCIPR2_ASSEL)
  *            @arg @ref RCC_IT_CAPTURE_ERROR   Capture Error Interrupt flag(*)
  *            @arg @ref RCC_IT_COMPARER        Comparer Interrupt flag(*)
  *            @arg @ref RCC_IT_CAPTURE_TRIGGER Capture Trigger Interrupt flag(*)
#endif
  * (*) Feature not available on all devices of the family
  * @retval None
  */
#if defined(RCC_CCIPR2_ASSEL)
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) ((((__INTERRUPT__) >> 5U) == 0U) ? \
                                             SET_BIT(RCC->CIER,1U << ((__INTERRUPT__) & RCC_FLAG_MASK)) : \
                                             SET_BIT(RCC->ASIER,1U << ((__INTERRUPT__) & RCC_FLAG_MASK)))
#else
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))
#endif /* RCC_CCIPR2_ASSEL */

/**
  * @brief Disable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to disable
  *        the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSI1RDY         LSI1 ready interrupt
  *            @arg @ref RCC_IT_LSERDY          LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY          HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY          HSE ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY         PLL1 ready interrupt
  *            @arg @ref RCC_IT_LSI2RDY         LSI2 ready interrupt(*)
#if defined(RCC_CCIPR2_ASSEL)
  *            @arg @ref RCC_IT_CAPTURE_ERROR   Capture Error Interrupt flag(*)
  *            @arg @ref RCC_IT_COMPARER        Comparer Interrupt flag(*)
  *            @arg @ref RCC_IT_CAPTURE_TRIGGER Capture Trigger Interrupt flag(*)
#endif
  * (*) Feature not available on all devices of the family
  * @retval None
  */
#if defined(RCC_CCIPR2_ASSEL)
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) ((((__INTERRUPT__) >> 5U) == 0U) ? \
                                              CLEAR_BIT(RCC->CIER,1U << ((__INTERRUPT__) & RCC_FLAG_MASK)) : \
                                              CLEAR_BIT(RCC->ASIER,1U << ((__INTERRUPT__) & RCC_FLAG_MASK)))
#else
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))
#endif /* RCC_CCIPR2_ASSEL */

/**
  * @brief  Clear the RCC's interrupt pending bits (Perform Byte access to RCC_CIR[23:16]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSI1RDY         LSI1 ready interrupt
  *            @arg @ref RCC_IT_LSERDY          LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY          HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY          HSE ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY         PLL1 ready interrupt
  *            @arg @ref RCC_IT_LSI2RDY         LSI2 ready interrupt(*)
#if defined(RCC_CCIPR2_ASSEL)
  *            @arg @ref RCC_IT_CAPTURE_ERROR   Capture Error Interrupt flag(*)
  *            @arg @ref RCC_IT_COMPARER        Comparer Interrupt flag(*)
  *            @arg @ref RCC_IT_CAPTURE_TRIGGER Capture Trigger Interrupt flag(*)
#endif
  * (*) Feature not available on all devices of the family
  * @retval None
  */
#if defined(RCC_CCIPR2_ASSEL)
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) ((((__INTERRUPT__) >> 5U) == 0U) ? \
                                           WRITE_REG(RCC->CICR,1U << ((__INTERRUPT__) & RCC_FLAG_MASK)) : \
                                           CLEAR_BIT(RCC->ASSR,1U << ((__INTERRUPT__) & RCC_FLAG_MASK)))
#else
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) WRITE_REG(RCC->CICR, (__INTERRUPT__))
#endif /* RCC_CCIPR2_ASSEL */

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSI1RDY         LSI1 ready interrupt
  *            @arg @ref RCC_IT_LSERDY          LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY          HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY          HSE ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY         PLL1 ready interrupt
  *            @arg @ref RCC_IT_LSI2RDY         LSI2 ready interrupt(*)
#if defined(RCC_CCIPR2_ASSEL)
  *            @arg @ref RCC_IT_CAPTURE_ERROR   Capture Error Interrupt flag(*)
  *            @arg @ref RCC_IT_COMPARER        Comparer Interrupt flag(*)
  *            @arg @ref RCC_IT_CAPTURE_TRIGGER Capture Trigger Interrupt flag(*)
#endif
  * (*) Feature not available on all devices of the family
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#if defined(RCC_CCIPR2_ASSEL)
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((((__INTERRUPT__) >> 5U) == 0U) ? \
                                         ((RCC->CIFR & (1U << ((__INTERRUPT__) & RCC_FLAG_MASK))) == (1U << ((__INTERRUPT__) & RCC_FLAG_MASK))) : \
                                         ((RCC->ASSR & (1U << ((__INTERRUPT__) & RCC_FLAG_MASK))) == (1U << ((__INTERRUPT__) & RCC_FLAG_MASK))))
#else
#define __HAL_RCC_GET_IT(__INTERRUPT__)  ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))
#endif /* RCC_CCIPR2_ASSEL */

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_FWRRST, RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_BORRST,
  *        RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST and RCC_FLAG_LPWRRST.
  * @retval None
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/**
  * @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HSIRDY   HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY   HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLL1RDY  PLL1 clock ready
  *            @arg @ref RCC_FLAG_LSERDY   LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD  Clock security system failure on LSE oscillator detection
  *            @arg @ref RCC_FLAG_LSI1RDY  LSI1 oscillator clock ready
  *            @arg @ref RCC_FLAG_LSI2RDY  LSI2 oscillator clock ready(*)
  *            @arg @ref RCC_FLAG_BORRST   BOR reset
  *            @arg @ref RCC_FLAG_OBLRST   OBLRST reset
  *            @arg @ref RCC_FLAG_PINRST   Pin reset
  *            @arg @ref RCC_FLAG_SFTRST   Software reset
  *            @arg @ref RCC_FLAG_IWDGRST  Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST  Window Watchdog reset(*)
  *            @arg @ref RCC_FLAG_LPWRRST  Low Power reset
  * (*) Feature not available on all devices of the family
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) ((((((((__FLAG__) >> 5U) == 1U) ? RCC->CR :                     \
                                          ((((__FLAG__) >> 5U) == 2U) ? RCC->BDCR1 :                   \
                                           ((((__FLAG__) >> 5U) == 3U) ? RCC->CSR : RCC->CIFR)))) &     \
                                        (1U << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) ? 1U : 0U)
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
#define PLL_VCOINPUTFREQ_MAX            16000000U /* Maximum VCO input frequency is 16 MHz */
#define PLL_VCOINPUTFREQ_MIN             4000000U /* Minimum VCO input frequency is 4 MHz */
#define HSE_TIMEOUT_VALUE               HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE               (2U)      /* 2 ms (minimum Tick + 1) */


/* Defines used for Flags */
#define CR_REG_INDEX                    (1U)
#define BDCR1_REG_INDEX                 (2U)
#define CSR_REG_INDEX                   (3U)
#if defined(RCC_CCIPR2_ASSEL)
/* Defines used for Interrupt Flags */
#define CIFR_REG_INDEX                  (0U)
#define ASSR_REG_INDEX                  (1U)
#endif /* RCC_CCIPR2_ASSEL */

#define RCC_FLAG_MASK                   (0x1FU)

/* Define used for IS_RCC_* below */
#define RCC_CLOCKTYPE_ALL               (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_HCLK5 | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK7)  /*!< All clocktype to configure */
#define RCC_OSCILLATORTYPE_ALL          (RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI)  /*!< All Oscillator to configure */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__)   (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE) || \
                                                 (((__OSCILLATOR__) & ~RCC_OSCILLATORTYPE_ALL) == 0x00U))

#define IS_RCC_HSE(__HSE__)                     (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON))

#define IS_RCC_HSEDIV(__HSEDIV__)               (((__HSEDIV__) == RCC_HSE_DIV1) || ((__HSEDIV__) == RCC_HSE_DIV2))

#define IS_RCC_LSE(__LSE__)                     (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON_RTC_ONLY) || \
                                                 ((__LSE__) == RCC_LSE_ON) || ((__LSE__) == RCC_LSE_BYPASS_RTC_ONLY) || \
                                                 ((__LSE__) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(__HSI__)                     (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (uint32_t)( RCC_ICSCR3_HSITRIM  >>  RCC_ICSCR3_HSITRIM_Pos))

#if defined(RCC_LSI2_SUPPORT)
#define IS_RCC_LSI(__LSI__)                     (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI1_ON) || \
                                                 ((__LSI__) == RCC_LSI2_ON))
#else
#define IS_RCC_LSI(__LSI__)                     (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI1_ON))
#endif /* RCC_BDCR1_LSI2ON */

#define IS_RCC_LSIDIV(__LSIDIV__)               (((__LSIDIV__) == RCC_LSI_DIV1) || ((__LSIDIV__) == RCC_LSI_DIV128))

#define IS_RCC_PLL(PLL1)                        (((PLL1) == RCC_PLL_NONE) ||((PLL1) == RCC_PLL_OFF) || \
                                                 ((PLL1) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(SOURCE)                (((SOURCE) == RCC_PLLSOURCE_HSI)  || \
                                                 ((SOURCE) == RCC_PLLSOURCE_HSE))

#define IS_RCC_PLLM_VALUE(VALUE)                ((1U <= (VALUE)) && ((VALUE) <= 8U))
#define IS_RCC_PLLN_VALUE(VALUE)                ((4U <= (VALUE)) && ((VALUE) <= 512U))
#define IS_RCC_PLLP_VALUE(VALUE)                ((1U <= (VALUE)) && ((VALUE) <= 128U))
#define IS_RCC_PLLQ_VALUE(VALUE)                ((1U <= (VALUE)) && ((VALUE) <= 128U))
#define IS_RCC_PLLR_VALUE(VALUE)                ((1U <= (VALUE)) && ((VALUE) <= 128U))

#define IS_RCC_PLL_VCOINPUTFREQ(VALUE)          ((PLL_VCOINPUTFREQ_MIN <= (VALUE)) && ((VALUE) <= PLL_VCOINPUTFREQ_MAX))

#define IS_RCC_PLLFRACN_VALUE(VALUE)            ((VALUE) <= (RCC_PLL1FRACR_PLL1FRACN >> RCC_PLL1FRACR_PLL1FRACN_Pos))

#define IS_RCC_CLOCKTYPE(__CLK__)               ((((__CLK__) & RCC_CLOCKTYPE_ALL) != 0x00UL) && (((__CLK__) & ~RCC_CLOCKTYPE_ALL) == 0x00UL))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                                 ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                                 ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))

#define IS_RCC_HCLK(__HCLK__)                   (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                                                 ((__HCLK__) == RCC_SYSCLK_DIV4)   || ((__HCLK__) == RCC_SYSCLK_DIV8)   || \
                                                 ((__HCLK__) == RCC_SYSCLK_DIV16))

#define IS_RCC_PCLK(__PCLK__)                   (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                                                 ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                                                 ((__PCLK__) == RCC_HCLK_DIV16))

#define IS_RCC_HCLK5_PLL1(__HCLK5__)            (((__HCLK5__) == RCC_SYSCLK_PLL1_DIV1) || ((__HCLK5__) == RCC_SYSCLK_PLL1_DIV2) || \
                                                 ((__HCLK5__) == RCC_SYSCLK_PLL1_DIV3) || ((__HCLK5__) == RCC_SYSCLK_PLL1_DIV4) || \
                                                 ((__HCLK5__) == RCC_SYSCLK_PLL1_DIV6))

#define IS_RCC_HCLK5_HSEHSI(__HCLK5__)          (((__HCLK5__) == RCC_SYSCLK_HSEHSI_DIV1) || ((__HCLK5__) == RCC_SYSCLK_HSEHSI_DIV2))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__)         (((__SOURCE__) == RCC_RTCCLKSOURCE_DISABLE) || \
                                                 ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)     || \
                                                 ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)     || \
                                                 ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32))

#define IS_RCC_MCO(__MCOX__)                    ((__MCOX__) == RCC_MCO1)

#define IS_RCC_MCO1SOURCE(__SOURCE__)           (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK)  || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK)   || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_HSI)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_HSE)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_PLL1RCLK) || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_LSI)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_LSE)      || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_PLL1PCLK) || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_PLL1QCLK) || \
                                                 ((__SOURCE__) == RCC_MCO1SOURCE_HCLK5))

#define IS_RCC_MCODIV(__DIV__)                  (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                                 ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                                 ((__DIV__) == RCC_MCODIV_16))

#define IS_RCC_LSE_DRIVE(__DRIVE__)             (((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

#define IS_RCC_ITEM_ATTRIBUTES(__ITEM__)        (((__ITEM__) != 0x00U) && (((__ITEM__) & ~RCC_ALL) == 0x00U))

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_RCC_ATTRIBUTES(__ATTRIBUTES__)       (((__ATTRIBUTES__)  == RCC_SEC_PRIV)   || \
                                                 ((__ATTRIBUTES__)  == RCC_SEC_NPRIV)  || \
                                                 ((__ATTRIBUTES__)  == RCC_NSEC_PRIV)  || \
                                                 ((__ATTRIBUTES__)  == RCC_NSEC_NPRIV))
#else
#define IS_RCC_ATTRIBUTES(__ATTRIBUTES__)       (((__ATTRIBUTES__) == RCC_NSEC_NPRIV) || ((__ATTRIBUTES__) == RCC_NSEC_PRIV))
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/**
  * @}
  */
/* Include RCC HAL Extended module */
#include "stm32wbaxx_hal_rcc_ex.h"

/* Exported functions ----------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions **********************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);
uint32_t          HAL_RCC_GetPCLK7Freq(void);
uint32_t          HAL_RCC_GetHCLK5Freq(void);
uint32_t          HAL_RCC_GetPLL1PFreq(void);
uint32_t          HAL_RCC_GetPLL1QFreq(void);
uint32_t          HAL_RCC_GetPLL1RFreq(void);
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

#endif /* __STM32WBAxx_HAL_RCC_H */
