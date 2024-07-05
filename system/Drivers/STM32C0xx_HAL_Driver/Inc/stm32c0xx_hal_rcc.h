/**
  ******************************************************************************
  * @file    stm32c0xx_hal_rcc.h
  * @author  MCD Application Team
   * @brief   Header file of RCC HAL module.
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
#ifndef STM32C0xx_HAL_RCC_H
#define STM32C0xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal_def.h"
#include "stm32c0xx_ll_rcc.h"

/** @addtogroup STM32C0xx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Constants
  * @{
  */

/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_LSE_TIMEOUT_VALUE     LSE_STARTUP_TIMEOUT  /* LSE timeout in ms        */
/**
  * @}
  */

/* Defines used for Flags */
#define RCC_CR_REG_INDEX          1U
#define RCC_CSR1_REG_INDEX        2U
#define RCC_CSR2_REG_INDEX        3U
#if defined(RCC_HSI48_SUPPORT)
#define RCC_CRRCR_REG_INDEX       4U
#endif /* RCC_HSI48_SUPPORT */

#define RCC_FLAG_MASK             0x1FU

/* Define used for IS_RCC_CLOCKTYPE() */
#define RCC_CLOCKTYPE_ALL     (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1)  /*!< All clocktype to configure */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */

#if defined(RCC_CR_HSIUSB48ON)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__)                                     \
  (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                               || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)     || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)     || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48) || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)     || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))
#else
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__)                                 \
  (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))
#endif /* RCC_CR_HSIUSB48ON */

#define IS_RCC_HSE(__HSE__)  (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                              ((__HSE__) == RCC_HSE_BYPASS))

#define IS_RCC_LSE(__LSE__)  (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                              ((__LSE__) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(__HSI__)  (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#if defined(RCC_CR_HSIUSB48ON)
#define IS_RCC_HSI48(__HSI48__)  (((__HSI48__) == RCC_HSI48_OFF) || ((__HSI48__) == RCC_HSI48_ON))
#endif /* RCC_CR_HSIUSB48ON */

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (uint32_t)127U)

#define IS_RCC_HSIDIV(__DIV__) (((__DIV__) == RCC_HSI_DIV1)  || ((__DIV__) == RCC_HSI_DIV2) || \
                                ((__DIV__) == RCC_HSI_DIV4)  || ((__DIV__) == RCC_HSI_DIV8) || \
                                ((__DIV__) == RCC_HSI_DIV16) || ((__DIV__) == RCC_HSI_DIV32)|| \
                                ((__DIV__) == RCC_HSI_DIV64) || ((__DIV__) == RCC_HSI_DIV128))

#define IS_RCC_LSI(__LSI__)  (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))


#define IS_RCC_CLOCKTYPE(__CLK__)  ((((__CLK__)\
                                      & RCC_CLOCKTYPE_ALL) != 0x00UL) && (((__CLK__) & ~RCC_CLOCKTYPE_ALL) == 0x00UL))
#if defined(RCC_HSI48_SUPPORT)
#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI)       || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE)       || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSIUSB48)  || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE)       || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#else
#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI)  || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE)  || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LSE)  || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LSI))
#endif /* RCC_HSI48_SUPPORT */

#if defined(RCC_CR_SYSDIV)
#define IS_RCC_SYSCLK(SYSCLK) (((SYSCLK) == RCC_SYSCLK_DIV1) || ((SYSCLK) == RCC_SYSCLK_DIV2) || \
                               ((SYSCLK) == RCC_SYSCLK_DIV3) || ((SYSCLK) == RCC_SYSCLK_DIV4) || \
                               ((SYSCLK) == RCC_SYSCLK_DIV5) || ((SYSCLK) == RCC_SYSCLK_DIV6) || \
                               ((SYSCLK) == RCC_SYSCLK_DIV7) || ((SYSCLK) == RCC_SYSCLK_DIV8))
#else
#define IS_RCC_SYSCLK(SYSCLK) ((SYSCLK) == RCC_SYSCLK_DIV1)
#endif /* RCC_CR_SYSDIV */

#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_HCLK_DIV1)   || ((HCLK) == RCC_HCLK_DIV2)   || \
                           ((HCLK) == RCC_HCLK_DIV4)   || ((HCLK) == RCC_HCLK_DIV8)   || \
                           ((HCLK) == RCC_HCLK_DIV16)  || ((HCLK) == RCC_HCLK_DIV64)  || \
                           ((HCLK) == RCC_HCLK_DIV128) || ((HCLK) == RCC_HCLK_DIV256) || \
                           ((HCLK) == RCC_HCLK_DIV512))

#define IS_RCC_PCLK(__PCLK__) (((__PCLK__) == RCC_APB1_DIV1) || ((__PCLK__) == RCC_APB1_DIV2) || \
                               ((__PCLK__) == RCC_APB1_DIV4) || ((__PCLK__) == RCC_APB1_DIV8) || \
                               ((__PCLK__) == RCC_APB1_DIV16))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32))

#if defined(STM32C011xx)
#define IS_RCC_MCO(__MCOX__) (((__MCOX__) == RCC_MCO1_PA8) || \
                              ((__MCOX__) == RCC_MCO1_PA9) || \
                              ((__MCOX__) == RCC_MCO1_PF2) || \
                              ((__MCOX__) == RCC_MCO2_PA8) || \
                              ((__MCOX__) == RCC_MCO2_PA10) || \
                              ((__MCOX__) == RCC_MCO2_PA14))
#else
#define IS_RCC_MCO(__MCOX__) (((__MCOX__) == RCC_MCO1_PA8) || \
                              ((__MCOX__) == RCC_MCO1_PA9) || \
                              ((__MCOX__) == RCC_MCO1_PF2) || \
                              ((__MCOX__) == RCC_MCO2_PA8) || \
                              ((__MCOX__) == RCC_MCO2_PA10) || \
                              ((__MCOX__) == RCC_MCO2_PA14) || \
                              ((__MCOX__) == RCC_MCO2_PA15) || \
                              ((__MCOX__) == RCC_MCO2_PB2))
#endif /* STM32C011xx */

#if defined(RCC_CR_HSIUSB48ON)
#define IS_RCC_MCO1SOURCE(__SOURCE__)  (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSI48) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_LSE))
#else
#define IS_RCC_MCO1SOURCE(__SOURCE__)  (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_LSE))
#endif /* RCC_CR_HSIUSB48ON */

#if defined(RCC_CR_HSIUSB48ON)
#define IS_RCC_MCO2SOURCE(__SOURCE__)  (((__SOURCE__) == RCC_MCO2SOURCE_NOCLOCK) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_SYSCLK) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSI48)   || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_LSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_LSE))
#else
#define IS_RCC_MCO2SOURCE(__SOURCE__)  (((__SOURCE__) == RCC_MCO2SOURCE_NOCLOCK) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_SYSCLK) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_LSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_LSE))
#endif /* RCC_CR_HSIUSB48ON */

