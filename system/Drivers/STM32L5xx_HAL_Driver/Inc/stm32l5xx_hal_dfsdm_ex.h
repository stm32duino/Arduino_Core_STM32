/**
  ******************************************************************************
  * @file    stm32l5xx_hal_dfsdm_ex.h
  * @author  MCD Application Team
  * @brief   Header file of DFSDM HAL extended module.
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
#ifndef STM32L5xx_HAL_DFSDM_EX_H
#define STM32L5xx_HAL_DFSDM_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal_def.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @addtogroup DFSDMEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup DFSDMEx_Exported_Functions DFSDM Extended Exported Functions
  * @{
  */

/** @addtogroup DFSDMEx_Exported_Functions_Group1_Channel Extended channel operation functions
  * @{
  */

HAL_StatusTypeDef HAL_DFDSMEx_ChannelSetPulsesSkipping(DFSDM_Channel_HandleTypeDef *hdfsdm_channel, uint32_t PulsesValue);
HAL_StatusTypeDef HAL_DFDSMEx_ChannelGetPulsesSkipping(const DFSDM_Channel_HandleTypeDef *hdfsdm_channel, uint32_t *PulsesValue);

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @addtogroup DFSDMEx_Private_Macros DFSDM Extended Private Macros
  * @{
  */

#define IS_DFSDM_CHANNEL_SKIPPING_VALUE(VALUE)   ((VALUE) < 64U)

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

#endif /* STM32L5xx_HAL_DFSDM_EX_H */
