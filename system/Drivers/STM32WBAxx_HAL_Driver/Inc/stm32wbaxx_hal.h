/**
  ******************************************************************************
  * @file    stm32wbaxx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef __STM32WBAxx_HAL_H
#define __STM32WBAxx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_conf.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HAL_Exported_Types HAL Exported Types
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/** @defgroup HAL_Exported_Variables HAL Exported Variables
  * @{
  */
extern __IO uint32_t            uwTick;
extern uint32_t                 uwTickPrio;
extern HAL_TickFreqTypeDef      uwTickFreq;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */

/**
  * @brief STM32WBAxx HAL Driver version number
  */
#define __STM32WBAxx_HAL_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32WBAxx_HAL_VERSION_SUB1   (0x04U) /*!< [23:16] sub1 version */
#define __STM32WBAxx_HAL_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32WBAxx_HAL_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32WBAxx_HAL_VERSION    ((__STM32WBAxx_HAL_VERSION_MAIN << 24U)\
                                     |(__STM32WBAxx_HAL_VERSION_SUB1 << 16U)\
                                     |(__STM32WBAxx_HAL_VERSION_SUB2 << 8U )\
                                     |(__STM32WBAxx_HAL_VERSION_RC))

/**
  * @}
  */

/** @defgroup REV_ID device revision ID
  * @{
  */