#if defined(RCC_CFGR_MCOPRE_3)
#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16)|| ((__DIV__) == RCC_MCODIV_32) || \
                                ((__DIV__) == RCC_MCODIV_64)|| ((__DIV__) == RCC_MCODIV_128) || \
                                ((__DIV__) == RCC_MCODIV_256)|| ((__DIV__) == RCC_MCODIV_512) || \
                                ((__DIV__) == RCC_MCODIV_1024))
#else
#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16)|| ((__DIV__) == RCC_MCODIV_32) || \
                                ((__DIV__) == RCC_MCODIV_64)|| ((__DIV__) == RCC_MCODIV_128))
#endif /* RCC_CFGR_MCOPRE_3 */

#if defined(RCC_CFGR_MCO2PRE_3)
#define IS_RCC_MCO2DIV(__DIV__) (((__DIV__) == RCC_MCO2DIV_1) || ((__DIV__) == RCC_MCO2DIV_2) || \
                                 ((__DIV__) == RCC_MCO2DIV_4) || ((__DIV__) == RCC_MCO2DIV_8) || \
                                 ((__DIV__) == RCC_MCO2DIV_16)|| ((__DIV__) == RCC_MCO2DIV_32) || \
                                 ((__DIV__) == RCC_MCO2DIV_64)|| ((__DIV__) == RCC_MCO2DIV_128) || \
                                 ((__DIV__) == RCC_MCO2DIV_256)|| ((__DIV__) == RCC_MCO2DIV_512) || \
                                 ((__DIV__) == RCC_MCO2DIV_1024))
#else
#define IS_RCC_MCO2DIV(__DIV__) (((__DIV__) == RCC_MCO2DIV_1) || ((__DIV__) == RCC_MCO2DIV_2) || \
                                 ((__DIV__) == RCC_MCO2DIV_4) || ((__DIV__) == RCC_MCO2DIV_8) || \
                                 ((__DIV__) == RCC_MCO2DIV_16)|| ((__DIV__) == RCC_MCO2DIV_32) || \
                                 ((__DIV__) == RCC_MCO2DIV_64)|| ((__DIV__) == RCC_MCO2DIV_128))
#endif /* RCC_CFGR_MCO2PRE_3 */

#define IS_RCC_LSE_DRIVE(__DRIVE__) (((__DRIVE__) == RCC_LSEDRIVE_LOW)        || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */


/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition
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

  uint32_t HSIDiv;               /*!< The division factor of the HSI48.
                                      This parameter can be a value of @ref RCC_HSI_Div                           */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

#if defined(RCC_CR_HSIUSB48ON)
  uint32_t HSI48State;             /*!< The new state of the HSI48 (only applicable to STM32C071xx devices).
                                        This parameter can be a value of @ref RCC_HSI48_Config */

