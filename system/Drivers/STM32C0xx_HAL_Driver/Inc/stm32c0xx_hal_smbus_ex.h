/**
  ******************************************************************************
  * @file    stm32c0xx_hal_smbus_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SMBUS HAL Extended module.
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
#ifndef STM32C0xx_HAL_SMBUS_EX_H
#define STM32C0xx_HAL_SMBUS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal_def.h"

/** @addtogroup STM32C0xx_HAL_Driver
  * @{
  */

/** @addtogroup SMBUSEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SMBUSEx_Exported_Constants SMBUS Extended Exported Constants
  * @{
  */

/** @defgroup SMBUSEx_FastModePlus SMBUS Extended Fast Mode Plus
  * @{
  */
#define SMBUS_FMP_NOT_SUPPORTED           0xAAAA0000U                                     /*!< Fast Mode Plus not supported       */
#define SMBUS_FASTMODEPLUS_PA9            SYSCFG_CFGR1_I2C_PA9_FMP                        /*!< Enable Fast Mode Plus on PA9       */
#define SMBUS_FASTMODEPLUS_PA10           SYSCFG_CFGR1_I2C_PA10_FMP                       /*!< Enable Fast Mode Plus on PA10      */
#define SMBUS_FASTMODEPLUS_PB6            SYSCFG_CFGR1_I2C_PB6_FMP                        /*!< Enable Fast Mode Plus on PB6       */
#define SMBUS_FASTMODEPLUS_PB7            SYSCFG_CFGR1_I2C_PB7_FMP                        /*!< Enable Fast Mode Plus on PB7       */
#if defined(SYSCFG_CFGR1_I2C_PB8_FMP)
#define SMBUS_FASTMODEPLUS_PB8            SYSCFG_CFGR1_I2C_PB8_FMP                        /*!< Enable Fast Mode Plus on PB8       */
#define SMBUS_FASTMODEPLUS_PB9            SYSCFG_CFGR1_I2C_PB9_FMP                        /*!< Enable Fast Mode Plus on PB9       */
#else
#define SMBUS_FASTMODEPLUS_PB8            (uint32_t)(0x00000010U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus PB8 not supported   */
#define SMBUS_FASTMODEPLUS_PB9            (uint32_t)(0x00000012U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus PB9 not supported   */
#endif /* SYSCFG_CFGR1_I2C_PB8_FMP */
#define SMBUS_FASTMODEPLUS_I2C1           SYSCFG_CFGR1_I2C1_FMP                           /*!< Enable Fast Mode Plus on I2C1 pins */
#if defined(SYSCFG_CFGR1_I2C2_FMP)
#define SMBUS_FASTMODEPLUS_I2C2           SYSCFG_CFGR1_I2C2_FMP                           /*!< Enable Fast Mode Plus on I2C2 pins */
#else
#define SMBUS_FASTMODEPLUS_I2C2           (uint32_t)(0x00000200U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus I2C2 not supported  */
#endif /* SYSCFG_CFGR1_I2C2_FMP */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SMBUSEx_Exported_Macros SMBUS Extended Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SMBUSEx_Exported_Functions SMBUS Extended Exported Functions
  * @{
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group2 WakeUp Mode Functions
  * @{
  */
/* Peripheral Control functions  ************************************************/
#if defined(I2C_CR1_WUPEN)
HAL_StatusTypeDef HAL_SMBUSEx_EnableWakeUp(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUSEx_DisableWakeUp(SMBUS_HandleTypeDef *hsmbus);
#endif /* I2C_CR1_WUPEN */
/**
  * @}
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
  * @{
  */
void HAL_SMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus);
void HAL_SMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus);
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Constants SMBUS Extended Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Macro SMBUS Extended Private Macros
  * @{
  */
#define IS_SMBUS_FASTMODEPLUS(__CONFIG__) ((((__CONFIG__) & (SMBUS_FASTMODEPLUS_PA9))  == SMBUS_FASTMODEPLUS_PA9)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PA10)) == SMBUS_FASTMODEPLUS_PA10)  || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB6))  == SMBUS_FASTMODEPLUS_PB6)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB7))  == SMBUS_FASTMODEPLUS_PB7)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB8))  == SMBUS_FASTMODEPLUS_PB8)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB9))  == SMBUS_FASTMODEPLUS_PB9)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C1)) == SMBUS_FASTMODEPLUS_I2C1))
/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Functions SMBUS Extended Private Functions
  * @{
  */
/* Private functions are defined in stm32c0xx_hal_smbus_ex.c file */
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

#endif /* STM32C0xx_HAL_SMBUS_EX_H */