#define REV_ID_A 0x1000U  /*!< STM32WBA_2 rev.A */
#define REV_ID_B 0x2000U  /*!< STM32WBA_2 rev.B */
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_FPU_Interrupts FPU Interrupts
  * @{
  */
#define SYSCFG_IT_FPU_IOC              SYSCFG_FPUIMR_FPU_IE_0  /*!< Floating Point Unit Invalid operation Interrupt */
#define SYSCFG_IT_FPU_DZC              SYSCFG_FPUIMR_FPU_IE_1  /*!< Floating Point Unit Divide-by-zero Interrupt */
#define SYSCFG_IT_FPU_UFC              SYSCFG_FPUIMR_FPU_IE_2  /*!< Floating Point Unit Underflow Interrupt */
#define SYSCFG_IT_FPU_OFC              SYSCFG_FPUIMR_FPU_IE_3  /*!< Floating Point Unit Overflow Interrupt */
#define SYSCFG_IT_FPU_IDC              SYSCFG_FPUIMR_FPU_IE_4  /*!< Floating Point Unit Input denormal Interrupt */
#define SYSCFG_IT_FPU_IXC              SYSCFG_FPUIMR_FPU_IE_5  /*!< Floating Point Unit Inexact Interrupt */
#define SYSCFG_IT_FPU_ALL              (SYSCFG_IT_FPU_IOC|SYSCFG_IT_FPU_DZC|SYSCFG_IT_FPU_UFC|SYSCFG_IT_FPU_OFC|SYSCFG_IT_FPU_IDC|SYSCFG_IT_FPU_IXC)  /*!< All */

/**
  * @}
  */

/** @defgroup SYSCFG_Compensation_Cell_Selection Compensation Cell Selection
  * @{
  */
#define SYSCFG_IO_CELL    SYSCFG_CCCSR_EN1   /*!< Compensation cell for the VDD I/O power rail */
#ifdef SYSCFG_CCCSR_EN2
#define SYSCFG_IO2_CELL   SYSCFG_CCCSR_EN2   /*!< Compensation cell for the VDDIO2 I/O power rail */
#endif /* SYSCFG_CCCSR_EN2 */
/**
  * @}
  */

/** @defgroup SYSCFG_Compensation_Cell_Ready_Selection Compensation Cell Ready Selection
  * @{
  */
#define SYSCFG_IO_CELL_READY    SYSCFG_CCCSR_RDY1  /*!< Ready flag of compensation cell for the VDD I/O power rail */
#ifdef SYSCFG_CCCSR_EN2
#define SYSCFG_IO2_CELL_READY   SYSCFG_CCCSR_RDY2  /*!< Ready flag of compensation cell for the VDDIO2 I/O power rail */
#endif /* SYSCFG_CCCSR_EN2 */
/**
  * @}
  */

/** @defgroup SYSCFG_IO_Compensation_Code_Config IO Compensation Code config
  * @{
  */
#define SYSCFG_IO_CELL_CODE       0UL   /*!< Code from the cell */
#define SYSCFG_IO_REGISTER_CODE   1UL   /*!< Code from the values in the cell code register */
/**
  * @}
  */


/** @defgroup SYSCFG_Flags_Definition Flags
  * @{
  */

#define SYSCFG_FLAG_MCLR               SYSCFG_MESR_MCLR        /*!< Device memories erase status */
#define SYSCFG_FLAG_IPMEE              SYSCFG_MESR_IPMEE       /*!< ICACHE and PKA SRAM erase status */

/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_PA6        SYSCFG_CFGR1_PA6_FMP   /*!< Enable Fast-mode Plus on PA6  */
#define SYSCFG_FASTMODEPLUS_PA7        SYSCFG_CFGR1_PA7_FMP   /*!< Enable Fast-mode Plus on PA7  */
#define SYSCFG_FASTMODEPLUS_PA15       SYSCFG_CFGR1_PA15_FMP  /*!< Enable Fast-mode Plus on PA15 */
#define SYSCFG_FASTMODEPLUS_PB3        SYSCFG_CFGR1_PB3_FMP   /*!< Enable Fast-mode Plus on PB3  */
#define SYSCFG_FASTMODEPLUS_ALL        (SYSCFG_FASTMODEPLUS_PA6|SYSCFG_FASTMODEPLUS_PA7|SYSCFG_FASTMODEPLUS_PA15|SYSCFG_FASTMODEPLUS_PB3)  /*!< All */

/**
  * @}
  */

/** @defgroup SYSCFG_Lock_items SYSCFG Lock items
  * @brief SYSCFG items to set lock on
  * @{
  */
#define SYSCFG_MPU_NSEC                SYSCFG_CNSLCKR_LOCKNSMPU            /*!< Non-secure MPU lock (privileged secure or non-secure only) */
#define SYSCFG_VTOR_NSEC               SYSCFG_CNSLCKR_LOCKNSVTOR           /*!< Non-secure VTOR lock (privileged secure or non-secure only) */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define SYSCFG_SAU                     (SYSCFG_CSLCKR_LOCKSAU << 16U)      /*!< SAU lock (privileged secure code only) */
#define SYSCFG_MPU_SEC                 (SYSCFG_CSLCKR_LOCKSMPU << 16U)     /*!< Secure MPU lock (privileged secure code only) */
#define SYSCFG_VTOR_AIRCR_SEC          (SYSCFG_CSLCKR_LOCKSVTAIRCR << 16U) /*!< VTOR_S and AIRCR lock (privileged secure code only) */
#define SYSCFG_LOCK_ALL                (SYSCFG_MPU_NSEC|SYSCFG_VTOR_NSEC|SYSCFG_SAU|SYSCFG_MPU_SEC|SYSCFG_VTOR_AIRCR_SEC)  /*!< All */
#else
#define SYSCFG_LOCK_ALL                (SYSCFG_MPU_NSEC|SYSCFG_VTOR_NSEC)  /*!< All (privileged secure or non-secure only) */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

#if defined (SYSCFG_SECCFGR_SYSCFGSEC)
/** @defgroup SYSCFG_Attributes_items SYSCFG Attributes items
  * @brief SYSCFG items to configure secure or non-secure attributes on
  * @{
  */
#define SYSCFG_CLK                     SYSCFG_SECCFGR_SYSCFGSEC   /*!< SYSCFG clock control */
#define SYSCFG_CLASSB                  SYSCFG_SECCFGR_CLASSBSEC   /*!< Class B */
#define SYSCFG_FPU                     SYSCFG_SECCFGR_FPUSEC      /*!< FPU */
#define SYSCFG_ALL                     (SYSCFG_CLK | SYSCFG_CLASSB | SYSCFG_FPU) /*!< All */
/**
  * @}
  */
#endif /* SYSCFG_SECCFGR_SYSCFGSEC */

/** @defgroup SYSCFG_attributes SYSCFG attributes
  * @brief SYSCFG secure or non-secure attributes
  * @{
  */
#define SYSCFG_SEC                     0x00000001U   /*!< Secure attribute      */
#define SYSCFG_NSEC                    0x00000000U   /*!< Non-secure attribute  */
/**
  * @}
  */

#ifdef SYSCFG_OTGHSPHYCR_EN
/** @defgroup SYSCFG_OTG_PHY_RefenceClockSelection  OTG PHY Reference Clock Selection
  * @{
  */

/** @brief  OTG HS PHY reference clock frequency selection
  */
#define SYSCFG_OTG_HS_PHY_CLK_SELECT_1 (SYSCFG_OTGHSPHYCR_CLKSEL_0 | SYSCFG_OTGHSPHYCR_CLKSEL_1)                              /*!< 16Mhz */
#define SYSCFG_OTG_HS_PHY_CLK_SELECT_2 SYSCFG_OTGHSPHYCR_CLKSEL_3                                                             /*!< 19.2Mhz */
#define SYSCFG_OTG_HS_PHY_CLK_SELECT_3 (SYSCFG_OTGHSPHYCR_CLKSEL_0 | SYSCFG_OTGHSPHYCR_CLKSEL_3)                              /*!< 20Mhz */
#define SYSCFG_OTG_HS_PHY_CLK_SELECT_4 (SYSCFG_OTGHSPHYCR_CLKSEL_1 | SYSCFG_OTGHSPHYCR_CLKSEL_3)                              /*!< 24Mhz */
#define SYSCFG_OTG_HS_PHY_CLK_SELECT_5 (SYSCFG_OTGHSPHYCR_CLKSEL_1 | SYSCFG_OTGHSPHYCR_CLKSEL_2 | SYSCFG_OTGHSPHYCR_CLKSEL_3) /*!< 26Mhz */
#define SYSCFG_OTG_HS_PHY_CLK_SELECT_6 (SYSCFG_OTGHSPHYCR_CLKSEL_0 | SYSCFG_OTGHSPHYCR_CLKSEL_1 | SYSCFG_OTGHSPHYCR_CLKSEL_3) /*!< 32Mhz */
/**
  * @}
  */

/** @defgroup SYSCFG_OTG_PHY_PowerDown  OTG PHY Power Down
  * @{
  */

/** @brief  OTG HS PHY Power Down config
  */
#define SYSCFG_OTG_HS_PHY_POWER_ON   0x00000000U              /*!< PHY state machine, bias and OTG PHY PLL are powered down */
#define SYSCFG_OTG_HS_PHY_POWER_DOWN SYSCFG_OTGHSPHYCR_PDCTRL /*!< PHY state machine, bias and OTG PHY PLL remain powered */
/**
  * @}
  */

/** @defgroup SYSCFG_OTG_PHY_Enable  OTG PHY Enable
  * @{
  */
#define SYSCFG_OTG_HS_PHY_UNDERRESET 0x00000000U          /*!< PHY under reset */
#define SYSCFG_OTG_HS_PHY_ENABLE     SYSCFG_OTGHSPHYCR_EN /*!< PHY enabled */
/**
  * @}
  */

/** @defgroup SYSCFG_OTG_PHYTUNER_PreemphasisCurrent  OTG PHYTUNER Preemphasis Current
  * @{
  */

/** @brief  High-speed (HS) transmitter preemphasis current control
  */
#define SYSCFG_OTG_HS_PHY_PREEMP_DISABLED 0x00000000U                                                                         /*!< HS transmitter preemphasis circuit disabled */
#define SYSCFG_OTG_HS_PHY_PREEMP_1X       SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE_0                                             /*!< HS transmitter preemphasis circuit sources 1x preemphasis current */
#define SYSCFG_OTG_HS_PHY_PREEMP_2X       SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE_1                                             /*!< HS transmitter preemphasis circuit sources 2x preemphasis current */
#define SYSCFG_OTG_HS_PHY_PREEMP_3X       (SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE_0 | SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE_1) /*!< HS transmitter preemphasis circuit sources 3x preemphasis current */
/**
  * @}
  */

/** @defgroup SYSCFG_OTG_PHYTUNER_SquelchThreshold  OTG PHYTUNER Squelch Threshold
  * @{
  */

/** @brief Squelch threshold adjustment
  */
#define SYSCFG_OTG_HS_PHY_SQUELCH_15PERCENT 0x00000000U                                                           /*!< +15% (recommended value) */
#define SYSCFG_OTG_HS_PHY_SQUELCH_0PERCENT  (SYSCFG_OTGHSPHYTUNER2_SQRXTUNE_0 | SYSCFG_OTGHSPHYTUNER2_SQRXTUNE_1) /*!< 0% (default value) */
/**
  * @}
  */

/** @defgroup SYSCFG_OTG_PHYTUNER_DisconnectThreshold  OTG PHYTUNER Disconnect Threshold
  * @{
  */

/** @brief Disconnect threshold adjustment
  */
#define SYSCFG_OTG_HS_PHY_DISCONNECT_5_9PERCENT SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE_1 /*!< +5.9% (recommended value) */
#define SYSCFG_OTG_HS_PHY_DISCONNECT_0PERCENT   SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE_0 /*!< 0% (default value) */
/**
  * @}
  */
#endif /* SYSCFG_OTGHSPHYCR_EN */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @brief  Freeze/Unfreeze Peripherals in Debug mode
  */
#if defined(DBGMCU_APB1LFZR_DBG_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()           SET_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         CLEAR_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_TIM2_STOP)
#endif /* DBGMCU_APB1LFZR_DBG_TIM2_STOP */

#if defined(DBGMCU_APB1LFZR_DBG_TIM3_STOP)
#define __HAL_DBGMCU_FREEZE_TIM3()           SET_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_TIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM3()         CLEAR_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_TIM3_STOP)
#endif /* DBGMCU_APB1LFZR_DBG_TIM3_STOP */

#if defined(DBGMCU_APB1LFZR_DBG_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG()           SET_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()         CLEAR_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_WWDG_STOP)
#endif /* DBGMCU_APB1LFZR_DBG_WWDG_STOP */

#if defined(DBGMCU_APB1LFZR_DBG_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()           SET_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         CLEAR_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_IWDG_STOP)
#endif /* DBGMCU_APB1LFZR_DBG_IWDG_STOP */

#if defined(DBGMCU_APB1LFZR_DBG_I2C1_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1()              SET_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1()            CLEAR_BIT(DBGMCU->APB1LFZR, DBGMCU_APB1LFZR_DBG_I2C1_STOP)
#endif /* DBGMCU_APB1LFZR_DBG_I2C1_STOP */

#if defined(DBGMCU_APB1HFZR_DBG_LPTIM2_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM2()            SET_BIT(DBGMCU->APB1HFZR, DBGMCU_APB1HFZR_DBG_LPTIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM2()          CLEAR_BIT(DBGMCU->APB1HFZR, DBGMCU_APB1HFZR_DBG_LPTIM2_STOP)
#endif /* DBGMCU_APB1HFZR_DBG_LPTIM2_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1()              SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM1()            CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM1_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM1_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM16_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM16_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM17_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM17()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM17_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM17_STOP */

#if defined(DBGMCU_APB7FZR_DBG_I2C3_STOP)
#define __HAL_DBGMCU_FREEZE_I2C3()              SET_BIT(DBGMCU->APB7FZR, DBGMCU_APB7FZR_DBG_I2C3_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C3()            CLEAR_BIT(DBGMCU->APB7FZR, DBGMCU_APB7FZR_DBG_I2C3_STOP)
#endif /* DBGMCU_APB7FZR_DBG_I2C3_STOP */

#if defined(DBGMCU_APB7FZR_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM1()            SET_BIT(DBGMCU->APB7FZR, DBGMCU_APB7FZR_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()          CLEAR_BIT(DBGMCU->APB7FZR, DBGMCU_APB7FZR_DBG_LPTIM1_STOP)
#endif /* DBGMCU_APB7FZR_DBG_LPTIM1_STOP */

#if defined(DBGMCU_APB7FZR_DBG_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()               SET_BIT(DBGMCU->APB7FZR, DBGMCU_APB7FZR_DBG_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()             CLEAR_BIT(DBGMCU->APB7FZR, DBGMCU_APB7FZR_DBG_RTC_STOP)
#endif /* DBGMCU_APB7FZR_DBG_RTC_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH0_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA0()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH0_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA0()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH0_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH0_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH1_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA1()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH1_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA1()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH1_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH1_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH2_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA2()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH2_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA2()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH2_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH2_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH3_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA3()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH3_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA3()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH3_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH3_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH4_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA4()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH4_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA4()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH4_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH4_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH5_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA5()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH5_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA5()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH5_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH5_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH6_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA6()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH6_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA6()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH6_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH6_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_CH7_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA7()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH7_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA7()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_CH7_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_CH7_STOP */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @brief  Floating Point Unit interrupt enable/disable macros
  * @param __INTERRUPT__: This parameter can be a value of @ref SYSCFG_FPU_Interrupts
  */
#define __HAL_SYSCFG_FPU_INTERRUPT_ENABLE(__INTERRUPT__)    do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 SET_BIT(SYSCFG->FPUIMR, (__INTERRUPT__));\
                                                               }while(0)

