/**
  ******************************************************************************
  * @file    stm32wb0x_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
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
#ifndef STM32WB0x_HAL_RCC_H
#define STM32WB0x_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_def.h"
#include "stm32wb0x_ll_rcc.h"
#include "stm32wb0x_ll_bus.h"
#include "stm32wb0x_ll_pwr.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */
/** @defgroup RCC_IS_RCC_Definitions RCC Private macros to check input parameters
  * @{
  */

#if defined(STM32WB05) || defined(STM32WB06)|| defined(STM32WB07)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__)                            == RCC_OSCILLATORTYPE_NONE)               || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)                || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)                || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)                || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE_BYPASS) == RCC_OSCILLATORTYPE_LSE_BYPASS))
#endif
#if defined(STM32WB09)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) ((((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)                || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)                || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)                || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE_BYPASS) == RCC_OSCILLATORTYPE_LSE_BYPASS))
#endif


#define IS_RCC_HSE(__HSE__)  (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON))

#define IS_RCC_HSI(__HSI__)  (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_LSE(__LSE__)  (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON))

#define IS_RCC_LSE_BYPASS(__LSE_BYPASS__)  (((__LSE_BYPASS__) == RCC_LSE_BYPASS_OFF) ||\
                                            ((__LSE_BYPASS__) == RCC_LSE_BYPASS_ON))

#define IS_RCC_LSI(__LSI__)  (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_RC64MPLL) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_DIRECT_HSE))

#define IS_RCC_SYSCLK_DIVIDER(__HCLK__) ((((__HCLK__) == RCC_RC64MPLL_DIV1) || ((__HCLK__) == RCC_RC64MPLL_DIV2)  || \
                                          ((__HCLK__) == RCC_RC64MPLL_DIV4) || ((__HCLK__) == RCC_RC64MPLL_DIV8)  || \
                                          ((__HCLK__) == RCC_RC64MPLL_DIV16)|| ((__HCLK__) == RCC_RC64MPLL_DIV32) || \
                                          ((__HCLK__) == RCC_RC64MPLL_DIV64)) || \
                                         (((__HCLK__) == RCC_DIRECT_HSE_DIV1) || ((__HCLK__) == RCC_DIRECT_HSE_DIV2)  || \
                                          ((__HCLK__) == RCC_DIRECT_HSE_DIV4) || ((__HCLK__) == RCC_DIRECT_HSE_DIV8)  || \
                                          ((__HCLK__) == RCC_RC64MPLL_DIV16)|| ((__HCLK__) == RCC_DIRECT_HSE_DIV32)))

#define IS_RCC_MCO(__MCOX__) ( ((__MCOX__) == RCC_MCO1) || ((__MCOX__) == RCC_MCO2) || ((__MCOX__) == RCC_MCO3) )

#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCOSOURCE_NOCLOCK)        || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SYSCLK)         || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI)            || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSE)            || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_RC64MPLL)       || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_HSI64M_DIV2048) || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_SMPS)           || \
                                       ((__SOURCE__) == RCC_MCOSOURCE_ADC))

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16)|| ((__DIV__) == RCC_MCODIV_32))

#define IS_RCC_LSE_DRIVE(__DRIVE__) (((__DRIVE__) == RCC_LSEDRIVE_LOW)        || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_HIGH))
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC Internal/External Oscillator (HSE, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t LSEBYPASSState;       /*!< The new state of the LSE Bypass.
                                      This parameter can be a value of @ref RCC_LSEBYPASS_Config                  */
} RCC_OscInitTypeDef;

/**
  * @brief  RCC System clock configuration structure definition
  */
