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
#if defined(ARDUINO_NUCLEO_H745ZI_Q)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_7,    // 0
  PB_6,    // 1
  PG_14,   // 2
  PE_13,   // 3
  PE_14,   // 4
  PE_11,   // 5
  PA_8,    // 6
  PG_12,   // 7
  PG_9,    // 8
  PD_15,   // 9
  PD_14,   // 10
  PB_5,    // 11
  PA_6,    // 12
  PA_5,    // 13
  PB_9,    // 14
  PB_8,    // 15
  PC_6,    // 16
  PB_15,   // 17
  PB_13,   // 18
  PB_12,   // 19
  PA_15,   // 20
  PC_7,    // 21
  PB_5,    // 22
  PB_3,    // 23
  PA_4,    // 24
  PB_4,    // 25
  PG_6,    // 26
  PB_2,    // 27
  PD_13,   // 28
  PD_12,   // 29
  PD_11,   // 30
  PE_2,    // 31
  PA_0,    // 32
  PB_0,    // 33
  PE_0,    // 34
  PB_11,   // 35
  PB_10,   // 36
  PE_15,   // 37
  PE_6,    // 38
  PE_12,   // 39
  PE_10,   // 40
  PE_7,    // 41
  PE_8,    // 42
  PC_8,    // 43
  PC_9,    // 44
  PC_10,   // 45
  PC_11,   // 46
  PC_12,   // 47
  PD_2,    // 48
  PG_10,   // 49
  PG_8,    // 50
  PD_7,    // 51
  PD_6,    // 52
  PD_5,    // 53
  PD_4,    // 54
  PD_3,    // 55
  PE_2,    // 56
  PE_4,    // 57
  PE_5,    // 58
  PE_6,    // 59
  PE_3,    // 60
  PF_8,    // 61
  PF_7,    // 62
  PF_9,    // 63
  PD_10,   // 64
  PB_14,   // 65
  PD_1,    // 66
  PD_0,    // 67
  PF_15,   // 68
  PF_14,   // 69
  PB_5,    // 70
  PE_9,    // 71
  PB_2,    // 72
  PA_13,   // 73
  PA_14,   // 74
  PC_13,   // 75
  PC_14,   // 76
  PC_15,   // 77
  PH_0,    // 78
  PH_1,    // 79
  PE_1,    // 80
  PD_9,    // 81
  PA_1,    // 82
  PC_1,    // 83
  PG_13,   // 84
  PG_11,   // 85
  PA_7,    // 86
  PA_9,    // 87
  PA_10,   // 88
  PG_7,    // 89
  PC_5,    // 90
  PD_8,    // 91
  PA_12,   // 92
  PA_11,   // 93
  PC_4,    // 94
  PA_3,    // 95
  PC_0,    // 96
  PC_3,    // 97
  PB_1,    // 98
  PC_2,    // 99
  PF_11,   // 100
  PF_6,    // 101
  PF_10,   // 102
  PA_2     // 103
};


// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  95,  // 0
  96,  // 1
  97,  // 2
  98,  // 3
  99,  // 4
  100, // 5
  101, // 6
  102, // 7
  103, // 8
  12,  // 9
  13,  // 10
  24,  // 11
  32,  // 12
  33,  // 13
  61,  // 14
  62,  // 15
  63,  // 16
  69,  // 17
  82,  // 18
  83,  // 19
  86,  // 20
  90,  // 21
  94   // 22
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


  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_EXTERNAL_SOURCE_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_H745ZI_Q */

