/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_WL33CC1)
#include "pins_arduino.h"
#include "pinmap.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_7,   // D0
  PB_6,   // D1
  PA_9,   // D2
  PA_0,   // D3
  PA_8,   // D4
  PA_13,  // D5
  PA_12,  // D6
  PA_4,   // D7
  PA_5,   // D8
  PA_14,  // D9
  PB_10,  // D10
  PB_9,   // D11
  PB_8,   // D12
  PB_11,  // D13
  PA_7,   // D14
  PA_6,   // D15
  PB_0,   // D16
  PB_1,   // D17/A0
  PB_2,   // D18
  PB_3,   // D19/A1
  PB_14,  // D20
  PB_5,   // D21/A2
  PA_1,   // D22
  PA_15,  // D23
  PB_4,   // D24
  PB_15,  // D25
  PA_2,   // D26
  PA_3,   // D27
  PA_10,  // D28
  PA_11,  // D29
  PB_12,  // D30
  PB_13   // D31
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  17, // A0,  PB1
  19, // A1,  PB3
  21  // A2,  PB5
};

// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Configure the SYSCLKSource and SYSCLKDivider
  */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_RC64MPLL_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_WAIT_STATES_1) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLK_DIV2;
  PeriphClkInitStruct.KRMRateMultiplier = 2;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

WEAK void initVariant(void)
{
  pin_function(PA_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF0_SWDIO));
  pin_function(PA_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLDOWN, GPIO_AF0_SWCLK));
  HAL_PWREx_EnableGPIOPullUp(PWR_GPIO_A, PWR_GPIO_BIT_2);
  HAL_PWREx_DisableGPIOPullUp(PWR_GPIO_A, PWR_GPIO_BIT_3);
  HAL_PWREx_DisableGPIOPullDown(PWR_GPIO_A, PWR_GPIO_BIT_3);
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_WL33CC1 */
