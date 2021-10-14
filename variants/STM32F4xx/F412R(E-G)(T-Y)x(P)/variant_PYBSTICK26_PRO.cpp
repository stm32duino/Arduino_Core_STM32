/*
* ******************************************************************************
*Copyright(c) 2011 - 2021, STMicroelectronics
*All rights reserved.
*
*This software component is licensed by ST under BSD 3 - Clause license,
* the "License"; You may not use this file except in compliance with the
*License. You may obtain a copy of the License at:
*opensource.org / licenses / BSD - 3 - Clause
*
*******************************************************************************
*/
#if defined(ARDUINO_PYBSTICK26_PRO)

#include "pins_arduino.h"

// Digital PinName array (up to 64 pins)
const PinName digitalPin[] = {
  PB_9,
  PB_8,
  PB_7,
  PA_2,
  PA_3,
  PA_0,
  PB_3,
  PB_10,
  PB_12,
  PB_13,
  PB_14,
  PA_7,
  PB_4,
  PA_5,
  PA_10,
  PA_15,
  PA_4,
  PC_3,
  PC_5,
  PC_6,
  PC_7,
  PA_13,
  PA_14,
  PB_0,
  PB_1,
  PC_13,
  PA_11,
  PA_12,
  PC_14,
  PC_15,
  PH_0,
  PH_1,
  PA_6,
  PB_6,
  PA_8,
  PA_9,
  PB_5,
  PB_15,
  PC_9,
  PC_10,
  PC_8,
  PA_1,
  PB_2
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  3,  // A0
  4,  // A1
  5,  // A2
  11, // A3
  13, // A4
  16, // A5
  17, // A6
  18  // A7
};
// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 72;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 8;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  PeriphClkInitStruct.PLLI2S.PLLI2SQ = 3;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLI2SQ;
  PeriphClkInitStruct.PLLI2SSelection = RCC_PLLI2SCLKSOURCE_PLLSRC;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_PYBSTICK26_PRO */
