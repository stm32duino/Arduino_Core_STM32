/**
  ******************************************************************************
  * @file    stm32l0xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extension module.
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
#ifndef __STM32L0xx_HAL_PWR_EX_H
#define __STM32L0xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @{
  */

/** @defgroup PWREx_Exported_Macros PWREx Exported Macros
 * @{
 */

/** @brief  Macros to enable the Deep-sleep mode with Flash memory kept off.
  * @note   When entering low power mode (stop or standby only), if DS_EE_KOFF and RUN_PD of
  *         FLASH_ACR register are both set , the Flash memory will not be woken up
  *         when exiting from deep-sleep mode.
  */
#define __HAL_PWR_FLASHWAKEUP_ENABLE()      CLEAR_BIT(PWR->CR, PWR_CR_DSEEKOFF)

/** @brief  Macros to disable the Deep-sleep mode with Flash memory kept off.
  * @note   When entering low power mode (stop or standby only), if DS_EE_KOFF and RUN_PD of
  *         FLASH_ACR register are both set , the Flash memory will not be woken up
  *         when exiting from deep-sleep mode.
  */
#define __HAL_PWR_FLASHWAKEUP_DISABLE()     SET_BIT(PWR->CR, PWR_CR_DSEEKOFF)
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
 * @{
 */
uint32_t HAL_PWREx_GetVoltageRange(void);
void HAL_PWREx_EnableFastWakeUp(void);
void HAL_PWREx_DisableFastWakeUp(void);
void HAL_PWREx_EnableUltraLowPower(void);
void HAL_PWREx_DisableUltraLowPower(void);
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
/**
  * @}
  */

/* Define the private group ***********************************/
/**************************************************************/
/** @defgroup PWREx_Private PWREx Private
  * @{
  */
/**
  * @}
  */
/**************************************************************/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_PWR_EX_H */
