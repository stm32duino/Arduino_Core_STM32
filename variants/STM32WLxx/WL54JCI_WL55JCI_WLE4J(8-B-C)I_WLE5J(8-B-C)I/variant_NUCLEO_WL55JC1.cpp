/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_WL55JC1)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_7,  // D0
  PB_6,  // D1
  PB_12, // D2
  PB_3,  // D3/A6
  PB_5,  // D4
  PB_8,  // D5
  PB_10, // D6
  PC_1,  // D7
  PC_2,  // D8
  PA_9,  // D9
  PA_4,  // D10
  PA_7,  // D11
  PA_6,  // D12
  PA_5,  // D13
  PA_11, // D14/A7
  PA_12, // D15/A8
  PB_1,  // D16/A0
  PB_2,  // D17/A1
  PA_10, // D18/A2
  PB_4,  // D19/A3
  PB_14, // D20/A4
  PB_13, // D21/A5
  PA_0,  // D22
  PC_3,  // D23
  PA_1,  // D24
  PB_11, // D25
  PB_15, // D26
  PB_9,  // D27
  PB_0,  // D28
  PA_8,  // D29
  PC_0,  // D30
  PC_6,  // D31
  PC_5,  // D32
  PC_4,  // D33
  PC_15, // D34
  PC_14, // D35
  PC_13, // D36
  PA_15, // D37/A9
  PA_14, // D38/A10
  PA_13, // D39/A11
  PA_2,  // D40
  PA_3,  // D41
  PH_3   // D42
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0,  PB1
  17, // A1,  PB2
  18, // A2,  PA10
  19, // A3,  PB4
  20, // A4,  PB14
  21, // A5,  PB13
  3,  // A6,  PB3
  14, // A7,  PA11
  15, // A8,  PA12
  37, // A9,  PA15
  38, // A10, PA14
  39  // A11, PA13
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
                                | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_WL55JC1 */
