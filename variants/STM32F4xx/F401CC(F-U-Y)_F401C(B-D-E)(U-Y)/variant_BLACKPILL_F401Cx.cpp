/*
 *******************************************************************************
 * Copyright (c) 2011-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_BLACKPILL_F401CC) || defined(ARDUINO_BLACKPILL_F401CE)

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,  // Digital pin 0
  PA_1,  // Digital pin 1
  PA_2,  // Digital pin 2
  PA_3,  // Digital pin 3
  PA_4,  // Digital pin 4
  PA_5,  // Digital pin 5
  PA_6,  // Digital pin 6
  PA_7,  // Digital pin 7
  PA_8,  // Digital pin 8
  PA_9,  // Digital pin 9
  PA_10, // Digital pin 10
  PA_11, // Digital pin 11
  PA_12, // Digital pin 12
  PA_13, // Digital pin 13
  PA_14, // Digital pin 14
  PA_15, // Digital pin 15

  PB_0,  // Digital pin 16
  PB_1,  // Digital pin 17
  PB_2,  // Digital pin 18
  PB_3,  // Digital pin 19
  PB_4,  // Digital pin 20
  PB_5,  // Digital pin 21
  PB_6,  // Digital pin 22
  PB_7,  // Digital pin 23
  PB_8,  // Digital pin 24
  PB_9,  // Digital pin 25
  PB_10, // Digital pin 26
  PB_12, // Digital pin 27
  PB_13, // Digital pin 28
  PB_14, // Digital pin 29
  PB_15, // Digital pin 30

  PC_13, // Digital pin 31
  PC_14, // Digital pin 32
  PC_15, // Digital pin 33

  PH_0,  // Digital pin 34, used by the external oscillator
  PH_1   // Digital pin 35, used by the external oscillator
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA3
  4,  // A4,  PA4
  5,  // A5,  PA5
  6,  // A6,  PA6
  7,  // A7,  PA7
  16, // A8,  PB0
  17, // A9,  PB1
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

#endif /* (ARDUINO_BLACKPILL_F401CC) || (ARDUINO_BLACKPILL_F401CE) */
