/**
  ******************************************************************************
  * @file    stm32l0xx_hal_comp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of COMP HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_COMP_EX_H
#define __STM32L0xx_HAL_COMP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined(STM32L010xB) && !defined (STM32L010x8) && !defined (STM32L010x6) && !defined (STM32L010x4)
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup COMPEx COMPEx
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMPEx_Exported_Functions COMPEx Exported Functions
  * @{
  */

/** @defgroup COMPEx_Exported_Functions_Group1 Extended COMP VREFINT setup functions
 * @{
 */
/* COMP specific functions to manage VREFINT *************************************/
void HAL_COMPEx_EnableVREFINT(void);
void HAL_COMPEx_DisableVREFINT(void);

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
#endif /* #if !defined(STM32L010xB) && !defined (STM32L010x8) && !defined (STM32L010x6) && !defined (STM32L010x4) */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_COMP_EX_H */