#endif /* RCC_CR_HSIUSB48ON */
} RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a combination of @ref RCC_System_Clock_Type      */

  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t SYSCLKDivider;         /*!< The system clock  divider. This parameter can be
                                       a value of @ref RCC_SYS_Clock_Divider */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_HCLK_Clock_Divider       */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_Clock_Divider */


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
#define RCC_OSCILLATORTYPE_NONE        0x00000000U   /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSE         0x00000001U   /*!< HSE to configure */
#define RCC_OSCILLATORTYPE_HSI         0x00000002U   /*!< HSI to configure */
#define RCC_OSCILLATORTYPE_LSE         0x00000004U   /*!< LSE to configure */
#define RCC_OSCILLATORTYPE_LSI         0x00000008U   /*!< LSI to configure */
#if defined(RCC_CR_HSIUSB48ON)
#define RCC_OSCILLATORTYPE_HSI48       0x00000010U   /*!< HSI48 to configure */
#endif /* RCC_CR_HSIUSB48ON */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF               0x00000000U                                /*!< HSE clock deactivation */
#define RCC_HSE_ON                RCC_CR_HSEON                               /*!< HSE clock activation */
#define RCC_HSE_BYPASS            ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON)) /*!< External clock source for HSE clock */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF           0x00000000U                                    /*!< LSE clock deactivation */
#define RCC_LSE_ON            RCC_CSR1_LSEON                                 /*!< LSE clock activation */
#define RCC_LSE_BYPASS        ((uint32_t)(RCC_CSR1_LSEBYP | RCC_CSR1_LSEON)) /*!< External clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0x00000000U            /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_CR_HSION           /*!< HSI clock activation */
#define RCC_HSICALIBRATION_DEFAULT     64U                    /*!< Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_HSI_Div HSI Div
  * @{
  */
#define RCC_HSI_DIV1              0x00000000U                                        /*!< HSI clock is not divided */
#define RCC_HSI_DIV2              RCC_CR_HSIDIV_0                                    /*!< HSI clock is divided by 2 */
#define RCC_HSI_DIV4              RCC_CR_HSIDIV_1                                    /*!< HSI clock is divided by 4 */
#define RCC_HSI_DIV8              (RCC_CR_HSIDIV_1|RCC_CR_HSIDIV_0)                  /*!< HSI clock is divided by 8 */
#define RCC_HSI_DIV16             RCC_CR_HSIDIV_2                                    /*!< HSI clock is divided by 16 */
#define RCC_HSI_DIV32             (RCC_CR_HSIDIV_2|RCC_CR_HSIDIV_0)                  /*!< HSI clock is divided by 32 */
#define RCC_HSI_DIV64             (RCC_CR_HSIDIV_2|RCC_CR_HSIDIV_1)                  /*!< HSI clock is divided by 64 */
#define RCC_HSI_DIV128            (RCC_CR_HSIDIV_2|RCC_CR_HSIDIV_1|RCC_CR_HSIDIV_0)  /*!< HSI clock is divided by 128 */
/**
  * @}
  */


/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U            /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR2_LSION          /*!< LSI clock activation */
/**
  * @}
  */

#if defined(RCC_CR_HSIUSB48ON)
/** @defgroup RCC_HSI48_Config HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                  0x00000000U          /*!< HSI48 clock deactivation */
#define RCC_HSI48_ON                   RCC_CR_HSIUSB48ON    /*!< HSI48 clock activation */
/**
  * @}
  */
#endif /* RCC_CR_HSIUSB48ON */

/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           0x00000001U  /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK             0x00000002U  /*!< HCLK to configure */
#define RCC_CLOCKTYPE_PCLK1            0x00000004U  /*!< PCLK1 to configure */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI           0x00000000U                       /*!< HSI selection as system clock */
#define RCC_SYSCLKSOURCE_HSE           RCC_CFGR_SW_0                     /*!< HSE selection as system clock */
#if defined(RCC_HSI48_SUPPORT)
#define RCC_SYSCLKSOURCE_HSIUSB48      RCC_CFGR_SW_1                     /*!< HSIUSB48 selection used as system clock */
#endif /* RCC_HSI48_SUPPORT */
#define RCC_SYSCLKSOURCE_LSI           (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)   /*!< LSI selection as system clock */
#define RCC_SYSCLKSOURCE_LSE           RCC_CFGR_SW_2                     /*!< LSE selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSI           0x00000000U                       /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE           RCC_CFGR_SWS_0                    /*!< HSE used as system clock */
#if defined(RCC_HSI48_SUPPORT)
#define RCC_SYSCLKSOURCE_STATUS_HSIUSB48      RCC_CFGR_SWS_1                    /*!< HSIUSB48 used as system clock */
#endif /* RCC_HSI48_SUPPORT */
#define RCC_SYSCLKSOURCE_STATUS_LSI           (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0) /*!< LSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_LSE           RCC_CFGR_SWS_2                    /*!< LSE used as system clock */
/**
  * @}
  */

/** @defgroup RCC_SYS_Clock_Divider  RCC SYS Clock Divider
  * @{
  */
#if defined(RCC_CR_SYSDIV)
#define RCC_SYSCLK_DIV1          0x00000000U                                  /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2          RCC_CR_SYSDIV_0                              /*!< SYSCLK is divided by 2 */
#define RCC_SYSCLK_DIV3          RCC_CR_SYSDIV_1                              /*!< SYSCLK is divided by 3 */
#define RCC_SYSCLK_DIV4          (RCC_CR_SYSDIV_1 | RCC_CR_SYSDIV_0)          /*!< SYSCLK is divided by 4 */
#define RCC_SYSCLK_DIV5          RCC_CR_SYSDIV_2                              /*!< SYSCLK is divided by 5 */
#define RCC_SYSCLK_DIV6          (RCC_CR_SYSDIV_2 | RCC_CR_SYSDIV_0)          /*!< SYSCLK is divided by 6 */
#define RCC_SYSCLK_DIV7          (RCC_CR_SYSDIV_2 | RCC_CR_SYSDIV_1)          /*!< SYSCLK is divided by 7 */
#define RCC_SYSCLK_DIV8          (RCC_CR_SYSDIV_2 | RCC_CR_SYSDIV_1 | RCC_CR_SYSDIV_0)   /*!< SYSCLK is divided by 8 */
#else
#define RCC_SYSCLK_DIV1          0x00000000U                                  /*!< SYSCLK not divided */
#endif /* RCC_CR_SYSDIV */
/**
  * @}
  */

/** @defgroup RCC_HCLK_Clock_Divider  RCC HCLK Clock Divider
  * @{
  */
#define RCC_HCLK_DIV1        0x00000000U                                                    /*!< HCLK not divided */
#define RCC_HCLK_DIV2        RCC_CFGR_HPRE_3                                                /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4        (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0)                            /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8        (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1)                            /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16       (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)          /*!< HCLK divided by 16 */
#define RCC_HCLK_DIV64       (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2)                            /*!< HCLK divided by 64 */
#define RCC_HCLK_DIV128      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0)          /*!< HCLK divided by 128 */
#define RCC_HCLK_DIV256      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1)          /*!< HCLK divided by 256 */
#define RCC_HCLK_DIV512      (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)  /*!< HCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Divider  RCC APB1 Clock Divider
  * @{
  */
#define RCC_APB1_DIV1           0x00000000U                                             /*!< APB not divided */
#define RCC_APB1_DIV2           RCC_CFGR_PPRE_2                                         /*!< APB divided by 2  */
#define RCC_APB1_DIV4           (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_0)                     /*!< APB divided by 4  */
#define RCC_APB1_DIV8           (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1)                     /*!< APB divided by 4  */
#define RCC_APB1_DIV16          (RCC_CFGR_PPRE_2 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_0)   /*!< APB divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NONE          0x00000000U         /*!< No clock configured for RTC */
#define RCC_RTCCLKSOURCE_LSE           RCC_CSR1_RTCSEL_0   /*!< LSE oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSI           RCC_CSR1_RTCSEL_1   /*!< LSI oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV32     RCC_CSR1_RTCSEL     /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */

/* @cond */
/* 32     28      20       16      0
   --------------------------------
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
#define RCC_MCO2_INDEX         (0x1UL << RCC_MCO_INDEX_POS)             /*!< MCO2 index */
/* @endcond */

#define RCC_MCO1_PA8           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_8)
#define RCC_MCO1_PA9           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_9)
#define RCC_MCO1_PF2           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOF) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_2)
#define RCC_MCO1               RCC_MCO1_PA8         /*!< Alias for compatibility */

#define RCC_MCO2_PA8           (RCC_MCO2_INDEX |\
                                (GPIO_AF15_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_8)
#define RCC_MCO2_PA10          (RCC_MCO2_INDEX |\
                                (GPIO_AF3_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_10)
#define RCC_MCO2_PA14          (RCC_MCO2_INDEX |\
                                (GPIO_AF11_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_14)
#if !defined(STM32C011xx)
#define RCC_MCO2_PA15          (RCC_MCO2_INDEX |\
                                (GPIO_AF3_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_15)
#define RCC_MCO2_PB2           (RCC_MCO2_INDEX |\
                                (GPIO_AF3_MCO2 << RCC_MCO_GPIOAF_POS) | \
                                (GPIO_GET_INDEX(GPIOB) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_2)
#endif /* STM32C011xx */
#define RCC_MCO2               RCC_MCO2_PA10         /*!< Alias for compatibility */

#define RCC_MCO                RCC_MCO1             /*!< MCO1 to be compliant with other families with 1 MCO*/
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK         0x00000000U                            /*!< MCO1 output disabled, no clock on MCO1 */
#define RCC_MCO1SOURCE_SYSCLK          RCC_CFGR_MCOSEL_0                      /*!< SYSCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI             (RCC_CFGR_MCOSEL_0| RCC_CFGR_MCOSEL_1) /*!< HSI selection as MCO1 source */
#define RCC_MCO1SOURCE_HSE             RCC_CFGR_MCOSEL_2                      /*!< HSE selection as MCO1 source */
#define RCC_MCO1SOURCE_LSI             (RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2)  /*!< LSI selection as MCO1 source */
#define RCC_MCO1SOURCE_LSE             (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2) /*!< LSE selection as MCO1 source */
#if defined(RCC_HSI48_SUPPORT)
#define RCC_MCO1SOURCE_HSI48           RCC_CFGR_MCOSEL_3                      /*!< HSI48 selection as MCO1 source */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Source MCO2 Clock Source
  * @{
  */
#define RCC_MCO2SOURCE_NOCLOCK         0x00000000U                              /*!< MCO2 output disabled, no clock on MCO2 */
#define RCC_MCO2SOURCE_SYSCLK          RCC_CFGR_MCO2SEL_0                       /*!< SYSCLK selection as MCO2 source */
#define RCC_MCO2SOURCE_HSI             (RCC_CFGR_MCO2SEL_0| RCC_CFGR_MCO2SEL_1) /*!< HSI selection as MCO2 source */
#define RCC_MCO2SOURCE_HSE             RCC_CFGR_MCO2SEL_2                       /*!< HSE selection as MCO2 source */
#define RCC_MCO2SOURCE_LSI             (RCC_CFGR_MCO2SEL_1|RCC_CFGR_MCO2SEL_2)  /*!< LSI selection as MCO2 source */
#define RCC_MCO2SOURCE_LSE             (RCC_CFGR_MCO2SEL_0|RCC_CFGR_MCO2SEL_1|RCC_CFGR_MCO2SEL_2) /*!< LSE selection as MCO2 source */
#if defined(RCC_HSI48_SUPPORT)
#define RCC_MCO2SOURCE_HSI48           RCC_CFGR_MCO2SEL_3                       /*!< HSI48 selection as MCO2 source */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */
/** @defgroup RCC_MCO1_Clock_Prescaler MCO1 Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1              0x00000000U                                                 /*!< MCO not divided */
#define RCC_MCODIV_2              RCC_CFGR_MCOPRE_0                                           /*!< MCO divided by 2 */
#define RCC_MCODIV_4              RCC_CFGR_MCOPRE_1                                           /*!< MCO divided by 4 */
#define RCC_MCODIV_8              (RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0)                     /*!< MCO divided by 8 */
#define RCC_MCODIV_16             RCC_CFGR_MCOPRE_2                                           /*!< MCO divided by 16 */
#define RCC_MCODIV_32             (RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_0)                     /*!< MCO divided by 32 */
#define RCC_MCODIV_64             (RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_1)                     /*!< MCO divided by 64 */
#define RCC_MCODIV_128            (RCC_CFGR_MCOPRE_2 | RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0) /*!< MCO divided by 128 */
#if defined(RCC_CFGR_MCOPRE_3)
#define RCC_MCODIV_256            RCC_CFGR_MCOPRE_3                                           /*!< MCO divided by 256 */
#define RCC_MCODIV_512            (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_0)                     /*!< MCO divided by 512 */
#define RCC_MCODIV_1024           (RCC_CFGR_MCOPRE_3 | RCC_CFGR_MCOPRE_1)                     /*!< MCO divided by 1024*/
#endif /* RCC_CFGR_MCOPRE_3 */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Prescaler MCO2 Clock Prescaler
  * @{
  */
#define RCC_MCO2DIV_1          0x00000000U                                                    /*!< MCO not divided */
#define RCC_MCO2DIV_2          RCC_CFGR_MCO2PRE_0                                             /*!< MCO divided by 2 */
#define RCC_MCO2DIV_4          RCC_CFGR_MCO2PRE_1                                             /*!< MCO divided by 4 */
#define RCC_MCO2DIV_8          (RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO divided by 8 */
#define RCC_MCO2DIV_16         RCC_CFGR_MCO2PRE_2                                             /*!< MCO divided by 16 */
#define RCC_MCO2DIV_32         (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO divided by 32 */
#define RCC_MCO2DIV_64         (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1)                      /*!< MCO divided by 64 */
#define RCC_MCO2DIV_128        (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0) /*!< MCO divided by 128 */
#if defined(RCC_CFGR_MCO2PRE_3)
#define RCC_MCO2DIV_256        RCC_CFGR_MCO2PRE_3                                             /*!< MCO divided by 256 */
#define RCC_MCO2DIV_512        (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_0)                      /*!< MCO divided by 512 */
#define RCC_MCO2DIV_1024       (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_1)                      /*!< MCO divided by 1024*/
#endif /* RCC_CFGR_MCO2PRE_3 */
/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                  RCC_CIFR_LSIRDYF            /*!< LSI Ready Interrupt flag */
#define RCC_IT_LSERDY                  RCC_CIFR_LSERDYF            /*!< LSE Ready Interrupt flag */
#define RCC_IT_HSIRDY                  RCC_CIFR_HSIRDYF            /*!< HSI Ready Interrupt flag */
#define RCC_IT_HSERDY                  RCC_CIFR_HSERDYF            /*!< HSE Ready Interrupt flag */
#define RCC_IT_CSS                     RCC_CIFR_CSSF               /*!< HSE Clock Security System Interrupt flag */
#define RCC_IT_LSECSS                  RCC_CIFR_LSECSSF            /*!< LSE Clock Security System Interrupt flag */
#if defined(RCC_HSI48_SUPPORT)
#define RCC_IT_HSI48RDY                RCC_CIFR_HSIUSB48RDYF       /*!< HSI48 Ready Interrupt flag */
#endif /* RCC_HSI48_SUPPORT */
/**
  * @}
  */

/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: CSR1 register
  *                 - 011: CSR2 register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                ((RCC_CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos) /*!< HSI Ready flag */
#define RCC_FLAG_HSERDY                ((RCC_CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos) /*!< HSE Ready flag */
#if defined(RCC_HSI48_SUPPORT)
/* Flags in the CR register */
#define RCC_FLAG_HSI48RDY              ((CR_REG_INDEX << 5U) | RCC_CR_HSI48RDY_Pos) /*!< HSI48 Ready flag */
#endif /* RCC_HSI48_SUPPORT */

/* Flags in the CSR1 register */
#define RCC_FLAG_LSERDY                ((RCC_CSR1_REG_INDEX << 5U) | RCC_CSR1_LSERDY_Pos)  /*!< LSE Ready flag */
#define RCC_FLAG_LSECSSD               ((RCC_CSR1_REG_INDEX << 5U) | RCC_CSR1_LSECSSD_Pos) /*!< LSE Clock Security System Interrupt flag */

/* Flags in the CSR2 register */
#define RCC_FLAG_LSIRDY                ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_LSIRDY_Pos)    /*!< LSI Ready flag */
#define RCC_FLAG_OBLRST                ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_OBLRSTF_Pos)   /*!< Option Byte Loader reset flag */
#define RCC_FLAG_PINRST                ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_PINRSTF_Pos)   /*!< PIN reset flag */
#define RCC_FLAG_PWRRST                ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_PWRRSTF_Pos)   /*!< BOR or POR/PDR reset flag */
#define RCC_FLAG_SFTRST                ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_SFTRSTF_Pos)   /*!< Software Reset flag */
#define RCC_FLAG_IWDGRST               ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_IWDGRSTF_Pos)  /*!< Independent Watchdog reset flag */
#define RCC_FLAG_WWDGRST               ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_WWDGRSTF_Pos)  /*!< Window watchdog reset flag */
#define RCC_FLAG_LPWRRST               ((RCC_CSR2_REG_INDEX << 5U) | RCC_CSR2_LPWRRSTF_Pos)  /*!< Low-Power reset flag */

/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Configuration
  * @{
  */
#define RCC_LSEDRIVE_LOW                 0x00000000U            /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           RCC_CSR1_LSEDRV_0      /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          RCC_CSR1_LSEDRV_1      /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                RCC_CSR1_LSEDRV        /*!< LSE high drive capability */
/**
  * @}
  */

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
                                                  } while(0U)

#define __HAL_RCC_FLASH_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_CRC_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)


#define __HAL_RCC_DMA1_CLK_DISABLE()           CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN)
#define __HAL_RCC_FLASH_CLK_DISABLE()          CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN)
#define __HAL_RCC_CRC_CLK_DISABLE()            CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)

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
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)
#endif /* GPIOD */
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
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_CLK_DISABLE()          CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN)

/**
  * @}
  */

/** @defgroup RCC_APB1_GRP1_Clock_Enable_Disable APB1_GRP1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(TIM2)
#define __HAL_RCC_TIM2_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* TIM2 */

#define __HAL_RCC_TIM3_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_RTCAPB_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_WWDG_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_USBEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_USBEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)
#endif /* USB_DRD_FS */

#if defined(SPI2)
#define __HAL_RCC_SPI2_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* SPI2 */

#if defined(CRS)
#define __HAL_RCC_CRS_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0)
#endif /* CRS */

#define __HAL_RCC_USART2_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_I2C1_CLK_ENABLE()            do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_ENABLE()             do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0)
#endif /* I2C2 */

#define __HAL_RCC_DBGMCU_CLK_ENABLE()          do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_PWR_CLK_ENABLE()             do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR1, RCC_APBENR1_PWREN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)
#if defined(TIM2)
#define __HAL_RCC_TIM2_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)
#define __HAL_RCC_RTCAPB_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN)
#define __HAL_RCC_WWDG_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_USBEN)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN)
#endif /* CRS */
#define __HAL_RCC_USART2_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN)
#define __HAL_RCC_I2C1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)
#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN)
#define __HAL_RCC_PWR_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP2_Clock_Enable_Disable APB1_GRP2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1_GRP2 peripheral clock.
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

#define __HAL_RCC_TIM14_CLK_ENABLE()            do { \
                                                     __IO uint32_t tmpreg; \
                                                     SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN); \
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN); \
                                                     UNUSED(tmpreg); \
                                                   } while(0U)