typedef struct
{
  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t SYSCLKDivider;         /*!< The clock divider used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_RC64MPLL_Clock_Divider or
                                       @ref RCC_DIRECT_HSE_Clock_Divider */
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
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT  /* LSE timeout in ms        */
/**
  * @}
  */

/** @defgroup RCC_HSI_CALIBRATION_DEFAULT HSI default calibration trimming value
  * @{
  */
#define RCC_HSICALIBRATION_DEFAULT     0x1FU        /*!< Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_HSI         0x00000010U   /*!< Oscillator configuration unchanged  */
#define RCC_OSCILLATORTYPE_NONE         0x00000000U   /*!< Oscillator configuration unchanged  */
#define RCC_OSCILLATORTYPE_HSE         0x00000001U   /*!< HSE to configure                    */
#define RCC_OSCILLATORTYPE_LSE         0x00000002U   /*!< LSE to configure                    */
#define RCC_OSCILLATORTYPE_LSI         0x00000004U   /*!< LSI to configure                    */
#define RCC_OSCILLATORTYPE_LSE_BYPASS  0x00000008U   /*!< Slow clock is directly provided     */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                   RCC_CFGR_STOPHSI     /*!< HSI clock activation   */
#define RCC_HSI_ON                    0x00000000U          /*!< HSI clock deactivation */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0x00000000U      /*!< HSE clock deactivation */
#define RCC_HSE_ON                     RCC_CR_HSEON     /*!< HSE clock activation   */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0x00000000U     /*!< LSE clock deactivation */
#define RCC_LSE_ON                     RCC_CR_LSEON    /*!< LSE clock activation   */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U     /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CR_LSION    /*!< LSI clock activation   */
/**
  * @}
  */

/** @defgroup RCC_LSEBYPASS_Config LSE BYPASS Config
  * @{
  */
#define RCC_LSE_BYPASS_OFF             0x00000000U     /*!< LSE clock deactivation */
#define RCC_LSE_BYPASS_ON              RCC_CR_LSEBYP   /*!< LSE clock activation   */
/**
  * @}
  */

/** @defgroup RCC_RF_Clock  RF Clock
  * @{
  */
#define RCC_RF_CLK_16M       LL_RCC_RF_CLK_16M   /*!< RF system clock 16 MHz*/
#define RCC_RF_CLK_32M       LL_RCC_RF_CLK_32M   /*!< RF system clock 32 MHz */
/**
  * @}
  */

/** @defgroup RCC_DIRECT_HSE_Clock_Divider DIRECT HSE Clock Divider
  * @{
  */
#define RCC_DIRECT_HSE_DIV1              LL_RCC_DIRECT_HSE_DIV_1   /*!< DIRECT HSE division factor = 1   */
#define RCC_DIRECT_HSE_DIV2              LL_RCC_DIRECT_HSE_DIV_2   /*!< DIRECT HSE division factor = 2   */
#define RCC_DIRECT_HSE_DIV4              LL_RCC_DIRECT_HSE_DIV_4   /*!< DIRECT HSE division factor = 4   */
#define RCC_DIRECT_HSE_DIV8              LL_RCC_DIRECT_HSE_DIV_8   /*!< DIRECT HSE division factor = 8   */
#define RCC_DIRECT_HSE_DIV16             LL_RCC_DIRECT_HSE_DIV_16  /*!< DIRECT HSE division factor = 16  */
#define RCC_DIRECT_HSE_DIV32             LL_RCC_DIRECT_HSE_DIV_32  /*!< DIRECT HSE division factor = 32  */
/**
  * @}
  */

/** @defgroup RCC_RC64MPLL_Clock_Divider RC64MPLL Clock Divider
  * @{
  */
#define RCC_RC64MPLL_DIV1              LL_RCC_RC64MPLL_DIV_1    /*!< RC64MPLL division factor = 1   */
#define RCC_RC64MPLL_DIV2              LL_RCC_RC64MPLL_DIV_2    /*!< RC64MPLL division factor = 2   */
#define RCC_RC64MPLL_DIV4              LL_RCC_RC64MPLL_DIV_4    /*!< RC64MPLL division factor = 4   */
#define RCC_RC64MPLL_DIV8              LL_RCC_RC64MPLL_DIV_8    /*!< RC64MPLL division factor = 8   */
#define RCC_RC64MPLL_DIV16             LL_RCC_RC64MPLL_DIV_16   /*!< RC64MPLL division factor = 16  */
#define RCC_RC64MPLL_DIV32             LL_RCC_RC64MPLL_DIV_32   /*!< RC64MPLL division factor = 32  */
#define RCC_RC64MPLL_DIV64             LL_RCC_RC64MPLL_DIV_64   /*!< RC64MPLL division factor = 64  */
/**
  * @}
  */

/** @defgroup RCC_Clock_SWITCH_Divider Clock Switch Divider
  * @{
  */
#define RCC_RC64MPLL_SWITCH_DIV1           LL_RCC_RC64MPLL_SWITCH_DIV_1    /*!< RC64MPLL division factor = 1   */
#define RCC_RC64MPLL_SWITCH_DIV2           LL_RCC_RC64MPLL_SWITCH_DIV_2    /*!< RC64MPLL division factor = 2   */
#define RCC_RC64MPLL_SWITCH_DIV4           LL_RCC_RC64MPLL_SWITCH_DIV_4    /*!< RC64MPLL division factor = 4   */
#define RCC_DIRECT_HSE_SWITCH_DIV1         LL_RCC_RC64MPLL_SWITCH_DIV_2    /*!< Direct HSE division factor = 1 */
#define RCC_DIRECT_HSE_SWITCH_DIV2         LL_RCC_RC64MPLL_SWITCH_DIV_4    /*!< Direct HSE division factor = 2 */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_RC64MPLL      0x00000000U   /*!< RC64MPLL system clock configuration   */
#define RCC_SYSCLKSOURCE_DIRECT_HSE    0x00000001U   /*!< DIRECT HSE system clock configuration */
#define RCC_SYSCLKSOURCE_HSI           0x00000002U   /*!< RC64MPLL system clock configuration   */

/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO1                       0x00000000U          /*!< MCO1 index */
#define RCC_MCO2                       0x00000001U          /*!< MCO2 index */
#define RCC_MCO3                       0x00000002U          /*!< MCO3 index */
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source MCO Clock Source
  * @{
  */
#define RCC_MCOSOURCE_NOCLOCK         LL_RCC_MCOSOURCE_NOCLOCK            /*!< MCO output disabled, no clock on MCO */
#define RCC_MCO1SOURCE_SYSCLK          LL_RCC_MCOSOURCE_SYSCLK             /*!< SYSCLK selection as MCO source */
#define RCC_MCO1SOURCE_HSI             LL_RCC_MCOSOURCE_HSI                /*!< HSI selection as MCO source */
#define RCC_MCO1SOURCE_HSE             LL_RCC_MCOSOURCE_HSE                /*!< HSE after stabilization selection as MCO source */
#define RCC_MCOSOURCE_RC64MPLL        LL_RCC_MCOSOURCE_RC64MPLL           /*!< RC64MPLL selection as MCO source */
#define RCC_MCOSOURCE_HSI64M_DIV2048  LL_RCC_MCOSOURCE_HSI64M_DIV2048     /*!< HSI64M_DIV2048 selection as MCO source */
#define RCC_MCOSOURCE_SMPS            LL_RCC_MCOSOURCE_SMPS               /*!< SMPS selection as MCO source */
#define RCC_MCOSOURCE_ADC             LL_RCC_MCOSOURCE_ADC                /*!< ADC selection as MCO source */
/**
  * @}
  */


/** @defgroup RCC_MCOx_Clock_Prescaler MCO Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                   LL_RCC_MCO_DIV_1                  /*!< MCO not divided */
#define RCC_MCODIV_2                   LL_RCC_MCO_DIV_2                  /*!< MCO divided by 2 */
#define RCC_MCODIV_4                   LL_RCC_MCO_DIV_4                  /*!< MCO divided by 4 */
#define RCC_MCODIV_8                   LL_RCC_MCO_DIV_8                  /*!< MCO divided by 8 */
#define RCC_MCODIV_16                  LL_RCC_MCO_DIV_16                 /*!< MCO divided by 16 */
#define RCC_MCODIV_32                  LL_RCC_MCO_DIV_32                 /*!< MCO divided by 32 */
/**
  * @}
  */

/** @defgroup RCC_HSEAMPTHRESHOLD HSE bias current factor
  * @{
  */
#if defined(RCC_RFSWHSECR_SATRG)
#define RCC_HSEAMPTHRESHOLD_1_2       LL_RCC_HSEAMPTHRESHOLD_1_2           /*!< HSE bias current factor 1/2 */
#define RCC_HSEAMPTHRESHOLD_3_4       LL_RCC_HSEAMPTHRESHOLD_3_4           /*!< HSE bias current factor 3/4 */
#endif
/**
  * @}
  */

/** @defgroup RCC_HSE_CURRENTMAX HSE current max limit
  * @{
  */
#define RCC_HSE_CURRENTMAX_0           LL_RCC_HSE_CURRENTMAX_0             /*!< HSE current max limit 0.18 mA/V */
#define RCC_HSE_CURRENTMAX_1           LL_RCC_HSE_CURRENTMAX_1             /*!< HSE current max limit 0.57 mA/V */
#define RCC_HSE_CURRENTMAX_2           LL_RCC_HSE_CURRENTMAX_2             /*!< HSE current max limit 0.78 mA/V */
#define RCC_HSE_CURRENTMAX_3           LL_RCC_HSE_CURRENTMAX_3             /*!< HSE current max limit 1.13 mA/V */
#define RCC_HSE_CURRENTMAX_4           LL_RCC_HSE_CURRENTMAX_4             /*!< HSE current max limit 0.61 mA/V */
#define RCC_HSE_CURRENTMAX_5           LL_RCC_HSE_CURRENTMAX_5             /*!< HSE current max limit 1.65 mA/V */
#define RCC_HSE_CURRENTMAX_6           LL_RCC_HSE_CURRENTMAX_6             /*!< HSE current max limit 2.12 mA/V */
#define RCC_HSE_CURRENTMAX_7           LL_RCC_HSE_CURRENTMAX_7             /*!< HSE current max limit 2.84 mA/V */
/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                  LL_RCC_CIFR_LSIRDYF      /*!< LSI Ready Interrupt flag */
#define RCC_IT_LSERDY                  LL_RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt flag */
#define RCC_IT_HSIRDY                  LL_RCC_CIFR_HSIRDYF      /*!< HSI Ready Interrupt flag */
#define RCC_IT_HSERDY                  LL_RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt flag */
#define RCC_IT_PLLRDY                  LL_RCC_CIFR_PLLRDYF      /*!< PLL Ready Interrupt flag */
#define RCC_IT_PLL_UNLOCK              LL_RCC_CIFR_PLLUNLOCKDETF /*!< PLL Unlock Interrupt flag */
#define RCC_IT_RTCRSTRELRDY            LL_RCC_CIFR_RTCRSTRELF   /*!< RTC Reset Release Interrupt Flag */
#define RCC_IT_WDGRSTRELRDY            LL_RCC_CIFR_WDGRSTRELF   /*!< WDG Reset Release Interrupt Flag */
#if defined(RCC_CIFR_LPURSTF)
#define RCC_IT_LPURSTRELRDY            LL_RCC_CIFR_LPURSTRELF   /*!< LPU Reset Release Interrupt Flag */
#endif
/**
  * @}
  */

/** @defgroup RCC_Flag Flags
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                RCC_CR_HSIRDY        /*!< HSI Ready flag */
#define RCC_FLAG_HSERDY                RCC_CR_HSERDY        /*!< HSE Ready flag */
#define RCC_FLAG_PLLRDY                RCC_CR_HSIPLLRDY     /*!< PLL Ready flag */
#define RCC_FLAG_LSIRDY                RCC_CR_LSIRDY        /*!< LSI Ready flag */
#define RCC_FLAG_LSERDY                RCC_CR_LSERDY        /*!< LSE Ready flag */

/* Flags in the CSR register */
#define RCC_FLAG_LOCKUPRST             RCC_CSR_LOCKUPRSTF   /*!< CPU lockup reset flag      */
#define RCC_FLAG_WDGRST                RCC_CSR_WDGRSTF      /*!< Watchdog reset flag        */
#define RCC_FLAG_SFTRST                RCC_CSR_SFTRSTF      /*!< Software reset flag        */
#define RCC_FLAG_PORRST                RCC_CSR_PORRSTF      /*!< Power-On or BOR reset flag */
#define RCC_FLAG_PADRSTF               RCC_CSR_PADRSTF      /*!< NRSTn pad reset flag       */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Configuration
  * @{
  */
#define RCC_LSEDRIVE_LOW                 LL_RCC_LSEDRIVE_LOW            /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           LL_RCC_LSEDRIVE_MEDIUMLOW      /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          LL_RCC_LSEDRIVE_MEDIUMHIGH     /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                LL_RCC_LSEDRIVE_HIGH           /*!< LSE high drive capability */
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
#define __HAL_RCC_DMA_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA)
#define __HAL_RCC_GPIOA_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_CRC_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_RNG)


#define __HAL_RCC_DMA_CLK_DISABLE()            LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA)
#define __HAL_RCC_GPIOA_CLK_DISABLE()          LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_DISABLE()          LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_CRC_CLK_DISABLE()            LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_CLK_DISABLE()            LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_CLK_DISABLE()            LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_RNG)

/**
  * @}
  */

/** @defgroup RCC_APB0_Clock_Enable_Disable APB0 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB0 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(TIM1)
#define __HAL_RCC_TIM1_CLK_ENABLE()            LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_TIM1)
#endif
#if defined(TIM2)
#define __HAL_RCC_TIM2_CLK_ENABLE()            LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_CLK_ENABLE()          LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_SYSCFG)
#if defined(COMP1)
#define __HAL_RCC_COMP_CLK_ENABLE()            LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_CLK_ENABLE()            LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_CLK_ENABLE()             LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_RTC)

#define __HAL_RCC_WDG_CLK_ENABLE()             LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_WDG)
#if defined(TIM16)
#define __HAL_RCC_TIM16_CLK_ENABLE()           LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_TIM16)
#endif
#if defined(TIM17)
#define __HAL_RCC_TIM17_CLK_ENABLE()           LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_TIM17)
#endif

#if defined(TIM1)
#define __HAL_RCC_TIM1_CLK_DISABLE()           LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_TIM1)
#endif
#if defined(TIM2)
#define __HAL_RCC_TIM2_CLK_DISABLE()           LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_CLK_DISABLE()         LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_SYSCFG)
#if defined(COMP1)
#define __HAL_RCC_COMP_CLK_DISABLE()           LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_CLK_DISABLE()            LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_CLK_DISABLE()            LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_RTC)

#define __HAL_RCC_WDG_CLK_DISABLE()            LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_WDG)
#if defined(TIM16)
#define __HAL_RCC_TIM16_CLK_DISABLE()          LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_TIM16)
#endif
#if defined(TIM17)
#define __HAL_RCC_TIM17_CLK_DISABLE()          LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_TIM17)
#endif
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
#if defined(SPI1)
#define __HAL_RCC_SPI1_CLK_ENABLE()            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_CLK_ENABLE()          LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_CLK_ENABLE()          LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART1_CLK_ENABLE()         LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPUART1)
#define __HAL_RCC_USART1_CLK_ENABLE()          LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART1)
#if defined(SPI2)
#define __HAL_RCC_SPI2_CLK_ENABLE()            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2)
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_CLK_ENABLE()            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3)
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_CLK_ENABLE()            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1)
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_ENABLE()            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2)
#endif

#if defined(SPI1)
#define __HAL_RCC_SPI1_CLK_DISABLE()           LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_CLK_DISABLE()         LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_CLK_DISABLE()         LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART1_CLK_DISABLE()        LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPUART1)
#define __HAL_RCC_USART1_CLK_DISABLE()         LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART1)
#if defined(SPI2)
#define __HAL_RCC_SPI2_CLK_DISABLE()           LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2)
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_CLK_DISABLE()           LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3)
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_CLK_DISABLE()           LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1)
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_CLK_DISABLE()           LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2)
#endif
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
#if defined(BLUE)
#define __HAL_RCC_RADIO_CLK_ENABLE()            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_MRBLE)

#define __HAL_RCC_RADIO_CLK_DISABLE()           LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_MRBLE)
#endif

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
#define __HAL_RCC_DMA_IS_CLK_ENABLED()             LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA)
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()           LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()           LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()             LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_IS_CLK_ENABLED()             LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_IS_CLK_ENABLED()             LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_RNG)


#define __HAL_RCC_DMA_IS_CLK_DISABLED()            !(LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA))
#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()          !(LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOA))
#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()          !(LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOB))
#define __HAL_RCC_CRC_IS_CLK_DISABLED()            !(LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CRC))
#if defined(PKA)
#define __HAL_RCC_PKA_IS_CLK_DISABLED()            !(LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_PKA))
#endif
#define __HAL_RCC_RNG_IS_CLK_DISABLED()            !(LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_RNG))

/**
  * @}
  */

/** @defgroup RCC_APB0_Clock_Enable_Disable_Status APB0 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB0 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(TIM1)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()            LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM1)
#endif
#if defined(TIM2)
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()            LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()          LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_SYSCFG)
#if defined(COMP1)
#define __HAL_RCC_COMP_IS_CLK_ENABLED()            LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()             LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_IS_CLK_ENABLED()             LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_RTC)

#define __HAL_RCC_WDG_IS_CLK_ENABLED()             LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_WDG)
#if defined(TIM16)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()           LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM16)
#endif
#if defined(TIM17)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()           LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM17)
#endif

#if defined(TIM1)
#define __HAL_RCC_TIM1_IS_CLK_DISABLED()           !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM1))
#endif
#if defined(TIM2)
#define __HAL_RCC_TIM2_IS_CLK_DISABLED()           !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM2))
#endif
#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()         !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_SYSCFG))
#if defined(COMP1)
#define __HAL_RCC_COMP_IS_CLK_DISABLED()           !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_COMP))
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()            !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_DAC))
#endif
#define __HAL_RCC_RTC_IS_CLK_DISABLED()            !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_RTC))

#define __HAL_RCC_WDG_IS_CLK_DISABLED()            !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_WDG))
#if defined(TIM16)
#define __HAL_RCC_TIM16_IS_CLK_DISABLED()          !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM16))
#endif
#if defined(TIM17)
#define __HAL_RCC_TIM17_IS_CLK_DISABLED()          !(LL_APB0_GRP1_IsEnabledClock(LL_APB0_GRP1_PERIPH_TIM17))
#endif
/**
  * @}
  */


/** @defgroup RCC_APB1_Clock_Enable_Disable_Status APB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(SPI1)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()            LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADCDIG_IS_CLK_ENABLED()          LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_ADCDIG)
#define __HAL_RCC_ADCANA_IS_CLK_ENABLED()          LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_ADCANA)
#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()         LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_LPUART1)
#define __HAL_RCC_USART1_IS_CLK_ENABLED()          LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART1)
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()            LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2)
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()            LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI3)
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()            LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1)
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()            LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C2)
#endif

#if defined(SPI1)
#define __HAL_RCC_SPI1_IS_CLK_DISABLED()           !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI1))
#endif
#define __HAL_RCC_ADCDIG_IS_CLK_DISABLED()         !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_ADCDIG))
#define __HAL_RCC_ADCANA_IS_CLK_DISABLED()         !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_ADCANA))
#define __HAL_RCC_LPUART1_IS_CLK_DISABLED()        !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_LPUART1))
#define __HAL_RCC_USART1_IS_CLK_DISABLED()         !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART1))
#if defined(SPI2)
#define __HAL_RCC_SPI2_IS_CLK_DISABLED()           !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2))
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()           !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI3))
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_IS_CLK_DISABLED()           !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1))
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_IS_CLK_DISABLED()           !(LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C2))
#endif
/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enable_Disable_Status APB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(BLUE)
#define __HAL_RCC_RADIO_IS_CLK_ENABLED()            LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_MRBLE)

#define __HAL_RCC_RADIO_IS_CLK_DISABLED()           !(LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_MRBLE))
#endif

/**
  * @}
  */

/** @defgroup RCC_AHB_Force_Release_Reset AHB Peripheral Force Release Reset
  * @brief  Force or release AHB peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB1_FORCE_RESET()             LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_ALL)
#define __HAL_RCC_DMA_FORCE_RESET()             LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA)
#define __HAL_RCC_GPIOA_FORCE_RESET()           LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_FORCE_RESET()           LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_CRC_FORCE_RESET()             LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_FORCE_RESET()             LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_FORCE_RESET()             LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_RNG)

#define __HAL_RCC_AHB1_RELEASE_RESET()           LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_ALL)
#define __HAL_RCC_DMA_RELEASE_RESET()           LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA)
#define __HAL_RCC_GPIOA_RELEASE_RESET()         LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_RELEASE_RESET()         LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_CRC_RELEASE_RESET()           LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CRC)
#if defined(PKA)
#define __HAL_RCC_PKA_RELEASE_RESET()           LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_PKA)
#endif
#define __HAL_RCC_RNG_RELEASE_RESET()           LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_RNG)


/**
  * @}
  */

/** @defgroup RCC_APB0_Force_Release_Reset APB0 Peripheral Force Release Reset
  * @brief  Force or release APB0 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB0_FORCE_RESET()            LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_ALL)
#if defined(TIM1)
#define __HAL_RCC_TIM1_FORCE_RESET()            LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_TIM1)
#endif
#if defined(TIM2)
#define __HAL_RCC_TIM2_FORCE_RESET()            LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_FORCE_RESET()          LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_SYSCFG)
#if defined(COMP1)
#define __HAL_RCC_COMP_FORCE_RESET()            LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_FORCE_RESET()             LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_FORCE_RESET()             LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_RTC)

#define __HAL_RCC_WDG_FORCE_RESET()             LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_WDG)
#if defined(TIM16)
#define __HAL_RCC_TIM16_FORCE_RESET()           LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_TIM16)
#endif
#if defined(TIM17)
#define __HAL_RCC_TIM17_FORCE_RESET()           LL_APB0_GRP1_ForceReset(LL_APB0_GRP1_PERIPH_TIM17)
#endif

#define __HAL_RCC_APB0_RELEASE_RESET()          LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_ALL)
#if defined(TIM1)
#define __HAL_RCC_TIM1_RELEASE_RESET()          LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_TIM1)
#endif
#if defined(TIM2)
#define __HAL_RCC_TIM2_RELEASE_RESET()          LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_TIM2)
#endif
#define __HAL_RCC_SYSCFG_RELEASE_RESET()        LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_SYSCFG)
#if defined(COMP1)
#define __HAL_RCC_COMP_RELEASE_RESET()          LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_COMP)
#endif
#if defined(DAC)
#define __HAL_RCC_DAC_RELEASE_RESET()           LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_DAC)
#endif
#define __HAL_RCC_RTC_RELEASE_RESET()           LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_RTC)

#define __HAL_RCC_WDG_RELEASE_RESET()           LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_WDG)
#if defined(TIM16)
#define __HAL_RCC_TIM16_RELEASE_RESET()         LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_TIM16)
#endif
#if defined(TIM17)
#define __HAL_RCC_TIM17_RELEASE_RESET()         LL_APB0_GRP1_ReleaseReset(LL_APB0_GRP1_PERIPH_TIM17)
#endif
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_FORCE_RESET()            LL_APB1_GRP1_ForceReset( LL_APB1_GRP1_RESET_PERIPH_ALL)

#if defined(SPI1)
#define __HAL_RCC_SPI1_FORCE_RESET()            LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADC_FORCE_RESET()             LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_ADCDIG)
#define __HAL_RCC_LPUART1_FORCE_RESET()         LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_LPUART1)
#define __HAL_RCC_USART1_FORCE_RESET()          LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART1)
#if defined(SPI2)
#define __HAL_RCC_SPI2_FORCE_RESET()            LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2)
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_FORCE_RESET()            LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI3)
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_FORCE_RESET()            LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1)
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_FORCE_RESET()            LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2)
#endif

#define __HAL_RCC_APB1_RELEASE_RESET()          LL_APB1_GRP1_ReleaseReset( LL_APB1_GRP1_RESET_PERIPH_ALL)

#if defined(SPI1)
#define __HAL_RCC_SPI1_RELEASE_RESET()          LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI1)
#endif
#define __HAL_RCC_ADC_RELEASE_RESET()           LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_ADCDIG)
#define __HAL_RCC_LPUART1_RELEASE_RESET()       LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_LPUART1)
#define __HAL_RCC_USART1_RELEASE_RESET()        LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART1)
#if defined(SPI2)
#define __HAL_RCC_SPI2_RELEASE_RESET()          LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2)
#endif
#if defined(SPI3)
#define __HAL_RCC_SPI3_RELEASE_RESET()          LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI3)
#endif
#if defined(I2C1)
#define __HAL_RCC_I2C1_RELEASE_RESET()          LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1)
#endif
#if defined(I2C2)
#define __HAL_RCC_I2C2_RELEASE_RESET()          LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2)
#endif
/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()             LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_ALL)
#if defined(BLUE)
#define __HAL_RCC_RADIO_FORCE_RESET()            LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_MRBLE)
#endif

#define __HAL_RCC_APB2_RELEASE_RESET()           LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_ALL)
#if defined(BLUE)
#define __HAL_RCC_RADIO_RELEASE_RESET()          LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_MRBLE)
#endif

/**
  * @}
  */

/** @defgroup RCC_CLK_CONFIG_MACROS Clock Configuration Macros
  * @{
  */
/** @defgroup RCC_LSI_MACROS LSI Macros
  * @{
  */

 /**
  * @brief  Macro to configure the Internal High Speed oscillator (HSI).
  * @note   After enabling the HSI (RCC_HSI_ON), the application
  *         software should wait on HSIRDY flag to be set indicating that HSI clock
  *         is stable.
  * @note   The HSI is stopped by hardware when entering DEEPSTOP and SHUTDOWN modes.
  * @param  __STATE__  specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  * @retval None
  */
#define __HAL_RCC_HSI_CONFIG(__STATE__)    \
  do {                                     \
    if((__STATE__) == RCC_HSI_ON)          \
    {                                      \
      LL_RCC_HSI_Enable();                 \
    }                                      \
    else                                   \
    {                                      \
      LL_RCC_HSI_Disable();                \
    }                                      \
  } while(0U)

/**
  * @brief  Macro to get the HSI ready flag.
  * @retval Returns the Ready Flag status
  */
#define __HAL_RCC_GET_HSI_READYFLAG() LL_RCC_HSI_IsReady()

/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between Min_data=0 and Max_Data=63.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__)  LL_RCC_HSI_SetCalibTrimming(__HSICALIBRATIONVALUE__)
/**
  * @}
  */

/** @defgroup RCC_LSI_MACROS LSI Macros
  * @{
  */
/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI1 oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         LL_RCC_LSI_Enable()
#define __HAL_RCC_LSI_DISABLE()        LL_RCC_LSI_Disable()

/**
  * @brief  Macro to get the LSI ready flag.
  * @retval Returns the Ready Flag status
  */
#define __HAL_RCC_GET_LSI_READYFLAG() LL_RCC_LSI_IsReady()

/** @brief  Macro to adjust the Internal Low Speed oscillator (LSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __LSITRIMMINGVALUE__ specifies the calibration trimming value
  *         This parameter must be a number between Min_data=0 and Max_Data=15.
  * @retval None
  */
#define __HAL_RCC_LSI_CALIBRATIONVALUE_ADJUST(__LSITRIMMINGVALUE__)  LL_RCC_LSI_SetTrimming(__LSITRIMMINGVALUE__)
/**
  * @}
  */

/** @defgroup RCC_HSE_MACROS HSE Macros
  * @{
  */
/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the RC64MPLL.
  * @note   The HSE is stopped by hardware when entering DEEPSTOP and SHUTDOWN modes.
  * @param  __STATE__  specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                      \
  do {                                     \
    if((__STATE__) == RCC_HSE_ON)          \
    {                                      \
      LL_RCC_HSE_Enable();                  \
    }                                      \
    else                                   \
    {                                      \
      LL_RCC_HSE_Disable();                \
    }                                      \
  } while(0U)

/**
  * @brief  Macro to get the HSE ready flag.
  * @retval Returns the Ready Flag status
  */
#define __HAL_RCC_GET_HSE_READYFLAG() LL_RCC_HSE_IsReady()

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   After enabling the LSE (RCC_LSE_ON), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used.
  * @param  __STATE__  specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator.
  *            @arg @ref RCC_LSE_ON  Turn ON the LSE oscillator.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)                        \
  do {                                       \
    if((__STATE__) == RCC_LSE_ON)            \
    {                                        \
      LL_RCC_LSE_Enable();                   \
    }                                        \
    else                                     \
    {                                        \
      LL_RCC_LSE_Disable();                  \
    }                                        \
  } while(0U)

/**
  * @brief  Macro to get the LSE ready flag.
  * @retval Returns the Ready Flag status
  */
#define __HAL_RCC_GET_LSE_READYFLAG() LL_RCC_LSE_IsReady()

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) in Bypass mode.
  * @param  __STATE__  specifies the new state of the LSE bypass configuration.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_BYPASS_OFF  Turn OFF the LSE bypass configuration.
  *            @arg @ref RCC_LSE_BYPASS_ON  Turn ON the LSE bypass configuration.
  * @retval None
  */
