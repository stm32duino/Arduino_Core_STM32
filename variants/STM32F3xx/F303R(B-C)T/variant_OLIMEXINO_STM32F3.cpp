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
#if defined(ARDUINO_OLIMEXINO_STM32F3)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_3,   //D0 - A6 - RX2
  PA_2,   //D1 - A7 - TX2
  PA_0,   //D2 - A8
  PA_1,   //D3 - A9 - LED2 (yellow)
  PB_5,   //D4
  PB_6,   //D5 - TX1
  PA_8,   //D6
  PA_9,   //D7 - I2C2 SCL

  PA_10,  //D8 - I2C2 SDA
  PB_7,   //D9 - RX1
  PA_4,   //D10 - A10 - SS1
  PA_7,   //D11 - A11 - MOSI1
  PA_6,   //D12 - A12 - MISO1
  PA_5,   //D13 - A13 - SCK1, LED1 (green)
  PB_8,   //D14 - CAN_RX

  PC_0,   //D15 - A0
  PC_1,   //D16 - A1
  PC_2,   //D17 - A2
  PC_3,   //D18 - A3
  PC_4,   //D19 - A4
  PC_5,   //D20 - A5

  PC_13,  //D21
  PC_9,   //D22 - Button (not an actual D pin)

  PC_15,  //D23
  PB_9,   //D24 - CAN_TX
  PD_2,   //D25 - MMC_CS
  PC_10,  //D26
  PB_0,   //D27 - A14
  PB_1,   //D28 - A15
  PB_10,  //D29 - TX3
  PB_11,  //D30 - RX3
  PB_12,  //D31 - A16 - #SS2
  PB_13,  //D32 - A17 - SCK2
  PB_14,  //D33 - A18 - MISO2
  PB_15,  //D34 - A19 - MOSI2
  PC_6,   //D35
  PC_7,   //D36
  PC_8,   //D37

  PF_4,   //D38 - A20 - UEXT_PWR (not actual D pin)
  PC_12   //D39 - USB DISC
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  15, // A0
  16, // A1
  17, // A2
  18, // A3
  19, // A4
  20, // A5
  0,  // A6
  1,  // A7
  2,  // A8
  3,  // A9
  10, // A10
  11, // A11
  12, // A12
  13, // A13
  27, // A14
  28, // A15
  31, // A16
  32, // A17
  33, // A18
  34, // A19
  38  // A20
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

  /* Initializes the CPU, AHB and APB busses clocks */
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
  /* Initializes the CPU, AHB and APB busses clocks */
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

#endif /* ARDUINO_OLIMEXINO_STM32F3 */
