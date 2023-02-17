/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_DISCO_F303VC)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PC_0,  //D0/A0
  PC_2,  //D1/A1
  PF_2,  //D2/A2
  PA_0,  //D3/A23
  PA_2,  //D4/A25
  PA_4,  //D5/A27
  PA_6,  //D6/A29
  PC_4,  //D7/A3
  PB_0,  //D8/A4
  PB_2,  //D9/A5
  PE_8,  //D10/A31
  PE_10, //D11/A33
  PE_12, //D12/A35
  PE_14, //D13/A37
  PB_10, //D14
  PB_12, //D15/A6
  PB_14, //D16/A7
  PD_8,  //D17/A8
  PD_10, //D18/A9
  PD_12, //D19/A10
  PD_14, //D20/A11
  PC_7,  //D21
  PF_9,  //D22
  PF_0,  //D23
  PC_14, //D24
  PE_6,  //D25
  PE_4,  //D26
  PE_2,  //D27
  PE_0,  //D28
  PB_8,  //D29
  PB_6,  //D30
  PB_4,  //D31
  PD_7,  //D32
  PD_5,  //D33
  PD_3,  //D34
  PD_1,  //D35
  PC_12, //D36
  PC_10, //D37
  PA_14, //D38
  PF_6,  //D39
  PA_12, //D40
  PA_10, //D41
  PA_8,  //D42
  PC_8,  //D43
  PC_1,  //D44/A12
  PC_3,  //D45/A13
  PA_1,  //D46/A24
  PA_3,  //D47/A26
  PF_4,  //D48/A14
  PA_5,  //D49/A28
  PA_7,  //D50/A30
  PC_5,  //D51/A15
  PB_1,  //D52/A16
  PE_7,  //D53/A17
  PE_9,  //D54/A32
  PE_11, //D55/A34
  PE_13, //D56/A36
  PE_15, //D57/A38
  PB_11, //D58
  PB_13, //D59/A18
  PB_15, //D60/A19
  PD_9,  //D61/A20
  PD_11, //D62/A21
  PD_13, //D63/A22
  PD_15, //D64
  PC_6,  //D65
  PF_10, //D66
  PF_1,  //D67
  PC_15, //D68
  PC_13, //D69
  PE_5,  //D70
  PE_3,  //D71
  PE_1,  //D72
  PB_9,  //D73
  PB_7,  //D74
  PB_5,  //D75
  PB_3,  //D76
  PD_6,  //D77
  PD_4,  //D78
  PD_2,  //D79
  PD_0,  //D80
  PC_11, //D81
  PA_15, //D82
  PA_13, //D83
  PA_11, //D84
  PA_9,  //D85
  PC_9   //D86

};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  //A0
  1,  //A1
  2,  //A2
  7,  //A3
  8,  //A4
  9,  //A5
  15, //A6
  16, //A7
  17, //A8
  18, //A9
  19, //A10
  20, //A11
  44, //A12
  45, //A13
  48, //A14
  51, //A15
  52, //A16
  53, //A17
  59, //A18
  60, //A19
  61, //A20
  62, //A21
  63, //A22
  3,  //A23
  46, //A24
  4,  //A25
  47, //A26
  5,  //A27
  49, //A28
  6,  //A29
  50, //A30
  10, //A31
  54, //A32
  11, //A33
  55, //A34
  12, //A35
  56, //A36
  13, //A37
  57, //A38
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DISCO_F303VC */