#define __HAL_RCC_LSE_BYPASS_CONFIG(__STATE__)                 \
  do {                                       \
    if((__STATE__) == RCC_LSE_BYPASS_ON)     \
    {                                        \
      LL_RCC_LSE_EnableBypass();             \
    }                                        \
    else                                     \
    {                                        \
      LL_RCC_LSE_DisableBypass();            \
    }                                        \
  } while(0U)

#if defined(RCC_RFSWHSECR_SATRG)
/** @brief  Macros to configure HSE sense amplifier threshold.
  * @note   to configure HSE sense amplifier, first disable HSE
  *         using @ref __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF) macro.
  *
  * @param  __HSE_AMPTHRES__  specifies the HSE sense amplifier threshold.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSEAMPTHRESHOLD_1_2  HSE bias current factor 1/2.
  *            @arg @ref RCC_HSEAMPTHRESHOLD_3_4  HSE bias current factor 3/4.
  * @retval None
  */
#define __HAL_RCC_HSE_AMPCONFIG(__HSE_AMPTHRES__)  LL_RCC_HSE_SetSenseAmplifier(__HSE_AMPTHRES__)
#endif

/** @brief  Macros to configure HSE current control.
  * @note   to configure HSE current control, first disable HSE
  *         using @ref __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF) macro.
  *
  * @param  __HSE_CURRENTMAX__  specifies the HSE current max limit.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_CURRENTMAX_0  HSE current max limit 0.18 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_1  HSE current max limit 0.57 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_2  HSE current max limit 0.78 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_3  HSE current max limit 1.13 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_4  HSE current max limit 0.61 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_5  HSE current max limit 1.65 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_6  HSE current max limit 2.12 mA/V.
  *            @arg @ref RCC_HSE_CURRENTMAX_7  HSE current max limit 2.84 mA/V.
  * @retval None
  */
