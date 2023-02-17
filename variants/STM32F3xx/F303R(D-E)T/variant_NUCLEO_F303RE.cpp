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
#if defined(ARDUINO_NUCLEO_F303RE)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_3,  //D0/A14
  PA_2,  //D1/A15
  PA_10, //D2
  PB_3,  //D3
  PB_5,  //D4
  PB_4,  //D5
  PB_10, //D6
  PA_8,  //D7
  PA_9,  //D8
  PC_7,  //D9
  PB_6,  //D10
  PA_7,  //D11/A6
  PA_6,  //D12/A7
  PA_5,  //D13/A16
  PB_9,  //D14
  PB_8,  //D15
  // ST Morpho
  // CN7 Left Side
  PC_10, //D16
  PC_12, //D17
  NC,    //D18 - BOOT0
  PA_13, //D19 - SWD
  PA_14, //D20 - SWD
  PA_15, //D21
  PB_7,  //D22
  PC_13, //D23
  PC_14, //D24
  PC_15, //D25
  PF_0,  //D26
  PF_1,  //D27
  PC_2,  //D28/A8
  PC_3,  //D29/A9
  // CN7 Right Side
  PC_11, //D30
  PD_2,  //D31
  // CN10 Left Side
  PC_9,  //D32
  // CN10 Right side
  PC_8,  //D33
  PC_6,  //D34
  PC_5,  //D35/A10
  PA_12, //D36
  PA_11, //D37
  PB_12, //D38/A22
  PB_11, //D39/A11
  PB_2,  //D40/A12
  PB_1,  //D41/A19
  PB_15, //D42/A17
  PB_14, //D43/A18
  PB_13, //D44/A20
  PC_4,  //D45/A13
  PA_0,  //D46/A0
  PA_1,  //D47/A1
  PA_4,  //D48/A2
  PB_0,  //D49/A3
  PC_1,  //D50/A4
  PC_0   //D51/A5
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  46, //A0
  47, //A1
  48, //A2
  49, //A3
  50, //A4
  51, //A5
  11, //A6
  12, //A7
  28, //A8
  29, //A9
  35, //A10
  39, //A11
  40, //A12
  45, //A13
  0,  //A14
  1,  //A15
  13, //A16
  42, //A17
  43, //A18
  41, //A19
  44, //A20
  38  //A21
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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

#endif /* ARDUINO_NUCLEO_F303RE */