#define __HAL_SYSCFG_FPU_INTERRUPT_DISABLE(__INTERRUPT__)   do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 CLEAR_BIT(SYSCFG->FPUIMR, (__INTERRUPT__));\
                                                               }while(0)

/** @brief  SYSCFG Break ECC lock.
  *         Enable and lock the connection of Flash ECC error connection to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_ECC_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_ECCL)

/** @brief  SYSCFG Break Cortex-M33 Lockup lock.
  *         Enable and lock the connection of Cortex-M33 LOCKUP (Hardfault) output to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()     SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL)

/** @brief  SYSCFG Break PVD lock.
  *         Enable and lock the PVD connection to Timer1/8/15/16/17 Break input, as well as the PVDE and PLS[2:0] in
  *         the PWR_CR2 register.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_PVDL)

/** @brief  SYSCFG Break SRAM2 parity lock.
  *         Enable and lock the SRAM2 parity error signal connection to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked by system reset.
  */
#define __HAL_SYSCFG_BREAK_SRAM2PARITY_LOCK()  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPL)

/** @brief  Check SYSCFG flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref SYSCFG_FLAG_MCLR   Device memories erase status flag
  *            @arg @ref SYSCFG_FLAG_IPMEE  ICACHE and PKA SRAM erase status flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SYSCFG_GET_FLAG(__FLAG__)      (READ_BIT(SYSCFG->MESR, (__FLAG__)) == (__FLAG__))

/** @brief  Clear SYSCFG flag.
  * @param  __FLAG__ specifies the flag(s) to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref SYSCFG_FLAG_MCLR   Device memories erase status flag
  *            @arg @ref SYSCFG_FLAG_IPMEE  ICACHE and PKA SRAM erase status flag
  */
