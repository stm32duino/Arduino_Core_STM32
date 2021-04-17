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
#if defined(ARDUINO_FEATHER_F405)

#include "pins_arduino.h"

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  PB_11,  //D0
  PB_10,
  PB_3,
  PB_4,
  PB_5,
  PC_7,
  PC_6,
  PA_15,  // D7
  PC_0,   // D8
  PB_8,
  PB_9,
  PC_3,
  PC_2,
  PC_1,   // D13
  PB_7,   // D14 SDA
  PB_6,   // D15 SCL
  PA_4,   // D16 - A0
  PA_5,
  PA_6,
  PA_7,
  PC_4,
  PC_5,
  PA_3,   // D22 - A6
  PB_13,  // D23 SCK
  PB_14,  // D24 MISO
  PB_15,  // D25 MOSI
  PC_8,   // D26 SDIO
  PC_9,
  PC_10,
  PC_11,
  PC_12,
  PD_2,
  PB_12,  // D32 - SD Detect
  PC_14,  // D33 - OSC32
  PC_15,  // D34 - OSC32
  PA_11,  // D35 D+
  PA_12,  // D36 D-
  PA_13,  // D37 SWDIO
  PA_14,  // D38 SWCLK
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0
  17, // A1
  18, // A2
  19, // A3
  20, // A4
  21, // A5
  22  // A6
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

  /**Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  /* Ensure CCM RAM clock is enabled */
  __HAL_RCC_CCMDATARAMEN_CLK_ENABLE();

}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_FEATHER_F405 */
