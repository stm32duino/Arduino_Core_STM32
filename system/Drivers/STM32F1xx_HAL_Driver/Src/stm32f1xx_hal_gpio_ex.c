/**
  ******************************************************************************
  * @file    stm32f1xx_hal_gpio_ex.c
  * @author  MCD Application Team
  * @brief   GPIO Extension HAL module driver.
  *         This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO) extension peripheral.
  *           + Extended features functions
  *
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
  @verbatim
  ==============================================================================
                    ##### GPIO Peripheral extension features #####
  ==============================================================================
  [..] GPIO module on STM32F1 family, manage also the AFIO register:
       (+) Possibility to use the EVENTOUT Cortex feature

                     ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to use EVENTOUT Cortex feature
    (#) Configure EVENTOUT Cortex feature using the function HAL_GPIOEx_ConfigEventout()
    (#) Activate EVENTOUT Cortex feature using the HAL_GPIOEx_EnableEventout()
    (#) Deactivate EVENTOUT Cortex feature using the HAL_GPIOEx_DisableEventout()

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO HAL module driver
  * @{
  */

#ifdef HAL_GPIO_MODULE_ENABLED

/** @defgroup GPIOEx_Exported_Functions GPIOEx Exported Functions
  * @{
  */

/** @defgroup GPIOEx_Exported_Functions_Group1 Extended features functions
 *  @brief    Extended features functions
 *
@verbatim
  ==============================================================================
                 ##### Extended features functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
    (+) Configure EVENTOUT Cortex feature using the function HAL_GPIOEx_ConfigEventout()
    (+) Activate EVENTOUT Cortex feature using the HAL_GPIOEx_EnableEventout()
    (+) Deactivate EVENTOUT Cortex feature using the HAL_GPIOEx_DisableEventout()

@endverbatim
  * @{
  */

/**
  * @brief  Configures the port and pin on which the EVENTOUT Cortex signal will be connected.
  * @param  GPIO_PortSource Select the port used to output the Cortex EVENTOUT signal.
  *   This parameter can be a value of @ref GPIOEx_EVENTOUT_PORT.
  * @param  GPIO_PinSource Select the pin used to output the Cortex EVENTOUT signal.
  *   This parameter can be a value of @ref GPIOEx_EVENTOUT_PIN.
  * @retval None
  */
void HAL_GPIOEx_ConfigEventout(uint32_t GPIO_PortSource, uint32_t GPIO_PinSource)
{
  /* Verify the parameters */
  assert_param(IS_AFIO_EVENTOUT_PORT(GPIO_PortSource));
  assert_param(IS_AFIO_EVENTOUT_PIN(GPIO_PinSource));

  /* Apply the new configuration */
  MODIFY_REG(AFIO->EVCR, (AFIO_EVCR_PORT) | (AFIO_EVCR_PIN), (GPIO_PortSource) | (GPIO_PinSource));
}

/**
  * @brief  Enables the Event Output.
  * @retval None
  */
void HAL_GPIOEx_EnableEventout(void)
{
  SET_BIT(AFIO->EVCR, AFIO_EVCR_EVOE);
}

/**
  * @brief  Disables the Event Output.
  * @retval None
  */
void HAL_GPIOEx_DisableEventout(void)
{
  CLEAR_BIT(AFIO->EVCR, AFIO_EVCR_EVOE);
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_GPIO_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