#define __HAL_SYSCFG_CLEAR_FLAG(__FLAG__)    SET_BIT(SYSCFG->MESR, (__FLAG__))

/** @brief  Fast-mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__: This parameter can be a value of :
  *     @arg @ref SYSCFG_FASTMODEPLUS_PA6 Fast-mode Plus driving capability activation on PA6
  *     @arg @ref SYSCFG_FASTMODEPLUS_PA7 Fast-mode Plus driving capability activation on PA7
  *     @arg @ref SYSCFG_FASTMODEPLUS_PA15 Fast-mode Plus driving capability activation on PA15
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB3 Fast-mode Plus driving capability activation on PB3
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__) \
  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    SET_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) \
  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    CLEAR_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_FPU_INTERRUPT(__INTERRUPT__) ((((__INTERRUPT__) & SYSCFG_IT_FPU_ALL) != 0x00U) && \
                                                (((__INTERRUPT__) & ~SYSCFG_IT_FPU_ALL) == 0x00U))

#ifdef SYSCFG_CCCSR_EN2
#define IS_SYSCFG_COMPENSATION_CELL(__CELL__) (((__CELL__) == SYSCFG_IO_CELL) || \
                                               ((__CELL__) == SYSCFG_IO2_CELL))

#define IS_SYSCFG_COMPENSATION_CELL_READY(__CELL__) (((__CELL__) == SYSCFG_IO_CELL_READY) || \
                                                     ((__CELL__) == SYSCFG_IO2_CELL_READY))
#else
#define IS_SYSCFG_COMPENSATION_CELL(__CELL__) (((__CELL__) == SYSCFG_IO_CELL))

#define IS_SYSCFG_COMPENSATION_CELL_READY(__CELL__) (((__CELL__) == SYSCFG_IO_CELL_READY))
#endif /* SYSCFG_CCCSR_EN2 */

