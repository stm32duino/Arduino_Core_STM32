/**
  ******************************************************************************
  * @file    stm32l1xx_hal_cryp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of CRYPEx HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_HAL_CRYP_EX_H
#define __STM32L1xx_HAL_CRYP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32L162xC) || defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L162xE) || defined(STM32L162xDX)

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup CRYPEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup CRYPEx_Exported_Functions
  * @{
  */

/** @addtogroup CRYPEx_Exported_Functions_Group1
  * @{
  */

/* CallBack functions  ********************************************************/
void HAL_CRYPEx_ComputationCpltCallback(CRYP_HandleTypeDef *hcryp);

/**
  * @}
  */

/**
  * @}
  */

#endif /* STM32L162xC || STM32L162xCA || STM32L162xD || STM32L162xE || STM32L162xDX*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_HAL_CRYP_EX_H */