#define __HAL_RCC_HSE_CURRENTCONFIG(__HSE_CURRENTMAX__)  LL_RCC_HSE_SetCurrentControl(__HSE_CURRENTMAX__)

/** @brief  Macros to configure HSE capacitor tuning.
  * @note   to configure HSE current control, first disable HSE
  *         using __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF) macro.
  *
  * @param  __HSE_LOAD_CAPACITANCE__  specifies the HSE capacitor value.
  *         This Value Between Min_Data = 0 and Max_Data = 63
  * @retval None
  */
#define __HAL_RCC_HSE_CAPACITORTUNING(__HSE_LOAD_CAPACITANCE__)  LL_RCC_HSE_SetCapacitorTuning(__HSE_LOAD_CAPACITANCE__)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @param  __LSEDRIVE__  specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW  LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__)  LL_RCC_LSE_SetDriveCapability(__LSEDRIVE__)
/**
  * @}
  */

/** @defgroup RCC_CLK_SOURCE_CONFIG_MACROS Clock Source Configuration Macros
  * @{
  */
/** @brief  Macros to enable or disable the main RC64MPLL.
  * @note   After enabling the main RC64MPLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main RC64MPLL can not be disabled if it is used as system clock source
  * @note   The main RC64MPLL is disabled by hardware when entering DEEPSTOP and SHUTDOWN modes.
  * @retval None
  */
