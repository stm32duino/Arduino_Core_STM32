/**
  ******************************************************************************
  * @file    stm32wl3x_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
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
#ifndef STM32WL3x_HAL_FLASH_EX_H
#define STM32WL3x_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/* Extended Program operation functions  *************************************/
/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OTPWrite(uint32_t Address, uint32_t Data);
HAL_StatusTypeDef HAL_FLASHEx_OTPWrite_IT(uint32_t Address, uint32_t Data);
HAL_StatusTypeDef HAL_FLASHEx_PageProtection(FLASH_PageProtectionTypeDef *pageProtectionStruct);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
void              FLASH_PageErase(uint32_t Page);
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

#endif /* STM32WL3x_HAL_FLASH_EX_H */
