/**
  ******************************************************************************
  * @file    stm32l1xx_hal_flash_ramfunc.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH RAMFUNC driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_FLASH_RAMFUNC_H
#define __STM32L1xx_FLASH_RAMFUNC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH_RAMFUNC
  * @{
  */

/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/

/** @addtogroup FLASH_RAMFUNC_Exported_Functions
  * @{
  */

/*
  * @brief  FLASH memory functions that should be executed from internal SRAM.
  *         These functions are defined inside the "stm32l1xx_hal_flash_ramfunc.c"
  *         file.
  */

/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group1
  * @{
  */

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_EnableRunPowerDown(void);
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_DisableRunPowerDown(void);

/**
  * @}
  */

/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group2
  * @{
  */

#if defined(FLASH_PECR_PARALLBANK)

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_EraseParallelPage(uint32_t Page_Address1, uint32_t Page_Address2);
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_ProgramParallelHalfPage(uint32_t Address1, uint32_t* pBuffer1, uint32_t Address2, uint32_t* pBuffer2);

#endif /* FLASH_PECR_PARALLBANK */

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_HalfPageProgram(uint32_t Address, uint32_t* pBuffer);

/**
  * @}
  */

/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group3
  * @{
  */
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_GetError(uint32_t *Error);
/**
  * @}
  */

/** @addtogroup FLASH_RAMFUNC_Exported_Functions_Group4
  * @{
  */

__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_EraseDoubleWord(uint32_t Address);
__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_ProgramDoubleWord(uint32_t Address, uint64_t Data);

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

#endif /* __STM32L1xx_FLASH_RAMFUNC_H */

