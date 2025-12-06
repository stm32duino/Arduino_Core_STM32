/**
  ******************************************************************************
  * @file    stm32wl3x_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef STM32WL3x_HAL_H
#define STM32WL3x_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_conf.h"
#include "stm32wl3x_ll_system.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */
/** @defgroup HAL_Private_Constants HAL Private Constants
  * @{
  */
/**
  * @brief HAL Driver version number
   */
#define __STM32WL3X_HAL_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32WL3X_HAL_VERSION_SUB1   (0x03U) /*!< [23:16] sub1 version */
#define __STM32WL3X_HAL_VERSION_SUB2   (0x01U) /*!< [15:8]  sub2 version */
#define __STM32WL3X_HAL_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32WL3X_HAL_VERSION         ((__STM32WL3X_HAL_VERSION_MAIN << 24U)\
                                         |(__STM32WL3X_HAL_VERSION_SUB1 << 16U)\
                                         |(__STM32WL3X_HAL_VERSION_SUB2 << 8U )\
                                         |(__STM32WL3X_HAL_VERSION_RC))

/**
  * @}
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


/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_BootMode BOOT Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH           LL_SYSCFG_REMAP_FLASH           /*!< Main Flash memory mapped at 0x00000000   */
#define SYSCFG_BOOT_SRAM                LL_SYSCFG_REMAP_SRAM            /*!< SRAM1 mapped at 0x00000000               */

/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */
#if defined(I2C1)
#define SYSCFG_FASTMODEPLUS_PA0         SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP  /*!< Enable Fast-mode Plus on PA0       */
#define SYSCFG_FASTMODEPLUS_PA1         SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP  /*!< Enable Fast Mode Plus on PA1       */
#define SYSCFG_FASTMODEPLUS_PB6         SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP  /*!< Enable Fast-mode Plus on PB6       */
#define SYSCFG_FASTMODEPLUS_PB7         SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP  /*!< Enable Fast Mode Plus on PB7       */
#define SYSCFG_FASTMODEPLUS_PB10         SYSCFG_I2C_FMP_CTRL_I2C1_PB10_FMP  /*!< Enable Fast Mode Plus on PB10       */
#define SYSCFG_FASTMODEPLUS_PB11         SYSCFG_I2C_FMP_CTRL_I2C1_PB11_FMP  /*!< Enable Fast Mode Plus on PB11       */
#endif
#if defined(I2C2)
#define SYSCFG_FASTMODEPLUS_PA6         SYSCFG_I2C_FMP_CTRL_I2C2_PA6_FMP  /*!< Enable Fast Mode Plus on PA6       */
#define SYSCFG_FASTMODEPLUS_PA7         SYSCFG_I2C_FMP_CTRL_I2C2_PA7_FMP  /*!< Enable Fast Mode Plus on PA7       */
#define SYSCFG_FASTMODEPLUS_PA13        SYSCFG_I2C_FMP_CTRL_I2C2_PA13_FMP  /*!< Enable Fast Mode Plus on PA13       */
#define SYSCFG_FASTMODEPLUS_PA14         SYSCFG_I2C_FMP_CTRL_I2C2_PA14_FMP  /*!< Enable Fast Mode Plus on PA14       */
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @defgroup DBG_Exported_Macros DBG Exported Macros
  * @{
  */

/** @brief  Freeze and Unfreeze Peripherals in Debug mode
  */

#if defined(LL_DBGMCU_APB0_GRP1_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()           LL_DBGMCU_APB0_GRP1_FreezePeriph(LL_DBGMCU_APB0_GRP1_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         LL_DBGMCU_APB0_GRP1_UnFreezePeriph(LL_DBGMCU_APB0_GRP1_TIM2_STOP)
#endif

#if defined(LL_DBGMCU_APB0_GRP1_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()           LL_DBGMCU_APB0_GRP1_FreezePeriph(LL_DBGMCU_APB0_GRP1_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()         LL_DBGMCU_APB0_GRP1_UnFreezePeriph(LL_DBGMCU_APB0_GRP1_TIM16_STOP)
#endif

#if defined(LL_DBGMCU_APB0_GRP1_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()            LL_DBGMCU_APB0_GRP1_FreezePeriph(LL_DBGMCU_APB0_GRP1_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()          LL_DBGMCU_APB0_GRP1_UnFreezePeriph(LL_DBGMCU_APB0_GRP1_RTC_STOP)
#endif

#if defined(LL_DBGMCU_APB0_GRP1_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()           LL_DBGMCU_APB0_GRP1_FreezePeriph(LL_DBGMCU_APB0_GRP1_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         LL_DBGMCU_APB0_GRP1_UnFreezePeriph(LL_DBGMCU_APB0_GRP1_IWDG_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_I2C1_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1()           LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1()         LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_I2C1_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_I2C2_STOP)
#define __HAL_DBGMCU_FREEZE_I2C2()          LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_I2C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C2()        LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_I2C2_STOP)
#endif

/** @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()        LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_FLASH)

/** @brief  Embedded SRAM mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()         LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_SRAM)


/**
  * @brief  Return the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned value can be one
  *         of the following values:
  *           @arg @ref SYSCFG_BOOT_MAINFLASH
  *           @arg @ref SYSCFG_BOOT_SRAM
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()            LL_SYSCFG_GetRemapMemory()


/** @brief  Fast mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__ This parameter can be a value of @ref SYSCFG_FastModePlus_GPIO
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__)  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__))); \
                                                                 LL_SYSCFG_EnableFastModePlus(__FASTMODEPLUS__);           \
                                                               }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__))); \
                                                                 LL_SYSCFG_DisableFastModePlus(__FASTMODEPLUS__);          \
                                                               }while(0)

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */

/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_FASTMODEPLUS(__PIN__)                 ((((__PIN__) & SYSCFG_FASTMODEPLUS_PA0)  == SYSCFG_FASTMODEPLUS_PA0)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA1)  == SYSCFG_FASTMODEPLUS_PA1)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB6)  == SYSCFG_FASTMODEPLUS_PB6)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7)  == SYSCFG_FASTMODEPLUS_PB7) || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB10)  == SYSCFG_FASTMODEPLUS_PB10)|| \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB11)  == SYSCFG_FASTMODEPLUS_PB11)|| \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA6)  == SYSCFG_FASTMODEPLUS_PA6) || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA7)  == SYSCFG_FASTMODEPLUS_PA7) || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA13)  == SYSCFG_FASTMODEPLUS_PA13) || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA14)  == SYSCFG_FASTMODEPLUS_PA14))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 HAL Initialization and Configuration functions
  * @{
  */

/* Initialization and Configuration functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions
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
uint32_t HAL_GetVERID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetJTAGID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group3 DBGMCU Control functions
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
/**
  * @}
  */

/* Exported variables ---------------------------------------------------------*/
/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group4 SYSCFG configuration functions
  * @{
  */

/* SYSCFG Control functions  ****************************************************/

void HAL_SYSCFG_EnableIOAnalogSwitchControl_PB14(void);
void HAL_SYSCFG_DisableIOAnalogSwitchControl_PB14(void);

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

#endif /* STM32WL3x_HAL_H */
