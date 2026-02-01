/**
  ******************************************************************************
  * @file    stm32wb0x_hal_smbus_ex.c
  * @author  MCD Application Team
  * @brief   SMBUS Extended HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of SMBUS Extended peripheral:
  *           + Extended features functions
  *           + FastModePlus Functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
               ##### SMBUS peripheral Extended features  #####
  ==============================================================================

  [..] Comparing to other previous devices, the SMBUS interface for STM32WB0x
       devices contains the following additional features

       (+) Disable or enable Fast Mode Plus

                     ##### How to use this driver #####
  ==============================================================================
    (#) Configure the enable or disable of fast mode plus driving capability using the functions :
          (++) HAL_SMBUSEx_EnableFastModePlus()
          (++) HAL_SMBUSEx_DisableFastModePlus()
  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @defgroup SMBUSEx SMBUSEx
  * @brief SMBUS Extended HAL module driver
  * @{
  */

#ifdef HAL_SMBUS_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SMBUSEx_Exported_Functions SMBUS Extended Exported Functions
  * @{
  */

/** @defgroup SMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
  * @brief    Fast Mode Plus Functions
  *
@verbatim
 ===============================================================================
                      ##### Fast Mode Plus Functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
      (+) Configure Fast Mode Plus

@endverbatim
  * @{
  */

/**
  * @brief Enable the SMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref SMBUSEx_FastModePlus values
  * @retval None
  */
void HAL_SMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_SMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable fast mode plus driving capability for selected pin */
  SET_BIT(SYSCFG->I2C_FMP_CTRL, (uint32_t)ConfigFastModePlus);
}

/**
  * @brief Disable the SMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref SMBUSEx_FastModePlus values
  * @retval None
  */
void HAL_SMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_SMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Disable fast mode plus driving capability for selected pin */
  CLEAR_BIT(SYSCFG->I2C_FMP_CTRL, (uint32_t)ConfigFastModePlus);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_SMBUS_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
