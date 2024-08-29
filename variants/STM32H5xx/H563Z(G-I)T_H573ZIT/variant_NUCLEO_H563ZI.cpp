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
#if defined(ARDUINO_NUCLEO_H563ZI)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_7,  // D0
  PB_6,  // D1
  PG_14, // D2
  PE_13, // D3
  PE_14, // D4
  PE_11, // D5
  PE_9,  // D6
  PG_12, // D7
  PF_3,  // D8
  PD_15, // D9
  PD_14, // D10
  PB_5,  // D11
  PG_9,  // D12
  PA_5,  // D13/A9
  PB_9,  // D14
  PB_8,  // D15
  PC_6,  // D16
  PB_15, // D17
  PB_13, // D18
  PB_12, // D19
  PA_15, // D20
  PC_7,  // D21
  PB_5,  // D22
  PB_3,  // D23
  PG_10, // D24
  PB_4,  // D25
  PG_6,  // D26
  PB_2,  // D27
  PD_13, // D28
  PD_12, // D29
  PD_11, // D30
  PE_2,  // D31
  PA_0,  // D32/A10
  PB_0,  // D33/A11
  PE_0,  // D34
  PA_3,  // D35/A12
  PB_10, // D36
  PE_15, // D37
  PE_6,  // D38
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
  PG_2,  // D49
  PG_3,  // D50
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
  PG_1,  // D64
  PG_0,  // D65
  PD_1,  // D66
  PD_0,  // D67
  PF_0,  // D68
  PF_1,  // D69
  PF_2,  // D70
  PE_9,  // D71
  PB_2,  // D72
  PA_6,  // D73/A0
  PC_0,  // D74/A1
  PC_3,  // D75/A2
  PB_1,  // D76/A3
  PC_2,  // D77/A4
  PF_11, // D78/A5
  PF_12, // D79/A6
  PF_13, // D80/A7
  PF_14, // D81/A8
  PA_1,  // D82/A13
  PA_2,  // D83/A14
  PA_4,  // D84/A15
  PA_7,  // D85/A16
  PA_8,  // D86
  PA_9,  // D87
  PA_10, // D88
  PA_11, // D89
  PA_12, // D90
  PA_13, // D91
  PA_14, // D92
  PB_14, // D93
  PC_1,  // D94/A17
  PC_4,  // D95/A18
  PC_5,  // D96/A19
  PC_13, // D97
  PC_14, // D98
  PC_15, // D99
  PD_8,  // D100
  PD_9,  // D101
  PD_10, // D102
  PF_4,  // D103
  PF_5,  // D104
  PF_6,  // D105
  PF_10, // D106
  PF_15, // D107
  PG_4,  // D108
  PG_5,  // D109
  PG_7,  // D110
  PG_8,  // D111
  PG_11, // D112
  PG_13, // D113
  PG_15, // D114
  PH_0,  // D115
  PH_1   // D116
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  73, // A0,  PA6
  74, // A1,  PC0
  75, // A2,  PC3
  76, // A3,  PB1
  77, // A4,  PC2
  78, // A5,  PF11
  79, // A6,  PF12
  80, // A7,  PF13
  81, // A8,  PF14
  13, // A9,  PA5
  32, // A10, PA0
  33, // A11, PB0
  35, // A12, PA3
  82, // A13, PA1
  83, // A14, PA2
  84, // A15, PA4
  85, // A16, PA7
  94, // A17, PC1
  95, // A18, PC4
  96  // A19, PC5
};

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 250;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_LPUART1
                                             | RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_PLL2R;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK3;
  PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_HCLK;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3Q;

  PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_HSE;
  PeriphClkInitStruct.PLL2.PLL2M = 2;
  PeriphClkInitStruct.PLL2.PLL2N = 125;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 15;
  PeriphClkInitStruct.PLL2.PLL2R = 4;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVQ | RCC_PLL2_DIVR;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PLL2Q;
  PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_PLL2R;

  PeriphClkInitStruct.PLL3.PLL3Source = RCC_PLL3_SOURCE_HSE;
  PeriphClkInitStruct.PLL3.PLL3M = 2;
  PeriphClkInitStruct.PLL3.PLL3N = 96;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 8;
  PeriphClkInitStruct.PLL3.PLL3R = 2;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3_VCIRANGE_0;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3_VCORANGE_MEDIUM;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.PLL3.PLL3ClockOut = RCC_PLL3_DIVQ;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3Q;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
#endif /* ARDUINO_NUCLEO_H563ZI */
