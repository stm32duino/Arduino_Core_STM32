/**
  ******************************************************************************
  * @file    stm32f1xx_hal_pcd_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PCD HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1xx_HAL_PCD_EX_H
#define __STM32F1xx_HAL_PCD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F102x6) || defined(STM32F102xB) || \
    defined(STM32F103x6) || defined(STM32F103xB) || \
    defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup PCDEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCDEx_Exported_Functions PCDEx Exported Functions
  * @{
  */
/** @addtogroup PCDEx_Exported_Functions_Group1 Peripheral Control functions
  * @{
  */
#if defined (USB_OTG_FS)
HAL_StatusTypeDef HAL_PCDEx_SetTxFiFo(PCD_HandleTypeDef *hpcd, uint8_t fifo, uint16_t size);
HAL_StatusTypeDef HAL_PCDEx_SetRxFiFo(PCD_HandleTypeDef *hpcd, uint16_t size);
#endif /* USB_OTG_FS */

#if defined (USB)
HAL_StatusTypeDef HAL_PCDEx_PMAConfig(PCD_HandleTypeDef *hpcd,
                                     uint16_t ep_addr,
                                     uint16_t ep_kind,
                                     uint32_t pmaadress);
#endif /* USB */
/**
  * @}
  */

/** @addtogroup PCDEx_Exported_Functions_Group2 Peripheral State functions
  * @{
  */
void HAL_PCDEx_SetConnectionState(PCD_HandleTypeDef *hpcd, uint8_t state);
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
#endif /* STM32F102x6 || STM32F102xB || */
       /* STM32F103x6 || STM32F103xB || */
       /* STM32F103xE || STM32F103xG || */
       /* STM32F105xC || STM32F107xC    */

#ifdef __cplusplus
}
#endif


#endif /* __STM32F1xx_HAL_PCD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