#define __HAL_RCC_TIM16_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_TIM17_CLK_ENABLE()           do { \
                                                    __IO uint32_t tmpreg; \
                                                    SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN); \
                                                    /* Delay after an RCC peripheral clock enabling */ \
                                                    tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN); \
                                                    UNUSED(tmpreg); \
                                                  } while(0U)

#define __HAL_RCC_ADC_CLK_ENABLE()           do { \
                                                  __IO uint32_t tmpreg; \
                                                  SET_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN); \
                                                  /* Delay after an RCC peripheral clock enabling */ \
                                                  tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN); \
                                                  UNUSED(tmpreg); \
                                                } while(0U)

#define __HAL_RCC_SYSCFG_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN)
#define __HAL_RCC_TIM1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)
#define __HAL_RCC_SPI1_CLK_DISABLE()           CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)
#define __HAL_RCC_USART1_CLK_DISABLE()         CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN)
#define __HAL_RCC_TIM14_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN)
#define __HAL_RCC_TIM16_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)
#define __HAL_RCC_TIM17_CLK_DISABLE()          CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN)
#define __HAL_RCC_ADC_CLK_DISABLE()            CLEAR_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)
/**
  * @}
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enabled_Disabled_Status AHB Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_DMA1_IS_CLK_ENABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN)  != 0U)
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()       (READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN) != 0U)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()         (READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)   != 0U)

#define __HAL_RCC_DMA1_IS_CLK_DISABLED()       (READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN)  == 0U)
#define __HAL_RCC_FLASH_IS_CLK_DISABLED()      (READ_BIT(RCC->AHBENR, RCC_AHBENR_FLASHEN) == 0U)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()        (READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN)   == 0U)
/**
  * @}
  */