#define __HAL_RCC_RC64MPLL_ENABLE()         LL_RCC_RC64MPLL_Enable()
#define __HAL_RCC_RC64MPLL_DISABLE()        LL_RCC_RC64MPLL_Disable()

/**
  * @brief  Macro to get the RC64MPLL ready flag.
  * @retval Returns the Ready Flag status
  */
#define __HAL_RCC_RC64MPLL_READYFLAG()      LL_RCC_RC64MPLL_IsReady()

/** @brief  Macro to configure the RC64MPLL division factor.
  * @note   This function must be used only when the main RC64MPLL is disabled.
  * @param  __PLLD__  specifies the division factor
  *         This parameter must be a value of RCC_RC64MPLL_Clock_Divider.
  * @retval None
  *
  */
#define __HAL_RCC_RC64MPLL_PRESC_CONFIG(__PLLD__) LL_RCC_SetRC64MPLLPrescaler(__PLLD__)

/** @brief  Macro to configure the DIRERCT HSE division factor.
  * @note   This function must be used only when the main DIRECT HSE is disabled.
  * @param  __DIRECTHSED__  specifies the division factor
  *         This parameter must be a value of RCC_DIRECT_HSE_Clock_Divider.
  * @retval None
  *
  */
#define __HAL_RCC_DIRECT_HSE_PRESC_CONFIG(__DIRECTHSED__) MODIFY_REG(RCC->CFGR, RCC_CFGR_CLKSYSDIV, __DIRECTHSED__);

