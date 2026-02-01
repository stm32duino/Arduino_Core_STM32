/**
  ******************************************************************************
  * @file    stm32wb0x_hal_smbus_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SMBUS HAL Extended module.
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
#ifndef STM32WB0x_HAL_SMBUS_EX_H
#define STM32WB0x_HAL_SMBUS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_def.h"

/** @addtogroup STM32WB0x_HAL_Driver
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
#define SMBUS_FASTMODEPLUS_PA0            SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP                        /*!< Enable Fast Mode Plus on PA0       */
#define SMBUS_FASTMODEPLUS_PA1            SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP                        /*!< Enable Fast Mode Plus on PA1       */
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP)
#define SMBUS_FASTMODEPLUS_PB6            SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP                        /*!< Enable Fast Mode Plus on PB6       */
#define SMBUS_FASTMODEPLUS_PB7            SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP
#else
#define SMBUS_FASTMODEPLUS_PB6            SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP                        /*!< Enable Fast Mode Plus on PB6       */
#define SMBUS_FASTMODEPLUS_PB7            SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP                        /*!< Enable Fast Mode Plus on PB7       */
#endif /* SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP */
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
#define IS_SMBUS_FASTMODEPLUS(__CONFIG__) ((((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB6))  == SMBUS_FASTMODEPLUS_PB6)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB7))  == SMBUS_FASTMODEPLUS_PB7)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PA0))  == SMBUS_FASTMODEPLUS_PA0)   || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PA1))  == SMBUS_FASTMODEPLUS_PA1))
/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Functions SMBUS Extended Private Functions
  * @{
  */
/* Private functions are defined in stm32wb0x_hal_smbus_ex.c file */
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

#endif /* STM32WB0x_HAL_SMBUS_EX_H */