/** @defgroup RCC_IOPORT_Clock_Enabled_Disabled_Status IOPORT Clock Enabled or Disabled Status
  * @brief  Check whether the IO Port clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN) != 0U)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN) != 0U)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()       (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN) != 0U)

#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN) == 0U)
#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN) == 0U)
#define __HAL_RCC_GPIOC_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN) == 0U)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN) == 0U)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()      (READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN) == 0U)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP1_Clock_Enabled_Disabled_Status APB1_GRP1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1_GRP1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(TIM2)
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN) != 0U)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)   != 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN) != 0U)
#define __HAL_RCC_WWDG_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)   != 0U)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_USBEN) != 0U)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN) != 0U)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN) != 0U)
#endif /* CRS */
#define __HAL_RCC_USART2_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN) != 0U)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)   != 0U)
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN) != 0U)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN)    != 0U)
#define __HAL_RCC_PWR_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)    != 0U)

#if defined(TIM2)
#define __HAL_RCC_TIM2_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM2EN)   == 0U)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_TIM3EN)   == 0U)
#define __HAL_RCC_RTCAPB_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR1, RCC_APBENR1_RTCAPBEN) == 0U)
#define __HAL_RCC_WWDG_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_WWDGEN)   == 0U)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_USBEN) == 0U)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_SPI2EN) == 0U)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_CRSEN) == 0U)
#endif /* CRS */
#define __HAL_RCC_USART2_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN) == 0U)
#define __HAL_RCC_I2C1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C1EN)   == 0U)
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR1, RCC_APBENR1_I2C2EN) == 0U)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR1, RCC_APBENR1_DBGEN)    == 0U)
#define __HAL_RCC_PWR_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR1, RCC_APBENR1_PWREN)    == 0U)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP2_Clock_Enabled_Disabled_Status APB1_GRP2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1_GRP2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN) != 0U)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)   != 0U)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)   != 0U)
#define __HAL_RCC_USART1_IS_CLK_ENABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN) != 0U)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN)  != 0U)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)  != 0U)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN)  != 0U)
#define __HAL_RCC_ADC_IS_CLK_ENABLED()         (READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)    != 0U)

#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN) == 0U)
#define __HAL_RCC_TIM1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN)   == 0U)
#define __HAL_RCC_SPI1_IS_CLK_DISABLED()       (READ_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN)   == 0U)
#define __HAL_RCC_USART1_IS_CLK_DISABLED()     (READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN) == 0U)
#define __HAL_RCC_TIM14_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM14EN)  == 0U)
#define __HAL_RCC_TIM16_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM16EN)  == 0U)
#define __HAL_RCC_TIM17_IS_CLK_DISABLED()      (READ_BIT(RCC->APBENR2, RCC_APBENR2_TIM17EN)  == 0U)
#define __HAL_RCC_ADC_IS_CLK_DISABLED()        (READ_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN)    == 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB_Force_Release_Reset AHB Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB_FORCE_RESET()            WRITE_REG(RCC->AHBRSTR, 0xFFFFFFFFU)
#define __HAL_RCC_DMA1_FORCE_RESET()           SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMA1RST)
#define __HAL_RCC_FLASH_FORCE_RESET()          SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_FLASHRST)
#define __HAL_RCC_CRC_FORCE_RESET()            SET_BIT(RCC->AHBRSTR, RCC_AHBRSTR_CRCRST)

#define __HAL_RCC_AHB_RELEASE_RESET()          WRITE_REG(RCC->AHBRSTR, 0x00000000U)
#define __HAL_RCC_DMA1_RELEASE_RESET()         CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_DMA1RST)
#define __HAL_RCC_FLASH_RELEASE_RESET()        CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_FLASHRST)
#define __HAL_RCC_CRC_RELEASE_RESET()          CLEAR_BIT(RCC->AHBRSTR, RCC_AHBRSTR_CRCRST)
/**
  * @}
  */

/** @defgroup RCC_IOPORT_Force_Release_Reset IOPORT Force Release Reset
  * @brief  Force or release IO Port reset.
  * @{
  */
#define __HAL_RCC_IOP_FORCE_RESET()            WRITE_REG(RCC->IOPRSTR, 0xFFFFFFFFU)
#define __HAL_RCC_GPIOA_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOARST)
#define __HAL_RCC_GPIOB_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOBRST)
#define __HAL_RCC_GPIOC_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOCRST)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIODRST)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_FORCE_RESET()          SET_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOFRST)

