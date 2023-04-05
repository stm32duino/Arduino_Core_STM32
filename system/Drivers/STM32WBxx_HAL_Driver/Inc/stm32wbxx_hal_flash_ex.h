/**
  ******************************************************************************
  * @file    stm32wbxx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
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
#ifndef STM32WBxx_HAL_FLASH_EX_H
#define STM32WBxx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal_def.h"

/** @addtogroup STM32WBxx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Constants FLASH Exported Constants
  * @{
  */
/** @defgroup FLASHEx_EMPTY_CHECK FLASHEx Empty Check
  * @{
  */
#define FLASH_PROG_NOT_EMPTY            0x00000000U     /*!< 1st location in Flash is programmed */
#define FLASH_PROG_EMPTY                FLASH_ACR_EMPTY /*!< 1st location in Flash is empty      */
/**
  * @}
  */

/** @defgroup FLASHEx_ECC_CPUID FLASHEx ECC CPU Identification
  * @{
  */
#define FLASH_ECC_CPUID_1    0x00000000U            /*!< Bus-ID of the CPU1 access causing the ECC failure. */
#define FLASH_ECC_CPUID_2    FLASH_ECCR_CPUID_0     /*!< Bus-ID of the CPU2 access causing the ECC failure. */

/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASHEx_ECC FLASH ECC Macros
  *  @brief macros to get Error Code Correction information
  * @{
  */

/**
  * @brief Get the Bus-ID of the CPU access causing the ECC failure
  * @retval CPUID
  */
#define __HAL_FLASH_ECC_CPUID()   READ_BIT(FLASH->ECCR, FLASH_ECCR_CPUID)

/**
  * @}
  */

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
uint32_t          HAL_FLASHEx_FlashEmptyCheck(void);
void              HAL_FLASHEx_ForceFlashEmpty(uint32_t FlashEmpty);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_SuspendOperation(void);
void              HAL_FLASHEx_AllowOperation(void);
uint32_t          HAL_FLASHEx_IsOperationSuspended(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Macros FLASHEx Private Macros
  *  @{
  */
#define IS_FLASH_EMPTY_CHECK(__VALUE__)     (((__VALUE__) == FLASH_PROG_EMPTY) || ((__VALUE__) == FLASH_PROG_NOT_EMPTY))
/**
  * @}
  */

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

#endif /* STM32WBxx_HAL_FLASH_EX_H */
