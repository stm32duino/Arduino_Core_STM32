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
#if defined(ARDUINO_DISCO_F429ZI)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PF_4,    // 0
  PF_2,    // 1
  PF_0,    // 2
  PC_14,   // 3
  PE_6,    // 4
  PE_4,    // 5
  PE_2,    // 6
  PE_0,    // 7
  PB_8,    // 8
  NC,      // 9  - BOOT0
  PB_6,    // 10
  PB_4,    // 11
  PG_15,   // 12
  PG_13,   // 13
  PG_11,   // 14
  PG_9,    // 15
  PD_7,    // 16
  PD_5,    // 17
  PD_3,    // 18
  PD_1,    // 19
  PC_12,   // 20
  PC_10,   // 21
  PA_14,   // 22
  PA_12,   // 23
  PA_10,   // 24
  PA_8,    // 25
  PC_8,    // 26
  PC_6,    // 27
  PG_7,    // 28
  PG_5,    // 29
  PF_5,    // 30
  PF_3,    // 31
  PF_1,    // 32
  PC_15,   // 33
  PC_13,   // 34
  PE_5,    // 35
  PE_3,    // 36
  PE_1,    // 37
  PB_9,    // 38
  PB_7,    // 39
  PB_5,    // 40
  PB_3,    // 41
  PG_14,   // 42
  PG_12,   // 43
  PG_10,   // 44
  PD_6,    // 45
  PD_4,    // 46
  PD_2,    // 47
  PD_0,    // 48
  PC_11,   // 49
  PA_15,   // 50
  PA_13,   // 51
  PA_11,   // 52
  PA_9,    // 53
  PC_9,    // 54
  PC_7,    // 55
  PG_8,    // 56
  PG_6,    // 57
  PG_4,    // 58
  PF_6,    // 59
  PF_8,    // 60
  PF_10,   // 61
  PH_1,    // 62
  PC_1,    // 63
  PC_3,    // 64
  PA_1,    // 65
  PA_3,    // 66
  PA_5,    // 67
  PA_7,    // 68
  PC_5,    // 69
  PB_1,    // 70
  PF_12,   // 71
  PF_14,   // 72
  PG_0,    // 73
  PE_7,    // 74
  PE_9,    // 75
  PE_11,   // 76
  PE_13,   // 77
  PE_15,   // 78
  PB_11,   // 79
  PB_13,   // 80
  PB_15,   // 81 // Not connected SB26 OFF
  PD_9,    // 82
  PD_11,   // 83
  PD_13,   // 84
  PD_15,   // 85
  PG_3,    // 86
  PF_7,    // 87
  PF_9,    // 88
  PH_0,    // 89
  PC_0,    // 90
  PC_2,    // 91
  PA_0,    // 92
  PA_2,    // 93
  PA_4,    // 94
  PA_6,    // 95
  PC_4,    // 96
  PB_0,    // 97
  PB_2,    // 98 - BOOT1
  PF_11,   // 99
  PF_13,   // 100
  PF_15,   // 101
  PG_1,    // 102
  PE_8,    // 103
  PE_10,   // 104
  PE_12,   // 105
  PE_14,   // 106
  PB_10,   // 107
  PB_12,   // 108
  PB_14,   // 109 // Not connected SB27 OFF
  PD_8,    // 110
  PD_10,   // 111
  PD_12,   // 112
  PD_14,   // 113
  PG_2     // 114
};
// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  0,       // A0,
  30,      // A1,
  31,      // A2,
  59,      // A3,
  60,      // A4,
  61,      // A5,
  63,      // A6,
  64,      // A7,
  65,      // A8,
  66,      // A9,
  67,      // A10,
  68,      // A11,
  69,      // A12,
  70,      // A13,
  87,      // A14,
  88,      // A15,
  90,      // A16,
  91,      // A17,
  92,      // A18,
  93,      // A19,
  94,      // A20,
  95,      // A21,
  96,      // A22,
  97       // A23,
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  None
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DISCO_F429ZI */