#define __HAL_RCC_IOP_RELEASE_RESET()          WRITE_REG(RCC->IOPRSTR, 0x00000000U)
#define __HAL_RCC_GPIOA_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOARST)
#define __HAL_RCC_GPIOB_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOBRST)
#define __HAL_RCC_GPIOC_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOCRST)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIODRST)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_RELEASE_RESET()        CLEAR_BIT(RCC->IOPRSTR, RCC_IOPRSTR_GPIOFRST)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP1_Force_Release_Reset APB1_GRP1 Peripheral Force Release Reset
  * @brief  Force or release APB1_GRP1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_GRP1_FORCE_RESET()      WRITE_REG(RCC->APBRSTR1, 0xFFFFFFFFU)
#if defined(TIM2)
#define __HAL_RCC_TIM2_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM2RST)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM3RST)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_FORCE_RESET()            SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USBRST)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI2RST)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_FORCE_RESET()            SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_CRSRST)
#endif /* CRS */
#define __HAL_RCC_USART2_FORCE_RESET()         SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART2RST)
#define __HAL_RCC_I2C1_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C1RST)
#if defined(I2C2)
#define __HAL_RCC_I2C2_FORCE_RESET()           SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C2RST)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_FORCE_RESET()         SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_DBGRST)
#define __HAL_RCC_PWR_FORCE_RESET()            SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_PWRRST)

#define __HAL_RCC_APB1_GRP1_RELEASE_RESET()    WRITE_REG(RCC->APBRSTR1, 0x00000000U)
#if defined(TIM2)
#define __HAL_RCC_TIM2_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM2RST)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_TIM3RST)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USBRST)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_SPI2RST)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_CRSRST)
#endif /* CRS */
#define __HAL_RCC_USART2_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_USART2RST)
#define __HAL_RCC_I2C1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C1RST)
#if defined(I2C2)
#define __HAL_RCC_I2C2_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C2RST)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_DBGRST)
#define __HAL_RCC_PWR_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR1, RCC_APBRSTR1_PWRRST)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP2_Force_Release_Reset APB1_GRP2 Peripheral Force Release Reset
  * @brief  Force or release APB1_GRP2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_GRP2_FORCE_RESET()      WRITE_REG(RCC->APBRSTR2, 0xFFFFFFFFU)
#define __HAL_RCC_SYSCFG_FORCE_RESET()         SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SYSCFGRST)
#define __HAL_RCC_TIM1_FORCE_RESET()           SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM1RST)
#define __HAL_RCC_SPI1_FORCE_RESET()           SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SPI1RST)
#define __HAL_RCC_USART1_FORCE_RESET()         SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_USART1RST)
#define __HAL_RCC_TIM14_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM14RST)
#define __HAL_RCC_TIM16_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM16RST)
#define __HAL_RCC_TIM17_FORCE_RESET()          SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM17RST)
#define __HAL_RCC_ADC_FORCE_RESET()            SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST)

#define __HAL_RCC_APB1_GRP2_RELEASE_RESET()    WRITE_REG(RCC->APBRSTR2, 0x00000000U)
#define __HAL_RCC_SYSCFG_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SYSCFGRST)
#define __HAL_RCC_TIM1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM1RST)
#define __HAL_RCC_SPI1_RELEASE_RESET()         CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_SPI1RST)
#define __HAL_RCC_USART1_RELEASE_RESET()       CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_USART1RST)
#define __HAL_RCC_TIM14_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM14RST)
#define __HAL_RCC_TIM16_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM16RST)
#define __HAL_RCC_TIM17_RELEASE_RESET()        CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_TIM17RST)
#define __HAL_RCC_ADC_RELEASE_RESET()          CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST)
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Sleep_Enable_Disable AHB Peripherals Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB peripherals clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA1SMEN)
#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_FLASHSMEN)
#define __HAL_RCC_SRAM_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_SRAMSMEN)
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHBSMENR, RCC_AHBSMENR_CRCSMEN)

#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA1SMEN)
#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_FLASHSMEN)
#define __HAL_RCC_SRAM_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_SRAMSMEN)
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHBSMENR, RCC_AHBSMENR_CRCSMEN)
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
#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()     SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOASMEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()     SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOBSMEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()     SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOCSMEN)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()     SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIODSMEN)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()     SET_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOFSMEN)

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOASMEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOBSMEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOCSMEN)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIODSMEN)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOFSMEN)
/**
  *   @}
  */

/** @defgroup RCC_APB1_GRP1_Clock_Sleep_Enable_Disable APB1_GRP1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1_GRP1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#if defined(TIM2)
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM2SMEN)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM3SMEN)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_RTCAPBSMEN)
#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_WWDGSMEN)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USBSMEN)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI2SMEN)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_CRSSMEN)
#endif /* CRS */
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN)
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN)
#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_DBGSMEN)
#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APBSMENR1, RCC_APBSMENR1_PWRSMEN)

#if defined(TIM2)
#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM2SMEN)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM3SMEN)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_RTCAPBSMEN)
#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_WWDGSMEN)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USBSMEN)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI2SMEN)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_CRSSMEN)
#endif /* CRS */
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN)
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN)
#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_DBGSMEN)
#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APBSMENR1, RCC_APBSMENR1_PWRSMEN)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP2_Clock_Sleep_Enable_Disable APB1_GRP2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1_GRP2 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SYSCFGSMEN)
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM1SMEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SPI1SMEN)
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_USART1SMEN)
#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM14SMEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM16SMEN)
#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM17SMEN)
#define __HAL_RCC_ADC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_ADCSMEN)

#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SYSCFGSMEN)
#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM1SMEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SPI1SMEN)
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_USART1SMEN)
#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM14SMEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM16SMEN)
#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM17SMEN)
#define __HAL_RCC_ADC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_ADCSMEN)
/**
  * @}
  */


/** @defgroup RCC_AHB_Clock_Sleep_Enabled_Disabled_Status AHB Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the AHB peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_DMA1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA1SMEN) != RESET)
#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_FLASHSMEN)!= RESET)
#define __HAL_RCC_SRAM_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_SRAMSMEN) != RESET)
#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_CRCSMEN)  != RESET)

#define __HAL_RCC_DMA1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_DMA1SMEN)  == RESET)
#define __HAL_RCC_FLASH_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_FLASHSMEN) == RESET)
#define __HAL_RCC_SRAM_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_SRAMSMEN)  == RESET)
#define __HAL_RCC_CRC_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->AHBSMENR, RCC_AHBSMENR_CRCSMEN)   == RESET)
/**
  * @}
  */

