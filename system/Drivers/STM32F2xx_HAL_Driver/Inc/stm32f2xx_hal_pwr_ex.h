/**
  ******************************************************************************
  * @file    stm32f2xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extension module.
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
#ifndef __STM32F2xx_HAL_PWR_EX_H
#define __STM32F2xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal_def.h"

/** @addtogroup STM32F2xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Constants PWR Exported Constants
  * @{
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWREx_Exported_Constants PWR Exported Constants
  *  @{
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWREx_Exported_Functions PWR Exported Functions
  *  @{
  */
 
/** @addtogroup PWREx_Exported_Functions_Group1
  * @{
  */
void HAL_PWREx_EnableFlashPowerDown(void);
void HAL_PWREx_DisableFlashPowerDown(void); 
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void);
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void); 
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup PWREx_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWREx_register_alias_address PWR Register alias address
  * @{
  */
/* ------------- PWR registers bit address in the alias region ---------------*/
/* --- CR Register ---*/
/* Alias word address of FPDS bit */
#define FPDS_BIT_NUMBER          POSITION_VAL(PWR_CR_FPDS)
#define CR_FPDS_BB               (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (FPDS_BIT_NUMBER * 4U))

 /**
  * @}
  */

/** @defgroup PWREx_CSR_register_alias PWR CSR Register alias address
  * @{
  */  
/* --- CSR Register ---*/
/* Alias word address of BRE bit */
#define BRE_BIT_NUMBER   POSITION_VAL(PWR_CSR_BRE)
#define CSR_BRE_BB      (uint32_t)(PERIPH_BB_BASE + (PWR_CSR_OFFSET_BB * 32U) + (BRE_BIT_NUMBER * 4U))    
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup PWREx_Private_Macros PWR Private Macros
  * @{
  */

/** @defgroup PWREx_IS_PWR_Definitions PWR Private macros to check input parameters
  * @{
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

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif


#endif /* __STM32F2xx_HAL_PWR_EX_H */
