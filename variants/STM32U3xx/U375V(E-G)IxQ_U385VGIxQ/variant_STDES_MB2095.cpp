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
#if defined(ARDUINO_STDES_MB2095)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_12, // D0
  PA_11, // D1
  PH_3,  // D2
  PB_1,  // D3/A11
  PB_13, // D4
  PB_10, // D5
  PB_11, // D6
  PA_14, // D7
  PA_13, // D8
  PD_0,  // D9
  PD_1,  // D10
  PD_15, // D11
  PB_9,  // D12
  PB_6,  // D13
  PA_15, // D14
  PE_13, // D15
  PE_15, // D16
  PE_14, // D17
  PB_3,  // D18
  PD_5,  // D19
  PA_6,  // D20/A12
  PB_2,  // D21/A13
  PA_9,  // D22
  PA_10, // D23
  PD_14, // D24
  PC_0,  // D25/A14
  PC_1,  // D26/A15
  PA_2,  // D27/A16
  PE_0,  // D28
  PC_7,  // D29
  PE_8,  // D30
  PB_8,  // D31
  PE_9,  // D32
  PB_4,  // D33
  PE_5,  // D34
  PE_4,  // D35
  PE_7,  // D36
  PE_6,  // D37
  PE_2,  // D38
  PC_12, // D39
  PD_2,  // D40
  PC_8,  // D41
  PC_9,  // D42
  PC_10, // D43
  PC_11, // D44
  PH_0,  // D45
  PA_4,  // D46/A0
  PA_5,  // D47/A1
  PA_3,  // D48/A2
  PA_0,  // D49/A3
  PA_1,  // D50/A4
  PD_13, // D51/A5
  PD_12, // D52/A6
  PE_10, // D53
  PE_12, // D54
  PB_0,  // D55/A7
  PA_7,  // D56/A8
  PC_6,  // D57
  PD_4,  // D58
  PC_2,  // D59/A9
  PC_3,  // D60/A10
  PD_7,  // D61
  PE_3,  // D62
  PE_11, // D63
  PB_5,  // D64
  PB_7,  // D65
  PD_11, // D66/A17
  PB_15, // D67
  PB_14, // D68
  PA_8,  // D69
  PD_8,  // D70
  PD_9,  // D71
  PC_14, // D72
  PC_15  // D73
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  46, // A0,  PA4
  47, // A1,  PA5
  48, // A2,  PA3
  49, // A3,  PA0
  50, // A4,  PA1
  51, // A5,  PD13
  52, // A6,  PD12
  55, // A7,  PB0
  56, // A8,  PA7
  59, // A9,  PC2
  60, // A10, PC3
  3,  // A11, PB1
  20, // A12, PA6
  21, // A13, PB2
  25, // A14, PC0
  26, // A15, PC1
  27, // A16, PA2
  66  // A17, PD11
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

  /** Configure the System Power Supply
  */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK) {
    Error_Handler();
  }

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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE
                                     | RCC_OSCILLATORTYPE_MSIS;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_DAC1SH | RCC_PERIPHCLK_ICLK
                                       | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USB1;
  PeriphClkInit.Dac1SampleHoldClockSelection = RCC_DAC1SHCLKSOURCE_LSE;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.IclkClockSelection = RCC_ICLKCLKSOURCE_HSI48;
  PeriphClkInit.Usb1ClockSelection = RCC_USB1CLKSOURCE_ICLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}
#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_STDES_MB2095 */
