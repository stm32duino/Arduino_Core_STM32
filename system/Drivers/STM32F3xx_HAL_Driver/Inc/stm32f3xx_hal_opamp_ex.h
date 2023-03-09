/**
  ******************************************************************************
  * @file    stm32f3xx_hal_opamp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP HAL Extended module.
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
#ifndef STM32F3xx_HAL_OPAMP_EX_H
#define STM32F3xx_HAL_OPAMP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (OPAMP1) || defined (OPAMP2) || defined (OPAMP3) || defined (OPAMP4)

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMPEx OPAMPEx
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMPEx_Exported_Functions OPAMP Extended Exported Functions
  * @{
  */

/** @addtogroup OPAMPEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @{
  */

/* I/O operation functions  *****************************************************/

#if defined(STM32F302xE) || \
    defined(STM32F302xC)

HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2);

#endif /* STM32F302xE || */
       /* STM32F302xC    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2, OPAMP_HandleTypeDef *hopamp3, OPAMP_HandleTypeDef *hopamp4);
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

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

#endif /* OPAMP1 || OPAMP2 || OPAMP3 || OPAMP4 */

#ifdef __cplusplus
}
#endif

#endif /* STM32F3xx_HAL_OPAMP_EX_H */