/** @defgroup RCC_IOPORT_Clock_Sleep_Enabled_Disabled_Status IOPORT Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the IOPORT clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOASMEN)!= RESET)
#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOBSMEN)!= RESET)
#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOCSMEN)!= RESET)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIODSMEN)!= RESET)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOFSMEN)!= RESET)


#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOASMEN) == RESET)
#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOBSMEN) == RESET)
#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOCSMEN) == RESET)
#if defined (GPIOD)
#define __HAL_RCC_GPIOD_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIODSMEN) == RESET)
#endif /* GPIOD */
#define __HAL_RCC_GPIOF_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->IOPSMENR, RCC_IOPSMENR_GPIOFSMEN) == RESET)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP1_Clock_Sleep_Enabled_Disabled_Status APB1_GRP1 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB1_GRP1 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#if defined(TIM2)
#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM2SMEN)   != RESET)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM3SMEN)   != RESET)
#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_RTCAPBSMEN) != RESET)
#define __HAL_RCC_WWDG_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_WWDGSMEN)   != RESET)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USBSMEN)   != RESET)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI2SMEN)   != RESET)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_CRSSMEN)   != RESET)
#endif /* CRS */
#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN) != RESET)
#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN)   != RESET)
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN)   != RESET)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_DBGSMEN)    != RESET)
#define __HAL_RCC_PWR_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_PWRSMEN)    != RESET)

#if defined(TIM2)
#define __HAL_RCC_TIM2_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM2SMEN)   == RESET)
#endif /* TIM2 */
#define __HAL_RCC_TIM3_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_TIM3SMEN)   == RESET)
#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_RTCAPBSMEN) == RESET)
#define __HAL_RCC_WWDG_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_WWDGSMEN)   == RESET)
#if defined (USB_DRD_FS)
#define __HAL_RCC_USB_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USBSMEN)   == RESET)
#endif /* USB_DRD_FS */
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_SPI2SMEN)   == RESET)
#endif /* SPI2 */
#if defined(CRS)
#define __HAL_RCC_CRS_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_CRSSMEN)   == RESET)
#endif /* CRS */
#define __HAL_RCC_USART2_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN) == RESET)
#define __HAL_RCC_I2C1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN)   == RESET)
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN)   == RESET)
#endif /* I2C2 */
#define __HAL_RCC_DBGMCU_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_DBGSMEN)    == RESET)
#define __HAL_RCC_PWR_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APBSMENR1, RCC_APBSMENR1_PWRSMEN)    == RESET)
/**
  * @}
  */

/** @defgroup RCC_APB1_GRP2_Clock_Sleep_Enabled_Disabled_Status APB1_GRP2 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB1_GRP2 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SYSCFGSMEN) != RESET)
#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM1SMEN)   != RESET)
#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SPI1SMEN)   != RESET)
#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_USART1SMEN) != RESET)
#define __HAL_RCC_TIM14_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM14SMEN)  != RESET)
#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM16SMEN)  != RESET)
#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM17SMEN)  != RESET)
#define __HAL_RCC_ADC_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_ADCSMEN)    != RESET)

#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SYSCFGSMEN) == RESET)
#define __HAL_RCC_TIM1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM1SMEN)   == RESET)
#define __HAL_RCC_SPI1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_SPI1SMEN)   == RESET)
#define __HAL_RCC_USART1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_USART1SMEN) == RESET)
#define __HAL_RCC_TIM14_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM14SMEN)  == RESET)
#define __HAL_RCC_TIM16_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM16SMEN)  == RESET)
#define __HAL_RCC_TIM17_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_TIM17SMEN)  == RESET)
#define __HAL_RCC_ADC_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APBSMENR2 , RCC_APBSMENR2_ADCSMEN)    == RESET)
/**
  * @}
  */

/** @defgroup RCC_RTC_Domain_Reset RCC RTC Domain Reset
  * @{
  */

/** @brief  Macros to force or release the RTC domain reset.
  * @note   This function resets the RTC peripheral
  *         and the RTC clock source selection in RCC_CSR1 register.
  * @retval None
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   SET_BIT(RCC->CSR1, RCC_CSR1_RTCRST)

#define __HAL_RCC_BACKUPRESET_RELEASE() CLEAR_BIT(RCC->CSR1, RCC_CSR1_RTCRST)
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Configuration RCC RTC Clock Configuration
  * @{
  */

/** @brief  Macros to enable or disable the RTC clock.
  * @note   These macros must be used after the RTC clock source was selected.
  * @retval None
  */
#define __HAL_RCC_RTC_ENABLE()         SET_BIT(RCC->CSR1, RCC_CSR1_RTCEN)

#define __HAL_RCC_RTC_DISABLE()        CLEAR_BIT(RCC->CSR1, RCC_CSR1_RTCEN)
/**
  * @}
  */

/** @defgroup RCC_Clock_Configuration RCC Clock Configuration
  * @{
  */

/** @brief  Macros to enable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macros to disable the Internal High Speed oscillator (HSI).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_HSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 127.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__) \
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, (uint32_t)(__HSICALIBRATIONVALUE__) << RCC_ICSCR_HSITRIM_Pos)

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI startup time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()     SET_BIT(RCC->CR, RCC_CR_HSIKERON)

#define __HAL_RCC_HSISTOP_DISABLE()    CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON)

/** @brief  Macro to configure the HSISYS clock.
  * @param  __HSIDIV__ specifies the HSI16 division factor.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_HSI_DIV1   HSI clock source is divided by 1
  *            @arg @ref RCC_HSI_DIV2   HSI clock source is divided by 2
  *            @arg @ref RCC_HSI_DIV4   HSI clock source is divided by 4
  *            @arg @ref RCC_HSI_DIV8   HSI clock source is divided by 8
  *            @arg @ref RCC_HSI_DIV16  HSI clock source is divided by 16
  *            @arg @ref RCC_HSI_DIV32  HSI clock source is divided by 32
  *            @arg @ref RCC_HSI_DIV64  HSI clock source is divided by 64
  *            @arg @ref RCC_HSI_DIV128 HSI clock source is divided by 128
  */
#define __HAL_RCC_HSI_CONFIG(__HSIDIV__) \
  MODIFY_REG(RCC->CR, RCC_CR_HSIDIV, (__HSIDIV__))

/** @brief  Macro to get the HSI divider.
  * @retval The HSI divider. The returned value can be one
  *         of the following:
  *            - RCC_CR_HSIDIV_1  HSI oscillator divided by 1
  *            - RCC_CR_HSIDIV_2  HSI oscillator divided by 2
  *            - RCC_CR_HSIDIV_4  HSI oscillator divided by 4 (default after reset)
  *            - RCC_CR_HSIDIV_8  HSI oscillator divided by 8
  *            - RCC_CR_HSIDIV_16  HSI oscillator divided by 16
  *            - RCC_CR_HSIDIV_32  HSI oscillator divided by 32
  *            - RCC_CR_HSIDIV_64  HSI oscillator divided by 64
  *            - RCC_CR_HSIDIV_128  HSI oscillator divided by 128
  */
#define __HAL_RCC_GET_HSI_DIVIDER() ((uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSIDIV)))

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         SET_BIT(RCC->CSR2, RCC_CSR2_LSION)

