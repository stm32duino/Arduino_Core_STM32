/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_smbus_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SMBUS HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP1xx_HAL_SMBUS_EX_H
#define STM32MP1xx_HAL_SMBUS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal_def.h"

/** @addtogroup STM32MP1xx_HAL_Driver
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
#define SMBUS_FASTMODEPLUS_I2C1           SYSCFG_PMCSETR_I2C1_FMP                           /*!< Enable Fast Mode Plus on I2C1 pins */
#define SMBUS_FASTMODEPLUS_I2C2           SYSCFG_PMCSETR_I2C2_FMP                           /*!< Enable Fast Mode Plus on I2C2 pins */
#define SMBUS_FASTMODEPLUS_I2C3           SYSCFG_PMCSETR_I2C3_FMP                           /*!< Enable Fast Mode Plus on I2C3 pins */
#define SMBUS_FASTMODEPLUS_I2C4           SYSCFG_PMCSETR_I2C4_FMP                           /*!< Enable Fast Mode Plus on I2C4 pins */
#define SMBUS_FASTMODEPLUS_I2C5           SYSCFG_PMCSETR_I2C5_FMP                           /*!< Enable Fast Mode Plus on I2C5 pins */
#define SMBUS_FASTMODEPLUS_I2C6           SYSCFG_PMCSETR_I2C6_FMP                           /*!< Enable Fast Mode Plus on I2C6 pins */
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
HAL_StatusTypeDef HAL_SMBUSEx_EnableWakeUp(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUSEx_DisableWakeUp(SMBUS_HandleTypeDef *hsmbus);
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
#define IS_SMBUS_FASTMODEPLUS(__CONFIG__) ((((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C1)) == SMBUS_FASTMODEPLUS_I2C1)  || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C2)) == SMBUS_FASTMODEPLUS_I2C2)  || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C3)) == SMBUS_FASTMODEPLUS_I2C3)  || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C4)) == SMBUS_FASTMODEPLUS_I2C4)  || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C5)) == SMBUS_FASTMODEPLUS_I2C5)  || \
                                           (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C6)) == SMBUS_FASTMODEPLUS_I2C6))

/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Functions SMBUS Extended Private Functions
  * @{
  */
/* Private functions are defined in stm32mp1xx_hal_smbus_ex.c file */
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

#endif /* STM32MP1xx_HAL_SMBUS_EX_H */
