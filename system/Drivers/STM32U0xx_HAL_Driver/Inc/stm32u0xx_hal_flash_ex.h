/**
  ******************************************************************************
  * @file    stm32u0xx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U0xx_HAL_FLASH_EX_H
#define STM32U0xx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal_def.h"

/** @addtogroup STM32U0xx_HAL_Driver
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
/** @defgroup FLASHEx_Empty_Check FLASHEx Empty Check
  * @{
  */
#define FLASH_NOT_EMPTY                0x00000000U          /*!< 1st location in Flash is programmed */
#define FLASH_EMPTY                    FLASH_ACR_EMPTY      /*!< 1st location in Flash is empty */
/**
  * @}
  */

/** @defgroup FLASHEx_HDPEXT_Access FLASHEx HDPEXT access
  * @{
  */
#define FLASH_HDPEXT_ACCESS_GRANTED        (0xA3UL << FLASH_HDPCR_HDP1EXT_ACCDIS_Pos)             /*!< Access to HDP extension area granted */
#define FLASH_HDPEXT_ACCESS_DENIED         (0x5CUL << FLASH_HDPCR_HDP1EXT_ACCDIS_Pos)             /*!< Access to HDP extension area denied but HDP_EXT size increment allowed at any time */
#define FLASH_HDPEXT_ACCESS_LOCKED         (0x3AUL << FLASH_HDPCR_HDP1EXT_ACCDIS_Pos)             /*!< Access to HDP extension area denied and HDP_EXT size update not possible */
/**
  * @}
  */

/**
  * @}
  */
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
void              HAL_FLASHEx_EnableDebugger(void);
void              HAL_FLASHEx_DisableDebugger(void);
uint32_t          HAL_FLASHEx_FlashEmptyCheck(void);
void              HAL_FLASHEx_ForceFlashEmpty(uint32_t FlashEmpty);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_EnableHDPProtection(uint32_t Banks);
uint32_t          HAL_FLASHEx_IsEnabledHDPProtection(void);
void              HAL_FLASHEx_ConfigHDPExtension(const FLASH_HDPExtensionTypeDef *pHDPExtension);
void              HAL_FLASHEx_GetHDPExtensionConfig(FLASH_HDPExtensionTypeDef *pHDPExtension);
void              HAL_FLASH_OB_GetOEMKeyCRC(uint32_t RDPKeyType, uint32_t *OEMKeyCRC);
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
#define IS_FLASH_EMPTY_CHECK(__VALUE__)     (((__VALUE__) == FLASH_EMPTY) || ((__VALUE__) == FLASH_NOT_EMPTY))
void              FLASH_PageErase(uint32_t Page);
void              FLASH_FlushCaches(void);
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

#endif /* STM32U0xx_HAL_FLASH_EX_H */
