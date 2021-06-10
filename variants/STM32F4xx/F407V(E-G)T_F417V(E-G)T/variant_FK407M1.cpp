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
#if defined(ARDUINO_FK407M1)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  // Left Side (looking at board rear, SWD top left))
  //Ext   //Int
  //GND    //GND
  PD_10,  PD_11,
  PB_15,  PD_9,
  PB_12,  PD_8,
  PB_14,  PB_11,
  PE_8,   PB_13,
  PB_10,  PE_7,
  PE_14,  PE_15,
  PE_12,  PE_13,
  PE_11,  PE_10,
  PE_9,   PB_1,
  PB_2,   PC_5,
  PB_0,   PA_7,
  PC_4,   PA_6,
  PA_5,   PA_3,
  PA_4,   PC_3,
  PA_0,   PA_2,
  PA_1,   PD_13,
  PD_14,  PC_0,
  PC_1,   PC_2,
  // Right Side
  //Int   //Ext
  //5V    //5V
  //3V3   //3V3
  PA_12,  PA_11,
  PA_10,  PD_12,
  PC_9,   PA_9,
  PA_8,   PC_10,
  PC_11,  PC_12,
  PD_0,   PD_1,
  PD_2,   PD_3,
  PD_4,   PD_5,
  PB_5,   PB_4,
  PB_7,   PB_6,
  PB_9,   PB_8,
  PE_1,   PE_0,
  PE_2,   PE_6,
  PE_3,   PE_5,
  PB_3,   PE_4,
  PD_6,   PD_7,
  PC_7,   PC_8,
  PD_15,  PC_6,
  PC_13,  PA_15 // LED and Button pins - not broken out on the board
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  30, //A0
  32, //A1
  31, //A2
  27, //A3
  28, //A4
  26, //A5
  25, //A6
  23, //A7
  22, //A8
  19, //A9
  35, //A10
  36, //A11
  37, //A12
  29, //A13
  24, //A14
  21  //A15
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

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB busses clocks */
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

#endif /* ARDUINO_FK407M1 */
