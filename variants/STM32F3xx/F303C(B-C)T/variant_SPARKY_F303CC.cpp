/*
 *******************************************************************************
 * Copyright (c) 2018-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_SPARKY_F303CC)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PB_9,  //D0  - CAN_TX
  PB_8,  //D1  - CAN_RX
  PB_7,  //D2  - UART1_RX or I2C1_SDC
  PB_6,  //D3  - UART1_TX or I2C1_SCL
  PB_5,  //D4  - LED_RED
  PB_4,  //D5  - LED_BLUE
  PB_3,  //D6
  PA_15, //D7
  PA_12, //D8  - USB_DP
  PA_11, //D9  - USB_DM
  PA_10, //D10 - SDA MPU-9150
  PA_9,  //D11 - SCL MPU-9150
  PA_8,  //D12
  PB_15, //D13/A14
  PB_14, //D14/A13
  PB_13, //D15/A12
  PB_12, //D16/A11
  PC_13, //D17 - LED on Bluepill Board
  PC_14, //D18
  PC_15, //D19
  PA_0,  //D20/A0
  PA_1,  //D21/A1
  PA_2,  //D22/A2
  PA_3,  //D23/A3 - RCX
  PA_4,  //D24/A4
  PA_5,  //D25/A5
  PA_6,  //D26/A6
  PA_7,  //D27/A7
  PB_0,  //D28/A8
  PB_1,  //D29/A9
  PB_10, //D30 - UART3_TX
  PB_11, //D31 - UART3_RX
  PB_2,  //D32/A10 - BOOT1
  PA_13, //D33 - SWDI0
  PA_14, //D34 - SWCLK
  PF_0,  //D35 - OSC IN
  PF_1   //D36 - OSC OUT
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  20, // A0
  21, // A1
  22, // A2
  23, // A3
  24, // A4
  25, // A5
  26, // A6
  27, // A7
  28, // A8
  29, // A9
  32, // A10
  16, // A11
  15, // A12
  14, // A13
  13  // A14
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /**Initializes the CPU, AHB and APB busses clocks
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

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART3
                                       | RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_SPARKY_F303CC */
