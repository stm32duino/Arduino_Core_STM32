/**
  ******************************************************************************
  * @file    stm32f0xx_hal_cortex.h
  * @author  MCD Application Team
  * @brief   Header file of CORTEX HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_CORTEX_H
#define __STM32F0xx_HAL_CORTEX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX CORTEX
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */
  
/** @defgroup CORTEX_SysTick_clock_source CORTEX SysTick clock source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8    (0x00000000U)
#define SYSTICK_CLKSOURCE_HCLK         (0x00000004U)

/**
  * @}
  */

/**
  * @}
  */
  
/* Exported Macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */
/** @addtogroup CORTEX_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions
 * @{
 */
/* Initialization and de-initialization functions *******************************/
void HAL_NVIC_SetPriority(IRQn_Type IRQn,uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   Cortex control functions
 * @{
 */
 
/* Peripheral Control functions *************************************************/
uint32_t HAL_NVIC_GetPriority(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Private types -------------------------------------------------------------*/ 
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x4)

#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= 0x00)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                      ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))
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

#endif /* __STM32F0xx_HAL_CORTEX_H */
 