/** @brief  Macro to configure the RF clock frequency.
  * @param  __FREQ__  specifies the RF BLE clock frequency.
  *         This parameter must be a value of RCC_RF_Clock.
  * @retval None
  *
  */
#define __HAL_RCC_RF_CLK_SET_CONFIG(__FREQ__) LL_RCC_SetRFClock(__FREQ__)

/** @brief  Macro to get the RF BLE clock source.
  * @retval The RF BLE clock source. The returned value can be one of the
  *         following values:
  *              @arg @ref RCC_RF_CLK_16M
  *              @arg @ref RCC_RF_CLK_32M
  *
  */
#define __HAL_RCC_RF_CLK_GET_CONFIG() LL_RCC_GetRFClock()

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__  specifies the system clock source.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_SYSCLKSOURCE_RC64MPLL RC64PLL configuration is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_DIRECT_HSE DIRECT HSE configuration is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__)                           \
  do {                                                    \
    if((__SYSCLKSOURCE__) == RCC_SYSCLKSOURCE_RC64MPLL)   \
    {                                                     \
      LL_RCC_RC64MPLL_Enable();                           \
    }                                                     \
    else                                                  \
    {                                                     \
      LL_RCC_DIRECT_HSE_Enable();                         \
    }                                                     \
  } while(0U)

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              @arg @ref RCC_SYSCLKSOURCE_RC64MPLL RC64PLL configuration is used as system clock source..
  *              @arg @ref RCC_SYSCLKSOURCE_DIRECT_HSE DIRECT HSE configuration is used as system clock source.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE()        \
  (LL_RCC_DIRECT_HSE_IsEnabled() ? RCC_SYSCLKSOURCE_DIRECT_HSE : RCC_SYSCLKSOURCE_RC64MPLL)

