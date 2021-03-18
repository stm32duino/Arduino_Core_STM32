/*
 *******************************************************************************
 * Copyright (c) 2017-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_B_L072Z_LRWAN1)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_3,
  PA_2,
  PA_10,
  PB_13,
  PB_5,
  PB_7,
  PB_2,
  PA_8,
  PA_9,
  PB_12,
  PB_6,
  PB_15,
  PB_14,
  PB_13,
  PB_9,
  PB_8,
  // Non-arduino headers
  // Connector CN2
  NC,
  PA_13,
  PA_14,
  PH_1,
  PH_0,
  // Connector CN3
  PA_1,
  PC_2,
  PC_1,
  PA_12,
  PA_11,
  PA_0,
  PA_0,
  PA_4,
  PA_4,
  PA_5,
  PC_0,
  PA_7,
  PA_6,
  PB_3,
  PA_15,
  PB_4,
  PB_1,
  PB_0,
  PC_13,
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  26, // A0
  27, // A1
  28, // A2
  29  // A3
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/** System Clock Configuration
*/
WEAK void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_B_L072Z_LRWAN1 */
