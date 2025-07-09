/**
  ******************************************************************************
  * @file    stm32wb0x_hal.h
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
#ifndef STM32WB0x_HAL_H
#define STM32WB0x_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_conf.h"
#include "stm32wb0x_ll_system.h"

/** @addtogroup STM32WB0x_HAL_Driver
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
#define __STM32WB0x_HAL_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32WB0x_HAL_VERSION_SUB1   (0x03U) /*!< [23:16] sub1 version */
#define __STM32WB0x_HAL_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32WB0x_HAL_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32WB0x_HAL_VERSION         ((__STM32WB0x_HAL_VERSION_MAIN << 24U)\
                                         |(__STM32WB0x_HAL_VERSION_SUB1 << 16U)\
                                         |(__STM32WB0x_HAL_VERSION_SUB2 << 8U )\
                                         |(__STM32WB0x_HAL_VERSION_RC))
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
#if defined (STM32WB09) || defined (STM32WB05)
#define SYSCFG_FASTMODEPLUS_PB6         SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP  /*!< Enable Fast-mode Plus on PB6       */
#define SYSCFG_FASTMODEPLUS_PB7         SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP  /*!< Enable Fast-mode Plus on PB7       */
#endif
#endif /* I2C1 */
#if defined(I2C2)
#define SYSCFG_FASTMODEPLUS_PB6         SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP  /*!< Enable Fast Mode Plus on PB6       */
#define SYSCFG_FASTMODEPLUS_PB7         SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP  /*!< Enable Fast Mode Plus on PB7       */
#endif /* I2C2 */

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
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7)  == SYSCFG_FASTMODEPLUS_PB7))

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

#endif /* STM32WB0x_HAL_H */
