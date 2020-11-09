/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif


// This board doesn't breakout pins (no arduino r3 connections) 
// Pin number
const PinName digitalPin[] = {
  // LEFT
  PC_13, // D0
  PC_14, // D1
  PC_15, // D2
  PF_0, // D3
  PF_1, // D4
  PG_10, // D5
  PA_0, // D6
  PA_1, // D7
  PA_2, // D8
  PA_3, // D9
  PA_4, // D10
  // BOTTOM
  PA_5, // D11
  PA_6, // D12
  PA_7, // D13
  PC_4, // D14
  PB_0, // D15
  PB_1, // D16
  PB_2, // D17
  PB_10, // D18
  PB_11, // D19
  // RIGHT
  PB_12, // D20
  PB_13, // D21
  PB_14, // D22
  PB_15, // D23
  PC_6, // D24
  PA_8, // D25
  PA_9, // D26
  PA_10, // D27
  PA_11, // D28
  PA_12, // D29
  PA_13, // D30
  // TOP
  PA_14, // D31
  PA_15, // D32
  PC_10, // D33
  PC_11, // D34
  PB_3, // D35
  PB_4, // D36
  PB_5, // D37
  PB_6, // D38
  PB_7, // D39
  PB_8, // D40
  PB_9 // D41
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  6,  //PA0
  7,  //PA1
  8,  //PA2
  9, //PA3
  10, //PA4
  11, //PA5
  12, //PA6
  13, //PA7
  45, //PB0
  15, //PB2
  17, //PB11
  22, //PB14
  23, //PB15
  3, //PF0
  4,  //PF1
  5  //PG10
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
#ifdef USBCON
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};
#endif

  /* Configure the main internal regulator output voltage */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK) {
    Error_Handler();
  }

#ifdef USBCON
  /* Initializes the peripherals clocks */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
#endif
}

#ifdef __cplusplus
}
#endif
