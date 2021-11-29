/**
  ******************************************************************************
  * @file    stm32mp1xx_ll_delayblock.h
  * @author  MCD Application Team
  * @brief   Header file of Delay Block module.
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
#ifndef __STM32MP1xx_LL_DLYB_H
#define __STM32MP1xx_LL_DLYB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal_def.h"

/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */

/** @addtogroup DELAYBLOCK_LL
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup DELAYBLOCK_LL_Exported_Types DELAYBLOCK_LL Exported Types
  * @{
  */
  

/**
  * @}
  */
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup DLYB_Exported_Constants Delay Block Exported Constants
  * @{
  */


#define DLYB_MAX_UNIT   ((uint32_t)0x00000080U) /*!< Max UNIT value (128)  */

/** @defgroup DLYB_Instance DLYB Instance
  * @{
  */
#define IS_DLYB_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == DLYB_SDMMC1) || \
                                         ((INSTANCE) == DLYB_SDMMC2) || \
                                         ((INSTANCE) == DLYB_QUADSPI))
/**
  * @}
  */

/**
  * @}
  */ 
 
/* Peripheral Control functions  ************************************************/
/** @addtogroup HAL_DELAYBLOCK_LL_Group3 Delay Block functions
  * @{
  */
HAL_StatusTypeDef DelayBlock_Enable(DLYB_TypeDef *dlyb);
HAL_StatusTypeDef DelayBlock_Disable(DLYB_TypeDef *dlyb);

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

#endif /* __STM32MP1xx_LL_DLYB_H */