#define IS_SYSCFG_COMPENSATION_CELL_CODE(__VALUE__) (((__VALUE__) == SYSCFG_IO_CELL_CODE) || \
                                                     ((__VALUE__) == SYSCFG_IO_REGISTER_CODE))

#define IS_SYSCFG_COMPENSATION_CELL_PMOS_VALUE(__VALUE__) (((__VALUE__) < 16U))

#define IS_SYSCFG_COMPENSATION_CELL_NMOS_VALUE(__VALUE__) (((__VALUE__) < 16U))

#define IS_SYSCFG_BREAK_CONFIG(__CONFIG__) (((__CONFIG__) == SYSCFG_BREAK_ECC)           || \
                                            ((__CONFIG__) == SYSCFG_BREAK_PVD)           || \
                                            ((__CONFIG__) == SYSCFG_BREAK_SRAM2_PARITY)  || \
                                            ((__CONFIG__) == SYSCFG_BREAK_LOCKUP))


#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_ALL) != 0x00U) && \
                                         (((__PIN__) & ~SYSCFG_FASTMODEPLUS_ALL) == 0x00U))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

#define IS_SYSCFG_ATTRIBUTES(__ATTRIBUTES__) (((__ATTRIBUTES__) == SYSCFG_SEC)  ||\
                                              ((__ATTRIBUTES__) == SYSCFG_NSEC))