#define __HAL_RCC_LSI_DISABLE()        CLEAR_BIT(RCC->CSR2, RCC_CSR2_LSION)

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
  * @param  __STATE__  specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS  HSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                      \
  do {                                     \
    if((__STATE__) == RCC_HSE_ON)          \
    {                                      \
      SET_BIT(RCC->CR, RCC_CR_HSEON);      \
    }                                      \
    else if((__STATE__) == RCC_HSE_BYPASS) \
    {                                      \
      SET_BIT(RCC->CR, RCC_CR_HSEBYP);     \
      SET_BIT(RCC->CR, RCC_CR_HSEON);      \
    }                                      \
    else                                   \
    {                                      \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEON);    \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);   \
    }                                      \
  } while(0U)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__  specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON  Turn ON the LSE oscillator.
  *            @arg @ref RCC_LSE_BYPASS  LSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)      \
  do {                                       \
    if((__STATE__) == RCC_LSE_ON)            \
    {                                        \
      SET_BIT(RCC->CSR1, RCC_CSR1_LSEON);    \
    }                                        \
    else if((__STATE__) == RCC_LSE_BYPASS)   \
    {                                        \
      SET_BIT(RCC->CSR1, RCC_CSR1_LSEBYP);   \
      SET_BIT(RCC->CSR1, RCC_CSR1_LSEON);    \
    }                                        \
    else                                     \
    {                                        \
      CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSEON);  \
      CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSEBYP); \
    }                                        \
  } while(0U)
#if defined(RCC_CR_HSIUSB48ON)
/** @brief  Macros to enable or disable the Internal High Speed 48MHz oscillator (HSI48).
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @note   After enabling the HSI48, the application software should wait on HSI48RDY
  *         flag to be set indicating that HSI48 clock is stable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI48_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSIUSB48ON)

#define __HAL_RCC_HSI48_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSIUSB48ON)
#endif /* RCC_CR_HSIUSB48ON */
/**
  * @}
  */

/** @addtogroup RCC_RTC_Clock_Configuration
  * @{
  */

/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the RTC domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power RTC Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         RTC domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  *
  * @param  __RTC_CLKSOURCE__  specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE No clock selected as RTC clock.
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
  MODIFY_REG( RCC->CSR1, RCC_CSR1_RTCSEL, (__RTC_CLKSOURCE__))


/** @brief Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE No clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  */
#define  __HAL_RCC_GET_RTC_SOURCE() ((uint32_t)(READ_BIT(RCC->CSR1, RCC_CSR1_RTCSEL)))

/**
  * @}
  */

/** @addtogroup RCC_Clock_Configuration
  * @{
  */

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__ specifies the system clock source.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_SYSCLKSOURCE_HSI HSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_HSE HSE oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_HSIUSB48 HSIUSB48 oscillator is used as system clock source.(*)
  *              @arg @ref RCC_SYSCLKSOURCE_LSI LSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_LSE LSE oscillator is used as system clock source.
  * @note (*) peripheral not available on all devices
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__SYSCLKSOURCE__))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSI HSI used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSE HSE used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSIUSB48 HSIUSB48 used as system clock.(*)
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_LSI LSI used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_LSE LSE used as system clock source.
  * @note (*) peripheral not available on all devices
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE()         (RCC->CFGR & RCC_CFGR_SWS)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @param  __LSEDRIVE__ specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
  MODIFY_REG(RCC->CSR1, RCC_CSR1_LSEDRV, (uint32_t)(__LSEDRIVE__))

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE HSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI48  HSI48 clock selected as MCO source for devices with HSI48 (*)
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  *            @arg @ref RCC_MCODIV_32  MCO clock source is divided by 32
  *            @arg @ref RCC_MCODIV_64  MCO clock source is divided by 64
  *            @arg @ref RCC_MCODIV_128  MCO clock source is divided by 128
  *            @arg @ref RCC_MCODIV_256  MCO clock source is divided by 256 (*)
  *            @arg @ref RCC_MCODIV_512  MCO clock source is divided by 512 (*)
  *            @arg @ref RCC_MCODIV_1024  MCO clock source is divided by 1024 (*)
  * @note (*) not available on all devices
  * @retval None
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO2SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO2SOURCE_SYSCLK System  clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_HSI HSI clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_HSE HSE clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_LSI LSI clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_LSE LSE clock selected as MCO source
  *            @arg @ref RCC_MCO2SOURCE_HSI48  HSI48 clock selected as MCO2 source for devices with HSI48 (*)
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
  *            @arg @ref RCC_MCO2DIV_256  MCO clock source is divided by 256 (*)
  *            @arg @ref RCC_MCO2DIV_512  MCO clock source is divided by 512 (*)
  *            @arg @ref RCC_MCO2DIV_1024  MCO clock source is divided by 1024 (*)
  * @note (*) not available on all devices
  * @retval None
  */
#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))
/**
  * @}
  */
/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt for devices with HSI48 (*)
  * @note (*) peripheral not available on all devices
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt.
  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt for devices with HSI48 (*)
  * @note (*) peripheral not available on all devices
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear RCC interrupt pending bits.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_CSS     HSE Clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt for devices with HSI48 (*)
  * @retval None
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CICR = (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__ specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
  *            @arg @ref RCC_IT_CSS     HSE Clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt for devices with HSI48 (*)
  * @note (*) peripheral not available on all devices
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_PWRRST,
  *        RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST and RCC_FLAG_LPWRRST.
  * @retval None
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR2 |= RCC_CSR2_RMVF)

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HSIRDY HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSERDY LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD Clock security system failure on LSE oscillator detection
  *            @arg @ref RCC_FLAG_LSIRDY LSI oscillator clock ready
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt for devices with HSI48 (*)
  *            @arg @ref RCC_FLAG_PWRRST BOR or POR/PDR reset
  *            @arg @ref RCC_FLAG_OBLRST OBLRST reset
  *            @arg @ref RCC_FLAG_PINRST Pin reset
  *            @arg @ref RCC_FLAG_SFTRST Software reset
  *            @arg @ref RCC_FLAG_IWDGRST Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST Window Watchdog reset
  *            @arg @ref RCC_FLAG_LPWRRST Low Power reset
  * @note (*) peripheral not available on all devices
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5U) == RCC_CR_REG_INDEX) ? RCC->CR :                  \
                                         ((((__FLAG__) >> 5U) == RCC_CSR1_REG_INDEX) ? RCC->CSR1 :              \
                                          ((((__FLAG__) >> 5U) == RCC_CSR2_REG_INDEX) ? RCC->CSR2 : RCC->CIFR))) & \
                                        (1U << ((__FLAG__) & RCC_FLAG_MASK))) != RESET) \
                                      ? 1U : 0U)

/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "stm32c0xx_hal_rcc_ex.h"

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

/* Peripheral Control functions  ************************************************/
void      HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void      HAL_RCC_EnableCSS(void);
void      HAL_RCC_EnableLSECSS(void);
void      HAL_RCC_DisableLSECSS(void);
uint32_t  HAL_RCC_GetSysClockFreq(void);
uint32_t  HAL_RCC_GetHCLKFreq(void);
uint32_t  HAL_RCC_GetPCLK1Freq(void);
void      HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void      HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct,
                                 uint32_t *pFLatency);
/* LSE & HSE CSS NMI IRQ handler */
void      HAL_RCC_NMI_IRQHandler(void); /* User Callbacks in non blocking mode (IT mode) */
void      HAL_RCC_CSSCallback(void);
void      HAL_RCC_LSECSSCallback(void);

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

#endif /* STM32C0xx_HAL_RCC_H */