/**
  * @}
  */

/** @defgroup RCC_MCO_CONFIG_MACROS Main Configurable Clock Output Selection Macros
  * @{
  */
/**
  * @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCOSOURCE_NOCLOCK          MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK           System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI              HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE              HSE clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_RC64MPLL         Main PLL clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_HSI64M_DIV2048   HSI div 2048 clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_SMPS             SMPS clock selected as MCO source
  *            @arg @ref RCC_MCOSOURCE_ADC              ADC clock selected as MCO source

  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  *            @arg @ref RCC_MCODIV_32  MCO clock source is divided by 32

  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__)  LL_RCC_ConfigMCO((__MCOCLKSOURCE__), (__MCODIV__))
/**
  * @}
  */
/**
  * @}
  */
/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */
/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__  specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY        LSI ready interrupt enable
  *            @arg RCC_IT_LSERDY        LSE ready interrupt enable
  *            @arg RCC_IT_HSIRDY        HSI ready interrupt enable
  *            @arg RCC_IT_HSERDY        HSE ready interrupt enable
  *            @arg RCC_IT_PLLRDY        Main PLL ready interrupt enable
  *            @arg RCC_IT_PLL_UNLOCKRDY PLL unlock interrupt enable
  *            @arg RCC_IT_RTCRSTRELRDY  RTC Reset Release ready interrupt enable
  *            @arg RCC_IT_WDGRSTRELRDY  WDG Reset Release ready interrupt enable
  *            @arg RCC_IT_LPURSTRELRDY  LPU Reset Release ready interrupt enable
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt.
  * @param  __INTERRUPT__  specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY        LSI ready interrupt disable
  *            @arg RCC_IT_LSERDY        LSE ready interrupt disable
  *            @arg RCC_IT_HSIRDY        HSI ready interrupt disable
  *            @arg RCC_IT_HSERDY        HSE ready interrupt disable
  *            @arg RCC_IT_PLLRDY        Main PLL ready interrupt disable
  *            @arg RCC_IT_PLL_UNLOCKRDY PLL Unlock interrupt disable
  *            @arg RCC_IT_RTCRSTRELRDY  RTC Reset Release ready interrupt disable
  *            @arg RCC_IT_WDGRSTRELRDY  WDG Reset Release ready interrupt disable
  *            @arg RCC_IT_LPURSTRELRDY  LPU Reset Release ready interrupt disable
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear RCC interrupt pending bits (Perform Byte access to RCC_CICR[17:0]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__  specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY        LSI ready interrupt clear
  *            @arg RCC_IT_LSERDY        LSE ready interrupt clear
  *            @arg RCC_IT_HSIRDY        HSI ready interrupt clear
  *            @arg RCC_IT_HSERDY        HSE ready interrupt clear
  *            @arg RCC_IT_PLLRDY        Main PLL ready interrupt clear
  *            @arg RCC_IT_PLL_UNLOCKRDY PLL Unlock interrupt clear
  *            @arg RCC_IT_RTCRSTRELRDY  RTC Reset Release ready interrupt clear
  *            @arg RCC_IT_WDGRSTRELRDY  WDG Reset Release ready interrupt clear
  *            @arg RCC_IT_LPURSTRELRDY  LPU Reset Release ready interrupt clear
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CIFR = (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__  specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_IT_LSIRDY        LSI ready interrupt flag
  *            @arg RCC_IT_LSERDY        LSE ready interrupt flag
  *            @arg RCC_IT_HSIRDY        HSI ready interrupt flag
  *            @arg RCC_IT_HSERDY        HSE ready interrupt flag
  *            @arg RCC_IT_PLLRDY        Main PLL ready interrupt flag
  *            @arg RCC_IT_PLL_UNLOCKRDY PLL Unlock interrupt flag
  *            @arg RCC_IT_RTCRSTRELRDY  RTC Reset Release ready interrupt flag
  *            @arg RCC_IT_WDGRSTRELRDY  WDG Reset Release ready interrupt flag
  *            @arg RCC_IT_LPURSTRELRDY  LPU Reset Release ready interrupt flag
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))
/**
  * @}
  */

