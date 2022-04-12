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
#if defined(ARDUINO_NUCLEO_U575ZI_Q)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PG_8,  // D0
  PG_7,  // D1
  PF_15, // D2/A9
  PE_13, // D3
  PF_14, // D4/A10
  PE_11, // D5
  PE_9,  // D6
  PF_13, // D7
  PF_12, // D8
  PD_15, // D9
  PD_14, // D10
  PA_7,  // D11/A11
  PA_6,  // D12/A12
  PA_5,  // D13/A13
  PB_9,  // D14
  PB_8,  // D15
  PC_6,  // D16
  PD_11, // D17/A14
  PB_13, // D18
  PD_12, // D19/A15
  PA_4,  // D20/A16
  PB_4,  // D21
  PB_5,  // D22
  PB_3,  // D23
  PA_4,  // D24
  PB_4,  // D25
  PA_2,  // D26
  PB_10, // D27
  PE_15, // D28
  PB_0,  // D29
  PE_12, // D30
  PE_14, // D31
  PA_0,  // D32/A17
  PA_8,  // D33
  PE_0,  // D34
  PB_11, // D35
  PB_10, // D36
  PE_15, // D37
  PE_14, // D38
  PE_12, // D39
  PE_10, // D40
  PE_7,  // D41
  PE_8,  // D42
  PC_8,  // D43
  PC_9,  // D44
  PC_10, // D45
  PC_11, // D46
  PC_12, // D47
  PD_2,  // D48
  PF_3,  // D49
  PF_5,  // D50
  PD_7,  // D51
  PD_6,  // D52
  PD_5,  // D53
  PD_4,  // D54
  PD_3,  // D55
  PE_2,  // D56
  PE_4,  // D57
  PE_5,  // D58
  PE_6,  // D59
  PE_3,  // D60
  PF_8,  // D61
  PF_7,  // D62
  PF_9,  // D63
  PG_1,  // D64/A18
  PG_0,  // D65/A19
  PD_1,  // D66
  PD_0,  // D67
  PF_0,  // D68
  PF_1,  // D69
  PF_2,  // D70
  PB_6,  // D71
  PB_2,  // D72/A20
  PA_3,  // D73/A0
  PA_2,  // D74/A1
  PC_3,  // D75/A2
  PB_0,  // D76/A3
  PC_1,  // D77/A4
  PC_0,  // D78/A5
  PB_1,  // D79/A6
  PC_2,  // D80/A7
  PA_1,  // D81/A8
  PA_9,  // D82
  PA_10, // D83
  PA_11, // D84
  PA_12, // D85
  PA_13, // D86
  PA_14, // D87
  PA_15, // D88
  PB_7,  // D89
  PB_14, // D90
  PB_15, // D91
  PC_7,  // D92
  PC_13, // D93
  PC_14, // D94
  PC_15, // D95
  PD_8,  // D96
  PD_9,  // D97
  PD_10, // D98
  PD_13, // D99/A21
  PE_1,  // D100
  PF_4,  // D101
  PF_6,  // D102
  PF_10, // D103
  PF_11, // D104
  PG_2,  // D105
  PG_3,  // D106
  PG_4,  // D107
  PG_5,  // D108
  PG_6,  // D109
  PG_9,  // D110
  PG_10, // D111
  PG_12, // D112
  PG_13, // D113
  PG_14, // D114
  PG_15, // D115
  PH_0,  // D116
  PH_1,  // D117
  PH_3   // D118
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  73, // A0,  PA3
  74, // A1,  PA2
  75, // A2,  PC3
  76, // A3,  PB0
  77, // A4,  PC1
  78, // A5,  PC0
  79, // A6,  PB1
  80, // A7,  PC2
  81, // A8,  PA1
  2,  // A9,  PF15
  4,  // A10, PF14
  11, // A11, PA7
  12, // A12, PA6
  13, // A13, PA5
  17, // A14, PD11
  19, // A15, PD12
  20, // A16, PA4
  32, // A17, PA0
  64, // A18, PG1
  65, // A19, PG0
  72, // A20, PB2
  99  // A21, PD13
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
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {};

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_DAC1
                                       | RCC_PERIPHCLK_CLK48;
  PeriphClkInit.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_HSI;
  PeriphClkInit.Dac1ClockSelection = RCC_DAC1CLKSOURCE_LSE;
  PeriphClkInit.IclkClockSelection = RCC_CLK48CLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
  /** Enable the SYSCFG APB clock
  */
  __HAL_RCC_CRS_CLK_ENABLE();
  /** Configures CRS
  */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_NUCLEO_U575ZI_Q */
