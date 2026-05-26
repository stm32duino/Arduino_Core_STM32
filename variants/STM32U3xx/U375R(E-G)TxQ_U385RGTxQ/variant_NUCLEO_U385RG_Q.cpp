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
#if defined(ARDUINO_NUCLEO_U385RG_Q)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_3,  // D0/A6
  PA_2,  // D1/A7
  PC_8,  // D2
  PB_3,  // D3
  PB_5,  // D4
  PB_4,  // D5
  PB_10, // D6
  PA_8,  // D7
  PC_7,  // D8
  PC_6,  // D9
  PC_9,  // D10
  PA_7,  // D11/A8
  PA_6,  // D12/A9
  PA_5,  // D13/A10
  PB_14, // D14
  PB_13, // D15
  PA_0,  // D16/A2
  PA_1,  // D17/A3
  PA_4,  // D18/A4
  PB_0,  // D19/A5
  PC_1,  // D20
  PC_0,  // D21
  PC_10, // D22
  PC_12, // D23
  PH_3,  // D24
  PA_13, // D25
  PA_14, // D26
  PA_15, // D27
  PC_13, // D28
  PC_14, // D29
  PC_15, // D30
  PH_0,  // D31
  PH_1,  // D32
  PC_2,  // D33/A11
  PC_3,  // D34/A12
  PC_11, // D35
  PD_2,  // D36
  PA_9,  // D37
  PA_10, // D38
  PA_12, // D39
  PA_11, // D40/A13
  PB_2,  // D41/A14
  PB_1,  // D42
  PB_15, // D43
  PB_8,  // D44
  PB_6,  // D45
  PB_7   // D46
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  16, // A0,  PA0
  17, // A1,  PA1
  18, // A2,  PA4
  19, // A3,  PB0
  20, // A4,  PC1
  21, // A5,  PC0
  0,  // A6,  PA3
  1,  // A7,  PA2
  11, // A8,  PA7
  12, // A9,  PA6
  13, // A10, PA5
  33, // A11, PC2
  34, // A12, PC3
  41, // A13, PB2
  42  // A14, PB1
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

  /** Enable Epod Booster
  */
  if (HAL_RCCEx_EpodBoosterClkConfig(RCC_EPODBOOSTER_SOURCE_MSIS, RCC_EPODBOOSTER_DIV1) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_PWREx_EnableEpodBooster() != HAL_OK) {
    Error_Handler();
  }

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }

  /** Set Flash latency before increasing MSIS
  */
  __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_2);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_MSIS;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.MSISState = RCC_MSI_ON;
  RCC_OscInitStruct.MSISSource = RCC_MSI_RC0;
  RCC_OscInitStruct.MSISDiv = RCC_MSI_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSIS;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the peripherals clock
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USB1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.IclkClockSelection = RCC_ICLKCLKSOURCE_HSI48;
  PeriphClkInit.Usb1ClockSelection = RCC_USB1CLKSOURCE_ICLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
  /* Enable the SMPS regulator to improve power efficiency*/
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK) {
    Error_Handler();
  }
}
#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_U385RG_Q* */
