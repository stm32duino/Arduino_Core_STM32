/*
 *******************************************************************************
 * Copyright (c) 2025, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_WB09KE)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_5,   // D0/A3
  PB_4,   // D1
  PB_14,  // D2
  PB_3,   // D3/A0
  PA_11,  // D4
  PB_7,   // D5
  PB_6,   // D6
  PA_8,   // D7
  PB_15,  // D8
  PA_0,   // D9
  PA_9,   // D10
  PA_11,  // D11
  PA_8,   // D12
  PB_3,   // D13/A0
  PB_7,   // D14
  PB_6,   // D15
  PB_2,   // D16
  PB_1,   // D17/A2
  PB_0,   // D18
  PA_10,  // D19
  PA_2,   // D20
  PA_3,   // D21/A1
  PB_12,  // D22
  PB_13,  // D23
  PA_1    // D24
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  3,  // A0,  PB3
  21, // A1,  PA3
  17, // A2,  PB1
  0   // A3,  PB5
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Configure the SYSCLKSource and SYSCLKDivider
  */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_RC64MPLL;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_RC64MPLL_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_WAIT_STATES_1) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLK_DIV4;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_WB09KE */