#define IS_SYSCFG_ITEMS_ATTRIBUTES(__ITEM__) ((((__ITEM__) & SYSCFG_ALL) != 0x00U) && \
                                              (((__ITEM__) & ~SYSCFG_ALL) == 0x00U))

#endif /* __ARM_FEATURE_CMSE */

#if defined (SYSCFG_SECCFGR_SYSCFGSEC)
#define IS_SYSCFG_SINGLE_ITEMS_ATTRIBUTES(__ITEM__) (((__ITEM__) == (SYSCFG_CLK))    || \
                                                     ((__ITEM__) == (SYSCFG_CLASSB)) || \
                                                     ((__ITEM__) == (SYSCFG_FPU)))
#endif /* SYSCFG_SECCFGR_SYSCFGSEC */

#define IS_SYSCFG_LOCK_ITEMS(__ITEM__) ((((__ITEM__) & SYSCFG_LOCK_ALL) != 0x00U) && \
                                        (((__ITEM__) & ~SYSCFG_LOCK_ALL) == 0x00U))

#ifdef SYSCFG_OTGHSPHYCR_EN
#define IS_SYSCFG_OTGPHY_REFERENCE_CLOCK(__VALUE__) (((__VALUE__) == SYSCFG_OTG_HS_PHY_CLK_SELECT_1) || \
                                                     ((__VALUE__) == SYSCFG_OTG_HS_PHY_CLK_SELECT_2) || \
                                                     ((__VALUE__) == SYSCFG_OTG_HS_PHY_CLK_SELECT_3) || \
                                                     ((__VALUE__) == SYSCFG_OTG_HS_PHY_CLK_SELECT_4) || \
                                                     ((__VALUE__) == SYSCFG_OTG_HS_PHY_CLK_SELECT_5) || \
                                                     ((__VALUE__) == SYSCFG_OTG_HS_PHY_CLK_SELECT_6))

#define IS_SYSCFG_OTGPHY_POWERDOWN_CONFIG(__VALUE__) (((__VALUE__) == SYSCFG_OTG_HS_PHY_POWER_DOWN) || \
                                                      ((__VALUE__) == SYSCFG_OTG_HS_PHY_POWER_ON))

