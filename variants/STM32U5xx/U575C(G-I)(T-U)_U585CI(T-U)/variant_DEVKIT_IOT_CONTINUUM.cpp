/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_DEVKIT_IOT_CONTINUUM)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_2,   // D0/TX
  PA_3,   // D1/RX
  PA_0,   // D2/A0
  PA_1,   // D3/A1
  PA_6,   // D4/A2
  PB_10,  // D5
  PB_14,  // D6
  PB_0,   // D7/A3
  PB_1,   // D8/A4
  PB_15,  // D9
  PA_8,   // D10
  PA_11,  // D11
  PB_13,  // D12
  PB_2,   // D13/A5
  PB_3,   // D14/SCK
  PB_4,   // D15/MISO
  PB_5,   // D16/MOSI
  PB_6,   // D17/SCL
  PB_7,   // D18/SDA
  PA_4,   // D19/A6
  PA_5,   // D20
  PA_7,   // D21
  PA_9,   // D22
  PA_10,  // D23
  PA_12,  // D24
  PA_13,  // D25
  PA_14,  // D26
  PA_15,  // D27
  PB_8,   // D28
  PB_9,   // D29
  PB_12,  // D30
  PC_13,  // D31
  PC_14,  // D32
  PC_15,  // D33
  PH_0,   // D34
  PH_1,   // D35
  PH_3    // D36
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  2,  // A0,  PA0
  3,  // A1,  PA1
  4,  // A2,  PA6
  7,  // A3,  PB0
  8,  // A4,  PB1
  13, // A5,  PB2
  19  // A6,  PA4
};

/** System Clock Configuration
*/
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#endif /* ARDUINO_DEVKIT_IOT_CONTINUUM */