/** @defgroup RCC_Reset_Status_Management Rest Status Flags Management
  * @brief macros to manage the specified RCC Reset Flags.
  * @{
  */
/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_LOCKUPRST, RCC_FLAG_WDGRST, RCC_FLAG_SFTRST,
  *                             RCC_FLAG_PORRST and RCC_FLAG_PADRSTF.
  * @retval None
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() LL_RCC_ClearResetFlags()

/** @brief  Check whether the selected RCC Reset flag is set or not.
  * @param  __FLAG__  specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_LOCKUPRST   CPU lockup reset flag
  *            @arg @ref RCC_FLAG_WDGRST      Watchdog reset flag
  *            @arg @ref RCC_FLAG_SFTRST      Software reset flag
  *            @arg @ref RCC_FLAG_PORRST      Power-On or BOR reset flag
  *            @arg @ref RCC_FLAG_PADRSTF      NRSTn pad reset flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((__FLAG__) & 0x3FFFF) ?\
                                      ((RCC->CR & (__FLAG__)) == (__FLAG__)) :\
                                      ((RCC->CSR & (__FLAG__)) == (__FLAG__)))

/**
  * @}
  */

/** @defgroup RCC_HSECLK_BUFFER_RF_MACROS External high speed clock buffer for PLL RF2G4
  * @{
  */
/** @brief  Macros to enable or disable the high speed clock buffer for PLL RF2G4.
  * @retval Status of the high speed clock buffer for PLL RF2G4
  */
#define __HAL_RCC_HSEPLLBUFON_ENABLE()          LL_RCC_HSEPLLBUFON_Enable()
#define __HAL_RCC_HSEPLLBUFON_DISABLE()         LL_RCC_HSEPLLBUFON_Disable()

/** @brief  Macros to read the status of the high speed clock buffer for PLL RF2G4.
  * @retval Configuration status
  */
#define __HAL_RCC_HSEPLLBUFON_IS_ENABLED()  LL_RCC_HSEPLLBUFON_Disable()
/**
  * @}
  */

/** @defgroup RCC_CLOCK_SWITCH_MACROS Clock switch macros
  * @{
  */
/** @brief  Set RC64MPLL prescaler to switch the clock when the MR_BLE is enabled.
  * @note   The CPU/system frequency must be kept at minimum 16 MHz clock when the radio is used.
  * @param  __PLLD__  specifies the DIRECT_HSE or RC64MPLL value to setup.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_DIRECT_HSE_SWITCH_DIV1      DIRECT HSE division factor = 1
  *            @arg @ref RCC_DIRECT_HSE_SWITCH_DIV2      DIRECT HSE division factor = 2
  *            @arg @ref RCC_RC64MPLL_SWITCH_DIV1        RC64MPLL division factor = 1
  *            @arg @ref RCC_RC64MPLL_SWITCH_DIV2        RC64MPLL division factor = 2
  *            @arg @ref RCC_RC64MPLL_SWITCH_DIV4        RC64MPLL division factor = 4
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_CLOCK_SWITCH(__PLLD__)        \
  do {                                                                                \
    if (LL_RCC_GetRC64MPLLSwitchStatus() == LL_RCC_RC64MPLL_SWITCH_STATUS_IDLE)       \
    {                                                                                 \
      LL_RCC_SwitchRC64MPLLPrescaler(__PLLD__);                                 \
      LL_RCC_RequestSwitchRC64MPLLClock();                                    \
      while (LL_RCC_GetRC64MPLLSwitchStatus() != LL_RCC_RC64MPLL_SWITCH_STATUS_DONE); \
      LL_RCC_ClearFlag_EOFSEQ();                                                      \
    }                                                                                 \
  } while(0U)

/** @brief  Macros to enable or disable the interrupt of the CPU / system clock frequency switch.
  * @retval Status of the interrupt of the CPU / system clock frequency switch
  */
#define __HAL_RCC_CLOCK_SWITCH_IT_ENABLE()             LL_RCC_EnableIT_EOFSEQ()
#define __HAL_RCC_CLOCK_SWITCH_IT_DISABLE()            LL_RCC_DisableIT_EOFSEQ()

/** @brief  Macros to read the configuration status of the interrupt of the CPU / system clock frequency switch.
  * @retval Interrupt Enable status
  */
#define __HAL_RCC_CLOCK_SWITCH_INTERRUPT_IS_ENABLED()  LL_RCC_IsEnabledIT_EOFSEQ()

/** @brief  Macros to read the status of the interrupt of the CPU / system clock frequency switch.
  * @retval Interrupt status
  */
#define __HAL_RCC_CLOCK_SWITCH_INTERRUPT_STATUS()   LL_RCC_IsActiveFlag_EOFSEQ()

/** @brief  Macros to clear the status of the interrupt of the CPU / system clock frequency switch.
  * @retval Clear Interrupt status
  */
#define __HAL_RCC_CLOCK_SWITCH_CLEAR_INTERRUPT_STATUS()  LL_RCC_ClearFlag_EOFSEQ()
/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "stm32wb0x_hal_rcc_ex.h"

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
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void       HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
uint32_t   HAL_RCC_GetSysClockFreq(void);

void       HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void       HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

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

#endif /* STM32WB0x_HAL_RCC_H */