#define IS_SYSCFG_OTGPHY_CONFIG(__VALUE__) (((__VALUE__) == SYSCFG_OTG_HS_PHY_UNDERRESET) || \
                                            ((__VALUE__) == SYSCFG_OTG_HS_PHY_ENABLE))

#define IS_SYSCFG_OTGPHY_DISCONNECT(__VALUE__) (((__VALUE__) == SYSCFG_OTG_HS_PHY_DISCONNECT_5_9PERCENT) || \
                                                ((__VALUE__) == SYSCFG_OTG_HS_PHY_DISCONNECT_0PERCENT))

#define IS_SYSCFG_OTGPHY_SQUELCH(__VALUE__) (((__VALUE__) == SYSCFG_OTG_HS_PHY_SQUELCH_0PERCENT) || \
                                             ((__VALUE__) == SYSCFG_OTG_HS_PHY_SQUELCH_15PERCENT))

#define IS_SYSCFG_OTGPHY_PREEMPHASIS(__VALUE__) (((__VALUE__) == SYSCFG_OTG_HS_PHY_PREEMP_DISABLED) || \
                                                 ((__VALUE__) == SYSCFG_OTG_HS_PHY_PREEMP_1X)       || \
                                                 ((__VALUE__) == SYSCFG_OTG_HS_PHY_PREEMP_2X)       || \
                                                 ((__VALUE__) == SYSCFG_OTG_HS_PHY_PREEMP_3X))
#endif /* SYSCFG_OTGHSPHYCR_EN */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  */

/* SYSCFG Control functions  ****************************************************/
void HAL_SYSCFG_EnableIOAnalogSwitchBooster(void);
void HAL_SYSCFG_DisableIOAnalogSwitchBooster(void);
void HAL_SYSCFG_EnableIOAnalogSwitchVdd(void);
void HAL_SYSCFG_DisableIOAnalogSwitchVdd(void);


#ifdef SYSCFG_OTGHSPHYCR_EN
void HAL_SYSCFG_SetOTGPHYReferenceClockSelection(uint32_t RefClockSelection);
void HAL_SYSCFG_SetOTGPHYPowerDownConfig(uint32_t PowerDownConfig);
void HAL_SYSCFG_EnableOTGPHY(uint32_t OTGPHYConfig);
void HAL_SYSCFG_SetOTGPHYDisconnectThreshold(uint32_t DisconnectThreshold);
void HAL_SYSCFG_SetOTGPHYSquelchThreshold(uint32_t SquelchThreshold);
void HAL_SYSCFG_SetOTGPHYPreemphasisCurrent(uint32_t PreemphasisCurrent);
#endif /* SYSCFG_OTGHSPHYCR_EN */

void HAL_SYSCFG_EnableCompensationCell(uint32_t Selection);
void HAL_SYSCFG_DisableCompensationCell(uint32_t Selection);
uint32_t HAL_SYSCFG_GetCompensationCellReadyStatus(uint32_t Selection);
void HAL_SYSCFG_ConfigCompensationCell(uint32_t Selection, uint32_t Code, uint32_t NmosValue,
                                       uint32_t PmosValue);
HAL_StatusTypeDef HAL_SYSCFG_GetCompensationCell(uint32_t Selection, uint32_t *pCode, uint32_t *pNmosValue,
                                                 uint32_t *pPmosValue);
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group5
  * @{
  */

/* SYSCFG Lock functions ********************************************/
void HAL_SYSCFG_Lock(uint32_t Item);
HAL_StatusTypeDef HAL_SYSCFG_GetLock(uint32_t *pItem);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group6
  * @{
  */

#if defined (SYSCFG_SECCFGR_SYSCFGSEC)
/* SYSCFG Attributes functions ********************************************/
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
void HAL_SYSCFG_ConfigAttributes(uint32_t Item, uint32_t Attributes);
#endif /* __ARM_FEATURE_CMSE */
HAL_StatusTypeDef HAL_SYSCFG_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);
#endif /* SYSCFG_SECCFGR_SYSCFGSEC */

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

#endif /* __STM32WBAxx_HAL_H */
